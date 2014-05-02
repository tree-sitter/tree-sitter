#include "tree_sitter/parser.h"

#define STATE_COUNT 209
#define SYMBOL_COUNT 65

enum {
    ts_sym_program = 2,
    ts_sym_package_directive = 3,
    ts_sym_imports_block = 4,
    ts_sym_package_import = 5,
    ts_sym_declaration = 6,
    ts_sym_type_declaration = 7,
    ts_sym_var_declaration = 8,
    ts_sym_func_declaration = 9,
    ts_sym_statement_block = 10,
    ts_sym_type_expression = 11,
    ts_sym_pointer_type = 12,
    ts_sym_map_type = 13,
    ts_sym_slice_type = 14,
    ts_sym_struct_type = 15,
    ts_sym_interface_type = 16,
    ts_sym_expression = 17,
    ts_sym_math_op = 18,
    ts_sym_bool_op = 19,
    ts_sym__func_signature = 20,
    ts_sym_package_name = 21,
    ts_sym_var_name = 22,
    ts_sym_type_name = 23,
    ts_sym_string = 24,
    ts_sym__identifier = 25,
    ts_sym_number = 26,
    ts_aux_sym_program_repeat0 = 27,
    ts_aux_sym_program_repeat1 = 28,
    ts_aux_sym_imports_block_repeat0 = 29,
    ts_aux_sym_struct_type_repeat0 = 30,
    ts_aux_sym_interface_type_repeat0 = 31,
    ts_aux_sym__func_signature_repeat0 = 32,
    ts_aux_sym__func_signature_repeat1 = 33,
    ts_aux_sym__func_signature_repeat2 = 34,
    ts_aux_sym__func_signature_repeat3 = 35,
    ts_aux_sym__func_signature_repeat4 = 36,
    ts_aux_sym_token0 = 37,
    ts_aux_sym_token1 = 38,
    ts_aux_sym_token2 = 39,
    ts_aux_sym_token3 = 40,
    ts_aux_sym_token4 = 41,
    ts_aux_sym_token5 = 42,
    ts_aux_sym_token6 = 43,
    ts_aux_sym_token7 = 44,
    ts_aux_sym_token8 = 45,
    ts_aux_sym_token9 = 46,
    ts_aux_sym_token10 = 47,
    ts_aux_sym_token11 = 48,
    ts_aux_sym_token12 = 49,
    ts_aux_sym_token13 = 50,
    ts_aux_sym_token14 = 51,
    ts_aux_sym_token15 = 52,
    ts_aux_sym_token16 = 53,
    ts_aux_sym_token17 = 54,
    ts_aux_sym_token18 = 55,
    ts_aux_sym_token19 = 56,
    ts_aux_sym_token20 = 57,
    ts_aux_sym_token21 = 58,
    ts_aux_sym_token22 = 59,
    ts_aux_sym_token23 = 60,
    ts_aux_sym_token24 = 61,
    ts_aux_sym_token25 = 62,
    ts_aux_sym_token26 = 63,
    ts_aux_sym_token27 = 64,
};

SYMBOL_NAMES = {
    [ts_sym_program] = "program",
    [ts_sym_package_directive] = "package_directive",
    [ts_sym_imports_block] = "imports_block",
    [ts_sym_package_import] = "package_import",
    [ts_sym_declaration] = "declaration",
    [ts_sym_type_declaration] = "type_declaration",
    [ts_sym_var_declaration] = "var_declaration",
    [ts_sym_func_declaration] = "func_declaration",
    [ts_sym_statement_block] = "statement_block",
    [ts_sym_type_expression] = "type_expression",
    [ts_sym_pointer_type] = "pointer_type",
    [ts_sym_map_type] = "map_type",
    [ts_sym_slice_type] = "slice_type",
    [ts_sym_struct_type] = "struct_type",
    [ts_sym_interface_type] = "interface_type",
    [ts_sym_expression] = "expression",
    [ts_sym_math_op] = "math_op",
    [ts_sym_bool_op] = "bool_op",
    [ts_sym__func_signature] = "_func_signature",
    [ts_sym_package_name] = "package_name",
    [ts_sym_var_name] = "var_name",
    [ts_sym_type_name] = "type_name",
    [ts_builtin_sym_error] = "error",
    [ts_builtin_sym_end] = "end",
    [ts_sym_string] = "string",
    [ts_sym__identifier] = "_identifier",
    [ts_sym_number] = "number",
    [ts_aux_sym_program_repeat0] = "program_repeat0",
    [ts_aux_sym_program_repeat1] = "program_repeat1",
    [ts_aux_sym_imports_block_repeat0] = "imports_block_repeat0",
    [ts_aux_sym_struct_type_repeat0] = "struct_type_repeat0",
    [ts_aux_sym_interface_type_repeat0] = "interface_type_repeat0",
    [ts_aux_sym__func_signature_repeat0] = "_func_signature_repeat0",
    [ts_aux_sym__func_signature_repeat1] = "_func_signature_repeat1",
    [ts_aux_sym__func_signature_repeat2] = "_func_signature_repeat2",
    [ts_aux_sym__func_signature_repeat3] = "_func_signature_repeat3",
    [ts_aux_sym__func_signature_repeat4] = "_func_signature_repeat4",
    [ts_aux_sym_token0] = "",
    [ts_aux_sym_token1] = "",
    [ts_aux_sym_token2] = "'('",
    [ts_aux_sym_token3] = "')'",
    [ts_aux_sym_token4] = "",
    [ts_aux_sym_token5] = "",
    [ts_aux_sym_token6] = "'='",
    [ts_aux_sym_token7] = "",
    [ts_aux_sym_token8] = "'{'",
    [ts_aux_sym_token9] = "'}'",
    [ts_aux_sym_token10] = "'*'",
    [ts_aux_sym_token11] = "",
    [ts_aux_sym_token12] = "'['",
    [ts_aux_sym_token13] = "']'",
    [ts_aux_sym_token14] = "",
    [ts_aux_sym_token15] = "",
    [ts_aux_sym_token16] = "'/'",
    [ts_aux_sym_token17] = "'+'",
    [ts_aux_sym_token18] = "'-'",
    [ts_aux_sym_token19] = "'||'",
    [ts_aux_sym_token20] = "'&&'",
    [ts_aux_sym_token21] = "'=='",
    [ts_aux_sym_token22] = "'<='",
    [ts_aux_sym_token23] = "'<'",
    [ts_aux_sym_token24] = "'>='",
    [ts_aux_sym_token25] = "'>'",
    [ts_aux_sym_token26] = "'!'",
    [ts_aux_sym_token27] = "','",
};

