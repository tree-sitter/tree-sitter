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
    ts_sym__map = 24,
    ts_sym__interface = 25,
    ts_sym__struct = 26,
    ts_sym__package = 27,
    ts_sym__import = 28,
    ts_sym__var = 29,
    ts_sym__func = 30,
    ts_sym__type = 31,
    ts_sym_string = 32,
    ts_sym__identifier = 33,
    ts_sym_number = 34,
    ts_aux_sym_program_repeat0 = 35,
    ts_aux_sym_program_repeat1 = 36,
    ts_aux_sym_imports_block_repeat0 = 37,
    ts_aux_sym_struct_type_repeat0 = 38,
    ts_aux_sym_interface_type_repeat0 = 39,
    ts_aux_sym__func_signature_repeat0 = 40,
    ts_aux_sym__func_signature_repeat1 = 41,
    ts_aux_sym__func_signature_repeat2 = 42,
    ts_aux_sym__func_signature_repeat3 = 43,
    ts_aux_sym__func_signature_repeat4 = 44,
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
    ts_aux_sym_token10 = 55,
    ts_aux_sym_token11 = 56,
    ts_aux_sym_token12 = 57,
    ts_aux_sym_token13 = 58,
    ts_aux_sym_token14 = 59,
    ts_aux_sym_token15 = 60,
    ts_aux_sym_token16 = 61,
    ts_aux_sym_token17 = 62,
    ts_aux_sym_token18 = 63,
    ts_aux_sym_token19 = 64,
    ts_aux_sym_token20 = 65,
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
    [ts_sym__map] = "_map",
    [ts_sym__interface] = "_interface",
    [ts_sym__struct] = "_struct",
    [ts_sym__package] = "_package",
    [ts_sym__import] = "_import",
    [ts_sym__var] = "_var",
    [ts_sym__func] = "_func",
    [ts_sym__type] = "_type",
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
    [ts_aux_sym_token0] = "'('",
    [ts_aux_sym_token1] = "')'",
    [ts_aux_sym_token2] = "'='",
    [ts_aux_sym_token3] = "'{'",
    [ts_aux_sym_token4] = "'}'",
    [ts_aux_sym_token5] = "'*'",
    [ts_aux_sym_token6] = "'['",
    [ts_aux_sym_token7] = "']'",
    [ts_aux_sym_token8] = "'/'",
    [ts_aux_sym_token9] = "'+'",
    [ts_aux_sym_token10] = "'-'",
    [ts_aux_sym_token11] = "'&&'",
    [ts_aux_sym_token12] = "'||'",
    [ts_aux_sym_token13] = "'==='",
    [ts_aux_sym_token14] = "'=='",
    [ts_aux_sym_token15] = "'<='",
    [ts_aux_sym_token16] = "'<'",
    [ts_aux_sym_token17] = "'>='",
    [ts_aux_sym_token18] = "'>'",
    [ts_aux_sym_token19] = "'!'",
    [ts_aux_sym_token20] = "','",
};

