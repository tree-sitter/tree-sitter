#include "tree_sitter/parser.h"

#define STATE_COUNT 209
#define SYMBOL_COUNT 66

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
    ts_sym_comment = 27,
    ts_aux_sym_program_repeat0 = 28,
    ts_aux_sym_program_repeat1 = 29,
    ts_aux_sym_imports_block_repeat0 = 30,
    ts_aux_sym_struct_type_repeat0 = 31,
    ts_aux_sym_interface_type_repeat0 = 32,
    ts_aux_sym__func_signature_repeat0 = 33,
    ts_aux_sym__func_signature_repeat1 = 34,
    ts_aux_sym__func_signature_repeat2 = 35,
    ts_aux_sym__func_signature_repeat3 = 36,
    ts_aux_sym__func_signature_repeat4 = 37,
    ts_aux_sym_token0 = 38,
    ts_aux_sym_token1 = 39,
    ts_aux_sym_token2 = 40,
    ts_aux_sym_token3 = 41,
    ts_aux_sym_token4 = 42,
    ts_aux_sym_token5 = 43,
    ts_aux_sym_token6 = 44,
    ts_aux_sym_token7 = 45,
    ts_aux_sym_token8 = 46,
    ts_aux_sym_token9 = 47,
    ts_aux_sym_token10 = 48,
    ts_aux_sym_token11 = 49,
    ts_aux_sym_token12 = 50,
    ts_aux_sym_token13 = 51,
    ts_aux_sym_token14 = 52,
    ts_aux_sym_token15 = 53,
    ts_aux_sym_token16 = 54,
    ts_aux_sym_token17 = 55,
    ts_aux_sym_token18 = 56,
    ts_aux_sym_token19 = 57,
    ts_aux_sym_token20 = 58,
    ts_aux_sym_token21 = 59,
    ts_aux_sym_token22 = 60,
    ts_aux_sym_token23 = 61,
    ts_aux_sym_token24 = 62,
    ts_aux_sym_token25 = 63,
    ts_aux_sym_token26 = 64,
    ts_aux_sym_token27 = 65,
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
    [ts_sym_comment] = "comment",
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