HIDDEN_SYMBOLS = {
    [ts_sym__func_signature] = 1,
    [ts_sym__identifier] = 1,
    [ts_aux_sym_program_repeat0] = 1,
    [ts_aux_sym_program_repeat1] = 1,
    [ts_aux_sym_imports_block_repeat0] = 1,
    [ts_aux_sym_struct_type_repeat0] = 1,
    [ts_aux_sym_interface_type_repeat0] = 1,
    [ts_aux_sym__func_signature_repeat0] = 1,
    [ts_aux_sym__func_signature_repeat1] = 1,
    [ts_aux_sym__func_signature_repeat2] = 1,
    [ts_aux_sym__func_signature_repeat3] = 1,
    [ts_aux_sym__func_signature_repeat4] = 1,
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
            if (lookahead == 'f')
                ADVANCE(3);
            if (lookahead == 't')
                ADVANCE(7);
            if (lookahead == 'v')
                ADVANCE(11);
            LEX_ERROR();
        case 3:
            if (lookahead == 'u')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (lookahead == 'n')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (lookahead == 'c')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 7:
            if (lookahead == 'y')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'p')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (lookahead == 'e')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 11:
            if (lookahead == 'a')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (lookahead == 'r')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 14:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(14);
            if (lookahead == 'f')
                ADVANCE(3);
            if (lookahead == 'i')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(7);
            if (lookahead == 'v')
                ADVANCE(11);
            LEX_ERROR();
        case 15:
            if (lookahead == 'm')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            if (lookahead == 'p')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            if (lookahead == 'o')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            if (lookahead == 'r')
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            if (lookahead == 't')
                ADVANCE(20);
            LEX_ERROR();
        case 20:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 21:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(21);
            if (lookahead == '\"')
                ADVANCE(22);
            if (lookahead == ')')
                ADVANCE(27);
            LEX_ERROR();
        case 22:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(23);
            if (lookahead == '\\')
                ADVANCE(25);
            LEX_ERROR();
        case 23:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(23);
            if (lookahead == '\"')
                ADVANCE(24);
            if (lookahead == '\\')
                ADVANCE(25);
            LEX_ERROR();
        case 24:
            ACCEPT_TOKEN(ts_sym_string);
        case 25:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(23);
            if (lookahead == '\"')
                ADVANCE(26);
            if (lookahead == '\\')
                ADVANCE(25);
            LEX_ERROR();
        case 26:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(23);
            if (lookahead == '\"')
                ADVANCE(24);
            if (lookahead == '\\')
                ADVANCE(25);
            ACCEPT_TOKEN(ts_sym_string);
        case 27:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 28:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(28);
            if (lookahead == ')')
                ADVANCE(27);
            LEX_ERROR();
        case 29:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(29);
            if (lookahead == '\"')
                ADVANCE(22);
            if (lookahead == '(')
                ADVANCE(30);
            LEX_ERROR();
        case 30:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 31:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(31);
            if (lookahead == '*')
                ADVANCE(32);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(34);
            if (lookahead == 'i')
                ADVANCE(35);
            if (lookahead == 'm')
                ADVANCE(44);
            if (lookahead == 's')
                ADVANCE(47);
            LEX_ERROR();
        case 32:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 33:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 34:
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 35:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 36:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 37:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 38:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 39:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(40);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 40:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 41:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 42:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 43:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_token15);
        case 44:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 45:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 46:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(50);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_token14);
        case 53:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(53);
            if (lookahead == '}')
                ADVANCE(54);
            LEX_ERROR();
        case 54:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 55:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(55);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '}')
                ADVANCE(54);
            LEX_ERROR();
        case 56:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(56);
            if (lookahead == '{')
                ADVANCE(57);
            LEX_ERROR();
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 58:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(58);
            if (lookahead == '(')
                ADVANCE(30);
            LEX_ERROR();
        case 59:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(59);
            if (lookahead == ')')
                ADVANCE(27);
            if (lookahead == ',')
                ADVANCE(60);
            LEX_ERROR();
        case 60:
            ACCEPT_TOKEN(ts_aux_sym_token27);
        case 61:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(61);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 62:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(62);
            if (lookahead == ')')
                ADVANCE(27);
            if (lookahead == ',')
                ADVANCE(60);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 63:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(63);
            if (lookahead == '(')
                ADVANCE(30);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '}')
                ADVANCE(54);
            LEX_ERROR();
        case 64:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == ']')
                ADVANCE(65);
            LEX_ERROR();
        case 65:
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 66:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (lookahead == '[')
                ADVANCE(34);
            LEX_ERROR();
        case 67:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (lookahead == '*')
                ADVANCE(32);
            if (lookahead == ',')
                ADVANCE(60);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(34);
            if (lookahead == 'i')
                ADVANCE(35);
            if (lookahead == 'm')
                ADVANCE(44);
            if (lookahead == 's')
                ADVANCE(47);
            LEX_ERROR();
        case 68:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == ')')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 69:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '*')
                ADVANCE(32);
            if (lookahead == '+')
                ADVANCE(72);
            if (lookahead == '-')
                ADVANCE(73);
            if (lookahead == '/')
                ADVANCE(74);
            if (lookahead == '<')
                ADVANCE(75);
            if (lookahead == '=')
                ADVANCE(77);
            if (lookahead == '>')
                ADVANCE(79);
            if (lookahead == 'f')
                ADVANCE(3);
            if (lookahead == 't')
                ADVANCE(7);
            if (lookahead == 'v')
                ADVANCE(11);
            if (lookahead == '|')
                ADVANCE(81);
            LEX_ERROR();
        case 70:
            if (lookahead == '&')
                ADVANCE(71);
            LEX_ERROR();
        case 71:
            ACCEPT_TOKEN(ts_aux_sym_token20);
        case 72:
            ACCEPT_TOKEN(ts_aux_sym_token17);
        case 73:
            ACCEPT_TOKEN(ts_aux_sym_token18);
        case 74:
            ACCEPT_TOKEN(ts_aux_sym_token16);
        case 75:
            if (lookahead == '=')
                ADVANCE(76);
            ACCEPT_TOKEN(ts_aux_sym_token23);
        case 76:
            ACCEPT_TOKEN(ts_aux_sym_token22);
        case 77:
            if (lookahead == '=')
                ADVANCE(78);
            LEX_ERROR();
        case 78:
            ACCEPT_TOKEN(ts_aux_sym_token21);
        case 79:
            if (lookahead == '=')
                ADVANCE(80);
            ACCEPT_TOKEN(ts_aux_sym_token25);
        case 80:
            ACCEPT_TOKEN(ts_aux_sym_token24);
        case 81:
            if (lookahead == '|')
                ADVANCE(82);
            LEX_ERROR();
        case 82:
            ACCEPT_TOKEN(ts_aux_sym_token19);
        case 83:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
            if (lookahead == '!')
                ADVANCE(84);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 84:
            ACCEPT_TOKEN(ts_aux_sym_token26);
        case 85:
            if (lookahead == '.')
                ADVANCE(86);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            ACCEPT_TOKEN(ts_sym_number);
        case 86:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(87);
            LEX_ERROR();
        case 87:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(87);
            ACCEPT_TOKEN(ts_sym_number);
        case 88:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(88);
            if (lookahead == '=')
                ADVANCE(89);
            LEX_ERROR();
        case 89:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 90:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '(')
                ADVANCE(30);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '{')
                ADVANCE(57);
            LEX_ERROR();
        case 91:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(91);
            if (lookahead == 'p')
                ADVANCE(92);
            LEX_ERROR();
        case 92:
            if (lookahead == 'a')
                ADVANCE(93);
            LEX_ERROR();
        case 93:
            if (lookahead == 'c')
                ADVANCE(94);
            LEX_ERROR();
        case 94:
            if (lookahead == 'k')
                ADVANCE(95);
            LEX_ERROR();
        case 95:
            if (lookahead == 'a')
                ADVANCE(96);
            LEX_ERROR();
        case 96:
            if (lookahead == 'g')
                ADVANCE(97);
            LEX_ERROR();
        case 97:
            if (lookahead == 'e')
                ADVANCE(98);
            LEX_ERROR();
        case 98:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 99:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(22);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(30);
            if (lookahead == ')')
                ADVANCE(27);
            if (lookahead == '*')
                ADVANCE(32);
            if (lookahead == '+')
                ADVANCE(72);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '-')
                ADVANCE(73);
            if (lookahead == '/')
                ADVANCE(74);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(75);
            if (lookahead == '=')
                ADVANCE(100);
            if (lookahead == '>')
                ADVANCE(79);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(34);
            if (lookahead == ']')
                ADVANCE(65);
            if (lookahead == 'f')
                ADVANCE(101);
            if (lookahead == 'i')
                ADVANCE(105);
            if (lookahead == 'm')
                ADVANCE(44);
            if (lookahead == 'p')
                ADVANCE(111);
            if (lookahead == 's')
                ADVANCE(47);
            if (lookahead == 't')
                ADVANCE(118);
            if (lookahead == 'v')
                ADVANCE(122);
            if (lookahead == '{')
                ADVANCE(57);
            if (lookahead == '|')
                ADVANCE(81);
            if (lookahead == '}')
                ADVANCE(54);
            LEX_ERROR();
        case 100:
            if (lookahead == '=')
                ADVANCE(78);
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(102);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(103);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(104);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 104:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 105:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'm')
                ADVANCE(106);
            if (lookahead == 'n')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 106:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(107);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 107:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 108:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(109);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 109:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(110);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 110:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 111:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(112);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 112:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(113);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 113:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'k')
                ADVANCE(114);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 114:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(115);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 115:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(116);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 116:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(117);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 117:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 118:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(33);
            if (lookahead == 'y')
                ADVANCE(119);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 119:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(120);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 120:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(121);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 121:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 122:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(123);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 123:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(124);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(22);
            if (lookahead == '&')
                ADVANCE(70);
            if (lookahead == '(')
                ADVANCE(30);
            if (lookahead == ')')
                ADVANCE(27);
            if (lookahead == '*')
                ADVANCE(32);
            if (lookahead == '+')
                ADVANCE(72);
            if (lookahead == ',')
                ADVANCE(60);
            if (lookahead == '-')
                ADVANCE(73);
            if (lookahead == '/')
                ADVANCE(74);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == '<')
                ADVANCE(75);
            if (lookahead == '=')
                ADVANCE(100);
            if (lookahead == '>')
                ADVANCE(79);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(34);
            if (lookahead == ']')
                ADVANCE(65);
            if (lookahead == 'f')
                ADVANCE(101);
            if (lookahead == 'i')
                ADVANCE(105);
            if (lookahead == 'm')
                ADVANCE(44);
            if (lookahead == 'p')
                ADVANCE(111);
            if (lookahead == 's')
                ADVANCE(47);
            if (lookahead == 't')
                ADVANCE(118);
            if (lookahead == 'v')
                ADVANCE(122);
            if (lookahead == '{')
                ADVANCE(57);
            if (lookahead == '|')
                ADVANCE(81);
            if (lookahead == '}')
                ADVANCE(54);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 91,
    [1] = 0,
    [2] = 14,
    [3] = 14,
    [4] = 2,
    [5] = 29,
    [6] = 14,
    [7] = 14,
    [8] = 21,
    [9] = 21,
    [10] = 21,
    [11] = 28,
    [12] = 28,
    [13] = 14,
    [14] = 2,
    [15] = 2,
    [16] = 2,
    [17] = 0,
    [18] = 61,
    [19] = 31,
    [20] = 2,
    [21] = 2,
    [22] = 2,
    [23] = 31,
    [24] = 2,
    [25] = 66,
    [26] = 31,
    [27] = 64,
    [28] = 31,
    [29] = 2,
    [30] = 64,
    [31] = 31,
    [32] = 2,
    [33] = 56,
    [34] = 55,
    [35] = 31,
    [36] = 55,
    [37] = 31,
    [38] = 53,
    [39] = 55,
    [40] = 55,
    [41] = 31,
    [42] = 55,
    [43] = 66,
    [44] = 31,
    [45] = 64,
    [46] = 31,
    [47] = 55,
    [48] = 64,
    [49] = 31,
    [50] = 55,
    [51] = 56,
    [52] = 55,
    [53] = 53,
    [54] = 55,
    [55] = 56,
    [56] = 55,
    [57] = 58,
    [58] = 55,
    [59] = 58,
    [60] = 53,
    [61] = 68,
    [62] = 67,
    [63] = 31,
    [64] = 59,
    [65] = 28,
    [66] = 63,
    [67] = 55,
    [68] = 61,
    [69] = 61,
    [70] = 59,
    [71] = 28,
    [72] = 55,
    [73] = 61,
    [74] = 61,
    [75] = 59,
    [76] = 28,
    [77] = 59,
    [78] = 61,
    [79] = 59,
    [80] = 28,
    [81] = 55,
    [82] = 61,
    [83] = 59,
    [84] = 28,
    [85] = 62,
    [86] = 61,
    [87] = 67,
    [88] = 31,
    [89] = 59,
    [90] = 28,
    [91] = 59,
    [92] = 31,
    [93] = 59,
    [94] = 66,
    [95] = 31,
    [96] = 64,
    [97] = 31,
    [98] = 59,
    [99] = 64,
    [100] = 31,
    [101] = 59,
    [102] = 56,
    [103] = 55,
    [104] = 53,
    [105] = 59,
    [106] = 56,
    [107] = 55,
    [108] = 53,
    [109] = 59,
    [110] = 64,
    [111] = 64,
    [112] = 31,
    [113] = 64,
    [114] = 66,
    [115] = 31,
    [116] = 64,
    [117] = 31,
    [118] = 64,
    [119] = 64,
    [120] = 31,
    [121] = 64,
    [122] = 56,
    [123] = 55,
    [124] = 53,
    [125] = 64,
    [126] = 56,
    [127] = 55,
    [128] = 53,
    [129] = 64,
    [130] = 61,
    [131] = 67,
    [132] = 31,
    [133] = 67,
    [134] = 61,
    [135] = 67,
    [136] = 31,
    [137] = 63,
    [138] = 55,
    [139] = 61,
    [140] = 61,
    [141] = 59,
    [142] = 28,
    [143] = 59,
    [144] = 28,
    [145] = 55,
    [146] = 53,
    [147] = 55,
    [148] = 53,
    [149] = 2,
    [150] = 56,
    [151] = 55,
    [152] = 53,
    [153] = 2,
    [154] = 31,
    [155] = 61,
    [156] = 88,
    [157] = 83,
    [158] = 69,
    [159] = 83,
    [160] = 69,
    [161] = 83,
    [162] = 69,
    [163] = 83,
    [164] = 69,
    [165] = 83,
    [166] = 69,
    [167] = 83,
    [168] = 69,
    [169] = 69,
    [170] = 69,
    [171] = 83,
    [172] = 69,
    [173] = 88,
    [174] = 61,
    [175] = 58,
    [176] = 56,
    [177] = 2,
    [178] = 53,
    [179] = 2,
    [180] = 68,
    [181] = 67,
    [182] = 31,
    [183] = 59,
    [184] = 28,
    [185] = 90,
    [186] = 56,
    [187] = 56,
    [188] = 61,
    [189] = 61,
    [190] = 59,
    [191] = 28,
    [192] = 56,
    [193] = 59,
    [194] = 28,
    [195] = 56,
    [196] = 90,
    [197] = 56,
    [198] = 61,
    [199] = 61,
    [200] = 59,
    [201] = 28,
    [202] = 59,
    [203] = 28,
    [204] = 56,
    [205] = 0,
    [206] = 61,
    [207] = 14,
    [208] = 14,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_program] = SHIFT(1),
        [ts_sym_package_directive] = SHIFT(2),
        [ts_aux_sym_token0] = SHIFT(206),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [2] = {
        [ts_sym_imports_block] = SHIFT(3),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_program_repeat0] = SHIFT(14),
        [ts_aux_sym_token1] = SHIFT(5),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [3] = {
        [ts_sym_imports_block] = SHIFT(3),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_program_repeat0] = SHIFT(4),
        [ts_aux_sym_token1] = SHIFT(5),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [4] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [5] = {
        [ts_sym_package_import] = SHIFT(6),
        [ts_sym_string] = SHIFT(7),
        [ts_aux_sym_token2] = SHIFT(8),
    },
    [6] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_imports_block, 2),
    },
    [7] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_package_import, 1),
    },
    [8] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_builtin_sym_error] = SHIFT(12),
        [ts_sym_string] = SHIFT(10),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(12),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [9] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_sym_string] = SHIFT(10),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(11),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [10] = {
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_package_import, 1),
    },
    [11] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_imports_block_repeat0, 2),
    },
    [12] = {
        [ts_aux_sym_token3] = SHIFT(13),
    },
    [13] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_token1] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_imports_block, 4),
    },
    [14] = {
        [ts_sym_declaration] = SHIFT(15),
        [ts_sym_type_declaration] = SHIFT(16),
        [ts_sym_var_declaration] = SHIFT(16),
        [ts_sym_func_declaration] = SHIFT(16),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_aux_sym_program_repeat1] = SHIFT(205),
        [ts_aux_sym_token4] = SHIFT(18),
        [ts_aux_sym_token5] = SHIFT(155),
        [ts_aux_sym_token7] = SHIFT(174),
    },
    [15] = {
        [ts_sym_declaration] = SHIFT(15),
        [ts_sym_type_declaration] = SHIFT(16),
        [ts_sym_var_declaration] = SHIFT(16),
        [ts_sym_func_declaration] = SHIFT(16),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_aux_sym_program_repeat1] = SHIFT(17),
        [ts_aux_sym_token4] = SHIFT(18),
        [ts_aux_sym_token5] = SHIFT(155),
        [ts_aux_sym_token7] = SHIFT(174),
    },
    [16] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_declaration, 1),
    },
    [17] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
    },
    [18] = {
        [ts_sym_type_name] = SHIFT(19),
        [ts_sym__identifier] = SHIFT(154),
    },
    [19] = {
        [ts_sym_type_expression] = SHIFT(20),
        [ts_sym_pointer_type] = SHIFT(21),
        [ts_sym_map_type] = SHIFT(21),
        [ts_sym_slice_type] = SHIFT(21),
        [ts_sym_struct_type] = SHIFT(21),
        [ts_sym_interface_type] = SHIFT(21),
        [ts_sym_type_name] = SHIFT(21),
        [ts_sym__identifier] = SHIFT(22),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(30),
        [ts_aux_sym_token14] = SHIFT(33),
        [ts_aux_sym_token15] = SHIFT(150),
    },
    [20] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_declaration, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_declaration, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_declaration, 3),
    },
    [21] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_expression, 1),
    },
    [22] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_name, 1),
    },
    [23] = {
        [ts_sym_type_expression] = SHIFT(24),
        [ts_sym_pointer_type] = SHIFT(21),
        [ts_sym_map_type] = SHIFT(21),
        [ts_sym_slice_type] = SHIFT(21),
        [ts_sym_struct_type] = SHIFT(21),
        [ts_sym_interface_type] = SHIFT(21),
        [ts_sym_type_name] = SHIFT(21),
        [ts_sym__identifier] = SHIFT(22),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(30),
        [ts_aux_sym_token14] = SHIFT(33),
        [ts_aux_sym_token15] = SHIFT(150),
    },
    [24] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_pointer_type, 2),
    },
    [25] = {
        [ts_aux_sym_token12] = SHIFT(26),
    },
    [26] = {
        [ts_sym_type_expression] = SHIFT(27),
        [ts_sym_pointer_type] = SHIFT(110),
        [ts_sym_map_type] = SHIFT(110),
        [ts_sym_slice_type] = SHIFT(110),
        [ts_sym_struct_type] = SHIFT(110),
        [ts_sym_interface_type] = SHIFT(110),
        [ts_sym_type_name] = SHIFT(110),
        [ts_sym__identifier] = SHIFT(111),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [27] = {
        [ts_aux_sym_token13] = SHIFT(28),
    },
    [28] = {
        [ts_sym_type_expression] = SHIFT(29),
        [ts_sym_pointer_type] = SHIFT(21),
        [ts_sym_map_type] = SHIFT(21),
        [ts_sym_slice_type] = SHIFT(21),
        [ts_sym_struct_type] = SHIFT(21),
        [ts_sym_interface_type] = SHIFT(21),
        [ts_sym_type_name] = SHIFT(21),
        [ts_sym__identifier] = SHIFT(22),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(30),
        [ts_aux_sym_token14] = SHIFT(33),
        [ts_aux_sym_token15] = SHIFT(150),
    },
    [29] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_map_type, 5),
    },
    [30] = {
        [ts_aux_sym_token13] = SHIFT(31),
    },
    [31] = {
        [ts_sym_type_expression] = SHIFT(32),
        [ts_sym_pointer_type] = SHIFT(21),
        [ts_sym_map_type] = SHIFT(21),
        [ts_sym_slice_type] = SHIFT(21),
        [ts_sym_struct_type] = SHIFT(21),
        [ts_sym_interface_type] = SHIFT(21),
        [ts_sym_type_name] = SHIFT(21),
        [ts_sym__identifier] = SHIFT(22),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(30),
        [ts_aux_sym_token14] = SHIFT(33),
        [ts_aux_sym_token15] = SHIFT(150),
    },
    [32] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_slice_type, 3),
    },
    [33] = {
        [ts_aux_sym_token8] = SHIFT(34),
    },
    [34] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(148),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [35] = {
        [ts_sym_type_expression] = SHIFT(36),
        [ts_sym_pointer_type] = SHIFT(39),
        [ts_sym_map_type] = SHIFT(39),
        [ts_sym_slice_type] = SHIFT(39),
        [ts_sym_struct_type] = SHIFT(39),
        [ts_sym_interface_type] = SHIFT(39),
        [ts_sym_type_name] = SHIFT(39),
        [ts_sym__identifier] = SHIFT(40),
        [ts_aux_sym_token10] = SHIFT(41),
        [ts_aux_sym_token11] = SHIFT(43),
        [ts_aux_sym_token12] = SHIFT(48),
        [ts_aux_sym_token14] = SHIFT(51),
        [ts_aux_sym_token15] = SHIFT(55),
    },
    [36] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(38),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [37] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_name, 1),
    },
    [38] = {
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 3),
    },
    [39] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_type_expression, 1),
    },
    [40] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_type_name, 1),
    },
    [41] = {
        [ts_sym_type_expression] = SHIFT(42),
        [ts_sym_pointer_type] = SHIFT(39),
        [ts_sym_map_type] = SHIFT(39),
        [ts_sym_slice_type] = SHIFT(39),
        [ts_sym_struct_type] = SHIFT(39),
        [ts_sym_interface_type] = SHIFT(39),
        [ts_sym_type_name] = SHIFT(39),
        [ts_sym__identifier] = SHIFT(40),
        [ts_aux_sym_token10] = SHIFT(41),
        [ts_aux_sym_token11] = SHIFT(43),
        [ts_aux_sym_token12] = SHIFT(48),
        [ts_aux_sym_token14] = SHIFT(51),
        [ts_aux_sym_token15] = SHIFT(55),
    },
    [42] = {
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_pointer_type, 2),
    },
    [43] = {
        [ts_aux_sym_token12] = SHIFT(44),
    },
    [44] = {
        [ts_sym_type_expression] = SHIFT(45),
        [ts_sym_pointer_type] = SHIFT(110),
        [ts_sym_map_type] = SHIFT(110),
        [ts_sym_slice_type] = SHIFT(110),
        [ts_sym_struct_type] = SHIFT(110),
        [ts_sym_interface_type] = SHIFT(110),
        [ts_sym_type_name] = SHIFT(110),
        [ts_sym__identifier] = SHIFT(111),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [45] = {
        [ts_aux_sym_token13] = SHIFT(46),
    },
    [46] = {
        [ts_sym_type_expression] = SHIFT(47),
        [ts_sym_pointer_type] = SHIFT(39),
        [ts_sym_map_type] = SHIFT(39),
        [ts_sym_slice_type] = SHIFT(39),
        [ts_sym_struct_type] = SHIFT(39),
        [ts_sym_interface_type] = SHIFT(39),
        [ts_sym_type_name] = SHIFT(39),
        [ts_sym__identifier] = SHIFT(40),
        [ts_aux_sym_token10] = SHIFT(41),
        [ts_aux_sym_token11] = SHIFT(43),
        [ts_aux_sym_token12] = SHIFT(48),
        [ts_aux_sym_token14] = SHIFT(51),
        [ts_aux_sym_token15] = SHIFT(55),
    },
    [47] = {
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_map_type, 5),
    },
    [48] = {
        [ts_aux_sym_token13] = SHIFT(49),
    },
    [49] = {
        [ts_sym_type_expression] = SHIFT(50),
        [ts_sym_pointer_type] = SHIFT(39),
        [ts_sym_map_type] = SHIFT(39),
        [ts_sym_slice_type] = SHIFT(39),
        [ts_sym_struct_type] = SHIFT(39),
        [ts_sym_interface_type] = SHIFT(39),
        [ts_sym_type_name] = SHIFT(39),
        [ts_sym__identifier] = SHIFT(40),
        [ts_aux_sym_token10] = SHIFT(41),
        [ts_aux_sym_token11] = SHIFT(43),
        [ts_aux_sym_token12] = SHIFT(48),
        [ts_aux_sym_token14] = SHIFT(51),
        [ts_aux_sym_token15] = SHIFT(55),
    },
    [50] = {
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_slice_type, 3),
    },
    [51] = {
        [ts_aux_sym_token8] = SHIFT(52),
    },
    [52] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(53),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [53] = {
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [54] = {
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_struct_type, 4),
    },
    [55] = {
        [ts_aux_sym_token8] = SHIFT(56),
    },
    [56] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(146),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [57] = {
        [ts_sym__func_signature] = SHIFT(58),
        [ts_aux_sym_token2] = SHIFT(61),
    },
    [58] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(60),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [59] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_name, 1),
    },
    [60] = {
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [61] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__identifier] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(137),
    },
    [62] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(63),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token12] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token15] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token27] = SHIFT(134),
    },
    [63] = {
        [ts_sym_type_expression] = SHIFT(64),
        [ts_sym_pointer_type] = SHIFT(91),
        [ts_sym_map_type] = SHIFT(91),
        [ts_sym_slice_type] = SHIFT(91),
        [ts_sym_struct_type] = SHIFT(91),
        [ts_sym_interface_type] = SHIFT(91),
        [ts_sym_type_name] = SHIFT(91),
        [ts_sym__identifier] = SHIFT(77),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [64] = {
        [ts_aux_sym__func_signature_repeat2] = SHIFT(65),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token27] = SHIFT(86),
    },
    [65] = {
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [66] = {
        [ts_sym_type_name] = SHIFT(67),
        [ts_sym__identifier] = SHIFT(40),
        [ts_aux_sym_token2] = SHIFT(68),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 6),
    },
    [67] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 7),
    },
    [68] = {
        [ts_sym_var_name] = SHIFT(69),
        [ts_sym_type_name] = SHIFT(79),
        [ts_sym__identifier] = SHIFT(85),
    },
    [69] = {
        [ts_sym_type_name] = SHIFT(70),
        [ts_sym__identifier] = SHIFT(77),
    },
    [70] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(71),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [71] = {
        [ts_aux_sym_token3] = SHIFT(72),
    },
    [72] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 11),
    },
    [73] = {
        [ts_sym_var_name] = SHIFT(74),
        [ts_sym__identifier] = SHIFT(78),
    },
    [74] = {
        [ts_sym_type_name] = SHIFT(75),
        [ts_sym__identifier] = SHIFT(77),
    },
    [75] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(76),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [76] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [77] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_type_name, 1),
    },
    [78] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
    },
    [79] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(80),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [80] = {
        [ts_aux_sym_token3] = SHIFT(81),
    },
    [81] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 10),
    },
    [82] = {
        [ts_sym_type_name] = SHIFT(83),
        [ts_sym__identifier] = SHIFT(77),
    },
    [83] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(84),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [84] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [85] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token3] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_type_name, 1),
    },
    [86] = {
        [ts_sym_var_name] = SHIFT(87),
        [ts_sym__identifier] = SHIFT(133),
    },
    [87] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(88),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token12] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token15] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token27] = SHIFT(130),
    },
    [88] = {
        [ts_sym_type_expression] = SHIFT(89),
        [ts_sym_pointer_type] = SHIFT(91),
        [ts_sym_map_type] = SHIFT(91),
        [ts_sym_slice_type] = SHIFT(91),
        [ts_sym_struct_type] = SHIFT(91),
        [ts_sym_interface_type] = SHIFT(91),
        [ts_sym_type_name] = SHIFT(91),
        [ts_sym__identifier] = SHIFT(77),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [89] = {
        [ts_aux_sym__func_signature_repeat2] = SHIFT(90),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token27] = SHIFT(86),
    },
    [90] = {
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [91] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_type_expression, 1),
    },
    [92] = {
        [ts_sym_type_expression] = SHIFT(93),
        [ts_sym_pointer_type] = SHIFT(91),
        [ts_sym_map_type] = SHIFT(91),
        [ts_sym_slice_type] = SHIFT(91),
        [ts_sym_struct_type] = SHIFT(91),
        [ts_sym_interface_type] = SHIFT(91),
        [ts_sym_type_name] = SHIFT(91),
        [ts_sym__identifier] = SHIFT(77),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [93] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_pointer_type, 2),
    },
    [94] = {
        [ts_aux_sym_token12] = SHIFT(95),
    },
    [95] = {
        [ts_sym_type_expression] = SHIFT(96),
        [ts_sym_pointer_type] = SHIFT(110),
        [ts_sym_map_type] = SHIFT(110),
        [ts_sym_slice_type] = SHIFT(110),
        [ts_sym_struct_type] = SHIFT(110),
        [ts_sym_interface_type] = SHIFT(110),
        [ts_sym_type_name] = SHIFT(110),
        [ts_sym__identifier] = SHIFT(111),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [96] = {
        [ts_aux_sym_token13] = SHIFT(97),
    },
    [97] = {
        [ts_sym_type_expression] = SHIFT(98),
        [ts_sym_pointer_type] = SHIFT(91),
        [ts_sym_map_type] = SHIFT(91),
        [ts_sym_slice_type] = SHIFT(91),
        [ts_sym_struct_type] = SHIFT(91),
        [ts_sym_interface_type] = SHIFT(91),
        [ts_sym_type_name] = SHIFT(91),
        [ts_sym__identifier] = SHIFT(77),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [98] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_map_type, 5),
    },
    [99] = {
        [ts_aux_sym_token13] = SHIFT(100),
    },
    [100] = {
        [ts_sym_type_expression] = SHIFT(101),
        [ts_sym_pointer_type] = SHIFT(91),
        [ts_sym_map_type] = SHIFT(91),
        [ts_sym_slice_type] = SHIFT(91),
        [ts_sym_struct_type] = SHIFT(91),
        [ts_sym_interface_type] = SHIFT(91),
        [ts_sym_type_name] = SHIFT(91),
        [ts_sym__identifier] = SHIFT(77),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [101] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_slice_type, 3),
    },
    [102] = {
        [ts_aux_sym_token8] = SHIFT(103),
    },
    [103] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(104),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [104] = {
        [ts_aux_sym_token9] = SHIFT(105),
    },
    [105] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token27] = REDUCE(ts_sym_struct_type, 4),
    },
    [106] = {
        [ts_aux_sym_token8] = SHIFT(107),
    },
    [107] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [108] = {
        [ts_aux_sym_token9] = SHIFT(109),
    },
    [109] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token27] = REDUCE(ts_sym_interface_type, 4),
    },
    [110] = {
        [ts_aux_sym_token13] = REDUCE(ts_sym_type_expression, 1),
    },
    [111] = {
        [ts_aux_sym_token13] = REDUCE(ts_sym_type_name, 1),
    },
    [112] = {
        [ts_sym_type_expression] = SHIFT(113),
        [ts_sym_pointer_type] = SHIFT(110),
        [ts_sym_map_type] = SHIFT(110),
        [ts_sym_slice_type] = SHIFT(110),
        [ts_sym_struct_type] = SHIFT(110),
        [ts_sym_interface_type] = SHIFT(110),
        [ts_sym_type_name] = SHIFT(110),
        [ts_sym__identifier] = SHIFT(111),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [113] = {
        [ts_aux_sym_token13] = REDUCE(ts_sym_pointer_type, 2),
    },
    [114] = {
        [ts_aux_sym_token12] = SHIFT(115),
    },
    [115] = {
        [ts_sym_type_expression] = SHIFT(116),
        [ts_sym_pointer_type] = SHIFT(110),
        [ts_sym_map_type] = SHIFT(110),
        [ts_sym_slice_type] = SHIFT(110),
        [ts_sym_struct_type] = SHIFT(110),
        [ts_sym_interface_type] = SHIFT(110),
        [ts_sym_type_name] = SHIFT(110),
        [ts_sym__identifier] = SHIFT(111),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [116] = {
        [ts_aux_sym_token13] = SHIFT(117),
    },
    [117] = {
        [ts_sym_type_expression] = SHIFT(118),
        [ts_sym_pointer_type] = SHIFT(110),
        [ts_sym_map_type] = SHIFT(110),
        [ts_sym_slice_type] = SHIFT(110),
        [ts_sym_struct_type] = SHIFT(110),
        [ts_sym_interface_type] = SHIFT(110),
        [ts_sym_type_name] = SHIFT(110),
        [ts_sym__identifier] = SHIFT(111),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [118] = {
        [ts_aux_sym_token13] = REDUCE(ts_sym_map_type, 5),
    },
    [119] = {
        [ts_aux_sym_token13] = SHIFT(120),
    },
    [120] = {
        [ts_sym_type_expression] = SHIFT(121),
        [ts_sym_pointer_type] = SHIFT(110),
        [ts_sym_map_type] = SHIFT(110),
        [ts_sym_slice_type] = SHIFT(110),
        [ts_sym_struct_type] = SHIFT(110),
        [ts_sym_interface_type] = SHIFT(110),
        [ts_sym_type_name] = SHIFT(110),
        [ts_sym__identifier] = SHIFT(111),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [121] = {
        [ts_aux_sym_token13] = REDUCE(ts_sym_slice_type, 3),
    },
    [122] = {
        [ts_aux_sym_token8] = SHIFT(123),
    },
    [123] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(124),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [124] = {
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [125] = {
        [ts_aux_sym_token13] = REDUCE(ts_sym_struct_type, 4),
    },
    [126] = {
        [ts_aux_sym_token8] = SHIFT(127),
    },
    [127] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(128),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [128] = {
        [ts_aux_sym_token9] = SHIFT(129),
    },
    [129] = {
        [ts_aux_sym_token13] = REDUCE(ts_sym_interface_type, 4),
    },
    [130] = {
        [ts_sym_var_name] = SHIFT(131),
        [ts_sym__identifier] = SHIFT(133),
    },
    [131] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(132),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token12] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token15] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token27] = SHIFT(130),
    },
    [132] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token12] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token15] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [133] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_var_name, 1),
    },
    [134] = {
        [ts_sym_var_name] = SHIFT(135),
        [ts_sym__identifier] = SHIFT(133),
    },
    [135] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(136),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token12] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token15] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token27] = SHIFT(134),
    },
    [136] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token12] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token15] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
    },
    [137] = {
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__identifier] = SHIFT(40),
        [ts_aux_sym_token2] = SHIFT(139),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 2),
    },
    [138] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 3),
    },
    [139] = {
        [ts_sym_var_name] = SHIFT(140),
        [ts_sym_type_name] = SHIFT(143),
        [ts_sym__identifier] = SHIFT(85),
    },
    [140] = {
        [ts_sym_type_name] = SHIFT(141),
        [ts_sym__identifier] = SHIFT(77),
    },
    [141] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(142),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [142] = {
        [ts_aux_sym_token3] = SHIFT(67),
    },
    [143] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(144),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [144] = {
        [ts_aux_sym_token3] = SHIFT(145),
    },
    [145] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 6),
    },
    [146] = {
        [ts_aux_sym_token9] = SHIFT(147),
    },
    [147] = {
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_interface_type, 4),
    },
    [148] = {
        [ts_aux_sym_token9] = SHIFT(149),
    },
    [149] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_struct_type, 4),
    },
    [150] = {
        [ts_aux_sym_token8] = SHIFT(151),
    },
    [151] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(152),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [152] = {
        [ts_aux_sym_token9] = SHIFT(153),
    },
    [153] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_interface_type, 4),
    },
    [154] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_type_name, 1),
    },
    [155] = {
        [ts_sym_var_name] = SHIFT(156),
        [ts_sym__identifier] = SHIFT(173),
    },
    [156] = {
        [ts_aux_sym_token6] = SHIFT(157),
    },
    [157] = {
        [ts_sym_expression] = SHIFT(158),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(170),
        [ts_sym_number] = SHIFT(169),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [158] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_token10] = SHIFT(159),
        [ts_aux_sym_token16] = SHIFT(159),
        [ts_aux_sym_token17] = SHIFT(161),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token19] = SHIFT(163),
        [ts_aux_sym_token20] = SHIFT(165),
        [ts_aux_sym_token21] = SHIFT(167),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = SHIFT(167),
        [ts_aux_sym_token24] = SHIFT(167),
        [ts_aux_sym_token25] = SHIFT(167),
    },
    [159] = {
        [ts_sym_expression] = SHIFT(160),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(170),
        [ts_sym_number] = SHIFT(169),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [160] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token10] = SHIFT(159),
        [ts_aux_sym_token16] = SHIFT(159),
        [ts_aux_sym_token17] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token20] = SHIFT(165),
        [ts_aux_sym_token21] = SHIFT(167),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = SHIFT(167),
        [ts_aux_sym_token24] = SHIFT(167),
        [ts_aux_sym_token25] = SHIFT(167),
    },
    [161] = {
        [ts_sym_expression] = SHIFT(162),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(170),
        [ts_sym_number] = SHIFT(169),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [162] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token10] = SHIFT(159),
        [ts_aux_sym_token16] = SHIFT(159),
        [ts_aux_sym_token17] = SHIFT(161),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token19] = SHIFT(163),
        [ts_aux_sym_token20] = SHIFT(165),
        [ts_aux_sym_token21] = SHIFT(167),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = SHIFT(167),
        [ts_aux_sym_token24] = SHIFT(167),
        [ts_aux_sym_token25] = SHIFT(167),
    },
    [163] = {
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(170),
        [ts_sym_number] = SHIFT(169),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [164] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = SHIFT(159),
        [ts_aux_sym_token16] = SHIFT(159),
        [ts_aux_sym_token17] = SHIFT(161),
        [ts_aux_sym_token18] = SHIFT(161),
        [ts_aux_sym_token19] = SHIFT(163),
        [ts_aux_sym_token20] = SHIFT(165),
        [ts_aux_sym_token21] = SHIFT(167),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = SHIFT(167),
        [ts_aux_sym_token24] = SHIFT(167),
        [ts_aux_sym_token25] = SHIFT(167),
    },
    [165] = {
        [ts_sym_expression] = SHIFT(166),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(170),
        [ts_sym_number] = SHIFT(169),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [166] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = SHIFT(159),
        [ts_aux_sym_token16] = SHIFT(159),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = SHIFT(165),
        [ts_aux_sym_token21] = SHIFT(167),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = SHIFT(167),
        [ts_aux_sym_token24] = SHIFT(167),
        [ts_aux_sym_token25] = SHIFT(167),
    },
    [167] = {
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(170),
        [ts_sym_number] = SHIFT(169),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [168] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token19] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token21] = SHIFT(167),
        [ts_aux_sym_token22] = SHIFT(167),
        [ts_aux_sym_token23] = SHIFT(167),
        [ts_aux_sym_token24] = SHIFT(167),
        [ts_aux_sym_token25] = SHIFT(167),
    },
    [169] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
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
    },
    [170] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token19] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token21] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token22] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token23] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token24] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token25] = REDUCE(ts_sym_var_name, 1),
    },
    [171] = {
        [ts_sym_expression] = SHIFT(172),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(170),
        [ts_sym_number] = SHIFT(169),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [172] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
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
    },
    [173] = {
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),
    },
    [174] = {
        [ts_sym_var_name] = SHIFT(175),
        [ts_sym__identifier] = SHIFT(59),
    },
    [175] = {
        [ts_sym__func_signature] = SHIFT(176),
        [ts_aux_sym_token2] = SHIFT(180),
    },
    [176] = {
        [ts_sym_statement_block] = SHIFT(177),
        [ts_aux_sym_token8] = SHIFT(178),
    },
    [177] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_func_declaration, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_func_declaration, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_func_declaration, 4),
    },
    [178] = {
        [ts_aux_sym_token9] = SHIFT(179),
    },
    [179] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 2),
    },
    [180] = {
        [ts_sym_var_name] = SHIFT(181),
        [ts_sym__identifier] = SHIFT(133),
        [ts_aux_sym_token3] = SHIFT(196),
    },
    [181] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(182),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token12] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token15] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token27] = SHIFT(134),
    },
    [182] = {
        [ts_sym_type_expression] = SHIFT(183),
        [ts_sym_pointer_type] = SHIFT(91),
        [ts_sym_map_type] = SHIFT(91),
        [ts_sym_slice_type] = SHIFT(91),
        [ts_sym_struct_type] = SHIFT(91),
        [ts_sym_interface_type] = SHIFT(91),
        [ts_sym_type_name] = SHIFT(91),
        [ts_sym__identifier] = SHIFT(77),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [183] = {
        [ts_aux_sym__func_signature_repeat2] = SHIFT(184),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token27] = SHIFT(86),
    },
    [184] = {
        [ts_aux_sym_token3] = SHIFT(185),
    },
    [185] = {
        [ts_sym_type_name] = SHIFT(186),
        [ts_sym__identifier] = SHIFT(187),
        [ts_aux_sym_token2] = SHIFT(188),
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 6),
    },
    [186] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 7),
    },
    [187] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym_type_name, 1),
    },
    [188] = {
        [ts_sym_var_name] = SHIFT(189),
        [ts_sym_type_name] = SHIFT(193),
        [ts_sym__identifier] = SHIFT(85),
    },
    [189] = {
        [ts_sym_type_name] = SHIFT(190),
        [ts_sym__identifier] = SHIFT(77),
    },
    [190] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(191),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [191] = {
        [ts_aux_sym_token3] = SHIFT(192),
    },
    [192] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 11),
    },
    [193] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(194),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [194] = {
        [ts_aux_sym_token3] = SHIFT(195),
    },
    [195] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 10),
    },
    [196] = {
        [ts_sym_type_name] = SHIFT(197),
        [ts_sym__identifier] = SHIFT(187),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 2),
    },
    [197] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 3),
    },
    [198] = {
        [ts_sym_var_name] = SHIFT(199),
        [ts_sym_type_name] = SHIFT(202),
        [ts_sym__identifier] = SHIFT(85),
    },
    [199] = {
        [ts_sym_type_name] = SHIFT(200),
        [ts_sym__identifier] = SHIFT(77),
    },
    [200] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(201),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [201] = {
        [ts_aux_sym_token3] = SHIFT(186),
    },
    [202] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(203),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [203] = {
        [ts_aux_sym_token3] = SHIFT(204),
    },
    [204] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 6),
    },
    [205] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
    },
    [206] = {
        [ts_sym_package_name] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(208),
    },
    [207] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_token1] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_package_directive, 2),
    },
    [208] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_package_name, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_golang);
