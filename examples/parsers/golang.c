#include "tree_sitter/parser.h"

#define STATE_COUNT 372
#define SYMBOL_COUNT 89

enum {
    ts_sym_program = ts_builtin_sym_start,
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
    ts_sym__whitespace,
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
    [ts_builtin_sym_document] = "DOCUMENT",
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
    [ts_sym__whitespace] = "_whitespace",
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
    [ts_sym__whitespace] = 1,
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
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == 'p')
                ADVANCE(6);
            LEX_ERROR();
        case 2:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            ACCEPT_TOKEN(ts_sym__whitespace);
        case 3:
            ACCEPT_TOKEN(ts_sym__line_break);
        case 4:
            if (lookahead == '/')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (!(lookahead == '\n'))
                ADVANCE(5);
            ACCEPT_TOKEN(ts_sym_comment);
        case 6:
            if (lookahead == 'a')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (lookahead == 'c')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'k')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            if (lookahead == 'a')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            if (lookahead == 'g')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (lookahead == 'e')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            ACCEPT_TOKEN(ts_aux_sym_package);
        case 13:
            if (lookahead == 0)
                ADVANCE(14);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            LEX_ERROR();
        case 14:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 15:
            if (lookahead == 0)
                ADVANCE(14);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == 'f')
                ADVANCE(16);
            if (lookahead == 'i')
                ADVANCE(20);
            if (lookahead == 't')
                ADVANCE(26);
            if (lookahead == 'v')
                ADVANCE(30);
            LEX_ERROR();
        case 16:
            if (lookahead == 'u')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            if (lookahead == 'n')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            if (lookahead == 'c')
                ADVANCE(19);
            LEX_ERROR();
        case 19:
            ACCEPT_TOKEN(ts_aux_sym_func);
        case 20:
            if (lookahead == 'm')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if (lookahead == 'p')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            if (lookahead == 'o')
                ADVANCE(23);
            LEX_ERROR();
        case 23:
            if (lookahead == 'r')
                ADVANCE(24);
            LEX_ERROR();
        case 24:
            if (lookahead == 't')
                ADVANCE(25);
            LEX_ERROR();
        case 25:
            ACCEPT_TOKEN(ts_aux_sym_import);
        case 26:
            if (lookahead == 'y')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            if (lookahead == 'p')
                ADVANCE(28);
            LEX_ERROR();
        case 28:
            if (lookahead == 'e')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            ACCEPT_TOKEN(ts_aux_sym_type);
        case 30:
            if (lookahead == 'a')
                ADVANCE(31);
            LEX_ERROR();
        case 31:
            if (lookahead == 'r')
                ADVANCE(32);
            LEX_ERROR();
        case 32:
            ACCEPT_TOKEN(ts_aux_sym_var);
        case 33:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            LEX_ERROR();
        case 34:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 35:
            if (lookahead == 0)
                ADVANCE(14);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == 'f')
                ADVANCE(16);
            if (lookahead == 't')
                ADVANCE(26);
            if (lookahead == 'v')
                ADVANCE(30);
            LEX_ERROR();
        case 36:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '/')
                ADVANCE(4);
            LEX_ERROR();
        case 37:
            if (lookahead == '\"')
                ADVANCE(38);
            if (lookahead == '\\')
                ADVANCE(39);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(37);
            LEX_ERROR();
        case 38:
            ACCEPT_TOKEN(ts_sym_string);
        case 39:
            if (lookahead == '\"')
                ADVANCE(40);
            if (lookahead == '\\')
                ADVANCE(39);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(37);
            LEX_ERROR();
        case 40:
            if (lookahead == '\"')
                ADVANCE(38);
            if (lookahead == '\\')
                ADVANCE(39);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(37);
            ACCEPT_TOKEN(ts_sym_string);
        case 41:
            ACCEPT_TOKEN(ts_aux_sym_1);
        case 42:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == ')')
                ADVANCE(43);
            if (lookahead == '/')
                ADVANCE(4);
            LEX_ERROR();
        case 43:
            ACCEPT_TOKEN(ts_aux_sym_2);
        case 44:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(43);
            if (lookahead == '/')
                ADVANCE(4);
            LEX_ERROR();
        case 45:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '/')
                ADVANCE(4);
            LEX_ERROR();
        case 46:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == '{')
                ADVANCE(47);
            LEX_ERROR();
        case 47:
            ACCEPT_TOKEN(ts_aux_sym_5);
        case 48:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(43);
            if (lookahead == '/')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            LEX_ERROR();
        case 49:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == ',')
                ADVANCE(51);
            if (lookahead == '/')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == '[')
                ADVANCE(52);
            if (lookahead == 'i')
                ADVANCE(53);
            if (lookahead == 'm')
                ADVANCE(62);
            if (lookahead == 's')
                ADVANCE(65);
            LEX_ERROR();
        case 50:
            ACCEPT_TOKEN(ts_aux_sym_7);
        case 51:
            ACCEPT_TOKEN(ts_aux_sym_10);
        case 52:
            ACCEPT_TOKEN(ts_aux_sym_8);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'e')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'r')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'f')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'a')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'c')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'e')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_interface);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'a')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'p')
                ADVANCE(64);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_map);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'r')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'u')
                ADVANCE(68);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'c')
                ADVANCE(69);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(70);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_struct);
        case 71:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '/')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == '{')
                ADVANCE(47);
            LEX_ERROR();
        case 72:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(43);
            if (lookahead == ',')
                ADVANCE(51);
            if (lookahead == '/')
                ADVANCE(4);
            LEX_ERROR();
        case 73:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == ')')
                ADVANCE(43);
            if (lookahead == ',')
                ADVANCE(51);
            if (lookahead == '/')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            LEX_ERROR();
        case 74:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '/')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
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
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == '[')
                ADVANCE(52);
            LEX_ERROR();
        case 76:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == ']')
                ADVANCE(77);
            LEX_ERROR();
        case 77:
            ACCEPT_TOKEN(ts_aux_sym_9);
        case 78:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 79:
            ACCEPT_TOKEN(ts_aux_sym_6);
        case 80:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 81:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '/')
                ADVANCE(4);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 82:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == ';')
                ADVANCE(83);
            LEX_ERROR();
        case 83:
            ACCEPT_TOKEN(ts_aux_sym_3);
        case 84:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '!')
                ADVANCE(85);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            if (lookahead == ':')
                ADVANCE(89);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'f')
                ADVANCE(91);
            if (lookahead == 'i')
                ADVANCE(94);
            if (lookahead == 'r')
                ADVANCE(96);
            if (lookahead == 'v')
                ADVANCE(102);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 85:
            ACCEPT_TOKEN(ts_aux_sym_23);
        case 86:
            if (lookahead == '.')
                ADVANCE(87);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym_number);
        case 87:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            LEX_ERROR();
        case 88:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(88);
            ACCEPT_TOKEN(ts_sym_number);
        case 89:
            if (lookahead == '=')
                ADVANCE(90);
            LEX_ERROR();
        case 90:
            ACCEPT_TOKEN(ts_aux_sym_11);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'o')
                ADVANCE(92);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 92:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'r')
                ADVANCE(93);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_for);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'f')
                ADVANCE(95);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 95:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 96:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'e')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 97:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(98);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'u')
                ADVANCE(99);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 99:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'r')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 100:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(101);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_return);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'a')
                ADVANCE(103);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'r')
                ADVANCE(104);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 104:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_var);
        case 105:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(106);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '+')
                ADVANCE(108);
            if (lookahead == '-')
                ADVANCE(109);
            if (lookahead == '.')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == '<')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(114);
            if (lookahead == '>')
                ADVANCE(116);
            if (lookahead == '|')
                ADVANCE(118);
            LEX_ERROR();
        case 106:
            if (lookahead == '&')
                ADVANCE(107);
            LEX_ERROR();
        case 107:
            ACCEPT_TOKEN(ts_aux_sym_17);
        case 108:
            ACCEPT_TOKEN(ts_aux_sym_14);
        case 109:
            ACCEPT_TOKEN(ts_aux_sym_15);
        case 110:
            ACCEPT_TOKEN(ts_aux_sym_12);
        case 111:
            if (lookahead == '/')
                ADVANCE(5);
            ACCEPT_TOKEN(ts_aux_sym_13);
        case 112:
            if (lookahead == '=')
                ADVANCE(113);
            ACCEPT_TOKEN(ts_aux_sym_20);
        case 113:
            ACCEPT_TOKEN(ts_aux_sym_19);
        case 114:
            if (lookahead == '=')
                ADVANCE(115);
            LEX_ERROR();
        case 115:
            ACCEPT_TOKEN(ts_aux_sym_18);
        case 116:
            if (lookahead == '=')
                ADVANCE(117);
            ACCEPT_TOKEN(ts_aux_sym_22);
        case 117:
            ACCEPT_TOKEN(ts_aux_sym_21);
        case 118:
            if (lookahead == '|')
                ADVANCE(119);
            LEX_ERROR();
        case 119:
            ACCEPT_TOKEN(ts_aux_sym_16);
        case 120:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(106);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '+')
                ADVANCE(108);
            if (lookahead == ',')
                ADVANCE(51);
            if (lookahead == '-')
                ADVANCE(109);
            if (lookahead == '.')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(111);
            if (lookahead == ':')
                ADVANCE(89);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == '<')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(114);
            if (lookahead == '>')
                ADVANCE(116);
            if (lookahead == '|')
                ADVANCE(118);
            LEX_ERROR();
        case 121:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '!')
                ADVANCE(85);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            if (lookahead == ';')
                ADVANCE(83);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            LEX_ERROR();
        case 122:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '!')
                ADVANCE(85);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            LEX_ERROR();
        case 123:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(106);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '+')
                ADVANCE(108);
            if (lookahead == '-')
                ADVANCE(109);
            if (lookahead == '.')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(111);
            if (lookahead == '<')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(114);
            if (lookahead == '>')
                ADVANCE(116);
            if (lookahead == '{')
                ADVANCE(47);
            if (lookahead == '|')
                ADVANCE(118);
            LEX_ERROR();
        case 124:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '!')
                ADVANCE(85);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            if (lookahead == ':')
                ADVANCE(89);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'e')
                ADVANCE(125);
            if (lookahead == 'f')
                ADVANCE(91);
            if (lookahead == 'i')
                ADVANCE(94);
            if (lookahead == 'r')
                ADVANCE(96);
            if (lookahead == 'v')
                ADVANCE(102);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'l')
                ADVANCE(126);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 126:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 's')
                ADVANCE(127);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 127:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'e')
                ADVANCE(128);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 128:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_else);
        case 129:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '!')
                ADVANCE(85);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == ')')
                ADVANCE(43);
            if (lookahead == '/')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            LEX_ERROR();
        case 130:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(106);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == ')')
                ADVANCE(43);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '+')
                ADVANCE(108);
            if (lookahead == ',')
                ADVANCE(51);
            if (lookahead == '-')
                ADVANCE(109);
            if (lookahead == '.')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(111);
            if (lookahead == '<')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(114);
            if (lookahead == '>')
                ADVANCE(116);
            if (lookahead == '|')
                ADVANCE(118);
            LEX_ERROR();
        case 131:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == 'i')
                ADVANCE(132);
            if (lookahead == '{')
                ADVANCE(47);
            LEX_ERROR();
        case 132:
            if (lookahead == 'f')
                ADVANCE(133);
            LEX_ERROR();
        case 133:
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 134:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == ',')
                ADVANCE(51);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == ':')
                ADVANCE(89);
            LEX_ERROR();
        case 135:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
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
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == ':')
                ADVANCE(89);
            LEX_ERROR();
        case 142:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '!')
                ADVANCE(85);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '&')
                ADVANCE(106);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '+')
                ADVANCE(108);
            if (lookahead == '-')
                ADVANCE(109);
            if (lookahead == '.')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(111);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            if (lookahead == ':')
                ADVANCE(89);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == '<')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(114);
            if (lookahead == '>')
                ADVANCE(116);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'f')
                ADVANCE(91);
            if (lookahead == 'i')
                ADVANCE(94);
            if (lookahead == 'r')
                ADVANCE(96);
            if (lookahead == 'v')
                ADVANCE(102);
            if (lookahead == '|')
                ADVANCE(118);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 143:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(106);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '+')
                ADVANCE(108);
            if (lookahead == ',')
                ADVANCE(51);
            if (lookahead == '-')
                ADVANCE(109);
            if (lookahead == '.')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == '<')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(114);
            if (lookahead == '>')
                ADVANCE(116);
            if (lookahead == '|')
                ADVANCE(118);
            LEX_ERROR();
        case 144:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '!')
                ADVANCE(85);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            if (lookahead == ':')
                ADVANCE(89);
            if (lookahead == ';')
                ADVANCE(83);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'f')
                ADVANCE(91);
            if (lookahead == 'i')
                ADVANCE(94);
            if (lookahead == 'r')
                ADVANCE(96);
            if (lookahead == 'v')
                ADVANCE(102);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 145:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == '=')
                ADVANCE(146);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == '[')
                ADVANCE(52);
            if (lookahead == 'i')
                ADVANCE(53);
            if (lookahead == 'm')
                ADVANCE(62);
            if (lookahead == 's')
                ADVANCE(65);
            LEX_ERROR();
        case 146:
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 147:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == '=')
                ADVANCE(146);
            LEX_ERROR();
        case 148:
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '!')
                ADVANCE(85);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '/')
                ADVANCE(4);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            if (lookahead == ':')
                ADVANCE(89);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == '=')
                ADVANCE(146);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'f')
                ADVANCE(91);
            if (lookahead == 'i')
                ADVANCE(94);
            if (lookahead == 'r')
                ADVANCE(96);
            if (lookahead == 'v')
                ADVANCE(102);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        case 149:
            if (lookahead == 0)
                ADVANCE(14);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == 'f')
                ADVANCE(16);
            if (lookahead == 't')
                ADVANCE(26);
            if (lookahead == 'v')
                ADVANCE(30);
            LEX_ERROR();
        case 150:
            if (lookahead == 0)
                ADVANCE(14);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(106);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '+')
                ADVANCE(108);
            if (lookahead == '-')
                ADVANCE(109);
            if (lookahead == '.')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(111);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == '<')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(114);
            if (lookahead == '>')
                ADVANCE(116);
            if (lookahead == 'f')
                ADVANCE(16);
            if (lookahead == 't')
                ADVANCE(26);
            if (lookahead == 'v')
                ADVANCE(30);
            if (lookahead == '|')
                ADVANCE(118);
            LEX_ERROR();
        case 151:
            if (lookahead == 0)
                ADVANCE(14);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(4);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == '=')
                ADVANCE(146);
            if (lookahead == 'f')
                ADVANCE(16);
            if (lookahead == 't')
                ADVANCE(26);
            if (lookahead == 'v')
                ADVANCE(30);
            LEX_ERROR();
        case 152:
            if (lookahead == '=')
                ADVANCE(115);
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 153:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'o')
                ADVANCE(92);
            if (lookahead == 'u')
                ADVANCE(154);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 154:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(155);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 155:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'c')
                ADVANCE(156);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 156:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_func);
        case 157:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'f')
                ADVANCE(95);
            if (lookahead == 'm')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 158:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'p')
                ADVANCE(159);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 159:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'o')
                ADVANCE(160);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 160:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'r')
                ADVANCE(161);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 161:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 't')
                ADVANCE(162);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 162:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_import);
        case 163:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'a')
                ADVANCE(164);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 164:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'c')
                ADVANCE(165);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 165:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'k')
                ADVANCE(166);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 166:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'a')
                ADVANCE(167);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 167:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'g')
                ADVANCE(168);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 168:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'e')
                ADVANCE(169);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 169:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_package);
        case 170:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'a')
                ADVANCE(171);
            if (lookahead == 'e')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 171:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'n')
                ADVANCE(172);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 172:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'g')
                ADVANCE(173);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 173:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'e')
                ADVANCE(174);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 174:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_range);
        case 175:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(34);
            if (lookahead == 'y')
                ADVANCE(176);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 176:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'p')
                ADVANCE(177);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 177:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == 'e')
                ADVANCE(178);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 178:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            ACCEPT_TOKEN(ts_aux_sym_type);
        case ts_lex_state_error:
            if (lookahead == 0)
                ADVANCE(14);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(2);
            if (lookahead == '\n')
                ADVANCE(3);
            if (lookahead == '!')
                ADVANCE(85);
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '&')
                ADVANCE(106);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == ')')
                ADVANCE(43);
            if (lookahead == '*')
                ADVANCE(50);
            if (lookahead == '+')
                ADVANCE(108);
            if (lookahead == ',')
                ADVANCE(51);
            if (lookahead == '-')
                ADVANCE(109);
            if (lookahead == '.')
                ADVANCE(110);
            if (lookahead == '/')
                ADVANCE(111);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            if (lookahead == ':')
                ADVANCE(89);
            if (lookahead == ';')
                ADVANCE(83);
            if (lookahead == '<')
                ADVANCE(112);
            if (lookahead == '=')
                ADVANCE(152);
            if (lookahead == '>')
                ADVANCE(116);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                (lookahead == 'n') ||
                (lookahead == 'o') ||
                (lookahead == 'q') ||
                (lookahead == 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(34);
            if (lookahead == '[')
                ADVANCE(52);
            if (lookahead == ']')
                ADVANCE(77);
            if (lookahead == 'e')
                ADVANCE(125);
            if (lookahead == 'f')
                ADVANCE(153);
            if (lookahead == 'i')
                ADVANCE(157);
            if (lookahead == 'm')
                ADVANCE(62);
            if (lookahead == 'p')
                ADVANCE(163);
            if (lookahead == 'r')
                ADVANCE(170);
            if (lookahead == 's')
                ADVANCE(65);
            if (lookahead == 't')
                ADVANCE(175);
            if (lookahead == 'v')
                ADVANCE(102);
            if (lookahead == '{')
                ADVANCE(47);
            if (lookahead == '|')
                ADVANCE(118);
            if (lookahead == '}')
                ADVANCE(79);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

LEX_STATES = {
    [0] = 1,
    [1] = 13,
    [2] = 15,
    [3] = 33,
    [4] = 15,
    [5] = 15,
    [6] = 15,
    [7] = 35,
    [8] = 36,
    [9] = 15,
    [10] = 15,
    [11] = 42,
    [12] = 42,
    [13] = 44,
    [14] = 42,
    [15] = 15,
    [16] = 44,
    [17] = 35,
    [18] = 35,
    [19] = 13,
    [20] = 33,
    [21] = 33,
    [22] = 33,
    [23] = 45,
    [24] = 45,
    [25] = 46,
    [26] = 48,
    [27] = 49,
    [28] = 49,
    [29] = 71,
    [30] = 46,
    [31] = 46,
    [32] = 33,
    [33] = 33,
    [34] = 72,
    [35] = 73,
    [36] = 44,
    [37] = 33,
    [38] = 72,
    [39] = 72,
    [40] = 44,
    [41] = 46,
    [42] = 72,
    [43] = 44,
    [44] = 33,
    [45] = 33,
    [46] = 33,
    [47] = 72,
    [48] = 44,
    [49] = 46,
    [50] = 74,
    [51] = 33,
    [52] = 49,
    [53] = 74,
    [54] = 72,
    [55] = 72,
    [56] = 74,
    [57] = 75,
    [58] = 76,
    [59] = 46,
    [60] = 46,
    [61] = 78,
    [62] = 45,
    [63] = 80,
    [64] = 72,
    [65] = 78,
    [66] = 48,
    [67] = 49,
    [68] = 81,
    [69] = 78,
    [70] = 78,
    [71] = 33,
    [72] = 33,
    [73] = 72,
    [74] = 44,
    [75] = 78,
    [76] = 72,
    [77] = 44,
    [78] = 78,
    [79] = 74,
    [80] = 72,
    [81] = 44,
    [82] = 33,
    [83] = 49,
    [84] = 74,
    [85] = 33,
    [86] = 49,
    [87] = 74,
    [88] = 72,
    [89] = 44,
    [90] = 81,
    [91] = 33,
    [92] = 33,
    [93] = 72,
    [94] = 44,
    [95] = 78,
    [96] = 72,
    [97] = 44,
    [98] = 78,
    [99] = 80,
    [100] = 78,
    [101] = 74,
    [102] = 74,
    [103] = 80,
    [104] = 72,
    [105] = 78,
    [106] = 78,
    [107] = 74,
    [108] = 75,
    [109] = 76,
    [110] = 46,
    [111] = 46,
    [112] = 78,
    [113] = 80,
    [114] = 78,
    [115] = 78,
    [116] = 80,
    [117] = 78,
    [118] = 74,
    [119] = 78,
    [120] = 74,
    [121] = 76,
    [122] = 76,
    [123] = 76,
    [124] = 74,
    [125] = 75,
    [126] = 76,
    [127] = 46,
    [128] = 46,
    [129] = 78,
    [130] = 80,
    [131] = 76,
    [132] = 78,
    [133] = 80,
    [134] = 76,
    [135] = 74,
    [136] = 76,
    [137] = 74,
    [138] = 76,
    [139] = 74,
    [140] = 76,
    [141] = 76,
    [142] = 74,
    [143] = 78,
    [144] = 78,
    [145] = 80,
    [146] = 74,
    [147] = 72,
    [148] = 74,
    [149] = 76,
    [150] = 74,
    [151] = 72,
    [152] = 72,
    [153] = 44,
    [154] = 71,
    [155] = 33,
    [156] = 33,
    [157] = 72,
    [158] = 44,
    [159] = 46,
    [160] = 72,
    [161] = 44,
    [162] = 46,
    [163] = 82,
    [164] = 84,
    [165] = 84,
    [166] = 84,
    [167] = 84,
    [168] = 105,
    [169] = 105,
    [170] = 120,
    [171] = 80,
    [172] = 120,
    [173] = 33,
    [174] = 121,
    [175] = 122,
    [176] = 33,
    [177] = 122,
    [178] = 122,
    [179] = 105,
    [180] = 105,
    [181] = 123,
    [182] = 123,
    [183] = 123,
    [184] = 122,
    [185] = 123,
    [186] = 124,
    [187] = 129,
    [188] = 84,
    [189] = 122,
    [190] = 33,
    [191] = 122,
    [192] = 122,
    [193] = 122,
    [194] = 122,
    [195] = 123,
    [196] = 123,
    [197] = 123,
    [198] = 123,
    [199] = 123,
    [200] = 123,
    [201] = 80,
    [202] = 124,
    [203] = 130,
    [204] = 130,
    [205] = 130,
    [206] = 123,
    [207] = 122,
    [208] = 130,
    [209] = 44,
    [210] = 129,
    [211] = 122,
    [212] = 122,
    [213] = 33,
    [214] = 122,
    [215] = 122,
    [216] = 122,
    [217] = 122,
    [218] = 130,
    [219] = 130,
    [220] = 130,
    [221] = 130,
    [222] = 130,
    [223] = 130,
    [224] = 44,
    [225] = 130,
    [226] = 130,
    [227] = 130,
    [228] = 44,
    [229] = 130,
    [230] = 123,
    [231] = 131,
    [232] = 84,
    [233] = 84,
    [234] = 80,
    [235] = 84,
    [236] = 134,
    [237] = 134,
    [238] = 33,
    [239] = 135,
    [240] = 122,
    [241] = 123,
    [242] = 84,
    [243] = 141,
    [244] = 141,
    [245] = 135,
    [246] = 122,
    [247] = 123,
    [248] = 84,
    [249] = 105,
    [250] = 142,
    [251] = 129,
    [252] = 122,
    [253] = 33,
    [254] = 122,
    [255] = 122,
    [256] = 122,
    [257] = 122,
    [258] = 105,
    [259] = 105,
    [260] = 105,
    [261] = 105,
    [262] = 105,
    [263] = 105,
    [264] = 130,
    [265] = 105,
    [266] = 44,
    [267] = 105,
    [268] = 143,
    [269] = 143,
    [270] = 144,
    [271] = 143,
    [272] = 122,
    [273] = 143,
    [274] = 82,
    [275] = 129,
    [276] = 122,
    [277] = 122,
    [278] = 33,
    [279] = 122,
    [280] = 122,
    [281] = 122,
    [282] = 122,
    [283] = 143,
    [284] = 143,
    [285] = 143,
    [286] = 143,
    [287] = 143,
    [288] = 143,
    [289] = 82,
    [290] = 143,
    [291] = 130,
    [292] = 143,
    [293] = 44,
    [294] = 143,
    [295] = 144,
    [296] = 145,
    [297] = 145,
    [298] = 147,
    [299] = 147,
    [300] = 147,
    [301] = 122,
    [302] = 74,
    [303] = 75,
    [304] = 76,
    [305] = 46,
    [306] = 46,
    [307] = 78,
    [308] = 80,
    [309] = 147,
    [310] = 78,
    [311] = 80,
    [312] = 147,
    [313] = 74,
    [314] = 147,
    [315] = 74,
    [316] = 76,
    [317] = 74,
    [318] = 147,
    [319] = 147,
    [320] = 105,
    [321] = 142,
    [322] = 148,
    [323] = 122,
    [324] = 105,
    [325] = 142,
    [326] = 82,
    [327] = 141,
    [328] = 33,
    [329] = 134,
    [330] = 141,
    [331] = 122,
    [332] = 105,
    [333] = 142,
    [334] = 142,
    [335] = 80,
    [336] = 149,
    [337] = 145,
    [338] = 147,
    [339] = 122,
    [340] = 105,
    [341] = 150,
    [342] = 151,
    [343] = 122,
    [344] = 105,
    [345] = 150,
    [346] = 74,
    [347] = 74,
    [348] = 82,
    [349] = 82,
    [350] = 82,
    [351] = 74,
    [352] = 75,
    [353] = 76,
    [354] = 46,
    [355] = 46,
    [356] = 78,
    [357] = 80,
    [358] = 82,
    [359] = 78,
    [360] = 80,
    [361] = 82,
    [362] = 74,
    [363] = 82,
    [364] = 74,
    [365] = 76,
    [366] = 74,
    [367] = 82,
    [368] = 82,
    [369] = 149,
    [370] = 13,
    [371] = 35,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

PARSE_TABLE = {
    [0] = {
        [ts_sym_program] = SHIFT(1),
        [ts_sym_package_directive] = SHIFT(2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_package] = SHIFT(3),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [2] = {
        [ts_sym_imports_block] = SHIFT(6),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = SHIFT(7),
        [ts_aux_sym_import] = SHIFT(8),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [3] = {
        [ts_sym_package_name] = SHIFT(4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(5),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [4] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_directive, 2),
    },
    [5] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_name, 1),
    },
    [6] = {
        [ts_sym_imports_block] = SHIFT(6),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = SHIFT(371),
        [ts_aux_sym_import] = SHIFT(8),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 0),
    },
    [7] = {
        [ts_sym_declaration] = SHIFT(17),
        [ts_sym_type_declaration] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(18),
        [ts_sym_func_declaration] = SHIFT(18),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = SHIFT(19),
        [ts_aux_sym_type] = SHIFT(20),
        [ts_aux_sym_var] = SHIFT(21),
        [ts_aux_sym_func] = SHIFT(22),
    },
    [8] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(10),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(11),
    },
    [9] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 2),
    },
    [10] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_import, 1),
    },
    [11] = {
        [ts_sym_package_import] = SHIFT(12),
        [ts_builtin_sym_error] = SHIFT(13),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(13),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [12] = {
        [ts_sym_package_import] = SHIFT(12),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(16),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [13] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(15),
    },
    [14] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_package_import, 1),
    },
    [15] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 4),
    },
    [16] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 2),
    },
    [17] = {
        [ts_sym_declaration] = SHIFT(17),
        [ts_sym_type_declaration] = SHIFT(18),
        [ts_sym_var_declaration] = SHIFT(18),
        [ts_sym_func_declaration] = SHIFT(18),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 0),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = SHIFT(370),
        [ts_aux_sym_type] = SHIFT(20),
        [ts_aux_sym_var] = SHIFT(21),
        [ts_aux_sym_func] = SHIFT(22),
    },
    [18] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_declaration, 1),
    },
    [19] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [20] = {
        [ts_sym_type_name] = SHIFT(346),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(347),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [21] = {
        [ts_sym_var_name] = SHIFT(337),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(297),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [22] = {
        [ts_sym_var_name] = SHIFT(23),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [23] = {
        [ts_sym__func_signature] = SHIFT(25),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(26),
    },
    [24] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
    },
    [25] = {
        [ts_sym_block_statement] = SHIFT(163),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(164),
    },
    [26] = {
        [ts_sym_var_name] = SHIFT(27),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(29),
    },
    [27] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(50),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_10] = SHIFT(51),
    },
    [28] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
    },
    [29] = {
        [ts_sym_type_name] = SHIFT(30),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(31),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(32),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 2),
    },
    [30] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 3),
    },
    [31] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym_type_name, 1),
    },
    [32] = {
        [ts_sym_var_name] = SHIFT(33),
        [ts_sym_type_name] = SHIFT(34),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(35),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [33] = {
        [ts_sym_type_name] = SHIFT(42),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [34] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(36),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [35] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [36] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(41),
    },
    [37] = {
        [ts_sym_type_name] = SHIFT(38),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [38] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(40),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [39] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [40] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [41] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [42] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(43),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [43] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(49),
    },
    [44] = {
        [ts_sym_var_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [45] = {
        [ts_sym_type_name] = SHIFT(47),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [46] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [47] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(48),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [48] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [49] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 7),
    },
    [50] = {
        [ts_sym_type_expression] = SHIFT(54),
        [ts_sym_pointer_type] = SHIFT(55),
        [ts_sym_map_type] = SHIFT(55),
        [ts_sym_slice_type] = SHIFT(55),
        [ts_sym_struct_type] = SHIFT(55),
        [ts_sym_interface_type] = SHIFT(55),
        [ts_sym_type_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(56),
        [ts_aux_sym_map] = SHIFT(57),
        [ts_aux_sym_8] = SHIFT(58),
        [ts_aux_sym_struct] = SHIFT(59),
        [ts_aux_sym_interface] = SHIFT(60),
    },
    [51] = {
        [ts_sym_var_name] = SHIFT(52),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [52] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(53),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_10] = SHIFT(51),
    },
    [53] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
    },
    [54] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(153),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_10] = SHIFT(82),
    },
    [55] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_expression, 1),
    },
    [56] = {
        [ts_sym_type_expression] = SHIFT(152),
        [ts_sym_pointer_type] = SHIFT(55),
        [ts_sym_map_type] = SHIFT(55),
        [ts_sym_slice_type] = SHIFT(55),
        [ts_sym_struct_type] = SHIFT(55),
        [ts_sym_interface_type] = SHIFT(55),
        [ts_sym_type_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(56),
        [ts_aux_sym_map] = SHIFT(57),
        [ts_aux_sym_8] = SHIFT(58),
        [ts_aux_sym_struct] = SHIFT(59),
        [ts_aux_sym_interface] = SHIFT(60),
    },
    [57] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(148),
    },
    [58] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(146),
    },
    [59] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(100),
    },
    [60] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(61),
    },
    [61] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(63),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [62] = {
        [ts_sym__func_signature] = SHIFT(65),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(66),
    },
    [63] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(64),
    },
    [64] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_interface_type, 4),
    },
    [65] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(99),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [66] = {
        [ts_sym_var_name] = SHIFT(67),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(68),
    },
    [67] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(79),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 0),
        [ts_aux_sym_10] = SHIFT(51),
    },
    [68] = {
        [ts_sym_type_name] = SHIFT(69),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(70),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(71),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 2),
    },
    [69] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 3),
    },
    [70] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_name, 1),
    },
    [71] = {
        [ts_sym_var_name] = SHIFT(72),
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(35),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [72] = {
        [ts_sym_type_name] = SHIFT(76),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [73] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(74),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [74] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(75),
    },
    [75] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [76] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(77),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [77] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(78),
    },
    [78] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 7),
    },
    [79] = {
        [ts_sym_type_expression] = SHIFT(80),
        [ts_sym_pointer_type] = SHIFT(55),
        [ts_sym_map_type] = SHIFT(55),
        [ts_sym_slice_type] = SHIFT(55),
        [ts_sym_struct_type] = SHIFT(55),
        [ts_sym_interface_type] = SHIFT(55),
        [ts_sym_type_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(56),
        [ts_aux_sym_map] = SHIFT(57),
        [ts_aux_sym_8] = SHIFT(58),
        [ts_aux_sym_struct] = SHIFT(59),
        [ts_aux_sym_interface] = SHIFT(60),
    },
    [80] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(81),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_10] = SHIFT(82),
    },
    [81] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(90),
    },
    [82] = {
        [ts_sym_var_name] = SHIFT(83),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [83] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(84),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_10] = SHIFT(85),
    },
    [84] = {
        [ts_sym_type_expression] = SHIFT(88),
        [ts_sym_pointer_type] = SHIFT(55),
        [ts_sym_map_type] = SHIFT(55),
        [ts_sym_slice_type] = SHIFT(55),
        [ts_sym_struct_type] = SHIFT(55),
        [ts_sym_interface_type] = SHIFT(55),
        [ts_sym_type_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(56),
        [ts_aux_sym_map] = SHIFT(57),
        [ts_aux_sym_8] = SHIFT(58),
        [ts_aux_sym_struct] = SHIFT(59),
        [ts_aux_sym_interface] = SHIFT(60),
    },
    [85] = {
        [ts_sym_var_name] = SHIFT(86),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [86] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(87),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 0),
        [ts_aux_sym_10] = SHIFT(85),
    },
    [87] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [88] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(89),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_10] = SHIFT(82),
    },
    [89] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [90] = {
        [ts_sym_type_name] = SHIFT(78),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(70),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(91),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [91] = {
        [ts_sym_var_name] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(93),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(35),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [92] = {
        [ts_sym_type_name] = SHIFT(96),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [93] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(94),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [94] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(95),
    },
    [95] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 10),
    },
    [96] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(97),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [97] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(98),
    },
    [98] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 11),
    },
    [99] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [100] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(103),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [101] = {
        [ts_sym_type_expression] = SHIFT(105),
        [ts_sym_pointer_type] = SHIFT(106),
        [ts_sym_map_type] = SHIFT(106),
        [ts_sym_slice_type] = SHIFT(106),
        [ts_sym_struct_type] = SHIFT(106),
        [ts_sym_interface_type] = SHIFT(106),
        [ts_sym_type_name] = SHIFT(106),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(70),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(107),
        [ts_aux_sym_map] = SHIFT(108),
        [ts_aux_sym_8] = SHIFT(109),
        [ts_aux_sym_struct] = SHIFT(110),
        [ts_aux_sym_interface] = SHIFT(111),
    },
    [102] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
    },
    [103] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(104),
    },
    [104] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_struct_type, 4),
    },
    [105] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(145),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [106] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_expression, 1),
    },
    [107] = {
        [ts_sym_type_expression] = SHIFT(144),
        [ts_sym_pointer_type] = SHIFT(106),
        [ts_sym_map_type] = SHIFT(106),
        [ts_sym_slice_type] = SHIFT(106),
        [ts_sym_struct_type] = SHIFT(106),
        [ts_sym_interface_type] = SHIFT(106),
        [ts_sym_type_name] = SHIFT(106),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(70),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(107),
        [ts_aux_sym_map] = SHIFT(108),
        [ts_aux_sym_8] = SHIFT(109),
        [ts_aux_sym_struct] = SHIFT(110),
        [ts_aux_sym_interface] = SHIFT(111),
    },
    [108] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(120),
    },
    [109] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(118),
    },
    [110] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(115),
    },
    [111] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(112),
    },
    [112] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(113),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [113] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(114),
    },
    [114] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_interface_type, 4),
    },
    [115] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(116),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [116] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(117),
    },
    [117] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_struct_type, 4),
    },
    [118] = {
        [ts_sym_type_expression] = SHIFT(119),
        [ts_sym_pointer_type] = SHIFT(106),
        [ts_sym_map_type] = SHIFT(106),
        [ts_sym_slice_type] = SHIFT(106),
        [ts_sym_struct_type] = SHIFT(106),
        [ts_sym_interface_type] = SHIFT(106),
        [ts_sym_type_name] = SHIFT(106),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(70),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(107),
        [ts_aux_sym_map] = SHIFT(108),
        [ts_aux_sym_8] = SHIFT(109),
        [ts_aux_sym_struct] = SHIFT(110),
        [ts_aux_sym_interface] = SHIFT(111),
    },
    [119] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_slice_type, 3),
    },
    [120] = {
        [ts_sym_type_expression] = SHIFT(121),
        [ts_sym_pointer_type] = SHIFT(122),
        [ts_sym_map_type] = SHIFT(122),
        [ts_sym_slice_type] = SHIFT(122),
        [ts_sym_struct_type] = SHIFT(122),
        [ts_sym_interface_type] = SHIFT(122),
        [ts_sym_type_name] = SHIFT(122),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(123),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(124),
        [ts_aux_sym_map] = SHIFT(125),
        [ts_aux_sym_8] = SHIFT(126),
        [ts_aux_sym_struct] = SHIFT(127),
        [ts_aux_sym_interface] = SHIFT(128),
    },
    [121] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(142),
    },
    [122] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_expression, 1),
    },
    [123] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_name, 1),
    },
    [124] = {
        [ts_sym_type_expression] = SHIFT(141),
        [ts_sym_pointer_type] = SHIFT(122),
        [ts_sym_map_type] = SHIFT(122),
        [ts_sym_slice_type] = SHIFT(122),
        [ts_sym_struct_type] = SHIFT(122),
        [ts_sym_interface_type] = SHIFT(122),
        [ts_sym_type_name] = SHIFT(122),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(123),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(124),
        [ts_aux_sym_map] = SHIFT(125),
        [ts_aux_sym_8] = SHIFT(126),
        [ts_aux_sym_struct] = SHIFT(127),
        [ts_aux_sym_interface] = SHIFT(128),
    },
    [125] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(137),
    },
    [126] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(135),
    },
    [127] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(132),
    },
    [128] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(129),
    },
    [129] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(130),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [130] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(131),
    },
    [131] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_interface_type, 4),
    },
    [132] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(133),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [133] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(134),
    },
    [134] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_struct_type, 4),
    },
    [135] = {
        [ts_sym_type_expression] = SHIFT(136),
        [ts_sym_pointer_type] = SHIFT(122),
        [ts_sym_map_type] = SHIFT(122),
        [ts_sym_slice_type] = SHIFT(122),
        [ts_sym_struct_type] = SHIFT(122),
        [ts_sym_interface_type] = SHIFT(122),
        [ts_sym_type_name] = SHIFT(122),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(123),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(124),
        [ts_aux_sym_map] = SHIFT(125),
        [ts_aux_sym_8] = SHIFT(126),
        [ts_aux_sym_struct] = SHIFT(127),
        [ts_aux_sym_interface] = SHIFT(128),
    },
    [136] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_slice_type, 3),
    },
    [137] = {
        [ts_sym_type_expression] = SHIFT(138),
        [ts_sym_pointer_type] = SHIFT(122),
        [ts_sym_map_type] = SHIFT(122),
        [ts_sym_slice_type] = SHIFT(122),
        [ts_sym_struct_type] = SHIFT(122),
        [ts_sym_interface_type] = SHIFT(122),
        [ts_sym_type_name] = SHIFT(122),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(123),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(124),
        [ts_aux_sym_map] = SHIFT(125),
        [ts_aux_sym_8] = SHIFT(126),
        [ts_aux_sym_struct] = SHIFT(127),
        [ts_aux_sym_interface] = SHIFT(128),
    },
    [138] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(139),
    },
    [139] = {
        [ts_sym_type_expression] = SHIFT(140),
        [ts_sym_pointer_type] = SHIFT(122),
        [ts_sym_map_type] = SHIFT(122),
        [ts_sym_slice_type] = SHIFT(122),
        [ts_sym_struct_type] = SHIFT(122),
        [ts_sym_interface_type] = SHIFT(122),
        [ts_sym_type_name] = SHIFT(122),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(123),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(124),
        [ts_aux_sym_map] = SHIFT(125),
        [ts_aux_sym_8] = SHIFT(126),
        [ts_aux_sym_struct] = SHIFT(127),
        [ts_aux_sym_interface] = SHIFT(128),
    },
    [140] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_map_type, 5),
    },
    [141] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_pointer_type, 2),
    },
    [142] = {
        [ts_sym_type_expression] = SHIFT(143),
        [ts_sym_pointer_type] = SHIFT(106),
        [ts_sym_map_type] = SHIFT(106),
        [ts_sym_slice_type] = SHIFT(106),
        [ts_sym_struct_type] = SHIFT(106),
        [ts_sym_interface_type] = SHIFT(106),
        [ts_sym_type_name] = SHIFT(106),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(70),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(107),
        [ts_aux_sym_map] = SHIFT(108),
        [ts_aux_sym_8] = SHIFT(109),
        [ts_aux_sym_struct] = SHIFT(110),
        [ts_aux_sym_interface] = SHIFT(111),
    },
    [143] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_map_type, 5),
    },
    [144] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_pointer_type, 2),
    },
    [145] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 3),
    },
    [146] = {
        [ts_sym_type_expression] = SHIFT(147),
        [ts_sym_pointer_type] = SHIFT(55),
        [ts_sym_map_type] = SHIFT(55),
        [ts_sym_slice_type] = SHIFT(55),
        [ts_sym_struct_type] = SHIFT(55),
        [ts_sym_interface_type] = SHIFT(55),
        [ts_sym_type_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(56),
        [ts_aux_sym_map] = SHIFT(57),
        [ts_aux_sym_8] = SHIFT(58),
        [ts_aux_sym_struct] = SHIFT(59),
        [ts_aux_sym_interface] = SHIFT(60),
    },
    [147] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_slice_type, 3),
    },
    [148] = {
        [ts_sym_type_expression] = SHIFT(149),
        [ts_sym_pointer_type] = SHIFT(122),
        [ts_sym_map_type] = SHIFT(122),
        [ts_sym_slice_type] = SHIFT(122),
        [ts_sym_struct_type] = SHIFT(122),
        [ts_sym_interface_type] = SHIFT(122),
        [ts_sym_type_name] = SHIFT(122),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(123),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(124),
        [ts_aux_sym_map] = SHIFT(125),
        [ts_aux_sym_8] = SHIFT(126),
        [ts_aux_sym_struct] = SHIFT(127),
        [ts_aux_sym_interface] = SHIFT(128),
    },
    [149] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(150),
    },
    [150] = {
        [ts_sym_type_expression] = SHIFT(151),
        [ts_sym_pointer_type] = SHIFT(55),
        [ts_sym_map_type] = SHIFT(55),
        [ts_sym_slice_type] = SHIFT(55),
        [ts_sym_struct_type] = SHIFT(55),
        [ts_sym_interface_type] = SHIFT(55),
        [ts_sym_type_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(56),
        [ts_aux_sym_map] = SHIFT(57),
        [ts_aux_sym_8] = SHIFT(58),
        [ts_aux_sym_struct] = SHIFT(59),
        [ts_aux_sym_interface] = SHIFT(60),
    },
    [151] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_map_type, 5),
    },
    [152] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_pointer_type, 2),
    },
    [153] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(154),
    },
    [154] = {
        [ts_sym_type_name] = SHIFT(49),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(31),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(155),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [155] = {
        [ts_sym_var_name] = SHIFT(156),
        [ts_sym_type_name] = SHIFT(157),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(35),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [156] = {
        [ts_sym_type_name] = SHIFT(160),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [157] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(158),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [158] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(159),
    },
    [159] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 10),
    },
    [160] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(161),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [161] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(162),
    },
    [162] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 11),
    },
    [163] = {
        [ts_sym__line_break] = SHIFT(336),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(336),
    },
    [164] = {
        [ts_sym_var_declaration] = SHIFT(165),
        [ts_sym_statement] = SHIFT(166),
        [ts_sym_return_statement] = SHIFT(167),
        [ts_sym_declaration_statement] = SHIFT(167),
        [ts_sym_range_statement] = SHIFT(167),
        [ts_sym_if_statement] = SHIFT(167),
        [ts_sym_expression_statement] = SHIFT(167),
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(170),
        [ts_builtin_sym_error] = SHIFT(171),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(172),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(171),
        [ts_aux_sym_var] = SHIFT(173),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(174),
        [ts_aux_sym_11] = SHIFT(175),
        [ts_aux_sym_for] = SHIFT(176),
        [ts_aux_sym_if] = SHIFT(177),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [165] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [166] = {
        [ts_sym_var_declaration] = SHIFT(165),
        [ts_sym_statement] = SHIFT(166),
        [ts_sym_return_statement] = SHIFT(167),
        [ts_sym_declaration_statement] = SHIFT(167),
        [ts_sym_range_statement] = SHIFT(167),
        [ts_sym_if_statement] = SHIFT(167),
        [ts_sym_expression_statement] = SHIFT(167),
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(170),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(172),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(335),
        [ts_aux_sym_var] = SHIFT(173),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(174),
        [ts_aux_sym_11] = SHIFT(175),
        [ts_aux_sym_for] = SHIFT(176),
        [ts_aux_sym_if] = SHIFT(177),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [167] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [168] = {
        [ts_sym__line_break] = SHIFT(334),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(251),
        [ts_aux_sym_3] = SHIFT(334),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = SHIFT(253),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(254),
        [ts_aux_sym_15] = SHIFT(254),
        [ts_aux_sym_16] = SHIFT(255),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [169] = {
        [ts_sym__line_break] = REDUCE(ts_sym_expression, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [170] = {
        [ts_sym__line_break] = REDUCE(ts_sym_expression, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(327),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_10] = SHIFT(328),
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
    [171] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(326),
    },
    [172] = {
        [ts_sym__line_break] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [173] = {
        [ts_sym_var_name] = SHIFT(296),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(297),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [174] = {
        [ts_sym_expression] = SHIFT(268),
        [ts_sym_call_expression] = SHIFT(269),
        [ts_sym_selector_expression] = SHIFT(269),
        [ts_sym_math_op] = SHIFT(269),
        [ts_sym_bool_op] = SHIFT(269),
        [ts_sym_var_name] = SHIFT(269),
        [ts_sym__line_break] = SHIFT(270),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(270),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [175] = {
        [ts_sym_expression] = SHIFT(249),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [176] = {
        [ts_sym_var_name] = SHIFT(236),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(237),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [177] = {
        [ts_sym_expression] = SHIFT(181),
        [ts_sym_call_expression] = SHIFT(182),
        [ts_sym_selector_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(182),
        [ts_sym_bool_op] = SHIFT(182),
        [ts_sym_var_name] = SHIFT(182),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [178] = {
        [ts_sym_expression] = SHIFT(179),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [179] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [180] = {
        [ts_sym__line_break] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [181] = {
        [ts_sym_block_statement] = SHIFT(186),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(187),
        [ts_aux_sym_5] = SHIFT(188),
        [ts_aux_sym_7] = SHIFT(189),
        [ts_aux_sym_12] = SHIFT(190),
        [ts_aux_sym_13] = SHIFT(189),
        [ts_aux_sym_14] = SHIFT(191),
        [ts_aux_sym_15] = SHIFT(191),
        [ts_aux_sym_16] = SHIFT(192),
        [ts_aux_sym_17] = SHIFT(193),
        [ts_aux_sym_18] = SHIFT(194),
        [ts_aux_sym_19] = SHIFT(194),
        [ts_aux_sym_20] = SHIFT(194),
        [ts_aux_sym_21] = SHIFT(194),
        [ts_aux_sym_22] = SHIFT(194),
    },
    [182] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [183] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [184] = {
        [ts_sym_expression] = SHIFT(185),
        [ts_sym_call_expression] = SHIFT(182),
        [ts_sym_selector_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(182),
        [ts_sym_bool_op] = SHIFT(182),
        [ts_sym_var_name] = SHIFT(182),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [185] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [186] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
        [ts_aux_sym_else] = SHIFT(231),
        [ts_aux_sym_23] = REDUCE(ts_sym_if_statement, 3),
    },
    [187] = {
        [ts_sym_expression] = SHIFT(203),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(206),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [188] = {
        [ts_sym_var_declaration] = SHIFT(165),
        [ts_sym_statement] = SHIFT(166),
        [ts_sym_return_statement] = SHIFT(167),
        [ts_sym_declaration_statement] = SHIFT(167),
        [ts_sym_range_statement] = SHIFT(167),
        [ts_sym_if_statement] = SHIFT(167),
        [ts_sym_expression_statement] = SHIFT(167),
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(170),
        [ts_builtin_sym_error] = SHIFT(201),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(172),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(201),
        [ts_aux_sym_var] = SHIFT(173),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(174),
        [ts_aux_sym_11] = SHIFT(175),
        [ts_aux_sym_for] = SHIFT(176),
        [ts_aux_sym_if] = SHIFT(177),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [189] = {
        [ts_sym_expression] = SHIFT(200),
        [ts_sym_call_expression] = SHIFT(182),
        [ts_sym_selector_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(182),
        [ts_sym_bool_op] = SHIFT(182),
        [ts_sym_var_name] = SHIFT(182),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [190] = {
        [ts_sym_var_name] = SHIFT(199),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [191] = {
        [ts_sym_expression] = SHIFT(198),
        [ts_sym_call_expression] = SHIFT(182),
        [ts_sym_selector_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(182),
        [ts_sym_bool_op] = SHIFT(182),
        [ts_sym_var_name] = SHIFT(182),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [192] = {
        [ts_sym_expression] = SHIFT(197),
        [ts_sym_call_expression] = SHIFT(182),
        [ts_sym_selector_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(182),
        [ts_sym_bool_op] = SHIFT(182),
        [ts_sym_var_name] = SHIFT(182),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [193] = {
        [ts_sym_expression] = SHIFT(196),
        [ts_sym_call_expression] = SHIFT(182),
        [ts_sym_selector_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(182),
        [ts_sym_bool_op] = SHIFT(182),
        [ts_sym_var_name] = SHIFT(182),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [194] = {
        [ts_sym_expression] = SHIFT(195),
        [ts_sym_call_expression] = SHIFT(182),
        [ts_sym_selector_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(182),
        [ts_sym_bool_op] = SHIFT(182),
        [ts_sym_var_name] = SHIFT(182),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [195] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
        [ts_aux_sym_18] = SHIFT(194),
        [ts_aux_sym_19] = SHIFT(194),
        [ts_aux_sym_20] = SHIFT(194),
        [ts_aux_sym_21] = SHIFT(194),
        [ts_aux_sym_22] = SHIFT(194),
    },
    [196] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(189),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(189),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(193),
        [ts_aux_sym_18] = SHIFT(194),
        [ts_aux_sym_19] = SHIFT(194),
        [ts_aux_sym_20] = SHIFT(194),
        [ts_aux_sym_21] = SHIFT(194),
        [ts_aux_sym_22] = SHIFT(194),
    },
    [197] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(189),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(189),
        [ts_aux_sym_14] = SHIFT(191),
        [ts_aux_sym_15] = SHIFT(191),
        [ts_aux_sym_16] = SHIFT(192),
        [ts_aux_sym_17] = SHIFT(193),
        [ts_aux_sym_18] = SHIFT(194),
        [ts_aux_sym_19] = SHIFT(194),
        [ts_aux_sym_20] = SHIFT(194),
        [ts_aux_sym_21] = SHIFT(194),
        [ts_aux_sym_22] = SHIFT(194),
    },
    [198] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(189),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(189),
        [ts_aux_sym_14] = SHIFT(191),
        [ts_aux_sym_15] = SHIFT(191),
        [ts_aux_sym_16] = SHIFT(192),
        [ts_aux_sym_17] = SHIFT(193),
        [ts_aux_sym_18] = SHIFT(194),
        [ts_aux_sym_19] = SHIFT(194),
        [ts_aux_sym_20] = SHIFT(194),
        [ts_aux_sym_21] = SHIFT(194),
        [ts_aux_sym_22] = SHIFT(194),
    },
    [199] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [200] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(189),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(189),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(193),
        [ts_aux_sym_18] = SHIFT(194),
        [ts_aux_sym_19] = SHIFT(194),
        [ts_aux_sym_20] = SHIFT(194),
        [ts_aux_sym_21] = SHIFT(194),
        [ts_aux_sym_22] = SHIFT(194),
    },
    [201] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(202),
    },
    [202] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [203] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(209),
        [ts_aux_sym_1] = SHIFT(210),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(211),
        [ts_aux_sym_10] = SHIFT(212),
        [ts_aux_sym_12] = SHIFT(213),
        [ts_aux_sym_13] = SHIFT(211),
        [ts_aux_sym_14] = SHIFT(214),
        [ts_aux_sym_15] = SHIFT(214),
        [ts_aux_sym_16] = SHIFT(215),
        [ts_aux_sym_17] = SHIFT(216),
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [204] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [205] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [206] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [207] = {
        [ts_sym_expression] = SHIFT(208),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [208] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [209] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(230),
    },
    [210] = {
        [ts_sym_expression] = SHIFT(226),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(227),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [211] = {
        [ts_sym_expression] = SHIFT(225),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [212] = {
        [ts_sym_expression] = SHIFT(223),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [213] = {
        [ts_sym_var_name] = SHIFT(222),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [214] = {
        [ts_sym_expression] = SHIFT(221),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [215] = {
        [ts_sym_expression] = SHIFT(220),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [216] = {
        [ts_sym_expression] = SHIFT(219),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [217] = {
        [ts_sym_expression] = SHIFT(218),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [218] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [219] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(211),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(211),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(216),
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [220] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(211),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(211),
        [ts_aux_sym_14] = SHIFT(214),
        [ts_aux_sym_15] = SHIFT(214),
        [ts_aux_sym_16] = SHIFT(215),
        [ts_aux_sym_17] = SHIFT(216),
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [221] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(211),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(211),
        [ts_aux_sym_14] = SHIFT(214),
        [ts_aux_sym_15] = SHIFT(214),
        [ts_aux_sym_16] = SHIFT(215),
        [ts_aux_sym_17] = SHIFT(216),
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [222] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [223] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(224),
        [ts_aux_sym_1] = SHIFT(210),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(211),
        [ts_aux_sym_10] = SHIFT(212),
        [ts_aux_sym_12] = SHIFT(213),
        [ts_aux_sym_13] = SHIFT(211),
        [ts_aux_sym_14] = SHIFT(214),
        [ts_aux_sym_15] = SHIFT(214),
        [ts_aux_sym_16] = SHIFT(215),
        [ts_aux_sym_17] = SHIFT(216),
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [224] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 3),
    },
    [225] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(211),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(211),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(216),
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [226] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(228),
        [ts_aux_sym_1] = SHIFT(210),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(211),
        [ts_aux_sym_10] = SHIFT(212),
        [ts_aux_sym_12] = SHIFT(213),
        [ts_aux_sym_13] = SHIFT(211),
        [ts_aux_sym_14] = SHIFT(214),
        [ts_aux_sym_15] = SHIFT(214),
        [ts_aux_sym_16] = SHIFT(215),
        [ts_aux_sym_17] = SHIFT(216),
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [227] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [228] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(229),
    },
    [229] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [230] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [231] = {
        [ts_sym_block_statement] = SHIFT(232),
        [ts_sym_if_statement] = SHIFT(232),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(233),
        [ts_aux_sym_if] = SHIFT(177),
    },
    [232] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [233] = {
        [ts_sym_var_declaration] = SHIFT(165),
        [ts_sym_statement] = SHIFT(166),
        [ts_sym_return_statement] = SHIFT(167),
        [ts_sym_declaration_statement] = SHIFT(167),
        [ts_sym_range_statement] = SHIFT(167),
        [ts_sym_if_statement] = SHIFT(167),
        [ts_sym_expression_statement] = SHIFT(167),
        [ts_sym_expression] = SHIFT(168),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(170),
        [ts_builtin_sym_error] = SHIFT(234),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(172),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(234),
        [ts_aux_sym_var] = SHIFT(173),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 0),
        [ts_aux_sym_return] = SHIFT(174),
        [ts_aux_sym_11] = SHIFT(175),
        [ts_aux_sym_for] = SHIFT(176),
        [ts_aux_sym_if] = SHIFT(177),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [234] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(235),
    },
    [235] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [236] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = SHIFT(238),
        [ts_aux_sym_11] = SHIFT(239),
    },
    [237] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [238] = {
        [ts_sym_var_name] = SHIFT(243),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [239] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_range] = SHIFT(240),
    },
    [240] = {
        [ts_sym_expression] = SHIFT(241),
        [ts_sym_call_expression] = SHIFT(182),
        [ts_sym_selector_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(182),
        [ts_sym_bool_op] = SHIFT(182),
        [ts_sym_var_name] = SHIFT(182),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [241] = {
        [ts_sym_block_statement] = SHIFT(242),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(187),
        [ts_aux_sym_5] = SHIFT(233),
        [ts_aux_sym_7] = SHIFT(189),
        [ts_aux_sym_12] = SHIFT(190),
        [ts_aux_sym_13] = SHIFT(189),
        [ts_aux_sym_14] = SHIFT(191),
        [ts_aux_sym_15] = SHIFT(191),
        [ts_aux_sym_16] = SHIFT(192),
        [ts_aux_sym_17] = SHIFT(193),
        [ts_aux_sym_18] = SHIFT(194),
        [ts_aux_sym_19] = SHIFT(194),
        [ts_aux_sym_20] = SHIFT(194),
        [ts_aux_sym_21] = SHIFT(194),
        [ts_aux_sym_22] = SHIFT(194),
    },
    [242] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [243] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(245),
    },
    [244] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [245] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_range] = SHIFT(246),
    },
    [246] = {
        [ts_sym_expression] = SHIFT(247),
        [ts_sym_call_expression] = SHIFT(182),
        [ts_sym_selector_expression] = SHIFT(182),
        [ts_sym_math_op] = SHIFT(182),
        [ts_sym_bool_op] = SHIFT(182),
        [ts_sym_var_name] = SHIFT(182),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [247] = {
        [ts_sym_block_statement] = SHIFT(248),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(187),
        [ts_aux_sym_5] = SHIFT(233),
        [ts_aux_sym_7] = SHIFT(189),
        [ts_aux_sym_12] = SHIFT(190),
        [ts_aux_sym_13] = SHIFT(189),
        [ts_aux_sym_14] = SHIFT(191),
        [ts_aux_sym_15] = SHIFT(191),
        [ts_aux_sym_16] = SHIFT(192),
        [ts_aux_sym_17] = SHIFT(193),
        [ts_aux_sym_18] = SHIFT(194),
        [ts_aux_sym_19] = SHIFT(194),
        [ts_aux_sym_20] = SHIFT(194),
        [ts_aux_sym_21] = SHIFT(194),
        [ts_aux_sym_22] = SHIFT(194),
    },
    [248] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [249] = {
        [ts_sym__line_break] = SHIFT(250),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(251),
        [ts_aux_sym_3] = SHIFT(250),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = SHIFT(253),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(254),
        [ts_aux_sym_15] = SHIFT(254),
        [ts_aux_sym_16] = SHIFT(255),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [250] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [251] = {
        [ts_sym_expression] = SHIFT(264),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(265),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [252] = {
        [ts_sym_expression] = SHIFT(263),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [253] = {
        [ts_sym_var_name] = SHIFT(262),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [254] = {
        [ts_sym_expression] = SHIFT(261),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [255] = {
        [ts_sym_expression] = SHIFT(260),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [256] = {
        [ts_sym_expression] = SHIFT(259),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [257] = {
        [ts_sym_expression] = SHIFT(258),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [258] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [259] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [260] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(254),
        [ts_aux_sym_15] = SHIFT(254),
        [ts_aux_sym_16] = SHIFT(255),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [261] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(254),
        [ts_aux_sym_15] = SHIFT(254),
        [ts_aux_sym_16] = SHIFT(255),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [262] = {
        [ts_sym__line_break] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [263] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [264] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(266),
        [ts_aux_sym_1] = SHIFT(210),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(211),
        [ts_aux_sym_10] = SHIFT(212),
        [ts_aux_sym_12] = SHIFT(213),
        [ts_aux_sym_13] = SHIFT(211),
        [ts_aux_sym_14] = SHIFT(214),
        [ts_aux_sym_15] = SHIFT(214),
        [ts_aux_sym_16] = SHIFT(215),
        [ts_aux_sym_17] = SHIFT(216),
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [265] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [266] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(267),
    },
    [267] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [268] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(274),
        [ts_aux_sym_1] = SHIFT(275),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(276),
        [ts_aux_sym_10] = SHIFT(277),
        [ts_aux_sym_12] = SHIFT(278),
        [ts_aux_sym_13] = SHIFT(276),
        [ts_aux_sym_14] = SHIFT(279),
        [ts_aux_sym_15] = SHIFT(279),
        [ts_aux_sym_16] = SHIFT(280),
        [ts_aux_sym_17] = SHIFT(281),
        [ts_aux_sym_18] = SHIFT(282),
        [ts_aux_sym_19] = SHIFT(282),
        [ts_aux_sym_20] = SHIFT(282),
        [ts_aux_sym_21] = SHIFT(282),
        [ts_aux_sym_22] = SHIFT(282),
    },
    [269] = {
        [ts_sym__line_break] = REDUCE(ts_sym_expression, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [270] = {
        [ts_sym_expression] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_call_expression] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_selector_expression] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_math_op] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_bool_op] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym_var_name] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [271] = {
        [ts_sym__line_break] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [272] = {
        [ts_sym_expression] = SHIFT(273),
        [ts_sym_call_expression] = SHIFT(269),
        [ts_sym_selector_expression] = SHIFT(269),
        [ts_sym_math_op] = SHIFT(269),
        [ts_sym_bool_op] = SHIFT(269),
        [ts_sym_var_name] = SHIFT(269),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [273] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [274] = {
        [ts_sym__line_break] = SHIFT(295),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(295),
    },
    [275] = {
        [ts_sym_expression] = SHIFT(291),
        [ts_sym_call_expression] = SHIFT(204),
        [ts_sym_selector_expression] = SHIFT(204),
        [ts_sym_math_op] = SHIFT(204),
        [ts_sym_bool_op] = SHIFT(204),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(292),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [276] = {
        [ts_sym_expression] = SHIFT(290),
        [ts_sym_call_expression] = SHIFT(269),
        [ts_sym_selector_expression] = SHIFT(269),
        [ts_sym_math_op] = SHIFT(269),
        [ts_sym_bool_op] = SHIFT(269),
        [ts_sym_var_name] = SHIFT(269),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [277] = {
        [ts_sym_expression] = SHIFT(288),
        [ts_sym_call_expression] = SHIFT(269),
        [ts_sym_selector_expression] = SHIFT(269),
        [ts_sym_math_op] = SHIFT(269),
        [ts_sym_bool_op] = SHIFT(269),
        [ts_sym_var_name] = SHIFT(269),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [278] = {
        [ts_sym_var_name] = SHIFT(287),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [279] = {
        [ts_sym_expression] = SHIFT(286),
        [ts_sym_call_expression] = SHIFT(269),
        [ts_sym_selector_expression] = SHIFT(269),
        [ts_sym_math_op] = SHIFT(269),
        [ts_sym_bool_op] = SHIFT(269),
        [ts_sym_var_name] = SHIFT(269),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [280] = {
        [ts_sym_expression] = SHIFT(285),
        [ts_sym_call_expression] = SHIFT(269),
        [ts_sym_selector_expression] = SHIFT(269),
        [ts_sym_math_op] = SHIFT(269),
        [ts_sym_bool_op] = SHIFT(269),
        [ts_sym_var_name] = SHIFT(269),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [281] = {
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_call_expression] = SHIFT(269),
        [ts_sym_selector_expression] = SHIFT(269),
        [ts_sym_math_op] = SHIFT(269),
        [ts_sym_bool_op] = SHIFT(269),
        [ts_sym_var_name] = SHIFT(269),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [282] = {
        [ts_sym_expression] = SHIFT(283),
        [ts_sym_call_expression] = SHIFT(269),
        [ts_sym_selector_expression] = SHIFT(269),
        [ts_sym_math_op] = SHIFT(269),
        [ts_sym_bool_op] = SHIFT(269),
        [ts_sym_var_name] = SHIFT(269),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [283] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
        [ts_aux_sym_18] = SHIFT(282),
        [ts_aux_sym_19] = SHIFT(282),
        [ts_aux_sym_20] = SHIFT(282),
        [ts_aux_sym_21] = SHIFT(282),
        [ts_aux_sym_22] = SHIFT(282),
    },
    [284] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(276),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(276),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(281),
        [ts_aux_sym_18] = SHIFT(282),
        [ts_aux_sym_19] = SHIFT(282),
        [ts_aux_sym_20] = SHIFT(282),
        [ts_aux_sym_21] = SHIFT(282),
        [ts_aux_sym_22] = SHIFT(282),
    },
    [285] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(276),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(276),
        [ts_aux_sym_14] = SHIFT(279),
        [ts_aux_sym_15] = SHIFT(279),
        [ts_aux_sym_16] = SHIFT(280),
        [ts_aux_sym_17] = SHIFT(281),
        [ts_aux_sym_18] = SHIFT(282),
        [ts_aux_sym_19] = SHIFT(282),
        [ts_aux_sym_20] = SHIFT(282),
        [ts_aux_sym_21] = SHIFT(282),
        [ts_aux_sym_22] = SHIFT(282),
    },
    [286] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(276),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(276),
        [ts_aux_sym_14] = SHIFT(279),
        [ts_aux_sym_15] = SHIFT(279),
        [ts_aux_sym_16] = SHIFT(280),
        [ts_aux_sym_17] = SHIFT(281),
        [ts_aux_sym_18] = SHIFT(282),
        [ts_aux_sym_19] = SHIFT(282),
        [ts_aux_sym_20] = SHIFT(282),
        [ts_aux_sym_21] = SHIFT(282),
        [ts_aux_sym_22] = SHIFT(282),
    },
    [287] = {
        [ts_sym__line_break] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(289),
        [ts_aux_sym_1] = SHIFT(275),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(276),
        [ts_aux_sym_10] = SHIFT(277),
        [ts_aux_sym_12] = SHIFT(278),
        [ts_aux_sym_13] = SHIFT(276),
        [ts_aux_sym_14] = SHIFT(279),
        [ts_aux_sym_15] = SHIFT(279),
        [ts_aux_sym_16] = SHIFT(280),
        [ts_aux_sym_17] = SHIFT(281),
        [ts_aux_sym_18] = SHIFT(282),
        [ts_aux_sym_19] = SHIFT(282),
        [ts_aux_sym_20] = SHIFT(282),
        [ts_aux_sym_21] = SHIFT(282),
        [ts_aux_sym_22] = SHIFT(282),
    },
    [289] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
    },
    [290] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(276),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(276),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(281),
        [ts_aux_sym_18] = SHIFT(282),
        [ts_aux_sym_19] = SHIFT(282),
        [ts_aux_sym_20] = SHIFT(282),
        [ts_aux_sym_21] = SHIFT(282),
        [ts_aux_sym_22] = SHIFT(282),
    },
    [291] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(293),
        [ts_aux_sym_1] = SHIFT(210),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 0),
        [ts_aux_sym_7] = SHIFT(211),
        [ts_aux_sym_10] = SHIFT(212),
        [ts_aux_sym_12] = SHIFT(213),
        [ts_aux_sym_13] = SHIFT(211),
        [ts_aux_sym_14] = SHIFT(214),
        [ts_aux_sym_15] = SHIFT(214),
        [ts_aux_sym_16] = SHIFT(215),
        [ts_aux_sym_17] = SHIFT(216),
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [292] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [293] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(294),
    },
    [294] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [295] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [296] = {
        [ts_sym_type_expression] = SHIFT(298),
        [ts_sym_pointer_type] = SHIFT(299),
        [ts_sym_map_type] = SHIFT(299),
        [ts_sym_slice_type] = SHIFT(299),
        [ts_sym_struct_type] = SHIFT(299),
        [ts_sym_interface_type] = SHIFT(299),
        [ts_sym_type_name] = SHIFT(299),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(300),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(301),
        [ts_aux_sym_7] = SHIFT(302),
        [ts_aux_sym_map] = SHIFT(303),
        [ts_aux_sym_8] = SHIFT(304),
        [ts_aux_sym_struct] = SHIFT(305),
        [ts_aux_sym_interface] = SHIFT(306),
    },
    [297] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
    },
    [298] = {
        [ts_sym__line_break] = SHIFT(322),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(322),
        [ts_aux_sym_4] = SHIFT(323),
    },
    [299] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_expression, 1),
    },
    [300] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_name, 1),
    },
    [301] = {
        [ts_sym_expression] = SHIFT(320),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [302] = {
        [ts_sym_type_expression] = SHIFT(319),
        [ts_sym_pointer_type] = SHIFT(299),
        [ts_sym_map_type] = SHIFT(299),
        [ts_sym_slice_type] = SHIFT(299),
        [ts_sym_struct_type] = SHIFT(299),
        [ts_sym_interface_type] = SHIFT(299),
        [ts_sym_type_name] = SHIFT(299),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(300),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(302),
        [ts_aux_sym_map] = SHIFT(303),
        [ts_aux_sym_8] = SHIFT(304),
        [ts_aux_sym_struct] = SHIFT(305),
        [ts_aux_sym_interface] = SHIFT(306),
    },
    [303] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(315),
    },
    [304] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(313),
    },
    [305] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(310),
    },
    [306] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(307),
    },
    [307] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(308),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [308] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(309),
    },
    [309] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_interface_type, 4),
    },
    [310] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(311),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [311] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(312),
    },
    [312] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_struct_type, 4),
    },
    [313] = {
        [ts_sym_type_expression] = SHIFT(314),
        [ts_sym_pointer_type] = SHIFT(299),
        [ts_sym_map_type] = SHIFT(299),
        [ts_sym_slice_type] = SHIFT(299),
        [ts_sym_struct_type] = SHIFT(299),
        [ts_sym_interface_type] = SHIFT(299),
        [ts_sym_type_name] = SHIFT(299),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(300),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(302),
        [ts_aux_sym_map] = SHIFT(303),
        [ts_aux_sym_8] = SHIFT(304),
        [ts_aux_sym_struct] = SHIFT(305),
        [ts_aux_sym_interface] = SHIFT(306),
    },
    [314] = {
        [ts_sym__line_break] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_slice_type, 3),
    },
    [315] = {
        [ts_sym_type_expression] = SHIFT(316),
        [ts_sym_pointer_type] = SHIFT(122),
        [ts_sym_map_type] = SHIFT(122),
        [ts_sym_slice_type] = SHIFT(122),
        [ts_sym_struct_type] = SHIFT(122),
        [ts_sym_interface_type] = SHIFT(122),
        [ts_sym_type_name] = SHIFT(122),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(123),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(124),
        [ts_aux_sym_map] = SHIFT(125),
        [ts_aux_sym_8] = SHIFT(126),
        [ts_aux_sym_struct] = SHIFT(127),
        [ts_aux_sym_interface] = SHIFT(128),
    },
    [316] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(317),
    },
    [317] = {
        [ts_sym_type_expression] = SHIFT(318),
        [ts_sym_pointer_type] = SHIFT(299),
        [ts_sym_map_type] = SHIFT(299),
        [ts_sym_slice_type] = SHIFT(299),
        [ts_sym_struct_type] = SHIFT(299),
        [ts_sym_interface_type] = SHIFT(299),
        [ts_sym_type_name] = SHIFT(299),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(300),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(302),
        [ts_aux_sym_map] = SHIFT(303),
        [ts_aux_sym_8] = SHIFT(304),
        [ts_aux_sym_struct] = SHIFT(305),
        [ts_aux_sym_interface] = SHIFT(306),
    },
    [318] = {
        [ts_sym__line_break] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_4] = REDUCE(ts_sym_map_type, 5),
    },
    [319] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_pointer_type, 2),
    },
    [320] = {
        [ts_sym__line_break] = SHIFT(321),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(251),
        [ts_aux_sym_3] = SHIFT(321),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = SHIFT(253),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(254),
        [ts_aux_sym_15] = SHIFT(254),
        [ts_aux_sym_16] = SHIFT(255),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [321] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [322] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [323] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [324] = {
        [ts_sym__line_break] = SHIFT(325),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(251),
        [ts_aux_sym_3] = SHIFT(325),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = SHIFT(253),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(254),
        [ts_aux_sym_15] = SHIFT(254),
        [ts_aux_sym_16] = SHIFT(255),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [325] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [326] = {
        [ts_sym__line_break] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_block_statement, 3),
    },
    [327] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(331),
    },
    [328] = {
        [ts_sym_var_name] = SHIFT(329),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(237),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [329] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(330),
        [ts_aux_sym_10] = SHIFT(328),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 0),
    },
    [330] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 3),
    },
    [331] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [332] = {
        [ts_sym__line_break] = SHIFT(333),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(251),
        [ts_aux_sym_3] = SHIFT(333),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = SHIFT(253),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(254),
        [ts_aux_sym_15] = SHIFT(254),
        [ts_aux_sym_16] = SHIFT(255),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [333] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [334] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [335] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 2),
    },
    [336] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_func] = REDUCE(ts_sym_func_declaration, 5),
    },
    [337] = {
        [ts_sym_type_expression] = SHIFT(338),
        [ts_sym_pointer_type] = SHIFT(299),
        [ts_sym_map_type] = SHIFT(299),
        [ts_sym_slice_type] = SHIFT(299),
        [ts_sym_struct_type] = SHIFT(299),
        [ts_sym_interface_type] = SHIFT(299),
        [ts_sym_type_name] = SHIFT(299),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(300),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(339),
        [ts_aux_sym_7] = SHIFT(302),
        [ts_aux_sym_map] = SHIFT(303),
        [ts_aux_sym_8] = SHIFT(304),
        [ts_aux_sym_struct] = SHIFT(305),
        [ts_aux_sym_interface] = SHIFT(306),
    },
    [338] = {
        [ts_sym__line_break] = SHIFT(342),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(342),
        [ts_aux_sym_4] = SHIFT(343),
    },
    [339] = {
        [ts_sym_expression] = SHIFT(340),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [340] = {
        [ts_sym__line_break] = SHIFT(341),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(251),
        [ts_aux_sym_3] = SHIFT(341),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = SHIFT(253),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(254),
        [ts_aux_sym_15] = SHIFT(254),
        [ts_aux_sym_16] = SHIFT(255),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [341] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [342] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_4] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_func] = REDUCE(ts_sym_var_declaration, 4),
    },
    [343] = {
        [ts_sym_expression] = SHIFT(344),
        [ts_sym_call_expression] = SHIFT(169),
        [ts_sym_selector_expression] = SHIFT(169),
        [ts_sym_math_op] = SHIFT(169),
        [ts_sym_bool_op] = SHIFT(169),
        [ts_sym_var_name] = SHIFT(169),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [344] = {
        [ts_sym__line_break] = SHIFT(345),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(251),
        [ts_aux_sym_3] = SHIFT(345),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_12] = SHIFT(253),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(254),
        [ts_aux_sym_15] = SHIFT(254),
        [ts_aux_sym_16] = SHIFT(255),
        [ts_aux_sym_17] = SHIFT(256),
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [345] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
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
    [346] = {
        [ts_sym_type_expression] = SHIFT(348),
        [ts_sym_pointer_type] = SHIFT(349),
        [ts_sym_map_type] = SHIFT(349),
        [ts_sym_slice_type] = SHIFT(349),
        [ts_sym_struct_type] = SHIFT(349),
        [ts_sym_interface_type] = SHIFT(349),
        [ts_sym_type_name] = SHIFT(349),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(350),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(351),
        [ts_aux_sym_map] = SHIFT(352),
        [ts_aux_sym_8] = SHIFT(353),
        [ts_aux_sym_struct] = SHIFT(354),
        [ts_aux_sym_interface] = SHIFT(355),
    },
    [347] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_type_name, 1),
    },
    [348] = {
        [ts_sym__line_break] = SHIFT(369),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(369),
    },
    [349] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
    },
    [350] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_name, 1),
    },
    [351] = {
        [ts_sym_type_expression] = SHIFT(368),
        [ts_sym_pointer_type] = SHIFT(349),
        [ts_sym_map_type] = SHIFT(349),
        [ts_sym_slice_type] = SHIFT(349),
        [ts_sym_struct_type] = SHIFT(349),
        [ts_sym_interface_type] = SHIFT(349),
        [ts_sym_type_name] = SHIFT(349),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(350),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(351),
        [ts_aux_sym_map] = SHIFT(352),
        [ts_aux_sym_8] = SHIFT(353),
        [ts_aux_sym_struct] = SHIFT(354),
        [ts_aux_sym_interface] = SHIFT(355),
    },
    [352] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(364),
    },
    [353] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(362),
    },
    [354] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(359),
    },
    [355] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(356),
    },
    [356] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(357),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [357] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(358),
    },
    [358] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
    },
    [359] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(360),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [360] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(361),
    },
    [361] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 4),
    },
    [362] = {
        [ts_sym_type_expression] = SHIFT(363),
        [ts_sym_pointer_type] = SHIFT(349),
        [ts_sym_map_type] = SHIFT(349),
        [ts_sym_slice_type] = SHIFT(349),
        [ts_sym_struct_type] = SHIFT(349),
        [ts_sym_interface_type] = SHIFT(349),
        [ts_sym_type_name] = SHIFT(349),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(350),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(351),
        [ts_aux_sym_map] = SHIFT(352),
        [ts_aux_sym_8] = SHIFT(353),
        [ts_aux_sym_struct] = SHIFT(354),
        [ts_aux_sym_interface] = SHIFT(355),
    },
    [363] = {
        [ts_sym__line_break] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_slice_type, 3),
    },
    [364] = {
        [ts_sym_type_expression] = SHIFT(365),
        [ts_sym_pointer_type] = SHIFT(122),
        [ts_sym_map_type] = SHIFT(122),
        [ts_sym_slice_type] = SHIFT(122),
        [ts_sym_struct_type] = SHIFT(122),
        [ts_sym_interface_type] = SHIFT(122),
        [ts_sym_type_name] = SHIFT(122),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(123),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(124),
        [ts_aux_sym_map] = SHIFT(125),
        [ts_aux_sym_8] = SHIFT(126),
        [ts_aux_sym_struct] = SHIFT(127),
        [ts_aux_sym_interface] = SHIFT(128),
    },
    [365] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(366),
    },
    [366] = {
        [ts_sym_type_expression] = SHIFT(367),
        [ts_sym_pointer_type] = SHIFT(349),
        [ts_sym_map_type] = SHIFT(349),
        [ts_sym_slice_type] = SHIFT(349),
        [ts_sym_struct_type] = SHIFT(349),
        [ts_sym_interface_type] = SHIFT(349),
        [ts_sym_type_name] = SHIFT(349),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(350),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(351),
        [ts_aux_sym_map] = SHIFT(352),
        [ts_aux_sym_8] = SHIFT(353),
        [ts_aux_sym_struct] = SHIFT(354),
        [ts_aux_sym_interface] = SHIFT(355),
    },
    [367] = {
        [ts_sym__line_break] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
    },
    [368] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
    },
    [369] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_type_declaration, 4),
    },
    [370] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [371] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__whitespace] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_golang);
