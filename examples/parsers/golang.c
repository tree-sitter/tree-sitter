#include "tree_sitter/parser.h"

#define STATE_COUNT 372
#define SYMBOL_COUNT 87

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
    ts_sym_range_statement,
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
    ts_sym__line_break,
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
    ts_aux_sym_3,
    ts_aux_sym_var,
    ts_aux_sym_4,
    ts_aux_sym_func,
    ts_aux_sym_5,
    ts_aux_sym_6,
    ts_aux_sym_7,
    ts_aux_sym_map,
    ts_aux_sym_8,
    ts_aux_sym_9,
    ts_aux_sym_struct,
    ts_aux_sym_interface,
    ts_aux_sym_return,
    ts_aux_sym_10,
    ts_aux_sym_11,
    ts_aux_sym_for,
    ts_aux_sym_range,
    ts_aux_sym_if,
    ts_aux_sym_else,
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
    ts_aux_sym_23,
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
    [ts_sym_range_statement] = "range_statement",
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
    [ts_sym__line_break] = "_line_break",
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
    [ts_aux_sym_3] = "';'",
    [ts_aux_sym_var] = "'var'",
    [ts_aux_sym_4] = "'='",
    [ts_aux_sym_func] = "'func'",
    [ts_aux_sym_5] = "'{'",
    [ts_aux_sym_6] = "'}'",
    [ts_aux_sym_7] = "'*'",
    [ts_aux_sym_map] = "'map'",
    [ts_aux_sym_8] = "'['",
    [ts_aux_sym_9] = "']'",
    [ts_aux_sym_struct] = "'struct'",
    [ts_aux_sym_interface] = "'interface'",
    [ts_aux_sym_return] = "'return'",
    [ts_aux_sym_10] = "','",
    [ts_aux_sym_11] = "':='",
    [ts_aux_sym_for] = "'for'",
    [ts_aux_sym_range] = "'range'",
    [ts_aux_sym_if] = "'if'",
    [ts_aux_sym_else] = "'else'",
    [ts_aux_sym_12] = "'.'",
    [ts_aux_sym_13] = "'/'",
    [ts_aux_sym_14] = "'+'",
    [ts_aux_sym_15] = "'-'",
    [ts_aux_sym_16] = "'||'",
    [ts_aux_sym_17] = "'&&'",
    [ts_aux_sym_18] = "'=='",
    [ts_aux_sym_19] = "'<='",
    [ts_aux_sym_20] = "'<'",
    [ts_aux_sym_21] = "'>='",
    [ts_aux_sym_22] = "'>'",
    [ts_aux_sym_23] = "'!'",
};

HIDDEN_SYMBOLS = {
    [ts_sym__func_signature] = 1,
    [ts_sym__line_break] = 1,
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
    [ts_aux_sym_3] = 1,
    [ts_aux_sym_var] = 1,
    [ts_aux_sym_4] = 1,
    [ts_aux_sym_func] = 1,
    [ts_aux_sym_5] = 1,
    [ts_aux_sym_6] = 1,
    [ts_aux_sym_7] = 1,
    [ts_aux_sym_map] = 1,
    [ts_aux_sym_8] = 1,
    [ts_aux_sym_9] = 1,
    [ts_aux_sym_struct] = 1,
    [ts_aux_sym_interface] = 1,
    [ts_aux_sym_return] = 1,
    [ts_aux_sym_10] = 1,
    [ts_aux_sym_11] = 1,
    [ts_aux_sym_for] = 1,
    [ts_aux_sym_range] = 1,
    [ts_aux_sym_if] = 1,
    [ts_aux_sym_else] = 1,
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
    [ts_aux_sym_23] = 1,
};

