#include "tree_sitter/parser.h"

#define STATE_COUNT 196
#define SYMBOL_COUNT 52

enum {
    ts_sym__func = 2,
    ts_sym__func_signature = 3,
    ts_sym__identifier = 4,
    ts_sym__import = 5,
    ts_sym__interface = 6,
    ts_sym__map = 7,
    ts_sym__package = 8,
    ts_sym__struct = 9,
    ts_sym__type = 10,
    ts_sym__var = 11,
    ts_sym_declaration = 12,
    ts_sym_expression = 13,
    ts_sym_func_declaration = 14,
    ts_sym_imports_block = 15,
    ts_sym_interface_type = 16,
    ts_sym_map_type = 17,
    ts_sym_number = 18,
    ts_sym_package_directive = 19,
    ts_sym_package_import = 20,
    ts_sym_package_name = 21,
    ts_sym_pointer_type = 22,
    ts_sym_program = 23,
    ts_sym_slice_type = 24,
    ts_sym_statement_block = 25,
    ts_sym_string = 26,
    ts_sym_struct_type = 27,
    ts_sym_type_declaration = 28,
    ts_sym_type_expression = 29,
    ts_sym_type_name = 30,
    ts_sym_var_declaration = 31,
    ts_sym_var_name = 32,
    ts_aux_sym__func_signature_repeat1 = 33,
    ts_aux_sym__func_signature_repeat2 = 34,
    ts_aux_sym__func_signature_repeat3 = 35,
    ts_aux_sym__func_signature_repeat4 = 36,
    ts_aux_sym__func_signature_repeat5 = 37,
    ts_aux_sym_imports_block_repeat1 = 38,
    ts_aux_sym_interface_type_repeat1 = 39,
    ts_aux_sym_program_repeat1 = 40,
    ts_aux_sym_program_repeat2 = 41,
    ts_aux_sym_struct_type_repeat1 = 42,
    ts_aux_sym_token1 = 43,
    ts_aux_sym_token2 = 44,
    ts_aux_sym_token3 = 45,
    ts_aux_sym_token4 = 46,
    ts_aux_sym_token5 = 47,
    ts_aux_sym_token6 = 48,
    ts_aux_sym_token7 = 49,
    ts_aux_sym_token8 = 50,
    ts_aux_sym_token9 = 51,
};

SYMBOL_NAMES = {
    [ts_sym__func] = "_func",
    [ts_sym__func_signature] = "_func_signature",
    [ts_sym__identifier] = "_identifier",
    [ts_sym__import] = "_import",
    [ts_sym__interface] = "_interface",
    [ts_sym__map] = "_map",
    [ts_sym__package] = "_package",
    [ts_sym__struct] = "_struct",
    [ts_sym__type] = "_type",
    [ts_sym__var] = "_var",
    [ts_sym_declaration] = "declaration",
    [ts_sym_expression] = "expression",
    [ts_sym_func_declaration] = "func_declaration",
    [ts_sym_imports_block] = "imports_block",
    [ts_sym_interface_type] = "interface_type",
    [ts_sym_map_type] = "map_type",
    [ts_sym_number] = "number",
    [ts_sym_package_directive] = "package_directive",
    [ts_sym_package_import] = "package_import",
    [ts_sym_package_name] = "package_name",
    [ts_sym_pointer_type] = "pointer_type",
    [ts_sym_program] = "program",
    [ts_sym_slice_type] = "slice_type",
    [ts_sym_statement_block] = "statement_block",
    [ts_sym_string] = "string",
    [ts_sym_struct_type] = "struct_type",
    [ts_sym_type_declaration] = "type_declaration",
    [ts_sym_type_expression] = "type_expression",
    [ts_sym_type_name] = "type_name",
    [ts_sym_var_declaration] = "var_declaration",
    [ts_sym_var_name] = "var_name",
    [ts_aux_sym__func_signature_repeat1] = "_func_signature_repeat1",
    [ts_aux_sym__func_signature_repeat2] = "_func_signature_repeat2",
    [ts_aux_sym__func_signature_repeat3] = "_func_signature_repeat3",
    [ts_aux_sym__func_signature_repeat4] = "_func_signature_repeat4",
    [ts_aux_sym__func_signature_repeat5] = "_func_signature_repeat5",
    [ts_aux_sym_imports_block_repeat1] = "imports_block_repeat1",
    [ts_aux_sym_interface_type_repeat1] = "interface_type_repeat1",
    [ts_aux_sym_program_repeat1] = "program_repeat1",
    [ts_aux_sym_program_repeat2] = "program_repeat2",
    [ts_aux_sym_struct_type_repeat1] = "struct_type_repeat1",
    [ts_aux_sym_token1] = "'('",
    [ts_aux_sym_token2] = "')'",
    [ts_aux_sym_token3] = "'='",
    [ts_aux_sym_token4] = "'{'",
    [ts_aux_sym_token5] = "'}'",
    [ts_aux_sym_token6] = "'*'",
    [ts_aux_sym_token7] = "'['",
    [ts_aux_sym_token8] = "']'",
    [ts_aux_sym_token9] = "','",
    [ts_builtin_sym_end] = "EOF",
    [ts_builtin_sym_error] = "ERROR",
};