UBIQUITOUS_SYMBOLS = {
    [ts_sym_comment] = 1,
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
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == '/')
                ADVANCE(1);
            if (lookahead == 'p')
                ADVANCE(3);
            LEX_ERROR();
        case 1:
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 2:
            if (!(lookahead == '\n'))
                ADVANCE(2);
            ACCEPT_TOKEN(ts_sym_comment);
        case 3:
            if (lookahead == 'a')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (lookahead == 'c')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (lookahead == 'k')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (lookahead == 'a')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (lookahead == 'g')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'e')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 10:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(11);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(1);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 12:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(11);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(12);
            if (lookahead == '/')
                ADVANCE(1);
            if (lookahead == 'f')
                ADVANCE(13);
            if (lookahead == 'i')
                ADVANCE(17);
            if (lookahead == 't')
                ADVANCE(23);
            if (lookahead == 'v')
                ADVANCE(27);
            LEX_ERROR();
        case 13:
            if (lookahead == 'u')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            if (lookahead == 'n')
                ADVANCE(15);
            LEX_ERROR();
        case 15:
            if (lookahead == 'c')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 17:
            if (lookahead == 'm')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            if (lookahead == 'p')
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            if (lookahead == 'o')
                ADVANCE(20);
            LEX_ERROR();
        case 20:
            if (lookahead == 'r')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if (lookahead == 't')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 23:
            if (lookahead == 'y')
                ADVANCE(24);
            LEX_ERROR();
        case 24:
            if (lookahead == 'p')
                ADVANCE(25);
            LEX_ERROR();
        case 25:
            if (lookahead == 'e')
                ADVANCE(26);
            LEX_ERROR();
        case 26:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 27:
            if (lookahead == 'a')
                ADVANCE(28);
            LEX_ERROR();
        case 28:
            if (lookahead == 'r')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 30:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(11);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(30);
            if (lookahead == '/')
                ADVANCE(1);
            if (lookahead == 'f')
                ADVANCE(13);
            if (lookahead == 't')
                ADVANCE(23);
            if (lookahead == 'v')
                ADVANCE(27);
            LEX_ERROR();
        case 31:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(31);
            if (lookahead == '\"')
                ADVANCE(32);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(1);
            LEX_ERROR();
        case 32:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(33);
            if (lookahead == '\\')
                ADVANCE(35);
            LEX_ERROR();
        case 33:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(33);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '\\')
                ADVANCE(35);
            LEX_ERROR();
        case 34:
            ACCEPT_TOKEN(ts_sym_string);
        case 35:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(33);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '\\')
                ADVANCE(35);
            LEX_ERROR();
        case 36:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(33);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '\\')
                ADVANCE(35);
            ACCEPT_TOKEN(ts_sym_string);
        case 37:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 38:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(32);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '/')
                ADVANCE(1);
            LEX_ERROR();
        case 39:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 40:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(40);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '/')
                ADVANCE(1);
            LEX_ERROR();
        case 41:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(41);
            if (lookahead == '/')
                ADVANCE(1);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            LEX_ERROR();
        case 42:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 43:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(43);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '/')
                ADVANCE(1);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '[')
                ADVANCE(45);
            if (lookahead == 'i')
                ADVANCE(46);
            if (lookahead == 'm')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(58);
            LEX_ERROR();
        case 44:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 45:
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 46:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 't')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'e')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'r')
                ADVANCE(50);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'f')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'a')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'c')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'e')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            ACCEPT_TOKEN(ts_aux_sym_token15);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'a')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'p')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 't')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'r')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'u')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'c')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 't')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            ACCEPT_TOKEN(ts_aux_sym_token14);
        case 64:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == '/')
                ADVANCE(1);
            if (lookahead == '[')
                ADVANCE(45);
            LEX_ERROR();
        case 65:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(65);
            if (lookahead == '/')
                ADVANCE(1);
            if (lookahead == ']')
                ADVANCE(66);
            LEX_ERROR();
        case 66:
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 67:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (lookahead == '/')
                ADVANCE(1);
            if (lookahead == '{')
                ADVANCE(68);
            LEX_ERROR();
        case 68:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 69:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '/')
                ADVANCE(1);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 70:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 71:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == '/')
                ADVANCE(1);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 72:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(72);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(1);
            LEX_ERROR();
        case 73:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '/')
                ADVANCE(1);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            LEX_ERROR();
        case 74:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(74);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == ',')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(1);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '[')
                ADVANCE(45);
            if (lookahead == 'i')
                ADVANCE(46);
            if (lookahead == 'm')
                ADVANCE(55);
            if (lookahead == 's')
                ADVANCE(58);
            LEX_ERROR();
        case 75:
            ACCEPT_TOKEN(ts_aux_sym_token27);
        case 76:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == ',')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(1);
            LEX_ERROR();
        case 77:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(1);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 78:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == ',')
                ADVANCE(75);
            if (lookahead == '/')
                ADVANCE(1);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == '/')
                ADVANCE(1);
            if (lookahead == '=')
                ADVANCE(80);
            LEX_ERROR();
        case 80:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 81:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == '!')
                ADVANCE(82);
            if (lookahead == '/')
                ADVANCE(1);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(83);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            LEX_ERROR();
        case 82:
            ACCEPT_TOKEN(ts_aux_sym_token26);
        case 83:
            if (lookahead == '.')
                ADVANCE(84);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(83);
            ACCEPT_TOKEN(ts_sym_number);
        case 84:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            LEX_ERROR();
        case 85:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            ACCEPT_TOKEN(ts_sym_number);
        case 86:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(11);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(86);
            if (lookahead == '&')
                ADVANCE(87);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(89);
            if (lookahead == '-')
                ADVANCE(90);
            if (lookahead == '/')
                ADVANCE(91);
            if (lookahead == '<')
                ADVANCE(92);
            if (lookahead == '=')
                ADVANCE(94);
            if (lookahead == '>')
                ADVANCE(96);
            if (lookahead == 'f')
                ADVANCE(13);
            if (lookahead == 't')
                ADVANCE(23);
            if (lookahead == 'v')
                ADVANCE(27);
            if (lookahead == '|')
                ADVANCE(98);
            LEX_ERROR();
        case 87:
            if (lookahead == '&')
                ADVANCE(88);
            LEX_ERROR();
        case 88:
            ACCEPT_TOKEN(ts_aux_sym_token20);
        case 89:
            ACCEPT_TOKEN(ts_aux_sym_token17);
        case 90:
            ACCEPT_TOKEN(ts_aux_sym_token18);
        case 91:
            if (lookahead == '/')
                ADVANCE(2);
            ACCEPT_TOKEN(ts_aux_sym_token16);
        case 92:
            if (lookahead == '=')
                ADVANCE(93);
            ACCEPT_TOKEN(ts_aux_sym_token23);
        case 93:
            ACCEPT_TOKEN(ts_aux_sym_token22);
        case 94:
            if (lookahead == '=')
                ADVANCE(95);
            LEX_ERROR();
        case 95:
            ACCEPT_TOKEN(ts_aux_sym_token21);
        case 96:
            if (lookahead == '=')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_aux_sym_token25);
        case 97:
            ACCEPT_TOKEN(ts_aux_sym_token24);
        case 98:
            if (lookahead == '|')
                ADVANCE(99);
            LEX_ERROR();
        case 99:
            ACCEPT_TOKEN(ts_aux_sym_token19);
        case 100:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(1);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '{')
                ADVANCE(68);
            LEX_ERROR();
        case 101:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(11);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '!')
                ADVANCE(82);
            if (lookahead == '\"')
                ADVANCE(32);
            if (lookahead == '&')
                ADVANCE(87);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(89);
            if (lookahead == ',')
                ADVANCE(75);
            if (lookahead == '-')
                ADVANCE(90);
            if (lookahead == '/')
                ADVANCE(91);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(83);
            if (lookahead == '<')
                ADVANCE(92);
            if (lookahead == '=')
                ADVANCE(102);
            if (lookahead == '>')
                ADVANCE(96);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '[')
                ADVANCE(45);
            if (lookahead == ']')
                ADVANCE(66);
            if (lookahead == 'f')
                ADVANCE(103);
            if (lookahead == 'i')
                ADVANCE(107);
            if (lookahead == 'm')
                ADVANCE(55);
            if (lookahead == 'p')
                ADVANCE(113);
            if (lookahead == 's')
                ADVANCE(58);
            if (lookahead == 't')
                ADVANCE(120);
            if (lookahead == 'v')
                ADVANCE(124);
            if (lookahead == '{')
                ADVANCE(68);
            if (lookahead == '|')
                ADVANCE(98);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        case 102:
            if (lookahead == '=')
                ADVANCE(95);
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'u')
                ADVANCE(104);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 104:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(105);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 105:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'c')
                ADVANCE(106);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 106:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 107:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'm')
                ADVANCE(108);
            if (lookahead == 'n')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 108:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'p')
                ADVANCE(109);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 109:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'o')
                ADVANCE(110);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 110:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'r')
                ADVANCE(111);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 111:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 't')
                ADVANCE(112);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 112:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 113:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'a')
                ADVANCE(114);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 114:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'c')
                ADVANCE(115);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 115:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'k')
                ADVANCE(116);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 116:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'a')
                ADVANCE(117);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 117:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'g')
                ADVANCE(118);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 118:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'e')
                ADVANCE(119);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 119:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 120:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(42);
            if (lookahead == 'y')
                ADVANCE(121);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 121:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'p')
                ADVANCE(122);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 122:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'e')
                ADVANCE(123);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 123:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'a')
                ADVANCE(125);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'r')
                ADVANCE(126);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 126:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(11);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(101);
            if (lookahead == '!')
                ADVANCE(82);
            if (lookahead == '\"')
                ADVANCE(32);
            if (lookahead == '&')
                ADVANCE(87);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(89);
            if (lookahead == ',')
                ADVANCE(75);
            if (lookahead == '-')
                ADVANCE(90);
            if (lookahead == '/')
                ADVANCE(91);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(83);
            if (lookahead == '<')
                ADVANCE(92);
            if (lookahead == '=')
                ADVANCE(102);
            if (lookahead == '>')
                ADVANCE(96);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '[')
                ADVANCE(45);
            if (lookahead == ']')
                ADVANCE(66);
            if (lookahead == 'f')
                ADVANCE(103);
            if (lookahead == 'i')
                ADVANCE(107);
            if (lookahead == 'm')
                ADVANCE(55);
            if (lookahead == 'p')
                ADVANCE(113);
            if (lookahead == 's')
                ADVANCE(58);
            if (lookahead == 't')
                ADVANCE(120);
            if (lookahead == 'v')
                ADVANCE(124);
            if (lookahead == '{')
                ADVANCE(68);
            if (lookahead == '|')
                ADVANCE(98);
            if (lookahead == '}')
                ADVANCE(70);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 0,
    [1] = 10,
    [2] = 12,
    [3] = 12,
    [4] = 30,
    [5] = 31,
    [6] = 12,
    [7] = 12,
    [8] = 38,
    [9] = 38,
    [10] = 38,
    [11] = 40,
    [12] = 40,
    [13] = 12,
    [14] = 30,
    [15] = 30,
    [16] = 30,
    [17] = 10,
    [18] = 41,
    [19] = 43,
    [20] = 30,
    [21] = 30,
    [22] = 30,
    [23] = 43,
    [24] = 30,
    [25] = 64,
    [26] = 43,
    [27] = 65,
    [28] = 43,
    [29] = 30,
    [30] = 65,
    [31] = 43,
    [32] = 30,
    [33] = 67,
    [34] = 69,
    [35] = 43,
    [36] = 69,
    [37] = 43,
    [38] = 71,
    [39] = 69,
    [40] = 69,
    [41] = 43,
    [42] = 69,
    [43] = 64,
    [44] = 43,
    [45] = 65,
    [46] = 43,
    [47] = 69,
    [48] = 65,
    [49] = 43,
    [50] = 69,
    [51] = 67,
    [52] = 69,
    [53] = 71,
    [54] = 69,
    [55] = 67,
    [56] = 69,
    [57] = 72,
    [58] = 69,
    [59] = 72,
    [60] = 71,
    [61] = 73,
    [62] = 74,
    [63] = 43,
    [64] = 76,
    [65] = 40,
    [66] = 77,
    [67] = 69,
    [68] = 41,
    [69] = 41,
    [70] = 76,
    [71] = 40,
    [72] = 69,
    [73] = 41,
    [74] = 41,
    [75] = 76,
    [76] = 40,
    [77] = 76,
    [78] = 41,
    [79] = 76,
    [80] = 40,
    [81] = 69,
    [82] = 41,
    [83] = 76,
    [84] = 40,
    [85] = 78,
    [86] = 41,
    [87] = 74,
    [88] = 43,
    [89] = 76,
    [90] = 40,
    [91] = 76,
    [92] = 43,
    [93] = 76,
    [94] = 64,
    [95] = 43,
    [96] = 65,
    [97] = 43,
    [98] = 76,
    [99] = 65,
    [100] = 43,
    [101] = 76,
    [102] = 67,
    [103] = 69,
    [104] = 71,
    [105] = 76,
    [106] = 67,
    [107] = 69,
    [108] = 71,
    [109] = 76,
    [110] = 65,
    [111] = 65,
    [112] = 43,
    [113] = 65,
    [114] = 64,
    [115] = 43,
    [116] = 65,
    [117] = 43,
    [118] = 65,
    [119] = 65,
    [120] = 43,
    [121] = 65,
    [122] = 67,
    [123] = 69,
    [124] = 71,
    [125] = 65,
    [126] = 67,
    [127] = 69,
    [128] = 71,
    [129] = 65,
    [130] = 41,
    [131] = 74,
    [132] = 43,
    [133] = 74,
    [134] = 41,
    [135] = 74,
    [136] = 43,
    [137] = 77,
    [138] = 69,
    [139] = 41,
    [140] = 41,
    [141] = 76,
    [142] = 40,
    [143] = 76,
    [144] = 40,
    [145] = 69,
    [146] = 71,
    [147] = 69,
    [148] = 71,
    [149] = 30,
    [150] = 67,
    [151] = 69,
    [152] = 71,
    [153] = 30,
    [154] = 43,
    [155] = 41,
    [156] = 79,
    [157] = 81,
    [158] = 86,
    [159] = 81,
    [160] = 86,
    [161] = 81,
    [162] = 86,
    [163] = 81,
    [164] = 86,
    [165] = 81,
    [166] = 86,
    [167] = 81,
    [168] = 86,
    [169] = 86,
    [170] = 86,
    [171] = 81,
    [172] = 86,
    [173] = 79,
    [174] = 41,
    [175] = 72,
    [176] = 67,
    [177] = 30,
    [178] = 71,
    [179] = 30,
    [180] = 73,
    [181] = 74,
    [182] = 43,
    [183] = 76,
    [184] = 40,
    [185] = 100,
    [186] = 67,
    [187] = 67,
    [188] = 41,
    [189] = 41,
    [190] = 76,
    [191] = 40,
    [192] = 67,
    [193] = 76,
    [194] = 40,
    [195] = 67,
    [196] = 100,
    [197] = 67,
    [198] = 41,
    [199] = 41,
    [200] = 76,
    [201] = 40,
    [202] = 76,
    [203] = 40,
    [204] = 67,
    [205] = 10,
    [206] = 41,
    [207] = 12,
    [208] = 12,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_program] = SHIFT(1),
        [ts_sym_package_directive] = SHIFT(2),
        [ts_sym_comment] = SHIFT(0),
        [ts_aux_sym_token0] = SHIFT(206),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
        [ts_sym_comment] = SHIFT(1),
    },
    [2] = {
        [ts_sym_imports_block] = SHIFT(3),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym_comment] = SHIFT(2),
        [ts_aux_sym_program_repeat0] = SHIFT(14),
        [ts_aux_sym_token1] = SHIFT(5),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [3] = {
        [ts_sym_imports_block] = SHIFT(3),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym_comment] = SHIFT(3),
        [ts_aux_sym_program_repeat0] = SHIFT(4),
        [ts_aux_sym_token1] = SHIFT(5),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [4] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym_comment] = SHIFT(4),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [5] = {
        [ts_sym_package_import] = SHIFT(6),
        [ts_sym_string] = SHIFT(7),
        [ts_sym_comment] = SHIFT(5),
        [ts_aux_sym_token2] = SHIFT(8),
    },
    [6] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym_comment] = SHIFT(6),
        [ts_aux_sym_token1] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_imports_block, 2),
    },
    [7] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_comment] = SHIFT(7),
        [ts_aux_sym_token1] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_package_import, 1),
    },
    [8] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_builtin_sym_error] = SHIFT(12),
        [ts_sym_string] = SHIFT(10),
        [ts_sym_comment] = SHIFT(8),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(12),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [9] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_sym_string] = SHIFT(10),
        [ts_sym_comment] = SHIFT(9),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(11),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [10] = {
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_comment] = SHIFT(10),
        [ts_aux_sym_token3] = REDUCE(ts_sym_package_import, 1),
    },
    [11] = {
        [ts_sym_comment] = SHIFT(11),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym_imports_block_repeat0, 2),
    },
    [12] = {
        [ts_sym_comment] = SHIFT(12),
        [ts_aux_sym_token3] = SHIFT(13),
    },
    [13] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym_comment] = SHIFT(13),
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
        [ts_sym_comment] = SHIFT(14),
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
        [ts_sym_comment] = SHIFT(15),
        [ts_aux_sym_program_repeat1] = SHIFT(17),
        [ts_aux_sym_token4] = SHIFT(18),
        [ts_aux_sym_token5] = SHIFT(155),
        [ts_aux_sym_token7] = SHIFT(174),
    },
    [16] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_sym_comment] = SHIFT(16),
        [ts_aux_sym_token4] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_declaration, 1),
    },
    [17] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_sym_comment] = SHIFT(17),
    },
    [18] = {
        [ts_sym_type_name] = SHIFT(19),
        [ts_sym__identifier] = SHIFT(154),
        [ts_sym_comment] = SHIFT(18),
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
        [ts_sym_comment] = SHIFT(19),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(30),
        [ts_aux_sym_token14] = SHIFT(33),
        [ts_aux_sym_token15] = SHIFT(150),
    },
    [20] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 3),
        [ts_sym_comment] = SHIFT(20),
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_declaration, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_declaration, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_declaration, 3),
    },
    [21] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT(21),
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_expression, 1),
    },
    [22] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT(22),
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
        [ts_sym_comment] = SHIFT(23),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(30),
        [ts_aux_sym_token14] = SHIFT(33),
        [ts_aux_sym_token15] = SHIFT(150),
    },
    [24] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT(24),
        [ts_aux_sym_token4] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_pointer_type, 2),
    },
    [25] = {
        [ts_sym_comment] = SHIFT(25),
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
        [ts_sym_comment] = SHIFT(26),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [27] = {
        [ts_sym_comment] = SHIFT(27),
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
        [ts_sym_comment] = SHIFT(28),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(30),
        [ts_aux_sym_token14] = SHIFT(33),
        [ts_aux_sym_token15] = SHIFT(150),
    },
    [29] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT(29),
        [ts_aux_sym_token4] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token7] = REDUCE(ts_sym_map_type, 5),
    },
    [30] = {
        [ts_sym_comment] = SHIFT(30),
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
        [ts_sym_comment] = SHIFT(31),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(30),
        [ts_aux_sym_token14] = SHIFT(33),
        [ts_aux_sym_token15] = SHIFT(150),
    },
    [32] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT(32),
        [ts_aux_sym_token4] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token7] = REDUCE(ts_sym_slice_type, 3),
    },
    [33] = {
        [ts_sym_comment] = SHIFT(33),
        [ts_aux_sym_token8] = SHIFT(34),
    },
    [34] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_sym_comment] = SHIFT(34),
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
        [ts_sym_comment] = SHIFT(35),
        [ts_aux_sym_token10] = SHIFT(41),
        [ts_aux_sym_token11] = SHIFT(43),
        [ts_aux_sym_token12] = SHIFT(48),
        [ts_aux_sym_token14] = SHIFT(51),
        [ts_aux_sym_token15] = SHIFT(55),
    },
    [36] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_sym_comment] = SHIFT(36),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(38),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [37] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(37),
        [ts_aux_sym_token10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_name, 1),
    },
    [38] = {
        [ts_sym_comment] = SHIFT(38),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 3),
    },
    [39] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT(39),
        [ts_aux_sym_token9] = REDUCE(ts_sym_type_expression, 1),
    },
    [40] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT(40),
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
        [ts_sym_comment] = SHIFT(41),
        [ts_aux_sym_token10] = SHIFT(41),
        [ts_aux_sym_token11] = SHIFT(43),
        [ts_aux_sym_token12] = SHIFT(48),
        [ts_aux_sym_token14] = SHIFT(51),
        [ts_aux_sym_token15] = SHIFT(55),
    },
    [42] = {
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT(42),
        [ts_aux_sym_token9] = REDUCE(ts_sym_pointer_type, 2),
    },
    [43] = {
        [ts_sym_comment] = SHIFT(43),
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
        [ts_sym_comment] = SHIFT(44),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [45] = {
        [ts_sym_comment] = SHIFT(45),
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
        [ts_sym_comment] = SHIFT(46),
        [ts_aux_sym_token10] = SHIFT(41),
        [ts_aux_sym_token11] = SHIFT(43),
        [ts_aux_sym_token12] = SHIFT(48),
        [ts_aux_sym_token14] = SHIFT(51),
        [ts_aux_sym_token15] = SHIFT(55),
    },
    [47] = {
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT(47),
        [ts_aux_sym_token9] = REDUCE(ts_sym_map_type, 5),
    },
    [48] = {
        [ts_sym_comment] = SHIFT(48),
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
        [ts_sym_comment] = SHIFT(49),
        [ts_aux_sym_token10] = SHIFT(41),
        [ts_aux_sym_token11] = SHIFT(43),
        [ts_aux_sym_token12] = SHIFT(48),
        [ts_aux_sym_token14] = SHIFT(51),
        [ts_aux_sym_token15] = SHIFT(55),
    },
    [50] = {
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT(50),
        [ts_aux_sym_token9] = REDUCE(ts_sym_slice_type, 3),
    },
    [51] = {
        [ts_sym_comment] = SHIFT(51),
        [ts_aux_sym_token8] = SHIFT(52),
    },
    [52] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_sym_comment] = SHIFT(52),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(53),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [53] = {
        [ts_sym_comment] = SHIFT(53),
        [ts_aux_sym_token9] = SHIFT(54),
    },
    [54] = {
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT(54),
        [ts_aux_sym_token9] = REDUCE(ts_sym_struct_type, 4),
    },
    [55] = {
        [ts_sym_comment] = SHIFT(55),
        [ts_aux_sym_token8] = SHIFT(56),
    },
    [56] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_sym_comment] = SHIFT(56),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(146),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [57] = {
        [ts_sym__func_signature] = SHIFT(58),
        [ts_sym_comment] = SHIFT(57),
        [ts_aux_sym_token2] = SHIFT(61),
    },
    [58] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_sym_comment] = SHIFT(58),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(60),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [59] = {
        [ts_sym_comment] = SHIFT(59),
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_name, 1),
    },
    [60] = {
        [ts_sym_comment] = SHIFT(60),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [61] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__identifier] = SHIFT(133),
        [ts_sym_comment] = SHIFT(61),
        [ts_aux_sym_token3] = SHIFT(137),
    },
    [62] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT(62),
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
        [ts_sym_comment] = SHIFT(63),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [64] = {
        [ts_sym_comment] = SHIFT(64),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(65),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token27] = SHIFT(86),
    },
    [65] = {
        [ts_sym_comment] = SHIFT(65),
        [ts_aux_sym_token3] = SHIFT(66),
    },
    [66] = {
        [ts_sym_type_name] = SHIFT(67),
        [ts_sym__identifier] = SHIFT(40),
        [ts_sym_comment] = SHIFT(66),
        [ts_aux_sym_token2] = SHIFT(68),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 6),
    },
    [67] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_sym_comment] = SHIFT(67),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 7),
    },
    [68] = {
        [ts_sym_var_name] = SHIFT(69),
        [ts_sym_type_name] = SHIFT(79),
        [ts_sym__identifier] = SHIFT(85),
        [ts_sym_comment] = SHIFT(68),
    },
    [69] = {
        [ts_sym_type_name] = SHIFT(70),
        [ts_sym__identifier] = SHIFT(77),
        [ts_sym_comment] = SHIFT(69),
    },
    [70] = {
        [ts_sym_comment] = SHIFT(70),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(71),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [71] = {
        [ts_sym_comment] = SHIFT(71),
        [ts_aux_sym_token3] = SHIFT(72),
    },
    [72] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_sym_comment] = SHIFT(72),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 11),
    },
    [73] = {
        [ts_sym_var_name] = SHIFT(74),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(73),
    },
    [74] = {
        [ts_sym_type_name] = SHIFT(75),
        [ts_sym__identifier] = SHIFT(77),
        [ts_sym_comment] = SHIFT(74),
    },
    [75] = {
        [ts_sym_comment] = SHIFT(75),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(76),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [76] = {
        [ts_sym_comment] = SHIFT(76),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [77] = {
        [ts_sym_comment] = SHIFT(77),
        [ts_aux_sym_token3] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_type_name, 1),
    },
    [78] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(78),
    },
    [79] = {
        [ts_sym_comment] = SHIFT(79),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(80),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [80] = {
        [ts_sym_comment] = SHIFT(80),
        [ts_aux_sym_token3] = SHIFT(81),
    },
    [81] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_sym_comment] = SHIFT(81),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 10),
    },
    [82] = {
        [ts_sym_type_name] = SHIFT(83),
        [ts_sym__identifier] = SHIFT(77),
        [ts_sym_comment] = SHIFT(82),
    },
    [83] = {
        [ts_sym_comment] = SHIFT(83),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(84),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [84] = {
        [ts_sym_comment] = SHIFT(84),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [85] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(85),
        [ts_aux_sym_token3] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token27] = REDUCE(ts_sym_type_name, 1),
    },
    [86] = {
        [ts_sym_var_name] = SHIFT(87),
        [ts_sym__identifier] = SHIFT(133),
        [ts_sym_comment] = SHIFT(86),
    },
    [87] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym_comment] = SHIFT(87),
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
        [ts_sym_comment] = SHIFT(88),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [89] = {
        [ts_sym_comment] = SHIFT(89),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(90),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token27] = SHIFT(86),
    },
    [90] = {
        [ts_sym_comment] = SHIFT(90),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [91] = {
        [ts_sym_comment] = SHIFT(91),
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
        [ts_sym_comment] = SHIFT(92),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [93] = {
        [ts_sym_comment] = SHIFT(93),
        [ts_aux_sym_token3] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token27] = REDUCE(ts_sym_pointer_type, 2),
    },
    [94] = {
        [ts_sym_comment] = SHIFT(94),
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
        [ts_sym_comment] = SHIFT(95),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [96] = {
        [ts_sym_comment] = SHIFT(96),
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
        [ts_sym_comment] = SHIFT(97),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [98] = {
        [ts_sym_comment] = SHIFT(98),
        [ts_aux_sym_token3] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token27] = REDUCE(ts_sym_map_type, 5),
    },
    [99] = {
        [ts_sym_comment] = SHIFT(99),
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
        [ts_sym_comment] = SHIFT(100),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [101] = {
        [ts_sym_comment] = SHIFT(101),
        [ts_aux_sym_token3] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token27] = REDUCE(ts_sym_slice_type, 3),
    },
    [102] = {
        [ts_sym_comment] = SHIFT(102),
        [ts_aux_sym_token8] = SHIFT(103),
    },
    [103] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_sym_comment] = SHIFT(103),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(104),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [104] = {
        [ts_sym_comment] = SHIFT(104),
        [ts_aux_sym_token9] = SHIFT(105),
    },
    [105] = {
        [ts_sym_comment] = SHIFT(105),
        [ts_aux_sym_token3] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token27] = REDUCE(ts_sym_struct_type, 4),
    },
    [106] = {
        [ts_sym_comment] = SHIFT(106),
        [ts_aux_sym_token8] = SHIFT(107),
    },
    [107] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_sym_comment] = SHIFT(107),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(108),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [108] = {
        [ts_sym_comment] = SHIFT(108),
        [ts_aux_sym_token9] = SHIFT(109),
    },
    [109] = {
        [ts_sym_comment] = SHIFT(109),
        [ts_aux_sym_token3] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token27] = REDUCE(ts_sym_interface_type, 4),
    },
    [110] = {
        [ts_sym_comment] = SHIFT(110),
        [ts_aux_sym_token13] = REDUCE(ts_sym_type_expression, 1),
    },
    [111] = {
        [ts_sym_comment] = SHIFT(111),
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
        [ts_sym_comment] = SHIFT(112),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [113] = {
        [ts_sym_comment] = SHIFT(113),
        [ts_aux_sym_token13] = REDUCE(ts_sym_pointer_type, 2),
    },
    [114] = {
        [ts_sym_comment] = SHIFT(114),
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
        [ts_sym_comment] = SHIFT(115),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [116] = {
        [ts_sym_comment] = SHIFT(116),
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
        [ts_sym_comment] = SHIFT(117),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [118] = {
        [ts_sym_comment] = SHIFT(118),
        [ts_aux_sym_token13] = REDUCE(ts_sym_map_type, 5),
    },
    [119] = {
        [ts_sym_comment] = SHIFT(119),
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
        [ts_sym_comment] = SHIFT(120),
        [ts_aux_sym_token10] = SHIFT(112),
        [ts_aux_sym_token11] = SHIFT(114),
        [ts_aux_sym_token12] = SHIFT(119),
        [ts_aux_sym_token14] = SHIFT(122),
        [ts_aux_sym_token15] = SHIFT(126),
    },
    [121] = {
        [ts_sym_comment] = SHIFT(121),
        [ts_aux_sym_token13] = REDUCE(ts_sym_slice_type, 3),
    },
    [122] = {
        [ts_sym_comment] = SHIFT(122),
        [ts_aux_sym_token8] = SHIFT(123),
    },
    [123] = {
        [ts_sym_var_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(37),
        [ts_sym_comment] = SHIFT(123),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(124),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [124] = {
        [ts_sym_comment] = SHIFT(124),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [125] = {
        [ts_sym_comment] = SHIFT(125),
        [ts_aux_sym_token13] = REDUCE(ts_sym_struct_type, 4),
    },
    [126] = {
        [ts_sym_comment] = SHIFT(126),
        [ts_aux_sym_token8] = SHIFT(127),
    },
    [127] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_sym_comment] = SHIFT(127),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(128),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [128] = {
        [ts_sym_comment] = SHIFT(128),
        [ts_aux_sym_token9] = SHIFT(129),
    },
    [129] = {
        [ts_sym_comment] = SHIFT(129),
        [ts_aux_sym_token13] = REDUCE(ts_sym_interface_type, 4),
    },
    [130] = {
        [ts_sym_var_name] = SHIFT(131),
        [ts_sym__identifier] = SHIFT(133),
        [ts_sym_comment] = SHIFT(130),
    },
    [131] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym_comment] = SHIFT(131),
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
        [ts_sym_comment] = SHIFT(132),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token12] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token15] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [133] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(133),
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
        [ts_sym_comment] = SHIFT(134),
    },
    [135] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT(135),
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
        [ts_sym_comment] = SHIFT(136),
        [ts_aux_sym_token10] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token11] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token12] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token14] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token15] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
    },
    [137] = {
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__identifier] = SHIFT(40),
        [ts_sym_comment] = SHIFT(137),
        [ts_aux_sym_token2] = SHIFT(139),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 2),
    },
    [138] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_sym_comment] = SHIFT(138),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 3),
    },
    [139] = {
        [ts_sym_var_name] = SHIFT(140),
        [ts_sym_type_name] = SHIFT(143),
        [ts_sym__identifier] = SHIFT(85),
        [ts_sym_comment] = SHIFT(139),
    },
    [140] = {
        [ts_sym_type_name] = SHIFT(141),
        [ts_sym__identifier] = SHIFT(77),
        [ts_sym_comment] = SHIFT(140),
    },
    [141] = {
        [ts_sym_comment] = SHIFT(141),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(142),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [142] = {
        [ts_sym_comment] = SHIFT(142),
        [ts_aux_sym_token3] = SHIFT(67),
    },
    [143] = {
        [ts_sym_comment] = SHIFT(143),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(144),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [144] = {
        [ts_sym_comment] = SHIFT(144),
        [ts_aux_sym_token3] = SHIFT(145),
    },
    [145] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym_comment] = SHIFT(145),
        [ts_aux_sym_token9] = REDUCE(ts_sym__func_signature, 6),
    },
    [146] = {
        [ts_sym_comment] = SHIFT(146),
        [ts_aux_sym_token9] = SHIFT(147),
    },
    [147] = {
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT(147),
        [ts_aux_sym_token9] = REDUCE(ts_sym_interface_type, 4),
    },
    [148] = {
        [ts_sym_comment] = SHIFT(148),
        [ts_aux_sym_token9] = SHIFT(149),
    },
    [149] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT(149),
        [ts_aux_sym_token4] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_struct_type, 4),
    },
    [150] = {
        [ts_sym_comment] = SHIFT(150),
        [ts_aux_sym_token8] = SHIFT(151),
    },
    [151] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
        [ts_sym_comment] = SHIFT(151),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(152),
        [ts_aux_sym_token9] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [152] = {
        [ts_sym_comment] = SHIFT(152),
        [ts_aux_sym_token9] = SHIFT(153),
    },
    [153] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT(153),
        [ts_aux_sym_token4] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_interface_type, 4),
    },
    [154] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT(154),
        [ts_aux_sym_token10] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_type_name, 1),
    },
    [155] = {
        [ts_sym_var_name] = SHIFT(156),
        [ts_sym__identifier] = SHIFT(173),
        [ts_sym_comment] = SHIFT(155),
    },
    [156] = {
        [ts_sym_comment] = SHIFT(156),
        [ts_aux_sym_token6] = SHIFT(157),
    },
    [157] = {
        [ts_sym_expression] = SHIFT(158),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(170),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT(157),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [158] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_comment] = SHIFT(158),
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
        [ts_sym_comment] = SHIFT(159),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [160] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT(160),
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
        [ts_sym_comment] = SHIFT(161),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [162] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT(162),
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
        [ts_sym_comment] = SHIFT(163),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [164] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(164),
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
        [ts_sym_comment] = SHIFT(165),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [166] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(166),
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
        [ts_sym_comment] = SHIFT(167),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [168] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(168),
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
        [ts_sym_comment] = SHIFT(169),
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
        [ts_sym_comment] = SHIFT(170),
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
        [ts_sym_comment] = SHIFT(171),
        [ts_aux_sym_token26] = SHIFT(171),
    },
    [172] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym_comment] = SHIFT(172),
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
        [ts_sym_comment] = SHIFT(173),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),
    },
    [174] = {
        [ts_sym_var_name] = SHIFT(175),
        [ts_sym__identifier] = SHIFT(59),
        [ts_sym_comment] = SHIFT(174),
    },
    [175] = {
        [ts_sym__func_signature] = SHIFT(176),
        [ts_sym_comment] = SHIFT(175),
        [ts_aux_sym_token2] = SHIFT(180),
    },
    [176] = {
        [ts_sym_statement_block] = SHIFT(177),
        [ts_sym_comment] = SHIFT(176),
        [ts_aux_sym_token8] = SHIFT(178),
    },
    [177] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 4),
        [ts_sym_comment] = SHIFT(177),
        [ts_aux_sym_token4] = REDUCE(ts_sym_func_declaration, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_func_declaration, 4),
        [ts_aux_sym_token7] = REDUCE(ts_sym_func_declaration, 4),
    },
    [178] = {
        [ts_sym_comment] = SHIFT(178),
        [ts_aux_sym_token9] = SHIFT(179),
    },
    [179] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 2),
        [ts_sym_comment] = SHIFT(179),
        [ts_aux_sym_token4] = REDUCE(ts_sym_statement_block, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_statement_block, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_statement_block, 2),
    },
    [180] = {
        [ts_sym_var_name] = SHIFT(181),
        [ts_sym__identifier] = SHIFT(133),
        [ts_sym_comment] = SHIFT(180),
        [ts_aux_sym_token3] = SHIFT(196),
    },
    [181] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT(181),
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
        [ts_sym_comment] = SHIFT(182),
        [ts_aux_sym_token10] = SHIFT(92),
        [ts_aux_sym_token11] = SHIFT(94),
        [ts_aux_sym_token12] = SHIFT(99),
        [ts_aux_sym_token14] = SHIFT(102),
        [ts_aux_sym_token15] = SHIFT(106),
    },
    [183] = {
        [ts_sym_comment] = SHIFT(183),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(184),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token27] = SHIFT(86),
    },
    [184] = {
        [ts_sym_comment] = SHIFT(184),
        [ts_aux_sym_token3] = SHIFT(185),
    },
    [185] = {
        [ts_sym_type_name] = SHIFT(186),
        [ts_sym__identifier] = SHIFT(187),
        [ts_sym_comment] = SHIFT(185),
        [ts_aux_sym_token2] = SHIFT(188),
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 6),
    },
    [186] = {
        [ts_sym_comment] = SHIFT(186),
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 7),
    },
    [187] = {
        [ts_sym_comment] = SHIFT(187),
        [ts_aux_sym_token8] = REDUCE(ts_sym_type_name, 1),
    },
    [188] = {
        [ts_sym_var_name] = SHIFT(189),
        [ts_sym_type_name] = SHIFT(193),
        [ts_sym__identifier] = SHIFT(85),
        [ts_sym_comment] = SHIFT(188),
    },
    [189] = {
        [ts_sym_type_name] = SHIFT(190),
        [ts_sym__identifier] = SHIFT(77),
        [ts_sym_comment] = SHIFT(189),
    },
    [190] = {
        [ts_sym_comment] = SHIFT(190),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(191),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [191] = {
        [ts_sym_comment] = SHIFT(191),
        [ts_aux_sym_token3] = SHIFT(192),
    },
    [192] = {
        [ts_sym_comment] = SHIFT(192),
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 11),
    },
    [193] = {
        [ts_sym_comment] = SHIFT(193),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(194),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [194] = {
        [ts_sym_comment] = SHIFT(194),
        [ts_aux_sym_token3] = SHIFT(195),
    },
    [195] = {
        [ts_sym_comment] = SHIFT(195),
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 10),
    },
    [196] = {
        [ts_sym_type_name] = SHIFT(197),
        [ts_sym__identifier] = SHIFT(187),
        [ts_sym_comment] = SHIFT(196),
        [ts_aux_sym_token2] = SHIFT(198),
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 2),
    },
    [197] = {
        [ts_sym_comment] = SHIFT(197),
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 3),
    },
    [198] = {
        [ts_sym_var_name] = SHIFT(199),
        [ts_sym_type_name] = SHIFT(202),
        [ts_sym__identifier] = SHIFT(85),
        [ts_sym_comment] = SHIFT(198),
    },
    [199] = {
        [ts_sym_type_name] = SHIFT(200),
        [ts_sym__identifier] = SHIFT(77),
        [ts_sym_comment] = SHIFT(199),
    },
    [200] = {
        [ts_sym_comment] = SHIFT(200),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(201),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token27] = SHIFT(73),
    },
    [201] = {
        [ts_sym_comment] = SHIFT(201),
        [ts_aux_sym_token3] = SHIFT(186),
    },
    [202] = {
        [ts_sym_comment] = SHIFT(202),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(203),
        [ts_aux_sym_token3] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token27] = SHIFT(82),
    },
    [203] = {
        [ts_sym_comment] = SHIFT(203),
        [ts_aux_sym_token3] = SHIFT(204),
    },
    [204] = {
        [ts_sym_comment] = SHIFT(204),
        [ts_aux_sym_token8] = REDUCE(ts_sym__func_signature, 6),
    },
    [205] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
        [ts_sym_comment] = SHIFT(205),
    },
    [206] = {
        [ts_sym_package_name] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(208),
        [ts_sym_comment] = SHIFT(206),
    },
    [207] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym_comment] = SHIFT(207),
        [ts_aux_sym_token1] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_token7] = REDUCE(ts_sym_package_directive, 2),
    },
    [208] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
        [ts_sym_comment] = SHIFT(208),
        [ts_aux_sym_token1] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_package_name, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_golang);