LEX_FN() {
    START_LEXER();
    switch (lex_state) {
        case 1:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(1);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'p')
                ADVANCE(5);
            LEX_ERROR();
        case 2:
            ACCEPT_TOKEN(ts_sym__line_break);
        case 3:
            if (lookahead == '/')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (!(lookahead == '\n'))
                ADVANCE(4);
            ACCEPT_TOKEN(ts_sym_comment);
        case 5:
            if (lookahead == 'a')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (lookahead == 'c')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (lookahead == 'k')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'a')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (lookahead == 'g')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            if (lookahead == 'e')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            ACCEPT_TOKEN(ts_aux_sym_package);
        case 12:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(12);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 13:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 14:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(14);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(19);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            LEX_ERROR();
        case 15:
            if (lookahead == 'u')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            if (lookahead == 'n')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            if (lookahead == 'c')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            ACCEPT_TOKEN(ts_aux_sym_func);
        case 19:
            if (lookahead == 'm')
                ADVANCE(20);
            LEX_ERROR();
        case 20:
            if (lookahead == 'p')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if (lookahead == 'o')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            if (lookahead == 'r')
                ADVANCE(23);
            LEX_ERROR();
        case 23:
            if (lookahead == 't')
                ADVANCE(24);
            LEX_ERROR();
        case 24:
            ACCEPT_TOKEN(ts_aux_sym_import);
        case 25:
            if (lookahead == 'y')
                ADVANCE(26);
            LEX_ERROR();
        case 26:
            if (lookahead == 'p')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            if (lookahead == 'e')
                ADVANCE(28);
            LEX_ERROR();
        case 28:
            ACCEPT_TOKEN(ts_aux_sym_type);
        case 29:
            if (lookahead == 'a')
                ADVANCE(30);
            LEX_ERROR();
        case 30:
            if (lookahead == 'r')
                ADVANCE(31);
            LEX_ERROR();
        case 31:
            ACCEPT_TOKEN(ts_aux_sym_var);
        case 32:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(32);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            LEX_ERROR();
        case 33:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(33);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 34:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(34);
            if (lookahead == '\"')
                ADVANCE(35);
            if (lookahead == '\\')
                ADVANCE(36);
            LEX_ERROR();
        case 35:
            ACCEPT_TOKEN(ts_sym_string);
        case 36:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(34);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '\\')
                ADVANCE(36);
            LEX_ERROR();
        case 37:
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(34);
            if (lookahead == '\"')
                ADVANCE(35);
            if (lookahead == '\\')
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_string);
        case 38:
            ACCEPT_TOKEN(ts_aux_sym_1);
        case 39:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(39);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 40:
            ACCEPT_TOKEN(ts_aux_sym_2);
        case 41:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(41);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 42:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(42);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            LEX_ERROR();
        case 43:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 44:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(44);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(45);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == '[')
                ADVANCE(46);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'm')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(59);
            LEX_ERROR();
        case 45:
            ACCEPT_TOKEN(ts_aux_sym_7);
        case 46:
            ACCEPT_TOKEN(ts_aux_sym_8);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'n')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 't')
                ADVANCE(49);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'e')
                ADVANCE(50);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'r')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'f')
                ADVANCE(52);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'a')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'c')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'e')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_interface);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'a')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'p')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_map);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 't')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'r')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'u')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'c')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 't')
                ADVANCE(64);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_struct);
        case 65:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(65);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(66);
            LEX_ERROR();
        case 66:
            ACCEPT_TOKEN(ts_aux_sym_3);
        case 67:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(67);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            LEX_ERROR();
        case 68:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '[')
                ADVANCE(46);
            LEX_ERROR();
        case 69:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ']')
                ADVANCE(70);
            LEX_ERROR();
        case 70:
            ACCEPT_TOKEN(ts_aux_sym_9);
        case 71:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '{')
                ADVANCE(72);
            LEX_ERROR();
        case 72:
            ACCEPT_TOKEN(ts_aux_sym_5);
        case 73:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 74:
            ACCEPT_TOKEN(ts_aux_sym_6);
        case 75:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(75);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 76:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 77:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            LEX_ERROR();
        case 78:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(45);
            if (lookahead == ',')
                ADVANCE(79);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == '[')
                ADVANCE(46);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'm')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(59);
            LEX_ERROR();
        case 79:
            ACCEPT_TOKEN(ts_aux_sym_10);
        case 80:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == ',')
                ADVANCE(79);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 82:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == ',')
                ADVANCE(79);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            LEX_ERROR();
        case 83:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(45);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(84);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == '[')
                ADVANCE(46);
            if (lookahead == 'i')
                ADVANCE(47);
            if (lookahead == 'm')
                ADVANCE(56);
            if (lookahead == 's')
                ADVANCE(59);
            LEX_ERROR();
        case 84:
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 85:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(85);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '=')
                ADVANCE(84);
            LEX_ERROR();
        case 86:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(86);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '=')
                ADVANCE(84);
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            LEX_ERROR();
        case 87:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(87);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            LEX_ERROR();
        case 88:
            ACCEPT_TOKEN(ts_aux_sym_23);
        case 89:
            if (lookahead == '.')
                ADVANCE(90);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            ACCEPT_TOKEN(ts_sym_number);
        case 90:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(91);
            LEX_ERROR();
        case 91:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(91);
            ACCEPT_TOKEN(ts_sym_number);
        case 92:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(92);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '*')
                ADVANCE(45);
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
        case 93:
            if (lookahead == '&')
                ADVANCE(94);
            LEX_ERROR();
        case 94:
            ACCEPT_TOKEN(ts_aux_sym_17);
        case 95:
            ACCEPT_TOKEN(ts_aux_sym_14);
        case 96:
            ACCEPT_TOKEN(ts_aux_sym_15);
        case 97:
            ACCEPT_TOKEN(ts_aux_sym_12);
        case 98:
            if (lookahead == '/')
                ADVANCE(4);
            ACCEPT_TOKEN(ts_aux_sym_13);
        case 99:
            if (lookahead == '=')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_aux_sym_20);
        case 100:
            ACCEPT_TOKEN(ts_aux_sym_19);
        case 101:
            if (lookahead == '=')
                ADVANCE(102);
            LEX_ERROR();
        case 102:
            ACCEPT_TOKEN(ts_aux_sym_18);
        case 103:
            if (lookahead == '=')
                ADVANCE(104);
            ACCEPT_TOKEN(ts_aux_sym_22);
        case 104:
            ACCEPT_TOKEN(ts_aux_sym_21);
        case 105:
            if (lookahead == '|')
                ADVANCE(106);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(ts_aux_sym_16);
        case 107:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(107);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '*')
                ADVANCE(45);
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
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            if (lookahead == '|')
                ADVANCE(105);
            LEX_ERROR();
        case 108:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            LEX_ERROR();
        case 109:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(45);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(79);
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
        case 110:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(110);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (lookahead == ':')
                ADVANCE(111);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'f')
                ADVANCE(113);
            if (lookahead == 'i')
                ADVANCE(116);
            if (lookahead == 'r')
                ADVANCE(118);
            if (lookahead == 'v')
                ADVANCE(124);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 111:
            if (lookahead == '=')
                ADVANCE(112);
            LEX_ERROR();
        case 112:
            ACCEPT_TOKEN(ts_aux_sym_11);
        case 113:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'o')
                ADVANCE(114);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 114:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'r')
                ADVANCE(115);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 115:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_for);
        case 116:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'f')
                ADVANCE(117);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 117:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 118:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'e')
                ADVANCE(119);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 119:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 't')
                ADVANCE(120);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 120:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'u')
                ADVANCE(121);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 121:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'r')
                ADVANCE(122);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 122:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'n')
                ADVANCE(123);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 123:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_return);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'a')
                ADVANCE(125);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'r')
                ADVANCE(126);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 126:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_var);
        case 127:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '*')
                ADVANCE(45);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (lookahead == ':')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(101);
            if (lookahead == '>')
                ADVANCE(103);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'f')
                ADVANCE(113);
            if (lookahead == 'i')
                ADVANCE(116);
            if (lookahead == 'r')
                ADVANCE(118);
            if (lookahead == 'v')
                ADVANCE(124);
            if (lookahead == '|')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 128:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '*')
                ADVANCE(45);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(79);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if (lookahead == ':')
                ADVANCE(111);
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
        case 129:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(111);
            LEX_ERROR();
        case 130:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(79);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(111);
            LEX_ERROR();
        case 131:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(131);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (lookahead == ':')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '=')
                ADVANCE(84);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'f')
                ADVANCE(113);
            if (lookahead == 'i')
                ADVANCE(116);
            if (lookahead == 'r')
                ADVANCE(118);
            if (lookahead == 'v')
                ADVANCE(124);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 132:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (lookahead == ';')
                ADVANCE(66);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            LEX_ERROR();
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '*')
                ADVANCE(45);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(79);
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
        case 134:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (lookahead == ':')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(66);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'f')
                ADVANCE(113);
            if (lookahead == 'i')
                ADVANCE(116);
            if (lookahead == 'r')
                ADVANCE(118);
            if (lookahead == 'v')
                ADVANCE(124);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'r')
                ADVANCE(136);
            LEX_ERROR();
        case 136:
            if (lookahead == 'a')
                ADVANCE(137);
            LEX_ERROR();
        case 137:
            if (lookahead == 'n')
                ADVANCE(138);
            LEX_ERROR();
        case 138:
            if (lookahead == 'g')
                ADVANCE(139);
            LEX_ERROR();
        case 139:
            if (lookahead == 'e')
                ADVANCE(140);
            LEX_ERROR();
        case 140:
            ACCEPT_TOKEN(ts_aux_sym_range);
        case 141:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '*')
                ADVANCE(45);
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
                ADVANCE(72);
            if (lookahead == '|')
                ADVANCE(105);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (lookahead == ':')
                ADVANCE(111);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('g' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'e')
                ADVANCE(143);
            if (lookahead == 'f')
                ADVANCE(113);
            if (lookahead == 'i')
                ADVANCE(116);
            if (lookahead == 'r')
                ADVANCE(118);
            if (lookahead == 'v')
                ADVANCE(124);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 143:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'l')
                ADVANCE(144);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 144:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 's')
                ADVANCE(145);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 145:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'e')
                ADVANCE(146);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 146:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_else);
        case 147:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(147);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'i')
                ADVANCE(148);
            if (lookahead == '{')
                ADVANCE(72);
            LEX_ERROR();
        case 148:
            if (lookahead == 'f')
                ADVANCE(149);
            LEX_ERROR();
        case 149:
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 150:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(150);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == '{')
                ADVANCE(72);
            LEX_ERROR();
        case 151:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(151);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(45);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(79);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (lookahead == ':')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(152);
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
                ADVANCE(43);
            if (lookahead == '[')
                ADVANCE(46);
            if (lookahead == ']')
                ADVANCE(70);
            if (lookahead == 'e')
                ADVANCE(143);
            if (lookahead == 'f')
                ADVANCE(153);
            if (lookahead == 'i')
                ADVANCE(157);
            if (lookahead == 'm')
                ADVANCE(56);
            if (lookahead == 'p')
                ADVANCE(163);
            if (lookahead == 'r')
                ADVANCE(170);
            if (lookahead == 's')
                ADVANCE(59);
            if (lookahead == 't')
                ADVANCE(175);
            if (lookahead == 'v')
                ADVANCE(124);
            if (lookahead == '{')
                ADVANCE(72);
            if (lookahead == '|')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        case 152:
            if (lookahead == '=')
                ADVANCE(102);
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 153:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'o')
                ADVANCE(114);
            if (lookahead == 'u')
                ADVANCE(154);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 154:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'n')
                ADVANCE(155);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 155:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'c')
                ADVANCE(156);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 156:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_func);
        case 157:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'f')
                ADVANCE(117);
            if (lookahead == 'm')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(48);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 158:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'p')
                ADVANCE(159);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 159:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'o')
                ADVANCE(160);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 160:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'r')
                ADVANCE(161);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 161:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 't')
                ADVANCE(162);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 162:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_import);
        case 163:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'a')
                ADVANCE(164);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 164:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'c')
                ADVANCE(165);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 165:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'k')
                ADVANCE(166);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 166:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'a')
                ADVANCE(167);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 167:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'g')
                ADVANCE(168);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 168:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'e')
                ADVANCE(169);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 169:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_package);
        case 170:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'a')
                ADVANCE(171);
            if (lookahead == 'e')
                ADVANCE(119);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 171:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'n')
                ADVANCE(172);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 172:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'g')
                ADVANCE(173);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 173:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'e')
                ADVANCE(174);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 174:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_range);
        case 175:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(43);
            if (lookahead == 'y')
                ADVANCE(176);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 176:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'p')
                ADVANCE(177);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 177:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            if (lookahead == 'e')
                ADVANCE(178);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 178:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(43);
            ACCEPT_TOKEN(ts_aux_sym_type);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == '\0')
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(151);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(88);
            if (lookahead == '\"')
                ADVANCE(34);
            if (lookahead == '&')
                ADVANCE(93);
            if (lookahead == '(')
                ADVANCE(38);
            if (lookahead == ')')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(45);
            if (lookahead == '+')
                ADVANCE(95);
            if (lookahead == ',')
                ADVANCE(79);
            if (lookahead == '-')
                ADVANCE(96);
            if (lookahead == '.')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(98);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(89);
            if (lookahead == ':')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(66);
            if (lookahead == '<')
                ADVANCE(99);
            if (lookahead == '=')
                ADVANCE(152);
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
                ADVANCE(43);
            if (lookahead == '[')
                ADVANCE(46);
            if (lookahead == ']')
                ADVANCE(70);
            if (lookahead == 'e')
                ADVANCE(143);
            if (lookahead == 'f')
                ADVANCE(153);
            if (lookahead == 'i')
                ADVANCE(157);
            if (lookahead == 'm')
                ADVANCE(56);
            if (lookahead == 'p')
                ADVANCE(163);
            if (lookahead == 'r')
                ADVANCE(170);
            if (lookahead == 's')
                ADVANCE(59);
            if (lookahead == 't')
                ADVANCE(175);
            if (lookahead == 'v')
                ADVANCE(124);
            if (lookahead == '{')
                ADVANCE(72);
            if (lookahead == '|')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(74);
            LEX_ERROR();
        default:
            LEX_PANIC();
    }
}

