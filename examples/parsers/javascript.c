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
    ts_sym__delete = 25,
    ts_sym__return = 26,
    ts_sym__break = 27,
    ts_sym__case = 28,
    ts_sym__default = 29,
    ts_sym__else = 30,
    ts_sym__for = 31,
    ts_sym__function = 32,
    ts_sym__if = 33,
    ts_sym__switch = 34,
    ts_sym__var = 35,
    ts_sym_null = 36,
    ts_sym_true = 37,
    ts_sym_false = 38,
    ts_sym_comment = 39,
    ts_sym__terminator = 40,
    ts_sym_regex = 41,
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
    [ts_sym_regex] = "regex",
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
            ACCEPT_TOKEN(ts_aux_sym_token2);
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
            ACCEPT_TOKEN(ts_aux_sym_token22);
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
            ACCEPT_TOKEN(ts_sym__break);
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
            ACCEPT_TOKEN(ts_sym__delete);
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
            ACCEPT_TOKEN(ts_sym__for);
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
            ACCEPT_TOKEN(ts_sym__function);
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
            ACCEPT_TOKEN(ts_sym__if);
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
            ACCEPT_TOKEN(ts_sym__return);
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
            ACCEPT_TOKEN(ts_sym__switch);
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
            ACCEPT_TOKEN(ts_sym__var);
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
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 80:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 81:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 82:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 83:
            ACCEPT_TOKEN(ts_aux_sym_token21);
        case 84:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 85:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 86:
            if (lookahead == '=')
                ADVANCE(87);
            ACCEPT_TOKEN(ts_aux_sym_token14);
        case 87:
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 88:
            if (lookahead == '=')
                ADVANCE(89);
            LEX_ERROR();
        case 89:
            if (lookahead == '=')
                ADVANCE(90);
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 90:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 91:
            if (lookahead == '=')
                ADVANCE(92);
            ACCEPT_TOKEN(ts_aux_sym_token16);
        case 92:
            ACCEPT_TOKEN(ts_aux_sym_token15);
        case 93:
            ACCEPT_TOKEN(ts_aux_sym_token18);
        case 94:
            if (lookahead == '|')
                ADVANCE(95);
            LEX_ERROR();
        case 95:
            ACCEPT_TOKEN(ts_aux_sym_token10);
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
            ACCEPT_TOKEN(ts_aux_sym_token3);
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
            ACCEPT_TOKEN(ts_aux_sym_token20);
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
            ACCEPT_TOKEN(ts_aux_sym_token4);
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
            ACCEPT_TOKEN(ts_aux_sym_token19);
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
            ACCEPT_TOKEN(ts_aux_sym_token23);
        case 107:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
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
        case 108:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 109:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == '\n')
                ADVANCE(110);
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
        case 110:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == '\n')
                ADVANCE(110);
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
        case 111:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(111);
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
        case 112:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(112);
            if (lookahead == '\n')
                ADVANCE(113);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 113:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(112);
            if (lookahead == '\n')
                ADVANCE(113);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '}')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 114:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(114);
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
        case 115:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == ')')
                ADVANCE(97);
            if (lookahead == ',')
                ADVANCE(99);
            LEX_ERROR();
        case 116:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 117:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == ',')
                ADVANCE(99);
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
        case 119:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
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
        case 120:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(120);
            if (lookahead == ']')
                ADVANCE(106);
            LEX_ERROR();
        case 121:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
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
        case 122:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(122);
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
                ADVANCE(123);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(124);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 123:
            if (!((lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(16);
            if (lookahead == '\\')
                ADVANCE(18);
            LEX_ERROR();
        case 124:
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
        case 125:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
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
        case 126:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
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
        case 127:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
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
        case 128:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '\n')
                ADVANCE(129);
            if (lookahead == ';')
                ADVANCE(85);
            LEX_ERROR();
        case 129:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '\n')
                ADVANCE(129);
            if (lookahead == ';')
                ADVANCE(85);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 130:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
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
                ADVANCE(131);
            if (lookahead == 'd')
                ADVANCE(135);
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
        case 131:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(132);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 132:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 's')
                ADVANCE(133);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 133:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(134);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 134:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__case);
        case 135:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'e')
                ADVANCE(136);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 136:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'f')
                ADVANCE(137);
            if (lookahead == 'l')
                ADVANCE(32);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 137:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'a')
                ADVANCE(138);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 138:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'u')
                ADVANCE(139);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 139:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 'l')
                ADVANCE(140);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 140:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == 't')
                ADVANCE(141);
            ACCEPT_TOKEN(ts_sym_identifier);
        case 141:
            if ((lookahead == '$') ||
                ('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__default);
        case 142:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
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
        case 143:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(143);
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
                ADVANCE(123);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(124);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 144:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == '\n')
                ADVANCE(145);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 145:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == '\n')
                ADVANCE(145);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '}')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 146:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if (lookahead == '\n')
                ADVANCE(147);
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
        case 147:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if (lookahead == '\n')
                ADVANCE(147);
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
        case 148:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
            if (lookahead == '\n')
                ADVANCE(149);
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
        case 149:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
            if (lookahead == '\n')
                ADVANCE(149);
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
        case 150:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(150);
            if (lookahead == ',')
                ADVANCE(99);
            if (lookahead == ']')
                ADVANCE(106);
            LEX_ERROR();
        case 151:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(151);
            if (lookahead == ':')
                ADVANCE(101);
            LEX_ERROR();
        case 152:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(152);
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
        case 153:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(153);
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
                ADVANCE(123);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == ']')
                ADVANCE(106);
            if (lookahead == 'f')
                ADVANCE(124);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 154:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(154);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 155:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(155);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == ')')
                ADVANCE(97);
            LEX_ERROR();
        case 156:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(156);
            if (lookahead == '(')
                ADVANCE(14);
            LEX_ERROR();
        case 157:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(157);
            if ((lookahead == '$') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(9);
            if (lookahead == '(')
                ADVANCE(14);
            LEX_ERROR();
        case 158:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(158);
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
        case 159:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == '\n')
                ADVANCE(160);
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
                ADVANCE(123);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(124);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
            LEX_ERROR();
        case 160:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == '\n')
                ADVANCE(160);
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
                ADVANCE(123);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == ';')
                ADVANCE(85);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(124);
            if (lookahead == 'n')
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == '{')
                ADVANCE(75);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 161:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(161);
            if (lookahead == 'c')
                ADVANCE(162);
            if (lookahead == 'd')
                ADVANCE(166);
            if (lookahead == '}')
                ADVANCE(108);
            LEX_ERROR();
        case 162:
            if (lookahead == 'a')
                ADVANCE(163);
            LEX_ERROR();
        case 163:
            if (lookahead == 's')
                ADVANCE(164);
            LEX_ERROR();
        case 164:
            if (lookahead == 'e')
                ADVANCE(165);
            LEX_ERROR();
        case 165:
            ACCEPT_TOKEN(ts_sym__case);
        case 166:
            if (lookahead == 'e')
                ADVANCE(167);
            LEX_ERROR();
        case 167:
            if (lookahead == 'f')
                ADVANCE(168);
            LEX_ERROR();
        case 168:
            if (lookahead == 'a')
                ADVANCE(169);
            LEX_ERROR();
        case 169:
            if (lookahead == 'u')
                ADVANCE(170);
            LEX_ERROR();
        case 170:
            if (lookahead == 'l')
                ADVANCE(171);
            LEX_ERROR();
        case 171:
            if (lookahead == 't')
                ADVANCE(172);
            LEX_ERROR();
        case 172:
            ACCEPT_TOKEN(ts_sym__default);
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
                ADVANCE(131);
            if (lookahead == 'd')
                ADVANCE(135);
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
            ACCEPT_TOKEN(ts_sym__else);
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
                ADVANCE(123);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            if (lookahead == '[')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(124);
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
                ADVANCE(131);
            if (lookahead == 'd')
                ADVANCE(135);
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
                ADVANCE(131);
            if (lookahead == 'd')
                ADVANCE(135);
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
            ACCEPT_TOKEN(ts_aux_sym_token6);
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
                ADVANCE(131);
            if (lookahead == 'd')
                ADVANCE(135);
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
    [6] = 122,
    [7] = 98,
    [8] = 96,
    [9] = 76,
    [10] = 122,
    [11] = 98,
    [12] = 96,
    [13] = 98,
    [14] = 143,
    [15] = 98,
    [16] = 143,
    [17] = 98,
    [18] = 143,
    [19] = 98,
    [20] = 143,
    [21] = 98,
    [22] = 143,
    [23] = 98,
    [24] = 143,
    [25] = 100,
    [26] = 122,
    [27] = 98,
    [28] = 96,
    [29] = 100,
    [30] = 143,
    [31] = 98,
    [32] = 96,
    [33] = 104,
    [34] = 102,
    [35] = 143,
    [36] = 105,
    [37] = 122,
    [38] = 98,
    [39] = 96,
    [40] = 105,
    [41] = 98,
    [42] = 102,
    [43] = 143,
    [44] = 98,
    [45] = 157,
    [46] = 154,
    [47] = 98,
    [48] = 107,
    [49] = 107,
    [50] = 107,
    [51] = 76,
    [52] = 107,
    [53] = 143,
    [54] = 76,
    [55] = 143,
    [56] = 76,
    [57] = 143,
    [58] = 76,
    [59] = 143,
    [60] = 76,
    [61] = 143,
    [62] = 76,
    [63] = 143,
    [64] = 100,
    [65] = 143,
    [66] = 76,
    [67] = 104,
    [68] = 109,
    [69] = 143,
    [70] = 105,
    [71] = 143,
    [72] = 105,
    [73] = 143,
    [74] = 105,
    [75] = 143,
    [76] = 105,
    [77] = 143,
    [78] = 105,
    [79] = 143,
    [80] = 105,
    [81] = 143,
    [82] = 100,
    [83] = 143,
    [84] = 105,
    [85] = 104,
    [86] = 111,
    [87] = 143,
    [88] = 105,
    [89] = 111,
    [90] = 105,
    [91] = 111,
    [92] = 143,
    [93] = 105,
    [94] = 157,
    [95] = 154,
    [96] = 105,
    [97] = 107,
    [98] = 76,
    [99] = 109,
    [100] = 143,
    [101] = 76,
    [102] = 157,
    [103] = 154,
    [104] = 76,
    [105] = 107,
    [106] = 112,
    [107] = 76,
    [108] = 143,
    [109] = 114,
    [110] = 122,
    [111] = 98,
    [112] = 96,
    [113] = 114,
    [114] = 115,
    [115] = 152,
    [116] = 117,
    [117] = 116,
    [118] = 98,
    [119] = 181,
    [120] = 117,
    [121] = 116,
    [122] = 151,
    [123] = 143,
    [124] = 118,
    [125] = 116,
    [126] = 122,
    [127] = 98,
    [128] = 96,
    [129] = 118,
    [130] = 115,
    [131] = 143,
    [132] = 119,
    [133] = 122,
    [134] = 98,
    [135] = 96,
    [136] = 119,
    [137] = 115,
    [138] = 119,
    [139] = 143,
    [140] = 98,
    [141] = 153,
    [142] = 121,
    [143] = 120,
    [144] = 98,
    [145] = 122,
    [146] = 98,
    [147] = 96,
    [148] = 121,
    [149] = 115,
    [150] = 121,
    [151] = 143,
    [152] = 121,
    [153] = 143,
    [154] = 121,
    [155] = 143,
    [156] = 121,
    [157] = 143,
    [158] = 121,
    [159] = 143,
    [160] = 121,
    [161] = 143,
    [162] = 100,
    [163] = 143,
    [164] = 121,
    [165] = 104,
    [166] = 125,
    [167] = 143,
    [168] = 105,
    [169] = 125,
    [170] = 152,
    [171] = 117,
    [172] = 116,
    [173] = 105,
    [174] = 151,
    [175] = 143,
    [176] = 118,
    [177] = 116,
    [178] = 105,
    [179] = 143,
    [180] = 118,
    [181] = 143,
    [182] = 118,
    [183] = 143,
    [184] = 118,
    [185] = 143,
    [186] = 118,
    [187] = 143,
    [188] = 118,
    [189] = 143,
    [190] = 100,
    [191] = 143,
    [192] = 118,
    [193] = 104,
    [194] = 126,
    [195] = 143,
    [196] = 105,
    [197] = 126,
    [198] = 143,
    [199] = 119,
    [200] = 105,
    [201] = 143,
    [202] = 119,
    [203] = 143,
    [204] = 119,
    [205] = 143,
    [206] = 119,
    [207] = 143,
    [208] = 119,
    [209] = 143,
    [210] = 119,
    [211] = 143,
    [212] = 100,
    [213] = 143,
    [214] = 119,
    [215] = 104,
    [216] = 127,
    [217] = 143,
    [218] = 105,
    [219] = 127,
    [220] = 143,
    [221] = 105,
    [222] = 153,
    [223] = 121,
    [224] = 120,
    [225] = 105,
    [226] = 143,
    [227] = 121,
    [228] = 120,
    [229] = 121,
    [230] = 125,
    [231] = 143,
    [232] = 121,
    [233] = 157,
    [234] = 154,
    [235] = 121,
    [236] = 107,
    [237] = 112,
    [238] = 121,
    [239] = 159,
    [240] = 76,
    [241] = 107,
    [242] = 107,
    [243] = 152,
    [244] = 117,
    [245] = 116,
    [246] = 76,
    [247] = 151,
    [248] = 143,
    [249] = 118,
    [250] = 116,
    [251] = 76,
    [252] = 118,
    [253] = 126,
    [254] = 143,
    [255] = 118,
    [256] = 157,
    [257] = 154,
    [258] = 118,
    [259] = 107,
    [260] = 112,
    [261] = 118,
    [262] = 128,
    [263] = 107,
    [264] = 156,
    [265] = 179,
    [266] = 143,
    [267] = 143,
    [268] = 119,
    [269] = 173,
    [270] = 107,
    [271] = 128,
    [272] = 156,
    [273] = 143,
    [274] = 119,
    [275] = 173,
    [276] = 180,
    [277] = 173,
    [278] = 107,
    [279] = 156,
    [280] = 143,
    [281] = 119,
    [282] = 154,
    [283] = 161,
    [284] = 161,
    [285] = 143,
    [286] = 100,
    [287] = 130,
    [288] = 130,
    [289] = 130,
    [290] = 76,
    [291] = 130,
    [292] = 128,
    [293] = 143,
    [294] = 114,
    [295] = 109,
    [296] = 130,
    [297] = 143,
    [298] = 114,
    [299] = 143,
    [300] = 114,
    [301] = 143,
    [302] = 114,
    [303] = 143,
    [304] = 114,
    [305] = 143,
    [306] = 114,
    [307] = 143,
    [308] = 114,
    [309] = 143,
    [310] = 100,
    [311] = 143,
    [312] = 114,
    [313] = 104,
    [314] = 142,
    [315] = 143,
    [316] = 105,
    [317] = 142,
    [318] = 142,
    [319] = 157,
    [320] = 154,
    [321] = 114,
    [322] = 107,
    [323] = 112,
    [324] = 114,
    [325] = 143,
    [326] = 114,
    [327] = 76,
    [328] = 107,
    [329] = 142,
    [330] = 109,
    [331] = 152,
    [332] = 117,
    [333] = 116,
    [334] = 114,
    [335] = 151,
    [336] = 143,
    [337] = 118,
    [338] = 116,
    [339] = 114,
    [340] = 152,
    [341] = 117,
    [342] = 116,
    [343] = 118,
    [344] = 151,
    [345] = 143,
    [346] = 118,
    [347] = 116,
    [348] = 118,
    [349] = 143,
    [350] = 119,
    [351] = 118,
    [352] = 119,
    [353] = 127,
    [354] = 143,
    [355] = 119,
    [356] = 157,
    [357] = 154,
    [358] = 119,
    [359] = 107,
    [360] = 112,
    [361] = 119,
    [362] = 116,
    [363] = 107,
    [364] = 144,
    [365] = 107,
    [366] = 146,
    [367] = 148,
    [368] = 116,
    [369] = 76,
    [370] = 143,
    [371] = 119,
    [372] = 76,
    [373] = 152,
    [374] = 117,
    [375] = 116,
    [376] = 119,
    [377] = 151,
    [378] = 143,
    [379] = 118,
    [380] = 116,
    [381] = 119,
    [382] = 143,
    [383] = 118,
    [384] = 153,
    [385] = 121,
    [386] = 120,
    [387] = 118,
    [388] = 150,
    [389] = 152,
    [390] = 117,
    [391] = 116,
    [392] = 121,
    [393] = 151,
    [394] = 143,
    [395] = 118,
    [396] = 116,
    [397] = 121,
    [398] = 121,
    [399] = 143,
    [400] = 119,
    [401] = 121,
    [402] = 143,
    [403] = 119,
    [404] = 119,
    [405] = 143,
    [406] = 119,
    [407] = 153,
    [408] = 121,
    [409] = 120,
    [410] = 119,
    [411] = 150,
    [412] = 143,
    [413] = 121,
    [414] = 153,
    [415] = 121,
    [416] = 120,
    [417] = 121,
    [418] = 150,
    [419] = 121,
    [420] = 119,
    [421] = 118,
    [422] = 119,
    [423] = 143,
    [424] = 76,
    [425] = 153,
    [426] = 121,
    [427] = 120,
    [428] = 76,
    [429] = 150,
    [430] = 76,
    [431] = 156,
    [432] = 154,
    [433] = 119,
    [434] = 155,
    [435] = 115,
    [436] = 96,
    [437] = 154,
    [438] = 104,
    [439] = 115,
    [440] = 96,
    [441] = 154,
    [442] = 118,
    [443] = 114,
    [444] = 143,
    [445] = 119,
    [446] = 114,
    [447] = 143,
    [448] = 114,
    [449] = 153,
    [450] = 121,
    [451] = 120,
    [452] = 114,
    [453] = 150,
    [454] = 114,
    [455] = 116,
    [456] = 156,
    [457] = 154,
    [458] = 114,
    [459] = 143,
    [460] = 100,
    [461] = 143,
    [462] = 100,
    [463] = 143,
    [464] = 100,
    [465] = 143,
    [466] = 100,
    [467] = 143,
    [468] = 100,
    [469] = 143,
    [470] = 100,
    [471] = 143,
    [472] = 100,
    [473] = 104,
    [474] = 158,
    [475] = 143,
    [476] = 105,
    [477] = 158,
    [478] = 100,
    [479] = 158,
    [480] = 143,
    [481] = 100,
    [482] = 157,
    [483] = 154,
    [484] = 100,
    [485] = 107,
    [486] = 112,
    [487] = 100,
    [488] = 116,
    [489] = 156,
    [490] = 154,
    [491] = 100,
    [492] = 152,
    [493] = 117,
    [494] = 116,
    [495] = 100,
    [496] = 151,
    [497] = 143,
    [498] = 118,
    [499] = 116,
    [500] = 100,
    [501] = 100,
    [502] = 143,
    [503] = 119,
    [504] = 100,
    [505] = 143,
    [506] = 100,
    [507] = 153,
    [508] = 121,
    [509] = 120,
    [510] = 100,
    [511] = 150,
    [512] = 100,
    [513] = 159,
    [514] = 76,
    [515] = 130,
    [516] = 130,
    [517] = 128,
    [518] = 130,
    [519] = 156,
    [520] = 179,
    [521] = 143,
    [522] = 143,
    [523] = 119,
    [524] = 173,
    [525] = 130,
    [526] = 156,
    [527] = 143,
    [528] = 119,
    [529] = 173,
    [530] = 174,
    [531] = 173,
    [532] = 130,
    [533] = 156,
    [534] = 143,
    [535] = 119,
    [536] = 154,
    [537] = 161,
    [538] = 151,
    [539] = 130,
    [540] = 143,
    [541] = 76,
    [542] = 130,
    [543] = 109,
    [544] = 161,
    [545] = 107,
    [546] = 144,
    [547] = 130,
    [548] = 116,
    [549] = 116,
    [550] = 130,
    [551] = 96,
    [552] = 174,
    [553] = 76,
    [554] = 174,
    [555] = 128,
    [556] = 143,
    [557] = 109,
    [558] = 174,
    [559] = 159,
    [560] = 76,
    [561] = 174,
    [562] = 174,
    [563] = 128,
    [564] = 174,
    [565] = 156,
    [566] = 179,
    [567] = 143,
    [568] = 143,
    [569] = 119,
    [570] = 173,
    [571] = 174,
    [572] = 156,
    [573] = 143,
    [574] = 119,
    [575] = 173,
    [576] = 174,
    [577] = 173,
    [578] = 174,
    [579] = 156,
    [580] = 143,
    [581] = 119,
    [582] = 154,
    [583] = 161,
    [584] = 116,
    [585] = 174,
    [586] = 96,
    [587] = 143,
    [588] = 76,
    [589] = 174,
    [590] = 109,
    [591] = 107,
    [592] = 144,
    [593] = 174,
    [594] = 116,
    [595] = 96,
    [596] = 96,
    [597] = 76,
    [598] = 143,
    [599] = 128,
    [600] = 143,
    [601] = 76,
    [602] = 143,
    [603] = 109,
    [604] = 96,
    [605] = 96,
    [606] = 161,
    [607] = 161,
    [608] = 116,
    [609] = 116,
    [610] = 107,
    [611] = 96,
    [612] = 180,
    [613] = 76,
    [614] = 180,
    [615] = 128,
    [616] = 143,
    [617] = 109,
    [618] = 180,
    [619] = 159,
    [620] = 76,
    [621] = 180,
    [622] = 180,
    [623] = 128,
    [624] = 180,
    [625] = 156,
    [626] = 179,
    [627] = 143,
    [628] = 143,
    [629] = 119,
    [630] = 173,
    [631] = 180,
    [632] = 156,
    [633] = 143,
    [634] = 119,
    [635] = 173,
    [636] = 180,
    [637] = 173,
    [638] = 180,
    [639] = 156,
    [640] = 143,
    [641] = 119,
    [642] = 154,
    [643] = 161,
    [644] = 116,
    [645] = 180,
    [646] = 96,
    [647] = 143,
    [648] = 76,
    [649] = 180,
    [650] = 109,
    [651] = 107,
    [652] = 144,
    [653] = 180,
    [654] = 116,
    [655] = 96,
    [656] = 96,
    [657] = 96,
    [658] = 96,
    [659] = 116,
    [660] = 156,
    [661] = 154,
    [662] = 118,
    [663] = 116,
    [664] = 156,
    [665] = 154,
    [666] = 121,
    [667] = 150,
    [668] = 150,
    [669] = 105,
    [670] = 105,
    [671] = 150,
    [672] = 98,
    [673] = 98,
    [674] = 118,
    [675] = 151,
    [676] = 143,
    [677] = 118,
    [678] = 116,
    [679] = 98,
    [680] = 98,
    [681] = 114,
    [682] = 109,
    [683] = 107,
    [684] = 116,
    [685] = 156,
    [686] = 154,
    [687] = 76,
    [688] = 112,
    [689] = 105,
    [690] = 116,
    [691] = 156,
    [692] = 154,
    [693] = 105,
    [694] = 109,
    [695] = 116,
    [696] = 112,
    [697] = 98,
    [698] = 116,
    [699] = 156,
    [700] = 154,
    [701] = 98,
    [702] = 115,
    [703] = 105,
    [704] = 102,
    [705] = 115,
    [706] = 115,
    [707] = 100,
    [708] = 143,
    [709] = 98,
    [710] = 115,
    [711] = 98,
    [712] = 115,
    [713] = 76,
    [714] = 128,
    [715] = 143,
    [716] = 109,
    [717] = 2,
    [718] = 159,
    [719] = 76,
    [720] = 2,
    [721] = 2,
    [722] = 128,
    [723] = 2,
    [724] = 156,
    [725] = 179,
    [726] = 143,
    [727] = 143,
    [728] = 119,
    [729] = 173,
    [730] = 2,
    [731] = 156,
    [732] = 143,
    [733] = 119,
    [734] = 173,
    [735] = 182,
    [736] = 173,
    [737] = 2,
    [738] = 156,
    [739] = 143,
    [740] = 119,
    [741] = 154,
    [742] = 161,
    [743] = 116,
    [744] = 2,
    [745] = 96,
    [746] = 143,
    [747] = 76,
    [748] = 2,
    [749] = 109,
    [750] = 107,
    [751] = 144,
    [752] = 2,
    [753] = 116,
    [754] = 182,
    [755] = 76,
    [756] = 182,
    [757] = 128,
    [758] = 143,
    [759] = 109,
    [760] = 182,
    [761] = 159,
    [762] = 76,
    [763] = 182,
    [764] = 182,
    [765] = 128,
    [766] = 182,
    [767] = 156,
    [768] = 179,
    [769] = 143,
    [770] = 143,
    [771] = 119,
    [772] = 173,
    [773] = 182,
    [774] = 156,
    [775] = 143,
    [776] = 119,
    [777] = 173,
    [778] = 182,
    [779] = 173,
    [780] = 182,
    [781] = 156,
    [782] = 143,
    [783] = 119,
    [784] = 154,
    [785] = 161,
    [786] = 116,
    [787] = 182,
    [788] = 96,
    [789] = 143,
    [790] = 76,
    [791] = 182,
    [792] = 109,
    [793] = 107,
    [794] = 144,
    [795] = 182,
    [796] = 116,
    [797] = 96,
    [798] = 96,
    [799] = 96,
    [800] = 96,
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
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
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
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
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(712),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(710),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [25] = {
        [ts_aux_sym_token2] = SHIFT(26),
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
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
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
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(707),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(705),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [36] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(704),
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
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token3] = SHIFT(703),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
        [ts_aux_sym_token0] = SHIFT(115),
        [ts_aux_sym_token2] = SHIFT(131),
        [ts_aux_sym_token17] = SHIFT(139),
        [ts_aux_sym_token22] = SHIFT(141),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(696),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(271),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [55] = {
        [ts_sym_expression] = SHIFT(56),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [57] = {
        [ts_sym_expression] = SHIFT(58),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [59] = {
        [ts_sym_expression] = SHIFT(60),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [61] = {
        [ts_sym_expression] = SHIFT(62),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [62] = {
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [63] = {
        [ts_sym_expression] = SHIFT(64),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [64] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(65),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
    },
    [65] = {
        [ts_sym_expression] = SHIFT(66),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [66] = {
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
    },
    [67] = {
        [ts_sym_identifier] = SHIFT(68),
    },
    [68] = {
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
    [69] = {
        [ts_sym_expression] = SHIFT(70),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [70] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(694),
    },
    [71] = {
        [ts_sym_expression] = SHIFT(72),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [72] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [73] = {
        [ts_sym_expression] = SHIFT(74),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [74] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_math_op, 3),
    },
    [75] = {
        [ts_sym_expression] = SHIFT(76),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [76] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [77] = {
        [ts_sym_expression] = SHIFT(78),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [78] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [79] = {
        [ts_sym_expression] = SHIFT(80),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [80] = {
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
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [81] = {
        [ts_sym_expression] = SHIFT(82),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [82] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(83),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
    },
    [83] = {
        [ts_sym_expression] = SHIFT(84),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [84] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = REDUCE(ts_sym_ternary, 5),
    },
    [85] = {
        [ts_sym_identifier] = SHIFT(86),
    },
    [86] = {
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
    [87] = {
        [ts_sym_expression] = SHIFT(88),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [88] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(89),
    },
    [89] = {
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
        [ts_aux_sym_token19] = SHIFT(92),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
    },
    [92] = {
        [ts_sym_expression] = SHIFT(93),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [93] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = REDUCE(ts_sym_assignment, 3),
    },
    [94] = {
        [ts_sym_formal_parameters] = SHIFT(95),
        [ts_sym_identifier] = SHIFT(691),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [95] = {
        [ts_sym_statement_block] = SHIFT(96),
        [ts_aux_sym_token0] = SHIFT(97),
    },
    [96] = {
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
    [97] = {
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(688),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(690),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [98] = {
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
    [99] = {
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
        [ts_aux_sym_token19] = SHIFT(100),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [100] = {
        [ts_sym_expression] = SHIFT(101),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [101] = {
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(106),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(682),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [109] = {
        [ts_aux_sym_token2] = SHIFT(110),
        [ts_aux_sym_token5] = SHIFT(299),
        [ts_aux_sym_token6] = SHIFT(299),
        [ts_aux_sym_token7] = SHIFT(301),
        [ts_aux_sym_token8] = SHIFT(301),
        [ts_aux_sym_token9] = SHIFT(303),
        [ts_aux_sym_token10] = SHIFT(305),
        [ts_aux_sym_token11] = SHIFT(305),
        [ts_aux_sym_token12] = SHIFT(305),
        [ts_aux_sym_token13] = SHIFT(305),
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = SHIFT(305),
        [ts_aux_sym_token16] = SHIFT(305),
        [ts_aux_sym_token18] = SHIFT(309),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
    },
    [110] = {
        [ts_sym_expression] = SHIFT(111),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(114),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
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
        [ts_aux_sym_token20] = SHIFT(30),
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
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [124] = {
        [ts_aux_sym_object_repeat0] = SHIFT(125),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
    },
    [125] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 5),
    },
    [126] = {
        [ts_sym_expression] = SHIFT(127),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(130),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
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
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [131] = {
        [ts_sym_expression] = SHIFT(132),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [132] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(673),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [133] = {
        [ts_sym_expression] = SHIFT(134),
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(137),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
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
        [ts_aux_sym_token20] = SHIFT(30),
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
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [141] = {
        [ts_sym_expression] = SHIFT(142),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_builtin_sym_error] = SHIFT(671),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
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
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_builtin_sym_error] = SHIFT(149),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = SHIFT(30),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
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
        [ts_aux_sym_token20] = SHIFT(30),
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
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
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
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
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
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
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
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
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
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [160] = {
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 3),
    },
    [161] = {
        [ts_sym_expression] = SHIFT(162),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [162] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(163),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
    },
    [163] = {
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [164] = {
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = REDUCE(ts_sym_ternary, 5),
    },
    [165] = {
        [ts_sym_identifier] = SHIFT(166),
    },
    [166] = {
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
    [167] = {
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [168] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(169),
    },
    [169] = {
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
    [170] = {
        [ts_builtin_sym_error] = SHIFT(171),
        [ts_sym_string] = SHIFT(174),
        [ts_sym_identifier] = SHIFT(174),
        [ts_aux_sym_token1] = SHIFT(670),
    },
    [171] = {
        [ts_aux_sym_object_repeat0] = SHIFT(172),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [172] = {
        [ts_aux_sym_token1] = SHIFT(173),
    },
    [173] = {
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
    [174] = {
        [ts_aux_sym_token4] = SHIFT(175),
    },
    [175] = {
        [ts_sym_expression] = SHIFT(176),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [176] = {
        [ts_aux_sym_object_repeat0] = SHIFT(177),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
    },
    [177] = {
        [ts_aux_sym_token1] = SHIFT(178),
    },
    [178] = {
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
    [179] = {
        [ts_sym_expression] = SHIFT(180),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [180] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [181] = {
        [ts_sym_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [182] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [183] = {
        [ts_sym_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [184] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [185] = {
        [ts_sym_expression] = SHIFT(186),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [186] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [187] = {
        [ts_sym_expression] = SHIFT(188),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [188] = {
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
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [189] = {
        [ts_sym_expression] = SHIFT(190),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [190] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(191),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
    },
    [191] = {
        [ts_sym_expression] = SHIFT(192),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [192] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
    },
    [193] = {
        [ts_sym_identifier] = SHIFT(194),
    },
    [194] = {
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
    [195] = {
        [ts_sym_expression] = SHIFT(196),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [196] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(197),
    },
    [197] = {
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
    [198] = {
        [ts_sym_expression] = SHIFT(199),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [199] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(200),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [200] = {
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
    [201] = {
        [ts_sym_expression] = SHIFT(202),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [202] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [203] = {
        [ts_sym_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [204] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [205] = {
        [ts_sym_expression] = SHIFT(206),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [206] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [207] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [208] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [209] = {
        [ts_sym_expression] = SHIFT(210),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [210] = {
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
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [211] = {
        [ts_sym_expression] = SHIFT(212),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [212] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(213),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
    },
    [213] = {
        [ts_sym_expression] = SHIFT(214),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [214] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [215] = {
        [ts_sym_identifier] = SHIFT(216),
    },
    [216] = {
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
    [217] = {
        [ts_sym_expression] = SHIFT(218),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [218] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(219),
    },
    [219] = {
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
    [220] = {
        [ts_sym_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [221] = {
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
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token23] = REDUCE(ts_sym_bool_op, 2),
    },
    [222] = {
        [ts_sym_expression] = SHIFT(223),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_builtin_sym_error] = SHIFT(668),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
        [ts_aux_sym_token23] = SHIFT(669),
    },
    [223] = {
        [ts_aux_sym_array_repeat0] = SHIFT(224),
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [224] = {
        [ts_aux_sym_token23] = SHIFT(225),
    },
    [225] = {
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
    [226] = {
        [ts_sym_expression] = SHIFT(227),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_builtin_sym_error] = SHIFT(667),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [227] = {
        [ts_aux_sym_array_repeat0] = SHIFT(228),
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [228] = {
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 3),
    },
    [229] = {
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
    [230] = {
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
        [ts_aux_sym_token19] = SHIFT(231),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_expression, 1),
    },
    [231] = {
        [ts_sym_expression] = SHIFT(232),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
        [ts_aux_sym_token0] = SHIFT(389),
        [ts_aux_sym_token2] = SHIFT(399),
        [ts_aux_sym_token17] = SHIFT(412),
        [ts_aux_sym_token22] = SHIFT(414),
    },
    [232] = {
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = REDUCE(ts_sym_assignment, 3),
    },
    [233] = {
        [ts_sym_formal_parameters] = SHIFT(234),
        [ts_sym_identifier] = SHIFT(664),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [234] = {
        [ts_sym_statement_block] = SHIFT(235),
        [ts_aux_sym_token0] = SHIFT(236),
    },
    [235] = {
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
    [236] = {
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(237),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(663),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [237] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(238),
    },
    [238] = {
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
    [239] = {
        [ts_sym_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym__terminator] = SHIFT(242),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [240] = {
        [ts_sym__terminator] = SHIFT(241),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
    },
    [241] = {
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 3),
    },
    [242] = {
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_return_statement, 2),
    },
    [243] = {
        [ts_builtin_sym_error] = SHIFT(244),
        [ts_sym_string] = SHIFT(247),
        [ts_sym_identifier] = SHIFT(247),
        [ts_aux_sym_token1] = SHIFT(369),
    },
    [244] = {
        [ts_aux_sym_object_repeat0] = SHIFT(245),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [245] = {
        [ts_aux_sym_token1] = SHIFT(246),
    },
    [246] = {
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
    [247] = {
        [ts_aux_sym_token4] = SHIFT(248),
    },
    [248] = {
        [ts_sym_expression] = SHIFT(249),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [249] = {
        [ts_aux_sym_object_repeat0] = SHIFT(250),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
    },
    [250] = {
        [ts_aux_sym_token1] = SHIFT(251),
    },
    [251] = {
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
        [ts_aux_sym_token19] = SHIFT(254),
        [ts_aux_sym_token20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [254] = {
        [ts_sym_expression] = SHIFT(255),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [255] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
    },
    [256] = {
        [ts_sym_formal_parameters] = SHIFT(257),
        [ts_sym_identifier] = SHIFT(660),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [257] = {
        [ts_sym_statement_block] = SHIFT(258),
        [ts_aux_sym_token0] = SHIFT(259),
    },
    [258] = {
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
    [259] = {
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(260),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(659),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [260] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(261),
    },
    [261] = {
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
    [262] = {
        [ts_sym__terminator] = SHIFT(263),
    },
    [263] = {
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
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_break_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_break_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_break_statement, 2),
    },
    [264] = {
        [ts_aux_sym_token2] = SHIFT(265),
    },
    [265] = {
        [ts_sym_var_declaration] = SHIFT(266),
        [ts_sym_expression_statement] = SHIFT(266),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [266] = {
        [ts_sym_expression_statement] = SHIFT(267),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [267] = {
        [ts_sym_expression] = SHIFT(268),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(658),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [268] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(269),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [269] = {
        [ts_sym_statement] = SHIFT(270),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(271),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [270] = {
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
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_for_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_for_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_for_statement, 7),
    },
    [271] = {
        [ts_sym__terminator] = SHIFT(52),
    },
    [272] = {
        [ts_aux_sym_token2] = SHIFT(273),
    },
    [273] = {
        [ts_sym_expression] = SHIFT(274),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(657),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [274] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(275),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [275] = {
        [ts_sym_statement] = SHIFT(276),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(615),
        [ts_sym__delete] = SHIFT(616),
        [ts_sym__return] = SHIFT(619),
        [ts_sym__break] = SHIFT(623),
        [ts_sym__for] = SHIFT(625),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(632),
        [ts_sym__switch] = SHIFT(639),
        [ts_sym__var] = SHIFT(647),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(612),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(651),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [276] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__delete] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__return] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__break] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__else] = SHIFT(277),
        [ts_sym__for] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__function] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__if] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__switch] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__var] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_null] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_true] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_false] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 5),
    },
    [277] = {
        [ts_sym_statement] = SHIFT(278),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(271),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [278] = {
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_identifier] = REDUCE(ts_sym_if_statement, 7),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token0] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token2] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token17] = REDUCE(ts_sym_if_statement, 7),
        [ts_aux_sym_token22] = REDUCE(ts_sym_if_statement, 7),
    },
    [279] = {
        [ts_aux_sym_token2] = SHIFT(280),
    },
    [280] = {
        [ts_sym_expression] = SHIFT(281),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(611),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [281] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(282),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [282] = {
        [ts_aux_sym_token0] = SHIFT(283),
    },
    [283] = {
        [ts_sym_switch_case] = SHIFT(284),
        [ts_sym__case] = SHIFT(285),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(609),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [284] = {
        [ts_sym_switch_case] = SHIFT(284),
        [ts_sym__case] = SHIFT(285),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(608),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [285] = {
        [ts_sym_expression] = SHIFT(286),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [286] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(287),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
    },
    [287] = {
        [ts_sym_statement] = SHIFT(288),
        [ts_sym_statement_block] = SHIFT(289),
        [ts_sym_for_statement] = SHIFT(289),
        [ts_sym_if_statement] = SHIFT(289),
        [ts_sym_switch_statement] = SHIFT(289),
        [ts_sym_break_statement] = SHIFT(289),
        [ts_sym_var_declaration] = SHIFT(289),
        [ts_sym_expression_statement] = SHIFT(289),
        [ts_sym_return_statement] = SHIFT(289),
        [ts_sym_delete_statement] = SHIFT(289),
        [ts_sym_expression] = SHIFT(290),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(292),
        [ts_sym__delete] = SHIFT(293),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(289),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(607),
        [ts_aux_sym_token0] = SHIFT(545),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [288] = {
        [ts_sym_statement] = SHIFT(288),
        [ts_sym_statement_block] = SHIFT(289),
        [ts_sym_for_statement] = SHIFT(289),
        [ts_sym_if_statement] = SHIFT(289),
        [ts_sym_switch_statement] = SHIFT(289),
        [ts_sym_break_statement] = SHIFT(289),
        [ts_sym_var_declaration] = SHIFT(289),
        [ts_sym_expression_statement] = SHIFT(289),
        [ts_sym_return_statement] = SHIFT(289),
        [ts_sym_delete_statement] = SHIFT(289),
        [ts_sym_expression] = SHIFT(290),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(292),
        [ts_sym__delete] = SHIFT(293),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(289),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(606),
        [ts_aux_sym_token0] = SHIFT(545),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [289] = {
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
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym_identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_statement, 1),
    },
    [290] = {
        [ts_sym__terminator] = SHIFT(291),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
    },
    [291] = {
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
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token0] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression_statement, 2),
    },
    [292] = {
        [ts_sym__terminator] = SHIFT(291),
    },
    [293] = {
        [ts_sym_expression] = SHIFT(109),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(295),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [294] = {
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
    [295] = {
        [ts_sym__terminator] = SHIFT(296),
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
        [ts_aux_sym_token19] = SHIFT(297),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [296] = {
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
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_string] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_delete_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_delete_statement, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_delete_statement, 3),
    },
    [297] = {
        [ts_sym_expression] = SHIFT(298),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(318),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [298] = {
        [ts_aux_sym_token2] = SHIFT(110),
        [ts_aux_sym_token5] = SHIFT(299),
        [ts_aux_sym_token6] = SHIFT(299),
        [ts_aux_sym_token7] = SHIFT(301),
        [ts_aux_sym_token8] = SHIFT(301),
        [ts_aux_sym_token9] = SHIFT(303),
        [ts_aux_sym_token10] = SHIFT(305),
        [ts_aux_sym_token11] = SHIFT(305),
        [ts_aux_sym_token12] = SHIFT(305),
        [ts_aux_sym_token13] = SHIFT(305),
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = SHIFT(305),
        [ts_aux_sym_token16] = SHIFT(305),
        [ts_aux_sym_token18] = SHIFT(309),
        [ts_aux_sym_token21] = SHIFT(313),
        [ts_aux_sym_token22] = SHIFT(315),
    },
    [299] = {
        [ts_sym_expression] = SHIFT(300),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(318),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [300] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(299),
        [ts_aux_sym_token6] = SHIFT(299),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token9] = SHIFT(303),
        [ts_aux_sym_token10] = SHIFT(305),
        [ts_aux_sym_token11] = SHIFT(305),
        [ts_aux_sym_token12] = SHIFT(305),
        [ts_aux_sym_token13] = SHIFT(305),
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = SHIFT(305),
        [ts_aux_sym_token16] = SHIFT(305),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [301] = {
        [ts_sym_expression] = SHIFT(302),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(318),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [302] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(299),
        [ts_aux_sym_token6] = SHIFT(299),
        [ts_aux_sym_token7] = SHIFT(301),
        [ts_aux_sym_token8] = SHIFT(301),
        [ts_aux_sym_token9] = SHIFT(303),
        [ts_aux_sym_token10] = SHIFT(305),
        [ts_aux_sym_token11] = SHIFT(305),
        [ts_aux_sym_token12] = SHIFT(305),
        [ts_aux_sym_token13] = SHIFT(305),
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = SHIFT(305),
        [ts_aux_sym_token16] = SHIFT(305),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [303] = {
        [ts_sym_expression] = SHIFT(304),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(318),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [304] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(303),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [305] = {
        [ts_sym_expression] = SHIFT(306),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(318),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [306] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(299),
        [ts_aux_sym_token6] = SHIFT(299),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = SHIFT(303),
        [ts_aux_sym_token10] = SHIFT(305),
        [ts_aux_sym_token11] = SHIFT(305),
        [ts_aux_sym_token12] = SHIFT(305),
        [ts_aux_sym_token13] = SHIFT(305),
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = SHIFT(305),
        [ts_aux_sym_token16] = SHIFT(305),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [307] = {
        [ts_sym_expression] = SHIFT(308),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(318),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [308] = {
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
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [309] = {
        [ts_sym_expression] = SHIFT(310),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [310] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(311),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
    },
    [311] = {
        [ts_sym_expression] = SHIFT(312),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(318),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [312] = {
        [ts_aux_sym_token2] = SHIFT(110),
        [ts_aux_sym_token5] = SHIFT(299),
        [ts_aux_sym_token6] = SHIFT(299),
        [ts_aux_sym_token7] = SHIFT(301),
        [ts_aux_sym_token8] = SHIFT(301),
        [ts_aux_sym_token9] = SHIFT(303),
        [ts_aux_sym_token10] = SHIFT(305),
        [ts_aux_sym_token11] = SHIFT(305),
        [ts_aux_sym_token12] = SHIFT(305),
        [ts_aux_sym_token13] = SHIFT(305),
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = SHIFT(305),
        [ts_aux_sym_token16] = SHIFT(305),
        [ts_aux_sym_token18] = SHIFT(309),
        [ts_aux_sym_token21] = SHIFT(313),
        [ts_aux_sym_token22] = SHIFT(315),
    },
    [313] = {
        [ts_sym_identifier] = SHIFT(314),
    },
    [314] = {
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
    [315] = {
        [ts_sym_expression] = SHIFT(316),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [316] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(317),
    },
    [317] = {
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
    [318] = {
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
        [ts_aux_sym_token19] = SHIFT(297),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [319] = {
        [ts_sym_formal_parameters] = SHIFT(320),
        [ts_sym_identifier] = SHIFT(456),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [320] = {
        [ts_sym_statement_block] = SHIFT(321),
        [ts_aux_sym_token0] = SHIFT(322),
    },
    [321] = {
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
    [322] = {
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(323),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(455),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_statement_block_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [323] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_token1] = SHIFT(324),
    },
    [324] = {
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
    [325] = {
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(327),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(329),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(330),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
        [ts_aux_sym_token2] = SHIFT(444),
        [ts_aux_sym_token17] = SHIFT(447),
        [ts_aux_sym_token22] = SHIFT(449),
    },
    [326] = {
        [ts_aux_sym_token2] = SHIFT(110),
        [ts_aux_sym_token5] = SHIFT(299),
        [ts_aux_sym_token6] = SHIFT(299),
        [ts_aux_sym_token7] = SHIFT(301),
        [ts_aux_sym_token8] = SHIFT(301),
        [ts_aux_sym_token9] = SHIFT(303),
        [ts_aux_sym_token10] = SHIFT(305),
        [ts_aux_sym_token11] = SHIFT(305),
        [ts_aux_sym_token12] = SHIFT(305),
        [ts_aux_sym_token13] = SHIFT(305),
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = SHIFT(305),
        [ts_aux_sym_token16] = SHIFT(305),
        [ts_aux_sym_token18] = SHIFT(309),
        [ts_aux_sym_token21] = SHIFT(313),
        [ts_aux_sym_token22] = SHIFT(315),
    },
    [327] = {
        [ts_sym__terminator] = SHIFT(328),
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
    [328] = {
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
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_identifier] = REDUCE(ts_sym_var_declaration, 3),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_declaration, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_var_declaration, 3),
    },
    [329] = {
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
        [ts_aux_sym_token19] = SHIFT(100),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [330] = {
        [ts_sym__terminator] = SHIFT(328),
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
        [ts_aux_sym_token19] = SHIFT(100),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [331] = {
        [ts_builtin_sym_error] = SHIFT(332),
        [ts_sym_string] = SHIFT(335),
        [ts_sym_identifier] = SHIFT(335),
        [ts_aux_sym_token1] = SHIFT(443),
    },
    [332] = {
        [ts_aux_sym_object_repeat0] = SHIFT(333),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [333] = {
        [ts_aux_sym_token1] = SHIFT(334),
    },
    [334] = {
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
    [335] = {
        [ts_aux_sym_token4] = SHIFT(336),
    },
    [336] = {
        [ts_sym_expression] = SHIFT(337),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [337] = {
        [ts_aux_sym_object_repeat0] = SHIFT(338),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
    },
    [338] = {
        [ts_aux_sym_token1] = SHIFT(339),
    },
    [339] = {
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
    [340] = {
        [ts_builtin_sym_error] = SHIFT(341),
        [ts_sym_string] = SHIFT(344),
        [ts_sym_identifier] = SHIFT(344),
        [ts_aux_sym_token1] = SHIFT(442),
    },
    [341] = {
        [ts_aux_sym_object_repeat0] = SHIFT(342),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(119),
    },
    [342] = {
        [ts_aux_sym_token1] = SHIFT(343),
    },
    [343] = {
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
    [344] = {
        [ts_aux_sym_token4] = SHIFT(345),
    },
    [345] = {
        [ts_sym_expression] = SHIFT(346),
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [346] = {
        [ts_aux_sym_object_repeat0] = SHIFT(347),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
    },
    [347] = {
        [ts_aux_sym_token1] = SHIFT(348),
    },
    [348] = {
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
    [349] = {
        [ts_sym_expression] = SHIFT(350),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [350] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(351),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [351] = {
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
    [352] = {
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
    [353] = {
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
        [ts_aux_sym_token19] = SHIFT(354),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [354] = {
        [ts_sym_expression] = SHIFT(355),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [355] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = REDUCE(ts_sym_assignment, 3),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(360),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(364),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(368),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [364] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(245),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = SHIFT(248),
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
    [367] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = SHIFT(248),
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
        [ts_aux_sym_token19] = SHIFT(100),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [371] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(372),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [379] = {
        [ts_aux_sym_object_repeat0] = SHIFT(380),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
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
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
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
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [384] = {
        [ts_sym_expression] = SHIFT(385),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_builtin_sym_error] = SHIFT(388),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
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
        [ts_aux_sym_token20] = SHIFT(226),
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
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [395] = {
        [ts_aux_sym_object_repeat0] = SHIFT(396),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [400] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(401),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [403] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(404),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
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
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [407] = {
        [ts_sym_expression] = SHIFT(408),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_builtin_sym_error] = SHIFT(411),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
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
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [412] = {
        [ts_sym_expression] = SHIFT(413),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
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
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_builtin_sym_error] = SHIFT(418),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
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
        [ts_aux_sym_token20] = SHIFT(226),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [425] = {
        [ts_sym_expression] = SHIFT(426),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_builtin_sym_error] = SHIFT(429),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
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
        [ts_aux_sym_token20] = SHIFT(226),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [445] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(446),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(318),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_aux_sym_token14] = SHIFT(307),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [449] = {
        [ts_sym_expression] = SHIFT(450),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_builtin_sym_error] = SHIFT(453),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
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
        [ts_aux_sym_token20] = SHIFT(226),
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
        [ts_aux_sym_token1] = SHIFT(324),
    },
    [456] = {
        [ts_sym_formal_parameters] = SHIFT(457),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [457] = {
        [ts_sym_statement_block] = SHIFT(458),
        [ts_aux_sym_token0] = SHIFT(322),
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
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
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
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [461] = {
        [ts_sym_expression] = SHIFT(462),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
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
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_math_op, 3),
    },
    [463] = {
        [ts_sym_expression] = SHIFT(464),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
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
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [465] = {
        [ts_sym_expression] = SHIFT(466),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
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
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [467] = {
        [ts_sym_expression] = SHIFT(468),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [468] = {
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
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 3),
    },
    [469] = {
        [ts_sym_expression] = SHIFT(470),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [470] = {
        [ts_aux_sym_token2] = SHIFT(26),
        [ts_aux_sym_token4] = SHIFT(471),
        [ts_aux_sym_token5] = SHIFT(459),
        [ts_aux_sym_token6] = SHIFT(459),
        [ts_aux_sym_token7] = SHIFT(461),
        [ts_aux_sym_token8] = SHIFT(461),
        [ts_aux_sym_token9] = SHIFT(463),
        [ts_aux_sym_token10] = SHIFT(465),
        [ts_aux_sym_token11] = SHIFT(465),
        [ts_aux_sym_token12] = SHIFT(465),
        [ts_aux_sym_token13] = SHIFT(465),
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
    },
    [471] = {
        [ts_sym_expression] = SHIFT(472),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [472] = {
        [ts_aux_sym_token2] = SHIFT(26),
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
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
    },
    [473] = {
        [ts_sym_identifier] = SHIFT(474),
    },
    [474] = {
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
    [475] = {
        [ts_sym_expression] = SHIFT(476),
        [ts_sym_math_op] = SHIFT(90),
        [ts_sym_bool_op] = SHIFT(90),
        [ts_sym_ternary] = SHIFT(90),
        [ts_sym_assignment] = SHIFT(90),
        [ts_sym_function_expression] = SHIFT(90),
        [ts_sym_function_call] = SHIFT(90),
        [ts_sym_property_access] = SHIFT(91),
        [ts_sym_object] = SHIFT(90),
        [ts_sym_array] = SHIFT(90),
        [ts_sym__function] = SHIFT(94),
        [ts_sym_null] = SHIFT(90),
        [ts_sym_true] = SHIFT(90),
        [ts_sym_false] = SHIFT(90),
        [ts_sym_regex] = SHIFT(90),
        [ts_sym_string] = SHIFT(90),
        [ts_sym_identifier] = SHIFT(91),
        [ts_sym_number] = SHIFT(90),
        [ts_aux_sym_token0] = SHIFT(170),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token17] = SHIFT(220),
        [ts_aux_sym_token22] = SHIFT(222),
    },
    [476] = {
        [ts_aux_sym_token2] = SHIFT(37),
        [ts_aux_sym_token5] = SHIFT(71),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
        [ts_aux_sym_token8] = SHIFT(73),
        [ts_aux_sym_token9] = SHIFT(75),
        [ts_aux_sym_token10] = SHIFT(77),
        [ts_aux_sym_token11] = SHIFT(77),
        [ts_aux_sym_token12] = SHIFT(77),
        [ts_aux_sym_token13] = SHIFT(77),
        [ts_aux_sym_token14] = SHIFT(79),
        [ts_aux_sym_token15] = SHIFT(77),
        [ts_aux_sym_token16] = SHIFT(77),
        [ts_aux_sym_token18] = SHIFT(81),
        [ts_aux_sym_token21] = SHIFT(85),
        [ts_aux_sym_token22] = SHIFT(87),
        [ts_aux_sym_token23] = SHIFT(477),
    },
    [477] = {
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
    [478] = {
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
    [479] = {
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
        [ts_aux_sym_token19] = SHIFT(480),
        [ts_aux_sym_token21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_expression, 1),
    },
    [480] = {
        [ts_sym_expression] = SHIFT(481),
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
        [ts_aux_sym_token0] = SHIFT(492),
        [ts_aux_sym_token2] = SHIFT(502),
        [ts_aux_sym_token17] = SHIFT(505),
        [ts_aux_sym_token22] = SHIFT(507),
    },
    [481] = {
        [ts_aux_sym_token2] = SHIFT(26),
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
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = SHIFT(465),
        [ts_aux_sym_token16] = SHIFT(465),
        [ts_aux_sym_token18] = SHIFT(469),
        [ts_aux_sym_token21] = SHIFT(473),
        [ts_aux_sym_token22] = SHIFT(475),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(486),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [498] = {
        [ts_aux_sym_object_repeat0] = SHIFT(499),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [503] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(504),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(478),
        [ts_sym_bool_op] = SHIFT(478),
        [ts_sym_ternary] = SHIFT(478),
        [ts_sym_assignment] = SHIFT(478),
        [ts_sym_function_expression] = SHIFT(478),
        [ts_sym_function_call] = SHIFT(478),
        [ts_sym_property_access] = SHIFT(479),
        [ts_sym_object] = SHIFT(478),
        [ts_sym_array] = SHIFT(478),
        [ts_sym__function] = SHIFT(482),
        [ts_sym_null] = SHIFT(478),
        [ts_sym_true] = SHIFT(478),
        [ts_sym_false] = SHIFT(478),
        [ts_sym_regex] = SHIFT(478),
        [ts_sym_string] = SHIFT(478),
        [ts_sym_identifier] = SHIFT(479),
        [ts_sym_number] = SHIFT(478),
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
        [ts_aux_sym_token14] = SHIFT(467),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token22] = REDUCE(ts_sym_bool_op, 2),
    },
    [507] = {
        [ts_sym_expression] = SHIFT(508),
        [ts_sym_math_op] = SHIFT(229),
        [ts_sym_bool_op] = SHIFT(229),
        [ts_sym_ternary] = SHIFT(229),
        [ts_sym_assignment] = SHIFT(229),
        [ts_sym_function_expression] = SHIFT(229),
        [ts_sym_function_call] = SHIFT(229),
        [ts_sym_property_access] = SHIFT(230),
        [ts_sym_object] = SHIFT(229),
        [ts_sym_array] = SHIFT(229),
        [ts_builtin_sym_error] = SHIFT(511),
        [ts_sym__function] = SHIFT(233),
        [ts_sym_null] = SHIFT(229),
        [ts_sym_true] = SHIFT(229),
        [ts_sym_false] = SHIFT(229),
        [ts_sym_regex] = SHIFT(229),
        [ts_sym_string] = SHIFT(229),
        [ts_sym_identifier] = SHIFT(230),
        [ts_sym_number] = SHIFT(229),
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
        [ts_aux_sym_token14] = SHIFT(159),
        [ts_aux_sym_token15] = SHIFT(157),
        [ts_aux_sym_token16] = SHIFT(157),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token21] = SHIFT(165),
        [ts_aux_sym_token22] = SHIFT(167),
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
        [ts_aux_sym_token20] = SHIFT(226),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym__terminator] = SHIFT(516),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
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
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [521] = {
        [ts_sym_expression_statement] = SHIFT(522),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [522] = {
        [ts_sym_expression] = SHIFT(523),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(605),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [523] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(524),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [524] = {
        [ts_sym_statement] = SHIFT(525),
        [ts_sym_statement_block] = SHIFT(289),
        [ts_sym_for_statement] = SHIFT(289),
        [ts_sym_if_statement] = SHIFT(289),
        [ts_sym_switch_statement] = SHIFT(289),
        [ts_sym_break_statement] = SHIFT(289),
        [ts_sym_var_declaration] = SHIFT(289),
        [ts_sym_expression_statement] = SHIFT(289),
        [ts_sym_return_statement] = SHIFT(289),
        [ts_sym_delete_statement] = SHIFT(289),
        [ts_sym_expression] = SHIFT(290),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(292),
        [ts_sym__delete] = SHIFT(293),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(289),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(604),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [528] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(529),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(555),
        [ts_sym__delete] = SHIFT(556),
        [ts_sym__return] = SHIFT(559),
        [ts_sym__break] = SHIFT(563),
        [ts_sym__for] = SHIFT(565),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(572),
        [ts_sym__switch] = SHIFT(579),
        [ts_sym__var] = SHIFT(587),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(552),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
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
        [ts_sym_statement_block] = SHIFT(289),
        [ts_sym_for_statement] = SHIFT(289),
        [ts_sym_if_statement] = SHIFT(289),
        [ts_sym_switch_statement] = SHIFT(289),
        [ts_sym_break_statement] = SHIFT(289),
        [ts_sym_var_declaration] = SHIFT(289),
        [ts_sym_expression_statement] = SHIFT(289),
        [ts_sym_return_statement] = SHIFT(289),
        [ts_sym_delete_statement] = SHIFT(289),
        [ts_sym_expression] = SHIFT(290),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(292),
        [ts_sym__delete] = SHIFT(293),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(289),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(551),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [535] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(536),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [536] = {
        [ts_aux_sym_token0] = SHIFT(537),
    },
    [537] = {
        [ts_sym_switch_case] = SHIFT(284),
        [ts_sym__case] = SHIFT(285),
        [ts_sym__default] = SHIFT(538),
        [ts_aux_sym_switch_statement_repeat0] = SHIFT(549),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_statement_repeat0, 0),
    },
    [538] = {
        [ts_aux_sym_token4] = SHIFT(539),
    },
    [539] = {
        [ts_sym_statement] = SHIFT(288),
        [ts_sym_statement_block] = SHIFT(289),
        [ts_sym_for_statement] = SHIFT(289),
        [ts_sym_if_statement] = SHIFT(289),
        [ts_sym_switch_statement] = SHIFT(289),
        [ts_sym_break_statement] = SHIFT(289),
        [ts_sym_var_declaration] = SHIFT(289),
        [ts_sym_expression_statement] = SHIFT(289),
        [ts_sym_return_statement] = SHIFT(289),
        [ts_sym_delete_statement] = SHIFT(289),
        [ts_sym_expression] = SHIFT(290),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(292),
        [ts_sym__delete] = SHIFT(293),
        [ts_sym__return] = SHIFT(513),
        [ts_sym__break] = SHIFT(517),
        [ts_sym__case] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__default] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_sym__for] = SHIFT(519),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(526),
        [ts_sym__switch] = SHIFT(533),
        [ts_sym__var] = SHIFT(540),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(289),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_switch_case_repeat0] = SHIFT(544),
        [ts_aux_sym_token0] = SHIFT(545),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_switch_case_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [540] = {
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(541),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(329),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(543),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token19] = SHIFT(100),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(546),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(548),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [546] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(245),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(557),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_aux_sym_token19] = SHIFT(297),
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
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym__terminator] = SHIFT(562),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
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
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [567] = {
        [ts_sym_expression_statement] = SHIFT(568),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [568] = {
        [ts_sym_expression] = SHIFT(569),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(596),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [569] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(570),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(555),
        [ts_sym__delete] = SHIFT(556),
        [ts_sym__return] = SHIFT(559),
        [ts_sym__break] = SHIFT(563),
        [ts_sym__for] = SHIFT(565),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(572),
        [ts_sym__switch] = SHIFT(579),
        [ts_sym__var] = SHIFT(587),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(552),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(595),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [574] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(575),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(555),
        [ts_sym__delete] = SHIFT(556),
        [ts_sym__return] = SHIFT(559),
        [ts_sym__break] = SHIFT(563),
        [ts_sym__for] = SHIFT(565),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(572),
        [ts_sym__switch] = SHIFT(579),
        [ts_sym__var] = SHIFT(587),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(552),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(555),
        [ts_sym__delete] = SHIFT(556),
        [ts_sym__return] = SHIFT(559),
        [ts_sym__break] = SHIFT(563),
        [ts_sym__for] = SHIFT(565),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(572),
        [ts_sym__switch] = SHIFT(579),
        [ts_sym__var] = SHIFT(587),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(552),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(586),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [581] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(582),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [582] = {
        [ts_aux_sym_token0] = SHIFT(583),
    },
    [583] = {
        [ts_sym_switch_case] = SHIFT(284),
        [ts_sym__case] = SHIFT(285),
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
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(588),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(329),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(590),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token19] = SHIFT(100),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(592),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(594),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [592] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(245),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
    },
    [598] = {
        [ts_builtin_sym_error] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__function] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_null] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_true] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_false] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(601),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(329),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(603),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token19] = SHIFT(100),
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
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_aux_sym_token3] = SHIFT(282),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(617),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_aux_sym_token19] = SHIFT(297),
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
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym__terminator] = SHIFT(622),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
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
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [627] = {
        [ts_sym_expression_statement] = SHIFT(628),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [628] = {
        [ts_sym_expression] = SHIFT(629),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(656),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [629] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(630),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(615),
        [ts_sym__delete] = SHIFT(616),
        [ts_sym__return] = SHIFT(619),
        [ts_sym__break] = SHIFT(623),
        [ts_sym__for] = SHIFT(625),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(632),
        [ts_sym__switch] = SHIFT(639),
        [ts_sym__var] = SHIFT(647),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(612),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(655),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [634] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(635),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(615),
        [ts_sym__delete] = SHIFT(616),
        [ts_sym__return] = SHIFT(619),
        [ts_sym__break] = SHIFT(623),
        [ts_sym__for] = SHIFT(625),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(632),
        [ts_sym__switch] = SHIFT(639),
        [ts_sym__var] = SHIFT(647),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(612),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(615),
        [ts_sym__delete] = SHIFT(616),
        [ts_sym__return] = SHIFT(619),
        [ts_sym__break] = SHIFT(623),
        [ts_sym__for] = SHIFT(625),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(632),
        [ts_sym__switch] = SHIFT(639),
        [ts_sym__var] = SHIFT(647),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(612),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(646),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [641] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(642),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [642] = {
        [ts_aux_sym_token0] = SHIFT(643),
    },
    [643] = {
        [ts_sym_switch_case] = SHIFT(284),
        [ts_sym__case] = SHIFT(285),
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
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(648),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(329),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(650),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token19] = SHIFT(100),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(652),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(654),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [652] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(245),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_aux_sym_token3] = SHIFT(275),
    },
    [658] = {
        [ts_aux_sym_token3] = SHIFT(269),
    },
    [659] = {
        [ts_aux_sym_token1] = SHIFT(261),
    },
    [660] = {
        [ts_sym_formal_parameters] = SHIFT(661),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [661] = {
        [ts_sym_statement_block] = SHIFT(662),
        [ts_aux_sym_token0] = SHIFT(259),
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
        [ts_aux_sym_token1] = SHIFT(238),
    },
    [664] = {
        [ts_sym_formal_parameters] = SHIFT(665),
        [ts_aux_sym_token2] = SHIFT(434),
    },
    [665] = {
        [ts_sym_statement_block] = SHIFT(666),
        [ts_aux_sym_token0] = SHIFT(236),
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
        [ts_aux_sym_array_repeat0] = SHIFT(228),
        [ts_aux_sym_token20] = SHIFT(226),
        [ts_aux_sym_token23] = REDUCE(ts_aux_sym_array_repeat0, 0),
    },
    [668] = {
        [ts_aux_sym_array_repeat0] = SHIFT(224),
        [ts_aux_sym_token20] = SHIFT(226),
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
        [ts_aux_sym_token20] = SHIFT(226),
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
        [ts_sym_math_op] = SHIFT(252),
        [ts_sym_bool_op] = SHIFT(252),
        [ts_sym_ternary] = SHIFT(252),
        [ts_sym_assignment] = SHIFT(252),
        [ts_sym_function_expression] = SHIFT(252),
        [ts_sym_function_call] = SHIFT(252),
        [ts_sym_property_access] = SHIFT(253),
        [ts_sym_object] = SHIFT(252),
        [ts_sym_array] = SHIFT(252),
        [ts_sym__function] = SHIFT(256),
        [ts_sym_null] = SHIFT(252),
        [ts_sym_true] = SHIFT(252),
        [ts_sym_false] = SHIFT(252),
        [ts_sym_regex] = SHIFT(252),
        [ts_sym_string] = SHIFT(252),
        [ts_sym_identifier] = SHIFT(253),
        [ts_sym_number] = SHIFT(252),
        [ts_aux_sym_token0] = SHIFT(340),
        [ts_aux_sym_token2] = SHIFT(349),
        [ts_aux_sym_token17] = SHIFT(382),
        [ts_aux_sym_token22] = SHIFT(384),
    },
    [677] = {
        [ts_aux_sym_object_repeat0] = SHIFT(678),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_object_repeat0, 0),
        [ts_aux_sym_token2] = SHIFT(126),
        [ts_aux_sym_token5] = SHIFT(179),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
        [ts_aux_sym_token8] = SHIFT(181),
        [ts_aux_sym_token9] = SHIFT(183),
        [ts_aux_sym_token10] = SHIFT(185),
        [ts_aux_sym_token11] = SHIFT(185),
        [ts_aux_sym_token12] = SHIFT(185),
        [ts_aux_sym_token13] = SHIFT(185),
        [ts_aux_sym_token14] = SHIFT(187),
        [ts_aux_sym_token15] = SHIFT(185),
        [ts_aux_sym_token16] = SHIFT(185),
        [ts_aux_sym_token18] = SHIFT(189),
        [ts_aux_sym_token20] = SHIFT(119),
        [ts_aux_sym_token21] = SHIFT(193),
        [ts_aux_sym_token22] = SHIFT(195),
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
        [ts_aux_sym_token19] = SHIFT(297),
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
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
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
        [ts_aux_sym_token0] = SHIFT(97),
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
        [ts_aux_sym_function_call_repeat0] = SHIFT(39),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
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
        [ts_aux_sym_function_call_repeat0] = SHIFT(32),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
    },
    [706] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(28),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
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
        [ts_sym_math_op] = SHIFT(41),
        [ts_sym_bool_op] = SHIFT(41),
        [ts_sym_ternary] = SHIFT(41),
        [ts_sym_assignment] = SHIFT(41),
        [ts_sym_function_expression] = SHIFT(41),
        [ts_sym_function_call] = SHIFT(41),
        [ts_sym_property_access] = SHIFT(42),
        [ts_sym_object] = SHIFT(41),
        [ts_sym_array] = SHIFT(41),
        [ts_sym__function] = SHIFT(45),
        [ts_sym_null] = SHIFT(41),
        [ts_sym_true] = SHIFT(41),
        [ts_sym_false] = SHIFT(41),
        [ts_sym_regex] = SHIFT(41),
        [ts_sym_string] = SHIFT(41),
        [ts_sym_identifier] = SHIFT(42),
        [ts_sym_number] = SHIFT(41),
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
        [ts_aux_sym_token14] = SHIFT(22),
        [ts_aux_sym_token15] = SHIFT(20),
        [ts_aux_sym_token16] = SHIFT(20),
        [ts_aux_sym_token18] = SHIFT(24),
        [ts_aux_sym_token20] = REDUCE(ts_sym_ternary, 5),
        [ts_aux_sym_token21] = SHIFT(33),
        [ts_aux_sym_token22] = SHIFT(35),
    },
    [710] = {
        [ts_aux_sym_function_call_repeat0] = SHIFT(12),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_function_call_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(30),
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
        [ts_aux_sym_token20] = SHIFT(30),
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
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(716),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_aux_sym_token19] = SHIFT(297),
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
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym__terminator] = SHIFT(721),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
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
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [726] = {
        [ts_sym_expression_statement] = SHIFT(727),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [727] = {
        [ts_sym_expression] = SHIFT(728),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(800),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [728] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(729),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_sym__delete] = SHIFT(715),
        [ts_sym__return] = SHIFT(718),
        [ts_sym__break] = SHIFT(722),
        [ts_sym__for] = SHIFT(724),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(731),
        [ts_sym__switch] = SHIFT(738),
        [ts_sym__var] = SHIFT(746),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(799),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [733] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(734),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(757),
        [ts_sym__delete] = SHIFT(758),
        [ts_sym__return] = SHIFT(761),
        [ts_sym__break] = SHIFT(765),
        [ts_sym__for] = SHIFT(767),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(774),
        [ts_sym__switch] = SHIFT(781),
        [ts_sym__var] = SHIFT(789),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(754),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(714),
        [ts_sym__delete] = SHIFT(715),
        [ts_sym__return] = SHIFT(718),
        [ts_sym__break] = SHIFT(722),
        [ts_sym__for] = SHIFT(724),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(731),
        [ts_sym__switch] = SHIFT(738),
        [ts_sym__var] = SHIFT(746),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(3),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(745),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [740] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(741),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [741] = {
        [ts_aux_sym_token0] = SHIFT(742),
    },
    [742] = {
        [ts_sym_switch_case] = SHIFT(284),
        [ts_sym__case] = SHIFT(285),
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
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(747),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(329),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(749),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token19] = SHIFT(100),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(751),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(753),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [751] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(245),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement, 1),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_expression_statement, 2),
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
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(294),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(759),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(318),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_aux_sym_token19] = SHIFT(297),
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
        [ts_sym_regex] = REDUCE(ts_sym_delete_statement, 3),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym__terminator] = SHIFT(764),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
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
        [ts_aux_sym_token14] = SHIFT(61),
        [ts_aux_sym_token15] = SHIFT(59),
        [ts_aux_sym_token16] = SHIFT(59),
        [ts_aux_sym_token18] = SHIFT(63),
        [ts_aux_sym_token21] = SHIFT(67),
        [ts_aux_sym_token22] = SHIFT(69),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 3),
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
        [ts_sym_regex] = REDUCE(ts_sym_return_statement, 2),
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
        [ts_sym_regex] = REDUCE(ts_sym_break_statement, 2),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__var] = SHIFT(600),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [769] = {
        [ts_sym_expression_statement] = SHIFT(770),
        [ts_sym_expression] = SHIFT(597),
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(599),
        [ts_sym__function] = SHIFT(102),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_token0] = SHIFT(243),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [770] = {
        [ts_sym_expression] = SHIFT(771),
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(798),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [771] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(772),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(757),
        [ts_sym__delete] = SHIFT(758),
        [ts_sym__return] = SHIFT(761),
        [ts_sym__break] = SHIFT(765),
        [ts_sym__for] = SHIFT(767),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(774),
        [ts_sym__switch] = SHIFT(781),
        [ts_sym__var] = SHIFT(789),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(754),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_for_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(797),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [776] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(777),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(757),
        [ts_sym__delete] = SHIFT(758),
        [ts_sym__return] = SHIFT(761),
        [ts_sym__break] = SHIFT(765),
        [ts_sym__for] = SHIFT(767),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(774),
        [ts_sym__switch] = SHIFT(781),
        [ts_sym__var] = SHIFT(789),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(754),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 5),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(757),
        [ts_sym__delete] = SHIFT(758),
        [ts_sym__return] = SHIFT(761),
        [ts_sym__break] = SHIFT(765),
        [ts_sym__for] = SHIFT(767),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(774),
        [ts_sym__switch] = SHIFT(781),
        [ts_sym__var] = SHIFT(789),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(754),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(98),
        [ts_sym_identifier] = SHIFT(99),
        [ts_sym_number] = SHIFT(98),
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
        [ts_sym_regex] = REDUCE(ts_sym_if_statement, 7),
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
        [ts_sym_math_op] = SHIFT(352),
        [ts_sym_bool_op] = SHIFT(352),
        [ts_sym_ternary] = SHIFT(352),
        [ts_sym_assignment] = SHIFT(352),
        [ts_sym_function_expression] = SHIFT(352),
        [ts_sym_function_call] = SHIFT(352),
        [ts_sym_property_access] = SHIFT(353),
        [ts_sym_object] = SHIFT(352),
        [ts_sym_array] = SHIFT(352),
        [ts_builtin_sym_error] = SHIFT(788),
        [ts_sym__function] = SHIFT(356),
        [ts_sym_null] = SHIFT(352),
        [ts_sym_true] = SHIFT(352),
        [ts_sym_false] = SHIFT(352),
        [ts_sym_regex] = SHIFT(352),
        [ts_sym_string] = SHIFT(352),
        [ts_sym_identifier] = SHIFT(353),
        [ts_sym_number] = SHIFT(352),
        [ts_aux_sym_token0] = SHIFT(373),
        [ts_aux_sym_token2] = SHIFT(402),
        [ts_aux_sym_token17] = SHIFT(405),
        [ts_aux_sym_token22] = SHIFT(407),
    },
    [783] = {
        [ts_aux_sym_token2] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(784),
        [ts_aux_sym_token5] = SHIFT(201),
        [ts_aux_sym_token6] = SHIFT(201),
        [ts_aux_sym_token7] = SHIFT(203),
        [ts_aux_sym_token8] = SHIFT(203),
        [ts_aux_sym_token9] = SHIFT(205),
        [ts_aux_sym_token10] = SHIFT(207),
        [ts_aux_sym_token11] = SHIFT(207),
        [ts_aux_sym_token12] = SHIFT(207),
        [ts_aux_sym_token13] = SHIFT(207),
        [ts_aux_sym_token14] = SHIFT(209),
        [ts_aux_sym_token15] = SHIFT(207),
        [ts_aux_sym_token16] = SHIFT(207),
        [ts_aux_sym_token18] = SHIFT(211),
        [ts_aux_sym_token21] = SHIFT(215),
        [ts_aux_sym_token22] = SHIFT(217),
    },
    [784] = {
        [ts_aux_sym_token0] = SHIFT(785),
    },
    [785] = {
        [ts_sym_switch_case] = SHIFT(284),
        [ts_sym__case] = SHIFT(285),
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
        [ts_sym_regex] = REDUCE(ts_sym_switch_statement, 7),
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
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(294),
        [ts_sym_bool_op] = SHIFT(294),
        [ts_sym_ternary] = SHIFT(294),
        [ts_sym_assignment] = SHIFT(790),
        [ts_sym_function_expression] = SHIFT(294),
        [ts_sym_function_call] = SHIFT(294),
        [ts_sym_property_access] = SHIFT(329),
        [ts_sym_object] = SHIFT(294),
        [ts_sym_array] = SHIFT(294),
        [ts_sym__function] = SHIFT(319),
        [ts_sym_null] = SHIFT(294),
        [ts_sym_true] = SHIFT(294),
        [ts_sym_false] = SHIFT(294),
        [ts_sym_regex] = SHIFT(294),
        [ts_sym_string] = SHIFT(294),
        [ts_sym_identifier] = SHIFT(792),
        [ts_sym_number] = SHIFT(294),
        [ts_aux_sym_token0] = SHIFT(331),
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
        [ts_sym_regex] = REDUCE(ts_sym_var_declaration, 3),
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
        [ts_aux_sym_token19] = SHIFT(100),
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
        [ts_sym_math_op] = SHIFT(98),
        [ts_sym_bool_op] = SHIFT(98),
        [ts_sym_ternary] = SHIFT(98),
        [ts_sym_assignment] = SHIFT(98),
        [ts_sym_function_expression] = SHIFT(98),
        [ts_sym_function_call] = SHIFT(98),
        [ts_sym_property_access] = SHIFT(99),
        [ts_sym_object] = SHIFT(98),
        [ts_sym_array] = SHIFT(98),
        [ts_builtin_sym_error] = SHIFT(794),
        [ts_sym__delete] = SHIFT(108),
        [ts_sym__return] = SHIFT(239),
        [ts_sym__break] = SHIFT(262),
        [ts_sym__for] = SHIFT(264),
        [ts_sym__function] = SHIFT(102),
        [ts_sym__if] = SHIFT(272),
        [ts_sym__switch] = SHIFT(279),
        [ts_sym__var] = SHIFT(325),
        [ts_sym_null] = SHIFT(98),
        [ts_sym_true] = SHIFT(98),
        [ts_sym_false] = SHIFT(98),
        [ts_sym_comment] = SHIFT(50),
        [ts_sym_regex] = SHIFT(98),
        [ts_sym_string] = SHIFT(366),
        [ts_sym_identifier] = SHIFT(367),
        [ts_sym_number] = SHIFT(98),
        [ts_aux_sym_statement_block_repeat0] = SHIFT(796),
        [ts_aux_sym_token0] = SHIFT(363),
        [ts_aux_sym_token1] = SHIFT(369),
        [ts_aux_sym_token2] = SHIFT(370),
        [ts_aux_sym_token17] = SHIFT(423),
        [ts_aux_sym_token22] = SHIFT(425),
    },
    [794] = {
        [ts_sym__terminator] = SHIFT(52),
        [ts_aux_sym_object_repeat0] = SHIFT(245),
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
        [ts_sym_regex] = REDUCE(ts_sym_statement_block, 3),
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
