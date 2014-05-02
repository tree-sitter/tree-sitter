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
    [ts_aux_sym_token15] = "'*'",
    [ts_aux_sym_token16] = "'/'",
    [ts_aux_sym_token17] = "'+'",
    [ts_aux_sym_token18] = "'-'",
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
            if (lookahead == '/')
                ADVANCE(15);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'd')
                ADVANCE(30);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(20);
            if (lookahead == '\\')
                ADVANCE(18);
            LEX_ERROR();
        case 16:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if (lookahead == '\\')
                ADVANCE(18);
            LEX_ERROR();
        case 17:
            ACCEPT_TOKEN(ts_sym_regex);
        case 18:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(19);
            if (lookahead == '\\')
                ADVANCE(18);
            LEX_ERROR();
        case 19:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if (lookahead == '\\')
                ADVANCE(18);
            ACCEPT_TOKEN(ts_sym_regex);
        case 20:
            if (!(lookahead == '\n'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym_comment);
        case 21:
            if (lookahead == '.')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            ACCEPT_TOKEN(ts_sym_number);
        case 22:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            LEX_ERROR();
        case 23:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(23);
            ACCEPT_TOKEN(ts_sym_number);
        case 24:
            ACCEPT_TOKEN(ts_aux_sym_token33);
        case 25:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
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
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 28:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'k')
                ADVANCE(29);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 29:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 30:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(31);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 31:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(32);
            ACCEPT_TOKEN(ts_sym_identifier);
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
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
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
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token14);
        case 36:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(37);
            if (lookahead == 'o')
                ADVANCE(41);
            if (lookahead == 'u')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 37:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 38:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 's')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 39:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 40:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_false);
        case 41:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 42:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 43:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'n')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 44:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'c')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 45:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 46:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'i')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 47:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'o')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 48:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'n')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 49:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token30);
        case 50:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'f')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 51:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 52:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 53:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 54:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 55:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_null);
        case 56:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 57:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 58:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 59:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 60:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'n')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 61:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 62:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'v') ||
                ('x' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'w')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 63:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'i')
                ADVANCE(64);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 64:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(65);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 65:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'c')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 66:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('i' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'h')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 67:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 68:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(69);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 69:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(70);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 70:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(71);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 71:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym_true);
        case 72:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(73);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 73:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'r')
                ADVANCE(74);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 74:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 75:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 76:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == '\n')
                ADVANCE(77);
            if (lookahead == '&')
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 77:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == '\n')
                ADVANCE(77);
            if (lookahead == '&')
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
            if (lookahead == '|')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 78:
            if (lookahead == '&')
                ADVANCE(79);
            LEX_ERROR();
        case 79:
            ACCEPT_TOKEN(ts_aux_sym_token20);
        case 80:
            ACCEPT_TOKEN(ts_aux_sym_token15);
        case 81:
            ACCEPT_TOKEN(ts_aux_sym_token17);
        case 82:
            ACCEPT_TOKEN(ts_aux_sym_token18);
        case 83:
            ACCEPT_TOKEN(ts_aux_sym_token32);
        case 84:
            ACCEPT_TOKEN(ts_aux_sym_token16);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
            if (lookahead == '/')
                ADVANCE(15);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'd')
                ADVANCE(30);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
            if (lookahead == '/')
                ADVANCE(15);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
                ADVANCE(32);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 157:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '\\')
                ADVANCE(18);
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
                ADVANCE(37);
            if (lookahead == 'u')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 159:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == '&')
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
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
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 166:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(166);
            if (lookahead == '{')
                ADVANCE(75);
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
                ADVANCE(78);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == '-')
                ADVANCE(82);
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
                ADVANCE(24);
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
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
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
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
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
            if (lookahead == '/')
                ADVANCE(15);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'd')
                ADVANCE(30);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
            if (lookahead == '/')
                ADVANCE(15);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
            if (lookahead == '/')
                ADVANCE(157);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
            if (lookahead == '/')
                ADVANCE(15);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'd')
                ADVANCE(30);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
            if (lookahead == '/')
                ADVANCE(15);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'd')
                ADVANCE(30);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
                ADVANCE(78);
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(82);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(185);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
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
                ADVANCE(24);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
                ADVANCE(78);
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(82);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(185);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
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
                ADVANCE(24);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
            if (lookahead == '|')
                ADVANCE(94);
            if (lookahead == '}')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 185:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(20);
            if (lookahead == '\\')
                ADVANCE(18);
            ACCEPT_TOKEN(ts_aux_sym_token16);
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
                ADVANCE(78);
            if (lookahead == '\'')
                ADVANCE(10);
            if (lookahead == '(')
                ADVANCE(14);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(80);
            if (lookahead == '+')
                ADVANCE(81);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == '-')
                ADVANCE(82);
            if (lookahead == '.')
                ADVANCE(83);
            if (lookahead == '/')
                ADVANCE(185);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
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
                ADVANCE(24);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == 'b')
                ADVANCE(25);
            if (lookahead == 'c')
                ADVANCE(130);
            if (lookahead == 'd')
                ADVANCE(134);
            if (lookahead == 'e')
                ADVANCE(175);
            if (lookahead == 'f')
                ADVANCE(36);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'v')
                ADVANCE(72);
            if (lookahead == '{')
                ADVANCE(75);
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
    [4] = 76,
    [5] = 2,
    [6] = 156,
    [7] = 98,
    [8] = 96,
    [9] = 76,
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
    [71] = 169,
    [72] = 166,
    [73] = 98,
    [74] = 113,
    [75] = 113,
    [76] = 113,
    [77] = 76,
    [78] = 113,
    [79] = 162,
    [80] = 76,
    [81] = 162,
    [82] = 76,
    [83] = 162,
    [84] = 76,
    [85] = 162,
    [86] = 76,
    [87] = 162,
    [88] = 76,
    [89] = 162,
    [90] = 100,
    [91] = 162,
    [92] = 76,
    [93] = 104,
    [94] = 114,
    [95] = 162,
    [96] = 105,
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
    [108] = 100,
    [109] = 162,
    [110] = 105,
    [111] = 104,
    [112] = 116,
    [113] = 162,
    [114] = 105,
    [115] = 116,
    [116] = 105,
    [117] = 116,
    [118] = 162,
    [119] = 105,
    [120] = 164,
    [121] = 109,
    [122] = 107,
    [123] = 105,
    [124] = 163,
    [125] = 162,
    [126] = 110,
    [127] = 107,
    [128] = 105,
    [129] = 162,
    [130] = 110,
    [131] = 162,
    [132] = 110,
    [133] = 162,
    [134] = 110,
    [135] = 162,
    [136] = 110,
    [137] = 162,
    [138] = 110,
    [139] = 162,
    [140] = 100,
    [141] = 162,
    [142] = 110,
    [143] = 104,
    [144] = 117,
    [145] = 162,
    [146] = 105,
    [147] = 117,
    [148] = 162,
    [149] = 112,
    [150] = 105,
    [151] = 162,
    [152] = 112,
    [153] = 162,
    [154] = 112,
    [155] = 162,
    [156] = 112,
    [157] = 162,
    [158] = 112,
    [159] = 162,
    [160] = 112,
    [161] = 162,
    [162] = 100,
    [163] = 162,
    [164] = 112,
    [165] = 104,
    [166] = 118,
    [167] = 162,
    [168] = 105,
    [169] = 118,
    [170] = 162,
    [171] = 105,
    [172] = 169,
    [173] = 166,
    [174] = 105,
    [175] = 113,
    [176] = 76,
    [177] = 114,
    [178] = 162,
    [179] = 76,
    [180] = 164,
    [181] = 109,
    [182] = 107,
    [183] = 76,
    [184] = 163,
    [185] = 162,
    [186] = 110,
    [187] = 107,
    [188] = 76,
    [189] = 110,
    [190] = 117,
    [191] = 162,
    [192] = 110,
    [193] = 164,
    [194] = 109,
    [195] = 107,
    [196] = 110,
    [197] = 163,
    [198] = 162,
    [199] = 110,
    [200] = 107,
    [201] = 110,
    [202] = 162,
    [203] = 112,
    [204] = 110,
    [205] = 112,
    [206] = 118,
    [207] = 162,
    [208] = 112,
    [209] = 164,
    [210] = 109,
    [211] = 107,
    [212] = 112,
    [213] = 163,
    [214] = 162,
    [215] = 110,
    [216] = 107,
    [217] = 112,
    [218] = 162,
    [219] = 110,
    [220] = 169,
    [221] = 166,
    [222] = 110,
    [223] = 113,
    [224] = 119,
    [225] = 110,
    [226] = 107,
    [227] = 113,
    [228] = 121,
    [229] = 113,
    [230] = 123,
    [231] = 125,
    [232] = 107,
    [233] = 76,
    [234] = 168,
    [235] = 179,
    [236] = 162,
    [237] = 162,
    [238] = 112,
    [239] = 173,
    [240] = 113,
    [241] = 127,
    [242] = 162,
    [243] = 112,
    [244] = 76,
    [245] = 162,
    [246] = 112,
    [247] = 112,
    [248] = 162,
    [249] = 112,
    [250] = 169,
    [251] = 166,
    [252] = 112,
    [253] = 113,
    [254] = 119,
    [255] = 112,
    [256] = 107,
    [257] = 168,
    [258] = 162,
    [259] = 112,
    [260] = 173,
    [261] = 180,
    [262] = 173,
    [263] = 113,
    [264] = 168,
    [265] = 162,
    [266] = 112,
    [267] = 166,
    [268] = 141,
    [269] = 141,
    [270] = 107,
    [271] = 162,
    [272] = 100,
    [273] = 129,
    [274] = 129,
    [275] = 129,
    [276] = 76,
    [277] = 129,
    [278] = 127,
    [279] = 141,
    [280] = 113,
    [281] = 121,
    [282] = 129,
    [283] = 107,
    [284] = 127,
    [285] = 113,
    [286] = 162,
    [287] = 153,
    [288] = 156,
    [289] = 98,
    [290] = 96,
    [291] = 153,
    [292] = 111,
    [293] = 153,
    [294] = 165,
    [295] = 155,
    [296] = 154,
    [297] = 98,
    [298] = 156,
    [299] = 98,
    [300] = 96,
    [301] = 155,
    [302] = 111,
    [303] = 155,
    [304] = 162,
    [305] = 155,
    [306] = 162,
    [307] = 155,
    [308] = 162,
    [309] = 155,
    [310] = 162,
    [311] = 155,
    [312] = 162,
    [313] = 155,
    [314] = 162,
    [315] = 100,
    [316] = 162,
    [317] = 155,
    [318] = 104,
    [319] = 159,
    [320] = 162,
    [321] = 105,
    [322] = 159,
    [323] = 165,
    [324] = 155,
    [325] = 154,
    [326] = 105,
    [327] = 162,
    [328] = 155,
    [329] = 154,
    [330] = 155,
    [331] = 159,
    [332] = 162,
    [333] = 155,
    [334] = 164,
    [335] = 109,
    [336] = 107,
    [337] = 155,
    [338] = 163,
    [339] = 162,
    [340] = 110,
    [341] = 107,
    [342] = 155,
    [343] = 165,
    [344] = 155,
    [345] = 154,
    [346] = 110,
    [347] = 160,
    [348] = 162,
    [349] = 112,
    [350] = 155,
    [351] = 165,
    [352] = 155,
    [353] = 154,
    [354] = 112,
    [355] = 160,
    [356] = 162,
    [357] = 155,
    [358] = 169,
    [359] = 166,
    [360] = 155,
    [361] = 113,
    [362] = 119,
    [363] = 155,
    [364] = 107,
    [365] = 171,
    [366] = 76,
    [367] = 113,
    [368] = 113,
    [369] = 162,
    [370] = 76,
    [371] = 169,
    [372] = 166,
    [373] = 76,
    [374] = 113,
    [375] = 119,
    [376] = 76,
    [377] = 107,
    [378] = 162,
    [379] = 153,
    [380] = 162,
    [381] = 153,
    [382] = 162,
    [383] = 153,
    [384] = 162,
    [385] = 153,
    [386] = 162,
    [387] = 153,
    [388] = 162,
    [389] = 153,
    [390] = 162,
    [391] = 100,
    [392] = 162,
    [393] = 153,
    [394] = 104,
    [395] = 161,
    [396] = 162,
    [397] = 105,
    [398] = 161,
    [399] = 153,
    [400] = 161,
    [401] = 162,
    [402] = 153,
    [403] = 164,
    [404] = 109,
    [405] = 107,
    [406] = 153,
    [407] = 163,
    [408] = 162,
    [409] = 110,
    [410] = 107,
    [411] = 153,
    [412] = 153,
    [413] = 162,
    [414] = 112,
    [415] = 153,
    [416] = 162,
    [417] = 153,
    [418] = 169,
    [419] = 166,
    [420] = 153,
    [421] = 113,
    [422] = 119,
    [423] = 153,
    [424] = 107,
    [425] = 165,
    [426] = 155,
    [427] = 154,
    [428] = 76,
    [429] = 160,
    [430] = 165,
    [431] = 155,
    [432] = 154,
    [433] = 155,
    [434] = 160,
    [435] = 155,
    [436] = 76,
    [437] = 168,
    [438] = 166,
    [439] = 153,
    [440] = 167,
    [441] = 111,
    [442] = 96,
    [443] = 166,
    [444] = 104,
    [445] = 111,
    [446] = 96,
    [447] = 166,
    [448] = 165,
    [449] = 155,
    [450] = 154,
    [451] = 153,
    [452] = 160,
    [453] = 153,
    [454] = 162,
    [455] = 100,
    [456] = 162,
    [457] = 100,
    [458] = 162,
    [459] = 100,
    [460] = 162,
    [461] = 100,
    [462] = 162,
    [463] = 100,
    [464] = 162,
    [465] = 100,
    [466] = 162,
    [467] = 100,
    [468] = 104,
    [469] = 170,
    [470] = 162,
    [471] = 105,
    [472] = 170,
    [473] = 100,
    [474] = 170,
    [475] = 162,
    [476] = 100,
    [477] = 164,
    [478] = 109,
    [479] = 107,
    [480] = 100,
    [481] = 163,
    [482] = 162,
    [483] = 110,
    [484] = 107,
    [485] = 100,
    [486] = 100,
    [487] = 162,
    [488] = 112,
    [489] = 100,
    [490] = 162,
    [491] = 100,
    [492] = 169,
    [493] = 166,
    [494] = 100,
    [495] = 113,
    [496] = 119,
    [497] = 100,
    [498] = 107,
    [499] = 168,
    [500] = 166,
    [501] = 100,
    [502] = 165,
    [503] = 155,
    [504] = 154,
    [505] = 100,
    [506] = 160,
    [507] = 100,
    [508] = 114,
    [509] = 113,
    [510] = 168,
    [511] = 166,
    [512] = 76,
    [513] = 168,
    [514] = 166,
    [515] = 155,
    [516] = 112,
    [517] = 110,
    [518] = 155,
    [519] = 160,
    [520] = 160,
    [521] = 105,
    [522] = 160,
    [523] = 98,
    [524] = 76,
    [525] = 113,
    [526] = 161,
    [527] = 114,
    [528] = 168,
    [529] = 179,
    [530] = 162,
    [531] = 162,
    [532] = 112,
    [533] = 173,
    [534] = 129,
    [535] = 168,
    [536] = 162,
    [537] = 112,
    [538] = 173,
    [539] = 174,
    [540] = 173,
    [541] = 129,
    [542] = 168,
    [543] = 162,
    [544] = 112,
    [545] = 166,
    [546] = 141,
    [547] = 107,
    [548] = 129,
    [549] = 163,
    [550] = 129,
    [551] = 141,
    [552] = 127,
    [553] = 129,
    [554] = 162,
    [555] = 76,
    [556] = 129,
    [557] = 114,
    [558] = 171,
    [559] = 76,
    [560] = 129,
    [561] = 129,
    [562] = 162,
    [563] = 114,
    [564] = 129,
    [565] = 96,
    [566] = 174,
    [567] = 76,
    [568] = 174,
    [569] = 127,
    [570] = 113,
    [571] = 121,
    [572] = 174,
    [573] = 107,
    [574] = 168,
    [575] = 179,
    [576] = 162,
    [577] = 162,
    [578] = 112,
    [579] = 173,
    [580] = 174,
    [581] = 168,
    [582] = 162,
    [583] = 112,
    [584] = 173,
    [585] = 174,
    [586] = 173,
    [587] = 174,
    [588] = 168,
    [589] = 162,
    [590] = 112,
    [591] = 166,
    [592] = 141,
    [593] = 107,
    [594] = 174,
    [595] = 96,
    [596] = 127,
    [597] = 174,
    [598] = 162,
    [599] = 76,
    [600] = 174,
    [601] = 114,
    [602] = 171,
    [603] = 76,
    [604] = 174,
    [605] = 174,
    [606] = 162,
    [607] = 114,
    [608] = 174,
    [609] = 96,
    [610] = 96,
    [611] = 76,
    [612] = 162,
    [613] = 127,
    [614] = 162,
    [615] = 76,
    [616] = 162,
    [617] = 114,
    [618] = 96,
    [619] = 96,
    [620] = 141,
    [621] = 107,
    [622] = 113,
    [623] = 96,
    [624] = 180,
    [625] = 76,
    [626] = 180,
    [627] = 127,
    [628] = 113,
    [629] = 121,
    [630] = 180,
    [631] = 107,
    [632] = 168,
    [633] = 179,
    [634] = 162,
    [635] = 162,
    [636] = 112,
    [637] = 173,
    [638] = 180,
    [639] = 168,
    [640] = 162,
    [641] = 112,
    [642] = 173,
    [643] = 180,
    [644] = 173,
    [645] = 180,
    [646] = 168,
    [647] = 162,
    [648] = 112,
    [649] = 166,
    [650] = 141,
    [651] = 107,
    [652] = 180,
    [653] = 96,
    [654] = 127,
    [655] = 180,
    [656] = 162,
    [657] = 76,
    [658] = 180,
    [659] = 114,
    [660] = 171,
    [661] = 76,
    [662] = 180,
    [663] = 180,
    [664] = 162,
    [665] = 114,
    [666] = 180,
    [667] = 96,
    [668] = 96,
    [669] = 96,
    [670] = 168,
    [671] = 166,
    [672] = 112,
    [673] = 96,
    [674] = 168,
    [675] = 166,
    [676] = 110,
    [677] = 112,
    [678] = 110,
    [679] = 119,
    [680] = 105,
    [681] = 107,
    [682] = 168,
    [683] = 166,
    [684] = 105,
    [685] = 105,
    [686] = 114,
    [687] = 107,
    [688] = 119,
    [689] = 98,
    [690] = 107,
    [691] = 168,
    [692] = 166,
    [693] = 98,
    [694] = 98,
    [695] = 110,
    [696] = 163,
    [697] = 162,
    [698] = 110,
    [699] = 107,
    [700] = 98,
    [701] = 98,
    [702] = 111,
    [703] = 105,
    [704] = 102,
    [705] = 111,
    [706] = 111,
    [707] = 100,
    [708] = 162,
    [709] = 98,
    [710] = 111,
    [711] = 98,
    [712] = 111,
    [713] = 76,
    [714] = 127,
    [715] = 0,
    [716] = 113,
    [717] = 121,
    [718] = 2,
    [719] = 107,
    [720] = 168,
    [721] = 179,
    [722] = 162,
    [723] = 162,
    [724] = 112,
    [725] = 173,
    [726] = 2,
    [727] = 168,
    [728] = 162,
    [729] = 112,
    [730] = 173,
    [731] = 182,
    [732] = 173,
    [733] = 2,
    [734] = 168,
    [735] = 162,
    [736] = 112,
    [737] = 166,
    [738] = 141,
    [739] = 107,
    [740] = 2,
    [741] = 96,
    [742] = 127,
    [743] = 2,
    [744] = 162,
    [745] = 76,
    [746] = 2,
    [747] = 114,
    [748] = 171,
    [749] = 76,
    [750] = 2,
    [751] = 2,
    [752] = 162,
    [753] = 114,
    [754] = 2,
    [755] = 182,
    [756] = 76,
    [757] = 182,
    [758] = 127,
    [759] = 113,
    [760] = 121,
    [761] = 182,
    [762] = 107,
    [763] = 168,
    [764] = 179,
    [765] = 162,
    [766] = 162,
    [767] = 112,
    [768] = 173,
    [769] = 182,
    [770] = 168,
    [771] = 162,
    [772] = 112,
    [773] = 173,
    [774] = 182,
    [775] = 173,
    [776] = 182,
    [777] = 168,
    [778] = 162,
    [779] = 112,
    [780] = 166,
    [781] = 141,
    [782] = 107,
    [783] = 182,
    [784] = 96,
    [785] = 127,
    [786] = 182,
    [787] = 162,
    [788] = 76,
    [789] = 182,
    [790] = 114,
    [791] = 171,
    [792] = 76,
    [793] = 182,
    [794] = 182,
    [795] = 162,
    [796] = 114,
    [797] = 182,
    [798] = 96,
    [799] = 96,
    [800] = 96,
    [801] = 96,
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
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_program_repeat0] = SHIFT(802),
        [ts_aux_sym_token0] = SHIFT(716),
        [ts_aux_sym_token2] = SHIFT(720),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(727),
        [ts_aux_sym_token7] = SHIFT(734),
        [ts_aux_sym_token11] = SHIFT(742),
        [ts_aux_sym_token12] = SHIFT(744),
        [ts_aux_sym_token13] = SHIFT(748),
        [ts_aux_sym_token14] = SHIFT(752),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
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
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_program_repeat0] = SHIFT(715),
        [ts_aux_sym_token0] = SHIFT(716),
        [ts_aux_sym_token2] = SHIFT(720),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(727),
        [ts_aux_sym_token7] = SHIFT(734),
        [ts_aux_sym_token11] = SHIFT(742),
        [ts_aux_sym_token12] = SHIFT(744),
        [ts_aux_sym_token13] = SHIFT(748),
        [ts_aux_sym_token14] = SHIFT(752),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [4] = {
        [ts_sym__terminator] = SHIFT(5),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
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
        [ts_builtin_sym_error] = SHIFT(712),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(713),
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_builtin_sym_error] = SHIFT(710),
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
    },
    [15] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
    },
    [17] = {
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
    },
    [21] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(14),
        [ts_aux_sym_token16] = SHIFT(14),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [25] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(708),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
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
        [ts_builtin_sym_error] = SHIFT(706),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(707),
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_builtin_sym_error] = SHIFT(705),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [36] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = SHIFT(704),
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
        [ts_builtin_sym_error] = SHIFT(702),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(703),
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_sym_string] = SHIFT(696),
        [ts_sym_identifier] = SHIFT(696),
        [ts_aux_sym_token1] = SHIFT(701),
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
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [54] = {
        [ts_aux_sym_object_repeat0] = SHIFT(55),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
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
        [ts_aux_sym_token4] = SHIFT(695),
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [62] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(694),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
    },
    [70] = {
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
    [71] = {
        [ts_sym_formal_parameters] = SHIFT(72),
        [ts_sym_identifier] = SHIFT(691),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [72] = {
        [ts_sym_statement_block] = SHIFT(73),
        [ts_aux_sym_token0] = SHIFT(74),
    },
    [73] = {
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
    [74] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(688),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(690),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [75] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(241),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(687),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [76] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [77] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [78] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [79] = {
        [ts_sym_expression] = SHIFT(80),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [80] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [81] = {
        [ts_sym_expression] = SHIFT(82),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [82] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [83] = {
        [ts_sym_expression] = SHIFT(84),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [84] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [85] = {
        [ts_sym_expression] = SHIFT(86),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [86] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [87] = {
        [ts_sym_expression] = SHIFT(88),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [88] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [89] = {
        [ts_sym_expression] = SHIFT(90),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [90] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(91),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [91] = {
        [ts_sym_expression] = SHIFT(92),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [92] = {
        [ts_sym__terminator] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [93] = {
        [ts_sym_identifier] = SHIFT(94),
    },
    [94] = {
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
    [95] = {
        [ts_sym_expression] = SHIFT(96),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [96] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = SHIFT(686),
    },
    [97] = {
        [ts_sym_expression] = SHIFT(98),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [98] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 3),
    },
    [99] = {
        [ts_sym_expression] = SHIFT(100),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [100] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 3),
    },
    [101] = {
        [ts_sym_expression] = SHIFT(102),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [102] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [103] = {
        [ts_sym_expression] = SHIFT(104),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [104] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [105] = {
        [ts_sym_expression] = SHIFT(106),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [106] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [107] = {
        [ts_sym_expression] = SHIFT(108),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [108] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(109),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [109] = {
        [ts_sym_expression] = SHIFT(110),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [110] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = REDUCE(ts_sym_ternary, 5),
    },
    [111] = {
        [ts_sym_identifier] = SHIFT(112),
    },
    [112] = {
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
    [113] = {
        [ts_sym_expression] = SHIFT(114),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [114] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = SHIFT(115),
    },
    [115] = {
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
    [116] = {
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
    [117] = {
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
        [ts_aux_sym_token29] = SHIFT(118),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token34] = REDUCE(ts_sym_expression, 1),
    },
    [118] = {
        [ts_sym_expression] = SHIFT(119),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [119] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = REDUCE(ts_sym_assignment, 3),
    },
    [120] = {
        [ts_builtin_sym_error] = SHIFT(121),
        [ts_sym_string] = SHIFT(124),
        [ts_sym_identifier] = SHIFT(124),
        [ts_aux_sym_token1] = SHIFT(685),
    },
    [121] = {
        [ts_aux_sym_object_repeat0] = SHIFT(122),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [122] = {
        [ts_aux_sym_token1] = SHIFT(123),
    },
    [123] = {
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
    [124] = {
        [ts_aux_sym_token10] = SHIFT(125),
    },
    [125] = {
        [ts_sym_expression] = SHIFT(126),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [126] = {
        [ts_aux_sym_object_repeat0] = SHIFT(127),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [127] = {
        [ts_aux_sym_token1] = SHIFT(128),
    },
    [128] = {
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
    [129] = {
        [ts_sym_expression] = SHIFT(130),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [130] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [131] = {
        [ts_sym_expression] = SHIFT(132),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [132] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [133] = {
        [ts_sym_expression] = SHIFT(134),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [134] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [135] = {
        [ts_sym_expression] = SHIFT(136),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [136] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [137] = {
        [ts_sym_expression] = SHIFT(138),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [138] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [139] = {
        [ts_sym_expression] = SHIFT(140),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [140] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(141),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [141] = {
        [ts_sym_expression] = SHIFT(142),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [142] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [143] = {
        [ts_sym_identifier] = SHIFT(144),
    },
    [144] = {
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
    [145] = {
        [ts_sym_expression] = SHIFT(146),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [146] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = SHIFT(147),
    },
    [147] = {
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
    [148] = {
        [ts_sym_expression] = SHIFT(149),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [149] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(150),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [150] = {
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
    [151] = {
        [ts_sym_expression] = SHIFT(152),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [152] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [153] = {
        [ts_sym_expression] = SHIFT(154),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [154] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [155] = {
        [ts_sym_expression] = SHIFT(156),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [156] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [157] = {
        [ts_sym_expression] = SHIFT(158),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [158] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [159] = {
        [ts_sym_expression] = SHIFT(160),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [160] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [161] = {
        [ts_sym_expression] = SHIFT(162),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [162] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(163),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [163] = {
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [164] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [165] = {
        [ts_sym_identifier] = SHIFT(166),
    },
    [166] = {
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
    [167] = {
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [168] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = SHIFT(169),
    },
    [169] = {
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
    [170] = {
        [ts_sym_expression] = SHIFT(171),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [171] = {
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
    [172] = {
        [ts_sym_formal_parameters] = SHIFT(173),
        [ts_sym_identifier] = SHIFT(682),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [173] = {
        [ts_sym_statement_block] = SHIFT(174),
        [ts_aux_sym_token0] = SHIFT(175),
    },
    [174] = {
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
    [175] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(679),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(681),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [176] = {
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
    [177] = {
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [178] = {
        [ts_sym_expression] = SHIFT(179),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [179] = {
        [ts_sym__terminator] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [180] = {
        [ts_builtin_sym_error] = SHIFT(181),
        [ts_sym_string] = SHIFT(184),
        [ts_sym_identifier] = SHIFT(184),
        [ts_aux_sym_token1] = SHIFT(233),
    },
    [181] = {
        [ts_aux_sym_object_repeat0] = SHIFT(182),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [182] = {
        [ts_aux_sym_token1] = SHIFT(183),
    },
    [183] = {
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
    [184] = {
        [ts_aux_sym_token10] = SHIFT(185),
    },
    [185] = {
        [ts_sym_expression] = SHIFT(186),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [186] = {
        [ts_aux_sym_object_repeat0] = SHIFT(187),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [187] = {
        [ts_aux_sym_token1] = SHIFT(188),
    },
    [188] = {
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
    [189] = {
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
    [190] = {
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
        [ts_aux_sym_token29] = SHIFT(191),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [191] = {
        [ts_sym_expression] = SHIFT(192),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [192] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [193] = {
        [ts_builtin_sym_error] = SHIFT(194),
        [ts_sym_string] = SHIFT(197),
        [ts_sym_identifier] = SHIFT(197),
        [ts_aux_sym_token1] = SHIFT(678),
    },
    [194] = {
        [ts_aux_sym_object_repeat0] = SHIFT(195),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [195] = {
        [ts_aux_sym_token1] = SHIFT(196),
    },
    [196] = {
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
    [197] = {
        [ts_aux_sym_token10] = SHIFT(198),
    },
    [198] = {
        [ts_sym_expression] = SHIFT(199),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [199] = {
        [ts_aux_sym_object_repeat0] = SHIFT(200),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [200] = {
        [ts_aux_sym_token1] = SHIFT(201),
    },
    [201] = {
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
    [202] = {
        [ts_sym_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [203] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(204),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [204] = {
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
    [205] = {
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
    [206] = {
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
        [ts_aux_sym_token29] = SHIFT(207),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [207] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [208] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [209] = {
        [ts_builtin_sym_error] = SHIFT(210),
        [ts_sym_string] = SHIFT(213),
        [ts_sym_identifier] = SHIFT(213),
        [ts_aux_sym_token1] = SHIFT(677),
    },
    [210] = {
        [ts_aux_sym_object_repeat0] = SHIFT(211),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [211] = {
        [ts_aux_sym_token1] = SHIFT(212),
    },
    [212] = {
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
    [213] = {
        [ts_aux_sym_token10] = SHIFT(214),
    },
    [214] = {
        [ts_sym_expression] = SHIFT(215),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [215] = {
        [ts_aux_sym_object_repeat0] = SHIFT(216),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [216] = {
        [ts_aux_sym_token1] = SHIFT(217),
    },
    [217] = {
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
    [218] = {
        [ts_sym_expression] = SHIFT(219),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [219] = {
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
    [220] = {
        [ts_sym_formal_parameters] = SHIFT(221),
        [ts_sym_identifier] = SHIFT(674),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [221] = {
        [ts_sym_statement_block] = SHIFT(222),
        [ts_aux_sym_token0] = SHIFT(223),
    },
    [222] = {
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
    [223] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(224),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(226),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [224] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_token1] = SHIFT(225),
    },
    [225] = {
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
    [226] = {
        [ts_aux_sym_token1] = SHIFT(225),
    },
    [227] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(228),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(231),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(232),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = SHIFT(233),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [228] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_object_repeat0] = SHIFT(182),
        [ts_aux_sym_token1] = SHIFT(229),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [229] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [230] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(185),
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
    [231] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = SHIFT(185),
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [232] = {
        [ts_aux_sym_token1] = SHIFT(229),
    },
    [233] = {
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
    [234] = {
        [ts_aux_sym_token3] = SHIFT(235),
    },
    [235] = {
        [ts_sym_var_declaration] = SHIFT(236),
        [ts_sym_expression_statement] = SHIFT(236),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [236] = {
        [ts_sym_expression_statement] = SHIFT(237),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [237] = {
        [ts_sym_expression] = SHIFT(238),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(673),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [238] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(239),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [239] = {
        [ts_sym_statement] = SHIFT(240),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(241),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [240] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [241] = {
        [ts_sym__terminator] = SHIFT(78),
    },
    [242] = {
        [ts_sym_expression] = SHIFT(243),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [243] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(244),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [244] = {
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
    [245] = {
        [ts_sym_expression] = SHIFT(246),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [246] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(247),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [247] = {
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
    [248] = {
        [ts_sym_expression] = SHIFT(249),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [249] = {
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
    [250] = {
        [ts_sym_formal_parameters] = SHIFT(251),
        [ts_sym_identifier] = SHIFT(670),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [251] = {
        [ts_sym_statement_block] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(253),
    },
    [252] = {
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
    [253] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(254),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(256),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [254] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_token1] = SHIFT(255),
    },
    [255] = {
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
    [256] = {
        [ts_aux_sym_token1] = SHIFT(255),
    },
    [257] = {
        [ts_aux_sym_token3] = SHIFT(258),
    },
    [258] = {
        [ts_sym_expression] = SHIFT(259),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(669),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [259] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(260),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [260] = {
        [ts_sym_statement] = SHIFT(261),
        [ts_sym_statement_block] = SHIFT(624),
        [ts_sym_for_statement] = SHIFT(624),
        [ts_sym_if_statement] = SHIFT(624),
        [ts_sym_switch_statement] = SHIFT(624),
        [ts_sym_break_statement] = SHIFT(624),
        [ts_sym_var_declaration] = SHIFT(624),
        [ts_sym_expression_statement] = SHIFT(624),
        [ts_sym_return_statement] = SHIFT(624),
        [ts_sym_delete_statement] = SHIFT(624),
        [ts_sym_expression] = SHIFT(625),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(627),
        [ts_sym_comment] = SHIFT(624),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(628),
        [ts_aux_sym_token2] = SHIFT(632),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(639),
        [ts_aux_sym_token7] = SHIFT(646),
        [ts_aux_sym_token11] = SHIFT(654),
        [ts_aux_sym_token12] = SHIFT(656),
        [ts_aux_sym_token13] = SHIFT(660),
        [ts_aux_sym_token14] = SHIFT(664),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [261] = {
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
        [ts_aux_sym_token6] = SHIFT(262),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [262] = {
        [ts_sym_statement] = SHIFT(263),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(241),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [263] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [264] = {
        [ts_aux_sym_token3] = SHIFT(265),
    },
    [265] = {
        [ts_sym_expression] = SHIFT(266),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(623),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [266] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(267),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [267] = {
        [ts_aux_sym_token0] = SHIFT(268),
    },
    [268] = {
        [ts_sym_switch_case] = SHIFT(269),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(621),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(549),
    },
    [269] = {
        [ts_sym_switch_case] = SHIFT(269),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(270),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(549),
    },
    [270] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 2),
    },
    [271] = {
        [ts_sym_expression] = SHIFT(272),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [272] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(273),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [273] = {
        [ts_sym_statement] = SHIFT(274),
        [ts_sym_statement_block] = SHIFT(275),
        [ts_sym_for_statement] = SHIFT(275),
        [ts_sym_if_statement] = SHIFT(275),
        [ts_sym_switch_statement] = SHIFT(275),
        [ts_sym_break_statement] = SHIFT(275),
        [ts_sym_var_declaration] = SHIFT(275),
        [ts_sym_expression_statement] = SHIFT(275),
        [ts_sym_return_statement] = SHIFT(275),
        [ts_sym_delete_statement] = SHIFT(275),
        [ts_sym_expression] = SHIFT(276),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(278),
        [ts_sym_comment] = SHIFT(275),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(620),
        [ts_aux_sym_token0] = SHIFT(280),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(528),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(535),
        [ts_aux_sym_token7] = SHIFT(542),
        [ts_aux_sym_token8] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(552),
        [ts_aux_sym_token12] = SHIFT(554),
        [ts_aux_sym_token13] = SHIFT(558),
        [ts_aux_sym_token14] = SHIFT(562),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [274] = {
        [ts_sym_statement] = SHIFT(274),
        [ts_sym_statement_block] = SHIFT(275),
        [ts_sym_for_statement] = SHIFT(275),
        [ts_sym_if_statement] = SHIFT(275),
        [ts_sym_switch_statement] = SHIFT(275),
        [ts_sym_break_statement] = SHIFT(275),
        [ts_sym_var_declaration] = SHIFT(275),
        [ts_sym_expression_statement] = SHIFT(275),
        [ts_sym_return_statement] = SHIFT(275),
        [ts_sym_delete_statement] = SHIFT(275),
        [ts_sym_expression] = SHIFT(276),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(278),
        [ts_sym_comment] = SHIFT(275),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(279),
        [ts_aux_sym_token0] = SHIFT(280),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(528),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(535),
        [ts_aux_sym_token7] = SHIFT(542),
        [ts_aux_sym_token8] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(552),
        [ts_aux_sym_token12] = SHIFT(554),
        [ts_aux_sym_token13] = SHIFT(558),
        [ts_aux_sym_token14] = SHIFT(562),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [275] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [276] = {
        [ts_sym__terminator] = SHIFT(277),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [277] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [278] = {
        [ts_sym__terminator] = SHIFT(277),
    },
    [279] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token8] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_switch_case_repeat0, 2),
    },
    [280] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(281),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(231),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(283),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = SHIFT(233),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [281] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_object_repeat0] = SHIFT(182),
        [ts_aux_sym_token1] = SHIFT(282),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [282] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [283] = {
        [ts_aux_sym_token1] = SHIFT(282),
    },
    [284] = {
        [ts_sym__terminator] = SHIFT(285),
    },
    [285] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [286] = {
        [ts_sym_expression] = SHIFT(287),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(524),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(526),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(527),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [287] = {
        [ts_aux_sym_token3] = SHIFT(288),
        [ts_aux_sym_token15] = SHIFT(380),
        [ts_aux_sym_token16] = SHIFT(380),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token18] = SHIFT(382),
        [ts_aux_sym_token19] = SHIFT(384),
        [ts_aux_sym_token20] = SHIFT(386),
        [ts_aux_sym_token21] = SHIFT(388),
        [ts_aux_sym_token22] = SHIFT(388),
        [ts_aux_sym_token23] = SHIFT(388),
        [ts_aux_sym_token24] = SHIFT(388),
        [ts_aux_sym_token25] = SHIFT(388),
        [ts_aux_sym_token26] = SHIFT(388),
        [ts_aux_sym_token28] = SHIFT(390),
        [ts_aux_sym_token32] = SHIFT(394),
        [ts_aux_sym_token33] = SHIFT(396),
    },
    [288] = {
        [ts_sym_expression] = SHIFT(289),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(292),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(293),
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
    },
    [289] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(290),
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
    [290] = {
        [ts_aux_sym_token4] = SHIFT(291),
    },
    [291] = {
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
    [292] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(290),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [293] = {
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
    [294] = {
        [ts_sym_expression] = SHIFT(295),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_builtin_sym_error] = SHIFT(522),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
        [ts_aux_sym_token34] = SHIFT(523),
    },
    [295] = {
        [ts_aux_sym_array_repeat0] = SHIFT(296),
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [296] = {
        [ts_aux_sym_token34] = SHIFT(297),
    },
    [297] = {
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
    [298] = {
        [ts_sym_expression] = SHIFT(299),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(302),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(45),
        [ts_aux_sym_token3] = SHIFT(61),
        [ts_aux_sym_token4] = SHIFT(303),
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
    },
    [299] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(300),
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
    [300] = {
        [ts_aux_sym_token4] = SHIFT(301),
    },
    [301] = {
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
    [302] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(300),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [303] = {
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
    [304] = {
        [ts_sym_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
    },
    [305] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 3),
    },
    [306] = {
        [ts_sym_expression] = SHIFT(307),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
    },
    [307] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_math_op, 3),
    },
    [308] = {
        [ts_sym_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
    },
    [309] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [310] = {
        [ts_sym_expression] = SHIFT(311),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
    },
    [311] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [312] = {
        [ts_sym_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
    },
    [313] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token31] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token34] = REDUCE(ts_sym_bool_op, 3),
    },
    [314] = {
        [ts_sym_expression] = SHIFT(315),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [315] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(316),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [316] = {
        [ts_sym_expression] = SHIFT(317),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
    },
    [317] = {
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_sym_ternary, 5),
    },
    [318] = {
        [ts_sym_identifier] = SHIFT(319),
    },
    [319] = {
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
    [320] = {
        [ts_sym_expression] = SHIFT(321),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [321] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = SHIFT(322),
    },
    [322] = {
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
    [323] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_builtin_sym_error] = SHIFT(520),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
        [ts_aux_sym_token34] = SHIFT(521),
    },
    [324] = {
        [ts_aux_sym_array_repeat0] = SHIFT(325),
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [325] = {
        [ts_aux_sym_token34] = SHIFT(326),
    },
    [326] = {
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
    [327] = {
        [ts_sym_expression] = SHIFT(328),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_builtin_sym_error] = SHIFT(519),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
    },
    [328] = {
        [ts_aux_sym_array_repeat0] = SHIFT(329),
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [329] = {
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [330] = {
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
    [331] = {
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
        [ts_aux_sym_token29] = SHIFT(332),
        [ts_aux_sym_token31] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token34] = REDUCE(ts_sym_expression, 1),
    },
    [332] = {
        [ts_sym_expression] = SHIFT(333),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
    },
    [333] = {
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_sym_assignment, 3),
    },
    [334] = {
        [ts_builtin_sym_error] = SHIFT(335),
        [ts_sym_string] = SHIFT(338),
        [ts_sym_identifier] = SHIFT(338),
        [ts_aux_sym_token1] = SHIFT(518),
    },
    [335] = {
        [ts_aux_sym_object_repeat0] = SHIFT(336),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [336] = {
        [ts_aux_sym_token1] = SHIFT(337),
    },
    [337] = {
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
    [338] = {
        [ts_aux_sym_token10] = SHIFT(339),
    },
    [339] = {
        [ts_sym_expression] = SHIFT(340),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [340] = {
        [ts_aux_sym_object_repeat0] = SHIFT(341),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [341] = {
        [ts_aux_sym_token1] = SHIFT(342),
    },
    [342] = {
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
    [343] = {
        [ts_sym_expression] = SHIFT(344),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_builtin_sym_error] = SHIFT(347),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
        [ts_aux_sym_token34] = SHIFT(517),
    },
    [344] = {
        [ts_aux_sym_array_repeat0] = SHIFT(345),
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [345] = {
        [ts_aux_sym_token34] = SHIFT(346),
    },
    [346] = {
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
    [347] = {
        [ts_aux_sym_array_repeat0] = SHIFT(345),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [348] = {
        [ts_sym_expression] = SHIFT(349),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [349] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(350),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [350] = {
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
    [351] = {
        [ts_sym_expression] = SHIFT(352),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_builtin_sym_error] = SHIFT(355),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
        [ts_aux_sym_token34] = SHIFT(516),
    },
    [352] = {
        [ts_aux_sym_array_repeat0] = SHIFT(353),
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [353] = {
        [ts_aux_sym_token34] = SHIFT(354),
    },
    [354] = {
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
    [355] = {
        [ts_aux_sym_array_repeat0] = SHIFT(353),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [356] = {
        [ts_sym_expression] = SHIFT(357),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
    },
    [357] = {
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
    [358] = {
        [ts_sym_formal_parameters] = SHIFT(359),
        [ts_sym_identifier] = SHIFT(513),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [359] = {
        [ts_sym_statement_block] = SHIFT(360),
        [ts_aux_sym_token0] = SHIFT(361),
    },
    [360] = {
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
    [361] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(362),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(364),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [362] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_token1] = SHIFT(363),
    },
    [363] = {
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
    [364] = {
        [ts_aux_sym_token1] = SHIFT(363),
    },
    [365] = {
        [ts_sym_expression] = SHIFT(366),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym__terminator] = SHIFT(368),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [366] = {
        [ts_sym__terminator] = SHIFT(367),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [367] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [368] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [369] = {
        [ts_sym_expression] = SHIFT(370),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [370] = {
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
    [371] = {
        [ts_sym_formal_parameters] = SHIFT(372),
        [ts_sym_identifier] = SHIFT(510),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [372] = {
        [ts_sym_statement_block] = SHIFT(373),
        [ts_aux_sym_token0] = SHIFT(374),
    },
    [373] = {
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
    [374] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(375),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(377),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [375] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_token1] = SHIFT(376),
    },
    [376] = {
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
    [377] = {
        [ts_aux_sym_token1] = SHIFT(376),
    },
    [378] = {
        [ts_sym_expression] = SHIFT(379),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(508),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [379] = {
        [ts_aux_sym_token3] = SHIFT(288),
        [ts_aux_sym_token15] = SHIFT(380),
        [ts_aux_sym_token16] = SHIFT(380),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token18] = SHIFT(382),
        [ts_aux_sym_token19] = SHIFT(384),
        [ts_aux_sym_token20] = SHIFT(386),
        [ts_aux_sym_token21] = SHIFT(388),
        [ts_aux_sym_token22] = SHIFT(388),
        [ts_aux_sym_token23] = SHIFT(388),
        [ts_aux_sym_token24] = SHIFT(388),
        [ts_aux_sym_token25] = SHIFT(388),
        [ts_aux_sym_token26] = SHIFT(388),
        [ts_aux_sym_token28] = SHIFT(390),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [380] = {
        [ts_sym_expression] = SHIFT(381),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(400),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [381] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(380),
        [ts_aux_sym_token16] = SHIFT(380),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(386),
        [ts_aux_sym_token21] = SHIFT(388),
        [ts_aux_sym_token22] = SHIFT(388),
        [ts_aux_sym_token23] = SHIFT(388),
        [ts_aux_sym_token24] = SHIFT(388),
        [ts_aux_sym_token25] = SHIFT(388),
        [ts_aux_sym_token26] = SHIFT(388),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [382] = {
        [ts_sym_expression] = SHIFT(383),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(400),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [383] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(380),
        [ts_aux_sym_token16] = SHIFT(380),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token18] = SHIFT(382),
        [ts_aux_sym_token19] = SHIFT(384),
        [ts_aux_sym_token20] = SHIFT(386),
        [ts_aux_sym_token21] = SHIFT(388),
        [ts_aux_sym_token22] = SHIFT(388),
        [ts_aux_sym_token23] = SHIFT(388),
        [ts_aux_sym_token24] = SHIFT(388),
        [ts_aux_sym_token25] = SHIFT(388),
        [ts_aux_sym_token26] = SHIFT(388),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [384] = {
        [ts_sym_expression] = SHIFT(385),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(400),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [385] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(380),
        [ts_aux_sym_token16] = SHIFT(380),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token18] = SHIFT(382),
        [ts_aux_sym_token19] = SHIFT(384),
        [ts_aux_sym_token20] = SHIFT(386),
        [ts_aux_sym_token21] = SHIFT(388),
        [ts_aux_sym_token22] = SHIFT(388),
        [ts_aux_sym_token23] = SHIFT(388),
        [ts_aux_sym_token24] = SHIFT(388),
        [ts_aux_sym_token25] = SHIFT(388),
        [ts_aux_sym_token26] = SHIFT(388),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [386] = {
        [ts_sym_expression] = SHIFT(387),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(400),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [387] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(380),
        [ts_aux_sym_token16] = SHIFT(380),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(386),
        [ts_aux_sym_token21] = SHIFT(388),
        [ts_aux_sym_token22] = SHIFT(388),
        [ts_aux_sym_token23] = SHIFT(388),
        [ts_aux_sym_token24] = SHIFT(388),
        [ts_aux_sym_token25] = SHIFT(388),
        [ts_aux_sym_token26] = SHIFT(388),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [388] = {
        [ts_sym_expression] = SHIFT(389),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(400),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [389] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(388),
        [ts_aux_sym_token22] = SHIFT(388),
        [ts_aux_sym_token23] = SHIFT(388),
        [ts_aux_sym_token24] = SHIFT(388),
        [ts_aux_sym_token25] = SHIFT(388),
        [ts_aux_sym_token26] = SHIFT(388),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [390] = {
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [391] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(392),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [392] = {
        [ts_sym_expression] = SHIFT(393),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(400),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [393] = {
        [ts_aux_sym_token3] = SHIFT(288),
        [ts_aux_sym_token15] = SHIFT(380),
        [ts_aux_sym_token16] = SHIFT(380),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token18] = SHIFT(382),
        [ts_aux_sym_token19] = SHIFT(384),
        [ts_aux_sym_token20] = SHIFT(386),
        [ts_aux_sym_token21] = SHIFT(388),
        [ts_aux_sym_token22] = SHIFT(388),
        [ts_aux_sym_token23] = SHIFT(388),
        [ts_aux_sym_token24] = SHIFT(388),
        [ts_aux_sym_token25] = SHIFT(388),
        [ts_aux_sym_token26] = SHIFT(388),
        [ts_aux_sym_token28] = SHIFT(390),
        [ts_aux_sym_token32] = SHIFT(394),
        [ts_aux_sym_token33] = SHIFT(396),
    },
    [394] = {
        [ts_sym_identifier] = SHIFT(395),
    },
    [395] = {
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
    [396] = {
        [ts_sym_expression] = SHIFT(397),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [397] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = SHIFT(398),
    },
    [398] = {
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
    [399] = {
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
    [400] = {
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
        [ts_aux_sym_token29] = SHIFT(401),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [401] = {
        [ts_sym_expression] = SHIFT(402),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(400),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [402] = {
        [ts_aux_sym_token3] = SHIFT(288),
        [ts_aux_sym_token15] = SHIFT(380),
        [ts_aux_sym_token16] = SHIFT(380),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token18] = SHIFT(382),
        [ts_aux_sym_token19] = SHIFT(384),
        [ts_aux_sym_token20] = SHIFT(386),
        [ts_aux_sym_token21] = SHIFT(388),
        [ts_aux_sym_token22] = SHIFT(388),
        [ts_aux_sym_token23] = SHIFT(388),
        [ts_aux_sym_token24] = SHIFT(388),
        [ts_aux_sym_token25] = SHIFT(388),
        [ts_aux_sym_token26] = SHIFT(388),
        [ts_aux_sym_token28] = SHIFT(390),
        [ts_aux_sym_token32] = SHIFT(394),
        [ts_aux_sym_token33] = SHIFT(396),
    },
    [403] = {
        [ts_builtin_sym_error] = SHIFT(404),
        [ts_sym_string] = SHIFT(407),
        [ts_sym_identifier] = SHIFT(407),
        [ts_aux_sym_token1] = SHIFT(412),
    },
    [404] = {
        [ts_aux_sym_object_repeat0] = SHIFT(405),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [405] = {
        [ts_aux_sym_token1] = SHIFT(406),
    },
    [406] = {
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
    [407] = {
        [ts_aux_sym_token10] = SHIFT(408),
    },
    [408] = {
        [ts_sym_expression] = SHIFT(409),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [409] = {
        [ts_aux_sym_object_repeat0] = SHIFT(410),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [410] = {
        [ts_aux_sym_token1] = SHIFT(411),
    },
    [411] = {
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
    [412] = {
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
    [413] = {
        [ts_sym_expression] = SHIFT(414),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [414] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(415),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [415] = {
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
    [416] = {
        [ts_sym_expression] = SHIFT(417),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(400),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [417] = {
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
    [418] = {
        [ts_sym_formal_parameters] = SHIFT(419),
        [ts_sym_identifier] = SHIFT(437),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [419] = {
        [ts_sym_statement_block] = SHIFT(420),
        [ts_aux_sym_token0] = SHIFT(421),
    },
    [420] = {
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
    [421] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(422),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(424),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [422] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_token1] = SHIFT(423),
    },
    [423] = {
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
    [424] = {
        [ts_aux_sym_token1] = SHIFT(423),
    },
    [425] = {
        [ts_sym_expression] = SHIFT(426),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_builtin_sym_error] = SHIFT(429),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
        [ts_aux_sym_token34] = SHIFT(436),
    },
    [426] = {
        [ts_aux_sym_array_repeat0] = SHIFT(427),
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [427] = {
        [ts_aux_sym_token34] = SHIFT(428),
    },
    [428] = {
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
    [429] = {
        [ts_aux_sym_array_repeat0] = SHIFT(427),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [430] = {
        [ts_sym_expression] = SHIFT(431),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_builtin_sym_error] = SHIFT(434),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
        [ts_aux_sym_token34] = SHIFT(435),
    },
    [431] = {
        [ts_aux_sym_array_repeat0] = SHIFT(432),
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [432] = {
        [ts_aux_sym_token34] = SHIFT(433),
    },
    [433] = {
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
    [434] = {
        [ts_aux_sym_array_repeat0] = SHIFT(432),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [435] = {
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
    [436] = {
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
    [437] = {
        [ts_sym_formal_parameters] = SHIFT(438),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [438] = {
        [ts_sym_statement_block] = SHIFT(439),
        [ts_aux_sym_token0] = SHIFT(421),
    },
    [439] = {
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
    [440] = {
        [ts_sym_identifier] = SHIFT(441),
        [ts_aux_sym_token4] = SHIFT(447),
    },
    [441] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(442),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(444),
    },
    [442] = {
        [ts_aux_sym_token4] = SHIFT(443),
    },
    [443] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 4),
    },
    [444] = {
        [ts_sym_identifier] = SHIFT(445),
    },
    [445] = {
        [ts_aux_sym_formal_parameters_repeat0] = SHIFT(446),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(444),
    },
    [446] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_formal_parameters_repeat0, 3),
    },
    [447] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_formal_parameters, 2),
    },
    [448] = {
        [ts_sym_expression] = SHIFT(449),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_builtin_sym_error] = SHIFT(452),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
        [ts_aux_sym_token34] = SHIFT(453),
    },
    [449] = {
        [ts_aux_sym_array_repeat0] = SHIFT(450),
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [450] = {
        [ts_aux_sym_token34] = SHIFT(451),
    },
    [451] = {
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
    [452] = {
        [ts_aux_sym_array_repeat0] = SHIFT(450),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [453] = {
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
    [454] = {
        [ts_sym_expression] = SHIFT(455),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [455] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [456] = {
        [ts_sym_expression] = SHIFT(457),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [457] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_math_op, 3),
    },
    [458] = {
        [ts_sym_expression] = SHIFT(459),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [459] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [460] = {
        [ts_sym_expression] = SHIFT(461),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [461] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [462] = {
        [ts_sym_expression] = SHIFT(463),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [463] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token32] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_bool_op, 3),
    },
    [464] = {
        [ts_sym_expression] = SHIFT(465),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [465] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(466),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [466] = {
        [ts_sym_expression] = SHIFT(467),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [467] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [468] = {
        [ts_sym_identifier] = SHIFT(469),
    },
    [469] = {
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
    [470] = {
        [ts_sym_expression] = SHIFT(471),
        [ts_sym_math_op] = SHIFT(116),
        [ts_sym_bool_op] = SHIFT(116),
        [ts_sym_ternary] = SHIFT(116),
        [ts_sym_assignment] = SHIFT(116),
        [ts_sym_function_expression] = SHIFT(116),
        [ts_sym_function_call] = SHIFT(116),
        [ts_sym_property_access] = SHIFT(117),
        [ts_sym_object] = SHIFT(116),
        [ts_sym_array] = SHIFT(116),
        [ts_sym_regex] = SHIFT(116),
        [ts_sym_string] = SHIFT(116),
        [ts_sym_identifier] = SHIFT(117),
        [ts_sym_number] = SHIFT(116),
        [ts_sym_null] = SHIFT(116),
        [ts_sym_true] = SHIFT(116),
        [ts_sym_false] = SHIFT(116),
        [ts_aux_sym_token0] = SHIFT(120),
        [ts_aux_sym_token3] = SHIFT(148),
        [ts_aux_sym_token27] = SHIFT(170),
        [ts_aux_sym_token30] = SHIFT(172),
        [ts_aux_sym_token33] = SHIFT(323),
    },
    [471] = {
        [ts_aux_sym_token3] = SHIFT(37),
        [ts_aux_sym_token15] = SHIFT(97),
        [ts_aux_sym_token16] = SHIFT(97),
        [ts_aux_sym_token17] = SHIFT(99),
        [ts_aux_sym_token18] = SHIFT(99),
        [ts_aux_sym_token19] = SHIFT(101),
        [ts_aux_sym_token20] = SHIFT(103),
        [ts_aux_sym_token21] = SHIFT(105),
        [ts_aux_sym_token22] = SHIFT(105),
        [ts_aux_sym_token23] = SHIFT(105),
        [ts_aux_sym_token24] = SHIFT(105),
        [ts_aux_sym_token25] = SHIFT(105),
        [ts_aux_sym_token26] = SHIFT(105),
        [ts_aux_sym_token28] = SHIFT(107),
        [ts_aux_sym_token32] = SHIFT(111),
        [ts_aux_sym_token33] = SHIFT(113),
        [ts_aux_sym_token34] = SHIFT(472),
    },
    [472] = {
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
    [473] = {
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
    [474] = {
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
        [ts_aux_sym_token29] = SHIFT(475),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [475] = {
        [ts_sym_expression] = SHIFT(476),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [476] = {
        [ts_aux_sym_token3] = SHIFT(26),
        [ts_aux_sym_token10] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token15] = SHIFT(454),
        [ts_aux_sym_token16] = SHIFT(454),
        [ts_aux_sym_token17] = SHIFT(456),
        [ts_aux_sym_token18] = SHIFT(456),
        [ts_aux_sym_token19] = SHIFT(458),
        [ts_aux_sym_token20] = SHIFT(460),
        [ts_aux_sym_token21] = SHIFT(462),
        [ts_aux_sym_token22] = SHIFT(462),
        [ts_aux_sym_token23] = SHIFT(462),
        [ts_aux_sym_token24] = SHIFT(462),
        [ts_aux_sym_token25] = SHIFT(462),
        [ts_aux_sym_token26] = SHIFT(462),
        [ts_aux_sym_token28] = SHIFT(464),
        [ts_aux_sym_token32] = SHIFT(468),
        [ts_aux_sym_token33] = SHIFT(470),
    },
    [477] = {
        [ts_builtin_sym_error] = SHIFT(478),
        [ts_sym_string] = SHIFT(481),
        [ts_sym_identifier] = SHIFT(481),
        [ts_aux_sym_token1] = SHIFT(486),
    },
    [478] = {
        [ts_aux_sym_object_repeat0] = SHIFT(479),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [479] = {
        [ts_aux_sym_token1] = SHIFT(480),
    },
    [480] = {
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
    [481] = {
        [ts_aux_sym_token10] = SHIFT(482),
    },
    [482] = {
        [ts_sym_expression] = SHIFT(483),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [483] = {
        [ts_aux_sym_object_repeat0] = SHIFT(484),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [484] = {
        [ts_aux_sym_token1] = SHIFT(485),
    },
    [485] = {
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
    [486] = {
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
    [487] = {
        [ts_sym_expression] = SHIFT(488),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [488] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(489),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [489] = {
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
    [490] = {
        [ts_sym_expression] = SHIFT(491),
        [ts_sym_math_op] = SHIFT(473),
        [ts_sym_bool_op] = SHIFT(473),
        [ts_sym_ternary] = SHIFT(473),
        [ts_sym_assignment] = SHIFT(473),
        [ts_sym_function_expression] = SHIFT(473),
        [ts_sym_function_call] = SHIFT(473),
        [ts_sym_property_access] = SHIFT(474),
        [ts_sym_object] = SHIFT(473),
        [ts_sym_array] = SHIFT(473),
        [ts_sym_regex] = SHIFT(473),
        [ts_sym_string] = SHIFT(473),
        [ts_sym_identifier] = SHIFT(474),
        [ts_sym_number] = SHIFT(473),
        [ts_sym_null] = SHIFT(473),
        [ts_sym_true] = SHIFT(473),
        [ts_sym_false] = SHIFT(473),
        [ts_aux_sym_token0] = SHIFT(477),
        [ts_aux_sym_token3] = SHIFT(487),
        [ts_aux_sym_token27] = SHIFT(490),
        [ts_aux_sym_token30] = SHIFT(492),
        [ts_aux_sym_token33] = SHIFT(502),
    },
    [491] = {
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
    [492] = {
        [ts_sym_formal_parameters] = SHIFT(493),
        [ts_sym_identifier] = SHIFT(499),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [493] = {
        [ts_sym_statement_block] = SHIFT(494),
        [ts_aux_sym_token0] = SHIFT(495),
    },
    [494] = {
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
    [495] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(496),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(498),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [496] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_token1] = SHIFT(497),
    },
    [497] = {
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
    [498] = {
        [ts_aux_sym_token1] = SHIFT(497),
    },
    [499] = {
        [ts_sym_formal_parameters] = SHIFT(500),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [500] = {
        [ts_sym_statement_block] = SHIFT(501),
        [ts_aux_sym_token0] = SHIFT(495),
    },
    [501] = {
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
    [502] = {
        [ts_sym_expression] = SHIFT(503),
        [ts_sym_math_op] = SHIFT(330),
        [ts_sym_bool_op] = SHIFT(330),
        [ts_sym_ternary] = SHIFT(330),
        [ts_sym_assignment] = SHIFT(330),
        [ts_sym_function_expression] = SHIFT(330),
        [ts_sym_function_call] = SHIFT(330),
        [ts_sym_property_access] = SHIFT(331),
        [ts_sym_object] = SHIFT(330),
        [ts_sym_array] = SHIFT(330),
        [ts_builtin_sym_error] = SHIFT(506),
        [ts_sym_regex] = SHIFT(330),
        [ts_sym_string] = SHIFT(330),
        [ts_sym_identifier] = SHIFT(331),
        [ts_sym_number] = SHIFT(330),
        [ts_sym_null] = SHIFT(330),
        [ts_sym_true] = SHIFT(330),
        [ts_sym_false] = SHIFT(330),
        [ts_aux_sym_token0] = SHIFT(334),
        [ts_aux_sym_token3] = SHIFT(348),
        [ts_aux_sym_token27] = SHIFT(356),
        [ts_aux_sym_token30] = SHIFT(358),
        [ts_aux_sym_token33] = SHIFT(430),
        [ts_aux_sym_token34] = SHIFT(507),
    },
    [503] = {
        [ts_aux_sym_array_repeat0] = SHIFT(504),
        [ts_aux_sym_token3] = SHIFT(298),
        [ts_aux_sym_token15] = SHIFT(304),
        [ts_aux_sym_token16] = SHIFT(304),
        [ts_aux_sym_token17] = SHIFT(306),
        [ts_aux_sym_token18] = SHIFT(306),
        [ts_aux_sym_token19] = SHIFT(308),
        [ts_aux_sym_token20] = SHIFT(310),
        [ts_aux_sym_token21] = SHIFT(312),
        [ts_aux_sym_token22] = SHIFT(312),
        [ts_aux_sym_token23] = SHIFT(312),
        [ts_aux_sym_token24] = SHIFT(312),
        [ts_aux_sym_token25] = SHIFT(312),
        [ts_aux_sym_token26] = SHIFT(312),
        [ts_aux_sym_token28] = SHIFT(314),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token32] = SHIFT(318),
        [ts_aux_sym_token33] = SHIFT(320),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [504] = {
        [ts_aux_sym_token34] = SHIFT(505),
    },
    [505] = {
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
    [506] = {
        [ts_aux_sym_array_repeat0] = SHIFT(504),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [507] = {
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
    [508] = {
        [ts_sym__terminator] = SHIFT(509),
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
        [ts_aux_sym_token29] = SHIFT(401),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [509] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [510] = {
        [ts_sym_formal_parameters] = SHIFT(511),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [511] = {
        [ts_sym_statement_block] = SHIFT(512),
        [ts_aux_sym_token0] = SHIFT(374),
    },
    [512] = {
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
    [513] = {
        [ts_sym_formal_parameters] = SHIFT(514),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [514] = {
        [ts_sym_statement_block] = SHIFT(515),
        [ts_aux_sym_token0] = SHIFT(361),
    },
    [515] = {
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
    [516] = {
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
    [517] = {
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
    [518] = {
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
    [519] = {
        [ts_aux_sym_array_repeat0] = SHIFT(329),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [520] = {
        [ts_aux_sym_array_repeat0] = SHIFT(325),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [521] = {
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
    [522] = {
        [ts_aux_sym_array_repeat0] = SHIFT(296),
        [ts_aux_sym_token31] = SHIFT(327),
        [ts_aux_sym_token34] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [523] = {
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
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [525] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [526] = {
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [527] = {
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [528] = {
        [ts_aux_sym_token3] = SHIFT(529),
    },
    [529] = {
        [ts_sym_var_declaration] = SHIFT(530),
        [ts_sym_expression_statement] = SHIFT(530),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [530] = {
        [ts_sym_expression_statement] = SHIFT(531),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [531] = {
        [ts_sym_expression] = SHIFT(532),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(619),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [532] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(533),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [533] = {
        [ts_sym_statement] = SHIFT(534),
        [ts_sym_statement_block] = SHIFT(275),
        [ts_sym_for_statement] = SHIFT(275),
        [ts_sym_if_statement] = SHIFT(275),
        [ts_sym_switch_statement] = SHIFT(275),
        [ts_sym_break_statement] = SHIFT(275),
        [ts_sym_var_declaration] = SHIFT(275),
        [ts_sym_expression_statement] = SHIFT(275),
        [ts_sym_return_statement] = SHIFT(275),
        [ts_sym_delete_statement] = SHIFT(275),
        [ts_sym_expression] = SHIFT(276),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(278),
        [ts_sym_comment] = SHIFT(275),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(280),
        [ts_aux_sym_token2] = SHIFT(528),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(535),
        [ts_aux_sym_token7] = SHIFT(542),
        [ts_aux_sym_token11] = SHIFT(552),
        [ts_aux_sym_token12] = SHIFT(554),
        [ts_aux_sym_token13] = SHIFT(558),
        [ts_aux_sym_token14] = SHIFT(562),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [534] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [535] = {
        [ts_aux_sym_token3] = SHIFT(536),
    },
    [536] = {
        [ts_sym_expression] = SHIFT(537),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(618),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [537] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(538),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [538] = {
        [ts_sym_statement] = SHIFT(539),
        [ts_sym_statement_block] = SHIFT(566),
        [ts_sym_for_statement] = SHIFT(566),
        [ts_sym_if_statement] = SHIFT(566),
        [ts_sym_switch_statement] = SHIFT(566),
        [ts_sym_break_statement] = SHIFT(566),
        [ts_sym_var_declaration] = SHIFT(566),
        [ts_sym_expression_statement] = SHIFT(566),
        [ts_sym_return_statement] = SHIFT(566),
        [ts_sym_delete_statement] = SHIFT(566),
        [ts_sym_expression] = SHIFT(567),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(569),
        [ts_sym_comment] = SHIFT(566),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(570),
        [ts_aux_sym_token2] = SHIFT(574),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(581),
        [ts_aux_sym_token7] = SHIFT(588),
        [ts_aux_sym_token11] = SHIFT(596),
        [ts_aux_sym_token12] = SHIFT(598),
        [ts_aux_sym_token13] = SHIFT(602),
        [ts_aux_sym_token14] = SHIFT(606),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [539] = {
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
        [ts_aux_sym_token6] = SHIFT(540),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [540] = {
        [ts_sym_statement] = SHIFT(541),
        [ts_sym_statement_block] = SHIFT(275),
        [ts_sym_for_statement] = SHIFT(275),
        [ts_sym_if_statement] = SHIFT(275),
        [ts_sym_switch_statement] = SHIFT(275),
        [ts_sym_break_statement] = SHIFT(275),
        [ts_sym_var_declaration] = SHIFT(275),
        [ts_sym_expression_statement] = SHIFT(275),
        [ts_sym_return_statement] = SHIFT(275),
        [ts_sym_delete_statement] = SHIFT(275),
        [ts_sym_expression] = SHIFT(276),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(278),
        [ts_sym_comment] = SHIFT(275),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(280),
        [ts_aux_sym_token2] = SHIFT(528),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(535),
        [ts_aux_sym_token7] = SHIFT(542),
        [ts_aux_sym_token11] = SHIFT(552),
        [ts_aux_sym_token12] = SHIFT(554),
        [ts_aux_sym_token13] = SHIFT(558),
        [ts_aux_sym_token14] = SHIFT(562),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [541] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [542] = {
        [ts_aux_sym_token3] = SHIFT(543),
    },
    [543] = {
        [ts_sym_expression] = SHIFT(544),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(565),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [544] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(545),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [545] = {
        [ts_aux_sym_token0] = SHIFT(546),
    },
    [546] = {
        [ts_sym_switch_case] = SHIFT(269),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(547),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(549),
    },
    [547] = {
        [ts_aux_sym_token1] = SHIFT(548),
    },
    [548] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [549] = {
        [ts_aux_sym_token10] = SHIFT(550),
    },
    [550] = {
        [ts_sym_statement] = SHIFT(274),
        [ts_sym_statement_block] = SHIFT(275),
        [ts_sym_for_statement] = SHIFT(275),
        [ts_sym_if_statement] = SHIFT(275),
        [ts_sym_switch_statement] = SHIFT(275),
        [ts_sym_break_statement] = SHIFT(275),
        [ts_sym_var_declaration] = SHIFT(275),
        [ts_sym_expression_statement] = SHIFT(275),
        [ts_sym_return_statement] = SHIFT(275),
        [ts_sym_delete_statement] = SHIFT(275),
        [ts_sym_expression] = SHIFT(276),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(278),
        [ts_sym_comment] = SHIFT(275),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(551),
        [ts_aux_sym_token0] = SHIFT(280),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(528),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(535),
        [ts_aux_sym_token7] = SHIFT(542),
        [ts_aux_sym_token8] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token11] = SHIFT(552),
        [ts_aux_sym_token12] = SHIFT(554),
        [ts_aux_sym_token13] = SHIFT(558),
        [ts_aux_sym_token14] = SHIFT(562),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [551] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_case, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_case, 3),
    },
    [552] = {
        [ts_sym__terminator] = SHIFT(553),
    },
    [553] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [554] = {
        [ts_sym_expression] = SHIFT(287),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(555),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(526),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(557),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [555] = {
        [ts_sym__terminator] = SHIFT(556),
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
    [556] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [557] = {
        [ts_sym__terminator] = SHIFT(556),
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [558] = {
        [ts_sym_expression] = SHIFT(559),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym__terminator] = SHIFT(561),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [559] = {
        [ts_sym__terminator] = SHIFT(560),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [560] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [561] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [562] = {
        [ts_sym_expression] = SHIFT(379),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(563),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [563] = {
        [ts_sym__terminator] = SHIFT(564),
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
        [ts_aux_sym_token29] = SHIFT(401),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [564] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [565] = {
        [ts_aux_sym_token4] = SHIFT(545),
    },
    [566] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [567] = {
        [ts_sym__terminator] = SHIFT(568),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [568] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [569] = {
        [ts_sym__terminator] = SHIFT(568),
    },
    [570] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(571),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(231),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(573),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = SHIFT(233),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [571] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_object_repeat0] = SHIFT(182),
        [ts_aux_sym_token1] = SHIFT(572),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [572] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [573] = {
        [ts_aux_sym_token1] = SHIFT(572),
    },
    [574] = {
        [ts_aux_sym_token3] = SHIFT(575),
    },
    [575] = {
        [ts_sym_var_declaration] = SHIFT(576),
        [ts_sym_expression_statement] = SHIFT(576),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [576] = {
        [ts_sym_expression_statement] = SHIFT(577),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [577] = {
        [ts_sym_expression] = SHIFT(578),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(610),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [578] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(579),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [579] = {
        [ts_sym_statement] = SHIFT(580),
        [ts_sym_statement_block] = SHIFT(566),
        [ts_sym_for_statement] = SHIFT(566),
        [ts_sym_if_statement] = SHIFT(566),
        [ts_sym_switch_statement] = SHIFT(566),
        [ts_sym_break_statement] = SHIFT(566),
        [ts_sym_var_declaration] = SHIFT(566),
        [ts_sym_expression_statement] = SHIFT(566),
        [ts_sym_return_statement] = SHIFT(566),
        [ts_sym_delete_statement] = SHIFT(566),
        [ts_sym_expression] = SHIFT(567),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(569),
        [ts_sym_comment] = SHIFT(566),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(570),
        [ts_aux_sym_token2] = SHIFT(574),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(581),
        [ts_aux_sym_token7] = SHIFT(588),
        [ts_aux_sym_token11] = SHIFT(596),
        [ts_aux_sym_token12] = SHIFT(598),
        [ts_aux_sym_token13] = SHIFT(602),
        [ts_aux_sym_token14] = SHIFT(606),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [580] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [581] = {
        [ts_aux_sym_token3] = SHIFT(582),
    },
    [582] = {
        [ts_sym_expression] = SHIFT(583),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(609),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [583] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(584),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [584] = {
        [ts_sym_statement] = SHIFT(585),
        [ts_sym_statement_block] = SHIFT(566),
        [ts_sym_for_statement] = SHIFT(566),
        [ts_sym_if_statement] = SHIFT(566),
        [ts_sym_switch_statement] = SHIFT(566),
        [ts_sym_break_statement] = SHIFT(566),
        [ts_sym_var_declaration] = SHIFT(566),
        [ts_sym_expression_statement] = SHIFT(566),
        [ts_sym_return_statement] = SHIFT(566),
        [ts_sym_delete_statement] = SHIFT(566),
        [ts_sym_expression] = SHIFT(567),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(569),
        [ts_sym_comment] = SHIFT(566),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(570),
        [ts_aux_sym_token2] = SHIFT(574),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(581),
        [ts_aux_sym_token7] = SHIFT(588),
        [ts_aux_sym_token11] = SHIFT(596),
        [ts_aux_sym_token12] = SHIFT(598),
        [ts_aux_sym_token13] = SHIFT(602),
        [ts_aux_sym_token14] = SHIFT(606),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [585] = {
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
        [ts_aux_sym_token6] = SHIFT(586),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [586] = {
        [ts_sym_statement] = SHIFT(587),
        [ts_sym_statement_block] = SHIFT(566),
        [ts_sym_for_statement] = SHIFT(566),
        [ts_sym_if_statement] = SHIFT(566),
        [ts_sym_switch_statement] = SHIFT(566),
        [ts_sym_break_statement] = SHIFT(566),
        [ts_sym_var_declaration] = SHIFT(566),
        [ts_sym_expression_statement] = SHIFT(566),
        [ts_sym_return_statement] = SHIFT(566),
        [ts_sym_delete_statement] = SHIFT(566),
        [ts_sym_expression] = SHIFT(567),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(569),
        [ts_sym_comment] = SHIFT(566),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(570),
        [ts_aux_sym_token2] = SHIFT(574),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(581),
        [ts_aux_sym_token7] = SHIFT(588),
        [ts_aux_sym_token11] = SHIFT(596),
        [ts_aux_sym_token12] = SHIFT(598),
        [ts_aux_sym_token13] = SHIFT(602),
        [ts_aux_sym_token14] = SHIFT(606),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [587] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [588] = {
        [ts_aux_sym_token3] = SHIFT(589),
    },
    [589] = {
        [ts_sym_expression] = SHIFT(590),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(595),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [590] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(591),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [591] = {
        [ts_aux_sym_token0] = SHIFT(592),
    },
    [592] = {
        [ts_sym_switch_case] = SHIFT(269),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(593),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(549),
    },
    [593] = {
        [ts_aux_sym_token1] = SHIFT(594),
    },
    [594] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [595] = {
        [ts_aux_sym_token4] = SHIFT(591),
    },
    [596] = {
        [ts_sym__terminator] = SHIFT(597),
    },
    [597] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [598] = {
        [ts_sym_expression] = SHIFT(287),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(599),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(526),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(601),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [599] = {
        [ts_sym__terminator] = SHIFT(600),
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
    [600] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [601] = {
        [ts_sym__terminator] = SHIFT(600),
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [602] = {
        [ts_sym_expression] = SHIFT(603),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym__terminator] = SHIFT(605),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [603] = {
        [ts_sym__terminator] = SHIFT(604),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [604] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [605] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [606] = {
        [ts_sym_expression] = SHIFT(379),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(607),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [607] = {
        [ts_sym__terminator] = SHIFT(608),
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
        [ts_aux_sym_token29] = SHIFT(401),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [608] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [609] = {
        [ts_aux_sym_token4] = SHIFT(584),
    },
    [610] = {
        [ts_aux_sym_token4] = SHIFT(579),
    },
    [611] = {
        [ts_sym__terminator] = SHIFT(612),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [612] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [613] = {
        [ts_sym__terminator] = SHIFT(612),
    },
    [614] = {
        [ts_sym_expression] = SHIFT(287),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(615),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(526),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(617),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
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
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_null] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_true] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_false] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [618] = {
        [ts_aux_sym_token4] = SHIFT(538),
    },
    [619] = {
        [ts_aux_sym_token4] = SHIFT(533),
    },
    [620] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_switch_case, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_switch_case, 4),
    },
    [621] = {
        [ts_aux_sym_token1] = SHIFT(622),
    },
    [622] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [623] = {
        [ts_aux_sym_token4] = SHIFT(267),
    },
    [624] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [625] = {
        [ts_sym__terminator] = SHIFT(626),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [626] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [627] = {
        [ts_sym__terminator] = SHIFT(626),
    },
    [628] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(629),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(231),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(631),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = SHIFT(233),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [629] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_object_repeat0] = SHIFT(182),
        [ts_aux_sym_token1] = SHIFT(630),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [630] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [631] = {
        [ts_aux_sym_token1] = SHIFT(630),
    },
    [632] = {
        [ts_aux_sym_token3] = SHIFT(633),
    },
    [633] = {
        [ts_sym_var_declaration] = SHIFT(634),
        [ts_sym_expression_statement] = SHIFT(634),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [634] = {
        [ts_sym_expression_statement] = SHIFT(635),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [635] = {
        [ts_sym_expression] = SHIFT(636),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(668),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [636] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(637),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [637] = {
        [ts_sym_statement] = SHIFT(638),
        [ts_sym_statement_block] = SHIFT(624),
        [ts_sym_for_statement] = SHIFT(624),
        [ts_sym_if_statement] = SHIFT(624),
        [ts_sym_switch_statement] = SHIFT(624),
        [ts_sym_break_statement] = SHIFT(624),
        [ts_sym_var_declaration] = SHIFT(624),
        [ts_sym_expression_statement] = SHIFT(624),
        [ts_sym_return_statement] = SHIFT(624),
        [ts_sym_delete_statement] = SHIFT(624),
        [ts_sym_expression] = SHIFT(625),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(627),
        [ts_sym_comment] = SHIFT(624),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(628),
        [ts_aux_sym_token2] = SHIFT(632),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(639),
        [ts_aux_sym_token7] = SHIFT(646),
        [ts_aux_sym_token11] = SHIFT(654),
        [ts_aux_sym_token12] = SHIFT(656),
        [ts_aux_sym_token13] = SHIFT(660),
        [ts_aux_sym_token14] = SHIFT(664),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [638] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [639] = {
        [ts_aux_sym_token3] = SHIFT(640),
    },
    [640] = {
        [ts_sym_expression] = SHIFT(641),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(667),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [641] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(642),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [642] = {
        [ts_sym_statement] = SHIFT(643),
        [ts_sym_statement_block] = SHIFT(624),
        [ts_sym_for_statement] = SHIFT(624),
        [ts_sym_if_statement] = SHIFT(624),
        [ts_sym_switch_statement] = SHIFT(624),
        [ts_sym_break_statement] = SHIFT(624),
        [ts_sym_var_declaration] = SHIFT(624),
        [ts_sym_expression_statement] = SHIFT(624),
        [ts_sym_return_statement] = SHIFT(624),
        [ts_sym_delete_statement] = SHIFT(624),
        [ts_sym_expression] = SHIFT(625),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(627),
        [ts_sym_comment] = SHIFT(624),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(628),
        [ts_aux_sym_token2] = SHIFT(632),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(639),
        [ts_aux_sym_token7] = SHIFT(646),
        [ts_aux_sym_token11] = SHIFT(654),
        [ts_aux_sym_token12] = SHIFT(656),
        [ts_aux_sym_token13] = SHIFT(660),
        [ts_aux_sym_token14] = SHIFT(664),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [643] = {
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
        [ts_aux_sym_token6] = SHIFT(644),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [644] = {
        [ts_sym_statement] = SHIFT(645),
        [ts_sym_statement_block] = SHIFT(624),
        [ts_sym_for_statement] = SHIFT(624),
        [ts_sym_if_statement] = SHIFT(624),
        [ts_sym_switch_statement] = SHIFT(624),
        [ts_sym_break_statement] = SHIFT(624),
        [ts_sym_var_declaration] = SHIFT(624),
        [ts_sym_expression_statement] = SHIFT(624),
        [ts_sym_return_statement] = SHIFT(624),
        [ts_sym_delete_statement] = SHIFT(624),
        [ts_sym_expression] = SHIFT(625),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(627),
        [ts_sym_comment] = SHIFT(624),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(628),
        [ts_aux_sym_token2] = SHIFT(632),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(639),
        [ts_aux_sym_token7] = SHIFT(646),
        [ts_aux_sym_token11] = SHIFT(654),
        [ts_aux_sym_token12] = SHIFT(656),
        [ts_aux_sym_token13] = SHIFT(660),
        [ts_aux_sym_token14] = SHIFT(664),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [645] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [646] = {
        [ts_aux_sym_token3] = SHIFT(647),
    },
    [647] = {
        [ts_sym_expression] = SHIFT(648),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(653),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [648] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(649),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [649] = {
        [ts_aux_sym_token0] = SHIFT(650),
    },
    [650] = {
        [ts_sym_switch_case] = SHIFT(269),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(651),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(549),
    },
    [651] = {
        [ts_aux_sym_token1] = SHIFT(652),
    },
    [652] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [653] = {
        [ts_aux_sym_token4] = SHIFT(649),
    },
    [654] = {
        [ts_sym__terminator] = SHIFT(655),
    },
    [655] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [656] = {
        [ts_sym_expression] = SHIFT(287),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(657),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(526),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(659),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [657] = {
        [ts_sym__terminator] = SHIFT(658),
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
    [658] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [659] = {
        [ts_sym__terminator] = SHIFT(658),
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [660] = {
        [ts_sym_expression] = SHIFT(661),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym__terminator] = SHIFT(663),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [661] = {
        [ts_sym__terminator] = SHIFT(662),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [662] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [663] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [664] = {
        [ts_sym_expression] = SHIFT(379),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(665),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [665] = {
        [ts_sym__terminator] = SHIFT(666),
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
        [ts_aux_sym_token29] = SHIFT(401),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [666] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [667] = {
        [ts_aux_sym_token4] = SHIFT(642),
    },
    [668] = {
        [ts_aux_sym_token4] = SHIFT(637),
    },
    [669] = {
        [ts_aux_sym_token4] = SHIFT(260),
    },
    [670] = {
        [ts_sym_formal_parameters] = SHIFT(671),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [671] = {
        [ts_sym_statement_block] = SHIFT(672),
        [ts_aux_sym_token0] = SHIFT(253),
    },
    [672] = {
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
    [673] = {
        [ts_aux_sym_token4] = SHIFT(239),
    },
    [674] = {
        [ts_sym_formal_parameters] = SHIFT(675),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [675] = {
        [ts_sym_statement_block] = SHIFT(676),
        [ts_aux_sym_token0] = SHIFT(223),
    },
    [676] = {
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
    [677] = {
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
    [678] = {
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
    [679] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_token1] = SHIFT(680),
    },
    [680] = {
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
    [681] = {
        [ts_aux_sym_token1] = SHIFT(680),
    },
    [682] = {
        [ts_sym_formal_parameters] = SHIFT(683),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [683] = {
        [ts_sym_statement_block] = SHIFT(684),
        [ts_aux_sym_token0] = SHIFT(175),
    },
    [684] = {
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
    [685] = {
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
    [686] = {
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
    [687] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 2),
    },
    [688] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_token1] = SHIFT(689),
    },
    [689] = {
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
    [690] = {
        [ts_aux_sym_token1] = SHIFT(689),
    },
    [691] = {
        [ts_sym_formal_parameters] = SHIFT(692),
        [ts_aux_sym_token3] = SHIFT(440),
    },
    [692] = {
        [ts_sym_statement_block] = SHIFT(693),
        [ts_aux_sym_token0] = SHIFT(74),
    },
    [693] = {
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
    [694] = {
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
    [695] = {
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
    [696] = {
        [ts_aux_sym_token10] = SHIFT(697),
    },
    [697] = {
        [ts_sym_expression] = SHIFT(698),
        [ts_sym_math_op] = SHIFT(189),
        [ts_sym_bool_op] = SHIFT(189),
        [ts_sym_ternary] = SHIFT(189),
        [ts_sym_assignment] = SHIFT(189),
        [ts_sym_function_expression] = SHIFT(189),
        [ts_sym_function_call] = SHIFT(189),
        [ts_sym_property_access] = SHIFT(190),
        [ts_sym_object] = SHIFT(189),
        [ts_sym_array] = SHIFT(189),
        [ts_sym_regex] = SHIFT(189),
        [ts_sym_string] = SHIFT(189),
        [ts_sym_identifier] = SHIFT(190),
        [ts_sym_number] = SHIFT(189),
        [ts_sym_null] = SHIFT(189),
        [ts_sym_true] = SHIFT(189),
        [ts_sym_false] = SHIFT(189),
        [ts_aux_sym_token0] = SHIFT(193),
        [ts_aux_sym_token3] = SHIFT(202),
        [ts_aux_sym_token27] = SHIFT(218),
        [ts_aux_sym_token30] = SHIFT(220),
        [ts_aux_sym_token33] = SHIFT(343),
    },
    [698] = {
        [ts_aux_sym_object_repeat0] = SHIFT(699),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token3] = SHIFT(56),
        [ts_aux_sym_token15] = SHIFT(129),
        [ts_aux_sym_token16] = SHIFT(129),
        [ts_aux_sym_token17] = SHIFT(131),
        [ts_aux_sym_token18] = SHIFT(131),
        [ts_aux_sym_token19] = SHIFT(133),
        [ts_aux_sym_token20] = SHIFT(135),
        [ts_aux_sym_token21] = SHIFT(137),
        [ts_aux_sym_token22] = SHIFT(137),
        [ts_aux_sym_token23] = SHIFT(137),
        [ts_aux_sym_token24] = SHIFT(137),
        [ts_aux_sym_token25] = SHIFT(137),
        [ts_aux_sym_token26] = SHIFT(137),
        [ts_aux_sym_token28] = SHIFT(139),
        [ts_aux_sym_token31] = SHIFT(49),
        [ts_aux_sym_token32] = SHIFT(143),
        [ts_aux_sym_token33] = SHIFT(145),
    },
    [699] = {
        [ts_aux_sym_token1] = SHIFT(700),
    },
    [700] = {
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
    [701] = {
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
    [702] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(39),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [703] = {
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
    [704] = {
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
    [705] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(32),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [706] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(28),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [707] = {
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
    [708] = {
        [ts_sym_expression] = SHIFT(709),
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
        [ts_aux_sym_token27] = SHIFT(69),
        [ts_aux_sym_token30] = SHIFT(71),
        [ts_aux_sym_token33] = SHIFT(294),
    },
    [709] = {
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
    [710] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [711] = {
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
    [712] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(8),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token31] = SHIFT(30),
    },
    [713] = {
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
    [714] = {
        [ts_sym__terminator] = SHIFT(5),
    },
    [715] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [716] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(717),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(231),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(719),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = SHIFT(233),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [717] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_object_repeat0] = SHIFT(182),
        [ts_aux_sym_token1] = SHIFT(718),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [718] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [719] = {
        [ts_aux_sym_token1] = SHIFT(718),
    },
    [720] = {
        [ts_aux_sym_token3] = SHIFT(721),
    },
    [721] = {
        [ts_sym_var_declaration] = SHIFT(722),
        [ts_sym_expression_statement] = SHIFT(722),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [722] = {
        [ts_sym_expression_statement] = SHIFT(723),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [723] = {
        [ts_sym_expression] = SHIFT(724),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(801),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [724] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(725),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [725] = {
        [ts_sym_statement] = SHIFT(726),
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
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(716),
        [ts_aux_sym_token2] = SHIFT(720),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(727),
        [ts_aux_sym_token7] = SHIFT(734),
        [ts_aux_sym_token11] = SHIFT(742),
        [ts_aux_sym_token12] = SHIFT(744),
        [ts_aux_sym_token13] = SHIFT(748),
        [ts_aux_sym_token14] = SHIFT(752),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [726] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [727] = {
        [ts_aux_sym_token3] = SHIFT(728),
    },
    [728] = {
        [ts_sym_expression] = SHIFT(729),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(800),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [729] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(730),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [730] = {
        [ts_sym_statement] = SHIFT(731),
        [ts_sym_statement_block] = SHIFT(755),
        [ts_sym_for_statement] = SHIFT(755),
        [ts_sym_if_statement] = SHIFT(755),
        [ts_sym_switch_statement] = SHIFT(755),
        [ts_sym_break_statement] = SHIFT(755),
        [ts_sym_var_declaration] = SHIFT(755),
        [ts_sym_expression_statement] = SHIFT(755),
        [ts_sym_return_statement] = SHIFT(755),
        [ts_sym_delete_statement] = SHIFT(755),
        [ts_sym_expression] = SHIFT(756),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(758),
        [ts_sym_comment] = SHIFT(755),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(759),
        [ts_aux_sym_token2] = SHIFT(763),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(770),
        [ts_aux_sym_token7] = SHIFT(777),
        [ts_aux_sym_token11] = SHIFT(785),
        [ts_aux_sym_token12] = SHIFT(787),
        [ts_aux_sym_token13] = SHIFT(791),
        [ts_aux_sym_token14] = SHIFT(795),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [731] = {
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
        [ts_aux_sym_token6] = SHIFT(732),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [732] = {
        [ts_sym_statement] = SHIFT(733),
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
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(716),
        [ts_aux_sym_token2] = SHIFT(720),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(727),
        [ts_aux_sym_token7] = SHIFT(734),
        [ts_aux_sym_token11] = SHIFT(742),
        [ts_aux_sym_token12] = SHIFT(744),
        [ts_aux_sym_token13] = SHIFT(748),
        [ts_aux_sym_token14] = SHIFT(752),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [733] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [734] = {
        [ts_aux_sym_token3] = SHIFT(735),
    },
    [735] = {
        [ts_sym_expression] = SHIFT(736),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(741),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [736] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(737),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [737] = {
        [ts_aux_sym_token0] = SHIFT(738),
    },
    [738] = {
        [ts_sym_switch_case] = SHIFT(269),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(739),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(549),
    },
    [739] = {
        [ts_aux_sym_token1] = SHIFT(740),
    },
    [740] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [741] = {
        [ts_aux_sym_token4] = SHIFT(737),
    },
    [742] = {
        [ts_sym__terminator] = SHIFT(743),
    },
    [743] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [744] = {
        [ts_sym_expression] = SHIFT(287),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(745),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(526),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(747),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [745] = {
        [ts_sym__terminator] = SHIFT(746),
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
    [746] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [747] = {
        [ts_sym__terminator] = SHIFT(746),
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [748] = {
        [ts_sym_expression] = SHIFT(749),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym__terminator] = SHIFT(751),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [749] = {
        [ts_sym__terminator] = SHIFT(750),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [750] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [751] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [752] = {
        [ts_sym_expression] = SHIFT(379),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(753),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [753] = {
        [ts_sym__terminator] = SHIFT(754),
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
        [ts_aux_sym_token29] = SHIFT(401),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [754] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [755] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement, 1),
    },
    [756] = {
        [ts_sym__terminator] = SHIFT(757),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [757] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression_statement, 2),
    },
    [758] = {
        [ts_sym__terminator] = SHIFT(757),
    },
    [759] = {
        [ts_sym_statement] = SHIFT(75),
        [ts_sym_statement_block] = SHIFT(76),
        [ts_sym_for_statement] = SHIFT(76),
        [ts_sym_if_statement] = SHIFT(76),
        [ts_sym_switch_statement] = SHIFT(76),
        [ts_sym_break_statement] = SHIFT(76),
        [ts_sym_var_declaration] = SHIFT(76),
        [ts_sym_expression_statement] = SHIFT(76),
        [ts_sym_return_statement] = SHIFT(76),
        [ts_sym_delete_statement] = SHIFT(76),
        [ts_sym_expression] = SHIFT(77),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(760),
        [ts_sym_comment] = SHIFT(76),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(230),
        [ts_sym_identifier] = SHIFT(231),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(762),
        [ts_aux_sym_token0] = SHIFT(227),
        [ts_aux_sym_token1] = SHIFT(233),
        [ts_aux_sym_token2] = SHIFT(234),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(257),
        [ts_aux_sym_token7] = SHIFT(264),
        [ts_aux_sym_token11] = SHIFT(284),
        [ts_aux_sym_token12] = SHIFT(286),
        [ts_aux_sym_token13] = SHIFT(365),
        [ts_aux_sym_token14] = SHIFT(378),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [760] = {
        [ts_sym__terminator] = SHIFT(78),
        [ts_aux_sym_object_repeat0] = SHIFT(182),
        [ts_aux_sym_token1] = SHIFT(761),
        [ts_aux_sym_token31] = SHIFT(49),
    },
    [761] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_statement_block, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_statement_block, 3),
    },
    [762] = {
        [ts_aux_sym_token1] = SHIFT(761),
    },
    [763] = {
        [ts_aux_sym_token3] = SHIFT(764),
    },
    [764] = {
        [ts_sym_var_declaration] = SHIFT(765),
        [ts_sym_expression_statement] = SHIFT(765),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token12] = SHIFT(614),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [765] = {
        [ts_sym_expression_statement] = SHIFT(766),
        [ts_sym_expression] = SHIFT(611),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(613),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [766] = {
        [ts_sym_expression] = SHIFT(767),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(799),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [767] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(768),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [768] = {
        [ts_sym_statement] = SHIFT(769),
        [ts_sym_statement_block] = SHIFT(755),
        [ts_sym_for_statement] = SHIFT(755),
        [ts_sym_if_statement] = SHIFT(755),
        [ts_sym_switch_statement] = SHIFT(755),
        [ts_sym_break_statement] = SHIFT(755),
        [ts_sym_var_declaration] = SHIFT(755),
        [ts_sym_expression_statement] = SHIFT(755),
        [ts_sym_return_statement] = SHIFT(755),
        [ts_sym_delete_statement] = SHIFT(755),
        [ts_sym_expression] = SHIFT(756),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(758),
        [ts_sym_comment] = SHIFT(755),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(759),
        [ts_aux_sym_token2] = SHIFT(763),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(770),
        [ts_aux_sym_token7] = SHIFT(777),
        [ts_aux_sym_token11] = SHIFT(785),
        [ts_aux_sym_token12] = SHIFT(787),
        [ts_aux_sym_token13] = SHIFT(791),
        [ts_aux_sym_token14] = SHIFT(795),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [769] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_for_statement, 7),
    },
    [770] = {
        [ts_aux_sym_token3] = SHIFT(771),
    },
    [771] = {
        [ts_sym_expression] = SHIFT(772),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(798),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [772] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(773),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [773] = {
        [ts_sym_statement] = SHIFT(774),
        [ts_sym_statement_block] = SHIFT(755),
        [ts_sym_for_statement] = SHIFT(755),
        [ts_sym_if_statement] = SHIFT(755),
        [ts_sym_switch_statement] = SHIFT(755),
        [ts_sym_break_statement] = SHIFT(755),
        [ts_sym_var_declaration] = SHIFT(755),
        [ts_sym_expression_statement] = SHIFT(755),
        [ts_sym_return_statement] = SHIFT(755),
        [ts_sym_delete_statement] = SHIFT(755),
        [ts_sym_expression] = SHIFT(756),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(758),
        [ts_sym_comment] = SHIFT(755),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(759),
        [ts_aux_sym_token2] = SHIFT(763),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(770),
        [ts_aux_sym_token7] = SHIFT(777),
        [ts_aux_sym_token11] = SHIFT(785),
        [ts_aux_sym_token12] = SHIFT(787),
        [ts_aux_sym_token13] = SHIFT(791),
        [ts_aux_sym_token14] = SHIFT(795),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [774] = {
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
        [ts_aux_sym_token6] = SHIFT(775),
        [ts_aux_sym_token7] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token12] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token13] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token14] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 5),
    },
    [775] = {
        [ts_sym_statement] = SHIFT(776),
        [ts_sym_statement_block] = SHIFT(755),
        [ts_sym_for_statement] = SHIFT(755),
        [ts_sym_if_statement] = SHIFT(755),
        [ts_sym_switch_statement] = SHIFT(755),
        [ts_sym_break_statement] = SHIFT(755),
        [ts_sym_var_declaration] = SHIFT(755),
        [ts_sym_expression_statement] = SHIFT(755),
        [ts_sym_return_statement] = SHIFT(755),
        [ts_sym_delete_statement] = SHIFT(755),
        [ts_sym_expression] = SHIFT(756),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_builtin_sym_error] = SHIFT(758),
        [ts_sym_comment] = SHIFT(755),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(759),
        [ts_aux_sym_token2] = SHIFT(763),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token5] = SHIFT(770),
        [ts_aux_sym_token7] = SHIFT(777),
        [ts_aux_sym_token11] = SHIFT(785),
        [ts_aux_sym_token12] = SHIFT(787),
        [ts_aux_sym_token13] = SHIFT(791),
        [ts_aux_sym_token14] = SHIFT(795),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [776] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_if_statement, 7),
    },
    [777] = {
        [ts_aux_sym_token3] = SHIFT(778),
    },
    [778] = {
        [ts_sym_expression] = SHIFT(779),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_ternary] = SHIFT(205),
        [ts_sym_assignment] = SHIFT(205),
        [ts_sym_function_expression] = SHIFT(205),
        [ts_sym_function_call] = SHIFT(205),
        [ts_sym_property_access] = SHIFT(206),
        [ts_sym_object] = SHIFT(205),
        [ts_sym_array] = SHIFT(205),
        [ts_builtin_sym_error] = SHIFT(784),
        [ts_sym_regex] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym_identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_null] = SHIFT(205),
        [ts_sym_true] = SHIFT(205),
        [ts_sym_false] = SHIFT(205),
        [ts_aux_sym_token0] = SHIFT(209),
        [ts_aux_sym_token3] = SHIFT(245),
        [ts_aux_sym_token27] = SHIFT(248),
        [ts_aux_sym_token30] = SHIFT(250),
        [ts_aux_sym_token33] = SHIFT(351),
    },
    [779] = {
        [ts_aux_sym_token3] = SHIFT(63),
        [ts_aux_sym_token4] = SHIFT(780),
        [ts_aux_sym_token15] = SHIFT(151),
        [ts_aux_sym_token16] = SHIFT(151),
        [ts_aux_sym_token17] = SHIFT(153),
        [ts_aux_sym_token18] = SHIFT(153),
        [ts_aux_sym_token19] = SHIFT(155),
        [ts_aux_sym_token20] = SHIFT(157),
        [ts_aux_sym_token21] = SHIFT(159),
        [ts_aux_sym_token22] = SHIFT(159),
        [ts_aux_sym_token23] = SHIFT(159),
        [ts_aux_sym_token24] = SHIFT(159),
        [ts_aux_sym_token25] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(159),
        [ts_aux_sym_token28] = SHIFT(161),
        [ts_aux_sym_token32] = SHIFT(165),
        [ts_aux_sym_token33] = SHIFT(167),
    },
    [780] = {
        [ts_aux_sym_token0] = SHIFT(781),
    },
    [781] = {
        [ts_sym_switch_case] = SHIFT(269),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(782),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(271),
        [ts_aux_sym_token9] = SHIFT(549),
    },
    [782] = {
        [ts_aux_sym_token1] = SHIFT(783),
    },
    [783] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token30] = REDUCE(ts_sym_switch_statement, 7),
        [ts_aux_sym_token33] = REDUCE(ts_sym_switch_statement, 7),
    },
    [784] = {
        [ts_aux_sym_token4] = SHIFT(780),
    },
    [785] = {
        [ts_sym__terminator] = SHIFT(786),
    },
    [786] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_break_statement, 2),
    },
    [787] = {
        [ts_sym_expression] = SHIFT(287),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(788),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(526),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(790),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [788] = {
        [ts_sym__terminator] = SHIFT(789),
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
    [789] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_var_declaration, 3),
    },
    [790] = {
        [ts_sym__terminator] = SHIFT(789),
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
        [ts_aux_sym_token29] = SHIFT(178),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [791] = {
        [ts_sym_expression] = SHIFT(792),
        [ts_sym_math_op] = SHIFT(176),
        [ts_sym_bool_op] = SHIFT(176),
        [ts_sym_ternary] = SHIFT(176),
        [ts_sym_assignment] = SHIFT(176),
        [ts_sym_function_expression] = SHIFT(176),
        [ts_sym_function_call] = SHIFT(176),
        [ts_sym_property_access] = SHIFT(177),
        [ts_sym_object] = SHIFT(176),
        [ts_sym_array] = SHIFT(176),
        [ts_sym__terminator] = SHIFT(794),
        [ts_sym_regex] = SHIFT(176),
        [ts_sym_string] = SHIFT(176),
        [ts_sym_identifier] = SHIFT(177),
        [ts_sym_number] = SHIFT(176),
        [ts_sym_null] = SHIFT(176),
        [ts_sym_true] = SHIFT(176),
        [ts_sym_false] = SHIFT(176),
        [ts_aux_sym_token0] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(242),
        [ts_aux_sym_token27] = SHIFT(369),
        [ts_aux_sym_token30] = SHIFT(371),
        [ts_aux_sym_token33] = SHIFT(425),
    },
    [792] = {
        [ts_sym__terminator] = SHIFT(793),
        [ts_aux_sym_token3] = SHIFT(6),
        [ts_aux_sym_token15] = SHIFT(79),
        [ts_aux_sym_token16] = SHIFT(79),
        [ts_aux_sym_token17] = SHIFT(81),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token19] = SHIFT(83),
        [ts_aux_sym_token20] = SHIFT(85),
        [ts_aux_sym_token21] = SHIFT(87),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(87),
        [ts_aux_sym_token24] = SHIFT(87),
        [ts_aux_sym_token25] = SHIFT(87),
        [ts_aux_sym_token26] = SHIFT(87),
        [ts_aux_sym_token28] = SHIFT(89),
        [ts_aux_sym_token32] = SHIFT(93),
        [ts_aux_sym_token33] = SHIFT(95),
    },
    [793] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 3),
    },
    [794] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token30] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token33] = REDUCE(ts_sym_return_statement, 2),
    },
    [795] = {
        [ts_sym_expression] = SHIFT(379),
        [ts_sym_math_op] = SHIFT(399),
        [ts_sym_bool_op] = SHIFT(399),
        [ts_sym_ternary] = SHIFT(399),
        [ts_sym_assignment] = SHIFT(399),
        [ts_sym_function_expression] = SHIFT(399),
        [ts_sym_function_call] = SHIFT(399),
        [ts_sym_property_access] = SHIFT(796),
        [ts_sym_object] = SHIFT(399),
        [ts_sym_array] = SHIFT(399),
        [ts_sym_regex] = SHIFT(399),
        [ts_sym_string] = SHIFT(399),
        [ts_sym_identifier] = SHIFT(400),
        [ts_sym_number] = SHIFT(399),
        [ts_sym_null] = SHIFT(399),
        [ts_sym_true] = SHIFT(399),
        [ts_sym_false] = SHIFT(399),
        [ts_aux_sym_token0] = SHIFT(403),
        [ts_aux_sym_token3] = SHIFT(413),
        [ts_aux_sym_token27] = SHIFT(416),
        [ts_aux_sym_token30] = SHIFT(418),
        [ts_aux_sym_token33] = SHIFT(448),
    },
    [796] = {
        [ts_sym__terminator] = SHIFT(797),
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
        [ts_aux_sym_token29] = SHIFT(401),
        [ts_aux_sym_token32] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token33] = REDUCE(ts_sym_expression, 1),
    },
    [797] = {
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
        [ts_aux_sym_token27] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token30] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token33] = REDUCE(ts_sym_delete_statement, 3),
    },
    [798] = {
        [ts_aux_sym_token4] = SHIFT(773),
    },
    [799] = {
        [ts_aux_sym_token4] = SHIFT(768),
    },
    [800] = {
        [ts_aux_sym_token4] = SHIFT(730),
    },
    [801] = {
        [ts_aux_sym_token4] = SHIFT(725),
    },
    [802] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_javascript);
