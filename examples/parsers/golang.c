#include "tree_sitter/parser.h"

#define STATE_COUNT 196
#define SYMBOL_COUNT 52

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
    ts_sym_expression = 11,
    ts_sym_type_expression = 12,
    ts_sym_pointer_type = 13,
    ts_sym_map_type = 14,
    ts_sym_slice_type = 15,
    ts_sym_struct_type = 16,
    ts_sym_interface_type = 17,
    ts_sym__func_signature = 18,
    ts_sym_package_name = 19,
    ts_sym_var_name = 20,
    ts_sym_type_name = 21,
    ts_sym__map = 22,
    ts_sym__interface = 23,
    ts_sym__struct = 24,
    ts_sym__package = 25,
    ts_sym__import = 26,
    ts_sym__var = 27,
    ts_sym__func = 28,
    ts_sym__type = 29,
    ts_sym_string = 30,
    ts_sym__identifier = 31,
    ts_sym_number = 32,
    ts_aux_sym_program_repeat0 = 33,
    ts_aux_sym_program_repeat1 = 34,
    ts_aux_sym_imports_block_repeat0 = 35,
    ts_aux_sym_struct_type_repeat0 = 36,
    ts_aux_sym_interface_type_repeat0 = 37,
    ts_aux_sym__func_signature_repeat0 = 38,
    ts_aux_sym__func_signature_repeat1 = 39,
    ts_aux_sym__func_signature_repeat2 = 40,
    ts_aux_sym__func_signature_repeat3 = 41,
    ts_aux_sym__func_signature_repeat4 = 42,
    ts_aux_sym_token0 = 43,
    ts_aux_sym_token1 = 44,
    ts_aux_sym_token2 = 45,
    ts_aux_sym_token3 = 46,
    ts_aux_sym_token4 = 47,
    ts_aux_sym_token5 = 48,
    ts_aux_sym_token6 = 49,
    ts_aux_sym_token7 = 50,
    ts_aux_sym_token8 = 51,
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
    [ts_sym_expression] = "expression",
    [ts_sym_type_expression] = "type_expression",
    [ts_sym_pointer_type] = "pointer_type",
    [ts_sym_map_type] = "map_type",
    [ts_sym_slice_type] = "slice_type",
    [ts_sym_struct_type] = "struct_type",
    [ts_sym_interface_type] = "interface_type",
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
    [ts_aux_sym_token8] = "','",
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
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(31);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            LEX_ERROR();
        case 32:
            if (lookahead == '.')
                ADVANCE(33);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            ACCEPT_TOKEN(ts_sym_number);
        case 33:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(34);
            LEX_ERROR();
        case 34:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym_number);
        case 35:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(35);
            if (lookahead == '=')
                ADVANCE(36);
            LEX_ERROR();
        case 36:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 37:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            LEX_ERROR();
        case 38:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 39:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(39);
            if (lookahead == '}')
                ADVANCE(40);
            LEX_ERROR();
        case 40:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 41:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(41);
            if (lookahead == '{')
                ADVANCE(42);
            LEX_ERROR();
        case 42:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 43:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(43);
            if (lookahead == ')')
                ADVANCE(26);
            if (lookahead == ',')
                ADVANCE(44);
            LEX_ERROR();
        case 44:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 45:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(45);
            if (lookahead == ')')
                ADVANCE(26);
            if (lookahead == ',')
                ADVANCE(44);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            LEX_ERROR();
        case 46:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(46);
            if (lookahead == '(')
                ADVANCE(29);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == '{')
                ADVANCE(42);
            LEX_ERROR();
        case 47:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(47);
            if (lookahead == '(')
                ADVANCE(29);
            LEX_ERROR();
        case 48:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(48);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == '}')
                ADVANCE(40);
            LEX_ERROR();
        case 49:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(49);
            if (lookahead == '(')
                ADVANCE(29);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == '}')
                ADVANCE(40);
            LEX_ERROR();
        case 50:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(50);
            if (lookahead == '*')
                ADVANCE(51);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == '[')
                ADVANCE(52);
            if (lookahead == 'i')
                ADVANCE(53);
            if (lookahead == 'm')
                ADVANCE(62);
            if (lookahead == 's')
                ADVANCE(65);
            LEX_ERROR();
        case 51:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 52:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'n')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'e')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'r')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'f')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'a')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'c')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'e')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__interface);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'a')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'p')
                ADVANCE(64);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__map);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'r')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'u')
                ADVANCE(68);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'c')
                ADVANCE(69);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(70);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__struct);
        case 71:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == ']')
                ADVANCE(72);
            LEX_ERROR();
        case 72:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 73:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '[')
                ADVANCE(52);
            LEX_ERROR();
        case 74:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(74);
            if (lookahead == '*')
                ADVANCE(51);
            if (lookahead == ',')
                ADVANCE(44);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == '[')
                ADVANCE(52);
            if (lookahead == 'i')
                ADVANCE(53);
            if (lookahead == 'm')
                ADVANCE(62);
            if (lookahead == 's')
                ADVANCE(65);
            LEX_ERROR();
        case 75:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == ')')
                ADVANCE(26);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
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
                ADVANCE(21);
            if (lookahead == '(')
                ADVANCE(29);
            if (lookahead == ')')
                ADVANCE(26);
            if (lookahead == '*')
                ADVANCE(51);
            if (lookahead == ',')
                ADVANCE(44);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == '=')
                ADVANCE(36);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == '[')
                ADVANCE(52);
            if (lookahead == ']')
                ADVANCE(72);
            if (lookahead == 'f')
                ADVANCE(85);
            if (lookahead == 'i')
                ADVANCE(89);
            if (lookahead == 'm')
                ADVANCE(62);
            if (lookahead == 'p')
                ADVANCE(95);
            if (lookahead == 's')
                ADVANCE(65);
            if (lookahead == 't')
                ADVANCE(102);
            if (lookahead == 'v')
                ADVANCE(106);
            if (lookahead == '{')
                ADVANCE(42);
            if (lookahead == '}')
                ADVANCE(40);
            LEX_ERROR();
        case 85:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'u')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 86:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'n')
                ADVANCE(87);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 87:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'c')
                ADVANCE(88);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 88:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__func);
        case 89:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'm')
                ADVANCE(90);
            if (lookahead == 'n')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'p')
                ADVANCE(91);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'o')
                ADVANCE(92);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 92:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'r')
                ADVANCE(93);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 't')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__import);
        case 95:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'a')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 96:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'c')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 97:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'k')
                ADVANCE(98);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'a')
                ADVANCE(99);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 99:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'g')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 100:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'e')
                ADVANCE(101);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__package);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(38);
            if (lookahead == 'y')
                ADVANCE(103);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'p')
                ADVANCE(104);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 104:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'e')
                ADVANCE(105);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 105:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__type);
        case 106:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'a')
                ADVANCE(107);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 107:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == 'r')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 108:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            ACCEPT_TOKEN(ts_sym__var);
        case ts_lex_state_error:
            if (lookahead == '\0')
                ADVANCE(1);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(21);
            if (lookahead == '(')
                ADVANCE(29);
            if (lookahead == ')')
                ADVANCE(26);
            if (lookahead == '*')
                ADVANCE(51);
            if (lookahead == ',')
                ADVANCE(44);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(32);
            if (lookahead == '=')
                ADVANCE(36);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(38);
            if (lookahead == '[')
                ADVANCE(52);
            if (lookahead == ']')
                ADVANCE(72);
            if (lookahead == 'f')
                ADVANCE(85);
            if (lookahead == 'i')
                ADVANCE(89);
            if (lookahead == 'm')
                ADVANCE(62);
            if (lookahead == 'p')
                ADVANCE(95);
            if (lookahead == 's')
                ADVANCE(65);
            if (lookahead == 't')
                ADVANCE(102);
            if (lookahead == 'v')
                ADVANCE(106);
            if (lookahead == '{')
                ADVANCE(42);
            if (lookahead == '}')
                ADVANCE(40);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 76,
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
    [17] = 37,
    [18] = 35,
    [19] = 31,
    [20] = 30,
    [21] = 30,
    [22] = 35,
    [23] = 37,
    [24] = 47,
    [25] = 41,
    [26] = 30,
    [27] = 39,
    [28] = 30,
    [29] = 75,
    [30] = 74,
    [31] = 50,
    [32] = 43,
    [33] = 27,
    [34] = 46,
    [35] = 41,
    [36] = 41,
    [37] = 37,
    [38] = 37,
    [39] = 43,
    [40] = 27,
    [41] = 41,
    [42] = 37,
    [43] = 37,
    [44] = 43,
    [45] = 27,
    [46] = 43,
    [47] = 37,
    [48] = 43,
    [49] = 27,
    [50] = 41,
    [51] = 37,
    [52] = 43,
    [53] = 27,
    [54] = 45,
    [55] = 37,
    [56] = 74,
    [57] = 50,
    [58] = 43,
    [59] = 27,
    [60] = 43,
    [61] = 73,
    [62] = 50,
    [63] = 71,
    [64] = 50,
    [65] = 43,
    [66] = 41,
    [67] = 48,
    [68] = 47,
    [69] = 48,
    [70] = 47,
    [71] = 39,
    [72] = 75,
    [73] = 74,
    [74] = 50,
    [75] = 43,
    [76] = 27,
    [77] = 49,
    [78] = 48,
    [79] = 48,
    [80] = 37,
    [81] = 37,
    [82] = 43,
    [83] = 27,
    [84] = 48,
    [85] = 43,
    [86] = 27,
    [87] = 48,
    [88] = 41,
    [89] = 48,
    [90] = 50,
    [91] = 48,
    [92] = 50,
    [93] = 39,
    [94] = 48,
    [95] = 73,
    [96] = 50,
    [97] = 71,
    [98] = 50,
    [99] = 48,
    [100] = 41,
    [101] = 48,
    [102] = 39,
    [103] = 48,
    [104] = 41,
    [105] = 48,
    [106] = 39,
    [107] = 48,
    [108] = 50,
    [109] = 48,
    [110] = 71,
    [111] = 50,
    [112] = 48,
    [113] = 71,
    [114] = 73,
    [115] = 50,
    [116] = 71,
    [117] = 50,
    [118] = 71,
    [119] = 41,
    [120] = 48,
    [121] = 39,
    [122] = 71,
    [123] = 41,
    [124] = 48,
    [125] = 39,
    [126] = 71,
    [127] = 71,
    [128] = 50,
    [129] = 71,
    [130] = 71,
    [131] = 50,
    [132] = 71,
    [133] = 39,
    [134] = 43,
    [135] = 50,
    [136] = 43,
    [137] = 71,
    [138] = 50,
    [139] = 43,
    [140] = 37,
    [141] = 74,
    [142] = 50,
    [143] = 74,
    [144] = 49,
    [145] = 48,
    [146] = 37,
    [147] = 37,
    [148] = 43,
    [149] = 27,
    [150] = 43,
    [151] = 27,
    [152] = 48,
    [153] = 39,
    [154] = 43,
    [155] = 37,
    [156] = 74,
    [157] = 50,
    [158] = 46,
    [159] = 41,
    [160] = 37,
    [161] = 37,
    [162] = 43,
    [163] = 27,
    [164] = 43,
    [165] = 27,
    [166] = 41,
    [167] = 37,
    [168] = 50,
    [169] = 30,
    [170] = 30,
    [171] = 73,
    [172] = 50,
    [173] = 71,
    [174] = 50,
    [175] = 30,
    [176] = 41,
    [177] = 48,
    [178] = 39,
    [179] = 30,
    [180] = 41,
    [181] = 48,
    [182] = 39,
    [183] = 30,
    [184] = 30,
    [185] = 50,
    [186] = 30,
    [187] = 71,
    [188] = 50,
    [189] = 30,
    [190] = 50,
    [191] = 0,
    [192] = 0,
    [193] = 37,
    [194] = 2,
    [195] = 2,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_program] = SHIFT(1),
        [ts_sym_package_directive] = SHIFT(2),
        [ts_sym__package] = SHIFT(193),
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
        [ts_sym__func] = SHIFT(23),
        [ts_sym__type] = SHIFT(167),
        [ts_aux_sym_program_repeat1] = SHIFT(192),
    },
    [15] = {
        [ts_sym_declaration] = SHIFT(15),
        [ts_sym_type_declaration] = SHIFT(16),
        [ts_sym_var_declaration] = SHIFT(16),
        [ts_sym_func_declaration] = SHIFT(16),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym__var] = SHIFT(17),
        [ts_sym__func] = SHIFT(23),
        [ts_sym__type] = SHIFT(167),
        [ts_aux_sym_program_repeat1] = SHIFT(191),
    },
    [16] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__var] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__func] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__type] = REDUCE(ts_sym_declaration, 1),
    },
    [17] = {
        [ts_sym_var_name] = SHIFT(18),
        [ts_sym__identifier] = SHIFT(22),
    },
    [18] = {
        [ts_aux_sym_token2] = SHIFT(19),
    },
    [19] = {
        [ts_sym_expression] = SHIFT(20),
        [ts_sym_number] = SHIFT(21),
    },
    [20] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__func] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__type] = REDUCE(ts_sym_var_declaration, 4),
    },
    [21] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
        [ts_sym__var] = REDUCE(ts_sym_expression, 1),
        [ts_sym__func] = REDUCE(ts_sym_expression, 1),
        [ts_sym__type] = REDUCE(ts_sym_expression, 1),
    },
    [22] = {
        [ts_aux_sym_token2] = REDUCE(ts_sym_var_name, 1),
    },
    [23] = {
        [ts_sym_var_name] = SHIFT(24),
        [ts_sym__identifier] = SHIFT(70),
    },
    [24] = {
        [ts_sym__func_signature] = SHIFT(25),
        [ts_aux_sym_token0] = SHIFT(29),
    },
    [25] = {
        [ts_sym_statement_block] = SHIFT(26),
        [ts_aux_sym_token3] = SHIFT(27),
    },
    [26] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 4),
        [ts_sym__var] = REDUCE(ts_sym_func_declaration, 4),
        [ts_sym__func] = REDUCE(ts_sym_func_declaration, 4),
        [ts_sym__type] = REDUCE(ts_sym_func_declaration, 4),
    },
    [27] = {
        [ts_aux_sym_token4] = SHIFT(28),
    },
    [28] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_statement_block, 2),
        [ts_sym__var] = REDUCE(ts_sym_statement_block, 2),
        [ts_sym__func] = REDUCE(ts_sym_statement_block, 2),
        [ts_sym__type] = REDUCE(ts_sym_statement_block, 2),
    },
    [29] = {
        [ts_sym_var_name] = SHIFT(30),
        [ts_sym__identifier] = SHIFT(143),
        [ts_aux_sym_token1] = SHIFT(158),
    },
    [30] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(31),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(140),
    },
    [31] = {
        [ts_sym_type_expression] = SHIFT(32),
        [ts_sym_pointer_type] = SHIFT(60),
        [ts_sym_map_type] = SHIFT(60),
        [ts_sym_slice_type] = SHIFT(60),
        [ts_sym_struct_type] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(60),
        [ts_sym_type_name] = SHIFT(60),
        [ts_sym__map] = SHIFT(61),
        [ts_sym__interface] = SHIFT(66),
        [ts_sym__struct] = SHIFT(88),
        [ts_sym__identifier] = SHIFT(46),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(137),
    },
    [32] = {
        [ts_aux_sym__func_signature_repeat2] = SHIFT(33),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token8] = SHIFT(55),
    },
    [33] = {
        [ts_aux_sym_token1] = SHIFT(34),
    },
    [34] = {
        [ts_sym_type_name] = SHIFT(35),
        [ts_sym__identifier] = SHIFT(36),
        [ts_aux_sym_token0] = SHIFT(37),
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 6),
    },
    [35] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 7),
    },
    [36] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym_type_name, 1),
    },
    [37] = {
        [ts_sym_var_name] = SHIFT(38),
        [ts_sym_type_name] = SHIFT(48),
        [ts_sym__identifier] = SHIFT(54),
    },
    [38] = {
        [ts_sym_type_name] = SHIFT(39),
        [ts_sym__identifier] = SHIFT(46),
    },
    [39] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(40),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token8] = SHIFT(42),
    },
    [40] = {
        [ts_aux_sym_token1] = SHIFT(41),
    },
    [41] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 11),
    },
    [42] = {
        [ts_sym_var_name] = SHIFT(43),
        [ts_sym__identifier] = SHIFT(47),
    },
    [43] = {
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__identifier] = SHIFT(46),
    },
    [44] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(45),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token8] = SHIFT(42),
    },
    [45] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [46] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_type_name, 1),
    },
    [47] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
    },
    [48] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(49),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token8] = SHIFT(51),
    },
    [49] = {
        [ts_aux_sym_token1] = SHIFT(50),
    },
    [50] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 10),
    },
    [51] = {
        [ts_sym_type_name] = SHIFT(52),
        [ts_sym__identifier] = SHIFT(46),
    },
    [52] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(53),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token8] = SHIFT(51),
    },
    [53] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [54] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token1] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_type_name, 1),
    },
    [55] = {
        [ts_sym_var_name] = SHIFT(56),
        [ts_sym__identifier] = SHIFT(143),
    },
    [56] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(57),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token8] = SHIFT(155),
    },
    [57] = {
        [ts_sym_type_expression] = SHIFT(58),
        [ts_sym_pointer_type] = SHIFT(60),
        [ts_sym_map_type] = SHIFT(60),
        [ts_sym_slice_type] = SHIFT(60),
        [ts_sym_struct_type] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(60),
        [ts_sym_type_name] = SHIFT(60),
        [ts_sym__map] = SHIFT(61),
        [ts_sym__interface] = SHIFT(66),
        [ts_sym__struct] = SHIFT(88),
        [ts_sym__identifier] = SHIFT(46),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(137),
    },
    [58] = {
        [ts_aux_sym__func_signature_repeat2] = SHIFT(59),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token8] = SHIFT(55),
    },
    [59] = {
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [60] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_type_expression, 1),
    },
    [61] = {
        [ts_aux_sym_token6] = SHIFT(62),
    },
    [62] = {
        [ts_sym_type_expression] = SHIFT(63),
        [ts_sym_pointer_type] = SHIFT(113),
        [ts_sym_map_type] = SHIFT(113),
        [ts_sym_slice_type] = SHIFT(113),
        [ts_sym_struct_type] = SHIFT(113),
        [ts_sym_interface_type] = SHIFT(113),
        [ts_sym_type_name] = SHIFT(113),
        [ts_sym__map] = SHIFT(114),
        [ts_sym__interface] = SHIFT(119),
        [ts_sym__struct] = SHIFT(123),
        [ts_sym__identifier] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(128),
        [ts_aux_sym_token6] = SHIFT(130),
    },
    [63] = {
        [ts_aux_sym_token7] = SHIFT(64),
    },
    [64] = {
        [ts_sym_type_expression] = SHIFT(65),
        [ts_sym_pointer_type] = SHIFT(60),
        [ts_sym_map_type] = SHIFT(60),
        [ts_sym_slice_type] = SHIFT(60),
        [ts_sym_struct_type] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(60),
        [ts_sym_type_name] = SHIFT(60),
        [ts_sym__map] = SHIFT(61),
        [ts_sym__interface] = SHIFT(66),
        [ts_sym__struct] = SHIFT(88),
        [ts_sym__identifier] = SHIFT(46),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(137),
    },
    [65] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token8] = REDUCE(ts_sym_map_type, 5),
    },
    [66] = {
        [ts_aux_sym_token3] = SHIFT(67),
    },
    [67] = {
        [ts_sym_var_name] = SHIFT(68),
        [ts_sym__identifier] = SHIFT(70),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(153),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [68] = {
        [ts_sym__func_signature] = SHIFT(69),
        [ts_aux_sym_token0] = SHIFT(72),
    },
    [69] = {
        [ts_sym_var_name] = SHIFT(68),
        [ts_sym__identifier] = SHIFT(70),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(71),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [70] = {
        [ts_aux_sym_token0] = REDUCE(ts_sym_var_name, 1),
    },
    [71] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [72] = {
        [ts_sym_var_name] = SHIFT(73),
        [ts_sym__identifier] = SHIFT(143),
        [ts_aux_sym_token1] = SHIFT(144),
    },
    [73] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(74),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(140),
    },
    [74] = {
        [ts_sym_type_expression] = SHIFT(75),
        [ts_sym_pointer_type] = SHIFT(60),
        [ts_sym_map_type] = SHIFT(60),
        [ts_sym_slice_type] = SHIFT(60),
        [ts_sym_struct_type] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(60),
        [ts_sym_type_name] = SHIFT(60),
        [ts_sym__map] = SHIFT(61),
        [ts_sym__interface] = SHIFT(66),
        [ts_sym__struct] = SHIFT(88),
        [ts_sym__identifier] = SHIFT(46),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(137),
    },
    [75] = {
        [ts_aux_sym__func_signature_repeat2] = SHIFT(76),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_token8] = SHIFT(55),
    },
    [76] = {
        [ts_aux_sym_token1] = SHIFT(77),
    },
    [77] = {
        [ts_sym_type_name] = SHIFT(78),
        [ts_sym__identifier] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(80),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 6),
    },
    [78] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 7),
    },
    [79] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_name, 1),
    },
    [80] = {
        [ts_sym_var_name] = SHIFT(81),
        [ts_sym_type_name] = SHIFT(85),
        [ts_sym__identifier] = SHIFT(54),
    },
    [81] = {
        [ts_sym_type_name] = SHIFT(82),
        [ts_sym__identifier] = SHIFT(46),
    },
    [82] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(83),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token8] = SHIFT(42),
    },
    [83] = {
        [ts_aux_sym_token1] = SHIFT(84),
    },
    [84] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 11),
    },
    [85] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(86),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token8] = SHIFT(51),
    },
    [86] = {
        [ts_aux_sym_token1] = SHIFT(87),
    },
    [87] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 10),
    },
    [88] = {
        [ts_aux_sym_token3] = SHIFT(89),
    },
    [89] = {
        [ts_sym_var_name] = SHIFT(90),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(133),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [90] = {
        [ts_sym_type_expression] = SHIFT(91),
        [ts_sym_pointer_type] = SHIFT(94),
        [ts_sym_map_type] = SHIFT(94),
        [ts_sym_slice_type] = SHIFT(94),
        [ts_sym_struct_type] = SHIFT(94),
        [ts_sym_interface_type] = SHIFT(94),
        [ts_sym_type_name] = SHIFT(94),
        [ts_sym__map] = SHIFT(95),
        [ts_sym__interface] = SHIFT(100),
        [ts_sym__struct] = SHIFT(104),
        [ts_sym__identifier] = SHIFT(79),
        [ts_aux_sym_token5] = SHIFT(108),
        [ts_aux_sym_token6] = SHIFT(110),
    },
    [91] = {
        [ts_sym_var_name] = SHIFT(90),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(93),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [92] = {
        [ts_sym__map] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__interface] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__struct] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),
    },
    [93] = {
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 3),
    },
    [94] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_expression, 1),
    },
    [95] = {
        [ts_aux_sym_token6] = SHIFT(96),
    },
    [96] = {
        [ts_sym_type_expression] = SHIFT(97),
        [ts_sym_pointer_type] = SHIFT(113),
        [ts_sym_map_type] = SHIFT(113),
        [ts_sym_slice_type] = SHIFT(113),
        [ts_sym_struct_type] = SHIFT(113),
        [ts_sym_interface_type] = SHIFT(113),
        [ts_sym_type_name] = SHIFT(113),
        [ts_sym__map] = SHIFT(114),
        [ts_sym__interface] = SHIFT(119),
        [ts_sym__struct] = SHIFT(123),
        [ts_sym__identifier] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(128),
        [ts_aux_sym_token6] = SHIFT(130),
    },
    [97] = {
        [ts_aux_sym_token7] = SHIFT(98),
    },
    [98] = {
        [ts_sym_type_expression] = SHIFT(99),
        [ts_sym_pointer_type] = SHIFT(94),
        [ts_sym_map_type] = SHIFT(94),
        [ts_sym_slice_type] = SHIFT(94),
        [ts_sym_struct_type] = SHIFT(94),
        [ts_sym_interface_type] = SHIFT(94),
        [ts_sym_type_name] = SHIFT(94),
        [ts_sym__map] = SHIFT(95),
        [ts_sym__interface] = SHIFT(100),
        [ts_sym__struct] = SHIFT(104),
        [ts_sym__identifier] = SHIFT(79),
        [ts_aux_sym_token5] = SHIFT(108),
        [ts_aux_sym_token6] = SHIFT(110),
    },
    [99] = {
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_token4] = REDUCE(ts_sym_map_type, 5),
    },
    [100] = {
        [ts_aux_sym_token3] = SHIFT(101),
    },
    [101] = {
        [ts_sym_var_name] = SHIFT(68),
        [ts_sym__identifier] = SHIFT(70),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(102),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [102] = {
        [ts_aux_sym_token4] = SHIFT(103),
    },
    [103] = {
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_interface_type, 4),
    },
    [104] = {
        [ts_aux_sym_token3] = SHIFT(105),
    },
    [105] = {
        [ts_sym_var_name] = SHIFT(90),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(106),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [106] = {
        [ts_aux_sym_token4] = SHIFT(107),
    },
    [107] = {
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token4] = REDUCE(ts_sym_struct_type, 4),
    },
    [108] = {
        [ts_sym_type_expression] = SHIFT(109),
        [ts_sym_pointer_type] = SHIFT(94),
        [ts_sym_map_type] = SHIFT(94),
        [ts_sym_slice_type] = SHIFT(94),
        [ts_sym_struct_type] = SHIFT(94),
        [ts_sym_interface_type] = SHIFT(94),
        [ts_sym_type_name] = SHIFT(94),
        [ts_sym__map] = SHIFT(95),
        [ts_sym__interface] = SHIFT(100),
        [ts_sym__struct] = SHIFT(104),
        [ts_sym__identifier] = SHIFT(79),
        [ts_aux_sym_token5] = SHIFT(108),
        [ts_aux_sym_token6] = SHIFT(110),
    },
    [109] = {
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token4] = REDUCE(ts_sym_pointer_type, 2),
    },
    [110] = {
        [ts_aux_sym_token7] = SHIFT(111),
    },
    [111] = {
        [ts_sym_type_expression] = SHIFT(112),
        [ts_sym_pointer_type] = SHIFT(94),
        [ts_sym_map_type] = SHIFT(94),
        [ts_sym_slice_type] = SHIFT(94),
        [ts_sym_struct_type] = SHIFT(94),
        [ts_sym_interface_type] = SHIFT(94),
        [ts_sym_type_name] = SHIFT(94),
        [ts_sym__map] = SHIFT(95),
        [ts_sym__interface] = SHIFT(100),
        [ts_sym__struct] = SHIFT(104),
        [ts_sym__identifier] = SHIFT(79),
        [ts_aux_sym_token5] = SHIFT(108),
        [ts_aux_sym_token6] = SHIFT(110),
    },
    [112] = {
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym_slice_type, 3),
    },
    [113] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_expression, 1),
    },
    [114] = {
        [ts_aux_sym_token6] = SHIFT(115),
    },
    [115] = {
        [ts_sym_type_expression] = SHIFT(116),
        [ts_sym_pointer_type] = SHIFT(113),
        [ts_sym_map_type] = SHIFT(113),
        [ts_sym_slice_type] = SHIFT(113),
        [ts_sym_struct_type] = SHIFT(113),
        [ts_sym_interface_type] = SHIFT(113),
        [ts_sym_type_name] = SHIFT(113),
        [ts_sym__map] = SHIFT(114),
        [ts_sym__interface] = SHIFT(119),
        [ts_sym__struct] = SHIFT(123),
        [ts_sym__identifier] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(128),
        [ts_aux_sym_token6] = SHIFT(130),
    },
    [116] = {
        [ts_aux_sym_token7] = SHIFT(117),
    },
    [117] = {
        [ts_sym_type_expression] = SHIFT(118),
        [ts_sym_pointer_type] = SHIFT(113),
        [ts_sym_map_type] = SHIFT(113),
        [ts_sym_slice_type] = SHIFT(113),
        [ts_sym_struct_type] = SHIFT(113),
        [ts_sym_interface_type] = SHIFT(113),
        [ts_sym_type_name] = SHIFT(113),
        [ts_sym__map] = SHIFT(114),
        [ts_sym__interface] = SHIFT(119),
        [ts_sym__struct] = SHIFT(123),
        [ts_sym__identifier] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(128),
        [ts_aux_sym_token6] = SHIFT(130),
    },
    [118] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_map_type, 5),
    },
    [119] = {
        [ts_aux_sym_token3] = SHIFT(120),
    },
    [120] = {
        [ts_sym_var_name] = SHIFT(68),
        [ts_sym__identifier] = SHIFT(70),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(121),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [121] = {
        [ts_aux_sym_token4] = SHIFT(122),
    },
    [122] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_interface_type, 4),
    },
    [123] = {
        [ts_aux_sym_token3] = SHIFT(124),
    },
    [124] = {
        [ts_sym_var_name] = SHIFT(90),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(125),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [125] = {
        [ts_aux_sym_token4] = SHIFT(126),
    },
    [126] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_struct_type, 4),
    },
    [127] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_name, 1),
    },
    [128] = {
        [ts_sym_type_expression] = SHIFT(129),
        [ts_sym_pointer_type] = SHIFT(113),
        [ts_sym_map_type] = SHIFT(113),
        [ts_sym_slice_type] = SHIFT(113),
        [ts_sym_struct_type] = SHIFT(113),
        [ts_sym_interface_type] = SHIFT(113),
        [ts_sym_type_name] = SHIFT(113),
        [ts_sym__map] = SHIFT(114),
        [ts_sym__interface] = SHIFT(119),
        [ts_sym__struct] = SHIFT(123),
        [ts_sym__identifier] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(128),
        [ts_aux_sym_token6] = SHIFT(130),
    },
    [129] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_pointer_type, 2),
    },
    [130] = {
        [ts_aux_sym_token7] = SHIFT(131),
    },
    [131] = {
        [ts_sym_type_expression] = SHIFT(132),
        [ts_sym_pointer_type] = SHIFT(113),
        [ts_sym_map_type] = SHIFT(113),
        [ts_sym_slice_type] = SHIFT(113),
        [ts_sym_struct_type] = SHIFT(113),
        [ts_sym_interface_type] = SHIFT(113),
        [ts_sym_type_name] = SHIFT(113),
        [ts_sym__map] = SHIFT(114),
        [ts_sym__interface] = SHIFT(119),
        [ts_sym__struct] = SHIFT(123),
        [ts_sym__identifier] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(128),
        [ts_aux_sym_token6] = SHIFT(130),
    },
    [132] = {
        [ts_aux_sym_token7] = REDUCE(ts_sym_slice_type, 3),
    },
    [133] = {
        [ts_aux_sym_token4] = SHIFT(134),
    },
    [134] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_struct_type, 4),
    },
    [135] = {
        [ts_sym_type_expression] = SHIFT(136),
        [ts_sym_pointer_type] = SHIFT(60),
        [ts_sym_map_type] = SHIFT(60),
        [ts_sym_slice_type] = SHIFT(60),
        [ts_sym_struct_type] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(60),
        [ts_sym_type_name] = SHIFT(60),
        [ts_sym__map] = SHIFT(61),
        [ts_sym__interface] = SHIFT(66),
        [ts_sym__struct] = SHIFT(88),
        [ts_sym__identifier] = SHIFT(46),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(137),
    },
    [136] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_token8] = REDUCE(ts_sym_pointer_type, 2),
    },
    [137] = {
        [ts_aux_sym_token7] = SHIFT(138),
    },
    [138] = {
        [ts_sym_type_expression] = SHIFT(139),
        [ts_sym_pointer_type] = SHIFT(60),
        [ts_sym_map_type] = SHIFT(60),
        [ts_sym_slice_type] = SHIFT(60),
        [ts_sym_struct_type] = SHIFT(60),
        [ts_sym_interface_type] = SHIFT(60),
        [ts_sym_type_name] = SHIFT(60),
        [ts_sym__map] = SHIFT(61),
        [ts_sym__interface] = SHIFT(66),
        [ts_sym__struct] = SHIFT(88),
        [ts_sym__identifier] = SHIFT(46),
        [ts_aux_sym_token5] = SHIFT(135),
        [ts_aux_sym_token6] = SHIFT(137),
    },
    [139] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_token8] = REDUCE(ts_sym_slice_type, 3),
    },
    [140] = {
        [ts_sym_var_name] = SHIFT(141),
        [ts_sym__identifier] = SHIFT(143),
    },
    [141] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(142),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_token8] = SHIFT(140),
    },
    [142] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
    },
    [143] = {
        [ts_sym__map] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__interface] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__struct] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_token8] = REDUCE(ts_sym_var_name, 1),
    },
    [144] = {
        [ts_sym_type_name] = SHIFT(145),
        [ts_sym__identifier] = SHIFT(79),
        [ts_aux_sym_token0] = SHIFT(146),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 2),
    },
    [145] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 3),
    },
    [146] = {
        [ts_sym_var_name] = SHIFT(147),
        [ts_sym_type_name] = SHIFT(150),
        [ts_sym__identifier] = SHIFT(54),
    },
    [147] = {
        [ts_sym_type_name] = SHIFT(148),
        [ts_sym__identifier] = SHIFT(46),
    },
    [148] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(149),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token8] = SHIFT(42),
    },
    [149] = {
        [ts_aux_sym_token1] = SHIFT(78),
    },
    [150] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(151),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token8] = SHIFT(51),
    },
    [151] = {
        [ts_aux_sym_token1] = SHIFT(152),
    },
    [152] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 6),
    },
    [153] = {
        [ts_aux_sym_token4] = SHIFT(154),
    },
    [154] = {
        [ts_aux_sym_token1] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_token8] = REDUCE(ts_sym_interface_type, 4),
    },
    [155] = {
        [ts_sym_var_name] = SHIFT(156),
        [ts_sym__identifier] = SHIFT(143),
    },
    [156] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(157),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_token8] = SHIFT(155),
    },
    [157] = {
        [ts_sym__map] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [158] = {
        [ts_sym_type_name] = SHIFT(159),
        [ts_sym__identifier] = SHIFT(36),
        [ts_aux_sym_token0] = SHIFT(160),
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 2),
    },
    [159] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 3),
    },
    [160] = {
        [ts_sym_var_name] = SHIFT(161),
        [ts_sym_type_name] = SHIFT(164),
        [ts_sym__identifier] = SHIFT(54),
    },
    [161] = {
        [ts_sym_type_name] = SHIFT(162),
        [ts_sym__identifier] = SHIFT(46),
    },
    [162] = {
        [ts_aux_sym__func_signature_repeat3] = SHIFT(163),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_token8] = SHIFT(42),
    },
    [163] = {
        [ts_aux_sym_token1] = SHIFT(35),
    },
    [164] = {
        [ts_aux_sym__func_signature_repeat4] = SHIFT(165),
        [ts_aux_sym_token1] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_token8] = SHIFT(51),
    },
    [165] = {
        [ts_aux_sym_token1] = SHIFT(166),
    },
    [166] = {
        [ts_aux_sym_token3] = REDUCE(ts_sym__func_signature, 6),
    },
    [167] = {
        [ts_sym_type_name] = SHIFT(168),
        [ts_sym__identifier] = SHIFT(190),
    },
    [168] = {
        [ts_sym_type_expression] = SHIFT(169),
        [ts_sym_pointer_type] = SHIFT(170),
        [ts_sym_map_type] = SHIFT(170),
        [ts_sym_slice_type] = SHIFT(170),
        [ts_sym_struct_type] = SHIFT(170),
        [ts_sym_interface_type] = SHIFT(170),
        [ts_sym_type_name] = SHIFT(170),
        [ts_sym__map] = SHIFT(171),
        [ts_sym__interface] = SHIFT(176),
        [ts_sym__struct] = SHIFT(180),
        [ts_sym__identifier] = SHIFT(184),
        [ts_aux_sym_token5] = SHIFT(185),
        [ts_aux_sym_token6] = SHIFT(187),
    },
    [169] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 3),
        [ts_sym__var] = REDUCE(ts_sym_type_declaration, 3),
        [ts_sym__func] = REDUCE(ts_sym_type_declaration, 3),
        [ts_sym__type] = REDUCE(ts_sym_type_declaration, 3),
    },
    [170] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__var] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__func] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__type] = REDUCE(ts_sym_type_expression, 1),
    },
    [171] = {
        [ts_aux_sym_token6] = SHIFT(172),
    },
    [172] = {
        [ts_sym_type_expression] = SHIFT(173),
        [ts_sym_pointer_type] = SHIFT(113),
        [ts_sym_map_type] = SHIFT(113),
        [ts_sym_slice_type] = SHIFT(113),
        [ts_sym_struct_type] = SHIFT(113),
        [ts_sym_interface_type] = SHIFT(113),
        [ts_sym_type_name] = SHIFT(113),
        [ts_sym__map] = SHIFT(114),
        [ts_sym__interface] = SHIFT(119),
        [ts_sym__struct] = SHIFT(123),
        [ts_sym__identifier] = SHIFT(127),
        [ts_aux_sym_token5] = SHIFT(128),
        [ts_aux_sym_token6] = SHIFT(130),
    },
    [173] = {
        [ts_aux_sym_token7] = SHIFT(174),
    },
    [174] = {
        [ts_sym_type_expression] = SHIFT(175),
        [ts_sym_pointer_type] = SHIFT(170),
        [ts_sym_map_type] = SHIFT(170),
        [ts_sym_slice_type] = SHIFT(170),
        [ts_sym_struct_type] = SHIFT(170),
        [ts_sym_interface_type] = SHIFT(170),
        [ts_sym_type_name] = SHIFT(170),
        [ts_sym__map] = SHIFT(171),
        [ts_sym__interface] = SHIFT(176),
        [ts_sym__struct] = SHIFT(180),
        [ts_sym__identifier] = SHIFT(184),
        [ts_aux_sym_token5] = SHIFT(185),
        [ts_aux_sym_token6] = SHIFT(187),
    },
    [175] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__var] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__func] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__type] = REDUCE(ts_sym_map_type, 5),
    },
    [176] = {
        [ts_aux_sym_token3] = SHIFT(177),
    },
    [177] = {
        [ts_sym_var_name] = SHIFT(68),
        [ts_sym__identifier] = SHIFT(70),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(178),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [178] = {
        [ts_aux_sym_token4] = SHIFT(179),
    },
    [179] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__var] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__func] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__type] = REDUCE(ts_sym_interface_type, 4),
    },
    [180] = {
        [ts_aux_sym_token3] = SHIFT(181),
    },
    [181] = {
        [ts_sym_var_name] = SHIFT(90),
        [ts_sym__identifier] = SHIFT(92),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(182),
        [ts_aux_sym_token4] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [182] = {
        [ts_aux_sym_token4] = SHIFT(183),
    },
    [183] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__var] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__func] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__type] = REDUCE(ts_sym_struct_type, 4),
    },
    [184] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__var] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__func] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__type] = REDUCE(ts_sym_type_name, 1),
    },
    [185] = {
        [ts_sym_type_expression] = SHIFT(186),
        [ts_sym_pointer_type] = SHIFT(170),
        [ts_sym_map_type] = SHIFT(170),
        [ts_sym_slice_type] = SHIFT(170),
        [ts_sym_struct_type] = SHIFT(170),
        [ts_sym_interface_type] = SHIFT(170),
        [ts_sym_type_name] = SHIFT(170),
        [ts_sym__map] = SHIFT(171),
        [ts_sym__interface] = SHIFT(176),
        [ts_sym__struct] = SHIFT(180),
        [ts_sym__identifier] = SHIFT(184),
        [ts_aux_sym_token5] = SHIFT(185),
        [ts_aux_sym_token6] = SHIFT(187),
    },
    [186] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__var] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__func] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__type] = REDUCE(ts_sym_pointer_type, 2),
    },
    [187] = {
        [ts_aux_sym_token7] = SHIFT(188),
    },
    [188] = {
        [ts_sym_type_expression] = SHIFT(189),
        [ts_sym_pointer_type] = SHIFT(170),
        [ts_sym_map_type] = SHIFT(170),
        [ts_sym_slice_type] = SHIFT(170),
        [ts_sym_struct_type] = SHIFT(170),
        [ts_sym_interface_type] = SHIFT(170),
        [ts_sym_type_name] = SHIFT(170),
        [ts_sym__map] = SHIFT(171),
        [ts_sym__interface] = SHIFT(176),
        [ts_sym__struct] = SHIFT(180),
        [ts_sym__identifier] = SHIFT(184),
        [ts_aux_sym_token5] = SHIFT(185),
        [ts_aux_sym_token6] = SHIFT(187),
    },
    [189] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__var] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__func] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__type] = REDUCE(ts_sym_slice_type, 3),
    },
    [190] = {
        [ts_sym__map] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__interface] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__struct] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_token6] = REDUCE(ts_sym_type_name, 1),
    },
    [191] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
    },
    [192] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
    },
    [193] = {
        [ts_sym_package_name] = SHIFT(194),
        [ts_sym__identifier] = SHIFT(195),
    },
    [194] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__import] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__var] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__func] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__type] = REDUCE(ts_sym_package_directive, 2),
    },
    [195] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__import] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__var] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__func] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__type] = REDUCE(ts_sym_package_name, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_golang);