HIDDEN_SYMBOLS = {
    [ts_sym__func_signature] = 1,
    [ts_sym__map] = 1,
    [ts_sym__interface] = 1,
    [ts_sym__struct] = 1,
    [ts_sym__package] = 1,
    [ts_sym__import] = 1,
    [ts_sym__var] = 1,
    [ts_sym__func] = 1,
    [ts_sym__type] = 1,
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
            if (lookahead == 'i')
                ADVANCE(7);
            if (lookahead == 't')
                ADVANCE(13);
            if (lookahead == 'v')
                ADVANCE(17);
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
            ACCEPT_TOKEN(ts_sym__func);
        case 7:
            if (lookahead == 'm')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'p')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (lookahead == 'o')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            if (lookahead == 'r')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (lookahead == 't')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            ACCEPT_TOKEN(ts_sym__import);
        case 13:
            if (lookahead == 'y')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            if (lookahead == 'p')
                ADVANCE(15);
            LEX_ERROR();
        case 15:
            if (lookahead == 'e')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            ACCEPT_TOKEN(ts_sym__type);
        case 17:
            if (lookahead == 'a')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            if (lookahead == 'r')
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            ACCEPT_TOKEN(ts_sym__var);
        case 20:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(20);
            if (lookahead == '\"')
                ADVANCE(21);
            if (lookahead == ')')
                ADVANCE(26);
            LEX_ERROR();
        case 21:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\\')
                ADVANCE(24);
            LEX_ERROR();
        case 22:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\"')
                ADVANCE(23);
            if (lookahead == '\\')
                ADVANCE(24);
            LEX_ERROR();
        case 23:
            ACCEPT_TOKEN(ts_sym_string);
        case 24:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\"')
                ADVANCE(25);
            if (lookahead == '\\')
                ADVANCE(24);
            LEX_ERROR();
        case 25:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(22);
            if (lookahead == '\"')
                ADVANCE(23);
            if (lookahead == '\\')
                ADVANCE(24);
            ACCEPT_TOKEN(ts_sym_string);
        case 26:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 27:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(27);
            if (lookahead == ')')
                ADVANCE(26);
            LEX_ERROR();
        case 28:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(28);
            if (lookahead == '\"')
                ADVANCE(21);
            if (lookahead == '(')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            ACCEPT_TOKEN(ts_aux_sym_token0);
        case 30:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(30);
            if (lookahead == 'f')
                ADVANCE(3);
            if (lookahead == 't')
                ADVANCE(13);
            if (lookahead == 'v')
                ADVANCE(17);
            LEX_ERROR();
        case 31:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(31);
            if (lookahead == '&')
                ADVANCE(32);
            if (lookahead == '*')
                ADVANCE(34);
            if (lookahead == '+')
                ADVANCE(35);
            if (lookahead == '-')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(37);
            if (lookahead == '<')
                ADVANCE(38);
            if (lookahead == '=')
                ADVANCE(40);
            if (lookahead == '>')
                ADVANCE(43);
            if (lookahead == 'f')
                ADVANCE(3);
            if (lookahead == 't')
                ADVANCE(13);
            if (lookahead == 'v')
                ADVANCE(17);
            if (lookahead == '|')
                ADVANCE(45);
            LEX_ERROR();
        case 32:
            if (lookahead == '&')
                ADVANCE(33);
            LEX_ERROR();
        case 33:
            ACCEPT_TOKEN(ts_aux_sym_token11);
        case 34:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 35:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 36:
            ACCEPT_TOKEN(ts_aux_sym_token10);
        case 37:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 38:
            if (lookahead == '=')
                ADVANCE(39);
            ACCEPT_TOKEN(ts_aux_sym_token16);
        case 39:
            ACCEPT_TOKEN(ts_aux_sym_token15);
        case 40:
            if (lookahead == '=')
                ADVANCE(41);
            LEX_ERROR();
        case 41:
            if (lookahead == '=')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_aux_sym_token14);
        case 42:
            ACCEPT_TOKEN(ts_aux_sym_token13);
        case 43:
            if (lookahead == '=')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_aux_sym_token18);
        case 44:
            ACCEPT_TOKEN(ts_aux_sym_token17);
        case 45:
            if (lookahead == '|')
                ADVANCE(46);
            LEX_ERROR();
        case 46:
            ACCEPT_TOKEN(ts_aux_sym_token12);
        case 47:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(47);
            if (lookahead == '!')
                ADVANCE(48);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(49);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            LEX_ERROR();
        case 48:
            ACCEPT_TOKEN(ts_aux_sym_token19);
        case 49:
            if (lookahead == '.')
                ADVANCE(50);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym_number);
        case 50:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(51);
            LEX_ERROR();
        case 51:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym_number);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 53:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(53);
            if (lookahead == '=')
                ADVANCE(54);
            LEX_ERROR();
        case 54:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 55:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(55);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            LEX_ERROR();
        case 56:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(56);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 57:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 58:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(58);
            if (lookahead == '{')
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
            if (lookahead == ')')
                ADVANCE(26);
            if (lookahead == ',')
                ADVANCE(61);
            LEX_ERROR();
        case 61:
            ACCEPT_TOKEN(ts_aux_sym_token20);
        case 62:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(62);
            if (lookahead == ')')
                ADVANCE(26);
            if (lookahead == ',')
                ADVANCE(61);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            LEX_ERROR();
        case 63:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(63);
            if (lookahead == '(')
                ADVANCE(29);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == '{')
                ADVANCE(59);
            LEX_ERROR();
        case 64:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == '(')
                ADVANCE(29);
            LEX_ERROR();
        case 65:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(65);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 66:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (lookahead == '(')
                ADVANCE(29);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 67:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (lookahead == '*')
                ADVANCE(34);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == '[')
                ADVANCE(68);
            if (lookahead == 'i')
                ADVANCE(69);
            if (lookahead == 'm')
                ADVANCE(78);
            if (lookahead == 's')
                ADVANCE(81);
            LEX_ERROR();
        case 68:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(70);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(71);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 71:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'e')
                ADVANCE(72);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 72:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(73);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 73:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'f')
                ADVANCE(74);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 74:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'a')
                ADVANCE(75);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 75:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'c')
                ADVANCE(76);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 76:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'e')
                ADVANCE(77);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 77:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__interface);
        case 78:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'a')
                ADVANCE(79);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 79:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'p')
                ADVANCE(80);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 80:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__map);
        case 81:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(82);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 82:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(83);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 83:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'u')
                ADVANCE(84);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 84:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'c')
                ADVANCE(85);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 85:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 86:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__struct);
        case 87:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(87);
            if (lookahead == ']')
                ADVANCE(88);
            LEX_ERROR();
        case 88:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 89:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(89);
            if (lookahead == '[')
                ADVANCE(68);
            LEX_ERROR();
        case 90:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(90);
            if (lookahead == '*')
                ADVANCE(34);
            if (lookahead == ',')
                ADVANCE(61);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == '[')
                ADVANCE(68);
            if (lookahead == 'i')
                ADVANCE(69);
            if (lookahead == 'm')
                ADVANCE(78);
            if (lookahead == 's')
                ADVANCE(81);
            LEX_ERROR();
        case 91:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(91);
            if (lookahead == ')')
                ADVANCE(26);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            LEX_ERROR();
        case 92:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(92);
            if (lookahead == 'p')
                ADVANCE(93);
            LEX_ERROR();
        case 93:
            if (lookahead == 'a')
                ADVANCE(94);
            LEX_ERROR();
        case 94:
            if (lookahead == 'c')
                ADVANCE(95);
            LEX_ERROR();
        case 95:
            if (lookahead == 'k')
                ADVANCE(96);
            LEX_ERROR();
        case 96:
            if (lookahead == 'a')
                ADVANCE(97);
            LEX_ERROR();
        case 97:
            if (lookahead == 'g')
                ADVANCE(98);
            LEX_ERROR();
        case 98:
            if (lookahead == 'e')
                ADVANCE(99);
            LEX_ERROR();
        case 99:
            ACCEPT_TOKEN(ts_sym__package);
        case 100:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '!')
                ADVANCE(48);
            if (lookahead == '\"')
                ADVANCE(21);
            if (lookahead == '&')
                ADVANCE(32);
            if (lookahead == '(')
                ADVANCE(29);
            if (lookahead == ')')
                ADVANCE(26);
            if (lookahead == '*')
                ADVANCE(34);
            if (lookahead == '+')
                ADVANCE(35);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '-')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(37);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(49);
            if (lookahead == '<')
                ADVANCE(38);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(43);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == '[')
                ADVANCE(68);
            if (lookahead == ']')
                ADVANCE(88);
            if (lookahead == 'f')
                ADVANCE(102);
            if (lookahead == 'i')
                ADVANCE(106);
            if (lookahead == 'm')
                ADVANCE(78);
            if (lookahead == 'p')
                ADVANCE(112);
            if (lookahead == 's')
                ADVANCE(81);
            if (lookahead == 't')
                ADVANCE(119);
            if (lookahead == 'v')
                ADVANCE(123);
            if (lookahead == '{')
                ADVANCE(59);
            if (lookahead == '|')
                ADVANCE(45);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        case 101:
            if (lookahead == '=')
                ADVANCE(41);
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'u')
                ADVANCE(103);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'n')
                ADVANCE(104);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 104:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'c')
                ADVANCE(105);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 105:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__func);
        case 106:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'm')
                ADVANCE(107);
            if (lookahead == 'n')
                ADVANCE(70);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 107:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'p')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 108:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'o')
                ADVANCE(109);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 109:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(110);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 110:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 't')
                ADVANCE(111);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 111:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__import);
        case 112:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'a')
                ADVANCE(113);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 113:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'c')
                ADVANCE(114);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 114:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'k')
                ADVANCE(115);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 115:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'a')
                ADVANCE(116);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 116:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'g')
                ADVANCE(117);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 117:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'e')
                ADVANCE(118);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 118:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__package);
        case 119:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(52);
            if (lookahead == 'y')
                ADVANCE(120);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 120:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'p')
                ADVANCE(121);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 121:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'e')
                ADVANCE(122);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 122:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__type);
        case 123:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'a')
                ADVANCE(124);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == 'r')
                ADVANCE(125);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__var);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '!')
                ADVANCE(48);
            if (lookahead == '\"')
                ADVANCE(21);
            if (lookahead == '&')
                ADVANCE(32);
            if (lookahead == '(')
                ADVANCE(29);
            if (lookahead == ')')
                ADVANCE(26);
            if (lookahead == '*')
                ADVANCE(34);
            if (lookahead == '+')
                ADVANCE(35);
            if (lookahead == ',')
                ADVANCE(61);
            if (lookahead == '-')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(37);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(49);
            if (lookahead == '<')
                ADVANCE(38);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(43);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(52);
            if (lookahead == '[')
                ADVANCE(68);
            if (lookahead == ']')
                ADVANCE(88);
            if (lookahead == 'f')
                ADVANCE(102);
            if (lookahead == 'i')
                ADVANCE(106);
            if (lookahead == 'm')
                ADVANCE(78);
            if (lookahead == 'p')
                ADVANCE(112);
            if (lookahead == 's')
                ADVANCE(81);
            if (lookahead == 't')
                ADVANCE(119);
            if (lookahead == 'v')
                ADVANCE(123);
            if (lookahead == '{')
                ADVANCE(59);
            if (lookahead == '|')
                ADVANCE(45);
            if (lookahead == '}')
                ADVANCE(57);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 92,
    [1] = 0,
    [2] = 2,
    [3] = 2,
    [4] = 28,
    [5] = 2,
    [6] = 2,
    [7] = 20,
    [8] = 20,
    [9] = 20,
    [10] = 27,
    [11] = 27,
    [12] = 2,
    [13] = 30,
    [14] = 30,
    [15] = 30,
    [16] = 30,
    [17] = 55,
    [18] = 53,
    [19] = 47,
    [20] = 31,
    [21] = 47,
    [22] = 31,
    [23] = 47,
    [24] = 31,
    [25] = 47,
    [26] = 31,
    [27] = 47,
    [28] = 31,
    [29] = 47,
    [30] = 31,
    [31] = 31,
    [32] = 31,
    [33] = 47,
    [34] = 31,
    [35] = 53,
    [36] = 55,
    [37] = 64,
    [38] = 58,
    [39] = 30,
    [40] = 56,
    [41] = 30,
    [42] = 91,
    [43] = 90,
    [44] = 67,
    [45] = 60,
    [46] = 27,
    [47] = 63,
    [48] = 58,
    [49] = 58,
    [50] = 55,
    [51] = 55,
    [52] = 60,
    [53] = 27,
    [54] = 58,
    [55] = 55,
    [56] = 55,
    [57] = 60,
    [58] = 27,
    [59] = 60,
    [60] = 55,
    [61] = 60,
    [62] = 27,
    [63] = 58,
    [64] = 55,
    [65] = 60,
    [66] = 27,
    [67] = 62,
    [68] = 55,
    [69] = 90,
    [70] = 67,
    [71] = 60,
    [72] = 27,
    [73] = 60,
    [74] = 89,
    [75] = 67,
    [76] = 87,
    [77] = 67,
    [78] = 60,
    [79] = 58,
    [80] = 65,
    [81] = 64,
    [82] = 65,
    [83] = 64,
    [84] = 56,
    [85] = 91,
    [86] = 90,
    [87] = 67,
    [88] = 60,
    [89] = 27,
    [90] = 66,
    [91] = 65,
    [92] = 65,
    [93] = 55,
    [94] = 55,
    [95] = 60,
    [96] = 27,
    [97] = 65,
    [98] = 60,
    [99] = 27,
    [100] = 65,
    [101] = 58,
    [102] = 65,
    [103] = 67,
    [104] = 65,
    [105] = 67,
    [106] = 56,
    [107] = 65,
    [108] = 89,
    [109] = 67,
    [110] = 87,
    [111] = 67,
    [112] = 65,
    [113] = 58,
    [114] = 65,
    [115] = 56,
    [116] = 65,
    [117] = 58,
    [118] = 65,
    [119] = 56,
    [120] = 65,
    [121] = 67,
    [122] = 65,
    [123] = 87,
    [124] = 67,
    [125] = 65,
    [126] = 87,
    [127] = 89,
    [128] = 67,
    [129] = 87,
    [130] = 67,
    [131] = 87,
    [132] = 58,
    [133] = 65,
    [134] = 56,
    [135] = 87,
    [136] = 58,
    [137] = 65,
    [138] = 56,
    [139] = 87,
    [140] = 87,
    [141] = 67,
    [142] = 87,
    [143] = 87,
    [144] = 67,
    [145] = 87,
    [146] = 56,
    [147] = 60,
    [148] = 67,
    [149] = 60,
    [150] = 87,
    [151] = 67,
    [152] = 60,
    [153] = 55,
    [154] = 90,
    [155] = 67,
    [156] = 90,
    [157] = 66,
    [158] = 65,
    [159] = 55,
    [160] = 55,
    [161] = 60,
    [162] = 27,
    [163] = 60,
    [164] = 27,
    [165] = 65,
    [166] = 56,
    [167] = 60,
    [168] = 55,
    [169] = 90,
    [170] = 67,
    [171] = 63,
    [172] = 58,
    [173] = 55,
    [174] = 55,
    [175] = 60,
    [176] = 27,
    [177] = 60,
    [178] = 27,
    [179] = 58,
    [180] = 55,
    [181] = 67,
    [182] = 30,
    [183] = 30,
    [184] = 89,
    [185] = 67,
    [186] = 87,
    [187] = 67,
    [188] = 30,
    [189] = 58,
    [190] = 65,
    [191] = 56,
    [192] = 30,
    [193] = 58,
    [194] = 65,
    [195] = 56,
    [196] = 30,
    [197] = 30,
    [198] = 67,
    [199] = 30,
    [200] = 87,
    [201] = 67,
    [202] = 30,
    [203] = 67,
    [204] = 0,
    [205] = 0,
    [206] = 55,
    [207] = 2,
    [208] = 2,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_program] = SHIFT(1),
        [ts_sym_package_directive] = SHIFT(2),
        [ts_sym__package] = SHIFT(206),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [2] = {
        [ts_sym_imports_block] = SHIFT(3),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__import] = SHIFT(4),
        [ts_sym__var] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__func] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__type] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_program_repeat0] = SHIFT(14),
    },
    [3] = {
        [ts_sym_imports_block] = SHIFT(3),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__import] = SHIFT(4),
        [ts_sym__var] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__func] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__type] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_program_repeat0] = SHIFT(13),
    },
    [4] = {
        [ts_sym_package_import] = SHIFT(5),
        [ts_sym_string] = SHIFT(6),
        [ts_aux_sym_token0] = SHIFT(7),
    },
    [5] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__import] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__var] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__func] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__type] = REDUCE(ts_sym_imports_block, 2),
    },
    [6] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__import] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__var] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__func] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__type] = REDUCE(ts_sym_package_import, 1),
    },
    [7] = {
        [ts_sym_package_import] = SHIFT(8),
        [ts_builtin_sym_error] = SHIFT(11),
        [ts_sym_string] = SHIFT(9),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(11),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [8] = {
        [ts_sym_package_import] = SHIFT(8),
        [ts_sym_string] = SHIFT(9),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(10),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [9] = {
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_package_import, 1),
    },
    [10] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym_imports_block_repeat0, 2),
    },
    [11] = {
        [ts_aux_sym_token1] = SHIFT(12),
    },
    [12] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__import] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__var] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__func] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__type] = REDUCE(ts_sym_imports_block, 4),
    },
    [13] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym__var] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym__func] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym__type] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [14] = {
        [ts_sym_declaration] = SHIFT(15),
        [ts_sym_type_declaration] = SHIFT(16),
        [ts_sym_var_declaration] = SHIFT(16),
        [ts_sym_func_declaration] = SHIFT(16),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym__var] = SHIFT(17),
        [ts_sym__func] = SHIFT(36),
        [ts_sym__type] = SHIFT(180),
        [ts_aux_sym_program_repeat1] = SHIFT(205),
    },
    [15] = {
        [ts_sym_declaration] = SHIFT(15),
        [ts_sym_type_declaration] = SHIFT(16),
        [ts_sym_var_declaration] = SHIFT(16),
        [ts_sym_func_declaration] = SHIFT(16),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym__var] = SHIFT(17),
        [ts_sym__func] = SHIFT(36),
        [ts_sym__type] = SHIFT(180),
        [ts_aux_sym_program_repeat1] = SHIFT(204),
    },
    [16] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__var] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__func] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__type] = REDUCE(ts_sym_declaration, 1),
    },
    [17] = {
        [ts_sym_var_name] = SHIFT(18),
        [ts_sym__identifier] = SHIFT(35),
    },
    [18] = {
        [ts_aux_sym_token2] = SHIFT(19),
    },
    [19] = {
        [ts_sym_expression] = SHIFT(20),
        [ts_sym_math_op] = SHIFT(31),
        [ts_sym_bool_op] = SHIFT(31),
        [ts_sym_var_name] = SHIFT(31),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(31),
        [ts_aux_sym_token19] = SHIFT(33),
    },
    [20] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__func] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__type] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_token5] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(21),
        [ts_aux_sym_token9] = SHIFT(23),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(27),
        [ts_aux_sym_token14] = SHIFT(27),
        [ts_aux_sym_token15] = SHIFT(27),
        [ts_aux_sym_token16] = SHIFT(29),
        [ts_aux_sym_token17] = SHIFT(27),
        [ts_aux_sym_token18] = SHIFT(27),
    },
    [21] = {
        [ts_sym_expression] = SHIFT(22),
        [ts_sym_math_op] = SHIFT(31),
        [ts_sym_bool_op] = SHIFT(31),
        [ts_sym_var_name] = SHIFT(31),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(31),
        [ts_aux_sym_token19] = SHIFT(33),
    },
    [22] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__var] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__func] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__type] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(21),
        [ts_aux_sym_token9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(27),
        [ts_aux_sym_token14] = SHIFT(27),
        [ts_aux_sym_token15] = SHIFT(27),
        [ts_aux_sym_token16] = SHIFT(29),
        [ts_aux_sym_token17] = SHIFT(27),
        [ts_aux_sym_token18] = SHIFT(27),
    },
    [23] = {
        [ts_sym_expression] = SHIFT(24),
        [ts_sym_math_op] = SHIFT(31),
        [ts_sym_bool_op] = SHIFT(31),
        [ts_sym_var_name] = SHIFT(31),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(31),
        [ts_aux_sym_token19] = SHIFT(33),
    },
    [24] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__var] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__func] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__type] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_token5] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(21),
        [ts_aux_sym_token9] = SHIFT(23),
        [ts_aux_sym_token10] = SHIFT(23),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(27),
        [ts_aux_sym_token14] = SHIFT(27),
        [ts_aux_sym_token15] = SHIFT(27),
        [ts_aux_sym_token16] = SHIFT(29),
        [ts_aux_sym_token17] = SHIFT(27),
        [ts_aux_sym_token18] = SHIFT(27),
    },
    [25] = {
        [ts_sym_expression] = SHIFT(26),
        [ts_sym_math_op] = SHIFT(31),
        [ts_sym_bool_op] = SHIFT(31),
        [ts_sym_var_name] = SHIFT(31),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(31),
        [ts_aux_sym_token19] = SHIFT(33),
    },
    [26] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__var] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__func] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__type] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = SHIFT(29),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
    },
    [27] = {
        [ts_sym_expression] = SHIFT(28),
        [ts_sym_math_op] = SHIFT(31),
        [ts_sym_bool_op] = SHIFT(31),
        [ts_sym_var_name] = SHIFT(31),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(31),
        [ts_aux_sym_token19] = SHIFT(33),
    },
    [28] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__var] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__func] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__type] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = SHIFT(21),
        [ts_aux_sym_token8] = SHIFT(21),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = SHIFT(25),
        [ts_aux_sym_token12] = SHIFT(27),
        [ts_aux_sym_token13] = SHIFT(27),
        [ts_aux_sym_token14] = SHIFT(27),
        [ts_aux_sym_token15] = SHIFT(27),
        [ts_aux_sym_token16] = SHIFT(29),
        [ts_aux_sym_token17] = SHIFT(27),
        [ts_aux_sym_token18] = SHIFT(27),
    },
    [29] = {
        [ts_sym_expression] = SHIFT(30),
        [ts_sym_math_op] = SHIFT(31),
        [ts_sym_bool_op] = SHIFT(31),
        [ts_sym_var_name] = SHIFT(31),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(31),
        [ts_aux_sym_token19] = SHIFT(33),
    },
    [30] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__var] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__func] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__type] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token16] = SHIFT(29),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 3),
    },
    [31] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
        [ts_sym__var] = REDUCE(ts_sym_expression, 1),
        [ts_sym__func] = REDUCE(ts_sym_expression, 1),
        [ts_sym__type] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_expression, 1),
    },
    [32] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__var] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__func] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__type] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token13] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token15] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token16] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token17] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token18] = REDUCE(ts_sym_var_name, 1),
    },
    [33] = {
        [ts_sym_expression] = SHIFT(34),
        [ts_sym_math_op] = SHIFT(31),
        [ts_sym_bool_op] = SHIFT(31),
        [ts_sym_var_name] = SHIFT(31),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_number] = SHIFT(31),
        [ts_aux_sym_token19] = SHIFT(33),
    },
    [34] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym__var] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym__func] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym__type] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token16] = SHIFT(29),
        [ts_aux_sym_token17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_token18] = REDUCE(ts_sym_bool_op, 2),
    },
    [35] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_name, 1),
    },
    [36] = {
        [ts_sym_var_name] = SHIFT(37),
        [ts_sym__identifier] = SHIFT(83),
    },
    [37] = {
        [ts_sym__func_signature] = SHIFT(38),
        [ts_aux_sym_token0] = SHIFT(42),
    },
    [38] = {
        [ts_sym_statement_block] = SHIFT(39),
        [ts_aux_sym_token3] = SHIFT(40),
    },
    [39] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 4),
        [ts_sym__var] = REDUCE(ts_sym_func_declaration, 4),
        [ts_sym__func] = REDUCE(ts_sym_func_declaration, 4),
        [ts_sym__type] = REDUCE(ts_sym_func_declaration, 4),
    },
    [40] = {
        [ts_aux_sym_token4] = SHIFT(41),
    },
    [41] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 2),
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 2),
        [ts_sym__func] = REDUCE(ts_sym_statement_block, 2),
        [ts_sym__type] = REDUCE(ts_sym_statement_block, 2),
    },
    [42] = {
        [ts_sym_var_name] = SHIFT(43),
        [ts_sym__identifier] = SHIFT(156),
        [ts_aux_sym_token1] = SHIFT(171),
    },
    [43] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(44),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(153),
    },
    [44] = {
        [ts_sym_type_expression] = SHIFT(45),
        [ts_sym_pointer_type] = SHIFT(73),
        [ts_sym_map_type] = SHIFT(73),
        [ts_sym_slice_type] = SHIFT(73),
        [ts_sym_struct_type] = SHIFT(73),
        [ts_sym_interface_type] = SHIFT(73),
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__map] = SHIFT(74),
        [ts_sym__interface] = SHIFT(79),
        [ts_sym__struct] = SHIFT(101),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_token5] = SHIFT(148),
        [ts_aux_sym_token6] = SHIFT(150),
    },
    [45] = {
        [ts_aux_sym__func_signature_repeat2] = SHIFT(46),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token20] = SHIFT(68),
    },
    [46] = {
        [ts_aux_sym_token1] = SHIFT(47),
    },
    [47] = {
        [ts_sym_type_name] = SHIFT(48),
        [ts_sym__identifier] = SHIFT(49),
        [ts_aux_sym_token0] = SHIFT(50),
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 6),
    },
    [48] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 7),
    },
    [49] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_type_name, 1),
    },
    [50] = {
        [ts_sym_var_name] = SHIFT(51),
        [ts_sym_type_name] = SHIFT(61),
        [ts_sym__identifier] = SHIFT(67),
    },
    [51] = {
        [ts_sym_type_name] = SHIFT(52),
        [ts_sym__identifier] = SHIFT(59),
    },
    [52] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(53),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token20] = SHIFT(55),
    },
    [53] = {
        [ts_aux_sym_token1] = SHIFT(54),
    },
    [54] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 11),
    },
    [55] = {
        [ts_sym_var_name] = SHIFT(56),
        [ts_sym__identifier] = SHIFT(60),
    },
    [56] = {
        [ts_sym_type_name] = SHIFT(57),
        [ts_sym__identifier] = SHIFT(59),
    },
    [57] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(58),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token20] = SHIFT(55),
    },
    [58] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [59] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_type_name, 1),
    },
    [60] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
    },
    [61] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(62),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token20] = SHIFT(64),
    },
    [62] = {
        [ts_aux_sym_token1] = SHIFT(63),
    },
    [63] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 10),
    },
    [64] = {
        [ts_sym_type_name] = SHIFT(65),
        [ts_sym__identifier] = SHIFT(59),
    },
    [65] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(66),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token20] = SHIFT(64),
    },
    [66] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [67] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_type_name, 1),
    },
    [68] = {
        [ts_sym_var_name] = SHIFT(69),
        [ts_sym__identifier] = SHIFT(156),
    },
    [69] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(70),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token20] = SHIFT(168),
    },
    [70] = {
        [ts_sym_type_expression] = SHIFT(71),
        [ts_sym_pointer_type] = SHIFT(73),
        [ts_sym_map_type] = SHIFT(73),
        [ts_sym_slice_type] = SHIFT(73),
        [ts_sym_struct_type] = SHIFT(73),
        [ts_sym_interface_type] = SHIFT(73),
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__map] = SHIFT(74),
        [ts_sym__interface] = SHIFT(79),
        [ts_sym__struct] = SHIFT(101),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_token5] = SHIFT(148),
        [ts_aux_sym_token6] = SHIFT(150),
    },
    [71] = {
        [ts_aux_sym__func_signature_repeat2] = SHIFT(72),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token20] = SHIFT(68),
    },
    [72] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [73] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_type_expression, 1),
    },
    [74] = {
        [ts_aux_sym_token6] = SHIFT(75),
    },
    [75] = {
        [ts_sym_type_expression] = SHIFT(76),
        [ts_sym_pointer_type] = SHIFT(126),
        [ts_sym_map_type] = SHIFT(126),
        [ts_sym_slice_type] = SHIFT(126),
        [ts_sym_struct_type] = SHIFT(126),
        [ts_sym_interface_type] = SHIFT(126),
        [ts_sym_type_name] = SHIFT(126),
        [ts_sym__map] = SHIFT(127),
        [ts_sym__interface] = SHIFT(132),
        [ts_sym__struct] = SHIFT(136),
        [ts_sym__identifier] = SHIFT(140),
        [ts_aux_sym_token5] = SHIFT(141),
        [ts_aux_sym_token6] = SHIFT(143),
    },
    [76] = {
        [ts_aux_sym_token7] = SHIFT(77),
    },
    [77] = {
        [ts_sym_type_expression] = SHIFT(78),
        [ts_sym_pointer_type] = SHIFT(73),
        [ts_sym_map_type] = SHIFT(73),
        [ts_sym_slice_type] = SHIFT(73),
        [ts_sym_struct_type] = SHIFT(73),
        [ts_sym_interface_type] = SHIFT(73),
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__map] = SHIFT(74),
        [ts_sym__interface] = SHIFT(79),
        [ts_sym__struct] = SHIFT(101),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_token5] = SHIFT(148),
        [ts_aux_sym_token6] = SHIFT(150),
    },
    [78] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token20] = REDUCE(ts_sym_map_type, 5),
    },
    [79] = {
        [ts_aux_sym_token3] = SHIFT(80),
    },
    [80] = {
        [ts_sym_var_name] = SHIFT(81),
        [ts_sym__identifier] = SHIFT(83),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(166),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [81] = {
        [ts_sym__func_signature] = SHIFT(82),
        [ts_aux_sym_token0] = SHIFT(85),
    },
    [82] = {
        [ts_sym_var_name] = SHIFT(81),
        [ts_sym__identifier] = SHIFT(83),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(84),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [83] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_name, 1),
    },
    [84] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [85] = {
        [ts_sym_var_name] = SHIFT(86),
        [ts_sym__identifier] = SHIFT(156),
        [ts_aux_sym_token1] = SHIFT(157),
    },
    [86] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(87),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(153),
    },
    [87] = {
        [ts_sym_type_expression] = SHIFT(88),
        [ts_sym_pointer_type] = SHIFT(73),
        [ts_sym_map_type] = SHIFT(73),
        [ts_sym_slice_type] = SHIFT(73),
        [ts_sym_struct_type] = SHIFT(73),
        [ts_sym_interface_type] = SHIFT(73),
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__map] = SHIFT(74),
        [ts_sym__interface] = SHIFT(79),
        [ts_sym__struct] = SHIFT(101),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_token5] = SHIFT(148),
        [ts_aux_sym_token6] = SHIFT(150),
    },
    [88] = {
        [ts_aux_sym__func_signature_repeat2] = SHIFT(89),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token20] = SHIFT(68),
    },
    [89] = {
        [ts_aux_sym_token1] = SHIFT(90),
    },
    [90] = {
        [ts_sym_type_name] = SHIFT(91),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_token0] = SHIFT(93),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 6),
    },
    [91] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 7),
    },
    [92] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_name, 1),
    },
    [93] = {
        [ts_sym_var_name] = SHIFT(94),
        [ts_sym_type_name] = SHIFT(98),
        [ts_sym__identifier] = SHIFT(67),
    },
    [94] = {
        [ts_sym_type_name] = SHIFT(95),
        [ts_sym__identifier] = SHIFT(59),
    },
    [95] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(96),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token20] = SHIFT(55),
    },
    [96] = {
        [ts_aux_sym_token1] = SHIFT(97),
    },
    [97] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 11),
    },
    [98] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(99),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token20] = SHIFT(64),
    },
    [99] = {
        [ts_aux_sym_token1] = SHIFT(100),
    },
    [100] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 10),
    },
    [101] = {
        [ts_aux_sym_token3] = SHIFT(102),
    },
    [102] = {
        [ts_sym_var_name] = SHIFT(103),
        [ts_sym__identifier] = SHIFT(105),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(146),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [103] = {
        [ts_sym_type_expression] = SHIFT(104),
        [ts_sym_pointer_type] = SHIFT(107),
        [ts_sym_map_type] = SHIFT(107),
        [ts_sym_slice_type] = SHIFT(107),
        [ts_sym_struct_type] = SHIFT(107),
        [ts_sym_interface_type] = SHIFT(107),
        [ts_sym_type_name] = SHIFT(107),
        [ts_sym__map] = SHIFT(108),
        [ts_sym__interface] = SHIFT(113),
        [ts_sym__struct] = SHIFT(117),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_token5] = SHIFT(121),
        [ts_aux_sym_token6] = SHIFT(123),
    },
    [104] = {
        [ts_sym_var_name] = SHIFT(103),
        [ts_sym__identifier] = SHIFT(105),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(106),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [105] = {
        [ts_sym__map] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__interface] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__struct] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),
    },
    [106] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 3),
    },
    [107] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_expression, 1),
    },
    [108] = {
        [ts_aux_sym_token6] = SHIFT(109),
    },
    [109] = {
        [ts_sym_type_expression] = SHIFT(110),
        [ts_sym_pointer_type] = SHIFT(126),
        [ts_sym_map_type] = SHIFT(126),
        [ts_sym_slice_type] = SHIFT(126),
        [ts_sym_struct_type] = SHIFT(126),
        [ts_sym_interface_type] = SHIFT(126),
        [ts_sym_type_name] = SHIFT(126),
        [ts_sym__map] = SHIFT(127),
        [ts_sym__interface] = SHIFT(132),
        [ts_sym__struct] = SHIFT(136),
        [ts_sym__identifier] = SHIFT(140),
        [ts_aux_sym_token5] = SHIFT(141),
        [ts_aux_sym_token6] = SHIFT(143),
    },
    [110] = {
        [ts_aux_sym_token7] = SHIFT(111),
    },
    [111] = {
        [ts_sym_type_expression] = SHIFT(112),
        [ts_sym_pointer_type] = SHIFT(107),
        [ts_sym_map_type] = SHIFT(107),
        [ts_sym_slice_type] = SHIFT(107),
        [ts_sym_struct_type] = SHIFT(107),
        [ts_sym_interface_type] = SHIFT(107),
        [ts_sym_type_name] = SHIFT(107),
        [ts_sym__map] = SHIFT(108),
        [ts_sym__interface] = SHIFT(113),
        [ts_sym__struct] = SHIFT(117),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_token5] = SHIFT(121),
        [ts_aux_sym_token6] = SHIFT(123),
    },
    [112] = {
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_map_type, 5),
    },
    [113] = {
        [ts_aux_sym_token3] = SHIFT(114),
    },
    [114] = {
        [ts_sym_var_name] = SHIFT(81),
        [ts_sym__identifier] = SHIFT(83),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(115),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [115] = {
        [ts_aux_sym_token4] = SHIFT(116),
    },
    [116] = {
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_interface_type, 4),
    },
    [117] = {
        [ts_aux_sym_token3] = SHIFT(118),
    },
    [118] = {
        [ts_sym_var_name] = SHIFT(103),
        [ts_sym__identifier] = SHIFT(105),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(119),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [119] = {
        [ts_aux_sym_token4] = SHIFT(120),
    },
    [120] = {
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_struct_type, 4),
    },
    [121] = {
        [ts_sym_type_expression] = SHIFT(122),
        [ts_sym_pointer_type] = SHIFT(107),
        [ts_sym_map_type] = SHIFT(107),
        [ts_sym_slice_type] = SHIFT(107),
        [ts_sym_struct_type] = SHIFT(107),
        [ts_sym_interface_type] = SHIFT(107),
        [ts_sym_type_name] = SHIFT(107),
        [ts_sym__map] = SHIFT(108),
        [ts_sym__interface] = SHIFT(113),
        [ts_sym__struct] = SHIFT(117),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_token5] = SHIFT(121),
        [ts_aux_sym_token6] = SHIFT(123),
    },
    [122] = {
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_pointer_type, 2),
    },
    [123] = {
        [ts_aux_sym_token7] = SHIFT(124),
    },
    [124] = {
        [ts_sym_type_expression] = SHIFT(125),
        [ts_sym_pointer_type] = SHIFT(107),
        [ts_sym_map_type] = SHIFT(107),
        [ts_sym_slice_type] = SHIFT(107),
        [ts_sym_struct_type] = SHIFT(107),
        [ts_sym_interface_type] = SHIFT(107),
        [ts_sym_type_name] = SHIFT(107),
        [ts_sym__map] = SHIFT(108),
        [ts_sym__interface] = SHIFT(113),
        [ts_sym__struct] = SHIFT(117),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_token5] = SHIFT(121),
        [ts_aux_sym_token6] = SHIFT(123),
    },
    [125] = {
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_slice_type, 3),
    },
    [126] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_expression, 1),
    },
    [127] = {
        [ts_aux_sym_token6] = SHIFT(128),
    },
    [128] = {
        [ts_sym_type_expression] = SHIFT(129),
        [ts_sym_pointer_type] = SHIFT(126),
        [ts_sym_map_type] = SHIFT(126),
        [ts_sym_slice_type] = SHIFT(126),
        [ts_sym_struct_type] = SHIFT(126),
        [ts_sym_interface_type] = SHIFT(126),
        [ts_sym_type_name] = SHIFT(126),
        [ts_sym__map] = SHIFT(127),
        [ts_sym__interface] = SHIFT(132),
        [ts_sym__struct] = SHIFT(136),
        [ts_sym__identifier] = SHIFT(140),
        [ts_aux_sym_token5] = SHIFT(141),
        [ts_aux_sym_token6] = SHIFT(143),
    },
    [129] = {
        [ts_aux_sym_token7] = SHIFT(130),
    },
    [130] = {
        [ts_sym_type_expression] = SHIFT(131),
        [ts_sym_pointer_type] = SHIFT(126),
        [ts_sym_map_type] = SHIFT(126),
        [ts_sym_slice_type] = SHIFT(126),
        [ts_sym_struct_type] = SHIFT(126),
        [ts_sym_interface_type] = SHIFT(126),
        [ts_sym_type_name] = SHIFT(126),
        [ts_sym__map] = SHIFT(127),
        [ts_sym__interface] = SHIFT(132),
        [ts_sym__struct] = SHIFT(136),
        [ts_sym__identifier] = SHIFT(140),
        [ts_aux_sym_token5] = SHIFT(141),
        [ts_aux_sym_token6] = SHIFT(143),
    },
    [131] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_map_type, 5),
    },
    [132] = {
        [ts_aux_sym_token3] = SHIFT(133),
    },
    [133] = {
        [ts_sym_var_name] = SHIFT(81),
        [ts_sym__identifier] = SHIFT(83),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(134),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [134] = {
        [ts_aux_sym_token4] = SHIFT(135),
    },
    [135] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_interface_type, 4),
    },
    [136] = {
        [ts_aux_sym_token3] = SHIFT(137),
    },
    [137] = {
        [ts_sym_var_name] = SHIFT(103),
        [ts_sym__identifier] = SHIFT(105),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(138),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [138] = {
        [ts_aux_sym_token4] = SHIFT(139),
    },
    [139] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_struct_type, 4),
    },
    [140] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_name, 1),
    },
    [141] = {
        [ts_sym_type_expression] = SHIFT(142),
        [ts_sym_pointer_type] = SHIFT(126),
        [ts_sym_map_type] = SHIFT(126),
        [ts_sym_slice_type] = SHIFT(126),
        [ts_sym_struct_type] = SHIFT(126),
        [ts_sym_interface_type] = SHIFT(126),
        [ts_sym_type_name] = SHIFT(126),
        [ts_sym__map] = SHIFT(127),
        [ts_sym__interface] = SHIFT(132),
        [ts_sym__struct] = SHIFT(136),
        [ts_sym__identifier] = SHIFT(140),
        [ts_aux_sym_token5] = SHIFT(141),
        [ts_aux_sym_token6] = SHIFT(143),
    },
    [142] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_pointer_type, 2),
    },
    [143] = {
        [ts_aux_sym_token7] = SHIFT(144),
    },
    [144] = {
        [ts_sym_type_expression] = SHIFT(145),
        [ts_sym_pointer_type] = SHIFT(126),
        [ts_sym_map_type] = SHIFT(126),
        [ts_sym_slice_type] = SHIFT(126),
        [ts_sym_struct_type] = SHIFT(126),
        [ts_sym_interface_type] = SHIFT(126),
        [ts_sym_type_name] = SHIFT(126),
        [ts_sym__map] = SHIFT(127),
        [ts_sym__interface] = SHIFT(132),
        [ts_sym__struct] = SHIFT(136),
        [ts_sym__identifier] = SHIFT(140),
        [ts_aux_sym_token5] = SHIFT(141),
        [ts_aux_sym_token6] = SHIFT(143),
    },
    [145] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_slice_type, 3),
    },
    [146] = {
        [ts_aux_sym_token4] = SHIFT(147),
    },
    [147] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_struct_type, 4),
    },
    [148] = {
        [ts_sym_type_expression] = SHIFT(149),
        [ts_sym_pointer_type] = SHIFT(73),
        [ts_sym_map_type] = SHIFT(73),
        [ts_sym_slice_type] = SHIFT(73),
        [ts_sym_struct_type] = SHIFT(73),
        [ts_sym_interface_type] = SHIFT(73),
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__map] = SHIFT(74),
        [ts_sym__interface] = SHIFT(79),
        [ts_sym__struct] = SHIFT(101),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_token5] = SHIFT(148),
        [ts_aux_sym_token6] = SHIFT(150),
    },
    [149] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token20] = REDUCE(ts_sym_pointer_type, 2),
    },
    [150] = {
        [ts_aux_sym_token7] = SHIFT(151),
    },
    [151] = {
        [ts_sym_type_expression] = SHIFT(152),
        [ts_sym_pointer_type] = SHIFT(73),
        [ts_sym_map_type] = SHIFT(73),
        [ts_sym_slice_type] = SHIFT(73),
        [ts_sym_struct_type] = SHIFT(73),
        [ts_sym_interface_type] = SHIFT(73),
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__map] = SHIFT(74),
        [ts_sym__interface] = SHIFT(79),
        [ts_sym__struct] = SHIFT(101),
        [ts_sym__identifier] = SHIFT(59),
        [ts_aux_sym_token5] = SHIFT(148),
        [ts_aux_sym_token6] = SHIFT(150),
    },
    [152] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token20] = REDUCE(ts_sym_slice_type, 3),
    },
    [153] = {
        [ts_sym_var_name] = SHIFT(154),
        [ts_sym__identifier] = SHIFT(156),
    },
    [154] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(155),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token20] = SHIFT(153),
    },
    [155] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
    },
    [156] = {
        [ts_sym__map] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__interface] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__struct] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token20] = REDUCE(ts_sym_var_name, 1),
    },
    [157] = {
        [ts_sym_type_name] = SHIFT(158),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_token0] = SHIFT(159),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 2),
    },
    [158] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 3),
    },
    [159] = {
        [ts_sym_var_name] = SHIFT(160),
        [ts_sym_type_name] = SHIFT(163),
        [ts_sym__identifier] = SHIFT(67),
    },
    [160] = {
        [ts_sym_type_name] = SHIFT(161),
        [ts_sym__identifier] = SHIFT(59),
    },
    [161] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(162),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token20] = SHIFT(55),
    },
    [162] = {
        [ts_aux_sym_token1] = SHIFT(91),
    },
    [163] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(164),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token20] = SHIFT(64),
    },
    [164] = {
        [ts_aux_sym_token1] = SHIFT(165),
    },
    [165] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 6),
    },
    [166] = {
        [ts_aux_sym_token4] = SHIFT(167),
    },
    [167] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token20] = REDUCE(ts_sym_interface_type, 4),
    },
    [168] = {
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(156),
    },
    [169] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(170),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token20] = SHIFT(168),
    },
    [170] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [171] = {
        [ts_sym_type_name] = SHIFT(172),
        [ts_sym__identifier] = SHIFT(49),
        [ts_aux_sym_token0] = SHIFT(173),
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 2),
    },
    [172] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 3),
    },
    [173] = {
        [ts_sym_var_name] = SHIFT(174),
        [ts_sym_type_name] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(67),
    },
    [174] = {
        [ts_sym_type_name] = SHIFT(175),
        [ts_sym__identifier] = SHIFT(59),
    },
    [175] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(176),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token20] = SHIFT(55),
    },
    [176] = {
        [ts_aux_sym_token1] = SHIFT(48),
    },
    [177] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(178),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token20] = SHIFT(64),
    },
    [178] = {
        [ts_aux_sym_token1] = SHIFT(179),
    },
    [179] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 6),
    },
    [180] = {
        [ts_sym_type_name] = SHIFT(181),
        [ts_sym__identifier] = SHIFT(203),
    },
    [181] = {
        [ts_sym_type_expression] = SHIFT(182),
        [ts_sym_pointer_type] = SHIFT(183),
        [ts_sym_map_type] = SHIFT(183),
        [ts_sym_slice_type] = SHIFT(183),
        [ts_sym_struct_type] = SHIFT(183),
        [ts_sym_interface_type] = SHIFT(183),
        [ts_sym_type_name] = SHIFT(183),
        [ts_sym__map] = SHIFT(184),
        [ts_sym__interface] = SHIFT(189),
        [ts_sym__struct] = SHIFT(193),
        [ts_sym__identifier] = SHIFT(197),
        [ts_aux_sym_token5] = SHIFT(198),
        [ts_aux_sym_token6] = SHIFT(200),
    },
    [182] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 3),
        [ts_sym__var] = REDUCE(ts_sym_type_declaration, 3),
        [ts_sym__func] = REDUCE(ts_sym_type_declaration, 3),
        [ts_sym__type] = REDUCE(ts_sym_type_declaration, 3),
    },
    [183] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__var] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__func] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__type] = REDUCE(ts_sym_type_expression, 1),
    },
    [184] = {
        [ts_aux_sym_token6] = SHIFT(185),
    },
    [185] = {
        [ts_sym_type_expression] = SHIFT(186),
        [ts_sym_pointer_type] = SHIFT(126),
        [ts_sym_map_type] = SHIFT(126),
        [ts_sym_slice_type] = SHIFT(126),
        [ts_sym_struct_type] = SHIFT(126),
        [ts_sym_interface_type] = SHIFT(126),
        [ts_sym_type_name] = SHIFT(126),
        [ts_sym__map] = SHIFT(127),
        [ts_sym__interface] = SHIFT(132),
        [ts_sym__struct] = SHIFT(136),
        [ts_sym__identifier] = SHIFT(140),
        [ts_aux_sym_token5] = SHIFT(141),
        [ts_aux_sym_token6] = SHIFT(143),
    },
    [186] = {
        [ts_aux_sym_token7] = SHIFT(187),
    },
    [187] = {
        [ts_sym_type_expression] = SHIFT(188),
        [ts_sym_pointer_type] = SHIFT(183),
        [ts_sym_map_type] = SHIFT(183),
        [ts_sym_slice_type] = SHIFT(183),
        [ts_sym_struct_type] = SHIFT(183),
        [ts_sym_interface_type] = SHIFT(183),
        [ts_sym_type_name] = SHIFT(183),
        [ts_sym__map] = SHIFT(184),
        [ts_sym__interface] = SHIFT(189),
        [ts_sym__struct] = SHIFT(193),
        [ts_sym__identifier] = SHIFT(197),
        [ts_aux_sym_token5] = SHIFT(198),
        [ts_aux_sym_token6] = SHIFT(200),
    },
    [188] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__var] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__func] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__type] = REDUCE(ts_sym_map_type, 5),
    },
    [189] = {
        [ts_aux_sym_token3] = SHIFT(190),
    },
    [190] = {
        [ts_sym_var_name] = SHIFT(81),
        [ts_sym__identifier] = SHIFT(83),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(191),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [191] = {
        [ts_aux_sym_token4] = SHIFT(192),
    },
    [192] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__var] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__func] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__type] = REDUCE(ts_sym_interface_type, 4),
    },
    [193] = {
        [ts_aux_sym_token3] = SHIFT(194),
    },
    [194] = {
        [ts_sym_var_name] = SHIFT(103),
        [ts_sym__identifier] = SHIFT(105),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(195),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [195] = {
        [ts_aux_sym_token4] = SHIFT(196),
    },
    [196] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__var] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__func] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__type] = REDUCE(ts_sym_struct_type, 4),
    },
    [197] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__var] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__func] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__type] = REDUCE(ts_sym_type_name, 1),
    },
    [198] = {
        [ts_sym_type_expression] = SHIFT(199),
        [ts_sym_pointer_type] = SHIFT(183),
        [ts_sym_map_type] = SHIFT(183),
        [ts_sym_slice_type] = SHIFT(183),
        [ts_sym_struct_type] = SHIFT(183),
        [ts_sym_interface_type] = SHIFT(183),
        [ts_sym_type_name] = SHIFT(183),
        [ts_sym__map] = SHIFT(184),
        [ts_sym__interface] = SHIFT(189),
        [ts_sym__struct] = SHIFT(193),
        [ts_sym__identifier] = SHIFT(197),
        [ts_aux_sym_token5] = SHIFT(198),
        [ts_aux_sym_token6] = SHIFT(200),
    },
    [199] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__var] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__func] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__type] = REDUCE(ts_sym_pointer_type, 2),
    },
    [200] = {
        [ts_aux_sym_token7] = SHIFT(201),
    },
    [201] = {
        [ts_sym_type_expression] = SHIFT(202),
        [ts_sym_pointer_type] = SHIFT(183),
        [ts_sym_map_type] = SHIFT(183),
        [ts_sym_slice_type] = SHIFT(183),
        [ts_sym_struct_type] = SHIFT(183),
        [ts_sym_interface_type] = SHIFT(183),
        [ts_sym_type_name] = SHIFT(183),
        [ts_sym__map] = SHIFT(184),
        [ts_sym__interface] = SHIFT(189),
        [ts_sym__struct] = SHIFT(193),
        [ts_sym__identifier] = SHIFT(197),
        [ts_aux_sym_token5] = SHIFT(198),
        [ts_aux_sym_token6] = SHIFT(200),
    },
    [202] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__var] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__func] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__type] = REDUCE(ts_sym_slice_type, 3),
    },
    [203] = {
        [ts_sym__map] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__interface] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__struct] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_type_name, 1),
    },
    [204] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
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
        [ts_sym__import] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__var] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__func] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__type] = REDUCE(ts_sym_package_directive, 2),
    },
    [208] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__import] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__var] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__func] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__type] = REDUCE(ts_sym_package_name, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_golang);
