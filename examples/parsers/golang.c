#include "tree_sitter/parser.h"

STATE_COUNT = 225;
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
            if (lookahead == ')')
                ADVANCE(32);
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
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == '}')
                ADVANCE(39);
            LEX_ERROR();
        case 81:
            if (lookahead == ']')
                ADVANCE(82);
            LEX_ERROR();
        case 82:
            ACCEPT_TOKEN(ts_aux_sym_token8);
        case 83:
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
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(43);
            if (lookahead == 'm')
                ADVANCE(64);
            if ('n' <= lookahead && lookahead <= 'm')
                ADVANCE(84);
            if (lookahead == 's')
                ADVANCE(69);
            if ('t' <= lookahead && lookahead <= 's')
                ADVANCE(85);
            LEX_ERROR();
        case 84:
            if (lookahead == 'a')
                ADVANCE(65);
            LEX_ERROR();
        case 85:
            if (lookahead == 't')
                ADVANCE(70);
            LEX_ERROR();
        case 86:
            if (lookahead == '[')
                ADVANCE(54);
            LEX_ERROR();
        case 87:
            if (lookahead == ')')
                ADVANCE(32);
            if (lookahead == ',')
                ADVANCE(53);
            LEX_ERROR();
        case 88:
            if (lookahead == ')')
                ADVANCE(32);
            if (lookahead == ',')
                ADVANCE(53);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            LEX_ERROR();
        case 89:
            if (lookahead == ')')
                ADVANCE(32);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            LEX_ERROR();
        case 90:
            if (lookahead == '(')
                ADVANCE(35);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == '}')
                ADVANCE(39);
            LEX_ERROR();
        case 91:
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
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(43);
            if (lookahead == 'm')
                ADVANCE(64);
            if ('n' <= lookahead && lookahead <= 'm')
                ADVANCE(84);
            if (lookahead == 's')
                ADVANCE(69);
            if ('t' <= lookahead && lookahead <= 's')
                ADVANCE(85);
            LEX_ERROR();
        case 92:
            if (lookahead == ')')
                ADVANCE(32);
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
        case 93:
            if (lookahead == '(')
                ADVANCE(35);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(41);
            LEX_ERROR();
        case 94:
            if (lookahead == '=')
                ADVANCE(95);
            LEX_ERROR();
        case 95:
            ACCEPT_TOKEN(ts_aux_sym_token3);
        case 96:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(97);
            LEX_ERROR();
        case 97:
            if (lookahead == '.')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(101);
            ACCEPT_TOKEN(ts_sym_number);
        case 98:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(99);
            LEX_ERROR();
        case 99:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym_number);
        case 100:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym_number);
        case 101:
            if (lookahead == '.')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(101);
            ACCEPT_TOKEN(ts_sym_number);
        case 102:
            LEX_ERROR();
        case 103:
            if (lookahead == 'p')
                ADVANCE(104);
            LEX_ERROR();
        case 104:
            if (lookahead == 'a')
                ADVANCE(105);
            LEX_ERROR();
        case 105:
            if (lookahead == 'c')
                ADVANCE(106);
            LEX_ERROR();
        case 106:
            if (lookahead == 'k')
                ADVANCE(107);
            LEX_ERROR();
        case 107:
            if (lookahead == 'a')
                ADVANCE(108);
            LEX_ERROR();
        case 108:
            if (lookahead == 'g')
                ADVANCE(109);
            LEX_ERROR();
        case 109:
            if (lookahead == 'e')
                ADVANCE(110);
            LEX_ERROR();
        case 110:
            ACCEPT_TOKEN(ts_sym__package);
        case 111:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'u')
                ADVANCE(112);
            if ('v' <= lookahead && lookahead <= 'u')
                ADVANCE(2);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 112:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'n')
                ADVANCE(113);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(3);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 113:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(114);
            if ('d' <= lookahead && lookahead <= 'c')
                ADVANCE(4);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 114:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__func);
        case 115:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'm')
                ADVANCE(116);
            if ('n' <= lookahead && lookahead <= 'm')
                ADVANCE(6);
            if (lookahead == 'n')
                ADVANCE(56);
            if ('o' <= lookahead && lookahead <= 'n')
                ADVANCE(44);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 116:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'p')
                ADVANCE(117);
            if ('q' <= lookahead && lookahead <= 'p')
                ADVANCE(7);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 117:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'o')
                ADVANCE(118);
            if ('p' <= lookahead && lookahead <= 'o')
                ADVANCE(8);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 118:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(119);
            if ('s' <= lookahead && lookahead <= 'r')
                ADVANCE(9);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 119:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(120);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(10);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 120:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__import);
        case 121:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(122);
            if ('b' <= lookahead && lookahead <= 'a')
                ADVANCE(105);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 122:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'c')
                ADVANCE(123);
            if ('d' <= lookahead && lookahead <= 'c')
                ADVANCE(106);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 123:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'k')
                ADVANCE(124);
            if ('l' <= lookahead && lookahead <= 'k')
                ADVANCE(107);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(125);
            if ('b' <= lookahead && lookahead <= 'a')
                ADVANCE(108);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'g')
                ADVANCE(126);
            if ('h' <= lookahead && lookahead <= 'g')
                ADVANCE(109);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 126:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(127);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(110);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 127:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__package);
        case 128:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(20);
            if (lookahead == 'y')
                ADVANCE(129);
            if ('z' <= lookahead && lookahead <= 'y')
                ADVANCE(12);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 129:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'p')
                ADVANCE(130);
            if ('q' <= lookahead && lookahead <= 'p')
                ADVANCE(13);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 130:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(131);
            if ('f' <= lookahead && lookahead <= 'e')
                ADVANCE(14);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 131:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            ACCEPT_TOKEN(ts_sym__type);
        case 132:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'a')
                ADVANCE(133);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 133:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(20);
            if (lookahead == 'r')
                ADVANCE(134);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 134:
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
                ADVANCE(97);
            if (lookahead == '=')
                ADVANCE(95);
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
                ADVANCE(82);
            if (lookahead == 'f')
                ADVANCE(111);
            if ('g' <= lookahead && lookahead <= 'f')
                ADVANCE(1);
            if (lookahead == 'i')
                ADVANCE(115);
            if ('j' <= lookahead && lookahead <= 'i')
                ADVANCE(43);
            if (lookahead == 'm')
                ADVANCE(64);
            if ('n' <= lookahead && lookahead <= 'm')
                ADVANCE(84);
            if (lookahead == 'p')
                ADVANCE(121);
            if ('q' <= lookahead && lookahead <= 'p')
                ADVANCE(104);
            if (lookahead == 's')
                ADVANCE(69);
            if ('t' <= lookahead && lookahead <= 's')
                ADVANCE(85);
            if (lookahead == 't')
                ADVANCE(128);
            if ('u' <= lookahead && lookahead <= 't')
                ADVANCE(11);
            if (lookahead == 'v')
                ADVANCE(132);
            if ('w' <= lookahead && lookahead <= 'v')
                ADVANCE(15);
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
    [0] = 103,
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
    [24] = 92,
    [25] = 42,
    [26] = 40,
    [27] = 80,
    [28] = 37,
    [29] = 80,
    [30] = 38,
    [31] = 92,
    [32] = 86,
    [33] = 83,
    [34] = 81,
    [35] = 40,
    [36] = 80,
    [37] = 38,
    [38] = 81,
    [39] = 86,
    [40] = 83,
    [41] = 40,
    [42] = 80,
    [43] = 83,
    [44] = 83,
    [45] = 80,
    [46] = 40,
    [47] = 80,
    [48] = 38,
    [49] = 80,
    [50] = 86,
    [51] = 83,
    [52] = 81,
    [53] = 81,
    [54] = 83,
    [55] = 40,
    [56] = 80,
    [57] = 38,
    [58] = 80,
    [59] = 80,
    [60] = 80,
    [61] = 83,
    [62] = 80,
    [63] = 81,
    [64] = 83,
    [65] = 80,
    [66] = 83,
    [67] = 81,
    [68] = 81,
    [69] = 83,
    [70] = 81,
    [71] = 80,
    [72] = 38,
    [73] = 38,
    [74] = 81,
    [75] = 81,
    [76] = 83,
    [77] = 81,
    [78] = 81,
    [79] = 83,
    [80] = 87,
    [81] = 40,
    [82] = 80,
    [83] = 38,
    [84] = 87,
    [85] = 87,
    [86] = 87,
    [87] = 83,
    [88] = 87,
    [89] = 81,
    [90] = 83,
    [91] = 87,
    [92] = 87,
    [93] = 33,
    [94] = 90,
    [95] = 80,
    [96] = 89,
    [97] = 88,
    [98] = 87,
    [99] = 33,
    [100] = 80,
    [101] = 18,
    [102] = 87,
    [103] = 33,
    [104] = 18,
    [105] = 87,
    [106] = 33,
    [107] = 80,
    [108] = 18,
    [109] = 18,
    [110] = 18,
    [111] = 87,
    [112] = 33,
    [113] = 80,
    [114] = 83,
    [115] = 87,
    [116] = 33,
    [117] = 91,
    [118] = 83,
    [119] = 87,
    [120] = 33,
    [121] = 18,
    [122] = 91,
    [123] = 91,
    [124] = 83,
    [125] = 91,
    [126] = 83,
    [127] = 87,
    [128] = 33,
    [129] = 90,
    [130] = 80,
    [131] = 89,
    [132] = 87,
    [133] = 33,
    [134] = 80,
    [135] = 18,
    [136] = 87,
    [137] = 33,
    [138] = 80,
    [139] = 18,
    [140] = 91,
    [141] = 83,
    [142] = 90,
    [143] = 80,
    [144] = 89,
    [145] = 87,
    [146] = 33,
    [147] = 18,
    [148] = 87,
    [149] = 33,
    [150] = 80,
    [151] = 38,
    [152] = 87,
    [153] = 87,
    [154] = 33,
    [155] = 93,
    [156] = 40,
    [157] = 40,
    [158] = 89,
    [159] = 87,
    [160] = 33,
    [161] = 40,
    [162] = 18,
    [163] = 87,
    [164] = 33,
    [165] = 40,
    [166] = 40,
    [167] = 91,
    [168] = 83,
    [169] = 87,
    [170] = 33,
    [171] = 93,
    [172] = 40,
    [173] = 89,
    [174] = 87,
    [175] = 33,
    [176] = 40,
    [177] = 18,
    [178] = 87,
    [179] = 33,
    [180] = 40,
    [181] = 93,
    [182] = 40,
    [183] = 89,
    [184] = 87,
    [185] = 33,
    [186] = 18,
    [187] = 87,
    [188] = 33,
    [189] = 40,
    [190] = 18,
    [191] = 83,
    [192] = 83,
    [193] = 36,
    [194] = 40,
    [195] = 80,
    [196] = 38,
    [197] = 36,
    [198] = 86,
    [199] = 83,
    [200] = 81,
    [201] = 83,
    [202] = 40,
    [203] = 80,
    [204] = 38,
    [205] = 36,
    [206] = 36,
    [207] = 36,
    [208] = 83,
    [209] = 36,
    [210] = 81,
    [211] = 83,
    [212] = 36,
    [213] = 36,
    [214] = 18,
    [215] = 94,
    [216] = 94,
    [217] = 96,
    [218] = 36,
    [219] = 36,
    [220] = 36,
    [221] = 36,
    [222] = 102,
    [223] = 102,
    [224] = 102,
};

