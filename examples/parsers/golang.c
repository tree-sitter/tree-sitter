#include "tree_sitter/parser.h"

#define STATE_COUNT 376
#define SYMBOL_COUNT 83

enum {
    ts_sym_program = ts_start_sym,
    ts_sym_package_directive,
    ts_sym_imports_block,
    ts_sym_package_import,
    ts_sym_declaration,
    ts_sym_type_declaration,
    ts_sym_var_declaration,
    ts_sym_func_declaration,
    ts_sym_block_statement,
    ts_sym_type_expression,
    ts_sym_pointer_type,
    ts_sym_map_type,
    ts_sym_slice_type,
    ts_sym_struct_type,
    ts_sym_interface_type,
    ts_sym_statement,
    ts_sym_return_statement,
    ts_sym_declaration_statement,
    ts_sym_if_statement,
    ts_sym_expression_statement,
    ts_sym_expression,
    ts_sym_call_expression,
    ts_sym_selector_expression,
    ts_sym_math_op,
    ts_sym_bool_op,
    ts_sym__func_signature,
    ts_sym_package_name,
    ts_sym_var_name,
    ts_sym_type_name,
    ts_sym__terminator,
    ts_sym_string,
    ts_sym__identifier,
    ts_sym_number,
    ts_sym_comment,
    ts_aux_sym_program_repeat0,
    ts_aux_sym_program_repeat1,
    ts_aux_sym_imports_block_repeat0,
    ts_aux_sym_block_statement_repeat0,
    ts_aux_sym_struct_type_repeat0,
    ts_aux_sym_interface_type_repeat0,
    ts_aux_sym_return_statement_repeat0,
    ts_aux_sym_declaration_statement_repeat0,
    ts_aux_sym_call_expression_repeat0,
    ts_aux_sym__func_signature_repeat0,
    ts_aux_sym__func_signature_repeat1,
    ts_aux_sym__func_signature_repeat2,
    ts_aux_sym__func_signature_repeat3,
    ts_aux_sym__func_signature_repeat4,
    ts_aux_sym_package,
    ts_aux_sym_import,
    ts_aux_sym_1,
    ts_aux_sym_2,
    ts_aux_sym_type,
    ts_aux_sym_var,
    ts_aux_sym_3,
    ts_aux_sym_func,
    ts_aux_sym_4,
    ts_aux_sym_5,
    ts_aux_sym_6,
    ts_aux_sym_map,
    ts_aux_sym_7,
    ts_aux_sym_8,
    ts_aux_sym_struct,
    ts_aux_sym_interface,
    ts_aux_sym_return,
    ts_aux_sym_9,
    ts_aux_sym_10,
    ts_aux_sym_if,
    ts_aux_sym_else,
    ts_aux_sym_11,
    ts_aux_sym_12,
    ts_aux_sym_13,
    ts_aux_sym_14,
    ts_aux_sym_15,
    ts_aux_sym_16,
    ts_aux_sym_17,
    ts_aux_sym_18,
    ts_aux_sym_19,
    ts_aux_sym_20,
    ts_aux_sym_21,
    ts_aux_sym_22,
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
    [ts_sym_block_statement] = "block_statement",
    [ts_sym_type_expression] = "type_expression",
    [ts_sym_pointer_type] = "pointer_type",
    [ts_sym_map_type] = "map_type",
    [ts_sym_slice_type] = "slice_type",
    [ts_sym_struct_type] = "struct_type",
    [ts_sym_interface_type] = "interface_type",
    [ts_sym_statement] = "statement",
    [ts_sym_return_statement] = "return_statement",
    [ts_sym_declaration_statement] = "declaration_statement",
    [ts_sym_if_statement] = "if_statement",
    [ts_sym_expression_statement] = "expression_statement",
    [ts_sym_expression] = "expression",
    [ts_sym_call_expression] = "call_expression",
    [ts_sym_selector_expression] = "selector_expression",
    [ts_sym_math_op] = "math_op",
    [ts_sym_bool_op] = "bool_op",
    [ts_sym__func_signature] = "_func_signature",
    [ts_sym_package_name] = "package_name",
    [ts_sym_var_name] = "var_name",
    [ts_sym_type_name] = "type_name",
    [ts_builtin_sym_error] = "error",
    [ts_builtin_sym_end] = "end",
    [ts_sym__terminator] = "_terminator",
    [ts_sym_string] = "string",
    [ts_sym__identifier] = "_identifier",
    [ts_sym_number] = "number",
    [ts_sym_comment] = "comment",
    [ts_aux_sym_program_repeat0] = "program_repeat0",
    [ts_aux_sym_program_repeat1] = "program_repeat1",
    [ts_aux_sym_imports_block_repeat0] = "imports_block_repeat0",
    [ts_aux_sym_block_statement_repeat0] = "block_statement_repeat0",
    [ts_aux_sym_struct_type_repeat0] = "struct_type_repeat0",
    [ts_aux_sym_interface_type_repeat0] = "interface_type_repeat0",
    [ts_aux_sym_return_statement_repeat0] = "return_statement_repeat0",
    [ts_aux_sym_declaration_statement_repeat0] = "declaration_statement_repeat0",
    [ts_aux_sym_call_expression_repeat0] = "call_expression_repeat0",
    [ts_aux_sym__func_signature_repeat0] = "_func_signature_repeat0",
    [ts_aux_sym__func_signature_repeat1] = "_func_signature_repeat1",
    [ts_aux_sym__func_signature_repeat2] = "_func_signature_repeat2",
    [ts_aux_sym__func_signature_repeat3] = "_func_signature_repeat3",
    [ts_aux_sym__func_signature_repeat4] = "_func_signature_repeat4",
    [ts_aux_sym_package] = "'package'",
    [ts_aux_sym_import] = "'import'",
    [ts_aux_sym_1] = "'('",
    [ts_aux_sym_2] = "')'",
    [ts_aux_sym_type] = "'type'",
    [ts_aux_sym_var] = "'var'",
    [ts_aux_sym_3] = "'='",
    [ts_aux_sym_func] = "'func'",
    [ts_aux_sym_4] = "'{'",
    [ts_aux_sym_5] = "'}'",
    [ts_aux_sym_6] = "'*'",
    [ts_aux_sym_map] = "'map'",
    [ts_aux_sym_7] = "'['",
    [ts_aux_sym_8] = "']'",
    [ts_aux_sym_struct] = "'struct'",
    [ts_aux_sym_interface] = "'interface'",
    [ts_aux_sym_return] = "'return'",
    [ts_aux_sym_9] = "','",
    [ts_aux_sym_10] = "':='",
    [ts_aux_sym_if] = "'if'",
    [ts_aux_sym_else] = "'else'",
    [ts_aux_sym_11] = "'.'",
    [ts_aux_sym_12] = "'/'",
    [ts_aux_sym_13] = "'+'",
    [ts_aux_sym_14] = "'-'",
    [ts_aux_sym_15] = "'||'",
    [ts_aux_sym_16] = "'&&'",
    [ts_aux_sym_17] = "'=='",
    [ts_aux_sym_18] = "'<='",
    [ts_aux_sym_19] = "'<'",
    [ts_aux_sym_20] = "'>='",
    [ts_aux_sym_21] = "'>'",
    [ts_aux_sym_22] = "'!'",
};

UBIQUITOUS_SYMBOLS = {
    [ts_sym_comment] = 1,
};

HIDDEN_SYMBOLS = {
    [ts_sym__func_signature] = 1,
    [ts_sym__terminator] = 1,
    [ts_sym__identifier] = 1,
    [ts_aux_sym_program_repeat0] = 1,
    [ts_aux_sym_program_repeat1] = 1,
    [ts_aux_sym_imports_block_repeat0] = 1,
    [ts_aux_sym_block_statement_repeat0] = 1,
    [ts_aux_sym_struct_type_repeat0] = 1,
    [ts_aux_sym_interface_type_repeat0] = 1,
    [ts_aux_sym_return_statement_repeat0] = 1,
    [ts_aux_sym_declaration_statement_repeat0] = 1,
    [ts_aux_sym_call_expression_repeat0] = 1,
    [ts_aux_sym__func_signature_repeat0] = 1,
    [ts_aux_sym__func_signature_repeat1] = 1,
    [ts_aux_sym__func_signature_repeat2] = 1,
    [ts_aux_sym__func_signature_repeat3] = 1,
    [ts_aux_sym__func_signature_repeat4] = 1,
    [ts_aux_sym_package] = 1,
    [ts_aux_sym_import] = 1,
    [ts_aux_sym_1] = 1,
    [ts_aux_sym_2] = 1,
    [ts_aux_sym_type] = 1,
    [ts_aux_sym_var] = 1,
    [ts_aux_sym_3] = 1,
    [ts_aux_sym_func] = 1,
    [ts_aux_sym_4] = 1,
    [ts_aux_sym_5] = 1,
    [ts_aux_sym_6] = 1,
    [ts_aux_sym_map] = 1,
    [ts_aux_sym_7] = 1,
    [ts_aux_sym_8] = 1,
    [ts_aux_sym_struct] = 1,
    [ts_aux_sym_interface] = 1,
    [ts_aux_sym_return] = 1,
    [ts_aux_sym_9] = 1,
    [ts_aux_sym_10] = 1,
    [ts_aux_sym_if] = 1,
    [ts_aux_sym_else] = 1,
    [ts_aux_sym_11] = 1,
    [ts_aux_sym_12] = 1,
    [ts_aux_sym_13] = 1,
    [ts_aux_sym_14] = 1,
    [ts_aux_sym_15] = 1,
    [ts_aux_sym_16] = 1,
    [ts_aux_sym_17] = 1,
    [ts_aux_sym_18] = 1,
    [ts_aux_sym_19] = 1,
    [ts_aux_sym_20] = 1,
    [ts_aux_sym_21] = 1,
    [ts_aux_sym_22] = 1,
};