LEX_STATES = {
    [0] = 1,
    [1] = 12,
    [2] = 14,
    [3] = 14,
    [4] = 32,
    [5] = 33,
    [6] = 14,
    [7] = 14,
    [8] = 39,
    [9] = 39,
    [10] = 39,
    [11] = 41,
    [12] = 41,
    [13] = 14,
    [14] = 32,
    [15] = 32,
    [16] = 32,
    [17] = 12,
    [18] = 42,
    [19] = 44,
    [20] = 65,
    [21] = 67,
    [22] = 65,
    [23] = 65,
    [24] = 44,
    [25] = 65,
    [26] = 68,
    [27] = 44,
    [28] = 69,
    [29] = 44,
    [30] = 65,
    [31] = 69,
    [32] = 44,
    [33] = 65,
    [34] = 71,
    [35] = 73,
    [36] = 44,
    [37] = 73,
    [38] = 44,
    [39] = 75,
    [40] = 73,
    [41] = 73,
    [42] = 44,
    [43] = 73,
    [44] = 68,
    [45] = 44,
    [46] = 69,
    [47] = 44,
    [48] = 73,
    [49] = 69,
    [50] = 44,
    [51] = 73,
    [52] = 71,
    [53] = 73,
    [54] = 75,
    [55] = 73,
    [56] = 71,
    [57] = 73,
    [58] = 76,
    [59] = 73,
    [60] = 76,
    [61] = 75,
    [62] = 77,
    [63] = 78,
    [64] = 44,
    [65] = 80,
    [66] = 41,
    [67] = 81,
    [68] = 73,
    [69] = 42,
    [70] = 42,
    [71] = 80,
    [72] = 41,
    [73] = 73,
    [74] = 42,
    [75] = 42,
    [76] = 80,
    [77] = 41,
    [78] = 80,
    [79] = 42,
    [80] = 80,
    [81] = 41,
    [82] = 73,
    [83] = 42,
    [84] = 80,
    [85] = 41,
    [86] = 82,
    [87] = 42,
    [88] = 78,
    [89] = 44,
    [90] = 80,
    [91] = 41,
    [92] = 80,
    [93] = 44,
    [94] = 80,
    [95] = 68,
    [96] = 44,
    [97] = 69,
    [98] = 44,
    [99] = 80,
    [100] = 69,
    [101] = 44,
    [102] = 80,
    [103] = 71,
    [104] = 73,
    [105] = 75,
    [106] = 80,
    [107] = 71,
    [108] = 73,
    [109] = 75,
    [110] = 80,
    [111] = 69,
    [112] = 69,
    [113] = 44,
    [114] = 69,
    [115] = 68,
    [116] = 44,
    [117] = 69,
    [118] = 44,
    [119] = 69,
    [120] = 69,
    [121] = 44,
    [122] = 69,
    [123] = 71,
    [124] = 73,
    [125] = 75,
    [126] = 69,
    [127] = 71,
    [128] = 73,
    [129] = 75,
    [130] = 69,
    [131] = 42,
    [132] = 78,
    [133] = 44,
    [134] = 78,
    [135] = 42,
    [136] = 78,
    [137] = 44,
    [138] = 81,
    [139] = 73,
    [140] = 42,
    [141] = 42,
    [142] = 80,
    [143] = 41,
    [144] = 80,
    [145] = 41,
    [146] = 73,
    [147] = 75,
    [148] = 73,
    [149] = 75,
    [150] = 65,
    [151] = 71,
    [152] = 73,
    [153] = 75,
    [154] = 65,
    [155] = 44,
    [156] = 42,
    [157] = 83,
    [158] = 85,
    [159] = 86,
    [160] = 87,
    [161] = 92,
    [162] = 107,
    [163] = 108,
    [164] = 109,
    [165] = 41,
    [166] = 92,
    [167] = 108,
    [168] = 109,
    [169] = 41,
    [170] = 109,
    [171] = 87,
    [172] = 109,
    [173] = 87,
    [174] = 109,
    [175] = 87,
    [176] = 109,
    [177] = 109,
    [178] = 109,
    [179] = 87,
    [180] = 109,
    [181] = 87,
    [182] = 109,
    [183] = 41,
    [184] = 42,
    [185] = 109,
    [186] = 87,
    [187] = 109,
    [188] = 87,
    [189] = 109,
    [190] = 109,
    [191] = 92,
    [192] = 87,
    [193] = 92,
    [194] = 87,
    [195] = 92,
    [196] = 87,
    [197] = 92,
    [198] = 92,
    [199] = 92,
    [200] = 87,
    [201] = 92,
    [202] = 42,
    [203] = 92,
    [204] = 87,
    [205] = 92,
    [206] = 87,
    [207] = 92,
    [208] = 85,
    [209] = 85,
    [210] = 87,
    [211] = 92,
    [212] = 107,
    [213] = 44,
    [214] = 85,
    [215] = 68,
    [216] = 44,
    [217] = 69,
    [218] = 44,
    [219] = 85,
    [220] = 69,
    [221] = 44,
    [222] = 85,
    [223] = 71,
    [224] = 73,
    [225] = 75,
    [226] = 85,
    [227] = 71,
    [228] = 73,
    [229] = 75,
    [230] = 85,
    [231] = 83,
    [232] = 42,
    [233] = 76,
    [234] = 71,
    [235] = 65,
    [236] = 67,
    [237] = 110,
    [238] = 110,
    [239] = 110,
    [240] = 110,
    [241] = 92,
    [242] = 127,
    [243] = 128,
    [244] = 129,
    [245] = 87,
    [246] = 92,
    [247] = 127,
    [248] = 42,
    [249] = 130,
    [250] = 129,
    [251] = 130,
    [252] = 128,
    [253] = 75,
    [254] = 42,
    [255] = 83,
    [256] = 85,
    [257] = 131,
    [258] = 87,
    [259] = 92,
    [260] = 127,
    [261] = 87,
    [262] = 92,
    [263] = 127,
    [264] = 132,
    [265] = 133,
    [266] = 65,
    [267] = 134,
    [268] = 108,
    [269] = 109,
    [270] = 41,
    [271] = 133,
    [272] = 133,
    [273] = 87,
    [274] = 133,
    [275] = 87,
    [276] = 133,
    [277] = 87,
    [278] = 133,
    [279] = 133,
    [280] = 133,
    [281] = 87,
    [282] = 133,
    [283] = 87,
    [284] = 133,
    [285] = 65,
    [286] = 42,
    [287] = 133,
    [288] = 87,
    [289] = 133,
    [290] = 87,
    [291] = 133,
    [292] = 134,
    [293] = 87,
    [294] = 92,
    [295] = 127,
    [296] = 42,
    [297] = 130,
    [298] = 42,
    [299] = 129,
    [300] = 135,
    [301] = 87,
    [302] = 141,
    [303] = 110,
    [304] = 108,
    [305] = 109,
    [306] = 41,
    [307] = 141,
    [308] = 141,
    [309] = 110,
    [310] = 75,
    [311] = 110,
    [312] = 87,
    [313] = 141,
    [314] = 142,
    [315] = 147,
    [316] = 110,
    [317] = 110,
    [318] = 75,
    [319] = 142,
    [320] = 87,
    [321] = 141,
    [322] = 87,
    [323] = 141,
    [324] = 87,
    [325] = 141,
    [326] = 141,
    [327] = 141,
    [328] = 87,
    [329] = 141,
    [330] = 42,
    [331] = 141,
    [332] = 87,
    [333] = 141,
    [334] = 87,
    [335] = 141,
    [336] = 129,
    [337] = 135,
    [338] = 87,
    [339] = 141,
    [340] = 110,
    [341] = 75,
    [342] = 65,
    [343] = 77,
    [344] = 78,
    [345] = 44,
    [346] = 80,
    [347] = 41,
    [348] = 150,
    [349] = 71,
    [350] = 71,
    [351] = 42,
    [352] = 42,
    [353] = 80,
    [354] = 41,
    [355] = 71,
    [356] = 80,
    [357] = 41,
    [358] = 71,
    [359] = 150,
    [360] = 71,
    [361] = 42,
    [362] = 42,
    [363] = 80,
    [364] = 41,
    [365] = 80,
    [366] = 41,
    [367] = 71,
    [368] = 12,
    [369] = 42,
    [370] = 14,
    [371] = 14,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_program] = SHIFT(1),
        [ts_sym_package_directive] = SHIFT(2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_package] = SHIFT(369),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [2] = {
        [ts_sym_imports_block] = SHIFT(3),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = SHIFT(14),
        [ts_aux_sym_import] = SHIFT(5),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [3] = {
        [ts_sym_imports_block] = SHIFT(3),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = SHIFT(4),
        [ts_aux_sym_import] = SHIFT(5),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [4] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
    [5] = {
        [ts_sym_package_import] = SHIFT(6),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(7),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(8),
    },
    [6] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 2),
    },
    [7] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_import, 1),
    },
    [8] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_builtin_sym_error] = SHIFT(12),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(10),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(12),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [9] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(10),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(11),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [10] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_package_import, 1),
    },
    [11] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 2),
    },
    [12] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(13),
    },
    [13] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
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
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = SHIFT(368),
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
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = SHIFT(17),
        [ts_aux_sym_type] = SHIFT(18),
        [ts_aux_sym_var] = SHIFT(156),
        [ts_aux_sym_func] = SHIFT(232),
    },
    [16] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_declaration, 1),
    },
    [17] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [18] = {
        [ts_sym_type_name] = SHIFT(19),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(155),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [19] = {
        [ts_sym_type_expression] = SHIFT(20),
        [ts_sym_pointer_type] = SHIFT(22),
        [ts_sym_map_type] = SHIFT(22),
        [ts_sym_slice_type] = SHIFT(22),
        [ts_sym_struct_type] = SHIFT(22),
        [ts_sym_interface_type] = SHIFT(22),
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(24),
        [ts_aux_sym_map] = SHIFT(26),
        [ts_aux_sym_8] = SHIFT(31),
        [ts_aux_sym_struct] = SHIFT(34),
        [ts_aux_sym_interface] = SHIFT(151),
    },
    [20] = {
        [ts_sym__line_break] = SHIFT(21),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(21),
    },
    [21] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_type_declaration, 4),
    },
    [22] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
    },
    [23] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_name, 1),
    },
    [24] = {
        [ts_sym_type_expression] = SHIFT(25),
        [ts_sym_pointer_type] = SHIFT(22),
        [ts_sym_map_type] = SHIFT(22),
        [ts_sym_slice_type] = SHIFT(22),
        [ts_sym_struct_type] = SHIFT(22),
        [ts_sym_interface_type] = SHIFT(22),
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(24),
        [ts_aux_sym_map] = SHIFT(26),
        [ts_aux_sym_8] = SHIFT(31),
        [ts_aux_sym_struct] = SHIFT(34),
        [ts_aux_sym_interface] = SHIFT(151),
    },
    [25] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
    },
    [26] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(27),
    },
    [27] = {
        [ts_sym_type_expression] = SHIFT(28),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_8] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [28] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(29),
    },
    [29] = {
        [ts_sym_type_expression] = SHIFT(30),
        [ts_sym_pointer_type] = SHIFT(22),
        [ts_sym_map_type] = SHIFT(22),
        [ts_sym_slice_type] = SHIFT(22),
        [ts_sym_struct_type] = SHIFT(22),
        [ts_sym_interface_type] = SHIFT(22),
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(24),
        [ts_aux_sym_map] = SHIFT(26),
        [ts_aux_sym_8] = SHIFT(31),
        [ts_aux_sym_struct] = SHIFT(34),
        [ts_aux_sym_interface] = SHIFT(151),
    },
    [30] = {
        [ts_sym__line_break] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
    },
    [31] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(32),
    },
    [32] = {
        [ts_sym_type_expression] = SHIFT(33),
        [ts_sym_pointer_type] = SHIFT(22),
        [ts_sym_map_type] = SHIFT(22),
        [ts_sym_slice_type] = SHIFT(22),
        [ts_sym_struct_type] = SHIFT(22),
        [ts_sym_interface_type] = SHIFT(22),
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(24),
        [ts_aux_sym_map] = SHIFT(26),
        [ts_aux_sym_8] = SHIFT(31),
        [ts_aux_sym_struct] = SHIFT(34),
        [ts_aux_sym_interface] = SHIFT(151),
    },
    [33] = {
        [ts_sym__line_break] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_slice_type, 3),
    },
    [34] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(35),
    },
    [35] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(149),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [36] = {
        [ts_sym_type_expression] = SHIFT(37),
        [ts_sym_pointer_type] = SHIFT(40),
        [ts_sym_map_type] = SHIFT(40),
        [ts_sym_slice_type] = SHIFT(40),
        [ts_sym_struct_type] = SHIFT(40),
        [ts_sym_interface_type] = SHIFT(40),
        [ts_sym_type_name] = SHIFT(40),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(42),
        [ts_aux_sym_map] = SHIFT(44),
        [ts_aux_sym_8] = SHIFT(49),
        [ts_aux_sym_struct] = SHIFT(52),
        [ts_aux_sym_interface] = SHIFT(56),
    },
    [37] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(39),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [38] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
    },
    [39] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 3),
    },
    [40] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_expression, 1),
    },
    [41] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_name, 1),
    },
    [42] = {
        [ts_sym_type_expression] = SHIFT(43),
        [ts_sym_pointer_type] = SHIFT(40),
        [ts_sym_map_type] = SHIFT(40),
        [ts_sym_slice_type] = SHIFT(40),
        [ts_sym_struct_type] = SHIFT(40),
        [ts_sym_interface_type] = SHIFT(40),
        [ts_sym_type_name] = SHIFT(40),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(42),
        [ts_aux_sym_map] = SHIFT(44),
        [ts_aux_sym_8] = SHIFT(49),
        [ts_aux_sym_struct] = SHIFT(52),
        [ts_aux_sym_interface] = SHIFT(56),
    },
    [43] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_pointer_type, 2),
    },
    [44] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(45),
    },
    [45] = {
        [ts_sym_type_expression] = SHIFT(46),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_8] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [46] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(47),
    },
    [47] = {
        [ts_sym_type_expression] = SHIFT(48),
        [ts_sym_pointer_type] = SHIFT(40),
        [ts_sym_map_type] = SHIFT(40),
        [ts_sym_slice_type] = SHIFT(40),
        [ts_sym_struct_type] = SHIFT(40),
        [ts_sym_interface_type] = SHIFT(40),
        [ts_sym_type_name] = SHIFT(40),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(42),
        [ts_aux_sym_map] = SHIFT(44),
        [ts_aux_sym_8] = SHIFT(49),
        [ts_aux_sym_struct] = SHIFT(52),
        [ts_aux_sym_interface] = SHIFT(56),
    },
    [48] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_map_type, 5),
    },
    [49] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(50),
    },
    [50] = {
        [ts_sym_type_expression] = SHIFT(51),
        [ts_sym_pointer_type] = SHIFT(40),
        [ts_sym_map_type] = SHIFT(40),
        [ts_sym_slice_type] = SHIFT(40),
        [ts_sym_struct_type] = SHIFT(40),
        [ts_sym_interface_type] = SHIFT(40),
        [ts_sym_type_name] = SHIFT(40),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(42),
        [ts_aux_sym_map] = SHIFT(44),
        [ts_aux_sym_8] = SHIFT(49),
        [ts_aux_sym_struct] = SHIFT(52),
        [ts_aux_sym_interface] = SHIFT(56),
    },
    [51] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_slice_type, 3),
    },
    [52] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(53),
    },
    [53] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(54),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [54] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(55),
    },
    [55] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_struct_type, 4),
    },
    [56] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(57),
    },
    [57] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(147),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [58] = {
        [ts_sym__func_signature] = SHIFT(59),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(62),
    },
    [59] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(61),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [60] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
    },
    [61] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [62] = {
        [ts_sym_var_name] = SHIFT(63),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(138),
    },
    [63] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(64),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_10] = SHIFT(135),
    },
    [64] = {
        [ts_sym_type_expression] = SHIFT(65),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_8] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [65] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(66),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_10] = SHIFT(87),
    },
    [66] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(67),
    },
    [67] = {
        [ts_sym_type_name] = SHIFT(68),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(69),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [68] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 7),
    },
    [69] = {
        [ts_sym_var_name] = SHIFT(70),
        [ts_sym_type_name] = SHIFT(80),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(86),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [70] = {
        [ts_sym_type_name] = SHIFT(71),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [71] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(72),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(74),
    },
    [72] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(73),
    },
    [73] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 11),
    },
    [74] = {
        [ts_sym_var_name] = SHIFT(75),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(79),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [75] = {
        [ts_sym_type_name] = SHIFT(76),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [76] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(77),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(74),
    },
    [77] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [78] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [79] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [80] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(81),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(83),
    },
    [81] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(82),
    },
    [82] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 10),
    },
    [83] = {
        [ts_sym_type_name] = SHIFT(84),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [84] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(85),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(83),
    },
    [85] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [86] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [87] = {
        [ts_sym_var_name] = SHIFT(88),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [88] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(89),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_10] = SHIFT(131),
    },
    [89] = {
        [ts_sym_type_expression] = SHIFT(90),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_8] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [90] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(91),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_10] = SHIFT(87),
    },
    [91] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [92] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_expression, 1),
    },
    [93] = {
        [ts_sym_type_expression] = SHIFT(94),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_8] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [94] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_pointer_type, 2),
    },
    [95] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(96),
    },
    [96] = {
        [ts_sym_type_expression] = SHIFT(97),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_8] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [97] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(98),
    },
    [98] = {
        [ts_sym_type_expression] = SHIFT(99),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_8] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [99] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_map_type, 5),
    },
    [100] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(101),
    },
    [101] = {
        [ts_sym_type_expression] = SHIFT(102),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_8] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [102] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_slice_type, 3),
    },
    [103] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(104),
    },
    [104] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(105),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [105] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(106),
    },
    [106] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_struct_type, 4),
    },
    [107] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(108),
    },
    [108] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(109),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [109] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(110),
    },
    [110] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_interface_type, 4),
    },
    [111] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_expression, 1),
    },
    [112] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_name, 1),
    },
    [113] = {
        [ts_sym_type_expression] = SHIFT(114),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_8] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [114] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_pointer_type, 2),
    },
    [115] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(116),
    },
    [116] = {
        [ts_sym_type_expression] = SHIFT(117),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_8] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [117] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(118),
    },
    [118] = {
        [ts_sym_type_expression] = SHIFT(119),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_8] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [119] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_map_type, 5),
    },
    [120] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(121),
    },
    [121] = {
        [ts_sym_type_expression] = SHIFT(122),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_8] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [122] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_slice_type, 3),
    },
    [123] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(124),
    },
    [124] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(125),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [125] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(126),
    },
    [126] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_struct_type, 4),
    },
    [127] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(128),
    },
    [128] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(129),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [129] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(130),
    },
    [130] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_interface_type, 4),
    },
    [131] = {
        [ts_sym_var_name] = SHIFT(132),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [132] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(133),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_10] = SHIFT(131),
    },
    [133] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [134] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
    },
    [135] = {
        [ts_sym_var_name] = SHIFT(136),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [136] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(137),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_10] = SHIFT(135),
    },
    [137] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
    },
    [138] = {
        [ts_sym_type_name] = SHIFT(139),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(41),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(140),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 2),
    },
    [139] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 3),
    },
    [140] = {
        [ts_sym_var_name] = SHIFT(141),
        [ts_sym_type_name] = SHIFT(144),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(86),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [141] = {
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [142] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(143),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(74),
    },
    [143] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(68),
    },
    [144] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(145),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(83),
    },
    [145] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(146),
    },
    [146] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [147] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(148),
    },
    [148] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_interface_type, 4),
    },
    [149] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(150),
    },
    [150] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 4),
    },
    [151] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(152),
    },
    [152] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(153),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [153] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(154),
    },
    [154] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
    },
    [155] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_type_name, 1),
    },
    [156] = {
        [ts_sym_var_name] = SHIFT(157),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(231),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [157] = {
        [ts_sym_type_expression] = SHIFT(158),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(210),
        [ts_aux_sym_7] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_8] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [158] = {
        [ts_sym__line_break] = SHIFT(159),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(159),
        [ts_aux_sym_4] = SHIFT(160),
    },
    [159] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_4] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_func] = REDUCE(ts_sym_var_declaration, 4),
    },
    [160] = {
        [ts_sym_expression] = SHIFT(161),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [161] = {
        [ts_sym__line_break] = SHIFT(162),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_3] = SHIFT(162),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = SHIFT(202),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = SHIFT(204),
        [ts_aux_sym_15] = SHIFT(204),
        [ts_aux_sym_16] = SHIFT(206),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [162] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_type] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_func] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_7] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_12] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_13] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_14] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_15] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_16] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_17] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_18] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_19] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_20] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_21] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_22] = REDUCE_EXTRA(ts_sym__line_break),
    },
    [163] = {
        [ts_sym_expression] = SHIFT(164),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(191),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [164] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(165),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(171),
        [ts_aux_sym_10] = SHIFT(181),
        [ts_aux_sym_12] = SHIFT(184),
        [ts_aux_sym_13] = SHIFT(171),
        [ts_aux_sym_14] = SHIFT(186),
        [ts_aux_sym_15] = SHIFT(186),
        [ts_aux_sym_16] = SHIFT(188),
        [ts_aux_sym_17] = SHIFT(173),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [165] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(166),
    },
    [166] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_3] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 5),
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
    [167] = {
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(190),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [168] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(169),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(171),
        [ts_aux_sym_10] = SHIFT(181),
        [ts_aux_sym_12] = SHIFT(184),
        [ts_aux_sym_13] = SHIFT(171),
        [ts_aux_sym_14] = SHIFT(186),
        [ts_aux_sym_15] = SHIFT(186),
        [ts_aux_sym_16] = SHIFT(188),
        [ts_aux_sym_17] = SHIFT(173),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [169] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(170),
    },
    [170] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_2] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 5),
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
    [171] = {
        [ts_sym_expression] = SHIFT(172),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [172] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(171),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(171),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(173),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [173] = {
        [ts_sym_expression] = SHIFT(174),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [174] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(171),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(171),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(173),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [175] = {
        [ts_sym_expression] = SHIFT(176),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [176] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [177] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_expression, 1),
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
    [178] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
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
    [179] = {
        [ts_sym_expression] = SHIFT(180),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [180] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 2),
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
    [181] = {
        [ts_sym_expression] = SHIFT(182),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [182] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(183),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(171),
        [ts_aux_sym_10] = SHIFT(181),
        [ts_aux_sym_12] = SHIFT(184),
        [ts_aux_sym_13] = SHIFT(171),
        [ts_aux_sym_14] = SHIFT(186),
        [ts_aux_sym_15] = SHIFT(186),
        [ts_aux_sym_16] = SHIFT(188),
        [ts_aux_sym_17] = SHIFT(173),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [183] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 3),
    },
    [184] = {
        [ts_sym_var_name] = SHIFT(185),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [185] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_selector_expression, 3),
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
    [186] = {
        [ts_sym_expression] = SHIFT(187),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [187] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(171),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(171),
        [ts_aux_sym_14] = SHIFT(186),
        [ts_aux_sym_15] = SHIFT(186),
        [ts_aux_sym_16] = SHIFT(188),
        [ts_aux_sym_17] = SHIFT(173),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [188] = {
        [ts_sym_expression] = SHIFT(189),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [189] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(171),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(171),
        [ts_aux_sym_14] = SHIFT(186),
        [ts_aux_sym_15] = SHIFT(186),
        [ts_aux_sym_16] = SHIFT(188),
        [ts_aux_sym_17] = SHIFT(173),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [190] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 3),
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
    [191] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 3),
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
    [192] = {
        [ts_sym_expression] = SHIFT(193),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [193] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [194] = {
        [ts_sym_expression] = SHIFT(195),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [195] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [196] = {
        [ts_sym_expression] = SHIFT(197),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [197] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [198] = {
        [ts_sym__line_break] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_expression, 1),
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
    [199] = {
        [ts_sym__line_break] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
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
    [200] = {
        [ts_sym_expression] = SHIFT(201),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [201] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_7] = REDUCE(ts_sym_bool_op, 2),
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
    [202] = {
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [203] = {
        [ts_sym__line_break] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_selector_expression, 3),
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
    [204] = {
        [ts_sym_expression] = SHIFT(205),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [205] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = SHIFT(204),
        [ts_aux_sym_15] = SHIFT(204),
        [ts_aux_sym_16] = SHIFT(206),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [206] = {
        [ts_sym_expression] = SHIFT(207),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [207] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = SHIFT(204),
        [ts_aux_sym_15] = SHIFT(204),
        [ts_aux_sym_16] = SHIFT(206),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [208] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_expression, 1),
    },
    [209] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_name, 1),
    },
    [210] = {
        [ts_sym_expression] = SHIFT(211),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [211] = {
        [ts_sym__line_break] = SHIFT(212),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_3] = SHIFT(212),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = SHIFT(202),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = SHIFT(204),
        [ts_aux_sym_15] = SHIFT(204),
        [ts_aux_sym_16] = SHIFT(206),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [212] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_type] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_func] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_7] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_12] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_13] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_14] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_15] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_16] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_17] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_18] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_19] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_20] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_21] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_22] = REDUCE_EXTRA(ts_sym__line_break),
    },
    [213] = {
        [ts_sym_type_expression] = SHIFT(214),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_8] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [214] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_pointer_type, 2),
    },
    [215] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(216),
    },
    [216] = {
        [ts_sym_type_expression] = SHIFT(217),
        [ts_sym_pointer_type] = SHIFT(111),
        [ts_sym_map_type] = SHIFT(111),
        [ts_sym_slice_type] = SHIFT(111),
        [ts_sym_struct_type] = SHIFT(111),
        [ts_sym_interface_type] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(112),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(113),
        [ts_aux_sym_map] = SHIFT(115),
        [ts_aux_sym_8] = SHIFT(120),
        [ts_aux_sym_struct] = SHIFT(123),
        [ts_aux_sym_interface] = SHIFT(127),
    },
    [217] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(218),
    },
    [218] = {
        [ts_sym_type_expression] = SHIFT(219),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_8] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [219] = {
        [ts_sym__line_break] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_4] = REDUCE(ts_sym_map_type, 5),
    },
    [220] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(221),
    },
    [221] = {
        [ts_sym_type_expression] = SHIFT(222),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_8] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [222] = {
        [ts_sym__line_break] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_slice_type, 3),
    },
    [223] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(224),
    },
    [224] = {
        [ts_sym_var_name] = SHIFT(36),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(38),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(225),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [225] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(226),
    },
    [226] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_struct_type, 4),
    },
    [227] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(228),
    },
    [228] = {
        [ts_sym_var_name] = SHIFT(58),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(229),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [229] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(230),
    },
    [230] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_interface_type, 4),
    },
    [231] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
    },
    [232] = {
        [ts_sym_var_name] = SHIFT(233),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(60),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [233] = {
        [ts_sym__func_signature] = SHIFT(234),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(343),
    },
    [234] = {
        [ts_sym_block_statement] = SHIFT(235),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(237),
    },
    [235] = {
        [ts_sym__line_break] = SHIFT(236),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(236),
    },
    [236] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_func] = REDUCE(ts_sym_func_declaration, 5),
    },
    [237] = {
        [ts_sym_var_declaration] = SHIFT(238),
        [ts_sym_statement] = SHIFT(239),
        [ts_sym_return_statement] = SHIFT(240),
        [ts_sym_declaration_statement] = SHIFT(240),
        [ts_sym_range_statement] = SHIFT(240),
        [ts_sym_if_statement] = SHIFT(240),
        [ts_sym_expression_statement] = SHIFT(240),
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(243),
        [ts_builtin_sym_error] = SHIFT(341),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(252),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(341),
        [ts_aux_sym_var] = SHIFT(254),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(264),
        [ts_aux_sym_11] = SHIFT(293),
        [ts_aux_sym_for] = SHIFT(296),
        [ts_aux_sym_if] = SHIFT(312),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [238] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_for] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_23] = REDUCE(ts_sym_declaration_statement, 1),
    },
    [239] = {
        [ts_sym_var_declaration] = SHIFT(238),
        [ts_sym_statement] = SHIFT(239),
        [ts_sym_return_statement] = SHIFT(240),
        [ts_sym_declaration_statement] = SHIFT(240),
        [ts_sym_range_statement] = SHIFT(240),
        [ts_sym_if_statement] = SHIFT(240),
        [ts_sym_expression_statement] = SHIFT(240),
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(243),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(252),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(253),
        [ts_aux_sym_var] = SHIFT(254),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(264),
        [ts_aux_sym_11] = SHIFT(293),
        [ts_aux_sym_for] = SHIFT(296),
        [ts_aux_sym_if] = SHIFT(312),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [240] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_for] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_23] = REDUCE(ts_sym_statement, 1),
    },
    [241] = {
        [ts_sym__line_break] = SHIFT(242),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_3] = SHIFT(242),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = SHIFT(202),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = SHIFT(204),
        [ts_aux_sym_15] = SHIFT(204),
        [ts_aux_sym_16] = SHIFT(206),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [242] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_7] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_return] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_for] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_expression_statement, 2),
        [ts_aux_sym_12] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_13] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_14] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_15] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_16] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_17] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_18] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_19] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_20] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_21] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_22] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_23] = REDUCE(ts_sym_expression_statement, 2),
    },
    [243] = {
        [ts_sym__line_break] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(244),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_10] = SHIFT(248),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 0),
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
    [244] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(245),
    },
    [245] = {
        [ts_sym_expression] = SHIFT(246),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [246] = {
        [ts_sym__line_break] = SHIFT(247),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_3] = SHIFT(247),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = SHIFT(202),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = SHIFT(204),
        [ts_aux_sym_15] = SHIFT(204),
        [ts_aux_sym_16] = SHIFT(206),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [247] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_aux_sym_7] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_return] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_aux_sym_11] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_aux_sym_for] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_aux_sym_if] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_aux_sym_12] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_13] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_14] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_15] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_16] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_17] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_18] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_19] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_20] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_21] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_22] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_23] = REDUCE(ts_sym_declaration_statement, 5),
    },
    [248] = {
        [ts_sym_var_name] = SHIFT(249),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(251),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [249] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(250),
        [ts_aux_sym_10] = SHIFT(248),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 0),
    },
    [250] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 3),
    },
    [251] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [252] = {
        [ts_sym__line_break] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
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
        [ts_aux_sym_22] = REDUCE(ts_sym_var_name, 1),
    },
    [253] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 2),
    },
    [254] = {
        [ts_sym_var_name] = SHIFT(255),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(231),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [255] = {
        [ts_sym_type_expression] = SHIFT(256),
        [ts_sym_pointer_type] = SHIFT(208),
        [ts_sym_map_type] = SHIFT(208),
        [ts_sym_slice_type] = SHIFT(208),
        [ts_sym_struct_type] = SHIFT(208),
        [ts_sym_interface_type] = SHIFT(208),
        [ts_sym_type_name] = SHIFT(208),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(209),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(261),
        [ts_aux_sym_7] = SHIFT(213),
        [ts_aux_sym_map] = SHIFT(215),
        [ts_aux_sym_8] = SHIFT(220),
        [ts_aux_sym_struct] = SHIFT(223),
        [ts_aux_sym_interface] = SHIFT(227),
    },
    [256] = {
        [ts_sym__line_break] = SHIFT(257),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(257),
        [ts_aux_sym_4] = SHIFT(258),
    },
    [257] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__identifier] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_4] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_return] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_for] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_if] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_23] = REDUCE(ts_sym_var_declaration, 4),
    },
    [258] = {
        [ts_sym_expression] = SHIFT(259),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [259] = {
        [ts_sym__line_break] = SHIFT(260),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_3] = SHIFT(260),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = SHIFT(202),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = SHIFT(204),
        [ts_aux_sym_15] = SHIFT(204),
        [ts_aux_sym_16] = SHIFT(206),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [260] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym__identifier] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_7] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_return] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_for] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_if] = REDUCE(ts_sym_var_declaration, 6),
        [ts_aux_sym_12] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_13] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_14] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_15] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_16] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_17] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_18] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_19] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_20] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_21] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_22] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_23] = REDUCE(ts_sym_var_declaration, 6),
    },
    [261] = {
        [ts_sym_expression] = SHIFT(262),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [262] = {
        [ts_sym__line_break] = SHIFT(263),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_3] = SHIFT(263),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = SHIFT(202),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = SHIFT(204),
        [ts_aux_sym_15] = SHIFT(204),
        [ts_aux_sym_16] = SHIFT(206),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [263] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_7] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_return] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_for] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_if] = REDUCE(ts_sym_var_declaration, 5),
        [ts_aux_sym_12] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_13] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_14] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_15] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_16] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_17] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_18] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_19] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_20] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_21] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_22] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_23] = REDUCE(ts_sym_var_declaration, 5),
    },
    [264] = {
        [ts_sym_expression] = SHIFT(265),
        [ts_sym_call_expression] = SHIFT(279),
        [ts_sym_selector_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(279),
        [ts_sym_bool_op] = SHIFT(279),
        [ts_sym_var_name] = SHIFT(279),
        [ts_sym__line_break] = SHIFT(292),
        [ts_sym_string] = SHIFT(279),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(279),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(292),
        [ts_aux_sym_23] = SHIFT(281),
    },
    [265] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(266),
        [ts_aux_sym_1] = SHIFT(268),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(273),
        [ts_aux_sym_10] = SHIFT(283),
        [ts_aux_sym_12] = SHIFT(286),
        [ts_aux_sym_13] = SHIFT(273),
        [ts_aux_sym_14] = SHIFT(288),
        [ts_aux_sym_15] = SHIFT(288),
        [ts_aux_sym_16] = SHIFT(290),
        [ts_aux_sym_17] = SHIFT(275),
        [ts_aux_sym_18] = SHIFT(277),
        [ts_aux_sym_19] = SHIFT(277),
        [ts_aux_sym_20] = SHIFT(277),
        [ts_aux_sym_21] = SHIFT(277),
        [ts_aux_sym_22] = SHIFT(277),
    },
    [266] = {
        [ts_sym__line_break] = SHIFT(267),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(267),
    },
    [267] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym__identifier] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_return] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_11] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_for] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_if] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_23] = REDUCE(ts_sym_return_statement, 4),
    },
    [268] = {
        [ts_sym_expression] = SHIFT(269),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(272),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [269] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(270),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(171),
        [ts_aux_sym_10] = SHIFT(181),
        [ts_aux_sym_12] = SHIFT(184),
        [ts_aux_sym_13] = SHIFT(171),
        [ts_aux_sym_14] = SHIFT(186),
        [ts_aux_sym_15] = SHIFT(186),
        [ts_aux_sym_16] = SHIFT(188),
        [ts_aux_sym_17] = SHIFT(173),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [270] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(271),
    },
    [271] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_3] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 5),
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
    [272] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 3),
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
    [273] = {
        [ts_sym_expression] = SHIFT(274),
        [ts_sym_call_expression] = SHIFT(279),
        [ts_sym_selector_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(279),
        [ts_sym_bool_op] = SHIFT(279),
        [ts_sym_var_name] = SHIFT(279),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(279),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(279),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(281),
    },
    [274] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(273),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(273),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(275),
        [ts_aux_sym_18] = SHIFT(277),
        [ts_aux_sym_19] = SHIFT(277),
        [ts_aux_sym_20] = SHIFT(277),
        [ts_aux_sym_21] = SHIFT(277),
        [ts_aux_sym_22] = SHIFT(277),
    },
    [275] = {
        [ts_sym_expression] = SHIFT(276),
        [ts_sym_call_expression] = SHIFT(279),
        [ts_sym_selector_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(279),
        [ts_sym_bool_op] = SHIFT(279),
        [ts_sym_var_name] = SHIFT(279),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(279),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(279),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(281),
    },
    [276] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(273),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(273),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(275),
        [ts_aux_sym_18] = SHIFT(277),
        [ts_aux_sym_19] = SHIFT(277),
        [ts_aux_sym_20] = SHIFT(277),
        [ts_aux_sym_21] = SHIFT(277),
        [ts_aux_sym_22] = SHIFT(277),
    },
    [277] = {
        [ts_sym_expression] = SHIFT(278),
        [ts_sym_call_expression] = SHIFT(279),
        [ts_sym_selector_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(279),
        [ts_sym_bool_op] = SHIFT(279),
        [ts_sym_var_name] = SHIFT(279),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(279),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(279),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(281),
    },
    [278] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_18] = SHIFT(277),
        [ts_aux_sym_19] = SHIFT(277),
        [ts_aux_sym_20] = SHIFT(277),
        [ts_aux_sym_21] = SHIFT(277),
        [ts_aux_sym_22] = SHIFT(277),
    },
    [279] = {
        [ts_sym__line_break] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_expression, 1),
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
    [280] = {
        [ts_sym__line_break] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
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
    [281] = {
        [ts_sym_expression] = SHIFT(282),
        [ts_sym_call_expression] = SHIFT(279),
        [ts_sym_selector_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(279),
        [ts_sym_bool_op] = SHIFT(279),
        [ts_sym_var_name] = SHIFT(279),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(279),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(279),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(281),
    },
    [282] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_7] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 2),
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
    [283] = {
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_call_expression] = SHIFT(279),
        [ts_sym_selector_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(279),
        [ts_sym_bool_op] = SHIFT(279),
        [ts_sym_var_name] = SHIFT(279),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(279),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(279),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(281),
    },
    [284] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(285),
        [ts_aux_sym_1] = SHIFT(268),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(273),
        [ts_aux_sym_10] = SHIFT(283),
        [ts_aux_sym_12] = SHIFT(286),
        [ts_aux_sym_13] = SHIFT(273),
        [ts_aux_sym_14] = SHIFT(288),
        [ts_aux_sym_15] = SHIFT(288),
        [ts_aux_sym_16] = SHIFT(290),
        [ts_aux_sym_17] = SHIFT(275),
        [ts_aux_sym_18] = SHIFT(277),
        [ts_aux_sym_19] = SHIFT(277),
        [ts_aux_sym_20] = SHIFT(277),
        [ts_aux_sym_21] = SHIFT(277),
        [ts_aux_sym_22] = SHIFT(277),
    },
    [285] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
    },
    [286] = {
        [ts_sym_var_name] = SHIFT(287),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [287] = {
        [ts_sym__line_break] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_selector_expression, 3),
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
    [288] = {
        [ts_sym_expression] = SHIFT(289),
        [ts_sym_call_expression] = SHIFT(279),
        [ts_sym_selector_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(279),
        [ts_sym_bool_op] = SHIFT(279),
        [ts_sym_var_name] = SHIFT(279),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(279),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(279),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(281),
    },
    [289] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(273),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(273),
        [ts_aux_sym_14] = SHIFT(288),
        [ts_aux_sym_15] = SHIFT(288),
        [ts_aux_sym_16] = SHIFT(290),
        [ts_aux_sym_17] = SHIFT(275),
        [ts_aux_sym_18] = SHIFT(277),
        [ts_aux_sym_19] = SHIFT(277),
        [ts_aux_sym_20] = SHIFT(277),
        [ts_aux_sym_21] = SHIFT(277),
        [ts_aux_sym_22] = SHIFT(277),
    },
    [290] = {
        [ts_sym_expression] = SHIFT(291),
        [ts_sym_call_expression] = SHIFT(279),
        [ts_sym_selector_expression] = SHIFT(279),
        [ts_sym_math_op] = SHIFT(279),
        [ts_sym_bool_op] = SHIFT(279),
        [ts_sym_var_name] = SHIFT(279),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(279),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_number] = SHIFT(279),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(281),
    },
    [291] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(273),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(273),
        [ts_aux_sym_14] = SHIFT(288),
        [ts_aux_sym_15] = SHIFT(288),
        [ts_aux_sym_16] = SHIFT(290),
        [ts_aux_sym_17] = SHIFT(275),
        [ts_aux_sym_18] = SHIFT(277),
        [ts_aux_sym_19] = SHIFT(277),
        [ts_aux_sym_20] = SHIFT(277),
        [ts_aux_sym_21] = SHIFT(277),
        [ts_aux_sym_22] = SHIFT(277),
    },
    [292] = {
        [ts_sym_expression] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_call_expression] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_selector_expression] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_math_op] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_bool_op] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_var_name] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_return] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_for] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_23] = REDUCE(ts_sym_return_statement, 2),
    },
    [293] = {
        [ts_sym_expression] = SHIFT(294),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(199),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [294] = {
        [ts_sym__line_break] = SHIFT(295),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(163),
        [ts_aux_sym_3] = SHIFT(295),
        [ts_aux_sym_7] = SHIFT(192),
        [ts_aux_sym_12] = SHIFT(202),
        [ts_aux_sym_13] = SHIFT(192),
        [ts_aux_sym_14] = SHIFT(204),
        [ts_aux_sym_15] = SHIFT(204),
        [ts_aux_sym_16] = SHIFT(206),
        [ts_aux_sym_17] = SHIFT(194),
        [ts_aux_sym_18] = SHIFT(196),
        [ts_aux_sym_19] = SHIFT(196),
        [ts_aux_sym_20] = SHIFT(196),
        [ts_aux_sym_21] = SHIFT(196),
        [ts_aux_sym_22] = SHIFT(196),
    },
    [295] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_aux_sym_7] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_return] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_aux_sym_for] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_aux_sym_12] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_13] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_14] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_15] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_16] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_17] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_18] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_19] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_20] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_21] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_22] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_23] = REDUCE(ts_sym_declaration_statement, 3),
    },
    [296] = {
        [ts_sym_var_name] = SHIFT(297),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(251),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [297] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = SHIFT(298),
        [ts_aux_sym_11] = SHIFT(337),
    },
    [298] = {
        [ts_sym_var_name] = SHIFT(299),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(336),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [299] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(300),
    },
    [300] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_range] = SHIFT(301),
    },
    [301] = {
        [ts_sym_expression] = SHIFT(302),
        [ts_sym_call_expression] = SHIFT(326),
        [ts_sym_selector_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(326),
        [ts_sym_bool_op] = SHIFT(326),
        [ts_sym_var_name] = SHIFT(326),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(326),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_number] = SHIFT(326),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(328),
    },
    [302] = {
        [ts_sym_block_statement] = SHIFT(303),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(304),
        [ts_aux_sym_5] = SHIFT(309),
        [ts_aux_sym_7] = SHIFT(320),
        [ts_aux_sym_12] = SHIFT(330),
        [ts_aux_sym_13] = SHIFT(320),
        [ts_aux_sym_14] = SHIFT(332),
        [ts_aux_sym_15] = SHIFT(332),
        [ts_aux_sym_16] = SHIFT(334),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(324),
        [ts_aux_sym_19] = SHIFT(324),
        [ts_aux_sym_20] = SHIFT(324),
        [ts_aux_sym_21] = SHIFT(324),
        [ts_aux_sym_22] = SHIFT(324),
    },
    [303] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym__identifier] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_number] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_6] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_return] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_11] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_for] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_if] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_23] = REDUCE(ts_sym_range_statement, 8),
    },
    [304] = {
        [ts_sym_expression] = SHIFT(305),
        [ts_sym_call_expression] = SHIFT(177),
        [ts_sym_selector_expression] = SHIFT(177),
        [ts_sym_math_op] = SHIFT(177),
        [ts_sym_bool_op] = SHIFT(177),
        [ts_sym_var_name] = SHIFT(177),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(177),
        [ts_sym__identifier] = SHIFT(178),
        [ts_sym_number] = SHIFT(177),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(308),
        [ts_aux_sym_23] = SHIFT(179),
    },
    [305] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(306),
        [ts_aux_sym_1] = SHIFT(167),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(171),
        [ts_aux_sym_10] = SHIFT(181),
        [ts_aux_sym_12] = SHIFT(184),
        [ts_aux_sym_13] = SHIFT(171),
        [ts_aux_sym_14] = SHIFT(186),
        [ts_aux_sym_15] = SHIFT(186),
        [ts_aux_sym_16] = SHIFT(188),
        [ts_aux_sym_17] = SHIFT(173),
        [ts_aux_sym_18] = SHIFT(175),
        [ts_aux_sym_19] = SHIFT(175),
        [ts_aux_sym_20] = SHIFT(175),
        [ts_aux_sym_21] = SHIFT(175),
        [ts_aux_sym_22] = SHIFT(175),
    },
    [306] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(307),
    },
    [307] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_5] = REDUCE(ts_sym_call_expression, 5),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 5),
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
    [308] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_call_expression, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 3),
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
    [309] = {
        [ts_sym_var_declaration] = SHIFT(238),
        [ts_sym_statement] = SHIFT(239),
        [ts_sym_return_statement] = SHIFT(240),
        [ts_sym_declaration_statement] = SHIFT(240),
        [ts_sym_range_statement] = SHIFT(240),
        [ts_sym_if_statement] = SHIFT(240),
        [ts_sym_expression_statement] = SHIFT(240),
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(243),
        [ts_builtin_sym_error] = SHIFT(310),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(252),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(310),
        [ts_aux_sym_var] = SHIFT(254),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(264),
        [ts_aux_sym_11] = SHIFT(293),
        [ts_aux_sym_for] = SHIFT(296),
        [ts_aux_sym_if] = SHIFT(312),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [310] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(311),
    },
    [311] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_for] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_23] = REDUCE(ts_sym_block_statement, 3),
    },
    [312] = {
        [ts_sym_expression] = SHIFT(313),
        [ts_sym_call_expression] = SHIFT(326),
        [ts_sym_selector_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(326),
        [ts_sym_bool_op] = SHIFT(326),
        [ts_sym_var_name] = SHIFT(326),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(326),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_number] = SHIFT(326),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(328),
    },
    [313] = {
        [ts_sym_block_statement] = SHIFT(314),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(304),
        [ts_aux_sym_5] = SHIFT(317),
        [ts_aux_sym_7] = SHIFT(320),
        [ts_aux_sym_12] = SHIFT(330),
        [ts_aux_sym_13] = SHIFT(320),
        [ts_aux_sym_14] = SHIFT(332),
        [ts_aux_sym_15] = SHIFT(332),
        [ts_aux_sym_16] = SHIFT(334),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(324),
        [ts_aux_sym_19] = SHIFT(324),
        [ts_aux_sym_20] = SHIFT(324),
        [ts_aux_sym_21] = SHIFT(324),
        [ts_aux_sym_22] = SHIFT(324),
    },
    [314] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_for] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_else] = SHIFT(315),
        [ts_aux_sym_23] = REDUCE(ts_sym_if_statement, 3),
    },
    [315] = {
        [ts_sym_block_statement] = SHIFT(316),
        [ts_sym_if_statement] = SHIFT(316),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(309),
        [ts_aux_sym_if] = SHIFT(312),
    },
    [316] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_return] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_for] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_if] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_23] = REDUCE(ts_sym_if_statement, 5),
    },
    [317] = {
        [ts_sym_var_declaration] = SHIFT(238),
        [ts_sym_statement] = SHIFT(239),
        [ts_sym_return_statement] = SHIFT(240),
        [ts_sym_declaration_statement] = SHIFT(240),
        [ts_sym_range_statement] = SHIFT(240),
        [ts_sym_if_statement] = SHIFT(240),
        [ts_sym_expression_statement] = SHIFT(240),
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_call_expression] = SHIFT(198),
        [ts_sym_selector_expression] = SHIFT(198),
        [ts_sym_math_op] = SHIFT(198),
        [ts_sym_bool_op] = SHIFT(198),
        [ts_sym_var_name] = SHIFT(243),
        [ts_builtin_sym_error] = SHIFT(318),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(198),
        [ts_sym__identifier] = SHIFT(252),
        [ts_sym_number] = SHIFT(198),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(318),
        [ts_aux_sym_var] = SHIFT(254),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(264),
        [ts_aux_sym_11] = SHIFT(293),
        [ts_aux_sym_for] = SHIFT(296),
        [ts_aux_sym_if] = SHIFT(312),
        [ts_aux_sym_23] = SHIFT(200),
    },
    [318] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(319),
    },
    [319] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_for] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_else] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_23] = REDUCE(ts_sym_block_statement, 3),
    },
    [320] = {
        [ts_sym_expression] = SHIFT(321),
        [ts_sym_call_expression] = SHIFT(326),
        [ts_sym_selector_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(326),
        [ts_sym_bool_op] = SHIFT(326),
        [ts_sym_var_name] = SHIFT(326),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(326),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_number] = SHIFT(326),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(328),
    },
    [321] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(320),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(320),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(324),
        [ts_aux_sym_19] = SHIFT(324),
        [ts_aux_sym_20] = SHIFT(324),
        [ts_aux_sym_21] = SHIFT(324),
        [ts_aux_sym_22] = SHIFT(324),
    },
    [322] = {
        [ts_sym_expression] = SHIFT(323),
        [ts_sym_call_expression] = SHIFT(326),
        [ts_sym_selector_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(326),
        [ts_sym_bool_op] = SHIFT(326),
        [ts_sym_var_name] = SHIFT(326),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(326),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_number] = SHIFT(326),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(328),
    },
    [323] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(320),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(320),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(324),
        [ts_aux_sym_19] = SHIFT(324),
        [ts_aux_sym_20] = SHIFT(324),
        [ts_aux_sym_21] = SHIFT(324),
        [ts_aux_sym_22] = SHIFT(324),
    },
    [324] = {
        [ts_sym_expression] = SHIFT(325),
        [ts_sym_call_expression] = SHIFT(326),
        [ts_sym_selector_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(326),
        [ts_sym_bool_op] = SHIFT(326),
        [ts_sym_var_name] = SHIFT(326),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(326),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_number] = SHIFT(326),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(328),
    },
    [325] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_18] = SHIFT(324),
        [ts_aux_sym_19] = SHIFT(324),
        [ts_aux_sym_20] = SHIFT(324),
        [ts_aux_sym_21] = SHIFT(324),
        [ts_aux_sym_22] = SHIFT(324),
    },
    [326] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_expression, 1),
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
    [327] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_5] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
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
    [328] = {
        [ts_sym_expression] = SHIFT(329),
        [ts_sym_call_expression] = SHIFT(326),
        [ts_sym_selector_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(326),
        [ts_sym_bool_op] = SHIFT(326),
        [ts_sym_var_name] = SHIFT(326),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(326),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_number] = SHIFT(326),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(328),
    },
    [329] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 2),
        [ts_aux_sym_7] = REDUCE(ts_sym_bool_op, 2),
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
    [330] = {
        [ts_sym_var_name] = SHIFT(331),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [331] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_selector_expression, 3),
        [ts_aux_sym_7] = REDUCE(ts_sym_selector_expression, 3),
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
    [332] = {
        [ts_sym_expression] = SHIFT(333),
        [ts_sym_call_expression] = SHIFT(326),
        [ts_sym_selector_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(326),
        [ts_sym_bool_op] = SHIFT(326),
        [ts_sym_var_name] = SHIFT(326),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(326),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_number] = SHIFT(326),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(328),
    },
    [333] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(320),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(320),
        [ts_aux_sym_14] = SHIFT(332),
        [ts_aux_sym_15] = SHIFT(332),
        [ts_aux_sym_16] = SHIFT(334),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(324),
        [ts_aux_sym_19] = SHIFT(324),
        [ts_aux_sym_20] = SHIFT(324),
        [ts_aux_sym_21] = SHIFT(324),
        [ts_aux_sym_22] = SHIFT(324),
    },
    [334] = {
        [ts_sym_expression] = SHIFT(335),
        [ts_sym_call_expression] = SHIFT(326),
        [ts_sym_selector_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(326),
        [ts_sym_bool_op] = SHIFT(326),
        [ts_sym_var_name] = SHIFT(326),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(326),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_number] = SHIFT(326),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(328),
    },
    [335] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(320),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(320),
        [ts_aux_sym_14] = SHIFT(332),
        [ts_aux_sym_15] = SHIFT(332),
        [ts_aux_sym_16] = SHIFT(334),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(324),
        [ts_aux_sym_19] = SHIFT(324),
        [ts_aux_sym_20] = SHIFT(324),
        [ts_aux_sym_21] = SHIFT(324),
        [ts_aux_sym_22] = SHIFT(324),
    },
    [336] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [337] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_range] = SHIFT(338),
    },
    [338] = {
        [ts_sym_expression] = SHIFT(339),
        [ts_sym_call_expression] = SHIFT(326),
        [ts_sym_selector_expression] = SHIFT(326),
        [ts_sym_math_op] = SHIFT(326),
        [ts_sym_bool_op] = SHIFT(326),
        [ts_sym_var_name] = SHIFT(326),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(326),
        [ts_sym__identifier] = SHIFT(327),
        [ts_sym_number] = SHIFT(326),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(328),
    },
    [339] = {
        [ts_sym_block_statement] = SHIFT(340),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(304),
        [ts_aux_sym_5] = SHIFT(309),
        [ts_aux_sym_7] = SHIFT(320),
        [ts_aux_sym_12] = SHIFT(330),
        [ts_aux_sym_13] = SHIFT(320),
        [ts_aux_sym_14] = SHIFT(332),
        [ts_aux_sym_15] = SHIFT(332),
        [ts_aux_sym_16] = SHIFT(334),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(324),
        [ts_aux_sym_19] = SHIFT(324),
        [ts_aux_sym_20] = SHIFT(324),
        [ts_aux_sym_21] = SHIFT(324),
        [ts_aux_sym_22] = SHIFT(324),
    },
    [340] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym__identifier] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_number] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_6] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_return] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_11] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_for] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_if] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_23] = REDUCE(ts_sym_range_statement, 6),
    },
    [341] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(342),
    },
    [342] = {
        [ts_sym__line_break] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_block_statement, 3),
    },
    [343] = {
        [ts_sym_var_name] = SHIFT(344),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(134),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(359),
    },
    [344] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(345),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_10] = SHIFT(135),
    },
    [345] = {
        [ts_sym_type_expression] = SHIFT(346),
        [ts_sym_pointer_type] = SHIFT(92),
        [ts_sym_map_type] = SHIFT(92),
        [ts_sym_slice_type] = SHIFT(92),
        [ts_sym_struct_type] = SHIFT(92),
        [ts_sym_interface_type] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(92),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(93),
        [ts_aux_sym_map] = SHIFT(95),
        [ts_aux_sym_8] = SHIFT(100),
        [ts_aux_sym_struct] = SHIFT(103),
        [ts_aux_sym_interface] = SHIFT(107),
    },
    [346] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(347),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_10] = SHIFT(87),
    },
    [347] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(348),
    },
    [348] = {
        [ts_sym_type_name] = SHIFT(349),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(350),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(351),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [349] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 7),
    },
    [350] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym_type_name, 1),
    },
    [351] = {
        [ts_sym_var_name] = SHIFT(352),
        [ts_sym_type_name] = SHIFT(356),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(86),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [352] = {
        [ts_sym_type_name] = SHIFT(353),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [353] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(354),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(74),
    },
    [354] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(355),
    },
    [355] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 11),
    },
    [356] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(357),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(83),
    },
    [357] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(358),
    },
    [358] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 10),
    },
    [359] = {
        [ts_sym_type_name] = SHIFT(360),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(350),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(361),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 2),
    },
    [360] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 3),
    },
    [361] = {
        [ts_sym_var_name] = SHIFT(362),
        [ts_sym_type_name] = SHIFT(365),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(86),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [362] = {
        [ts_sym_type_name] = SHIFT(363),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(78),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [363] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(364),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(74),
    },
    [364] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(349),
    },
    [365] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(366),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(83),
    },
    [366] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(367),
    },
    [367] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [368] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [369] = {
        [ts_sym_package_name] = SHIFT(370),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(371),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [370] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_directive, 2),
    },
    [371] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_name, 1),
    },
};

#pragma GCC diagnostic pop

EXPORT_PARSER(ts_parser_golang);