PARSE_TABLE = {
    [0] = {    
        [ts_sym__package] = SHIFT(1),    
        [ts_sym_package_directive] = SHIFT(4),    
        [ts_sym_program] = SHIFT(224),
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
        [ts_sym__type] = SHIFT(190),    
        [ts_sym__var] = SHIFT(214),    
        [ts_sym_declaration] = SHIFT(220),    
        [ts_sym_func_declaration] = SHIFT(221),    
        [ts_sym_type_declaration] = SHIFT(221),    
        [ts_sym_var_declaration] = SHIFT(221),    
        [ts_aux_sym_repeat_helper2] = SHIFT(223),    
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
        [ts_sym__interface] = SHIFT(26),    
        [ts_sym__map] = SHIFT(32),    
        [ts_sym__struct] = SHIFT(81),    
        [ts_sym_interface_type] = SHIFT(85),    
        [ts_sym_map_type] = SHIFT(85),    
        [ts_sym_pointer_type] = SHIFT(85),    
        [ts_sym_slice_type] = SHIFT(85),    
        [ts_sym_struct_type] = SHIFT(85),    
        [ts_sym_type_expression] = SHIFT(153),    
        [ts_sym_type_name] = SHIFT(85),    
        [ts_sym_var_name] = SHIFT(167),    
        [ts_aux_sym_token2] = SHIFT(181),    
        [ts_aux_sym_token6] = SHIFT(87),    
        [ts_aux_sym_token7] = SHIFT(89),
    },
    
    [25] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),    
        [ts_sym__interface] = REDUCE(ts_sym_var_name, 1),    
        [ts_sym__map] = REDUCE(ts_sym_var_name, 1),    
        [ts_sym__struct] = REDUCE(ts_sym_var_name, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_type_name, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_name, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_name, 1),
    },
    
    [26] = {    
        [ts_aux_sym_token4] = SHIFT(27),
    },
    
    [27] = {    
        [ts_sym__identifier] = SHIFT(18),    
        [ts_sym_var_name] = SHIFT(28),    
        [ts_aux_sym_repeat_helper5] = SHIFT(151),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
    },
    
    [28] = {    
        [ts_sym__func_signature] = SHIFT(29),    
        [ts_aux_sym_token1] = SHIFT(31),
    },
    
    [29] = {    
        [ts_sym__identifier] = SHIFT(18),    
        [ts_sym_var_name] = SHIFT(28),    
        [ts_aux_sym_repeat_helper5] = SHIFT(30),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
    },
    
    [30] = {    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 3),
    },
    
    [31] = {    
        [ts_sym__identifier] = SHIFT(25),    
        [ts_sym__interface] = SHIFT(26),    
        [ts_sym__map] = SHIFT(32),    
        [ts_sym__struct] = SHIFT(81),    
        [ts_sym_interface_type] = SHIFT(85),    
        [ts_sym_map_type] = SHIFT(85),    
        [ts_sym_pointer_type] = SHIFT(85),    
        [ts_sym_slice_type] = SHIFT(85),    
        [ts_sym_struct_type] = SHIFT(85),    
        [ts_sym_type_expression] = SHIFT(92),    
        [ts_sym_type_name] = SHIFT(85),    
        [ts_sym_var_name] = SHIFT(125),    
        [ts_aux_sym_token2] = SHIFT(142),    
        [ts_aux_sym_token6] = SHIFT(87),    
        [ts_aux_sym_token7] = SHIFT(89),
    },
    
    [32] = {    
        [ts_aux_sym_token7] = SHIFT(33),
    },
    
    [33] = {    
        [ts_sym__identifier] = SHIFT(34),    
        [ts_sym__interface] = SHIFT(35),    
        [ts_sym__map] = SHIFT(39),    
        [ts_sym__struct] = SHIFT(41),    
        [ts_sym_interface_type] = SHIFT(52),    
        [ts_sym_map_type] = SHIFT(52),    
        [ts_sym_pointer_type] = SHIFT(52),    
        [ts_sym_slice_type] = SHIFT(52),    
        [ts_sym_struct_type] = SHIFT(52),    
        [ts_sym_type_expression] = SHIFT(78),    
        [ts_sym_type_name] = SHIFT(52),    
        [ts_aux_sym_token6] = SHIFT(66),    
        [ts_aux_sym_token7] = SHIFT(68),
    },
    
    [34] = {    
        [ts_aux_sym_token8] = REDUCE(ts_sym_type_name, 1),
    },
    
    [35] = {    
        [ts_aux_sym_token4] = SHIFT(36),
    },
    
    [36] = {    
        [ts_sym__identifier] = SHIFT(18),    
        [ts_sym_var_name] = SHIFT(28),    
        [ts_aux_sym_repeat_helper5] = SHIFT(37),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
    },
    
    [37] = {    
        [ts_aux_sym_token5] = SHIFT(38),
    },
    
    [38] = {    
        [ts_aux_sym_token8] = REDUCE(ts_sym_interface_type, 4),
    },
    
    [39] = {    
        [ts_aux_sym_token7] = SHIFT(40),
    },
    
    [40] = {    
        [ts_sym__identifier] = SHIFT(34),    
        [ts_sym__interface] = SHIFT(35),    
        [ts_sym__map] = SHIFT(39),    
        [ts_sym__struct] = SHIFT(41),    
        [ts_sym_interface_type] = SHIFT(52),    
        [ts_sym_map_type] = SHIFT(52),    
        [ts_sym_pointer_type] = SHIFT(52),    
        [ts_sym_slice_type] = SHIFT(52),    
        [ts_sym_struct_type] = SHIFT(52),    
        [ts_sym_type_expression] = SHIFT(75),    
        [ts_sym_type_name] = SHIFT(52),    
        [ts_aux_sym_token6] = SHIFT(66),    
        [ts_aux_sym_token7] = SHIFT(68),
    },
    
    [41] = {    
        [ts_aux_sym_token4] = SHIFT(42),
    },
    
    [42] = {    
        [ts_sym__identifier] = SHIFT(43),    
        [ts_sym_var_name] = SHIFT(44),    
        [ts_aux_sym_repeat_helper4] = SHIFT(73),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
    },
    
    [43] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),    
        [ts_sym__interface] = REDUCE(ts_sym_var_name, 1),    
        [ts_sym__map] = REDUCE(ts_sym_var_name, 1),    
        [ts_sym__struct] = REDUCE(ts_sym_var_name, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_name, 1),
    },
    
    [44] = {    
        [ts_sym__identifier] = SHIFT(45),    
        [ts_sym__interface] = SHIFT(46),    
        [ts_sym__map] = SHIFT(50),    
        [ts_sym__struct] = SHIFT(55),    
        [ts_sym_interface_type] = SHIFT(59),    
        [ts_sym_map_type] = SHIFT(59),    
        [ts_sym_pointer_type] = SHIFT(59),    
        [ts_sym_slice_type] = SHIFT(59),    
        [ts_sym_struct_type] = SHIFT(59),    
        [ts_sym_type_expression] = SHIFT(71),    
        [ts_sym_type_name] = SHIFT(59),    
        [ts_aux_sym_token6] = SHIFT(61),    
        [ts_aux_sym_token7] = SHIFT(63),
    },
    
    [45] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_name, 1),
    },
    
    [46] = {    
        [ts_aux_sym_token4] = SHIFT(47),
    },
    
    [47] = {    
        [ts_sym__identifier] = SHIFT(18),    
        [ts_sym_var_name] = SHIFT(28),    
        [ts_aux_sym_repeat_helper5] = SHIFT(48),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
    },
    
    [48] = {    
        [ts_aux_sym_token5] = SHIFT(49),
    },
    
    [49] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_interface_type, 4),
    },
    
    [50] = {    
        [ts_aux_sym_token7] = SHIFT(51),
    },
    
    [51] = {    
        [ts_sym__identifier] = SHIFT(34),    
        [ts_sym__interface] = SHIFT(35),    
        [ts_sym__map] = SHIFT(39),    
        [ts_sym__struct] = SHIFT(41),    
        [ts_sym_interface_type] = SHIFT(52),    
        [ts_sym_map_type] = SHIFT(52),    
        [ts_sym_pointer_type] = SHIFT(52),    
        [ts_sym_slice_type] = SHIFT(52),    
        [ts_sym_struct_type] = SHIFT(52),    
        [ts_sym_type_expression] = SHIFT(53),    
        [ts_sym_type_name] = SHIFT(52),    
        [ts_aux_sym_token6] = SHIFT(66),    
        [ts_aux_sym_token7] = SHIFT(68),
    },
    
    [52] = {    
        [ts_aux_sym_token8] = REDUCE(ts_sym_type_expression, 1),
    },
    
    [53] = {    
        [ts_aux_sym_token8] = SHIFT(54),
    },
    
    [54] = {    
        [ts_sym__identifier] = SHIFT(45),    
        [ts_sym__interface] = SHIFT(46),    
        [ts_sym__map] = SHIFT(50),    
        [ts_sym__struct] = SHIFT(55),    
        [ts_sym_interface_type] = SHIFT(59),    
        [ts_sym_map_type] = SHIFT(59),    
        [ts_sym_pointer_type] = SHIFT(59),    
        [ts_sym_slice_type] = SHIFT(59),    
        [ts_sym_struct_type] = SHIFT(59),    
        [ts_sym_type_expression] = SHIFT(60),    
        [ts_sym_type_name] = SHIFT(59),    
        [ts_aux_sym_token6] = SHIFT(61),    
        [ts_aux_sym_token7] = SHIFT(63),
    },
    
    [55] = {    
        [ts_aux_sym_token4] = SHIFT(56),
    },
    
    [56] = {    
        [ts_sym__identifier] = SHIFT(43),    
        [ts_sym_var_name] = SHIFT(44),    
        [ts_aux_sym_repeat_helper4] = SHIFT(57),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
    },
    
    [57] = {    
        [ts_aux_sym_token5] = SHIFT(58),
    },
    
    [58] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_struct_type, 4),
    },
    
    [59] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_type_expression, 1),
    },
    
    [60] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_map_type, 5),
    },
    
    [61] = {    
        [ts_sym__identifier] = SHIFT(45),    
        [ts_sym__interface] = SHIFT(46),    
        [ts_sym__map] = SHIFT(50),    
        [ts_sym__struct] = SHIFT(55),    
        [ts_sym_interface_type] = SHIFT(59),    
        [ts_sym_map_type] = SHIFT(59),    
        [ts_sym_pointer_type] = SHIFT(59),    
        [ts_sym_slice_type] = SHIFT(59),    
        [ts_sym_struct_type] = SHIFT(59),    
        [ts_sym_type_expression] = SHIFT(62),    
        [ts_sym_type_name] = SHIFT(59),    
        [ts_aux_sym_token6] = SHIFT(61),    
        [ts_aux_sym_token7] = SHIFT(63),
    },
    
    [62] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_pointer_type, 2),
    },
    
    [63] = {    
        [ts_aux_sym_token8] = SHIFT(64),
    },
    
    [64] = {    
        [ts_sym__identifier] = SHIFT(45),    
        [ts_sym__interface] = SHIFT(46),    
        [ts_sym__map] = SHIFT(50),    
        [ts_sym__struct] = SHIFT(55),    
        [ts_sym_interface_type] = SHIFT(59),    
        [ts_sym_map_type] = SHIFT(59),    
        [ts_sym_pointer_type] = SHIFT(59),    
        [ts_sym_slice_type] = SHIFT(59),    
        [ts_sym_struct_type] = SHIFT(59),    
        [ts_sym_type_expression] = SHIFT(65),    
        [ts_sym_type_name] = SHIFT(59),    
        [ts_aux_sym_token6] = SHIFT(61),    
        [ts_aux_sym_token7] = SHIFT(63),
    },
    
    [65] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),    
        [ts_aux_sym_token5] = REDUCE(ts_sym_slice_type, 3),
    },
    
    [66] = {    
        [ts_sym__identifier] = SHIFT(34),    
        [ts_sym__interface] = SHIFT(35),    
        [ts_sym__map] = SHIFT(39),    
        [ts_sym__struct] = SHIFT(41),    
        [ts_sym_interface_type] = SHIFT(52),    
        [ts_sym_map_type] = SHIFT(52),    
        [ts_sym_pointer_type] = SHIFT(52),    
        [ts_sym_slice_type] = SHIFT(52),    
        [ts_sym_struct_type] = SHIFT(52),    
        [ts_sym_type_expression] = SHIFT(67),    
        [ts_sym_type_name] = SHIFT(52),    
        [ts_aux_sym_token6] = SHIFT(66),    
        [ts_aux_sym_token7] = SHIFT(68),
    },
    
    [67] = {    
        [ts_aux_sym_token8] = REDUCE(ts_sym_pointer_type, 2),
    },
    
    [68] = {    
        [ts_aux_sym_token8] = SHIFT(69),
    },
    
    [69] = {    
        [ts_sym__identifier] = SHIFT(34),    
        [ts_sym__interface] = SHIFT(35),    
        [ts_sym__map] = SHIFT(39),    
        [ts_sym__struct] = SHIFT(41),    
        [ts_sym_interface_type] = SHIFT(52),    
        [ts_sym_map_type] = SHIFT(52),    
        [ts_sym_pointer_type] = SHIFT(52),    
        [ts_sym_slice_type] = SHIFT(52),    
        [ts_sym_struct_type] = SHIFT(52),    
        [ts_sym_type_expression] = SHIFT(70),    
        [ts_sym_type_name] = SHIFT(52),    
        [ts_aux_sym_token6] = SHIFT(66),    
        [ts_aux_sym_token7] = SHIFT(68),
    },
    
    [70] = {    
        [ts_aux_sym_token8] = REDUCE(ts_sym_slice_type, 3),
    },
    
    [71] = {    
        [ts_sym__identifier] = SHIFT(43),    
        [ts_sym_var_name] = SHIFT(44),    
        [ts_aux_sym_repeat_helper4] = SHIFT(72),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
    },
    
    [72] = {    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 3),
    },
    
    [73] = {    
        [ts_aux_sym_token5] = SHIFT(74),
    },
    
    [74] = {    
        [ts_aux_sym_token8] = REDUCE(ts_sym_struct_type, 4),
    },
    
    [75] = {    
        [ts_aux_sym_token8] = SHIFT(76),
    },
    
    [76] = {    
        [ts_sym__identifier] = SHIFT(34),    
        [ts_sym__interface] = SHIFT(35),    
        [ts_sym__map] = SHIFT(39),    
        [ts_sym__struct] = SHIFT(41),    
        [ts_sym_interface_type] = SHIFT(52),    
        [ts_sym_map_type] = SHIFT(52),    
        [ts_sym_pointer_type] = SHIFT(52),    
        [ts_sym_slice_type] = SHIFT(52),    
        [ts_sym_struct_type] = SHIFT(52),    
        [ts_sym_type_expression] = SHIFT(77),    
        [ts_sym_type_name] = SHIFT(52),    
        [ts_aux_sym_token6] = SHIFT(66),    
        [ts_aux_sym_token7] = SHIFT(68),
    },
    
    [77] = {    
        [ts_aux_sym_token8] = REDUCE(ts_sym_map_type, 5),
    },
    
    [78] = {    
        [ts_aux_sym_token8] = SHIFT(79),
    },
    
    [79] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym__interface] = SHIFT(26),    
        [ts_sym__map] = SHIFT(32),    
        [ts_sym__struct] = SHIFT(81),    
        [ts_sym_interface_type] = SHIFT(85),    
        [ts_sym_map_type] = SHIFT(85),    
        [ts_sym_pointer_type] = SHIFT(85),    
        [ts_sym_slice_type] = SHIFT(85),    
        [ts_sym_struct_type] = SHIFT(85),    
        [ts_sym_type_expression] = SHIFT(86),    
        [ts_sym_type_name] = SHIFT(85),    
        [ts_aux_sym_token6] = SHIFT(87),    
        [ts_aux_sym_token7] = SHIFT(89),
    },
    
    [80] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_type_name, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_type_name, 1),
    },
    
    [81] = {    
        [ts_aux_sym_token4] = SHIFT(82),
    },
    
    [82] = {    
        [ts_sym__identifier] = SHIFT(43),    
        [ts_sym_var_name] = SHIFT(44),    
        [ts_aux_sym_repeat_helper4] = SHIFT(83),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
    },
    
    [83] = {    
        [ts_aux_sym_token5] = SHIFT(84),
    },
    
    [84] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_struct_type, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_struct_type, 4),
    },
    
    [85] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_type_expression, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_type_expression, 1),
    },
    
    [86] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_map_type, 5),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_map_type, 5),
    },
    
    [87] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym__interface] = SHIFT(26),    
        [ts_sym__map] = SHIFT(32),    
        [ts_sym__struct] = SHIFT(81),    
        [ts_sym_interface_type] = SHIFT(85),    
        [ts_sym_map_type] = SHIFT(85),    
        [ts_sym_pointer_type] = SHIFT(85),    
        [ts_sym_slice_type] = SHIFT(85),    
        [ts_sym_struct_type] = SHIFT(85),    
        [ts_sym_type_expression] = SHIFT(88),    
        [ts_sym_type_name] = SHIFT(85),    
        [ts_aux_sym_token6] = SHIFT(87),    
        [ts_aux_sym_token7] = SHIFT(89),
    },
    
    [88] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_pointer_type, 2),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_pointer_type, 2),
    },
    
    [89] = {    
        [ts_aux_sym_token8] = SHIFT(90),
    },
    
    [90] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym__interface] = SHIFT(26),    
        [ts_sym__map] = SHIFT(32),    
        [ts_sym__struct] = SHIFT(81),    
        [ts_sym_interface_type] = SHIFT(85),    
        [ts_sym_map_type] = SHIFT(85),    
        [ts_sym_pointer_type] = SHIFT(85),    
        [ts_sym_slice_type] = SHIFT(85),    
        [ts_sym_struct_type] = SHIFT(85),    
        [ts_sym_type_expression] = SHIFT(91),    
        [ts_sym_type_name] = SHIFT(85),    
        [ts_aux_sym_token6] = SHIFT(87),    
        [ts_aux_sym_token7] = SHIFT(89),
    },
    
    [91] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_slice_type, 3),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_slice_type, 3),
    },
    
    [92] = {    
        [ts_aux_sym_repeat_helper8] = SHIFT(93),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 0),    
        [ts_aux_sym_token9] = SHIFT(114),
    },
    
    [93] = {    
        [ts_aux_sym_token2] = SHIFT(94),
    },
    
    [94] = {    
        [ts_sym__identifier] = SHIFT(45),    
        [ts_sym_type_name] = SHIFT(95),    
        [ts_aux_sym_token1] = SHIFT(96),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 4),
    },
    
    [95] = {    
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 5),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 5),
    },
    
    [96] = {    
        [ts_sym__identifier] = SHIFT(97),    
        [ts_sym_type_name] = SHIFT(98),    
        [ts_sym_var_name] = SHIFT(104),    
        [ts_aux_sym_token2] = SHIFT(113),
    },
    
    [97] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),    
        [ts_aux_sym_token2] = REDUCE(ts_sym_type_name, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_type_name, 1),
    },
    
    [98] = {    
        [ts_aux_sym_repeat_helper10] = SHIFT(99),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),    
        [ts_aux_sym_token9] = SHIFT(101),
    },
    
    [99] = {    
        [ts_aux_sym_token2] = SHIFT(100),
    },
    
    [100] = {    
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 8),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 8),
    },
    
    [101] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym_type_name] = SHIFT(102),
    },
    
    [102] = {    
        [ts_aux_sym_repeat_helper10] = SHIFT(103),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),    
        [ts_aux_sym_token9] = SHIFT(101),
    },
    
    [103] = {    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 3),
    },
    
    [104] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym_type_name] = SHIFT(105),
    },
    
    [105] = {    
        [ts_aux_sym_repeat_helper9] = SHIFT(106),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),    
        [ts_aux_sym_token9] = SHIFT(108),
    },
    
    [106] = {    
        [ts_aux_sym_token2] = SHIFT(107),
    },
    
    [107] = {    
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 9),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 9),
    },
    
    [108] = {    
        [ts_sym__identifier] = SHIFT(109),    
        [ts_sym_var_name] = SHIFT(110),
    },
    
    [109] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
    },
    
    [110] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym_type_name] = SHIFT(111),
    },
    
    [111] = {    
        [ts_aux_sym_repeat_helper9] = SHIFT(112),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),    
        [ts_aux_sym_token9] = SHIFT(108),
    },
    
    [112] = {    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 4),
    },
    
    [113] = {    
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 6),
    },
    
    [114] = {    
        [ts_sym__identifier] = SHIFT(25),    
        [ts_sym__interface] = SHIFT(26),    
        [ts_sym__map] = SHIFT(32),    
        [ts_sym__struct] = SHIFT(81),    
        [ts_sym_interface_type] = SHIFT(85),    
        [ts_sym_map_type] = SHIFT(85),    
        [ts_sym_pointer_type] = SHIFT(85),    
        [ts_sym_slice_type] = SHIFT(85),    
        [ts_sym_struct_type] = SHIFT(85),    
        [ts_sym_type_expression] = SHIFT(115),    
        [ts_sym_type_name] = SHIFT(85),    
        [ts_sym_var_name] = SHIFT(117),    
        [ts_aux_sym_token6] = SHIFT(87),    
        [ts_aux_sym_token7] = SHIFT(89),
    },
    
    [115] = {    
        [ts_aux_sym_repeat_helper8] = SHIFT(116),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 0),    
        [ts_aux_sym_token9] = SHIFT(114),
    },
    
    [116] = {    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 3),
    },
    
    [117] = {    
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_aux_sym_repeat_helper7] = SHIFT(118),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_aux_sym_token9] = SHIFT(121),
    },
    
    [118] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym__interface] = SHIFT(26),    
        [ts_sym__map] = SHIFT(32),    
        [ts_sym__struct] = SHIFT(81),    
        [ts_sym_interface_type] = SHIFT(85),    
        [ts_sym_map_type] = SHIFT(85),    
        [ts_sym_pointer_type] = SHIFT(85),    
        [ts_sym_slice_type] = SHIFT(85),    
        [ts_sym_struct_type] = SHIFT(85),    
        [ts_sym_type_expression] = SHIFT(119),    
        [ts_sym_type_name] = SHIFT(85),    
        [ts_aux_sym_token6] = SHIFT(87),    
        [ts_aux_sym_token7] = SHIFT(89),
    },
    
    [119] = {    
        [ts_aux_sym_repeat_helper8] = SHIFT(120),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 0),    
        [ts_aux_sym_token9] = SHIFT(114),
    },
    
    [120] = {    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 5),
    },
    
    [121] = {    
        [ts_sym__identifier] = SHIFT(122),    
        [ts_sym_var_name] = SHIFT(123),
    },
    
    [122] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),    
        [ts_sym__interface] = REDUCE(ts_sym_var_name, 1),    
        [ts_sym__map] = REDUCE(ts_sym_var_name, 1),    
        [ts_sym__struct] = REDUCE(ts_sym_var_name, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_var_name, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_var_name, 1),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_var_name, 1),
    },
    
    [123] = {    
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_aux_sym_repeat_helper7] = SHIFT(124),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper7, 0),    
        [ts_aux_sym_token9] = SHIFT(121),
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
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_repeat_helper6] = SHIFT(126),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token9] = SHIFT(139),
    },
    
    [126] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym__interface] = SHIFT(26),    
        [ts_sym__map] = SHIFT(32),    
        [ts_sym__struct] = SHIFT(81),    
        [ts_sym_interface_type] = SHIFT(85),    
        [ts_sym_map_type] = SHIFT(85),    
        [ts_sym_pointer_type] = SHIFT(85),    
        [ts_sym_slice_type] = SHIFT(85),    
        [ts_sym_struct_type] = SHIFT(85),    
        [ts_sym_type_expression] = SHIFT(127),    
        [ts_sym_type_name] = SHIFT(85),    
        [ts_aux_sym_token6] = SHIFT(87),    
        [ts_aux_sym_token7] = SHIFT(89),
    },
    
    [127] = {    
        [ts_aux_sym_repeat_helper8] = SHIFT(128),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 0),    
        [ts_aux_sym_token9] = SHIFT(114),
    },
    
    [128] = {    
        [ts_aux_sym_token2] = SHIFT(129),
    },
    
    [129] = {    
        [ts_sym__identifier] = SHIFT(45),    
        [ts_sym_type_name] = SHIFT(130),    
        [ts_aux_sym_token1] = SHIFT(131),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 6),
    },
    
    [130] = {    
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 7),
    },
    
    [131] = {    
        [ts_sym__identifier] = SHIFT(97),    
        [ts_sym_type_name] = SHIFT(132),    
        [ts_sym_var_name] = SHIFT(135),    
        [ts_aux_sym_token2] = SHIFT(100),
    },
    
    [132] = {    
        [ts_aux_sym_repeat_helper10] = SHIFT(133),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),    
        [ts_aux_sym_token9] = SHIFT(101),
    },
    
    [133] = {    
        [ts_aux_sym_token2] = SHIFT(134),
    },
    
    [134] = {    
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 10),
    },
    
    [135] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym_type_name] = SHIFT(136),
    },
    
    [136] = {    
        [ts_aux_sym_repeat_helper9] = SHIFT(137),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),    
        [ts_aux_sym_token9] = SHIFT(108),
    },
    
    [137] = {    
        [ts_aux_sym_token2] = SHIFT(138),
    },
    
    [138] = {    
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 11),
    },
    
    [139] = {    
        [ts_sym__identifier] = SHIFT(122),    
        [ts_sym_var_name] = SHIFT(140),
    },
    
    [140] = {    
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_repeat_helper6] = SHIFT(141),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token9] = SHIFT(139),
    },
    
    [141] = {    
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper6, 3),    
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper6, 3),    
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper6, 3),    
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper6, 3),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper6, 3),    
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper6, 3),
    },
    
    [142] = {    
        [ts_sym__identifier] = SHIFT(45),    
        [ts_sym_type_name] = SHIFT(143),    
        [ts_aux_sym_token1] = SHIFT(144),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 2),
    },
    
    [143] = {    
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 3),
    },
    
    [144] = {    
        [ts_sym__identifier] = SHIFT(97),    
        [ts_sym_type_name] = SHIFT(145),    
        [ts_sym_var_name] = SHIFT(147),    
        [ts_aux_sym_token2] = SHIFT(150),
    },
    
    [145] = {    
        [ts_aux_sym_repeat_helper10] = SHIFT(146),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),    
        [ts_aux_sym_token9] = SHIFT(101),
    },
    
    [146] = {    
        [ts_aux_sym_token2] = SHIFT(113),
    },
    
    [147] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym_type_name] = SHIFT(148),
    },
    
    [148] = {    
        [ts_aux_sym_repeat_helper9] = SHIFT(149),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),    
        [ts_aux_sym_token9] = SHIFT(108),
    },
    
    [149] = {    
        [ts_aux_sym_token2] = SHIFT(130),
    },
    
    [150] = {    
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 4),    
        [ts_aux_sym_token5] = REDUCE(ts_sym__func_signature, 4),
    },
    
    [151] = {    
        [ts_aux_sym_token5] = SHIFT(152),
    },
    
    [152] = {    
        [ts_aux_sym_token2] = REDUCE(ts_sym_interface_type, 4),    
        [ts_aux_sym_token9] = REDUCE(ts_sym_interface_type, 4),
    },
    
    [153] = {    
        [ts_aux_sym_repeat_helper8] = SHIFT(154),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 0),    
        [ts_aux_sym_token9] = SHIFT(114),
    },
    
    [154] = {    
        [ts_aux_sym_token2] = SHIFT(155),
    },
    
    [155] = {    
        [ts_sym__identifier] = SHIFT(156),    
        [ts_sym_type_name] = SHIFT(157),    
        [ts_aux_sym_token1] = SHIFT(158),    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 4),
    },
    
    [156] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym_type_name, 1),
    },
    
    [157] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 5),
    },
    
    [158] = {    
        [ts_sym__identifier] = SHIFT(97),    
        [ts_sym_type_name] = SHIFT(159),    
        [ts_sym_var_name] = SHIFT(162),    
        [ts_aux_sym_token2] = SHIFT(166),
    },
    
    [159] = {    
        [ts_aux_sym_repeat_helper10] = SHIFT(160),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),    
        [ts_aux_sym_token9] = SHIFT(101),
    },
    
    [160] = {    
        [ts_aux_sym_token2] = SHIFT(161),
    },
    
    [161] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 8),
    },
    
    [162] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym_type_name] = SHIFT(163),
    },
    
    [163] = {    
        [ts_aux_sym_repeat_helper9] = SHIFT(164),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),    
        [ts_aux_sym_token9] = SHIFT(108),
    },
    
    [164] = {    
        [ts_aux_sym_token2] = SHIFT(165),
    },
    
    [165] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 9),
    },
    
    [166] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 6),
    },
    
    [167] = {    
        [ts_sym__identifier] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_sym__interface] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_sym__map] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_sym__struct] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_repeat_helper6] = SHIFT(168),    
        [ts_aux_sym_token6] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token7] = REDUCE(ts_aux_sym_repeat_helper6, 0),    
        [ts_aux_sym_token9] = SHIFT(139),
    },
    
    [168] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym__interface] = SHIFT(26),    
        [ts_sym__map] = SHIFT(32),    
        [ts_sym__struct] = SHIFT(81),    
        [ts_sym_interface_type] = SHIFT(85),    
        [ts_sym_map_type] = SHIFT(85),    
        [ts_sym_pointer_type] = SHIFT(85),    
        [ts_sym_slice_type] = SHIFT(85),    
        [ts_sym_struct_type] = SHIFT(85),    
        [ts_sym_type_expression] = SHIFT(169),    
        [ts_sym_type_name] = SHIFT(85),    
        [ts_aux_sym_token6] = SHIFT(87),    
        [ts_aux_sym_token7] = SHIFT(89),
    },
    
    [169] = {    
        [ts_aux_sym_repeat_helper8] = SHIFT(170),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper8, 0),    
        [ts_aux_sym_token9] = SHIFT(114),
    },
    
    [170] = {    
        [ts_aux_sym_token2] = SHIFT(171),
    },
    
    [171] = {    
        [ts_sym__identifier] = SHIFT(156),    
        [ts_sym_type_name] = SHIFT(172),    
        [ts_aux_sym_token1] = SHIFT(173),    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 6),
    },
    
    [172] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 7),
    },
    
    [173] = {    
        [ts_sym__identifier] = SHIFT(97),    
        [ts_sym_type_name] = SHIFT(174),    
        [ts_sym_var_name] = SHIFT(177),    
        [ts_aux_sym_token2] = SHIFT(161),
    },
    
    [174] = {    
        [ts_aux_sym_repeat_helper10] = SHIFT(175),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),    
        [ts_aux_sym_token9] = SHIFT(101),
    },
    
    [175] = {    
        [ts_aux_sym_token2] = SHIFT(176),
    },
    
    [176] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 10),
    },
    
    [177] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym_type_name] = SHIFT(178),
    },
    
    [178] = {    
        [ts_aux_sym_repeat_helper9] = SHIFT(179),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),    
        [ts_aux_sym_token9] = SHIFT(108),
    },
    
    [179] = {    
        [ts_aux_sym_token2] = SHIFT(180),
    },
    
    [180] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 11),
    },
    
    [181] = {    
        [ts_sym__identifier] = SHIFT(156),    
        [ts_sym_type_name] = SHIFT(182),    
        [ts_aux_sym_token1] = SHIFT(183),    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 2),
    },
    
    [182] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 3),
    },
    
    [183] = {    
        [ts_sym__identifier] = SHIFT(97),    
        [ts_sym_type_name] = SHIFT(184),    
        [ts_sym_var_name] = SHIFT(186),    
        [ts_aux_sym_token2] = SHIFT(189),
    },
    
    [184] = {    
        [ts_aux_sym_repeat_helper10] = SHIFT(185),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper10, 0),    
        [ts_aux_sym_token9] = SHIFT(101),
    },
    
    [185] = {    
        [ts_aux_sym_token2] = SHIFT(166),
    },
    
    [186] = {    
        [ts_sym__identifier] = SHIFT(80),    
        [ts_sym_type_name] = SHIFT(187),
    },
    
    [187] = {    
        [ts_aux_sym_repeat_helper9] = SHIFT(188),    
        [ts_aux_sym_token2] = REDUCE(ts_aux_sym_repeat_helper9, 0),    
        [ts_aux_sym_token9] = SHIFT(108),
    },
    
    [188] = {    
        [ts_aux_sym_token2] = SHIFT(172),
    },
    
    [189] = {    
        [ts_aux_sym_token4] = REDUCE(ts_sym__func_signature, 4),
    },
    
    [190] = {    
        [ts_sym__identifier] = SHIFT(191),    
        [ts_sym_type_name] = SHIFT(192),
    },
    
    [191] = {    
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),    
        [ts_sym__interface] = REDUCE(ts_sym_type_name, 1),    
        [ts_sym__map] = REDUCE(ts_sym_type_name, 1),    
        [ts_sym__struct] = REDUCE(ts_sym_type_name, 1),    
        [ts_aux_sym_token6] = REDUCE(ts_sym_type_name, 1),    
        [ts_aux_sym_token7] = REDUCE(ts_sym_type_name, 1),
    },
    
    [192] = {    
        [ts_sym__identifier] = SHIFT(193),    
        [ts_sym__interface] = SHIFT(194),    
        [ts_sym__map] = SHIFT(198),    
        [ts_sym__struct] = SHIFT(202),    
        [ts_sym_interface_type] = SHIFT(206),    
        [ts_sym_map_type] = SHIFT(206),    
        [ts_sym_pointer_type] = SHIFT(206),    
        [ts_sym_slice_type] = SHIFT(206),    
        [ts_sym_struct_type] = SHIFT(206),    
        [ts_sym_type_expression] = SHIFT(213),    
        [ts_sym_type_name] = SHIFT(206),    
        [ts_aux_sym_token6] = SHIFT(208),    
        [ts_aux_sym_token7] = SHIFT(210),
    },
    
    [193] = {    
        [ts_sym__func] = REDUCE(ts_sym_type_name, 1),    
        [ts_sym__type] = REDUCE(ts_sym_type_name, 1),    
        [ts_sym__var] = REDUCE(ts_sym_type_name, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_name, 1),
    },
    
    [194] = {    
        [ts_aux_sym_token4] = SHIFT(195),
    },
    
    [195] = {    
        [ts_sym__identifier] = SHIFT(18),    
        [ts_sym_var_name] = SHIFT(28),    
        [ts_aux_sym_repeat_helper5] = SHIFT(196),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper5, 0),
    },
    
    [196] = {    
        [ts_aux_sym_token5] = SHIFT(197),
    },
    
    [197] = {    
        [ts_sym__func] = REDUCE(ts_sym_interface_type, 4),    
        [ts_sym__type] = REDUCE(ts_sym_interface_type, 4),    
        [ts_sym__var] = REDUCE(ts_sym_interface_type, 4),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_interface_type, 4),
    },
    
    [198] = {    
        [ts_aux_sym_token7] = SHIFT(199),
    },
    
    [199] = {    
        [ts_sym__identifier] = SHIFT(34),    
        [ts_sym__interface] = SHIFT(35),    
        [ts_sym__map] = SHIFT(39),    
        [ts_sym__struct] = SHIFT(41),    
        [ts_sym_interface_type] = SHIFT(52),    
        [ts_sym_map_type] = SHIFT(52),    
        [ts_sym_pointer_type] = SHIFT(52),    
        [ts_sym_slice_type] = SHIFT(52),    
        [ts_sym_struct_type] = SHIFT(52),    
        [ts_sym_type_expression] = SHIFT(200),    
        [ts_sym_type_name] = SHIFT(52),    
        [ts_aux_sym_token6] = SHIFT(66),    
        [ts_aux_sym_token7] = SHIFT(68),
    },
    
    [200] = {    
        [ts_aux_sym_token8] = SHIFT(201),
    },
    
    [201] = {    
        [ts_sym__identifier] = SHIFT(193),    
        [ts_sym__interface] = SHIFT(194),    
        [ts_sym__map] = SHIFT(198),    
        [ts_sym__struct] = SHIFT(202),    
        [ts_sym_interface_type] = SHIFT(206),    
        [ts_sym_map_type] = SHIFT(206),    
        [ts_sym_pointer_type] = SHIFT(206),    
        [ts_sym_slice_type] = SHIFT(206),    
        [ts_sym_struct_type] = SHIFT(206),    
        [ts_sym_type_expression] = SHIFT(207),    
        [ts_sym_type_name] = SHIFT(206),    
        [ts_aux_sym_token6] = SHIFT(208),    
        [ts_aux_sym_token7] = SHIFT(210),
    },
    
    [202] = {    
        [ts_aux_sym_token4] = SHIFT(203),
    },
    
    [203] = {    
        [ts_sym__identifier] = SHIFT(43),    
        [ts_sym_var_name] = SHIFT(44),    
        [ts_aux_sym_repeat_helper4] = SHIFT(204),    
        [ts_aux_sym_token5] = REDUCE(ts_aux_sym_repeat_helper4, 0),
    },
    
    [204] = {    
        [ts_aux_sym_token5] = SHIFT(205),
    },
    
    [205] = {    
        [ts_sym__func] = REDUCE(ts_sym_struct_type, 4),    
        [ts_sym__type] = REDUCE(ts_sym_struct_type, 4),    
        [ts_sym__var] = REDUCE(ts_sym_struct_type, 4),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_struct_type, 4),
    },
    
    [206] = {    
        [ts_sym__func] = REDUCE(ts_sym_type_expression, 1),    
        [ts_sym__type] = REDUCE(ts_sym_type_expression, 1),    
        [ts_sym__var] = REDUCE(ts_sym_type_expression, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_expression, 1),
    },
    
    [207] = {    
        [ts_sym__func] = REDUCE(ts_sym_map_type, 5),    
        [ts_sym__type] = REDUCE(ts_sym_map_type, 5),    
        [ts_sym__var] = REDUCE(ts_sym_map_type, 5),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_map_type, 5),
    },
    
    [208] = {    
        [ts_sym__identifier] = SHIFT(193),    
        [ts_sym__interface] = SHIFT(194),    
        [ts_sym__map] = SHIFT(198),    
        [ts_sym__struct] = SHIFT(202),    
        [ts_sym_interface_type] = SHIFT(206),    
        [ts_sym_map_type] = SHIFT(206),    
        [ts_sym_pointer_type] = SHIFT(206),    
        [ts_sym_slice_type] = SHIFT(206),    
        [ts_sym_struct_type] = SHIFT(206),    
        [ts_sym_type_expression] = SHIFT(209),    
        [ts_sym_type_name] = SHIFT(206),    
        [ts_aux_sym_token6] = SHIFT(208),    
        [ts_aux_sym_token7] = SHIFT(210),
    },
    
    [209] = {    
        [ts_sym__func] = REDUCE(ts_sym_pointer_type, 2),    
        [ts_sym__type] = REDUCE(ts_sym_pointer_type, 2),    
        [ts_sym__var] = REDUCE(ts_sym_pointer_type, 2),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_pointer_type, 2),
    },
    
    [210] = {    
        [ts_aux_sym_token8] = SHIFT(211),
    },
    
    [211] = {    
        [ts_sym__identifier] = SHIFT(193),    
        [ts_sym__interface] = SHIFT(194),    
        [ts_sym__map] = SHIFT(198),    
        [ts_sym__struct] = SHIFT(202),    
        [ts_sym_interface_type] = SHIFT(206),    
        [ts_sym_map_type] = SHIFT(206),    
        [ts_sym_pointer_type] = SHIFT(206),    
        [ts_sym_slice_type] = SHIFT(206),    
        [ts_sym_struct_type] = SHIFT(206),    
        [ts_sym_type_expression] = SHIFT(212),    
        [ts_sym_type_name] = SHIFT(206),    
        [ts_aux_sym_token6] = SHIFT(208),    
        [ts_aux_sym_token7] = SHIFT(210),
    },
    
    [212] = {    
        [ts_sym__func] = REDUCE(ts_sym_slice_type, 3),    
        [ts_sym__type] = REDUCE(ts_sym_slice_type, 3),    
        [ts_sym__var] = REDUCE(ts_sym_slice_type, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_slice_type, 3),
    },
    
    [213] = {    
        [ts_sym__func] = REDUCE(ts_sym_type_declaration, 3),    
        [ts_sym__type] = REDUCE(ts_sym_type_declaration, 3),    
        [ts_sym__var] = REDUCE(ts_sym_type_declaration, 3),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 3),
    },
    
    [214] = {    
        [ts_sym__identifier] = SHIFT(215),    
        [ts_sym_var_name] = SHIFT(216),
    },
    
    [215] = {    
        [ts_aux_sym_token3] = REDUCE(ts_sym_var_name, 1),
    },
    
    [216] = {    
        [ts_aux_sym_token3] = SHIFT(217),
    },
    
    [217] = {    
        [ts_sym_expression] = SHIFT(218),    
        [ts_sym_number] = SHIFT(219),
    },
    
    [218] = {    
        [ts_sym__func] = REDUCE(ts_sym_var_declaration, 4),    
        [ts_sym__type] = REDUCE(ts_sym_var_declaration, 4),    
        [ts_sym__var] = REDUCE(ts_sym_var_declaration, 4),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
    },
    
    [219] = {    
        [ts_sym__func] = REDUCE(ts_sym_expression, 1),    
        [ts_sym__type] = REDUCE(ts_sym_expression, 1),    
        [ts_sym__var] = REDUCE(ts_sym_expression, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_expression, 1),
    },
    
    [220] = {    
        [ts_sym__func] = SHIFT(17),    
        [ts_sym__type] = SHIFT(190),    
        [ts_sym__var] = SHIFT(214),    
        [ts_sym_declaration] = SHIFT(220),    
        [ts_sym_func_declaration] = SHIFT(221),    
        [ts_sym_type_declaration] = SHIFT(221),    
        [ts_sym_var_declaration] = SHIFT(221),    
        [ts_aux_sym_repeat_helper2] = SHIFT(222),    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper2, 0),
    },
    
    [221] = {    
        [ts_sym__func] = REDUCE(ts_sym_declaration, 1),    
        [ts_sym__type] = REDUCE(ts_sym_declaration, 1),    
        [ts_sym__var] = REDUCE(ts_sym_declaration, 1),    
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
    },
    
    [222] = {    
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_repeat_helper2, 2),
    },
    
    [223] = {    
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
    },
    
    [224] = {    
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
};

EXPORT_PARSER(ts_parser_golang);