HIDDEN_SYMBOLS = {
    [ts_sym__func] = 1,
    [ts_sym__func_signature] = 1,
    [ts_sym__identifier] = 1,
    [ts_sym__import] = 1,
    [ts_sym__interface] = 1,
    [ts_sym__map] = 1,
    [ts_sym__package] = 1,
    [ts_sym__struct] = 1,
    [ts_sym__type] = 1,
    [ts_sym__var] = 1,
    [ts_aux_sym__func_signature_repeat1] = 1,
    [ts_aux_sym__func_signature_repeat2] = 1,
    [ts_aux_sym__func_signature_repeat3] = 1,
    [ts_aux_sym__func_signature_repeat4] = 1,
    [ts_aux_sym__func_signature_repeat5] = 1,
    [ts_aux_sym_imports_block_repeat1] = 1,
    [ts_aux_sym_interface_type_repeat1] = 1,
    [ts_aux_sym_program_repeat1] = 1,
    [ts_aux_sym_program_repeat2] = 1,
    [ts_aux_sym_struct_type_repeat1] = 1,
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
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == 'f')
                ADVANCE(2);
            if (lookahead == 'i')
                ADVANCE(6);
            if (lookahead == 't')
                ADVANCE(12);
            if (lookahead == 'v')
                ADVANCE(16);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            if (lookahead == 'u')
                ADVANCE(3);
            LEX_ERROR();
        case 3:
            if (lookahead == 'n')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (lookahead == 'c')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            ACCEPT_TOKEN(ts_sym__func);
        case 6:
            if (lookahead == 'm')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (lookahead == 'p')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'o')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (lookahead == 'r')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            if (lookahead == 't')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_sym__import);
        case 12:
            if (lookahead == 'y')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            if (lookahead == 'p')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            if (lookahead == 'e')
                ADVANCE(15);
            LEX_ERROR();
        case 15:
            ACCEPT_TOKEN(ts_sym__type);
        case 16:
            if (lookahead == 'a')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            if (lookahead == 'r')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            ACCEPT_TOKEN(ts_sym__var);
        case 19:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(19);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            LEX_ERROR();
        case 20:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__identifier);
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
            ACCEPT_TOKEN(ts_aux_sym_token2);
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
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 31:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(2);
            if (lookahead == 't')
                ADVANCE(12);
            if (lookahead == 'v')
                ADVANCE(16);
            LEX_ERROR();
        case 32:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(32);
            if (lookahead == '(')
                ADVANCE(30);
            LEX_ERROR();
        case 33:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(33);
            if (lookahead == '}')
                ADVANCE(34);
            LEX_ERROR();
        case 34:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 35:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(35);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 36:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 37:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (lookahead == '*')
                ADVANCE(38);
            if (lookahead == ',')
                ADVANCE(39);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(40);
            if (lookahead == 'i')
                ADVANCE(41);
            if (lookahead == 'm')
                ADVANCE(50);
            if (lookahead == 's')
                ADVANCE(53);
            LEX_ERROR();
        case 38:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 39:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 40:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 41:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'n')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 42:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 43:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 44:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(45);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 45:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'f')
                ADVANCE(46);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 46:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__interface);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'p')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__map);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'u')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__struct);
        case 59:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(59);
            if (lookahead == ')')
                ADVANCE(27);
            if (lookahead == ',')
                ADVANCE(39);
            LEX_ERROR();
        case 60:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(60);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == '}')
                ADVANCE(34);
            LEX_ERROR();
        case 61:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(61);
            if (lookahead == ']')
                ADVANCE(62);
            LEX_ERROR();
        case 62:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 63:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(63);
            if (lookahead == '*')
                ADVANCE(38);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(40);
            if (lookahead == 'i')
                ADVANCE(41);
            if (lookahead == 'm')
                ADVANCE(50);
            if (lookahead == 's')
                ADVANCE(53);
            LEX_ERROR();
        case 64:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == '[')
                ADVANCE(40);
            LEX_ERROR();
        case 65:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(65);
            if (lookahead == ')')
                ADVANCE(27);
            if (lookahead == ',')
                ADVANCE(39);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            LEX_ERROR();
        case 66:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(66);
            if (lookahead == '(')
                ADVANCE(30);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == '}')
                ADVANCE(34);
            LEX_ERROR();
        case 67:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (lookahead == ')')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            LEX_ERROR();
        case 68:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '(')
                ADVANCE(30);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == '{')
                ADVANCE(36);
            LEX_ERROR();
        case 69:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '=')
                ADVANCE(70);
            LEX_ERROR();
        case 70:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 71:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(72);
            LEX_ERROR();
        case 72:
            if (lookahead == '.')
                ADVANCE(73);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(72);
            ACCEPT_TOKEN(ts_sym_number);
        case 73:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(74);
            LEX_ERROR();
        case 74:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(74);
            ACCEPT_TOKEN(ts_sym_number);
        case 75:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            LEX_ERROR();
        case 76:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == 'p')
                ADVANCE(77);
            LEX_ERROR();
        case 77:
            if (lookahead == 'a')
                ADVANCE(78);
            LEX_ERROR();
        case 78:
            if (lookahead == 'c')
                ADVANCE(79);
            LEX_ERROR();
        case 79:
            if (lookahead == 'k')
                ADVANCE(80);
            LEX_ERROR();
        case 80:
            if (lookahead == 'a')
                ADVANCE(81);
            LEX_ERROR();
        case 81:
            if (lookahead == 'g')
                ADVANCE(82);
            LEX_ERROR();
        case 82:
            if (lookahead == 'e')
                ADVANCE(83);
            LEX_ERROR();
        case 83:
            ACCEPT_TOKEN(ts_sym__package);
        case 84:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(22);
            if (lookahead == '(')
                ADVANCE(30);
            if (lookahead == ')')
                ADVANCE(27);
            if (lookahead == '*')
                ADVANCE(38);
            if (lookahead == ',')
                ADVANCE(39);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(72);
            if (lookahead == '=')
                ADVANCE(70);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(40);
            if (lookahead == ']')
                ADVANCE(62);
            if (lookahead == 'f')
                ADVANCE(85);
            if (lookahead == 'i')
                ADVANCE(89);
            if (lookahead == 'm')
                ADVANCE(50);
            if (lookahead == 'p')
                ADVANCE(95);
            if (lookahead == 's')
                ADVANCE(53);
            if (lookahead == 't')
                ADVANCE(102);
            if (lookahead == 'v')
                ADVANCE(106);
            if (lookahead == '{')
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(34);
            LEX_ERROR();
        case 85:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'u')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 86:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'n')
                ADVANCE(87);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 87:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(88);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 88:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__func);
        case 89:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'm')
                ADVANCE(90);
            if (lookahead == 'n')
                ADVANCE(42);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'p')
                ADVANCE(91);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'o')
                ADVANCE(92);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 92:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(93);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__import);
        case 95:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 96:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 97:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'k')
                ADVANCE(98);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(99);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 99:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'g')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 100:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(101);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__package);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(20);
            if (lookahead == 'y')
                ADVANCE(103);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'p')
                ADVANCE(104);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 104:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(105);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 105:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__type);
        case 106:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(107);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 107:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 108:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__var);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(22);
            if (lookahead == '(')
                ADVANCE(30);
            if (lookahead == ')')
                ADVANCE(27);
            if (lookahead == '*')
                ADVANCE(38);
            if (lookahead == ',')
                ADVANCE(39);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(72);
            if (lookahead == '=')
                ADVANCE(70);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == '[')
                ADVANCE(40);
            if (lookahead == ']')
                ADVANCE(62);
            if (lookahead == 'f')
                ADVANCE(85);
            if (lookahead == 'i')
                ADVANCE(89);
            if (lookahead == 'm')
                ADVANCE(50);
            if (lookahead == 'p')
                ADVANCE(95);
            if (lookahead == 's')
                ADVANCE(53);
            if (lookahead == 't')
                ADVANCE(102);
            if (lookahead == 'v')
                ADVANCE(106);
            if (lookahead == '{')
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(34);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 76,
    [1] = 19,
    [2] = 0,
    [3] = 0,
    [4] = 0,
    [5] = 29,
    [6] = 0,
    [7] = 0,
    [8] = 21,
    [9] = 21,
    [10] = 21,
    [11] = 28,
    [12] = 28,
    [13] = 0,
    [14] = 0,
    [15] = 31,
    [16] = 31,
    [17] = 19,
    [18] = 32,
    [19] = 32,
    [20] = 35,
    [21] = 31,
    [22] = 33,
    [23] = 31,
    [24] = 67,
    [25] = 37,
    [26] = 37,
    [27] = 63,
    [28] = 59,
    [29] = 35,
    [30] = 60,
    [31] = 32,
    [32] = 60,
    [33] = 33,
    [34] = 67,
    [35] = 37,
    [36] = 63,
    [37] = 64,
    [38] = 63,
    [39] = 61,
    [40] = 35,
    [41] = 60,
    [42] = 33,
    [43] = 61,
    [44] = 64,
    [45] = 63,
    [46] = 35,
    [47] = 60,
    [48] = 63,
    [49] = 63,
    [50] = 60,
    [51] = 35,
    [52] = 60,
    [53] = 33,
    [54] = 60,
    [55] = 64,
    [56] = 63,
    [57] = 61,
    [58] = 61,
    [59] = 63,
    [60] = 35,
    [61] = 60,
    [62] = 33,
    [63] = 60,
    [64] = 60,
    [65] = 60,
    [66] = 63,
    [67] = 60,
    [68] = 61,
    [69] = 63,
    [70] = 60,
    [71] = 63,
    [72] = 61,
    [73] = 61,
    [74] = 63,
    [75] = 61,
    [76] = 60,
    [77] = 33,
    [78] = 33,
    [79] = 61,
    [80] = 61,
    [81] = 63,
    [82] = 61,
    [83] = 61,
    [84] = 63,
    [85] = 35,
    [86] = 60,
    [87] = 33,
    [88] = 59,
    [89] = 59,
    [90] = 59,
    [91] = 63,
    [92] = 59,
    [93] = 61,
    [94] = 63,
    [95] = 59,
    [96] = 59,
    [97] = 28,
    [98] = 66,
    [99] = 60,
    [100] = 19,
    [101] = 65,
    [102] = 59,
    [103] = 28,
    [104] = 60,
    [105] = 19,
    [106] = 59,
    [107] = 28,
    [108] = 19,
    [109] = 59,
    [110] = 28,
    [111] = 60,
    [112] = 19,
    [113] = 19,
    [114] = 19,
    [115] = 59,
    [116] = 28,
    [117] = 19,
    [118] = 37,
    [119] = 63,
    [120] = 59,
    [121] = 28,
    [122] = 19,
    [123] = 37,
    [124] = 63,
    [125] = 19,
    [126] = 37,
    [127] = 63,
    [128] = 66,
    [129] = 60,
    [130] = 19,
    [131] = 59,
    [132] = 28,
    [133] = 60,
    [134] = 19,
    [135] = 59,
    [136] = 28,
    [137] = 33,
    [138] = 59,
    [139] = 59,
    [140] = 28,
    [141] = 68,
    [142] = 35,
    [143] = 35,
    [144] = 19,
    [145] = 59,
    [146] = 28,
    [147] = 35,
    [148] = 19,
    [149] = 59,
    [150] = 28,
    [151] = 35,
    [152] = 68,
    [153] = 35,
    [154] = 19,
    [155] = 59,
    [156] = 28,
    [157] = 35,
    [158] = 19,
    [159] = 59,
    [160] = 28,
    [161] = 19,
    [162] = 63,
    [163] = 63,
    [164] = 31,
    [165] = 35,
    [166] = 60,
    [167] = 33,
    [168] = 31,
    [169] = 64,
    [170] = 63,
    [171] = 61,
    [172] = 63,
    [173] = 35,
    [174] = 60,
    [175] = 33,
    [176] = 31,
    [177] = 31,
    [178] = 31,
    [179] = 63,
    [180] = 31,
    [181] = 61,
    [182] = 63,
    [183] = 31,
    [184] = 31,
    [185] = 19,
    [186] = 69,
    [187] = 69,
    [188] = 71,
    [189] = 31,
    [190] = 31,
    [191] = 31,
    [192] = 31,
    [193] = 75,
    [194] = 75,
    [195] = 75,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym__package] = SHIFT(1),
        [ts_sym_package_directive] = SHIFT(4),
        [ts_sym_program] = SHIFT(195),
    },
    [1] = {
        [ts_sym__identifier] = SHIFT(2),
        [ts_sym_package_name] = SHIFT(3),
    },
    [2] = {
        [ts_sym__func] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__import] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__type] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__var] = REDUCE(ts_sym_package_name, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
    },
    [3] = {
        [ts_sym__func] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__import] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__type] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__var] = REDUCE(ts_sym_package_directive, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_directive, 2),
    },
    [4] = {
        [ts_sym__func] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym__import] = SHIFT(5),
        [ts_sym__type] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym__var] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym_imports_block] = SHIFT(14),
        [ts_aux_sym_program_repeat1] = SHIFT(16),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
    },
    [5] = {
        [ts_sym_package_import] = SHIFT(6),
        [ts_sym_string] = SHIFT(7),
        [ts_aux_sym_token1] = SHIFT(8),
    },
    [6] = {
        [ts_sym__func] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__import] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__type] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__var] = REDUCE(ts_sym_imports_block, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
    },
    [7] = {
        [ts_sym__func] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__import] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__type] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__var] = REDUCE(ts_sym_package_import, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
    },
    [8] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_sym_string] = SHIFT(10),
        [ts_aux_sym_imports_block_repeat1] = SHIFT(12),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_imports_block_repeat1, 0),
        [ts_builtin_sym_error] = SHIFT(12),
    },
    [9] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_sym_string] = SHIFT(10),
        [ts_aux_sym_imports_block_repeat1] = SHIFT(11),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_imports_block_repeat1, 0),
    },
    [10] = {
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_package_import, 1),
    },
    [11] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_imports_block_repeat1, 2),
    },
    [12] = {
        [ts_aux_sym_token2] = SHIFT(13),
    },
    [13] = {
        [ts_sym__func] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__import] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__type] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__var] = REDUCE(ts_sym_imports_block, 4),
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
    },
    [14] = {
        [ts_sym__func] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym__import] = SHIFT(5),
        [ts_sym__type] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym__var] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym_imports_block] = SHIFT(14),
        [ts_aux_sym_program_repeat1] = SHIFT(15),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
    },
    [15] = {
        [ts_sym__func] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_sym__type] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_sym__var] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
    },
    [16] = {
        [ts_sym__func] = SHIFT(17),
        [ts_sym__type] = SHIFT(161),
        [ts_sym__var] = SHIFT(185),
        [ts_sym_declaration] = SHIFT(191),
        [ts_sym_func_declaration] = SHIFT(192),
        [ts_sym_type_declaration] = SHIFT(192),
        [ts_sym_var_declaration] = SHIFT(192),
        [ts_aux_sym_program_repeat2] = SHIFT(194),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat2, 0),
    },
    [17] = {
        [ts_sym__identifier] = SHIFT(18),
        [ts_sym_var_name] = SHIFT(19),
    },
    [18] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_var_name, 1),
    },
    [19] = {
        [ts_sym__func_signature] = SHIFT(20),
        [ts_aux_sym_token1] = SHIFT(24),
    },
    [20] = {
        [ts_sym_statement_block] = SHIFT(21),
        [ts_aux_sym_token4] = SHIFT(22),
    },
    [21] = {
        [ts_sym__func] = REDUCE(ts_sym_func_declaration, 4),
        [ts_sym__type] = REDUCE(ts_sym_func_declaration, 4),
        [ts_sym__var] = REDUCE(ts_sym_func_declaration, 4),
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 4),
    },
    [22] = {
        [ts_aux_sym_token5] = SHIFT(23),
    },
    [23] = {
        [ts_sym__func] = REDUCE(ts_sym_statement_block, 2),
        [ts_sym__type] = REDUCE(ts_sym_statement_block, 2),
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 2),
    },
    [24] = {
        [ts_sym__identifier] = SHIFT(25),
        [ts_sym_var_name] = SHIFT(26),
        [ts_aux_sym_token2] = SHIFT(152),
    },
    [25] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__interface] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__map] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_name, 1),
    },
    [26] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(27),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [27] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym__interface] = SHIFT(29),
        [ts_sym__map] = SHIFT(37),
        [ts_sym__struct] = SHIFT(85),
        [ts_sym_interface_type] = SHIFT(89),
        [ts_sym_map_type] = SHIFT(89),
        [ts_sym_pointer_type] = SHIFT(89),
        [ts_sym_slice_type] = SHIFT(89),
        [ts_sym_struct_type] = SHIFT(89),
        [ts_sym_type_expression] = SHIFT(139),
        [ts_sym_type_name] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(91),
        [ts_aux_sym_token7] = SHIFT(93),
    },
    [28] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_type_name, 1),
    },
    [29] = {
        [ts_aux_sym_token4] = SHIFT(30),
    },
    [30] = {
        [ts_sym__identifier] = SHIFT(18),
        [ts_sym_var_name] = SHIFT(31),
        [ts_aux_sym_interface_type_repeat1] = SHIFT(137),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_interface_type_repeat1, 0),
    },
    [31] = {
        [ts_sym__func_signature] = SHIFT(32),
        [ts_aux_sym_token1] = SHIFT(34),
    },
    [32] = {
        [ts_sym__identifier] = SHIFT(18),
        [ts_sym_var_name] = SHIFT(31),
        [ts_aux_sym_interface_type_repeat1] = SHIFT(33),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_interface_type_repeat1, 0),
    },
    [33] = {
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_interface_type_repeat1, 3),
    },
    [34] = {
        [ts_sym__identifier] = SHIFT(25),
        [ts_sym_var_name] = SHIFT(35),
        [ts_aux_sym_token2] = SHIFT(128),
    },
    [35] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(36),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [36] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym__interface] = SHIFT(29),
        [ts_sym__map] = SHIFT(37),
        [ts_sym__struct] = SHIFT(85),
        [ts_sym_interface_type] = SHIFT(89),
        [ts_sym_map_type] = SHIFT(89),
        [ts_sym_pointer_type] = SHIFT(89),
        [ts_sym_slice_type] = SHIFT(89),
        [ts_sym_struct_type] = SHIFT(89),
        [ts_sym_type_expression] = SHIFT(96),
        [ts_sym_type_name] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(91),
        [ts_aux_sym_token7] = SHIFT(93),
    },
    [37] = {
        [ts_aux_sym_token7] = SHIFT(38),
    },
    [38] = {
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym__interface] = SHIFT(40),
        [ts_sym__map] = SHIFT(44),
        [ts_sym__struct] = SHIFT(46),
        [ts_sym_interface_type] = SHIFT(57),
        [ts_sym_map_type] = SHIFT(57),
        [ts_sym_pointer_type] = SHIFT(57),
        [ts_sym_slice_type] = SHIFT(57),
        [ts_sym_struct_type] = SHIFT(57),
        [ts_sym_type_expression] = SHIFT(83),
        [ts_sym_type_name] = SHIFT(57),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
    },
    [39] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym_type_name, 1),
    },
    [40] = {
        [ts_aux_sym_token4] = SHIFT(41),
    },
    [41] = {
        [ts_sym__identifier] = SHIFT(18),
        [ts_sym_var_name] = SHIFT(31),
        [ts_aux_sym_interface_type_repeat1] = SHIFT(42),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_interface_type_repeat1, 0),
    },
    [42] = {
        [ts_aux_sym_token5] = SHIFT(43),
    },
    [43] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym_interface_type, 4),
    },
    [44] = {
        [ts_aux_sym_token7] = SHIFT(45),
    },
    [45] = {
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym__interface] = SHIFT(40),
        [ts_sym__map] = SHIFT(44),
        [ts_sym__struct] = SHIFT(46),
        [ts_sym_interface_type] = SHIFT(57),
        [ts_sym_map_type] = SHIFT(57),
        [ts_sym_pointer_type] = SHIFT(57),
        [ts_sym_slice_type] = SHIFT(57),
        [ts_sym_struct_type] = SHIFT(57),
        [ts_sym_type_expression] = SHIFT(80),
        [ts_sym_type_name] = SHIFT(57),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
    },
    [46] = {
        [ts_aux_sym_token4] = SHIFT(47),
    },
    [47] = {
        [ts_sym__identifier] = SHIFT(48),
        [ts_sym_var_name] = SHIFT(49),
        [ts_aux_sym_struct_type_repeat1] = SHIFT(78),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_struct_type_repeat1, 0),
    },
    [48] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__interface] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__map] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_name, 1),
    },
    [49] = {
        [ts_sym__identifier] = SHIFT(50),
        [ts_sym__interface] = SHIFT(51),
        [ts_sym__map] = SHIFT(55),
        [ts_sym__struct] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(64),
        [ts_sym_map_type] = SHIFT(64),
        [ts_sym_pointer_type] = SHIFT(64),
        [ts_sym_slice_type] = SHIFT(64),
        [ts_sym_struct_type] = SHIFT(64),
        [ts_sym_type_expression] = SHIFT(76),
        [ts_sym_type_name] = SHIFT(64),
        [ts_aux_sym_token6] = SHIFT(66),
        [ts_aux_sym_token7] = SHIFT(68),
    },
    [50] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_name, 1),
    },
    [51] = {
        [ts_aux_sym_token4] = SHIFT(52),
    },
    [52] = {
        [ts_sym__identifier] = SHIFT(18),
        [ts_sym_var_name] = SHIFT(31),
        [ts_aux_sym_interface_type_repeat1] = SHIFT(53),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_interface_type_repeat1, 0),
    },
    [53] = {
        [ts_aux_sym_token5] = SHIFT(54),
    },
    [54] = {
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_interface_type, 4),
    },
    [55] = {
        [ts_aux_sym_token7] = SHIFT(56),
    },
    [56] = {
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym__interface] = SHIFT(40),
        [ts_sym__map] = SHIFT(44),
        [ts_sym__struct] = SHIFT(46),
        [ts_sym_interface_type] = SHIFT(57),
        [ts_sym_map_type] = SHIFT(57),
        [ts_sym_pointer_type] = SHIFT(57),
        [ts_sym_slice_type] = SHIFT(57),
        [ts_sym_struct_type] = SHIFT(57),
        [ts_sym_type_expression] = SHIFT(58),
        [ts_sym_type_name] = SHIFT(57),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
    },
    [57] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym_type_expression, 1),
    },
    [58] = {
        [ts_aux_sym_token8] = SHIFT(59),
    },
    [59] = {
        [ts_sym__identifier] = SHIFT(50),
        [ts_sym__interface] = SHIFT(51),
        [ts_sym__map] = SHIFT(55),
        [ts_sym__struct] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(64),
        [ts_sym_map_type] = SHIFT(64),
        [ts_sym_pointer_type] = SHIFT(64),
        [ts_sym_slice_type] = SHIFT(64),
        [ts_sym_struct_type] = SHIFT(64),
        [ts_sym_type_expression] = SHIFT(65),
        [ts_sym_type_name] = SHIFT(64),
        [ts_aux_sym_token6] = SHIFT(66),
        [ts_aux_sym_token7] = SHIFT(68),
    },
    [60] = {
        [ts_aux_sym_token4] = SHIFT(61),
    },
    [61] = {
        [ts_sym__identifier] = SHIFT(48),
        [ts_sym_var_name] = SHIFT(49),
        [ts_aux_sym_struct_type_repeat1] = SHIFT(62),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_struct_type_repeat1, 0),
    },
    [62] = {
        [ts_aux_sym_token5] = SHIFT(63),
    },
    [63] = {
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token5] = REDUCE(ts_sym_struct_type, 4),
    },
    [64] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_expression, 1),
    },
    [65] = {
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token5] = REDUCE(ts_sym_map_type, 5),
    },
    [66] = {
        [ts_sym__identifier] = SHIFT(50),
        [ts_sym__interface] = SHIFT(51),
        [ts_sym__map] = SHIFT(55),
        [ts_sym__struct] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(64),
        [ts_sym_map_type] = SHIFT(64),
        [ts_sym_pointer_type] = SHIFT(64),
        [ts_sym_slice_type] = SHIFT(64),
        [ts_sym_struct_type] = SHIFT(64),
        [ts_sym_type_expression] = SHIFT(67),
        [ts_sym_type_name] = SHIFT(64),
        [ts_aux_sym_token6] = SHIFT(66),
        [ts_aux_sym_token7] = SHIFT(68),
    },
    [67] = {
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token5] = REDUCE(ts_sym_pointer_type, 2),
    },
    [68] = {
        [ts_aux_sym_token8] = SHIFT(69),
    },
    [69] = {
        [ts_sym__identifier] = SHIFT(50),
        [ts_sym__interface] = SHIFT(51),
        [ts_sym__map] = SHIFT(55),
        [ts_sym__struct] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(64),
        [ts_sym_map_type] = SHIFT(64),
        [ts_sym_pointer_type] = SHIFT(64),
        [ts_sym_slice_type] = SHIFT(64),
        [ts_sym_struct_type] = SHIFT(64),
        [ts_sym_type_expression] = SHIFT(70),
        [ts_sym_type_name] = SHIFT(64),
        [ts_aux_sym_token6] = SHIFT(66),
        [ts_aux_sym_token7] = SHIFT(68),
    },
    [70] = {
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym_slice_type, 3),
    },
    [71] = {
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym__interface] = SHIFT(40),
        [ts_sym__map] = SHIFT(44),
        [ts_sym__struct] = SHIFT(46),
        [ts_sym_interface_type] = SHIFT(57),
        [ts_sym_map_type] = SHIFT(57),
        [ts_sym_pointer_type] = SHIFT(57),
        [ts_sym_slice_type] = SHIFT(57),
        [ts_sym_struct_type] = SHIFT(57),
        [ts_sym_type_expression] = SHIFT(72),
        [ts_sym_type_name] = SHIFT(57),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
    },
    [72] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym_pointer_type, 2),
    },
    [73] = {
        [ts_aux_sym_token8] = SHIFT(74),
    },
    [74] = {
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym__interface] = SHIFT(40),
        [ts_sym__map] = SHIFT(44),
        [ts_sym__struct] = SHIFT(46),
        [ts_sym_interface_type] = SHIFT(57),
        [ts_sym_map_type] = SHIFT(57),
        [ts_sym_pointer_type] = SHIFT(57),
        [ts_sym_slice_type] = SHIFT(57),
        [ts_sym_struct_type] = SHIFT(57),
        [ts_sym_type_expression] = SHIFT(75),
        [ts_sym_type_name] = SHIFT(57),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
    },
    [75] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym_slice_type, 3),
    },
    [76] = {
        [ts_sym__identifier] = SHIFT(48),
        [ts_sym_var_name] = SHIFT(49),
        [ts_aux_sym_struct_type_repeat1] = SHIFT(77),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_struct_type_repeat1, 0),
    },
    [77] = {
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_struct_type_repeat1, 3),
    },
    [78] = {
        [ts_aux_sym_token5] = SHIFT(79),
    },
    [79] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym_struct_type, 4),
    },
    [80] = {
        [ts_aux_sym_token8] = SHIFT(81),
    },
    [81] = {
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym__interface] = SHIFT(40),
        [ts_sym__map] = SHIFT(44),
        [ts_sym__struct] = SHIFT(46),
        [ts_sym_interface_type] = SHIFT(57),
        [ts_sym_map_type] = SHIFT(57),
        [ts_sym_pointer_type] = SHIFT(57),
        [ts_sym_slice_type] = SHIFT(57),
        [ts_sym_struct_type] = SHIFT(57),
        [ts_sym_type_expression] = SHIFT(82),
        [ts_sym_type_name] = SHIFT(57),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
    },
    [82] = {
        [ts_aux_sym_token8] = REDUCE(ts_sym_map_type, 5),
    },
    [83] = {
        [ts_aux_sym_token8] = SHIFT(84),
    },
    [84] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym__interface] = SHIFT(29),
        [ts_sym__map] = SHIFT(37),
        [ts_sym__struct] = SHIFT(85),
        [ts_sym_interface_type] = SHIFT(89),
        [ts_sym_map_type] = SHIFT(89),
        [ts_sym_pointer_type] = SHIFT(89),
        [ts_sym_slice_type] = SHIFT(89),
        [ts_sym_struct_type] = SHIFT(89),
        [ts_sym_type_expression] = SHIFT(90),
        [ts_sym_type_name] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(91),
        [ts_aux_sym_token7] = SHIFT(93),
    },
    [85] = {
        [ts_aux_sym_token4] = SHIFT(86),
    },
    [86] = {
        [ts_sym__identifier] = SHIFT(48),
        [ts_sym_var_name] = SHIFT(49),
        [ts_aux_sym_struct_type_repeat1] = SHIFT(87),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_struct_type_repeat1, 0),
    },
    [87] = {
        [ts_aux_sym_token5] = SHIFT(88),
    },
    [88] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_struct_type, 4),
    },
    [89] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_type_expression, 1),
    },
    [90] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token9] = REDUCE(ts_sym_map_type, 5),
    },
    [91] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym__interface] = SHIFT(29),
        [ts_sym__map] = SHIFT(37),
        [ts_sym__struct] = SHIFT(85),
        [ts_sym_interface_type] = SHIFT(89),
        [ts_sym_map_type] = SHIFT(89),
        [ts_sym_pointer_type] = SHIFT(89),
        [ts_sym_slice_type] = SHIFT(89),
        [ts_sym_struct_type] = SHIFT(89),
        [ts_sym_type_expression] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(91),
        [ts_aux_sym_token7] = SHIFT(93),
    },
    [92] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token9] = REDUCE(ts_sym_pointer_type, 2),
    },
    [93] = {
        [ts_aux_sym_token8] = SHIFT(94),
    },
    [94] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym__interface] = SHIFT(29),
        [ts_sym__map] = SHIFT(37),
        [ts_sym__struct] = SHIFT(85),
        [ts_sym_interface_type] = SHIFT(89),
        [ts_sym_map_type] = SHIFT(89),
        [ts_sym_pointer_type] = SHIFT(89),
        [ts_sym_slice_type] = SHIFT(89),
        [ts_sym_struct_type] = SHIFT(89),
        [ts_sym_type_expression] = SHIFT(95),
        [ts_sym_type_name] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(91),
        [ts_aux_sym_token7] = SHIFT(93),
    },
    [95] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token9] = REDUCE(ts_sym_slice_type, 3),
    },
    [96] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(97),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token9] = SHIFT(117),
    },
    [97] = {
        [ts_aux_sym_token2] = SHIFT(98),
    },
    [98] = {
        [ts_sym__identifier] = SHIFT(50),
        [ts_sym_type_name] = SHIFT(99),
        [ts_aux_sym_token1] = SHIFT(100),
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 6),
    },
    [99] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 7),
    },
    [100] = {
        [ts_sym__identifier] = SHIFT(101),
        [ts_sym_type_name] = SHIFT(102),
        [ts_sym_var_name] = SHIFT(108),
    },
    [101] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token9] = REDUCE(ts_sym_type_name, 1),
    },
    [102] = {
        [ts_aux_sym__func_signature_repeat5] = SHIFT(103),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat5, 0),
        [ts_aux_sym_token9] = SHIFT(105),
    },
    [103] = {
        [ts_aux_sym_token2] = SHIFT(104),
    },
    [104] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 10),
    },
    [105] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_type_name] = SHIFT(106),
    },
    [106] = {
        [ts_aux_sym__func_signature_repeat5] = SHIFT(107),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat5, 0),
        [ts_aux_sym_token9] = SHIFT(105),
    },
    [107] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat5, 3),
    },
    [108] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_type_name] = SHIFT(109),
    },
    [109] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(110),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token9] = SHIFT(112),
    },
    [110] = {
        [ts_aux_sym_token2] = SHIFT(111),
    },
    [111] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 11),
    },
    [112] = {
        [ts_sym__identifier] = SHIFT(113),
        [ts_sym_var_name] = SHIFT(114),
    },
    [113] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
    },
    [114] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_type_name] = SHIFT(115),
    },
    [115] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(116),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token9] = SHIFT(112),
    },
    [116] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat4, 4),
    },
    [117] = {
        [ts_sym__identifier] = SHIFT(25),
        [ts_sym_var_name] = SHIFT(118),
    },
    [118] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(119),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token9] = SHIFT(122),
    },
    [119] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym__interface] = SHIFT(29),
        [ts_sym__map] = SHIFT(37),
        [ts_sym__struct] = SHIFT(85),
        [ts_sym_interface_type] = SHIFT(89),
        [ts_sym_map_type] = SHIFT(89),
        [ts_sym_pointer_type] = SHIFT(89),
        [ts_sym_slice_type] = SHIFT(89),
        [ts_sym_struct_type] = SHIFT(89),
        [ts_sym_type_expression] = SHIFT(120),
        [ts_sym_type_name] = SHIFT(89),
        [ts_aux_sym_token6] = SHIFT(91),
        [ts_aux_sym_token7] = SHIFT(93),
    },
    [120] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(121),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token9] = SHIFT(117),
    },
    [121] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat3, 5),
    },
    [122] = {
        [ts_sym__identifier] = SHIFT(25),
        [ts_sym_var_name] = SHIFT(123),
    },
    [123] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(124),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token9] = SHIFT(122),
    },
    [124] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat2, 3),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat2, 3),
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat2, 3),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat2, 3),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat2, 3),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym__func_signature_repeat2, 3),
    },
    [125] = {
        [ts_sym__identifier] = SHIFT(25),
        [ts_sym_var_name] = SHIFT(126),
    },
    [126] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(127),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [127] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [128] = {
        [ts_sym__identifier] = SHIFT(50),
        [ts_sym_type_name] = SHIFT(129),
        [ts_aux_sym_token1] = SHIFT(130),
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 2),
    },
    [129] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 3),
    },
    [130] = {
        [ts_sym__identifier] = SHIFT(101),
        [ts_sym_type_name] = SHIFT(131),
        [ts_sym_var_name] = SHIFT(134),
    },
    [131] = {
        [ts_aux_sym__func_signature_repeat5] = SHIFT(132),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat5, 0),
        [ts_aux_sym_token9] = SHIFT(105),
    },
    [132] = {
        [ts_aux_sym_token2] = SHIFT(133),
    },
    [133] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 6),
    },
    [134] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_type_name] = SHIFT(135),
    },
    [135] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(136),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token9] = SHIFT(112),
    },
    [136] = {
        [ts_aux_sym_token2] = SHIFT(99),
    },
    [137] = {
        [ts_aux_sym_token5] = SHIFT(138),
    },
    [138] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token9] = REDUCE(ts_sym_interface_type, 4),
    },
    [139] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(140),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token9] = SHIFT(117),
    },
    [140] = {
        [ts_aux_sym_token2] = SHIFT(141),
    },
    [141] = {
        [ts_sym__identifier] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(143),
        [ts_aux_sym_token1] = SHIFT(144),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 6),
    },
    [142] = {
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_name, 1),
    },
    [143] = {
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 7),
    },
    [144] = {
        [ts_sym__identifier] = SHIFT(101),
        [ts_sym_type_name] = SHIFT(145),
        [ts_sym_var_name] = SHIFT(148),
    },
    [145] = {
        [ts_aux_sym__func_signature_repeat5] = SHIFT(146),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat5, 0),
        [ts_aux_sym_token9] = SHIFT(105),
    },
    [146] = {
        [ts_aux_sym_token2] = SHIFT(147),
    },
    [147] = {
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 10),
    },
    [148] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_type_name] = SHIFT(149),
    },
    [149] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(150),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token9] = SHIFT(112),
    },
    [150] = {
        [ts_aux_sym_token2] = SHIFT(151),
    },
    [151] = {
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 11),
    },
    [152] = {
        [ts_sym__identifier] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(153),
        [ts_aux_sym_token1] = SHIFT(154),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 2),
    },
    [153] = {
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 3),
    },
    [154] = {
        [ts_sym__identifier] = SHIFT(101),
        [ts_sym_type_name] = SHIFT(155),
        [ts_sym_var_name] = SHIFT(158),
    },
    [155] = {
        [ts_aux_sym__func_signature_repeat5] = SHIFT(156),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat5, 0),
        [ts_aux_sym_token9] = SHIFT(105),
    },
    [156] = {
        [ts_aux_sym_token2] = SHIFT(157),
    },
    [157] = {
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 6),
    },
    [158] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_type_name] = SHIFT(159),
    },
    [159] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(160),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token9] = SHIFT(112),
    },
    [160] = {
        [ts_aux_sym_token2] = SHIFT(143),
    },
    [161] = {
        [ts_sym__identifier] = SHIFT(162),
        [ts_sym_type_name] = SHIFT(163),
    },
    [162] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__interface] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__map] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__struct] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_name, 1),
    },
    [163] = {
        [ts_sym__identifier] = SHIFT(164),
        [ts_sym__interface] = SHIFT(165),
        [ts_sym__map] = SHIFT(169),
        [ts_sym__struct] = SHIFT(173),
        [ts_sym_interface_type] = SHIFT(177),
        [ts_sym_map_type] = SHIFT(177),
        [ts_sym_pointer_type] = SHIFT(177),
        [ts_sym_slice_type] = SHIFT(177),
        [ts_sym_struct_type] = SHIFT(177),
        [ts_sym_type_expression] = SHIFT(184),
        [ts_sym_type_name] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
    },
    [164] = {
        [ts_sym__func] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__type] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__var] = REDUCE(ts_sym_type_name, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_name, 1),
    },
    [165] = {
        [ts_aux_sym_token4] = SHIFT(166),
    },
    [166] = {
        [ts_sym__identifier] = SHIFT(18),
        [ts_sym_var_name] = SHIFT(31),
        [ts_aux_sym_interface_type_repeat1] = SHIFT(167),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_interface_type_repeat1, 0),
    },
    [167] = {
        [ts_aux_sym_token5] = SHIFT(168),
    },
    [168] = {
        [ts_sym__func] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__type] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__var] = REDUCE(ts_sym_interface_type, 4),
        [ts_builtin_sym_end] = REDUCE(ts_sym_interface_type, 4),
    },
    [169] = {
        [ts_aux_sym_token7] = SHIFT(170),
    },
    [170] = {
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym__interface] = SHIFT(40),
        [ts_sym__map] = SHIFT(44),
        [ts_sym__struct] = SHIFT(46),
        [ts_sym_interface_type] = SHIFT(57),
        [ts_sym_map_type] = SHIFT(57),
        [ts_sym_pointer_type] = SHIFT(57),
        [ts_sym_slice_type] = SHIFT(57),
        [ts_sym_struct_type] = SHIFT(57),
        [ts_sym_type_expression] = SHIFT(171),
        [ts_sym_type_name] = SHIFT(57),
        [ts_aux_sym_token6] = SHIFT(71),
        [ts_aux_sym_token7] = SHIFT(73),
    },
    [171] = {
        [ts_aux_sym_token8] = SHIFT(172),
    },
    [172] = {
        [ts_sym__identifier] = SHIFT(164),
        [ts_sym__interface] = SHIFT(165),
        [ts_sym__map] = SHIFT(169),
        [ts_sym__struct] = SHIFT(173),
        [ts_sym_interface_type] = SHIFT(177),
        [ts_sym_map_type] = SHIFT(177),
        [ts_sym_pointer_type] = SHIFT(177),
        [ts_sym_slice_type] = SHIFT(177),
        [ts_sym_struct_type] = SHIFT(177),
        [ts_sym_type_expression] = SHIFT(178),
        [ts_sym_type_name] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
    },
    [173] = {
        [ts_aux_sym_token4] = SHIFT(174),
    },
    [174] = {
        [ts_sym__identifier] = SHIFT(48),
        [ts_sym_var_name] = SHIFT(49),
        [ts_aux_sym_struct_type_repeat1] = SHIFT(175),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_struct_type_repeat1, 0),
    },
    [175] = {
        [ts_aux_sym_token5] = SHIFT(176),
    },
    [176] = {
        [ts_sym__func] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__type] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__var] = REDUCE(ts_sym_struct_type, 4),
        [ts_builtin_sym_end] = REDUCE(ts_sym_struct_type, 4),
    },
    [177] = {
        [ts_sym__func] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__type] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__var] = REDUCE(ts_sym_type_expression, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_expression, 1),
    },
    [178] = {
        [ts_sym__func] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__type] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__var] = REDUCE(ts_sym_map_type, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_map_type, 5),
    },
    [179] = {
        [ts_sym__identifier] = SHIFT(164),
        [ts_sym__interface] = SHIFT(165),
        [ts_sym__map] = SHIFT(169),
        [ts_sym__struct] = SHIFT(173),
        [ts_sym_interface_type] = SHIFT(177),
        [ts_sym_map_type] = SHIFT(177),
        [ts_sym_pointer_type] = SHIFT(177),
        [ts_sym_slice_type] = SHIFT(177),
        [ts_sym_struct_type] = SHIFT(177),
        [ts_sym_type_expression] = SHIFT(180),
        [ts_sym_type_name] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
    },
    [180] = {
        [ts_sym__func] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__type] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__var] = REDUCE(ts_sym_pointer_type, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_pointer_type, 2),
    },
    [181] = {
        [ts_aux_sym_token8] = SHIFT(182),
    },
    [182] = {
        [ts_sym__identifier] = SHIFT(164),
        [ts_sym__interface] = SHIFT(165),
        [ts_sym__map] = SHIFT(169),
        [ts_sym__struct] = SHIFT(173),
        [ts_sym_interface_type] = SHIFT(177),
        [ts_sym_map_type] = SHIFT(177),
        [ts_sym_pointer_type] = SHIFT(177),
        [ts_sym_slice_type] = SHIFT(177),
        [ts_sym_struct_type] = SHIFT(177),
        [ts_sym_type_expression] = SHIFT(183),
        [ts_sym_type_name] = SHIFT(177),
        [ts_aux_sym_token6] = SHIFT(179),
        [ts_aux_sym_token7] = SHIFT(181),
    },
    [183] = {
        [ts_sym__func] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__type] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__var] = REDUCE(ts_sym_slice_type, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_slice_type, 3),
    },
    [184] = {
        [ts_sym__func] = REDUCE(ts_sym_type_declaration, 3),
        [ts_sym__type] = REDUCE(ts_sym_type_declaration, 3),
        [ts_sym__var] = REDUCE(ts_sym_type_declaration, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 3),
    },
    [185] = {
        [ts_sym__identifier] = SHIFT(186),
        [ts_sym_var_name] = SHIFT(187),
    },
    [186] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_name, 1),
    },
    [187] = {
        [ts_aux_sym_token3] = SHIFT(188),
    },
    [188] = {
        [ts_sym_expression] = SHIFT(189),
        [ts_sym_number] = SHIFT(190),
    },
    [189] = {
        [ts_sym__func] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__type] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
    },
    [190] = {
        [ts_sym__func] = REDUCE(ts_sym_expression, 1),
        [ts_sym__type] = REDUCE(ts_sym_expression, 1),
        [ts_sym__var] = REDUCE(ts_sym_expression, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
    },
    [191] = {
        [ts_sym__func] = SHIFT(17),
        [ts_sym__type] = SHIFT(161),
        [ts_sym__var] = SHIFT(185),
        [ts_sym_declaration] = SHIFT(191),
        [ts_sym_func_declaration] = SHIFT(192),
        [ts_sym_type_declaration] = SHIFT(192),
        [ts_sym_var_declaration] = SHIFT(192),
        [ts_aux_sym_program_repeat2] = SHIFT(193),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat2, 0),
    },
    [192] = {
        [ts_sym__func] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__type] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__var] = REDUCE(ts_sym_declaration, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
    },
    [193] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat2, 2),
    },
    [194] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
    },
    [195] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_golang);
