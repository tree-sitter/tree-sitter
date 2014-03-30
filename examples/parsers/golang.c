#include "tree_sitter/parser.h"

STATE_COUNT = 196;
SYMBOL_COUNT = 52;

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
    ts_aux_sym_repeat_helper1 = 33,
    ts_aux_sym_repeat_helper10 = 34,
    ts_aux_sym_repeat_helper2 = 35,
    ts_aux_sym_repeat_helper3 = 36,
    ts_aux_sym_repeat_helper4 = 37,
    ts_aux_sym_repeat_helper5 = 38,
    ts_aux_sym_repeat_helper6 = 39,
    ts_aux_sym_repeat_helper7 = 40,
    ts_aux_sym_repeat_helper8 = 41,
    ts_aux_sym_repeat_helper9 = 42,
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
    [ts_aux_sym_repeat_helper1] = "repeat_helper1",
    [ts_aux_sym_repeat_helper10] = "repeat_helper10",
    [ts_aux_sym_repeat_helper2] = "repeat_helper2",
    [ts_aux_sym_repeat_helper3] = "repeat_helper3",
    [ts_aux_sym_repeat_helper4] = "repeat_helper4",
    [ts_aux_sym_repeat_helper5] = "repeat_helper5",
    [ts_aux_sym_repeat_helper6] = "repeat_helper6",
    [ts_aux_sym_repeat_helper7] = "repeat_helper7",
    [ts_aux_sym_repeat_helper8] = "repeat_helper8",
    [ts_aux_sym_repeat_helper9] = "repeat_helper9",
    [ts_aux_sym_token1] = "'('",
    [ts_aux_sym_token2] = "')'",
    [ts_aux_sym_token3] = "'='",
    [ts_aux_sym_token4] = "'{'",
    [ts_aux_sym_token5] = "'}'",
    [ts_aux_sym_token6] = "'*'",
    [ts_aux_sym_token7] = "'['",
    [ts_aux_sym_token8] = "']'",
    [ts_aux_sym_token9] = "','",
    [ts_builtin_sym_end] = "end",
    [ts_builtin_sym_error] = "error",
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
    [ts_aux_sym_repeat_helper1] = 1,
    [ts_aux_sym_repeat_helper10] = 1,
    [ts_aux_sym_repeat_helper2] = 1,
    [ts_aux_sym_repeat_helper3] = 1,
    [ts_aux_sym_repeat_helper4] = 1,
    [ts_aux_sym_repeat_helper5] = 1,
    [ts_aux_sym_repeat_helper6] = 1,
    [ts_aux_sym_repeat_helper7] = 1,
    [ts_aux_sym_repeat_helper8] = 1,
    [ts_aux_sym_repeat_helper9] = 1,
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
            if (lookahead == 'f')
                ADVANCE(1);
            if (lookahead == 'i')
                ADVANCE(5);
            if (lookahead == 't')
                ADVANCE(11);
            if (lookahead == 'v')
                ADVANCE(15);
            LEX_ERROR();
        case 1:
            if (lookahead == 'u')
                ADVANCE(2);
            LEX_ERROR();
        case 2:
            if (lookahead == 'n')
                ADVANCE(3);
            LEX_ERROR();
        case 3:
            if (lookahead == 'c')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            ACCEPT_TOKEN(ts_sym__func);
        case 5:
            if (lookahead == 'm')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (lookahead == 'p')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (lookahead == 'o')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'r')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (lookahead == 't')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            ACCEPT_TOKEN(ts_sym__import);
        case 11:
            if (lookahead == 'y')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (lookahead == 'p')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            if (lookahead == 'e')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            ACCEPT_TOKEN(ts_sym__type);
        case 15:
            if (lookahead == 'a')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            if (lookahead == 'r')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            ACCEPT_TOKEN(ts_sym__var);
        case 18:
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 20:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 21:
            if (lookahead == '\"')
                ADVANCE(22);
            if (lookahead == ')')
                ADVANCE(32);
            LEX_ERROR();
        case 22:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(23);
            if (lookahead == '\\')
                ADVANCE(29);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(31);
            LEX_ERROR();
        case 23:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(24);
            if (lookahead == '\"')
                ADVANCE(25);
            if (lookahead == '\\')
                ADVANCE(26);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(28);
            LEX_ERROR();
        case 24:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(24);
            if (lookahead == '\"')
                ADVANCE(25);
            if (lookahead == '\\')
                ADVANCE(26);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(28);
            LEX_ERROR();
        case 25:
            ACCEPT_TOKEN(ts_sym_string);
        case 26:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(24);
            if (lookahead == '\"')
                ADVANCE(27);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(24);
            if (lookahead == '\\')
                ADVANCE(26);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(28);
            LEX_ERROR();
        case 27:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(24);
            if (lookahead == '\"')
                ADVANCE(25);
            if (lookahead == '\\')
                ADVANCE(26);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_string);
        case 28:
            if (lookahead == '\"')
                ADVANCE(24);
            LEX_ERROR();
        case 29:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(24);
            if (lookahead == '\"')
                ADVANCE(30);
            if ('#' <= lookahead && lookahead <= '\"')
                ADVANCE(23);
            if (lookahead == '\\')
                ADVANCE(26);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(28);
            LEX_ERROR();
        case 30:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(24);
            if (lookahead == '\"')
                ADVANCE(25);
            if (lookahead == '\\')
                ADVANCE(26);
            if (']' <= lookahead && lookahead <= '\\')
                ADVANCE(28);
            ACCEPT_TOKEN(ts_sym_string);
        case 31:
            if (lookahead == '\"')
                ADVANCE(23);
            LEX_ERROR();
        case 32:
            ACCEPT_TOKEN(ts_aux_sym_token2);
        case 33:
            if (lookahead == ')')
                ADVANCE(32);
            LEX_ERROR();
        case 34:
            if (lookahead == '\"')
                ADVANCE(22);
            if (lookahead == '(')
                ADVANCE(35);
            LEX_ERROR();
        case 35:
            ACCEPT_TOKEN(ts_aux_sym_token1);
        case 36:
            if (lookahead == 'f')
                ADVANCE(1);
            if (lookahead == 't')
                ADVANCE(11);
            if (lookahead == 'v')
                ADVANCE(15);
            LEX_ERROR();
        case 37:
            if (lookahead == '(')
                ADVANCE(35);
            LEX_ERROR();
        case 38:
            if (lookahead == '}')
                ADVANCE(39);
            LEX_ERROR();
        case 39:
            ACCEPT_TOKEN(ts_aux_sym_token5);
        case 40:
            if (lookahead == '{')
                ADVANCE(41);
            LEX_ERROR();
        case 41:
            ACCEPT_TOKEN(ts_aux_sym_token4);
        case 42:
            if (lookahead == '*')
                ADVANCE(52);
            if (lookahead == ',')
                ADVANCE(53);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == '[')
                ADVANCE(54);
            if (lookahead == 'i')
                ADVANCE(55);
            if (lookahead == 'm')
                ADVANCE(64);
            if (lookahead == 's')
                ADVANCE(69);
            LEX_ERROR();
        case 43:
            if (lookahead == 'n')
                ADVANCE(44);
            LEX_ERROR();
        case 44:
            if (lookahead == 't')
                ADVANCE(45);
            LEX_ERROR();
        case 45:
            if (lookahead == 'e')
                ADVANCE(46);
            LEX_ERROR();
        case 46:
            if (lookahead == 'r')
                ADVANCE(47);
            LEX_ERROR();
        case 47:
            if (lookahead == 'f')
                ADVANCE(48);
            LEX_ERROR();
        case 48:
            if (lookahead == 'a')
                ADVANCE(49);
            LEX_ERROR();
        case 49:
            if (lookahead == 'c')
                ADVANCE(50);
            LEX_ERROR();
        case 50:
            if (lookahead == 'e')
                ADVANCE(51);
            LEX_ERROR();
        case 51:
            ACCEPT_TOKEN(ts_sym__interface);
        case 52:
            ACCEPT_TOKEN(ts_aux_sym_token6);
        case 53:
            ACCEPT_TOKEN(ts_aux_sym_token9);
        case 54:
            ACCEPT_TOKEN(ts_aux_sym_token7);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'n')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'f')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__interface);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 65:
            if (lookahead == 'p')
                ADVANCE(66);
            LEX_ERROR();
        case 66:
            ACCEPT_TOKEN(ts_sym__map);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'p')
                ADVANCE(68);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__map);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(75);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 70:
            if (lookahead == 'r')
                ADVANCE(71);
            LEX_ERROR();
        case 71:
            if (lookahead == 'u')
                ADVANCE(72);
            LEX_ERROR();
        case 72:
            if (lookahead == 'c')
                ADVANCE(73);
            LEX_ERROR();
        case 73:
            if (lookahead == 't')
                ADVANCE(74);
            LEX_ERROR();
        case 74:
            ACCEPT_TOKEN(ts_sym__struct);
        case 75:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(76);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 76:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'u')
                ADVANCE(77);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 77:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(78);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 78:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(79);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 79:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__struct);
        case 80:
            if (lookahead == ')')
                ADVANCE(32);
            if (lookahead == ',')
                ADVANCE(53);
            LEX_ERROR();
        case 81:
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == '}')
                ADVANCE(39);
            LEX_ERROR();
        case 82:
            if (lookahead == ']')
                ADVANCE(83);
            LEX_ERROR();
        case 83:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 84:
            if (lookahead == '*')
                ADVANCE(52);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == '[')
                ADVANCE(54);
            if (lookahead == 'i')
                ADVANCE(55);
            if (lookahead == 'm')
                ADVANCE(64);
            if (lookahead == 's')
                ADVANCE(69);
            LEX_ERROR();
        case 85:
            if (lookahead == '[')
                ADVANCE(54);
            LEX_ERROR();
        case 86:
            if (lookahead == ')')
                ADVANCE(32);
            if (lookahead == ',')
                ADVANCE(53);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            LEX_ERROR();
        case 87:
            if (lookahead == '(')
                ADVANCE(35);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == '}')
                ADVANCE(39);
            LEX_ERROR();
        case 88:
            if (lookahead == ')')
                ADVANCE(32);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            LEX_ERROR();
        case 89:
            if (lookahead == '(')
                ADVANCE(35);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(41);
            LEX_ERROR();
        case 90:
            if (lookahead == '=')
                ADVANCE(91);
            LEX_ERROR();
        case 91:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 92:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(93);
            LEX_ERROR();
        case 93:
            if (lookahead == '.')
                ADVANCE(94);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym_number);
        case 94:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(95);
            LEX_ERROR();
        case 95:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym_number);
        case 96:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym_number);
        case 97:
            if (lookahead == '.')
                ADVANCE(94);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym_number);
        case 98:
            LEX_ERROR();
        case 99:
            if (lookahead == 'p')
                ADVANCE(100);
            LEX_ERROR();
        case 100:
            if (lookahead == 'a')
                ADVANCE(101);
            LEX_ERROR();
        case 101:
            if (lookahead == 'c')
                ADVANCE(102);
            LEX_ERROR();
        case 102:
            if (lookahead == 'k')
                ADVANCE(103);
            LEX_ERROR();
        case 103:
            if (lookahead == 'a')
                ADVANCE(104);
            LEX_ERROR();
        case 104:
            if (lookahead == 'g')
                ADVANCE(105);
            LEX_ERROR();
        case 105:
            if (lookahead == 'e')
                ADVANCE(106);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(ts_sym__package);
        case 107:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'u')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 108:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'n')
                ADVANCE(109);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 109:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(110);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 110:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__func);
        case 111:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'm')
                ADVANCE(112);
            if (lookahead == 'n')
                ADVANCE(56);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 112:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'p')
                ADVANCE(113);
            if ('q' <= lookahead && lookahead <= 'p')
                ADVANCE(7);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 113:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'o')
                ADVANCE(114);
            if ('p' <= lookahead && lookahead <= 'o')
                ADVANCE(8);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 114:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(115);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 115:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(116);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 116:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__import);
        case 117:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'm')
                ADVANCE(112);
            if ('n' <= lookahead && lookahead <= 'm')
                ADVANCE(6);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 118:
            if (lookahead == 'a')
                ADVANCE(65);
            LEX_ERROR();
        case 119:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(120);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 120:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(121);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 121:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'k')
                ADVANCE(122);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 122:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(123);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 123:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'g')
                ADVANCE(124);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(125);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__package);
        case 126:
            if (lookahead == 't')
                ADVANCE(70);
            LEX_ERROR();
        case 127:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(20);
            if (lookahead == 'y')
                ADVANCE(128);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 128:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'p')
                ADVANCE(129);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 129:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(130);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 130:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__type);
        case 131:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(132);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 132:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(133);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 133:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__var);
        case ts_lex_state_error:
            if (lookahead == '\"')
                ADVANCE(22);
            if (lookahead == '(')
                ADVANCE(35);
            if (lookahead == ')')
                ADVANCE(32);
            if (lookahead == '*')
                ADVANCE(52);
            if (lookahead == ',')
                ADVANCE(53);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(93);
            if (lookahead == '=')
                ADVANCE(91);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'r') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == '[')
                ADVANCE(54);
            if (lookahead == ']')
                ADVANCE(83);
            if (lookahead == 'f')
                ADVANCE(107);
            if (lookahead == 'i')
                ADVANCE(111);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(117);
            if (lookahead == 'm')
                ADVANCE(64);
            if ('n' <= lookahead && lookahead <= 'm')
                ADVANCE(118);
            if (lookahead == 'p')
                ADVANCE(119);
            if (lookahead == 's')
                ADVANCE(69);
            if ('t' <= lookahead && lookahead <= 's')
                ADVANCE(126);
            if (lookahead == 't')
                ADVANCE(127);
            if (lookahead == 'v')
                ADVANCE(131);
            if (lookahead == '{')
                ADVANCE(41);
            if (lookahead == '}')
                ADVANCE(39);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 99,
    [1] = 18,
    [2] = 0,
    [3] = 0,
    [4] = 0,
    [5] = 34,
    [6] = 0,
    [7] = 0,
    [8] = 21,
    [9] = 21,
    [10] = 21,
    [11] = 33,
    [12] = 33,
    [13] = 0,
    [14] = 0,
    [15] = 36,
    [16] = 36,
    [17] = 18,
    [18] = 37,
    [19] = 37,
    [20] = 40,
    [21] = 36,
    [22] = 38,
    [23] = 36,
    [24] = 88,
    [25] = 42,
    [26] = 42,
    [27] = 84,
    [28] = 80,
    [29] = 40,
    [30] = 81,
    [31] = 37,
    [32] = 81,
    [33] = 38,
    [34] = 88,
    [35] = 42,
    [36] = 84,
    [37] = 85,
    [38] = 84,
    [39] = 82,
    [40] = 40,
    [41] = 81,
    [42] = 38,
    [43] = 82,
    [44] = 85,
    [45] = 84,
    [46] = 40,
    [47] = 81,
    [48] = 84,
    [49] = 84,
    [50] = 81,
    [51] = 40,
    [52] = 81,
    [53] = 38,
    [54] = 81,
    [55] = 85,
    [56] = 84,
    [57] = 82,
    [58] = 82,
    [59] = 84,
    [60] = 40,
    [61] = 81,
    [62] = 38,
    [63] = 81,
    [64] = 81,
    [65] = 81,
    [66] = 84,
    [67] = 81,
    [68] = 82,
    [69] = 84,
    [70] = 81,
    [71] = 84,
    [72] = 82,
    [73] = 82,
    [74] = 84,
    [75] = 82,
    [76] = 81,
    [77] = 38,
    [78] = 38,
    [79] = 82,
    [80] = 82,
    [81] = 84,
    [82] = 82,
    [83] = 82,
    [84] = 84,
    [85] = 40,
    [86] = 81,
    [87] = 38,
    [88] = 80,
    [89] = 80,
    [90] = 80,
    [91] = 84,
    [92] = 80,
    [93] = 82,
    [94] = 84,
    [95] = 80,
    [96] = 80,
    [97] = 33,
    [98] = 87,
    [99] = 81,
    [100] = 18,
    [101] = 86,
    [102] = 80,
    [103] = 33,
    [104] = 81,
    [105] = 18,
    [106] = 80,
    [107] = 33,
    [108] = 18,
    [109] = 80,
    [110] = 33,
    [111] = 81,
    [112] = 18,
    [113] = 18,
    [114] = 18,
    [115] = 80,
    [116] = 33,
    [117] = 18,
    [118] = 42,
    [119] = 84,
    [120] = 80,
    [121] = 33,
    [122] = 18,
    [123] = 42,
    [124] = 84,
    [125] = 18,
    [126] = 42,
    [127] = 84,
    [128] = 87,
    [129] = 81,
    [130] = 18,
    [131] = 80,
    [132] = 33,
    [133] = 81,
    [134] = 18,
    [135] = 80,
    [136] = 33,
    [137] = 38,
    [138] = 80,
    [139] = 80,
    [140] = 33,
    [141] = 89,
    [142] = 40,
    [143] = 40,
    [144] = 18,
    [145] = 80,
    [146] = 33,
    [147] = 40,
    [148] = 18,
    [149] = 80,
    [150] = 33,
    [151] = 40,
    [152] = 89,
    [153] = 40,
    [154] = 18,
    [155] = 80,
    [156] = 33,
    [157] = 40,
    [158] = 18,
    [159] = 80,
    [160] = 33,
    [161] = 18,
    [162] = 84,
    [163] = 84,
    [164] = 36,
    [165] = 40,
    [166] = 81,
    [167] = 38,
    [168] = 36,
    [169] = 85,
    [170] = 84,
    [171] = 82,
    [172] = 84,
    [173] = 40,
    [174] = 81,
    [175] = 38,
    [176] = 36,
    [177] = 36,
    [178] = 36,
    [179] = 84,
    [180] = 36,
    [181] = 82,
    [182] = 84,
    [183] = 36,
    [184] = 36,
    [185] = 18,
    [186] = 90,
    [187] = 90,
    [188] = 92,
    [189] = 36,
    [190] = 36,
    [191] = 36,
    [192] = 36,
    [193] = 98,
    [194] = 98,
    [195] = 98,
};

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
        [ts_sym__func] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_sym__import] = SHIFT(5),
        [ts_sym__type] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_sym__var] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_sym_imports_block] = SHIFT(14),
        [ts_aux_sym_repeat_helper1] = SHIFT(16),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
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
        [ts_aux_sym_repeat_helper3] = SHIFT(12),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
        [ts_builtin_sym_error] = SHIFT(12),
    },
    [9] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_sym_string] = SHIFT(10),
        [ts_aux_sym_repeat_helper3] = SHIFT(11),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 0),
    },
    [10] = {
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_token2] = REDUCE(ts_sym_package_import, 1),
    },
    [11] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper3, 2),
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
        [ts_sym__func] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_sym__import] = SHIFT(5),
        [ts_sym__type] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_sym__var] = REDUCE(ts_aux_sym_repeat_helper1, 0),
        [ts_sym_imports_block] = SHIFT(14),
        [ts_aux_sym_repeat_helper1] = SHIFT(15),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 0),
    },
    [15] = {
        [ts_sym__func] = REDUCE(ts_aux_sym_repeat_helper1, 2),
        [ts_sym__type] = REDUCE(ts_aux_sym_repeat_helper1, 2),
        [ts_sym__var] = REDUCE(ts_aux_sym_repeat_helper1, 2),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper1, 2),
    },
    [16] = {
        [ts_sym__func] = SHIFT(17),
        [ts_sym__type] = SHIFT(161),
        [ts_sym__var] = SHIFT(185),
        [ts_sym_declaration] = SHIFT(191),
        [ts_sym_func_declaration] = SHIFT(192),
        [ts_sym_type_declaration] = SHIFT(192),
        [ts_sym_var_declaration] = SHIFT(192),
        [ts_aux_sym_repeat_helper2] = SHIFT(194),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper2, 0),
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
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_repeat_helper6] = SHIFT(27),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper6, 0),
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
        [ts_aux_sym_repeat_helper5] = SHIFT(137),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
    },
    [31] = {
        [ts_sym__func_signature] = SHIFT(32),
        [ts_aux_sym_token1] = SHIFT(34),
    },
    [32] = {
        [ts_sym__identifier] = SHIFT(18),
        [ts_sym_var_name] = SHIFT(31),
        [ts_aux_sym_repeat_helper5] = SHIFT(33),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
    },
    [33] = {
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 3),
    },
    [34] = {
        [ts_sym__identifier] = SHIFT(25),
        [ts_sym_var_name] = SHIFT(35),
        [ts_aux_sym_token2] = SHIFT(128),
    },
    [35] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_repeat_helper6] = SHIFT(36),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper6, 0),
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
        [ts_aux_sym_repeat_helper5] = SHIFT(42),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
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
        [ts_aux_sym_repeat_helper4] = SHIFT(78),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
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
        [ts_aux_sym_repeat_helper5] = SHIFT(53),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
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
        [ts_aux_sym_repeat_helper4] = SHIFT(62),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
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
        [ts_aux_sym_repeat_helper4] = SHIFT(77),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
    },
    [77] = {
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 3),
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
        [ts_aux_sym_repeat_helper4] = SHIFT(87),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
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
        [ts_aux_sym_repeat_helper8] = SHIFT(97),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 0),
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
        [ts_aux_sym_repeat_helper10] = SHIFT(103),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),
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
        [ts_aux_sym_repeat_helper10] = SHIFT(107),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),
        [ts_aux_sym_token9] = SHIFT(105),
    },
    [107] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 3),
    },
    [108] = {
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_type_name] = SHIFT(109),
    },
    [109] = {
        [ts_aux_sym_repeat_helper9] = SHIFT(110),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),
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
        [ts_aux_sym_repeat_helper9] = SHIFT(116),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),
        [ts_aux_sym_token9] = SHIFT(112),
    },
    [116] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 4),
    },
    [117] = {
        [ts_sym__identifier] = SHIFT(25),
        [ts_sym_var_name] = SHIFT(118),
    },
    [118] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_repeat_helper7] = SHIFT(119),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper7, 0),
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
        [ts_aux_sym_repeat_helper8] = SHIFT(121),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 0),
        [ts_aux_sym_token9] = SHIFT(117),
    },
    [121] = {
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 5),
    },
    [122] = {
        [ts_sym__identifier] = SHIFT(25),
        [ts_sym_var_name] = SHIFT(123),
    },
    [123] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_repeat_helper7] = SHIFT(124),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper7, 0),
        [ts_aux_sym_token9] = SHIFT(122),
    },
    [124] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper7, 3),
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper7, 3),
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper7, 3),
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper7, 3),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper7, 3),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper7, 3),
    },
    [125] = {
        [ts_sym__identifier] = SHIFT(25),
        [ts_sym_var_name] = SHIFT(126),
    },
    [126] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_repeat_helper6] = SHIFT(127),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper6, 0),
        [ts_aux_sym_token9] = SHIFT(125),
    },
    [127] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper6, 3),
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper6, 3),
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper6, 3),
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper6, 3),
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper6, 3),
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper6, 3),
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
        [ts_aux_sym_repeat_helper10] = SHIFT(132),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),
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
        [ts_aux_sym_repeat_helper9] = SHIFT(136),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),
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
        [ts_aux_sym_repeat_helper8] = SHIFT(140),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 0),
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
        [ts_aux_sym_repeat_helper10] = SHIFT(146),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),
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
        [ts_aux_sym_repeat_helper9] = SHIFT(150),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),
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
        [ts_aux_sym_repeat_helper10] = SHIFT(156),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),
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
        [ts_aux_sym_repeat_helper9] = SHIFT(160),
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),
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
        [ts_aux_sym_repeat_helper5] = SHIFT(167),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
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
        [ts_aux_sym_repeat_helper4] = SHIFT(175),
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
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
        [ts_aux_sym_repeat_helper2] = SHIFT(193),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    [192] = {
        [ts_sym__func] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__type] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__var] = REDUCE(ts_sym_declaration, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
    },
    [193] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    [194] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
    },
    [195] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
};

EXPORT_PARSER(ts_parser_golang);