LEX_FN() {
    START_LEXER();
    switch (lex_state) {
        case 1:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(1);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == 'p')
                ADVANCE(4);
            LEX_ERROR();
        case 2:
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 3:
            if (!(lookahead == '\n'))
                ADVANCE(3);
            ACCEPT_TOKEN(ts_sym_comment);
        case 4:
            if (lookahead == 'a')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (lookahead == 'c')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (lookahead == 'k')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (lookahead == 'a')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'g')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (lookahead == 'e')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            ACCEPT_TOKEN(ts_aux_sym_package);
        case 11:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(12);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 12:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 13:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(12);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(13);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == 'f')
                ADVANCE(14);
            if (lookahead == 'i')
                ADVANCE(18);
            if (lookahead == 't')
                ADVANCE(24);
            if (lookahead == 'v')
                ADVANCE(28);
            LEX_ERROR();
        case 14:
            if (lookahead == 'u')
                ADVANCE(15);
            LEX_ERROR();
        case 15:
            if (lookahead == 'n')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            if (lookahead == 'c')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            ACCEPT_TOKEN(ts_aux_sym_func);
        case 18:
            if (lookahead == 'm')
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            if (lookahead == 'p')
                ADVANCE(20);
            LEX_ERROR();
        case 20:
            if (lookahead == 'o')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if (lookahead == 'r')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            if (lookahead == 't')
                ADVANCE(23);
            LEX_ERROR();
        case 23:
            ACCEPT_TOKEN(ts_aux_sym_import);
        case 24:
            if (lookahead == 'y')
                ADVANCE(25);
            LEX_ERROR();
        case 25:
            if (lookahead == 'p')
                ADVANCE(26);
            LEX_ERROR();
        case 26:
            if (lookahead == 'e')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            ACCEPT_TOKEN(ts_aux_sym_type);
        case 28:
            if (lookahead == 'a')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            if (lookahead == 'r')
                ADVANCE(30);
            LEX_ERROR();
        case 30:
            ACCEPT_TOKEN(ts_aux_sym_var);
        case 31:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(12);
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(31);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == 'f')
                ADVANCE(14);
            if (lookahead == 't')
                ADVANCE(24);
            if (lookahead == 'v')
                ADVANCE(28);
            LEX_ERROR();
        case 32:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(32);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(2);
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
            ACCEPT_TOKEN(ts_aux_sym_1);
        case 38:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 39:
            ACCEPT_TOKEN(ts_aux_sym_2);
        case 40:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(40);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 41:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(41);
            if (lookahead == '/')
                ADVANCE(2);
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
                ADVANCE(2);
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
            ACCEPT_TOKEN(ts_aux_sym_6);
        case 45:
            ACCEPT_TOKEN(ts_aux_sym_7);
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
            ACCEPT_TOKEN(ts_aux_sym_interface);
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
            ACCEPT_TOKEN(ts_aux_sym_map);
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
            ACCEPT_TOKEN(ts_aux_sym_struct);
        case 64:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(64);
            if (lookahead == '\n')
                ADVANCE(65);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(66);
            LEX_ERROR();
        case 65:
            START_TOKEN();
            if (lookahead == '\n')
                ADVANCE(65);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 66:
            ACCEPT_TOKEN(ts_sym__terminator);
        case 67:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '[')
                ADVANCE(45);
            LEX_ERROR();
        case 68:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ']')
                ADVANCE(69);
            LEX_ERROR();
        case 69:
            ACCEPT_TOKEN(ts_aux_sym_8);
        case 70:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(70);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '{')
                ADVANCE(71);
            LEX_ERROR();
        case 71:
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 72:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(72);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '}')
                ADVANCE(73);
            LEX_ERROR();
        case 73:
            ACCEPT_TOKEN(ts_aux_sym_5);
        case 74:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(74);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(73);
            LEX_ERROR();
        case 75:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 76:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            LEX_ERROR();
        case 77:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '/')
                ADVANCE(2);
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
        case 78:
            ACCEPT_TOKEN(ts_aux_sym_9);
        case 79:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 80:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '}')
                ADVANCE(73);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            LEX_ERROR();
        case 82:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == '=')
                ADVANCE(83);
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
        case 83:
            ACCEPT_TOKEN(ts_aux_sym_3);
        case 84:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(84);
            if (lookahead == '\n')
                ADVANCE(85);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '=')
                ADVANCE(83);
            LEX_ERROR();
        case 85:
            START_TOKEN();
            if (lookahead == '\n')
                ADVANCE(85);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '=')
                ADVANCE(83);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 86:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(86);
            if (lookahead == '!')
                ADVANCE(87);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            LEX_ERROR();
        case 87:
            ACCEPT_TOKEN(ts_aux_sym_22);
        case 88:
            if (lookahead == '.')
                ADVANCE(89);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            ACCEPT_TOKEN(ts_sym_number);
        case 89:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(90);
            LEX_ERROR();
        case 90:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(90);
            ACCEPT_TOKEN(ts_sym_number);
        case 91:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(91);
            if (lookahead == '\n')
                ADVANCE(92);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(103);
            if (lookahead == '|')
                ADVANCE(105);
            LEX_ERROR();
        case 92:
            START_TOKEN();
            if (lookahead == '\n')
                ADVANCE(92);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(103);
            if (lookahead == '|')
                ADVANCE(105);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 93:
            if (lookahead == '&')
                ADVANCE(94);
            LEX_ERROR();
        case 94:
            ACCEPT_TOKEN(ts_aux_sym_16);
        case 95:
            ACCEPT_TOKEN(ts_aux_sym_13);
        case 96:
            ACCEPT_TOKEN(ts_aux_sym_14);
        case 97:
            ACCEPT_TOKEN(ts_aux_sym_11);
        case 98:
            if (lookahead == '/')
                ADVANCE(3);
            ACCEPT_TOKEN(ts_aux_sym_12);
        case 99:
            if (lookahead == '=')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_aux_sym_19);
        case 100:
            ACCEPT_TOKEN(ts_aux_sym_18);
        case 101:
            if (lookahead == '=')
                ADVANCE(102);
            LEX_ERROR();
        case 102:
            ACCEPT_TOKEN(ts_aux_sym_17);
        case 103:
            if (lookahead == '=')
                ADVANCE(104);
            ACCEPT_TOKEN(ts_aux_sym_21);
        case 104:
            ACCEPT_TOKEN(ts_aux_sym_20);
        case 105:
            if (lookahead == '|')
                ADVANCE(106);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(ts_aux_sym_15);
        case 107:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '!')
                ADVANCE(87);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(103);
            if (lookahead == '|')
                ADVANCE(105);
            LEX_ERROR();
        case 109:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == '!')
                ADVANCE(87);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            if (lookahead == ':')
                ADVANCE(110);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'i')
                ADVANCE(112);
            if (lookahead == 'r')
                ADVANCE(114);
            if (lookahead == 'v')
                ADVANCE(120);
            if (lookahead == '}')
                ADVANCE(73);
            LEX_ERROR();
        case 110:
            if (lookahead == '=')
                ADVANCE(111);
            LEX_ERROR();
        case 111:
            ACCEPT_TOKEN(ts_aux_sym_10);
        case 112:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'f')
                ADVANCE(113);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 113:
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 114:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'e')
                ADVANCE(115);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 115:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 't')
                ADVANCE(116);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 116:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'u')
                ADVANCE(117);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 117:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'r')
                ADVANCE(118);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 118:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(119);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 119:
            ACCEPT_TOKEN(ts_aux_sym_return);
        case 120:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'a')
                ADVANCE(121);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 121:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'r')
                ADVANCE(122);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 122:
            ACCEPT_TOKEN(ts_aux_sym_var);
        case 123:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(123);
            if (lookahead == '\n')
                ADVANCE(124);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if (lookahead == ':')
                ADVANCE(110);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(103);
            if (lookahead == '|')
                ADVANCE(105);
            LEX_ERROR();
        case 124:
            START_TOKEN();
            if (lookahead == '\n')
                ADVANCE(124);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if (lookahead == ':')
                ADVANCE(110);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(103);
            if (lookahead == '|')
                ADVANCE(105);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 125:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ':')
                ADVANCE(110);
            LEX_ERROR();
        case 126:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
            if (lookahead == '!')
                ADVANCE(87);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            if (lookahead == ':')
                ADVANCE(110);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(103);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'i')
                ADVANCE(112);
            if (lookahead == 'r')
                ADVANCE(114);
            if (lookahead == 'v')
                ADVANCE(120);
            if (lookahead == '|')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(73);
            LEX_ERROR();
        case 127:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == ':')
                ADVANCE(110);
            LEX_ERROR();
        case 128:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '!')
                ADVANCE(87);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            if (lookahead == ':')
                ADVANCE(110);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(103);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'i')
                ADVANCE(112);
            if (lookahead == 'r')
                ADVANCE(114);
            if (lookahead == 'v')
                ADVANCE(120);
            if (lookahead == '|')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(73);
            LEX_ERROR();
        case 129:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(103);
            if (lookahead == '{')
                ADVANCE(71);
            if (lookahead == '|')
                ADVANCE(105);
            LEX_ERROR();
        case 130:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
            if (lookahead == '!')
                ADVANCE(87);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == '/')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            if (lookahead == ':')
                ADVANCE(110);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'e')
                ADVANCE(131);
            if (lookahead == 'i')
                ADVANCE(112);
            if (lookahead == 'r')
                ADVANCE(114);
            if (lookahead == 'v')
                ADVANCE(120);
            if (lookahead == '}')
                ADVANCE(73);
            LEX_ERROR();
        case 131:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'l')
                ADVANCE(132);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 132:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 's')
                ADVANCE(133);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 133:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'e')
                ADVANCE(134);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 134:
            ACCEPT_TOKEN(ts_aux_sym_else);
        case 135:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(2);
            if (lookahead == 'i')
                ADVANCE(136);
            if (lookahead == '{')
                ADVANCE(71);
            LEX_ERROR();
        case 136:
            if (lookahead == 'f')
                ADVANCE(137);
            LEX_ERROR();
        case 137:
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 138:
            START_TOKEN();
            if (('\t' <= lookahead && lookahead <= '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(2);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '{')
                ADVANCE(71);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(12);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\n')
                ADVANCE(140);
            if (lookahead == '!')
                ADVANCE(87);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            if (lookahead == ':')
                ADVANCE(110);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(141);
            if (lookahead == '>')
                ADVANCE(103);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                (lookahead == 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '[')
                ADVANCE(45);
            if (lookahead == ']')
                ADVANCE(69);
            if (lookahead == 'e')
                ADVANCE(131);
            if (lookahead == 'f')
                ADVANCE(142);
            if (lookahead == 'i')
                ADVANCE(146);
            if (lookahead == 'm')
                ADVANCE(55);
            if (lookahead == 'p')
                ADVANCE(152);
            if (lookahead == 'r')
                ADVANCE(114);
            if (lookahead == 's')
                ADVANCE(58);
            if (lookahead == 't')
                ADVANCE(159);
            if (lookahead == 'v')
                ADVANCE(120);
            if (lookahead == '{')
                ADVANCE(71);
            if (lookahead == '|')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(73);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(12);
            if (lookahead == '\n')
                ADVANCE(140);
            if (lookahead == '!')
                ADVANCE(87);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            if (lookahead == ':')
                ADVANCE(110);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(141);
            if (lookahead == '>')
                ADVANCE(103);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                (lookahead == 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '[')
                ADVANCE(45);
            if (lookahead == ']')
                ADVANCE(69);
            if (lookahead == 'e')
                ADVANCE(131);
            if (lookahead == 'f')
                ADVANCE(142);
            if (lookahead == 'i')
                ADVANCE(146);
            if (lookahead == 'm')
                ADVANCE(55);
            if (lookahead == 'p')
                ADVANCE(152);
            if (lookahead == 'r')
                ADVANCE(114);
            if (lookahead == 's')
                ADVANCE(58);
            if (lookahead == 't')
                ADVANCE(159);
            if (lookahead == 'v')
                ADVANCE(120);
            if (lookahead == '{')
                ADVANCE(71);
            if (lookahead == '|')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(73);
            ACCEPT_TOKEN(ts_sym__terminator);
        case 141:
            if (lookahead == '=')
                ADVANCE(102);
            ACCEPT_TOKEN(ts_aux_sym_3);
        case 142:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'u')
                ADVANCE(143);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 143:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'n')
                ADVANCE(144);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 144:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'c')
                ADVANCE(145);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 145:
            ACCEPT_TOKEN(ts_aux_sym_func);
        case 146:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'f')
                ADVANCE(113);
            if (lookahead == 'm')
                ADVANCE(147);
            if (lookahead == 'n')
                ADVANCE(47);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 147:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'p')
                ADVANCE(148);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 148:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'o')
                ADVANCE(149);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 149:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'r')
                ADVANCE(150);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 150:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 't')
                ADVANCE(151);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 151:
            ACCEPT_TOKEN(ts_aux_sym_import);
        case 152:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'a')
                ADVANCE(153);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 153:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'c')
                ADVANCE(154);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 154:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'k')
                ADVANCE(155);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 155:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'a')
                ADVANCE(156);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 156:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'g')
                ADVANCE(157);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 157:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'e')
                ADVANCE(158);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 158:
            ACCEPT_TOKEN(ts_aux_sym_package);
        case 159:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(42);
            if (lookahead == 'y')
                ADVANCE(160);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 160:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'p')
                ADVANCE(161);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 161:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == 'e')
                ADVANCE(162);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 162:
            ACCEPT_TOKEN(ts_aux_sym_type);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(12);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\n')
                ADVANCE(140);
            if (lookahead == '!')
                ADVANCE(87);
            if (lookahead == '\"')
                ADVANCE(33);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(37);
            if (lookahead == ')')
                ADVANCE(39);
            if (lookahead == '*')
                ADVANCE(44);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(78);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            if (lookahead == ':')
                ADVANCE(110);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(141);
            if (lookahead == '>')
                ADVANCE(103);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'o') ||
                (lookahead == 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(42);
            if (lookahead == '[')
                ADVANCE(45);
            if (lookahead == ']')
                ADVANCE(69);
            if (lookahead == 'e')
                ADVANCE(131);
            if (lookahead == 'f')
                ADVANCE(142);
            if (lookahead == 'i')
                ADVANCE(146);
            if (lookahead == 'm')
                ADVANCE(55);
            if (lookahead == 'p')
                ADVANCE(152);
            if (lookahead == 'r')
                ADVANCE(114);
            if (lookahead == 's')
                ADVANCE(58);
            if (lookahead == 't')
                ADVANCE(159);
            if (lookahead == 'v')
                ADVANCE(120);
            if (lookahead == '{')
                ADVANCE(71);
            if (lookahead == '|')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(73);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 1,
    [1] = 11,
    [2] = 13,
    [3] = 13,
    [4] = 31,
    [5] = 32,
    [6] = 13,
    [7] = 13,
    [8] = 38,
    [9] = 38,
    [10] = 38,
    [11] = 40,
    [12] = 40,
    [13] = 13,
    [14] = 31,
    [15] = 31,
    [16] = 31,
    [17] = 11,
    [18] = 41,
    [19] = 43,
    [20] = 64,
    [21] = 31,
    [22] = 64,
    [23] = 64,
    [24] = 43,
    [25] = 64,
    [26] = 67,
    [27] = 43,
    [28] = 68,
    [29] = 43,
    [30] = 64,
    [31] = 68,
    [32] = 43,
    [33] = 64,
    [34] = 70,
    [35] = 72,
    [36] = 43,
    [37] = 72,
    [38] = 43,
    [39] = 74,
    [40] = 72,
    [41] = 72,
    [42] = 43,
    [43] = 72,
    [44] = 67,
    [45] = 43,
    [46] = 68,
    [47] = 43,
    [48] = 72,
    [49] = 68,
    [50] = 43,
    [51] = 72,
    [52] = 70,
    [53] = 72,
    [54] = 74,
    [55] = 72,
    [56] = 70,
    [57] = 72,
    [58] = 75,
    [59] = 72,
    [60] = 75,
    [61] = 74,
    [62] = 76,
    [63] = 77,
    [64] = 43,
    [65] = 79,
    [66] = 40,
    [67] = 80,
    [68] = 72,
    [69] = 41,
    [70] = 41,
    [71] = 79,
    [72] = 40,
    [73] = 72,
    [74] = 41,
    [75] = 41,
    [76] = 79,
    [77] = 40,
    [78] = 79,
    [79] = 41,
    [80] = 79,
    [81] = 40,
    [82] = 72,
    [83] = 41,
    [84] = 79,
    [85] = 40,
    [86] = 81,
    [87] = 41,
    [88] = 77,
    [89] = 43,
    [90] = 79,
    [91] = 40,
    [92] = 79,
    [93] = 43,
    [94] = 79,
    [95] = 67,
    [96] = 43,
    [97] = 68,
    [98] = 43,
    [99] = 79,
    [100] = 68,
    [101] = 43,
    [102] = 79,
    [103] = 70,
    [104] = 72,
    [105] = 74,
    [106] = 79,
    [107] = 70,
    [108] = 72,
    [109] = 74,
    [110] = 79,
    [111] = 68,
    [112] = 68,
    [113] = 43,
    [114] = 68,
    [115] = 67,
    [116] = 43,
    [117] = 68,
    [118] = 43,
    [119] = 68,
    [120] = 68,
    [121] = 43,
    [122] = 68,
    [123] = 70,
    [124] = 72,
    [125] = 74,
    [126] = 68,
    [127] = 70,
    [128] = 72,
    [129] = 74,
    [130] = 68,
    [131] = 41,
    [132] = 77,
    [133] = 43,
    [134] = 77,
    [135] = 41,
    [136] = 77,
    [137] = 43,
    [138] = 80,
    [139] = 72,
    [140] = 41,
    [141] = 41,
    [142] = 79,
    [143] = 40,
    [144] = 79,
    [145] = 40,
    [146] = 72,
    [147] = 74,
    [148] = 72,
    [149] = 74,
    [150] = 64,
    [151] = 70,
    [152] = 72,
    [153] = 74,
    [154] = 64,
    [155] = 43,
    [156] = 41,
    [157] = 82,
    [158] = 84,
    [159] = 31,
    [160] = 86,
    [161] = 91,
    [162] = 31,
    [163] = 107,
    [164] = 108,
    [165] = 40,
    [166] = 91,
    [167] = 107,
    [168] = 108,
    [169] = 40,
    [170] = 108,
    [171] = 86,
    [172] = 108,
    [173] = 41,
    [174] = 108,
    [175] = 108,
    [176] = 86,
    [177] = 108,
    [178] = 86,
    [179] = 108,
    [180] = 86,
    [181] = 108,
    [182] = 86,
    [183] = 108,
    [184] = 108,
    [185] = 86,
    [186] = 108,
    [187] = 86,
    [188] = 108,
    [189] = 40,
    [190] = 108,
    [191] = 91,
    [192] = 86,
    [193] = 91,
    [194] = 41,
    [195] = 91,
    [196] = 91,
    [197] = 86,
    [198] = 91,
    [199] = 86,
    [200] = 91,
    [201] = 86,
    [202] = 91,
    [203] = 86,
    [204] = 91,
    [205] = 91,
    [206] = 86,
    [207] = 91,
    [208] = 84,
    [209] = 84,
    [210] = 86,
    [211] = 91,
    [212] = 31,
    [213] = 43,
    [214] = 84,
    [215] = 67,
    [216] = 43,
    [217] = 68,
    [218] = 43,
    [219] = 84,
    [220] = 68,
    [221] = 43,
    [222] = 84,
    [223] = 70,
    [224] = 72,
    [225] = 74,
    [226] = 84,
    [227] = 70,
    [228] = 72,
    [229] = 74,
    [230] = 84,
    [231] = 82,
    [232] = 41,
    [233] = 75,
    [234] = 70,
    [235] = 64,
    [236] = 31,
    [237] = 109,
    [238] = 109,
    [239] = 109,
    [240] = 109,
    [241] = 91,
    [242] = 109,
    [243] = 123,
    [244] = 125,
    [245] = 86,
    [246] = 126,
    [247] = 107,
    [248] = 108,
    [249] = 40,
    [250] = 126,
    [251] = 126,
    [252] = 86,
    [253] = 126,
    [254] = 41,
    [255] = 126,
    [256] = 126,
    [257] = 86,
    [258] = 126,
    [259] = 86,
    [260] = 126,
    [261] = 86,
    [262] = 126,
    [263] = 86,
    [264] = 126,
    [265] = 126,
    [266] = 86,
    [267] = 126,
    [268] = 41,
    [269] = 127,
    [270] = 125,
    [271] = 127,
    [272] = 123,
    [273] = 74,
    [274] = 41,
    [275] = 82,
    [276] = 84,
    [277] = 109,
    [278] = 86,
    [279] = 91,
    [280] = 109,
    [281] = 86,
    [282] = 91,
    [283] = 109,
    [284] = 109,
    [285] = 128,
    [286] = 109,
    [287] = 107,
    [288] = 108,
    [289] = 40,
    [290] = 128,
    [291] = 128,
    [292] = 86,
    [293] = 128,
    [294] = 41,
    [295] = 128,
    [296] = 128,
    [297] = 86,
    [298] = 128,
    [299] = 86,
    [300] = 128,
    [301] = 86,
    [302] = 128,
    [303] = 86,
    [304] = 128,
    [305] = 128,
    [306] = 86,
    [307] = 128,
    [308] = 86,
    [309] = 128,
    [310] = 109,
    [311] = 86,
    [312] = 126,
    [313] = 86,
    [314] = 129,
    [315] = 130,
    [316] = 135,
    [317] = 109,
    [318] = 109,
    [319] = 74,
    [320] = 109,
    [321] = 107,
    [322] = 108,
    [323] = 40,
    [324] = 129,
    [325] = 129,
    [326] = 109,
    [327] = 74,
    [328] = 130,
    [329] = 86,
    [330] = 129,
    [331] = 41,
    [332] = 129,
    [333] = 129,
    [334] = 86,
    [335] = 129,
    [336] = 86,
    [337] = 129,
    [338] = 86,
    [339] = 129,
    [340] = 86,
    [341] = 129,
    [342] = 129,
    [343] = 86,
    [344] = 129,
    [345] = 74,
    [346] = 64,
    [347] = 76,
    [348] = 77,
    [349] = 43,
    [350] = 79,
    [351] = 40,
    [352] = 138,
    [353] = 70,
    [354] = 70,
    [355] = 41,
    [356] = 41,
    [357] = 79,
    [358] = 40,
    [359] = 70,
    [360] = 79,
    [361] = 40,
    [362] = 70,
    [363] = 138,
    [364] = 70,
    [365] = 41,
    [366] = 41,
    [367] = 79,
    [368] = 40,
    [369] = 79,
    [370] = 40,
    [371] = 70,
    [372] = 11,
    [373] = 41,
    [374] = 13,
    [375] = 13,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_program] = SHIFT(1),
        [ts_sym_package_directive] = SHIFT(2),
        [ts_sym_comment] = SHIFT(0),
        [ts_aux_sym_package] = SHIFT(373),
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
        [ts_aux_sym_import] = SHIFT(5),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [3] = {
        [ts_sym_imports_block] = SHIFT(3),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym_comment] = SHIFT(3),
        [ts_aux_sym_program_repeat0] = SHIFT(4),
        [ts_aux_sym_import] = SHIFT(5),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [4] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym_comment] = SHIFT(4),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [5] = {
        [ts_sym_package_import] = SHIFT(6),
        [ts_sym_string] = SHIFT(7),
        [ts_sym_comment] = SHIFT(5),
        [ts_aux_sym_1] = SHIFT(8),
    },
    [6] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym_comment] = SHIFT(6),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 2),
    },
    [7] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_comment] = SHIFT(7),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_import, 1),
    },
    [8] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_builtin_sym_error] = SHIFT(12),
        [ts_sym_string] = SHIFT(10),
        [ts_sym_comment] = SHIFT(8),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(12),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [9] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_sym_string] = SHIFT(10),
        [ts_sym_comment] = SHIFT(9),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(11),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [10] = {
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_comment] = SHIFT(10),
        [ts_aux_sym_2] = REDUCE(ts_sym_package_import, 1),
    },
    [11] = {
        [ts_sym_comment] = SHIFT(11),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 2),
    },
    [12] = {
        [ts_sym_comment] = SHIFT(12),
        [ts_aux_sym_2] = SHIFT(13),
    },
    [13] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym_comment] = SHIFT(13),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 4),
    },
    [14] = {
        [ts_sym_declaration] = SHIFT(15),
        [ts_sym_type_declaration] = SHIFT(16),
        [ts_sym_var_declaration] = SHIFT(16),
        [ts_sym_func_declaration] = SHIFT(16),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym_comment] = SHIFT(14),
        [ts_aux_sym_program_repeat1] = SHIFT(372),
        [ts_aux_sym_type] = SHIFT(18),
        [ts_aux_sym_var] = SHIFT(156),
        [ts_aux_sym_func] = SHIFT(232),
    },
    [15] = {
        [ts_sym_declaration] = SHIFT(15),
        [ts_sym_type_declaration] = SHIFT(16),
        [ts_sym_var_declaration] = SHIFT(16),
        [ts_sym_func_declaration] = SHIFT(16),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym_comment] = SHIFT(15),
        [ts_aux_sym_program_repeat1] = SHIFT(17),
        [ts_aux_sym_type] = SHIFT(18),
        [ts_aux_sym_var] = SHIFT(156),
        [ts_aux_sym_func] = SHIFT(232),
    },
    [16] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_sym_comment] = SHIFT(16),
        [ts_aux_sym_type] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_declaration, 1),
    },
    [17] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_sym_comment] = SHIFT(17),
    },
    [18] = {
        [ts_sym_type_name] = SHIFT(19),
        [ts_sym__identifier] = SHIFT(155),
        [ts_sym_comment] = SHIFT(18),
    },
    [19] = {
        [ts_sym_type_expression] = SHIFT(20),
        [ts_sym_pointer_type] = SHIFT(22),
        [ts_sym_map_type] = SHIFT(22),
        [ts_sym_slice_type] = SHIFT(22),
        [ts_sym_struct_type] = SHIFT(22),
        [ts_sym_interface_type] = SHIFT(22),
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT(19),
        [ts_aux_sym_6] = SHIFT(24),
        [ts_aux_sym_map] = SHIFT(26),
        [ts_aux_sym_7] = SHIFT(31),
        [ts_aux_sym_struct] = SHIFT(34),
        [ts_aux_sym_interface] = SHIFT(151),
    },
    [20] = {
        [ts_sym__terminator] = SHIFT(21),
        [ts_sym_comment] = SHIFT(20),
    },
    [21] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 4),
        [ts_sym_comment] = SHIFT(21),
        [ts_aux_sym_type] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_var] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_type_declaration, 4),
    },
    [22] = {
        [ts_sym__terminator] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT(22),
    },
    [23] = {
        [ts_sym__terminator] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT(23),
    },
    [24] = {
        [ts_sym_type_expression] = SHIFT(25),
        [ts_sym_pointer_type] = SHIFT(22),
        [ts_sym_map_type] = SHIFT(22),
        [ts_sym_slice_type] = SHIFT(22),
        [ts_sym_struct_type] = SHIFT(22),
        [ts_sym_interface_type] = SHIFT(22),
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT(24),
        [ts_aux_sym_6] = SHIFT(24),
        [ts_aux_sym_map] = SHIFT(26),
        [ts_aux_sym_7] = SHIFT(31),
        [ts_aux_sym_struct] = SHIFT(34),
        [ts_aux_sym_interface] = SHIFT(151),
    },
    [25] = {
        [ts_sym__terminator] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT(25),
    },
    [26] = {
        [ts_sym_comment] = SHIFT(26),
        [ts_aux_sym_7] = SHIFT(27),
    },
    [27] = {
        [ts_sym_type_expression] = SHIFT(28),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT(27),
        [ts_aux_sym_6] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_7] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [28] = {
        [ts_sym_comment] = SHIFT(28),
        [ts_aux_sym_8] = SHIFT(29),
    },
    [29] = {
        [ts_sym_type_expression] = SHIFT(30),
        [ts_sym_pointer_type] = SHIFT(22),
        [ts_sym_map_type] = SHIFT(22),
        [ts_sym_slice_type] = SHIFT(22),
        [ts_sym_struct_type] = SHIFT(22),
        [ts_sym_interface_type] = SHIFT(22),
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT(29),
        [ts_aux_sym_6] = SHIFT(24),
        [ts_aux_sym_map] = SHIFT(26),
        [ts_aux_sym_7] = SHIFT(31),
        [ts_aux_sym_struct] = SHIFT(34),
        [ts_aux_sym_interface] = SHIFT(151),
    },
    [30] = {
        [ts_sym__terminator] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT(30),
    },
    [31] = {
        [ts_sym_comment] = SHIFT(31),
        [ts_aux_sym_8] = SHIFT(32),
    },
    [32] = {
        [ts_sym_type_expression] = SHIFT(33),
        [ts_sym_pointer_type] = SHIFT(22),
        [ts_sym_map_type] = SHIFT(22),
        [ts_sym_slice_type] = SHIFT(22),
        [ts_sym_struct_type] = SHIFT(22),
        [ts_sym_interface_type] = SHIFT(22),
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT(32),
        [ts_aux_sym_6] = SHIFT(24),
        [ts_aux_sym_map] = SHIFT(26),
        [ts_aux_sym_7] = SHIFT(31),
        [ts_aux_sym_struct] = SHIFT(34),
        [ts_aux_sym_interface] = SHIFT(151),
    },
    [33] = {
        [ts_sym__terminator] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT(33),
    },
    [34] = {
        [ts_sym_comment] = SHIFT(34),
        [ts_aux_sym_4] = SHIFT(35),
    },
    [35] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT(35),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(149),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [36] = {
        [ts_sym_type_expression] = SHIFT(37),
        [ts_sym_pointer_type] = SHIFT(40),
        [ts_sym_map_type] = SHIFT(40),
        [ts_sym_slice_type] = SHIFT(40),
        [ts_sym_struct_type] = SHIFT(40),
        [ts_sym_interface_type] = SHIFT(40),
        [ts_sym_type_name] = SHIFT(40),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT(36),
        [ts_aux_sym_6] = SHIFT(42),
        [ts_aux_sym_map] = SHIFT(44),
        [ts_aux_sym_7] = SHIFT(49),
        [ts_aux_sym_struct] = SHIFT(52),
        [ts_aux_sym_interface] = SHIFT(56),
    },
    [37] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT(37),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(39),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [38] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(38),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
    },
    [39] = {
        [ts_sym_comment] = SHIFT(39),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_struct_type_repeat0, 3),
    },
    [40] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT(40),
        [ts_aux_sym_5] = REDUCE(ts_sym_type_expression, 1),
    },
    [41] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT(41),
        [ts_aux_sym_5] = REDUCE(ts_sym_type_name, 1),
    },
    [42] = {
        [ts_sym_type_expression] = SHIFT(43),
        [ts_sym_pointer_type] = SHIFT(40),
        [ts_sym_map_type] = SHIFT(40),
        [ts_sym_slice_type] = SHIFT(40),
        [ts_sym_struct_type] = SHIFT(40),
        [ts_sym_interface_type] = SHIFT(40),
        [ts_sym_type_name] = SHIFT(40),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT(42),
        [ts_aux_sym_6] = SHIFT(42),
        [ts_aux_sym_map] = SHIFT(44),
        [ts_aux_sym_7] = SHIFT(49),
        [ts_aux_sym_struct] = SHIFT(52),
        [ts_aux_sym_interface] = SHIFT(56),
    },
    [43] = {
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT(43),
        [ts_aux_sym_5] = REDUCE(ts_sym_pointer_type, 2),
    },
    [44] = {
        [ts_sym_comment] = SHIFT(44),
        [ts_aux_sym_7] = SHIFT(45),
    },
    [45] = {
        [ts_sym_type_expression] = SHIFT(46),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT(45),
        [ts_aux_sym_6] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_7] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [46] = {
        [ts_sym_comment] = SHIFT(46),
        [ts_aux_sym_8] = SHIFT(47),
    },
    [47] = {
        [ts_sym_type_expression] = SHIFT(48),
        [ts_sym_pointer_type] = SHIFT(40),
        [ts_sym_map_type] = SHIFT(40),
        [ts_sym_slice_type] = SHIFT(40),
        [ts_sym_struct_type] = SHIFT(40),
        [ts_sym_interface_type] = SHIFT(40),
        [ts_sym_type_name] = SHIFT(40),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT(47),
        [ts_aux_sym_6] = SHIFT(42),
        [ts_aux_sym_map] = SHIFT(44),
        [ts_aux_sym_7] = SHIFT(49),
        [ts_aux_sym_struct] = SHIFT(52),
        [ts_aux_sym_interface] = SHIFT(56),
    },
    [48] = {
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT(48),
        [ts_aux_sym_5] = REDUCE(ts_sym_map_type, 5),
    },
    [49] = {
        [ts_sym_comment] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
    },
    [50] = {
        [ts_sym_type_expression] = SHIFT(51),
        [ts_sym_pointer_type] = SHIFT(40),
        [ts_sym_map_type] = SHIFT(40),
        [ts_sym_slice_type] = SHIFT(40),
        [ts_sym_struct_type] = SHIFT(40),
        [ts_sym_interface_type] = SHIFT(40),
        [ts_sym_type_name] = SHIFT(40),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT(50),
        [ts_aux_sym_6] = SHIFT(42),
        [ts_aux_sym_map] = SHIFT(44),
        [ts_aux_sym_7] = SHIFT(49),
        [ts_aux_sym_struct] = SHIFT(52),
        [ts_aux_sym_interface] = SHIFT(56),
    },
    [51] = {
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT(51),
        [ts_aux_sym_5] = REDUCE(ts_sym_slice_type, 3),
    },
    [52] = {
        [ts_sym_comment] = SHIFT(52),
        [ts_aux_sym_4] = SHIFT(53),
    },
    [53] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT(53),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(54),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [54] = {
        [ts_sym_comment] = SHIFT(54),
        [ts_aux_sym_5] = SHIFT(55),
    },
    [55] = {
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT(55),
        [ts_aux_sym_5] = REDUCE(ts_sym_struct_type, 4),
    },
    [56] = {
        [ts_sym_comment] = SHIFT(56),
        [ts_aux_sym_4] = SHIFT(57),
    },
    [57] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT(57),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(147),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [58] = {
        [ts_sym__func_signature] = SHIFT(59),
        [ts_sym_comment] = SHIFT(58),
        [ts_aux_sym_1] = SHIFT(62),
    },
    [59] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT(59),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(61),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [60] = {
        [ts_sym_comment] = SHIFT(60),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
    },
    [61] = {
        [ts_sym_comment] = SHIFT(61),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [62] = {
        [ts_sym_var_name] = SHIFT(63),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT(62),
        [ts_aux_sym_2] = SHIFT(138),
    },
    [63] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT(63),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(64),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_9] = SHIFT(135),
    },
    [64] = {
        [ts_sym_type_expression] = SHIFT(65),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(64),
        [ts_aux_sym_6] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_7] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [65] = {
        [ts_sym_comment] = SHIFT(65),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(66),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_9] = SHIFT(87),
    },
    [66] = {
        [ts_sym_comment] = SHIFT(66),
        [ts_aux_sym_2] = SHIFT(67),
    },
    [67] = {
        [ts_sym_type_name] = SHIFT(68),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT(67),
        [ts_aux_sym_1] = SHIFT(69),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [68] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_sym_comment] = SHIFT(68),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 7),
    },
    [69] = {
        [ts_sym_var_name] = SHIFT(70),
        [ts_sym_type_name] = SHIFT(80),
        [ts_sym__identifier] = SHIFT(86),
        [ts_sym_comment] = SHIFT(69),
    },
    [70] = {
        [ts_sym_type_name] = SHIFT(71),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(70),
    },
    [71] = {
        [ts_sym_comment] = SHIFT(71),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(72),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_9] = SHIFT(74),
    },
    [72] = {
        [ts_sym_comment] = SHIFT(72),
        [ts_aux_sym_2] = SHIFT(73),
    },
    [73] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_sym_comment] = SHIFT(73),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 11),
    },
    [74] = {
        [ts_sym_var_name] = SHIFT(75),
        [ts_sym__identifier] = SHIFT(79),
        [ts_sym_comment] = SHIFT(74),
    },
    [75] = {
        [ts_sym_type_name] = SHIFT(76),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(75),
    },
    [76] = {
        [ts_sym_comment] = SHIFT(76),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(77),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_9] = SHIFT(74),
    },
    [77] = {
        [ts_sym_comment] = SHIFT(77),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [78] = {
        [ts_sym_comment] = SHIFT(78),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_name, 1),
    },
    [79] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(79),
    },
    [80] = {
        [ts_sym_comment] = SHIFT(80),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(81),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_9] = SHIFT(83),
    },
    [81] = {
        [ts_sym_comment] = SHIFT(81),
        [ts_aux_sym_2] = SHIFT(82),
    },
    [82] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_sym_comment] = SHIFT(82),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 10),
    },
    [83] = {
        [ts_sym_type_name] = SHIFT(84),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(83),
    },
    [84] = {
        [ts_sym_comment] = SHIFT(84),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(85),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_9] = SHIFT(83),
    },
    [85] = {
        [ts_sym_comment] = SHIFT(85),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [86] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(86),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_name, 1),
    },
    [87] = {
        [ts_sym_var_name] = SHIFT(88),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT(87),
    },
    [88] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym_comment] = SHIFT(88),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(89),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_9] = SHIFT(131),
    },
    [89] = {
        [ts_sym_type_expression] = SHIFT(90),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(89),
        [ts_aux_sym_6] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_7] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [90] = {
        [ts_sym_comment] = SHIFT(90),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(91),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_9] = SHIFT(87),
    },
    [91] = {
        [ts_sym_comment] = SHIFT(91),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [92] = {
        [ts_sym_comment] = SHIFT(92),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_expression, 1),
    },
    [93] = {
        [ts_sym_type_expression] = SHIFT(94),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(93),
        [ts_aux_sym_6] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_7] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [94] = {
        [ts_sym_comment] = SHIFT(94),
        [ts_aux_sym_2] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_9] = REDUCE(ts_sym_pointer_type, 2),
    },
    [95] = {
        [ts_sym_comment] = SHIFT(95),
        [ts_aux_sym_7] = SHIFT(96),
    },
    [96] = {
        [ts_sym_type_expression] = SHIFT(97),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT(96),
        [ts_aux_sym_6] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_7] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [97] = {
        [ts_sym_comment] = SHIFT(97),
        [ts_aux_sym_8] = SHIFT(98),
    },
    [98] = {
        [ts_sym_type_expression] = SHIFT(99),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(98),
        [ts_aux_sym_6] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_7] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [99] = {
        [ts_sym_comment] = SHIFT(99),
        [ts_aux_sym_2] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_9] = REDUCE(ts_sym_map_type, 5),
    },
    [100] = {
        [ts_sym_comment] = SHIFT(100),
        [ts_aux_sym_8] = SHIFT(101),
    },
    [101] = {
        [ts_sym_type_expression] = SHIFT(102),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(101),
        [ts_aux_sym_6] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_7] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [102] = {
        [ts_sym_comment] = SHIFT(102),
        [ts_aux_sym_2] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_slice_type, 3),
    },
    [103] = {
        [ts_sym_comment] = SHIFT(103),
        [ts_aux_sym_4] = SHIFT(104),
    },
    [104] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT(104),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(105),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [105] = {
        [ts_sym_comment] = SHIFT(105),
        [ts_aux_sym_5] = SHIFT(106),
    },
    [106] = {
        [ts_sym_comment] = SHIFT(106),
        [ts_aux_sym_2] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_9] = REDUCE(ts_sym_struct_type, 4),
    },
    [107] = {
        [ts_sym_comment] = SHIFT(107),
        [ts_aux_sym_4] = SHIFT(108),
    },
    [108] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT(108),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(109),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [109] = {
        [ts_sym_comment] = SHIFT(109),
        [ts_aux_sym_5] = SHIFT(110),
    },
    [110] = {
        [ts_sym_comment] = SHIFT(110),
        [ts_aux_sym_2] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_9] = REDUCE(ts_sym_interface_type, 4),
    },
    [111] = {
        [ts_sym_comment] = SHIFT(111),
        [ts_aux_sym_8] = REDUCE(ts_sym_type_expression, 1),
    },
    [112] = {
        [ts_sym_comment] = SHIFT(112),
        [ts_aux_sym_8] = REDUCE(ts_sym_type_name, 1),
    },
    [113] = {
        [ts_sym_type_expression] = SHIFT(114),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT(113),
        [ts_aux_sym_6] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_7] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [114] = {
        [ts_sym_comment] = SHIFT(114),
        [ts_aux_sym_8] = REDUCE(ts_sym_pointer_type, 2),
    },
    [115] = {
        [ts_sym_comment] = SHIFT(115),
        [ts_aux_sym_7] = SHIFT(116),
    },
    [116] = {
        [ts_sym_type_expression] = SHIFT(117),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT(116),
        [ts_aux_sym_6] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_7] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [117] = {
        [ts_sym_comment] = SHIFT(117),
        [ts_aux_sym_8] = SHIFT(118),
    },
    [118] = {
        [ts_sym_type_expression] = SHIFT(119),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT(118),
        [ts_aux_sym_6] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_7] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [119] = {
        [ts_sym_comment] = SHIFT(119),
        [ts_aux_sym_8] = REDUCE(ts_sym_map_type, 5),
    },
    [120] = {
        [ts_sym_comment] = SHIFT(120),
        [ts_aux_sym_8] = SHIFT(121),
    },
    [121] = {
        [ts_sym_type_expression] = SHIFT(122),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT(121),
        [ts_aux_sym_6] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_7] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [122] = {
        [ts_sym_comment] = SHIFT(122),
        [ts_aux_sym_8] = REDUCE(ts_sym_slice_type, 3),
    },
    [123] = {
        [ts_sym_comment] = SHIFT(123),
        [ts_aux_sym_4] = SHIFT(124),
    },
    [124] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT(124),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(125),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [125] = {
        [ts_sym_comment] = SHIFT(125),
        [ts_aux_sym_5] = SHIFT(126),
    },
    [126] = {
        [ts_sym_comment] = SHIFT(126),
        [ts_aux_sym_8] = REDUCE(ts_sym_struct_type, 4),
    },
    [127] = {
        [ts_sym_comment] = SHIFT(127),
        [ts_aux_sym_4] = SHIFT(128),
    },
    [128] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT(128),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(129),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [129] = {
        [ts_sym_comment] = SHIFT(129),
        [ts_aux_sym_5] = SHIFT(130),
    },
    [130] = {
        [ts_sym_comment] = SHIFT(130),
        [ts_aux_sym_8] = REDUCE(ts_sym_interface_type, 4),
    },
    [131] = {
        [ts_sym_var_name] = SHIFT(132),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT(131),
    },
    [132] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym_comment] = SHIFT(132),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(133),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_9] = SHIFT(131),
    },
    [133] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_comment] = SHIFT(133),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [134] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(134),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_9] = REDUCE(ts_sym_var_name, 1),
    },
    [135] = {
        [ts_sym_var_name] = SHIFT(136),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT(135),
    },
    [136] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT(136),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(137),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_9] = SHIFT(135),
    },
    [137] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_comment] = SHIFT(137),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
    },
    [138] = {
        [ts_sym_type_name] = SHIFT(139),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT(138),
        [ts_aux_sym_1] = SHIFT(140),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 2),
    },
    [139] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_sym_comment] = SHIFT(139),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 3),
    },
    [140] = {
        [ts_sym_var_name] = SHIFT(141),
        [ts_sym_type_name] = SHIFT(144),
        [ts_sym__identifier] = SHIFT(86),
        [ts_sym_comment] = SHIFT(140),
    },
    [141] = {
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(141),
    },
    [142] = {
        [ts_sym_comment] = SHIFT(142),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(143),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_9] = SHIFT(74),
    },
    [143] = {
        [ts_sym_comment] = SHIFT(143),
        [ts_aux_sym_2] = SHIFT(68),
    },
    [144] = {
        [ts_sym_comment] = SHIFT(144),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(145),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_9] = SHIFT(83),
    },
    [145] = {
        [ts_sym_comment] = SHIFT(145),
        [ts_aux_sym_2] = SHIFT(146),
    },
    [146] = {
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym_comment] = SHIFT(146),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [147] = {
        [ts_sym_comment] = SHIFT(147),
        [ts_aux_sym_5] = SHIFT(148),
    },
    [148] = {
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT(148),
        [ts_aux_sym_5] = REDUCE(ts_sym_interface_type, 4),
    },
    [149] = {
        [ts_sym_comment] = SHIFT(149),
        [ts_aux_sym_5] = SHIFT(150),
    },
    [150] = {
        [ts_sym__terminator] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT(150),
    },
    [151] = {
        [ts_sym_comment] = SHIFT(151),
        [ts_aux_sym_4] = SHIFT(152),
    },
    [152] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT(152),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(153),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [153] = {
        [ts_sym_comment] = SHIFT(153),
        [ts_aux_sym_5] = SHIFT(154),
    },
    [154] = {
        [ts_sym__terminator] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT(154),
    },
    [155] = {
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT(155),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_type_name, 1),
    },
    [156] = {
        [ts_sym_var_name] = SHIFT(157),
        [ts_sym__identifier] = SHIFT(231),
        [ts_sym_comment] = SHIFT(156),
    },
    [157] = {
        [ts_sym_type_expression] = SHIFT(158),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT(157),
        [ts_aux_sym_3] = SHIFT(210),
        [ts_aux_sym_6] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_7] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [158] = {
        [ts_sym__terminator] = SHIFT(159),
        [ts_sym_comment] = SHIFT(158),
        [ts_aux_sym_3] = SHIFT(160),
    },
    [159] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_comment] = SHIFT(159),
        [ts_aux_sym_type] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_var_declaration, 4),
    },
    [160] = {
        [ts_sym_expression] = SHIFT(161),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(160),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [161] = {
        [ts_sym__terminator] = SHIFT(162),
        [ts_sym_comment] = SHIFT(161),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_6] = SHIFT(192),
        [ts_aux_sym_11] = SHIFT(194),
        [ts_aux_sym_12] = SHIFT(192),
        [ts_aux_sym_13] = SHIFT(197),
        [ts_aux_sym_14] = SHIFT(197),
        [ts_aux_sym_15] = SHIFT(199),
        [ts_aux_sym_16] = SHIFT(201),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [162] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_comment] = SHIFT(162),
        [ts_aux_sym_type] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_func] = REDUCE(ts_sym_var_declaration, 6),
    },
    [163] = {
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(163),
        [ts_aux_sym_2] = SHIFT(191),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [164] = {
        [ts_sym_comment] = SHIFT(164),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(165),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = SHIFT(187),
        [ts_aux_sym_11] = SHIFT(173),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = SHIFT(176),
        [ts_aux_sym_14] = SHIFT(176),
        [ts_aux_sym_15] = SHIFT(178),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [165] = {
        [ts_sym_comment] = SHIFT(165),
        [ts_aux_sym_2] = SHIFT(166),
    },
    [166] = {
        [ts_sym__terminator] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym_comment] = SHIFT(166),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 5),
    },
    [167] = {
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(167),
        [ts_aux_sym_2] = SHIFT(190),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [168] = {
        [ts_sym_comment] = SHIFT(168),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(169),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = SHIFT(187),
        [ts_aux_sym_11] = SHIFT(173),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = SHIFT(176),
        [ts_aux_sym_14] = SHIFT(176),
        [ts_aux_sym_15] = SHIFT(178),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [169] = {
        [ts_sym_comment] = SHIFT(169),
        [ts_aux_sym_2] = SHIFT(170),
    },
    [170] = {
        [ts_sym_comment] = SHIFT(170),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_2] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_9] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 5),
    },
    [171] = {
        [ts_sym_expression] = SHIFT(172),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(171),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [172] = {
        [ts_sym_comment] = SHIFT(172),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [173] = {
        [ts_sym_var_name] = SHIFT(174),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_comment] = SHIFT(173),
    },
    [174] = {
        [ts_sym_comment] = SHIFT(174),
        [ts_aux_sym_1] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_selector_expression, 3),
    },
    [175] = {
        [ts_sym_comment] = SHIFT(175),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_9] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_var_name, 1),
    },
    [176] = {
        [ts_sym_expression] = SHIFT(177),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(176),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [177] = {
        [ts_sym_comment] = SHIFT(177),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = SHIFT(176),
        [ts_aux_sym_14] = SHIFT(176),
        [ts_aux_sym_15] = SHIFT(178),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [178] = {
        [ts_sym_expression] = SHIFT(179),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(178),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [179] = {
        [ts_sym_comment] = SHIFT(179),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = SHIFT(176),
        [ts_aux_sym_14] = SHIFT(176),
        [ts_aux_sym_15] = SHIFT(178),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [180] = {
        [ts_sym_expression] = SHIFT(181),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(180),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [181] = {
        [ts_sym_comment] = SHIFT(181),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [182] = {
        [ts_sym_expression] = SHIFT(183),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(182),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [183] = {
        [ts_sym_comment] = SHIFT(183),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [184] = {
        [ts_sym_comment] = SHIFT(184),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_expression, 1),
    },
    [185] = {
        [ts_sym_expression] = SHIFT(186),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(185),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [186] = {
        [ts_sym_comment] = SHIFT(186),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_21] = REDUCE(ts_sym_bool_op, 2),
    },
    [187] = {
        [ts_sym_expression] = SHIFT(188),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(187),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [188] = {
        [ts_sym_comment] = SHIFT(188),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(189),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = SHIFT(187),
        [ts_aux_sym_11] = SHIFT(173),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = SHIFT(176),
        [ts_aux_sym_14] = SHIFT(176),
        [ts_aux_sym_15] = SHIFT(178),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [189] = {
        [ts_sym_comment] = SHIFT(189),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 3),
    },
    [190] = {
        [ts_sym_comment] = SHIFT(190),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 3),
    },
    [191] = {
        [ts_sym__terminator] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym_comment] = SHIFT(191),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 3),
    },
    [192] = {
        [ts_sym_expression] = SHIFT(193),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(192),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [193] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT(193),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(192),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(192),
        [ts_aux_sym_13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = SHIFT(201),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [194] = {
        [ts_sym_var_name] = SHIFT(195),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_comment] = SHIFT(194),
    },
    [195] = {
        [ts_sym__terminator] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym_comment] = SHIFT(195),
        [ts_aux_sym_1] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_selector_expression, 3),
    },
    [196] = {
        [ts_sym__terminator] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(196),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_var_name, 1),
    },
    [197] = {
        [ts_sym_expression] = SHIFT(198),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(197),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [198] = {
        [ts_sym__terminator] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT(198),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(192),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(192),
        [ts_aux_sym_13] = SHIFT(197),
        [ts_aux_sym_14] = SHIFT(197),
        [ts_aux_sym_15] = SHIFT(199),
        [ts_aux_sym_16] = SHIFT(201),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [199] = {
        [ts_sym_expression] = SHIFT(200),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(199),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [200] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(200),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(192),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(192),
        [ts_aux_sym_13] = SHIFT(197),
        [ts_aux_sym_14] = SHIFT(197),
        [ts_aux_sym_15] = SHIFT(199),
        [ts_aux_sym_16] = SHIFT(201),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [201] = {
        [ts_sym_expression] = SHIFT(202),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(201),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [202] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(202),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(192),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(192),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = SHIFT(201),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [203] = {
        [ts_sym_expression] = SHIFT(204),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(203),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [204] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(204),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [205] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT(205),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_expression, 1),
    },
    [206] = {
        [ts_sym_expression] = SHIFT(207),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(206),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [207] = {
        [ts_sym__terminator] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym_comment] = SHIFT(207),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_21] = REDUCE(ts_sym_bool_op, 2),
    },
    [208] = {
        [ts_sym__terminator] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT(208),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
    },
    [209] = {
        [ts_sym__terminator] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT(209),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_name, 1),
    },
    [210] = {
        [ts_sym_expression] = SHIFT(211),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(210),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [211] = {
        [ts_sym__terminator] = SHIFT(212),
        [ts_sym_comment] = SHIFT(211),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_6] = SHIFT(192),
        [ts_aux_sym_11] = SHIFT(194),
        [ts_aux_sym_12] = SHIFT(192),
        [ts_aux_sym_13] = SHIFT(197),
        [ts_aux_sym_14] = SHIFT(197),
        [ts_aux_sym_15] = SHIFT(199),
        [ts_aux_sym_16] = SHIFT(201),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [212] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_comment] = SHIFT(212),
        [ts_aux_sym_type] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_func] = REDUCE(ts_sym_var_declaration, 5),
    },
    [213] = {
        [ts_sym_type_expression] = SHIFT(214),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT(213),
        [ts_aux_sym_6] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_7] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [214] = {
        [ts_sym__terminator] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT(214),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
    },
    [215] = {
        [ts_sym_comment] = SHIFT(215),
        [ts_aux_sym_7] = SHIFT(216),
    },
    [216] = {
        [ts_sym_type_expression] = SHIFT(217),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT(216),
        [ts_aux_sym_6] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_7] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [217] = {
        [ts_sym_comment] = SHIFT(217),
        [ts_aux_sym_8] = SHIFT(218),
    },
    [218] = {
        [ts_sym_type_expression] = SHIFT(219),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT(218),
        [ts_aux_sym_6] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_7] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [219] = {
        [ts_sym__terminator] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT(219),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
    },
    [220] = {
        [ts_sym_comment] = SHIFT(220),
        [ts_aux_sym_8] = SHIFT(221),
    },
    [221] = {
        [ts_sym_type_expression] = SHIFT(222),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT(221),
        [ts_aux_sym_6] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_7] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [222] = {
        [ts_sym__terminator] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT(222),
        [ts_aux_sym_3] = REDUCE(ts_sym_slice_type, 3),
    },
    [223] = {
        [ts_sym_comment] = SHIFT(223),
        [ts_aux_sym_4] = SHIFT(224),
    },
    [224] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT(224),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(225),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [225] = {
        [ts_sym_comment] = SHIFT(225),
        [ts_aux_sym_5] = SHIFT(226),
    },
    [226] = {
        [ts_sym__terminator] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT(226),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 4),
    },
    [227] = {
        [ts_sym_comment] = SHIFT(227),
        [ts_aux_sym_4] = SHIFT(228),
    },
    [228] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT(228),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(229),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [229] = {
        [ts_sym_comment] = SHIFT(229),
        [ts_aux_sym_5] = SHIFT(230),
    },
    [230] = {
        [ts_sym__terminator] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT(230),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
    },
    [231] = {
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(231),
        [ts_aux_sym_3] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
    },
    [232] = {
        [ts_sym_var_name] = SHIFT(233),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT(232),
    },
    [233] = {
        [ts_sym__func_signature] = SHIFT(234),
        [ts_sym_comment] = SHIFT(233),
        [ts_aux_sym_1] = SHIFT(347),
    },
    [234] = {
        [ts_sym_block_statement] = SHIFT(235),
        [ts_sym_comment] = SHIFT(234),
        [ts_aux_sym_4] = SHIFT(237),
    },
    [235] = {
        [ts_sym__terminator] = SHIFT(236),
        [ts_sym_comment] = SHIFT(235),
    },
    [236] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 5),
        [ts_sym_comment] = SHIFT(236),
        [ts_aux_sym_type] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_var] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_func] = REDUCE(ts_sym_func_declaration, 5),
    },
    [237] = {
        [ts_sym_var_declaration] = SHIFT(238),
        [ts_sym_statement] = SHIFT(239),
        [ts_sym_return_statement] = SHIFT(240),
        [ts_sym_declaration_statement] = SHIFT(240),
        [ts_sym_if_statement] = SHIFT(240),
        [ts_sym_expression_statement] = SHIFT(240),
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(243),
        [ts_builtin_sym_error] = SHIFT(345),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(272),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(237),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(345),
        [ts_aux_sym_var] = SHIFT(274),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(284),
        [ts_aux_sym_10] = SHIFT(311),
        [ts_aux_sym_if] = SHIFT(313),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [238] = {
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_comment] = SHIFT(238),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_22] = REDUCE(ts_sym_declaration_statement, 1),
    },
    [239] = {
        [ts_sym_var_declaration] = SHIFT(238),
        [ts_sym_statement] = SHIFT(239),
        [ts_sym_return_statement] = SHIFT(240),
        [ts_sym_declaration_statement] = SHIFT(240),
        [ts_sym_if_statement] = SHIFT(240),
        [ts_sym_expression_statement] = SHIFT(240),
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(243),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(272),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(239),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(273),
        [ts_aux_sym_var] = SHIFT(274),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(284),
        [ts_aux_sym_10] = SHIFT(311),
        [ts_aux_sym_if] = SHIFT(313),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [240] = {
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_sym_comment] = SHIFT(240),
        [ts_aux_sym_var] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_22] = REDUCE(ts_sym_statement, 1),
    },
    [241] = {
        [ts_sym__terminator] = SHIFT(242),
        [ts_sym_comment] = SHIFT(241),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_6] = SHIFT(192),
        [ts_aux_sym_11] = SHIFT(194),
        [ts_aux_sym_12] = SHIFT(192),
        [ts_aux_sym_13] = SHIFT(197),
        [ts_aux_sym_14] = SHIFT(197),
        [ts_aux_sym_15] = SHIFT(199),
        [ts_aux_sym_16] = SHIFT(201),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [242] = {
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_comment] = SHIFT(242),
        [ts_aux_sym_var] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_5] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_return] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_22] = REDUCE(ts_sym_expression_statement, 2),
    },
    [243] = {
        [ts_sym__terminator] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT(243),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(244),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_9] = SHIFT(268),
        [ts_aux_sym_10] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 0),
        [ts_aux_sym_11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_expression, 1),
    },
    [244] = {
        [ts_sym_comment] = SHIFT(244),
        [ts_aux_sym_10] = SHIFT(245),
    },
    [245] = {
        [ts_sym_expression] = SHIFT(246),
        [ts_sym_call_expression] = SHIFT(265),
        [ts_sym_selector_expression] = SHIFT(265),
        [ts_sym_math_op] = SHIFT(265),
        [ts_sym_bool_op] = SHIFT(265),
        [ts_sym_var_name] = SHIFT(265),
        [ts_sym_string] = SHIFT(265),
        [ts_sym__identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(265),
        [ts_sym_comment] = SHIFT(245),
        [ts_aux_sym_22] = SHIFT(266),
    },
    [246] = {
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_comment] = SHIFT(246),
        [ts_aux_sym_1] = SHIFT(247),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_5] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_6] = SHIFT(252),
        [ts_aux_sym_return] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_if] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_11] = SHIFT(254),
        [ts_aux_sym_12] = SHIFT(252),
        [ts_aux_sym_13] = SHIFT(257),
        [ts_aux_sym_14] = SHIFT(257),
        [ts_aux_sym_15] = SHIFT(259),
        [ts_aux_sym_16] = SHIFT(261),
        [ts_aux_sym_17] = SHIFT(263),
        [ts_aux_sym_18] = SHIFT(263),
        [ts_aux_sym_19] = SHIFT(263),
        [ts_aux_sym_20] = SHIFT(263),
        [ts_aux_sym_21] = SHIFT(263),
        [ts_aux_sym_22] = REDUCE(ts_sym_declaration_statement, 4),
    },
    [247] = {
        [ts_sym_expression] = SHIFT(248),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(247),
        [ts_aux_sym_2] = SHIFT(251),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [248] = {
        [ts_sym_comment] = SHIFT(248),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(249),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = SHIFT(187),
        [ts_aux_sym_11] = SHIFT(173),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = SHIFT(176),
        [ts_aux_sym_14] = SHIFT(176),
        [ts_aux_sym_15] = SHIFT(178),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [249] = {
        [ts_sym_comment] = SHIFT(249),
        [ts_aux_sym_2] = SHIFT(250),
    },
    [250] = {
        [ts_sym_string] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym_number] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym_comment] = SHIFT(250),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_var] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_5] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_return] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_if] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_22] = REDUCE(ts_sym_call_expression, 5),
    },
    [251] = {
        [ts_sym_string] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym_number] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym_comment] = SHIFT(251),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_22] = REDUCE(ts_sym_call_expression, 3),
    },
    [252] = {
        [ts_sym_expression] = SHIFT(253),
        [ts_sym_call_expression] = SHIFT(265),
        [ts_sym_selector_expression] = SHIFT(265),
        [ts_sym_math_op] = SHIFT(265),
        [ts_sym_bool_op] = SHIFT(265),
        [ts_sym_var_name] = SHIFT(265),
        [ts_sym_string] = SHIFT(265),
        [ts_sym__identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(265),
        [ts_sym_comment] = SHIFT(252),
        [ts_aux_sym_22] = SHIFT(266),
    },
    [253] = {
        [ts_sym_string] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT(253),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(252),
        [ts_aux_sym_return] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(252),
        [ts_aux_sym_13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = SHIFT(261),
        [ts_aux_sym_17] = SHIFT(263),
        [ts_aux_sym_18] = SHIFT(263),
        [ts_aux_sym_19] = SHIFT(263),
        [ts_aux_sym_20] = SHIFT(263),
        [ts_aux_sym_21] = SHIFT(263),
        [ts_aux_sym_22] = REDUCE(ts_sym_math_op, 3),
    },
    [254] = {
        [ts_sym_var_name] = SHIFT(255),
        [ts_sym__identifier] = SHIFT(256),
        [ts_sym_comment] = SHIFT(254),
    },
    [255] = {
        [ts_sym_string] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym_number] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym_comment] = SHIFT(255),
        [ts_aux_sym_1] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_22] = REDUCE(ts_sym_selector_expression, 3),
    },
    [256] = {
        [ts_sym_string] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_number] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(256),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_22] = REDUCE(ts_sym_var_name, 1),
    },
    [257] = {
        [ts_sym_expression] = SHIFT(258),
        [ts_sym_call_expression] = SHIFT(265),
        [ts_sym_selector_expression] = SHIFT(265),
        [ts_sym_math_op] = SHIFT(265),
        [ts_sym_bool_op] = SHIFT(265),
        [ts_sym_var_name] = SHIFT(265),
        [ts_sym_string] = SHIFT(265),
        [ts_sym__identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(265),
        [ts_sym_comment] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(266),
    },
    [258] = {
        [ts_sym_string] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT(258),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(252),
        [ts_aux_sym_return] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(252),
        [ts_aux_sym_13] = SHIFT(257),
        [ts_aux_sym_14] = SHIFT(257),
        [ts_aux_sym_15] = SHIFT(259),
        [ts_aux_sym_16] = SHIFT(261),
        [ts_aux_sym_17] = SHIFT(263),
        [ts_aux_sym_18] = SHIFT(263),
        [ts_aux_sym_19] = SHIFT(263),
        [ts_aux_sym_20] = SHIFT(263),
        [ts_aux_sym_21] = SHIFT(263),
        [ts_aux_sym_22] = REDUCE(ts_sym_math_op, 3),
    },
    [259] = {
        [ts_sym_expression] = SHIFT(260),
        [ts_sym_call_expression] = SHIFT(265),
        [ts_sym_selector_expression] = SHIFT(265),
        [ts_sym_math_op] = SHIFT(265),
        [ts_sym_bool_op] = SHIFT(265),
        [ts_sym_var_name] = SHIFT(265),
        [ts_sym_string] = SHIFT(265),
        [ts_sym__identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(265),
        [ts_sym_comment] = SHIFT(259),
        [ts_aux_sym_22] = SHIFT(266),
    },
    [260] = {
        [ts_sym_string] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(260),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(252),
        [ts_aux_sym_return] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(252),
        [ts_aux_sym_13] = SHIFT(257),
        [ts_aux_sym_14] = SHIFT(257),
        [ts_aux_sym_15] = SHIFT(259),
        [ts_aux_sym_16] = SHIFT(261),
        [ts_aux_sym_17] = SHIFT(263),
        [ts_aux_sym_18] = SHIFT(263),
        [ts_aux_sym_19] = SHIFT(263),
        [ts_aux_sym_20] = SHIFT(263),
        [ts_aux_sym_21] = SHIFT(263),
        [ts_aux_sym_22] = REDUCE(ts_sym_bool_op, 3),
    },
    [261] = {
        [ts_sym_expression] = SHIFT(262),
        [ts_sym_call_expression] = SHIFT(265),
        [ts_sym_selector_expression] = SHIFT(265),
        [ts_sym_math_op] = SHIFT(265),
        [ts_sym_bool_op] = SHIFT(265),
        [ts_sym_var_name] = SHIFT(265),
        [ts_sym_string] = SHIFT(265),
        [ts_sym__identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(265),
        [ts_sym_comment] = SHIFT(261),
        [ts_aux_sym_22] = SHIFT(266),
    },
    [262] = {
        [ts_sym_string] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(262),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(252),
        [ts_aux_sym_return] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(252),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = SHIFT(261),
        [ts_aux_sym_17] = SHIFT(263),
        [ts_aux_sym_18] = SHIFT(263),
        [ts_aux_sym_19] = SHIFT(263),
        [ts_aux_sym_20] = SHIFT(263),
        [ts_aux_sym_21] = SHIFT(263),
        [ts_aux_sym_22] = REDUCE(ts_sym_bool_op, 3),
    },
    [263] = {
        [ts_sym_expression] = SHIFT(264),
        [ts_sym_call_expression] = SHIFT(265),
        [ts_sym_selector_expression] = SHIFT(265),
        [ts_sym_math_op] = SHIFT(265),
        [ts_sym_bool_op] = SHIFT(265),
        [ts_sym_var_name] = SHIFT(265),
        [ts_sym_string] = SHIFT(265),
        [ts_sym__identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(265),
        [ts_sym_comment] = SHIFT(263),
        [ts_aux_sym_22] = SHIFT(266),
    },
    [264] = {
        [ts_sym_string] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(264),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(263),
        [ts_aux_sym_18] = SHIFT(263),
        [ts_aux_sym_19] = SHIFT(263),
        [ts_aux_sym_20] = SHIFT(263),
        [ts_aux_sym_21] = SHIFT(263),
        [ts_aux_sym_22] = REDUCE(ts_sym_bool_op, 3),
    },
    [265] = {
        [ts_sym_string] = REDUCE(ts_sym_expression, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_expression, 1),
        [ts_sym_number] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT(265),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_22] = REDUCE(ts_sym_expression, 1),
    },
    [266] = {
        [ts_sym_expression] = SHIFT(267),
        [ts_sym_call_expression] = SHIFT(265),
        [ts_sym_selector_expression] = SHIFT(265),
        [ts_sym_math_op] = SHIFT(265),
        [ts_sym_bool_op] = SHIFT(265),
        [ts_sym_var_name] = SHIFT(265),
        [ts_sym_string] = SHIFT(265),
        [ts_sym__identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(265),
        [ts_sym_comment] = SHIFT(266),
        [ts_aux_sym_22] = SHIFT(266),
    },
    [267] = {
        [ts_sym_string] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym_number] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym_comment] = SHIFT(267),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_return] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_22] = REDUCE(ts_sym_bool_op, 2),
    },
    [268] = {
        [ts_sym_var_name] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_comment] = SHIFT(268),
    },
    [269] = {
        [ts_sym_comment] = SHIFT(269),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(270),
        [ts_aux_sym_9] = SHIFT(268),
        [ts_aux_sym_10] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 0),
    },
    [270] = {
        [ts_sym_comment] = SHIFT(270),
        [ts_aux_sym_10] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 3),
    },
    [271] = {
        [ts_sym_comment] = SHIFT(271),
        [ts_aux_sym_9] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
    },
    [272] = {
        [ts_sym__terminator] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(272),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_9] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_var_name, 1),
    },
    [273] = {
        [ts_sym_comment] = SHIFT(273),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_block_statement_repeat0, 2),
    },
    [274] = {
        [ts_sym_var_name] = SHIFT(275),
        [ts_sym__identifier] = SHIFT(231),
        [ts_sym_comment] = SHIFT(274),
    },
    [275] = {
        [ts_sym_type_expression] = SHIFT(276),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT(275),
        [ts_aux_sym_3] = SHIFT(281),
        [ts_aux_sym_6] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_7] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [276] = {
        [ts_sym__terminator] = SHIFT(277),
        [ts_sym_comment] = SHIFT(276),
        [ts_aux_sym_3] = SHIFT(278),
    },
    [277] = {
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__identifier] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_comment] = SHIFT(277),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_5] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_return] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_if] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_22] = REDUCE(ts_sym_var_declaration, 4),
    },
    [278] = {
        [ts_sym_expression] = SHIFT(279),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(278),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [279] = {
        [ts_sym__terminator] = SHIFT(280),
        [ts_sym_comment] = SHIFT(279),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_6] = SHIFT(192),
        [ts_aux_sym_11] = SHIFT(194),
        [ts_aux_sym_12] = SHIFT(192),
        [ts_aux_sym_13] = SHIFT(197),
        [ts_aux_sym_14] = SHIFT(197),
        [ts_aux_sym_15] = SHIFT(199),
        [ts_aux_sym_16] = SHIFT(201),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [280] = {
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym__identifier] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_comment] = SHIFT(280),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_5] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_return] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_if] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_22] = REDUCE(ts_sym_var_declaration, 6),
    },
    [281] = {
        [ts_sym_expression] = SHIFT(282),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(205),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(196),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(281),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [282] = {
        [ts_sym__terminator] = SHIFT(283),
        [ts_sym_comment] = SHIFT(282),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_6] = SHIFT(192),
        [ts_aux_sym_11] = SHIFT(194),
        [ts_aux_sym_12] = SHIFT(192),
        [ts_aux_sym_13] = SHIFT(197),
        [ts_aux_sym_14] = SHIFT(197),
        [ts_aux_sym_15] = SHIFT(199),
        [ts_aux_sym_16] = SHIFT(201),
        [ts_aux_sym_17] = SHIFT(203),
        [ts_aux_sym_18] = SHIFT(203),
        [ts_aux_sym_19] = SHIFT(203),
        [ts_aux_sym_20] = SHIFT(203),
        [ts_aux_sym_21] = SHIFT(203),
    },
    [283] = {
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_comment] = SHIFT(283),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_5] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_return] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_if] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_22] = REDUCE(ts_sym_var_declaration, 5),
    },
    [284] = {
        [ts_sym_expression] = SHIFT(285),
        [ts_sym_call_expression] = SHIFT(305),
        [ts_sym_selector_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(305),
        [ts_sym_bool_op] = SHIFT(305),
        [ts_sym_var_name] = SHIFT(305),
        [ts_sym_string] = SHIFT(305),
        [ts_sym__identifier] = SHIFT(296),
        [ts_sym_number] = SHIFT(305),
        [ts_sym_comment] = SHIFT(284),
        [ts_aux_sym_var] = REDUCE(ts_sym_return_statement, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_return_statement, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_return_statement, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_return_statement, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_return_statement, 1),
        [ts_aux_sym_22] = SHIFT(306),
    },
    [285] = {
        [ts_sym_string] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym_number] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym_comment] = SHIFT(285),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(286),
        [ts_aux_sym_1] = SHIFT(287),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_6] = SHIFT(292),
        [ts_aux_sym_return] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_9] = SHIFT(308),
        [ts_aux_sym_10] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_if] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_11] = SHIFT(294),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(297),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(299),
        [ts_aux_sym_16] = SHIFT(301),
        [ts_aux_sym_17] = SHIFT(303),
        [ts_aux_sym_18] = SHIFT(303),
        [ts_aux_sym_19] = SHIFT(303),
        [ts_aux_sym_20] = SHIFT(303),
        [ts_aux_sym_21] = SHIFT(303),
        [ts_aux_sym_22] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
    },
    [286] = {
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = SHIFT(286),
        [ts_aux_sym_var] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_22] = REDUCE(ts_sym_return_statement, 3),
    },
    [287] = {
        [ts_sym_expression] = SHIFT(288),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(287),
        [ts_aux_sym_2] = SHIFT(291),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [288] = {
        [ts_sym_comment] = SHIFT(288),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(289),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = SHIFT(187),
        [ts_aux_sym_11] = SHIFT(173),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = SHIFT(176),
        [ts_aux_sym_14] = SHIFT(176),
        [ts_aux_sym_15] = SHIFT(178),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [289] = {
        [ts_sym_comment] = SHIFT(289),
        [ts_aux_sym_2] = SHIFT(290),
    },
    [290] = {
        [ts_sym_string] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym_number] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym_comment] = SHIFT(290),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_var] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_5] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_return] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_9] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_if] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_22] = REDUCE(ts_sym_call_expression, 5),
    },
    [291] = {
        [ts_sym_string] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym_number] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym_comment] = SHIFT(291),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_22] = REDUCE(ts_sym_call_expression, 3),
    },
    [292] = {
        [ts_sym_expression] = SHIFT(293),
        [ts_sym_call_expression] = SHIFT(305),
        [ts_sym_selector_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(305),
        [ts_sym_bool_op] = SHIFT(305),
        [ts_sym_var_name] = SHIFT(305),
        [ts_sym_string] = SHIFT(305),
        [ts_sym__identifier] = SHIFT(296),
        [ts_sym_number] = SHIFT(305),
        [ts_sym_comment] = SHIFT(292),
        [ts_aux_sym_22] = SHIFT(306),
    },
    [293] = {
        [ts_sym_string] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT(293),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(292),
        [ts_aux_sym_return] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = SHIFT(301),
        [ts_aux_sym_17] = SHIFT(303),
        [ts_aux_sym_18] = SHIFT(303),
        [ts_aux_sym_19] = SHIFT(303),
        [ts_aux_sym_20] = SHIFT(303),
        [ts_aux_sym_21] = SHIFT(303),
        [ts_aux_sym_22] = REDUCE(ts_sym_math_op, 3),
    },
    [294] = {
        [ts_sym_var_name] = SHIFT(295),
        [ts_sym__identifier] = SHIFT(296),
        [ts_sym_comment] = SHIFT(294),
    },
    [295] = {
        [ts_sym_string] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym_number] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym_comment] = SHIFT(295),
        [ts_aux_sym_1] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_22] = REDUCE(ts_sym_selector_expression, 3),
    },
    [296] = {
        [ts_sym_string] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_number] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT(296),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_9] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_22] = REDUCE(ts_sym_var_name, 1),
    },
    [297] = {
        [ts_sym_expression] = SHIFT(298),
        [ts_sym_call_expression] = SHIFT(305),
        [ts_sym_selector_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(305),
        [ts_sym_bool_op] = SHIFT(305),
        [ts_sym_var_name] = SHIFT(305),
        [ts_sym_string] = SHIFT(305),
        [ts_sym__identifier] = SHIFT(296),
        [ts_sym_number] = SHIFT(305),
        [ts_sym_comment] = SHIFT(297),
        [ts_aux_sym_22] = SHIFT(306),
    },
    [298] = {
        [ts_sym_string] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT(298),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(292),
        [ts_aux_sym_return] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(297),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(299),
        [ts_aux_sym_16] = SHIFT(301),
        [ts_aux_sym_17] = SHIFT(303),
        [ts_aux_sym_18] = SHIFT(303),
        [ts_aux_sym_19] = SHIFT(303),
        [ts_aux_sym_20] = SHIFT(303),
        [ts_aux_sym_21] = SHIFT(303),
        [ts_aux_sym_22] = REDUCE(ts_sym_math_op, 3),
    },
    [299] = {
        [ts_sym_expression] = SHIFT(300),
        [ts_sym_call_expression] = SHIFT(305),
        [ts_sym_selector_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(305),
        [ts_sym_bool_op] = SHIFT(305),
        [ts_sym_var_name] = SHIFT(305),
        [ts_sym_string] = SHIFT(305),
        [ts_sym__identifier] = SHIFT(296),
        [ts_sym_number] = SHIFT(305),
        [ts_sym_comment] = SHIFT(299),
        [ts_aux_sym_22] = SHIFT(306),
    },
    [300] = {
        [ts_sym_string] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(300),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(292),
        [ts_aux_sym_return] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(297),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(299),
        [ts_aux_sym_16] = SHIFT(301),
        [ts_aux_sym_17] = SHIFT(303),
        [ts_aux_sym_18] = SHIFT(303),
        [ts_aux_sym_19] = SHIFT(303),
        [ts_aux_sym_20] = SHIFT(303),
        [ts_aux_sym_21] = SHIFT(303),
        [ts_aux_sym_22] = REDUCE(ts_sym_bool_op, 3),
    },
    [301] = {
        [ts_sym_expression] = SHIFT(302),
        [ts_sym_call_expression] = SHIFT(305),
        [ts_sym_selector_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(305),
        [ts_sym_bool_op] = SHIFT(305),
        [ts_sym_var_name] = SHIFT(305),
        [ts_sym_string] = SHIFT(305),
        [ts_sym__identifier] = SHIFT(296),
        [ts_sym_number] = SHIFT(305),
        [ts_sym_comment] = SHIFT(301),
        [ts_aux_sym_22] = SHIFT(306),
    },
    [302] = {
        [ts_sym_string] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(302),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(292),
        [ts_aux_sym_return] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = SHIFT(301),
        [ts_aux_sym_17] = SHIFT(303),
        [ts_aux_sym_18] = SHIFT(303),
        [ts_aux_sym_19] = SHIFT(303),
        [ts_aux_sym_20] = SHIFT(303),
        [ts_aux_sym_21] = SHIFT(303),
        [ts_aux_sym_22] = REDUCE(ts_sym_bool_op, 3),
    },
    [303] = {
        [ts_sym_expression] = SHIFT(304),
        [ts_sym_call_expression] = SHIFT(305),
        [ts_sym_selector_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(305),
        [ts_sym_bool_op] = SHIFT(305),
        [ts_sym_var_name] = SHIFT(305),
        [ts_sym_string] = SHIFT(305),
        [ts_sym__identifier] = SHIFT(296),
        [ts_sym_number] = SHIFT(305),
        [ts_sym_comment] = SHIFT(303),
        [ts_aux_sym_22] = SHIFT(306),
    },
    [304] = {
        [ts_sym_string] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_number] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT(304),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_9] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(303),
        [ts_aux_sym_18] = SHIFT(303),
        [ts_aux_sym_19] = SHIFT(303),
        [ts_aux_sym_20] = SHIFT(303),
        [ts_aux_sym_21] = SHIFT(303),
        [ts_aux_sym_22] = REDUCE(ts_sym_bool_op, 3),
    },
    [305] = {
        [ts_sym_string] = REDUCE(ts_sym_expression, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_expression, 1),
        [ts_sym_number] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT(305),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_9] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_22] = REDUCE(ts_sym_expression, 1),
    },
    [306] = {
        [ts_sym_expression] = SHIFT(307),
        [ts_sym_call_expression] = SHIFT(305),
        [ts_sym_selector_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(305),
        [ts_sym_bool_op] = SHIFT(305),
        [ts_sym_var_name] = SHIFT(305),
        [ts_sym_string] = SHIFT(305),
        [ts_sym__identifier] = SHIFT(296),
        [ts_sym_number] = SHIFT(305),
        [ts_sym_comment] = SHIFT(306),
        [ts_aux_sym_22] = SHIFT(306),
    },
    [307] = {
        [ts_sym_string] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym_number] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym_comment] = SHIFT(307),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_return] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_9] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_21] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_22] = REDUCE(ts_sym_bool_op, 2),
    },
    [308] = {
        [ts_sym_expression] = SHIFT(309),
        [ts_sym_call_expression] = SHIFT(305),
        [ts_sym_selector_expression] = SHIFT(305),
        [ts_sym_math_op] = SHIFT(305),
        [ts_sym_bool_op] = SHIFT(305),
        [ts_sym_var_name] = SHIFT(305),
        [ts_sym_string] = SHIFT(305),
        [ts_sym__identifier] = SHIFT(296),
        [ts_sym_number] = SHIFT(305),
        [ts_sym_comment] = SHIFT(308),
        [ts_aux_sym_22] = SHIFT(306),
    },
    [309] = {
        [ts_sym_string] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym__identifier] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym_number] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym_comment] = SHIFT(309),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(310),
        [ts_aux_sym_1] = SHIFT(287),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_6] = SHIFT(292),
        [ts_aux_sym_return] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_9] = SHIFT(308),
        [ts_aux_sym_10] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_if] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_11] = SHIFT(294),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(297),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(299),
        [ts_aux_sym_16] = SHIFT(301),
        [ts_aux_sym_17] = SHIFT(303),
        [ts_aux_sym_18] = SHIFT(303),
        [ts_aux_sym_19] = SHIFT(303),
        [ts_aux_sym_20] = SHIFT(303),
        [ts_aux_sym_21] = SHIFT(303),
        [ts_aux_sym_22] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
    },
    [310] = {
        [ts_sym_string] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_sym__identifier] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_sym_number] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_sym_comment] = SHIFT(310),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_aux_sym_return] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_aux_sym_10] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_aux_sym_if] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_aux_sym_22] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
    },
    [311] = {
        [ts_sym_expression] = SHIFT(312),
        [ts_sym_call_expression] = SHIFT(265),
        [ts_sym_selector_expression] = SHIFT(265),
        [ts_sym_math_op] = SHIFT(265),
        [ts_sym_bool_op] = SHIFT(265),
        [ts_sym_var_name] = SHIFT(265),
        [ts_sym_string] = SHIFT(265),
        [ts_sym__identifier] = SHIFT(256),
        [ts_sym_number] = SHIFT(265),
        [ts_sym_comment] = SHIFT(311),
        [ts_aux_sym_22] = SHIFT(266),
    },
    [312] = {
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 2),
        [ts_sym_comment] = SHIFT(312),
        [ts_aux_sym_1] = SHIFT(247),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration_statement, 2),
        [ts_aux_sym_5] = REDUCE(ts_sym_declaration_statement, 2),
        [ts_aux_sym_6] = SHIFT(252),
        [ts_aux_sym_return] = REDUCE(ts_sym_declaration_statement, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_declaration_statement, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_declaration_statement, 2),
        [ts_aux_sym_11] = SHIFT(254),
        [ts_aux_sym_12] = SHIFT(252),
        [ts_aux_sym_13] = SHIFT(257),
        [ts_aux_sym_14] = SHIFT(257),
        [ts_aux_sym_15] = SHIFT(259),
        [ts_aux_sym_16] = SHIFT(261),
        [ts_aux_sym_17] = SHIFT(263),
        [ts_aux_sym_18] = SHIFT(263),
        [ts_aux_sym_19] = SHIFT(263),
        [ts_aux_sym_20] = SHIFT(263),
        [ts_aux_sym_21] = SHIFT(263),
        [ts_aux_sym_22] = REDUCE(ts_sym_declaration_statement, 2),
    },
    [313] = {
        [ts_sym_expression] = SHIFT(314),
        [ts_sym_call_expression] = SHIFT(342),
        [ts_sym_selector_expression] = SHIFT(342),
        [ts_sym_math_op] = SHIFT(342),
        [ts_sym_bool_op] = SHIFT(342),
        [ts_sym_var_name] = SHIFT(342),
        [ts_sym_string] = SHIFT(342),
        [ts_sym__identifier] = SHIFT(333),
        [ts_sym_number] = SHIFT(342),
        [ts_sym_comment] = SHIFT(313),
        [ts_aux_sym_22] = SHIFT(343),
    },
    [314] = {
        [ts_sym_block_statement] = SHIFT(315),
        [ts_sym_comment] = SHIFT(314),
        [ts_aux_sym_1] = SHIFT(321),
        [ts_aux_sym_4] = SHIFT(326),
        [ts_aux_sym_6] = SHIFT(329),
        [ts_aux_sym_11] = SHIFT(331),
        [ts_aux_sym_12] = SHIFT(329),
        [ts_aux_sym_13] = SHIFT(334),
        [ts_aux_sym_14] = SHIFT(334),
        [ts_aux_sym_15] = SHIFT(336),
        [ts_aux_sym_16] = SHIFT(338),
        [ts_aux_sym_17] = SHIFT(340),
        [ts_aux_sym_18] = SHIFT(340),
        [ts_aux_sym_19] = SHIFT(340),
        [ts_aux_sym_20] = SHIFT(340),
        [ts_aux_sym_21] = SHIFT(340),
    },
    [315] = {
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_comment] = SHIFT(315),
        [ts_aux_sym_var] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_else] = SHIFT(316),
        [ts_aux_sym_22] = REDUCE(ts_sym_if_statement, 3),
    },
    [316] = {
        [ts_sym_block_statement] = SHIFT(317),
        [ts_sym_if_statement] = SHIFT(317),
        [ts_sym_comment] = SHIFT(316),
        [ts_aux_sym_4] = SHIFT(318),
        [ts_aux_sym_if] = SHIFT(313),
    },
    [317] = {
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = SHIFT(317),
        [ts_aux_sym_var] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_5] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_return] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_if] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_22] = REDUCE(ts_sym_if_statement, 5),
    },
    [318] = {
        [ts_sym_var_declaration] = SHIFT(238),
        [ts_sym_statement] = SHIFT(239),
        [ts_sym_return_statement] = SHIFT(240),
        [ts_sym_declaration_statement] = SHIFT(240),
        [ts_sym_if_statement] = SHIFT(240),
        [ts_sym_expression_statement] = SHIFT(240),
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(243),
        [ts_builtin_sym_error] = SHIFT(319),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(272),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(318),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(319),
        [ts_aux_sym_var] = SHIFT(274),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(284),
        [ts_aux_sym_10] = SHIFT(311),
        [ts_aux_sym_if] = SHIFT(313),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [319] = {
        [ts_sym_comment] = SHIFT(319),
        [ts_aux_sym_5] = SHIFT(320),
    },
    [320] = {
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT(320),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_22] = REDUCE(ts_sym_block_statement, 3),
    },
    [321] = {
        [ts_sym_expression] = SHIFT(322),
        [ts_sym_call_expression] = SHIFT(184),
        [ts_sym_selector_expression] = SHIFT(184),
        [ts_sym_math_op] = SHIFT(184),
        [ts_sym_bool_op] = SHIFT(184),
        [ts_sym_var_name] = SHIFT(184),
        [ts_sym_string] = SHIFT(184),
        [ts_sym__identifier] = SHIFT(175),
        [ts_sym_number] = SHIFT(184),
        [ts_sym_comment] = SHIFT(321),
        [ts_aux_sym_2] = SHIFT(325),
        [ts_aux_sym_22] = SHIFT(185),
    },
    [322] = {
        [ts_sym_comment] = SHIFT(322),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(323),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_6] = SHIFT(171),
        [ts_aux_sym_9] = SHIFT(187),
        [ts_aux_sym_11] = SHIFT(173),
        [ts_aux_sym_12] = SHIFT(171),
        [ts_aux_sym_13] = SHIFT(176),
        [ts_aux_sym_14] = SHIFT(176),
        [ts_aux_sym_15] = SHIFT(178),
        [ts_aux_sym_16] = SHIFT(180),
        [ts_aux_sym_17] = SHIFT(182),
        [ts_aux_sym_18] = SHIFT(182),
        [ts_aux_sym_19] = SHIFT(182),
        [ts_aux_sym_20] = SHIFT(182),
        [ts_aux_sym_21] = SHIFT(182),
    },
    [323] = {
        [ts_sym_comment] = SHIFT(323),
        [ts_aux_sym_2] = SHIFT(324),
    },
    [324] = {
        [ts_sym_comment] = SHIFT(324),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_4] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 5),
    },
    [325] = {
        [ts_sym_comment] = SHIFT(325),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 3),
    },
    [326] = {
        [ts_sym_var_declaration] = SHIFT(238),
        [ts_sym_statement] = SHIFT(239),
        [ts_sym_return_statement] = SHIFT(240),
        [ts_sym_declaration_statement] = SHIFT(240),
        [ts_sym_if_statement] = SHIFT(240),
        [ts_sym_expression_statement] = SHIFT(240),
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_call_expression] = SHIFT(205),
        [ts_sym_selector_expression] = SHIFT(205),
        [ts_sym_math_op] = SHIFT(205),
        [ts_sym_bool_op] = SHIFT(205),
        [ts_sym_var_name] = SHIFT(243),
        [ts_builtin_sym_error] = SHIFT(327),
        [ts_sym_string] = SHIFT(205),
        [ts_sym__identifier] = SHIFT(272),
        [ts_sym_number] = SHIFT(205),
        [ts_sym_comment] = SHIFT(326),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(327),
        [ts_aux_sym_var] = SHIFT(274),
        [ts_aux_sym_5] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(284),
        [ts_aux_sym_10] = SHIFT(311),
        [ts_aux_sym_if] = SHIFT(313),
        [ts_aux_sym_22] = SHIFT(206),
    },
    [327] = {
        [ts_sym_comment] = SHIFT(327),
        [ts_aux_sym_5] = SHIFT(328),
    },
    [328] = {
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT(328),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_else] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_22] = REDUCE(ts_sym_block_statement, 3),
    },
    [329] = {
        [ts_sym_expression] = SHIFT(330),
        [ts_sym_call_expression] = SHIFT(342),
        [ts_sym_selector_expression] = SHIFT(342),
        [ts_sym_math_op] = SHIFT(342),
        [ts_sym_bool_op] = SHIFT(342),
        [ts_sym_var_name] = SHIFT(342),
        [ts_sym_string] = SHIFT(342),
        [ts_sym__identifier] = SHIFT(333),
        [ts_sym_number] = SHIFT(342),
        [ts_sym_comment] = SHIFT(329),
        [ts_aux_sym_22] = SHIFT(343),
    },
    [330] = {
        [ts_sym_comment] = SHIFT(330),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(329),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(329),
        [ts_aux_sym_13] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = SHIFT(338),
        [ts_aux_sym_17] = SHIFT(340),
        [ts_aux_sym_18] = SHIFT(340),
        [ts_aux_sym_19] = SHIFT(340),
        [ts_aux_sym_20] = SHIFT(340),
        [ts_aux_sym_21] = SHIFT(340),
    },
    [331] = {
        [ts_sym_var_name] = SHIFT(332),
        [ts_sym__identifier] = SHIFT(333),
        [ts_sym_comment] = SHIFT(331),
    },
    [332] = {
        [ts_sym_comment] = SHIFT(332),
        [ts_aux_sym_1] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_18] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_19] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_20] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_21] = REDUCE(ts_sym_selector_expression, 3),
    },
    [333] = {
        [ts_sym_comment] = SHIFT(333),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_var_name, 1),
    },
    [334] = {
        [ts_sym_expression] = SHIFT(335),
        [ts_sym_call_expression] = SHIFT(342),
        [ts_sym_selector_expression] = SHIFT(342),
        [ts_sym_math_op] = SHIFT(342),
        [ts_sym_bool_op] = SHIFT(342),
        [ts_sym_var_name] = SHIFT(342),
        [ts_sym_string] = SHIFT(342),
        [ts_sym__identifier] = SHIFT(333),
        [ts_sym_number] = SHIFT(342),
        [ts_sym_comment] = SHIFT(334),
        [ts_aux_sym_22] = SHIFT(343),
    },
    [335] = {
        [ts_sym_comment] = SHIFT(335),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_6] = SHIFT(329),
        [ts_aux_sym_11] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = SHIFT(329),
        [ts_aux_sym_13] = SHIFT(334),
        [ts_aux_sym_14] = SHIFT(334),
        [ts_aux_sym_15] = SHIFT(336),
        [ts_aux_sym_16] = SHIFT(338),
        [ts_aux_sym_17] = SHIFT(340),
        [ts_aux_sym_18] = SHIFT(340),
        [ts_aux_sym_19] = SHIFT(340),
        [ts_aux_sym_20] = SHIFT(340),
        [ts_aux_sym_21] = SHIFT(340),
    },
    [336] = {
        [ts_sym_expression] = SHIFT(337),
        [ts_sym_call_expression] = SHIFT(342),
        [ts_sym_selector_expression] = SHIFT(342),
        [ts_sym_math_op] = SHIFT(342),
        [ts_sym_bool_op] = SHIFT(342),
        [ts_sym_var_name] = SHIFT(342),
        [ts_sym_string] = SHIFT(342),
        [ts_sym__identifier] = SHIFT(333),
        [ts_sym_number] = SHIFT(342),
        [ts_sym_comment] = SHIFT(336),
        [ts_aux_sym_22] = SHIFT(343),
    },
    [337] = {
        [ts_sym_comment] = SHIFT(337),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(329),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(329),
        [ts_aux_sym_13] = SHIFT(334),
        [ts_aux_sym_14] = SHIFT(334),
        [ts_aux_sym_15] = SHIFT(336),
        [ts_aux_sym_16] = SHIFT(338),
        [ts_aux_sym_17] = SHIFT(340),
        [ts_aux_sym_18] = SHIFT(340),
        [ts_aux_sym_19] = SHIFT(340),
        [ts_aux_sym_20] = SHIFT(340),
        [ts_aux_sym_21] = SHIFT(340),
    },
    [338] = {
        [ts_sym_expression] = SHIFT(339),
        [ts_sym_call_expression] = SHIFT(342),
        [ts_sym_selector_expression] = SHIFT(342),
        [ts_sym_math_op] = SHIFT(342),
        [ts_sym_bool_op] = SHIFT(342),
        [ts_sym_var_name] = SHIFT(342),
        [ts_sym_string] = SHIFT(342),
        [ts_sym__identifier] = SHIFT(333),
        [ts_sym_number] = SHIFT(342),
        [ts_sym_comment] = SHIFT(338),
        [ts_aux_sym_22] = SHIFT(343),
    },
    [339] = {
        [ts_sym_comment] = SHIFT(339),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = SHIFT(329),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = SHIFT(329),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = SHIFT(338),
        [ts_aux_sym_17] = SHIFT(340),
        [ts_aux_sym_18] = SHIFT(340),
        [ts_aux_sym_19] = SHIFT(340),
        [ts_aux_sym_20] = SHIFT(340),
        [ts_aux_sym_21] = SHIFT(340),
    },
    [340] = {
        [ts_sym_expression] = SHIFT(341),
        [ts_sym_call_expression] = SHIFT(342),
        [ts_sym_selector_expression] = SHIFT(342),
        [ts_sym_math_op] = SHIFT(342),
        [ts_sym_bool_op] = SHIFT(342),
        [ts_sym_var_name] = SHIFT(342),
        [ts_sym_string] = SHIFT(342),
        [ts_sym__identifier] = SHIFT(333),
        [ts_sym_number] = SHIFT(342),
        [ts_sym_comment] = SHIFT(340),
        [ts_aux_sym_22] = SHIFT(343),
    },
    [341] = {
        [ts_sym_comment] = SHIFT(341),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(340),
        [ts_aux_sym_18] = SHIFT(340),
        [ts_aux_sym_19] = SHIFT(340),
        [ts_aux_sym_20] = SHIFT(340),
        [ts_aux_sym_21] = SHIFT(340),
    },
    [342] = {
        [ts_sym_comment] = SHIFT(342),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_12] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_13] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_14] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_15] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_16] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_17] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_18] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_19] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_20] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_21] = REDUCE(ts_sym_expression, 1),
    },
    [343] = {
        [ts_sym_expression] = SHIFT(344),
        [ts_sym_call_expression] = SHIFT(342),
        [ts_sym_selector_expression] = SHIFT(342),
        [ts_sym_math_op] = SHIFT(342),
        [ts_sym_bool_op] = SHIFT(342),
        [ts_sym_var_name] = SHIFT(342),
        [ts_sym_string] = SHIFT(342),
        [ts_sym__identifier] = SHIFT(333),
        [ts_sym_number] = SHIFT(342),
        [ts_sym_comment] = SHIFT(343),
        [ts_aux_sym_22] = SHIFT(343),
    },
    [344] = {
        [ts_sym_comment] = SHIFT(344),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_17] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_18] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_19] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_20] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_21] = REDUCE(ts_sym_bool_op, 2),
    },
    [345] = {
        [ts_sym_comment] = SHIFT(345),
        [ts_aux_sym_5] = SHIFT(346),
    },
    [346] = {
        [ts_sym__terminator] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT(346),
    },
    [347] = {
        [ts_sym_var_name] = SHIFT(348),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT(347),
        [ts_aux_sym_2] = SHIFT(363),
    },
    [348] = {
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT(348),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(349),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_9] = SHIFT(135),
    },
    [349] = {
        [ts_sym_type_expression] = SHIFT(350),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(349),
        [ts_aux_sym_6] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_7] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [350] = {
        [ts_sym_comment] = SHIFT(350),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(351),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_9] = SHIFT(87),
    },
    [351] = {
        [ts_sym_comment] = SHIFT(351),
        [ts_aux_sym_2] = SHIFT(352),
    },
    [352] = {
        [ts_sym_type_name] = SHIFT(353),
        [ts_sym__identifier] = SHIFT(354),
        [ts_sym_comment] = SHIFT(352),
        [ts_aux_sym_1] = SHIFT(355),
        [ts_aux_sym_4] = REDUCE(ts_sym__func_signature, 6),
    },
    [353] = {
        [ts_sym_comment] = SHIFT(353),
        [ts_aux_sym_4] = REDUCE(ts_sym__func_signature, 7),
    },
    [354] = {
        [ts_sym_comment] = SHIFT(354),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_name, 1),
    },
    [355] = {
        [ts_sym_var_name] = SHIFT(356),
        [ts_sym_type_name] = SHIFT(360),
        [ts_sym__identifier] = SHIFT(86),
        [ts_sym_comment] = SHIFT(355),
    },
    [356] = {
        [ts_sym_type_name] = SHIFT(357),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(356),
    },
    [357] = {
        [ts_sym_comment] = SHIFT(357),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(358),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_9] = SHIFT(74),
    },
    [358] = {
        [ts_sym_comment] = SHIFT(358),
        [ts_aux_sym_2] = SHIFT(359),
    },
    [359] = {
        [ts_sym_comment] = SHIFT(359),
        [ts_aux_sym_4] = REDUCE(ts_sym__func_signature, 11),
    },
    [360] = {
        [ts_sym_comment] = SHIFT(360),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(361),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_9] = SHIFT(83),
    },
    [361] = {
        [ts_sym_comment] = SHIFT(361),
        [ts_aux_sym_2] = SHIFT(362),
    },
    [362] = {
        [ts_sym_comment] = SHIFT(362),
        [ts_aux_sym_4] = REDUCE(ts_sym__func_signature, 10),
    },
    [363] = {
        [ts_sym_type_name] = SHIFT(364),
        [ts_sym__identifier] = SHIFT(354),
        [ts_sym_comment] = SHIFT(363),
        [ts_aux_sym_1] = SHIFT(365),
        [ts_aux_sym_4] = REDUCE(ts_sym__func_signature, 2),
    },
    [364] = {
        [ts_sym_comment] = SHIFT(364),
        [ts_aux_sym_4] = REDUCE(ts_sym__func_signature, 3),
    },
    [365] = {
        [ts_sym_var_name] = SHIFT(366),
        [ts_sym_type_name] = SHIFT(369),
        [ts_sym__identifier] = SHIFT(86),
        [ts_sym_comment] = SHIFT(365),
    },
    [366] = {
        [ts_sym_type_name] = SHIFT(367),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT(366),
    },
    [367] = {
        [ts_sym_comment] = SHIFT(367),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(368),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_9] = SHIFT(74),
    },
    [368] = {
        [ts_sym_comment] = SHIFT(368),
        [ts_aux_sym_2] = SHIFT(353),
    },
    [369] = {
        [ts_sym_comment] = SHIFT(369),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(370),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_9] = SHIFT(83),
    },
    [370] = {
        [ts_sym_comment] = SHIFT(370),
        [ts_aux_sym_2] = SHIFT(371),
    },
    [371] = {
        [ts_sym_comment] = SHIFT(371),
        [ts_aux_sym_4] = REDUCE(ts_sym__func_signature, 6),
    },
    [372] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
        [ts_sym_comment] = SHIFT(372),
    },
    [373] = {
        [ts_sym_package_name] = SHIFT(374),
        [ts_sym__identifier] = SHIFT(375),
        [ts_sym_comment] = SHIFT(373),
    },
    [374] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym_comment] = SHIFT(374),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_directive, 2),
    },
    [375] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
        [ts_sym_comment] = SHIFT(375),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_name, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_golang);
