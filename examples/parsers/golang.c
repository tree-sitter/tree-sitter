#include "tree_sitter/parser.h"

#define STATE_COUNT 431
#define SYMBOL_COUNT 88

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

static const char *ts_symbol_names[] = {
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

static const int ts_hidden_symbol_flags[SYMBOL_COUNT] = {
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

static TSTree *ts_lex(TSLexer *lexer, TSStateId lex_state) {
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
            if (lookahead == 0)
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
            if (lookahead == 0)
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
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(32);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 33:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 34:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(34);
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
        case 35:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(35);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 36:
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '\\')
                ADVANCE(38);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(36);
            LEX_ERROR();
        case 37:
            ACCEPT_TOKEN(ts_sym_string);
        case 38:
            if (lookahead == '\"')
                ADVANCE(39);
            if (lookahead == '\\')
                ADVANCE(38);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(36);
            LEX_ERROR();
        case 39:
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '\\')
                ADVANCE(38);
            if (!((lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(36);
            ACCEPT_TOKEN(ts_sym_string);
        case 40:
            ACCEPT_TOKEN(ts_aux_sym_1);
        case 41:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(41);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
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
            if (lookahead == '{')
                ADVANCE(43);
            LEX_ERROR();
        case 43:
            ACCEPT_TOKEN(ts_aux_sym_5);
        case 44:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(44);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(45);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 45:
            ACCEPT_TOKEN(ts_aux_sym_2);
        case 46:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(46);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(49);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'm')
                ADVANCE(59);
            if (lookahead == 's')
                ADVANCE(62);
            LEX_ERROR();
        case 47:
            ACCEPT_TOKEN(ts_aux_sym_7);
        case 48:
            ACCEPT_TOKEN(ts_aux_sym_10);
        case 49:
            ACCEPT_TOKEN(ts_aux_sym_8);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
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
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_interface);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(61);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_map);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(64);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(65);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_struct);
        case 68:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(68);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '{')
                ADVANCE(43);
            LEX_ERROR();
        case 69:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(45);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 70:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(70);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(45);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 71:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(71);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(45);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 72:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(72);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(49);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'm')
                ADVANCE(59);
            if (lookahead == 's')
                ADVANCE(62);
            LEX_ERROR();
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
            if (lookahead == '[')
                ADVANCE(49);
            LEX_ERROR();
        case 74:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(74);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ']')
                ADVANCE(75);
            LEX_ERROR();
        case 75:
            ACCEPT_TOKEN(ts_aux_sym_9);
        case 76:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(76);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 77:
            ACCEPT_TOKEN(ts_aux_sym_6);
        case 78:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(78);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 79:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 80:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(81);
            LEX_ERROR();
        case 81:
            ACCEPT_TOKEN(ts_aux_sym_3);
        case 82:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(82);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(87);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'i')
                ADVANCE(92);
            if (lookahead == 'r')
                ADVANCE(94);
            if (lookahead == 'v')
                ADVANCE(100);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 83:
            ACCEPT_TOKEN(ts_aux_sym_23);
        case 84:
            if (lookahead == '.')
                ADVANCE(85);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            ACCEPT_TOKEN(ts_sym_number);
        case 85:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            LEX_ERROR();
        case 86:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            ACCEPT_TOKEN(ts_sym_number);
        case 87:
            if (lookahead == '=')
                ADVANCE(88);
            LEX_ERROR();
        case 88:
            ACCEPT_TOKEN(ts_aux_sym_11);
        case 89:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(90);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(91);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_for);
        case 92:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(93);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(95);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 95:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 96:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 97:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(98);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(99);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 99:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_return);
        case 100:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(101);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(102);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_var);
        case 103:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(103);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(112);
            if (lookahead == '>')
                ADVANCE(114);
            if (lookahead == '|')
                ADVANCE(116);
            LEX_ERROR();
        case 104:
            if (lookahead == '&')
                ADVANCE(105);
            LEX_ERROR();
        case 105:
            ACCEPT_TOKEN(ts_aux_sym_17);
        case 106:
            ACCEPT_TOKEN(ts_aux_sym_14);
        case 107:
            ACCEPT_TOKEN(ts_aux_sym_15);
        case 108:
            ACCEPT_TOKEN(ts_aux_sym_12);
        case 109:
            if (lookahead == '/')
                ADVANCE(4);
            ACCEPT_TOKEN(ts_aux_sym_13);
        case 110:
            if (lookahead == '=')
                ADVANCE(111);
            ACCEPT_TOKEN(ts_aux_sym_20);
        case 111:
            ACCEPT_TOKEN(ts_aux_sym_19);
        case 112:
            if (lookahead == '=')
                ADVANCE(113);
            LEX_ERROR();
        case 113:
            ACCEPT_TOKEN(ts_aux_sym_18);
        case 114:
            if (lookahead == '=')
                ADVANCE(115);
            ACCEPT_TOKEN(ts_aux_sym_22);
        case 115:
            ACCEPT_TOKEN(ts_aux_sym_21);
        case 116:
            if (lookahead == '|')
                ADVANCE(117);
            LEX_ERROR();
        case 117:
            ACCEPT_TOKEN(ts_aux_sym_16);
        case 118:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(118);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if (lookahead == ':')
                ADVANCE(87);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(112);
            if (lookahead == '>')
                ADVANCE(114);
            if (lookahead == '|')
                ADVANCE(116);
            LEX_ERROR();
        case 119:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (lookahead == ';')
                ADVANCE(81);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 120:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(120);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 121:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(112);
            if (lookahead == '>')
                ADVANCE(114);
            if (lookahead == '{')
                ADVANCE(43);
            if (lookahead == '|')
                ADVANCE(116);
            LEX_ERROR();
        case 122:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(122);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(87);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(123);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'i')
                ADVANCE(92);
            if (lookahead == 'r')
                ADVANCE(94);
            if (lookahead == 'v')
                ADVANCE(100);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 123:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'l')
                ADVANCE(124);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(125);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(126);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 126:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_else);
        case 127:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == ')')
                ADVANCE(45);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
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
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == ')')
                ADVANCE(45);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(112);
            if (lookahead == '>')
                ADVANCE(114);
            if (lookahead == '|')
                ADVANCE(116);
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
            if (lookahead == 'i')
                ADVANCE(130);
            if (lookahead == '{')
                ADVANCE(43);
            LEX_ERROR();
        case 130:
            if (lookahead == 'f')
                ADVANCE(131);
            LEX_ERROR();
        case 131:
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 132:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(87);
            LEX_ERROR();
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'r')
                ADVANCE(134);
            LEX_ERROR();
        case 134:
            if (lookahead == 'a')
                ADVANCE(135);
            LEX_ERROR();
        case 135:
            if (lookahead == 'n')
                ADVANCE(136);
            LEX_ERROR();
        case 136:
            if (lookahead == 'g')
                ADVANCE(137);
            LEX_ERROR();
        case 137:
            if (lookahead == 'e')
                ADVANCE(138);
            LEX_ERROR();
        case 138:
            ACCEPT_TOKEN(ts_aux_sym_range);
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(87);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(87);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(112);
            if (lookahead == '>')
                ADVANCE(114);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'i')
                ADVANCE(92);
            if (lookahead == 'r')
                ADVANCE(94);
            if (lookahead == 'v')
                ADVANCE(100);
            if (lookahead == '|')
                ADVANCE(116);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(112);
            if (lookahead == '>')
                ADVANCE(114);
            if (lookahead == '|')
                ADVANCE(116);
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
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(87);
            if (lookahead == ';')
                ADVANCE(81);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'i')
                ADVANCE(92);
            if (lookahead == 'r')
                ADVANCE(94);
            if (lookahead == 'v')
                ADVANCE(100);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 143:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(143);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(87);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(112);
            if (lookahead == '>')
                ADVANCE(114);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'i')
                ADVANCE(92);
            if (lookahead == 'r')
                ADVANCE(94);
            if (lookahead == 'v')
                ADVANCE(100);
            if (lookahead == '|')
                ADVANCE(116);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 144:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(145);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(49);
            if (lookahead == 'i')
                ADVANCE(50);
            if (lookahead == 'm')
                ADVANCE(59);
            if (lookahead == 's')
                ADVANCE(62);
            LEX_ERROR();
        case 145:
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 146:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '=')
                ADVANCE(145);
            LEX_ERROR();
        case 147:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(147);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(87);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '=')
                ADVANCE(145);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(89);
            if (lookahead == 'i')
                ADVANCE(92);
            if (lookahead == 'r')
                ADVANCE(94);
            if (lookahead == 'v')
                ADVANCE(100);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 148:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            LEX_ERROR();
        case 149:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(149);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(112);
            if (lookahead == '>')
                ADVANCE(114);
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            if (lookahead == '|')
                ADVANCE(116);
            LEX_ERROR();
        case 150:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(150);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '=')
                ADVANCE(145);
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            LEX_ERROR();
        case 151:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(151);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == ')')
                ADVANCE(45);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 152:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(152);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == ')')
                ADVANCE(45);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(87);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(114);
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
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(49);
            if (lookahead == ']')
                ADVANCE(75);
            if (lookahead == 'e')
                ADVANCE(123);
            if (lookahead == 'f')
                ADVANCE(154);
            if (lookahead == 'i')
                ADVANCE(158);
            if (lookahead == 'm')
                ADVANCE(59);
            if (lookahead == 'p')
                ADVANCE(164);
            if (lookahead == 'r')
                ADVANCE(171);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(176);
            if (lookahead == 'v')
                ADVANCE(100);
            if (lookahead == '{')
                ADVANCE(43);
            if (lookahead == '|')
                ADVANCE(116);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        case 153:
            if (lookahead == '=')
                ADVANCE(113);
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 154:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(155);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 155:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(156);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 156:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(157);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 157:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_func);
        case 158:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(93);
            if (lookahead == 'm')
                ADVANCE(159);
            if (lookahead == 'n')
                ADVANCE(51);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 159:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(160);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 160:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(161);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 161:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(162);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 162:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(163);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 163:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_import);
        case 164:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(165);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 165:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(166);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 166:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'k')
                ADVANCE(167);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 167:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(168);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 168:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(169);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 169:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(170);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 170:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_package);
        case 171:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(172);
            if (lookahead == 'e')
                ADVANCE(95);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 172:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(173);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 173:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(174);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 174:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(175);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 175:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_range);
        case 176:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(33);
            if (lookahead == 'y')
                ADVANCE(177);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 177:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(178);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 178:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(179);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 179:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_type);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(152);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(83);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(104);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == ')')
                ADVANCE(45);
            if (lookahead == '*')
                ADVANCE(47);
            if (lookahead == '+')
                ADVANCE(106);
            if (lookahead == ',')
                ADVANCE(48);
            if (lookahead == '-')
                ADVANCE(107);
            if (lookahead == '.')
                ADVANCE(108);
            if (lookahead == '/')
                ADVANCE(109);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            if (lookahead == ':')
                ADVANCE(87);
            if (lookahead == ';')
                ADVANCE(81);
            if (lookahead == '<')
                ADVANCE(110);
            if (lookahead == '=')
                ADVANCE(153);
            if (lookahead == '>')
                ADVANCE(114);
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
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(49);
            if (lookahead == ']')
                ADVANCE(75);
            if (lookahead == 'e')
                ADVANCE(123);
            if (lookahead == 'f')
                ADVANCE(154);
            if (lookahead == 'i')
                ADVANCE(158);
            if (lookahead == 'm')
                ADVANCE(59);
            if (lookahead == 'p')
                ADVANCE(164);
            if (lookahead == 'r')
                ADVANCE(171);
            if (lookahead == 's')
                ADVANCE(62);
            if (lookahead == 't')
                ADVANCE(176);
            if (lookahead == 'v')
                ADVANCE(100);
            if (lookahead == '{')
                ADVANCE(43);
            if (lookahead == '|')
                ADVANCE(116);
            if (lookahead == '}')
                ADVANCE(77);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 12,
    [2] = 14,
    [3] = 32,
    [4] = 14,
    [5] = 14,
    [6] = 14,
    [7] = 34,
    [8] = 34,
    [9] = 34,
    [10] = 12,
    [11] = 35,
    [12] = 32,
    [13] = 32,
    [14] = 32,
    [15] = 41,
    [16] = 41,
    [17] = 42,
    [18] = 44,
    [19] = 46,
    [20] = 46,
    [21] = 68,
    [22] = 42,
    [23] = 42,
    [24] = 32,
    [25] = 32,
    [26] = 69,
    [27] = 70,
    [28] = 71,
    [29] = 42,
    [30] = 32,
    [31] = 69,
    [32] = 69,
    [33] = 71,
    [34] = 42,
    [35] = 69,
    [36] = 71,
    [37] = 32,
    [38] = 32,
    [39] = 32,
    [40] = 69,
    [41] = 71,
    [42] = 42,
    [43] = 69,
    [44] = 69,
    [45] = 72,
    [46] = 72,
    [47] = 73,
    [48] = 74,
    [49] = 42,
    [50] = 42,
    [51] = 32,
    [52] = 46,
    [53] = 72,
    [54] = 76,
    [55] = 41,
    [56] = 78,
    [57] = 69,
    [58] = 69,
    [59] = 76,
    [60] = 44,
    [61] = 46,
    [62] = 79,
    [63] = 76,
    [64] = 76,
    [65] = 32,
    [66] = 32,
    [67] = 69,
    [68] = 71,
    [69] = 76,
    [70] = 76,
    [71] = 69,
    [72] = 71,
    [73] = 76,
    [74] = 69,
    [75] = 72,
    [76] = 69,
    [77] = 71,
    [78] = 79,
    [79] = 32,
    [80] = 46,
    [81] = 69,
    [82] = 72,
    [83] = 32,
    [84] = 46,
    [85] = 72,
    [86] = 69,
    [87] = 71,
    [88] = 71,
    [89] = 32,
    [90] = 32,
    [91] = 69,
    [92] = 71,
    [93] = 76,
    [94] = 76,
    [95] = 69,
    [96] = 71,
    [97] = 76,
    [98] = 79,
    [99] = 32,
    [100] = 32,
    [101] = 69,
    [102] = 69,
    [103] = 71,
    [104] = 76,
    [105] = 71,
    [106] = 79,
    [107] = 32,
    [108] = 32,
    [109] = 69,
    [110] = 71,
    [111] = 69,
    [112] = 78,
    [113] = 76,
    [114] = 72,
    [115] = 72,
    [116] = 78,
    [117] = 69,
    [118] = 69,
    [119] = 76,
    [120] = 76,
    [121] = 72,
    [122] = 73,
    [123] = 74,
    [124] = 42,
    [125] = 42,
    [126] = 76,
    [127] = 78,
    [128] = 76,
    [129] = 76,
    [130] = 76,
    [131] = 78,
    [132] = 76,
    [133] = 76,
    [134] = 72,
    [135] = 76,
    [136] = 72,
    [137] = 74,
    [138] = 74,
    [139] = 74,
    [140] = 72,
    [141] = 73,
    [142] = 74,
    [143] = 42,
    [144] = 42,
    [145] = 76,
    [146] = 78,
    [147] = 74,
    [148] = 74,
    [149] = 76,
    [150] = 78,
    [151] = 74,
    [152] = 74,
    [153] = 72,
    [154] = 74,
    [155] = 72,
    [156] = 74,
    [157] = 72,
    [158] = 74,
    [159] = 74,
    [160] = 72,
    [161] = 76,
    [162] = 76,
    [163] = 78,
    [164] = 72,
    [165] = 69,
    [166] = 72,
    [167] = 74,
    [168] = 72,
    [169] = 69,
    [170] = 69,
    [171] = 69,
    [172] = 71,
    [173] = 68,
    [174] = 32,
    [175] = 32,
    [176] = 69,
    [177] = 71,
    [178] = 42,
    [179] = 42,
    [180] = 69,
    [181] = 71,
    [182] = 42,
    [183] = 68,
    [184] = 32,
    [185] = 32,
    [186] = 69,
    [187] = 69,
    [188] = 71,
    [189] = 42,
    [190] = 71,
    [191] = 68,
    [192] = 32,
    [193] = 32,
    [194] = 69,
    [195] = 71,
    [196] = 69,
    [197] = 80,
    [198] = 82,
    [199] = 82,
    [200] = 82,
    [201] = 82,
    [202] = 103,
    [203] = 103,
    [204] = 118,
    [205] = 78,
    [206] = 118,
    [207] = 32,
    [208] = 80,
    [209] = 119,
    [210] = 120,
    [211] = 32,
    [212] = 120,
    [213] = 120,
    [214] = 103,
    [215] = 103,
    [216] = 121,
    [217] = 121,
    [218] = 121,
    [219] = 120,
    [220] = 121,
    [221] = 122,
    [222] = 127,
    [223] = 82,
    [224] = 120,
    [225] = 32,
    [226] = 120,
    [227] = 120,
    [228] = 120,
    [229] = 120,
    [230] = 121,
    [231] = 121,
    [232] = 121,
    [233] = 121,
    [234] = 121,
    [235] = 121,
    [236] = 78,
    [237] = 122,
    [238] = 122,
    [239] = 128,
    [240] = 128,
    [241] = 128,
    [242] = 121,
    [243] = 120,
    [244] = 128,
    [245] = 71,
    [246] = 127,
    [247] = 121,
    [248] = 120,
    [249] = 120,
    [250] = 32,
    [251] = 120,
    [252] = 120,
    [253] = 120,
    [254] = 120,
    [255] = 128,
    [256] = 128,
    [257] = 128,
    [258] = 128,
    [259] = 128,
    [260] = 128,
    [261] = 71,
    [262] = 128,
    [263] = 128,
    [264] = 128,
    [265] = 71,
    [266] = 128,
    [267] = 128,
    [268] = 121,
    [269] = 129,
    [270] = 82,
    [271] = 82,
    [272] = 78,
    [273] = 82,
    [274] = 82,
    [275] = 132,
    [276] = 132,
    [277] = 32,
    [278] = 133,
    [279] = 120,
    [280] = 121,
    [281] = 82,
    [282] = 139,
    [283] = 139,
    [284] = 133,
    [285] = 120,
    [286] = 121,
    [287] = 82,
    [288] = 103,
    [289] = 140,
    [290] = 127,
    [291] = 120,
    [292] = 32,
    [293] = 120,
    [294] = 120,
    [295] = 120,
    [296] = 120,
    [297] = 103,
    [298] = 103,
    [299] = 103,
    [300] = 103,
    [301] = 103,
    [302] = 103,
    [303] = 128,
    [304] = 103,
    [305] = 71,
    [306] = 103,
    [307] = 103,
    [308] = 141,
    [309] = 141,
    [310] = 142,
    [311] = 141,
    [312] = 120,
    [313] = 141,
    [314] = 143,
    [315] = 80,
    [316] = 127,
    [317] = 120,
    [318] = 120,
    [319] = 32,
    [320] = 120,
    [321] = 120,
    [322] = 120,
    [323] = 120,
    [324] = 141,
    [325] = 141,
    [326] = 141,
    [327] = 141,
    [328] = 141,
    [329] = 141,
    [330] = 80,
    [331] = 141,
    [332] = 128,
    [333] = 141,
    [334] = 71,
    [335] = 141,
    [336] = 141,
    [337] = 142,
    [338] = 144,
    [339] = 144,
    [340] = 146,
    [341] = 146,
    [342] = 146,
    [343] = 120,
    [344] = 72,
    [345] = 73,
    [346] = 74,
    [347] = 42,
    [348] = 42,
    [349] = 76,
    [350] = 78,
    [351] = 146,
    [352] = 146,
    [353] = 76,
    [354] = 78,
    [355] = 146,
    [356] = 146,
    [357] = 72,
    [358] = 146,
    [359] = 72,
    [360] = 74,
    [361] = 72,
    [362] = 146,
    [363] = 146,
    [364] = 103,
    [365] = 140,
    [366] = 147,
    [367] = 120,
    [368] = 103,
    [369] = 140,
    [370] = 80,
    [371] = 139,
    [372] = 32,
    [373] = 120,
    [374] = 103,
    [375] = 140,
    [376] = 132,
    [377] = 139,
    [378] = 120,
    [379] = 103,
    [380] = 140,
    [381] = 140,
    [382] = 78,
    [383] = 148,
    [384] = 144,
    [385] = 146,
    [386] = 120,
    [387] = 103,
    [388] = 149,
    [389] = 150,
    [390] = 120,
    [391] = 103,
    [392] = 149,
    [393] = 72,
    [394] = 72,
    [395] = 80,
    [396] = 80,
    [397] = 80,
    [398] = 72,
    [399] = 73,
    [400] = 74,
    [401] = 42,
    [402] = 42,
    [403] = 76,
    [404] = 78,
    [405] = 80,
    [406] = 80,
    [407] = 76,
    [408] = 78,
    [409] = 80,
    [410] = 80,
    [411] = 72,
    [412] = 80,
    [413] = 72,
    [414] = 74,
    [415] = 72,
    [416] = 80,
    [417] = 80,
    [418] = 148,
    [419] = 14,
    [420] = 14,
    [421] = 151,
    [422] = 151,
    [423] = 71,
    [424] = 151,
    [425] = 14,
    [426] = 14,
    [427] = 71,
    [428] = 12,
    [429] = 12,
    [430] = 34,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [ts_sym_program] = SHIFT(1),
        [ts_sym_package_directive] = SHIFT(2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_package] = SHIFT(3),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [2] = {
        [ts_sym_imports_block] = SHIFT(6),
        [ts_sym_declaration] = SHIFT(7),
        [ts_sym_type_declaration] = SHIFT(8),
        [ts_sym_var_declaration] = SHIFT(8),
        [ts_sym_func_declaration] = SHIFT(8),
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = SHIFT(9),
        [ts_aux_sym_program_repeat1] = SHIFT(10),
        [ts_aux_sym_import] = SHIFT(11),
        [ts_aux_sym_type] = SHIFT(12),
        [ts_aux_sym_var] = SHIFT(13),
        [ts_aux_sym_func] = SHIFT(14),
    },
    [3] = {
        [ts_sym_package_name] = SHIFT(4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(5),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [4] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_directive, 2),
    },
    [5] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_name, 1),
    },
    [6] = {
        [ts_sym_imports_block] = SHIFT(6),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = SHIFT(430),
        [ts_aux_sym_import] = SHIFT(11),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 1),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 1),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 1),
    },
    [7] = {
        [ts_sym_declaration] = SHIFT(7),
        [ts_sym_type_declaration] = SHIFT(8),
        [ts_sym_var_declaration] = SHIFT(8),
        [ts_sym_func_declaration] = SHIFT(8),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = SHIFT(429),
        [ts_aux_sym_type] = SHIFT(12),
        [ts_aux_sym_var] = SHIFT(13),
        [ts_aux_sym_func] = SHIFT(14),
    },
    [8] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_declaration, 1),
    },
    [9] = {
        [ts_sym_declaration] = SHIFT(7),
        [ts_sym_type_declaration] = SHIFT(8),
        [ts_sym_var_declaration] = SHIFT(8),
        [ts_sym_func_declaration] = SHIFT(8),
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = SHIFT(428),
        [ts_aux_sym_type] = SHIFT(12),
        [ts_aux_sym_var] = SHIFT(13),
        [ts_aux_sym_func] = SHIFT(14),
    },
    [10] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [11] = {
        [ts_sym_package_import] = SHIFT(419),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(420),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(421),
    },
    [12] = {
        [ts_sym_type_name] = SHIFT(393),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(394),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [13] = {
        [ts_sym_var_name] = SHIFT(384),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(339),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [14] = {
        [ts_sym_var_name] = SHIFT(15),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [15] = {
        [ts_sym__func_signature] = SHIFT(17),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(18),
    },
    [16] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
    },
    [17] = {
        [ts_sym_block_statement] = SHIFT(197),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(198),
    },
    [18] = {
        [ts_sym_var_name] = SHIFT(19),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(20),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(21),
    },
    [19] = {
        [ts_sym_type_expression] = SHIFT(43),
        [ts_sym_pointer_type] = SHIFT(44),
        [ts_sym_map_type] = SHIFT(44),
        [ts_sym_slice_type] = SHIFT(44),
        [ts_sym_struct_type] = SHIFT(44),
        [ts_sym_interface_type] = SHIFT(44),
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(45),
        [ts_aux_sym_7] = SHIFT(46),
        [ts_aux_sym_map] = SHIFT(47),
        [ts_aux_sym_8] = SHIFT(48),
        [ts_aux_sym_struct] = SHIFT(49),
        [ts_aux_sym_interface] = SHIFT(50),
        [ts_aux_sym_10] = SHIFT(51),
    },
    [20] = {
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
    [21] = {
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(24),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 2),
    },
    [22] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 3),
    },
    [23] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym_type_name, 1),
    },
    [24] = {
        [ts_sym_var_name] = SHIFT(25),
        [ts_sym_type_name] = SHIFT(26),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [25] = {
        [ts_sym_type_name] = SHIFT(35),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [26] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(28),
        [ts_aux_sym_2] = SHIFT(29),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [27] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [28] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(34),
    },
    [29] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 5),
    },
    [30] = {
        [ts_sym_type_name] = SHIFT(31),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [31] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(33),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 2),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [32] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [33] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [34] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [35] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(36),
        [ts_aux_sym_2] = SHIFT(34),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [36] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(42),
    },
    [37] = {
        [ts_sym_var_name] = SHIFT(38),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [38] = {
        [ts_sym_type_name] = SHIFT(40),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [39] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [40] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(41),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 3),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [41] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [42] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 7),
    },
    [43] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(190),
        [ts_aux_sym_2] = SHIFT(191),
        [ts_aux_sym_10] = SHIFT(79),
    },
    [44] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_expression, 1),
    },
    [45] = {
        [ts_sym_type_expression] = SHIFT(171),
        [ts_sym_pointer_type] = SHIFT(44),
        [ts_sym_map_type] = SHIFT(44),
        [ts_sym_slice_type] = SHIFT(44),
        [ts_sym_struct_type] = SHIFT(44),
        [ts_sym_interface_type] = SHIFT(44),
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(46),
        [ts_aux_sym_map] = SHIFT(47),
        [ts_aux_sym_8] = SHIFT(48),
        [ts_aux_sym_struct] = SHIFT(49),
        [ts_aux_sym_interface] = SHIFT(50),
    },
    [46] = {
        [ts_sym_type_expression] = SHIFT(170),
        [ts_sym_pointer_type] = SHIFT(44),
        [ts_sym_map_type] = SHIFT(44),
        [ts_sym_slice_type] = SHIFT(44),
        [ts_sym_struct_type] = SHIFT(44),
        [ts_sym_interface_type] = SHIFT(44),
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(46),
        [ts_aux_sym_map] = SHIFT(47),
        [ts_aux_sym_8] = SHIFT(48),
        [ts_aux_sym_struct] = SHIFT(49),
        [ts_aux_sym_interface] = SHIFT(50),
    },
    [47] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(166),
    },
    [48] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(164),
    },
    [49] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(113),
    },
    [50] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(54),
    },
    [51] = {
        [ts_sym_var_name] = SHIFT(52),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(20),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [52] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(53),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_10] = SHIFT(51),
    },
    [53] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
    },
    [54] = {
        [ts_sym_var_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(56),
        [ts_aux_sym_6] = SHIFT(57),
    },
    [55] = {
        [ts_sym__func_signature] = SHIFT(59),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(60),
    },
    [56] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(58),
    },
    [57] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_interface_type, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_interface_type, 3),
    },
    [58] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_interface_type, 4),
    },
    [59] = {
        [ts_sym_var_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(112),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 2),
    },
    [60] = {
        [ts_sym_var_name] = SHIFT(61),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(20),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(62),
    },
    [61] = {
        [ts_sym_type_expression] = SHIFT(74),
        [ts_sym_pointer_type] = SHIFT(44),
        [ts_sym_map_type] = SHIFT(44),
        [ts_sym_slice_type] = SHIFT(44),
        [ts_sym_struct_type] = SHIFT(44),
        [ts_sym_interface_type] = SHIFT(44),
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(75),
        [ts_aux_sym_7] = SHIFT(46),
        [ts_aux_sym_map] = SHIFT(47),
        [ts_aux_sym_8] = SHIFT(48),
        [ts_aux_sym_struct] = SHIFT(49),
        [ts_aux_sym_interface] = SHIFT(50),
        [ts_aux_sym_10] = SHIFT(51),
    },
    [62] = {
        [ts_sym_type_name] = SHIFT(63),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(64),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(65),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 2),
    },
    [63] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 3),
    },
    [64] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_name, 1),
    },
    [65] = {
        [ts_sym_var_name] = SHIFT(66),
        [ts_sym_type_name] = SHIFT(67),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [66] = {
        [ts_sym_type_name] = SHIFT(71),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [67] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(68),
        [ts_aux_sym_2] = SHIFT(69),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [68] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(70),
    },
    [69] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 5),
    },
    [70] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [71] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(72),
        [ts_aux_sym_2] = SHIFT(70),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [72] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(73),
    },
    [73] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 7),
    },
    [74] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(105),
        [ts_aux_sym_2] = SHIFT(106),
        [ts_aux_sym_10] = SHIFT(79),
    },
    [75] = {
        [ts_sym_type_expression] = SHIFT(76),
        [ts_sym_pointer_type] = SHIFT(44),
        [ts_sym_map_type] = SHIFT(44),
        [ts_sym_slice_type] = SHIFT(44),
        [ts_sym_struct_type] = SHIFT(44),
        [ts_sym_interface_type] = SHIFT(44),
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(46),
        [ts_aux_sym_map] = SHIFT(47),
        [ts_aux_sym_8] = SHIFT(48),
        [ts_aux_sym_struct] = SHIFT(49),
        [ts_aux_sym_interface] = SHIFT(50),
    },
    [76] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(77),
        [ts_aux_sym_2] = SHIFT(78),
        [ts_aux_sym_10] = SHIFT(79),
    },
    [77] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(98),
    },
    [78] = {
        [ts_sym_type_name] = SHIFT(70),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(64),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(89),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 5),
    },
    [79] = {
        [ts_sym_var_name] = SHIFT(80),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(20),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [80] = {
        [ts_sym_type_expression] = SHIFT(81),
        [ts_sym_pointer_type] = SHIFT(44),
        [ts_sym_map_type] = SHIFT(44),
        [ts_sym_slice_type] = SHIFT(44),
        [ts_sym_struct_type] = SHIFT(44),
        [ts_sym_interface_type] = SHIFT(44),
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(82),
        [ts_aux_sym_7] = SHIFT(46),
        [ts_aux_sym_map] = SHIFT(47),
        [ts_aux_sym_8] = SHIFT(48),
        [ts_aux_sym_struct] = SHIFT(49),
        [ts_aux_sym_interface] = SHIFT(50),
        [ts_aux_sym_10] = SHIFT(83),
    },
    [81] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(88),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 3),
        [ts_aux_sym_10] = SHIFT(79),
    },
    [82] = {
        [ts_sym_type_expression] = SHIFT(86),
        [ts_sym_pointer_type] = SHIFT(44),
        [ts_sym_map_type] = SHIFT(44),
        [ts_sym_slice_type] = SHIFT(44),
        [ts_sym_struct_type] = SHIFT(44),
        [ts_sym_interface_type] = SHIFT(44),
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(46),
        [ts_aux_sym_map] = SHIFT(47),
        [ts_aux_sym_8] = SHIFT(48),
        [ts_aux_sym_struct] = SHIFT(49),
        [ts_aux_sym_interface] = SHIFT(50),
    },
    [83] = {
        [ts_sym_var_name] = SHIFT(84),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(20),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [84] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(85),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_10] = SHIFT(83),
    },
    [85] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [86] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(87),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 4),
        [ts_aux_sym_10] = SHIFT(79),
    },
    [87] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [88] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 4),
    },
    [89] = {
        [ts_sym_var_name] = SHIFT(90),
        [ts_sym_type_name] = SHIFT(91),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [90] = {
        [ts_sym_type_name] = SHIFT(95),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [91] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(92),
        [ts_aux_sym_2] = SHIFT(93),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [92] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(94),
    },
    [93] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 8),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 8),
    },
    [94] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 9),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 9),
    },
    [95] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(96),
        [ts_aux_sym_2] = SHIFT(94),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [96] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(97),
    },
    [97] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 10),
    },
    [98] = {
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(64),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(99),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [99] = {
        [ts_sym_var_name] = SHIFT(100),
        [ts_sym_type_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [100] = {
        [ts_sym_type_name] = SHIFT(102),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [101] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(96),
        [ts_aux_sym_2] = SHIFT(94),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [102] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(103),
        [ts_aux_sym_2] = SHIFT(97),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [103] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(104),
    },
    [104] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 11),
    },
    [105] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(78),
    },
    [106] = {
        [ts_sym_type_name] = SHIFT(69),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(64),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(107),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 4),
    },
    [107] = {
        [ts_sym_var_name] = SHIFT(108),
        [ts_sym_type_name] = SHIFT(109),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [108] = {
        [ts_sym_type_name] = SHIFT(111),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [109] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(110),
        [ts_aux_sym_2] = SHIFT(73),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [110] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(93),
    },
    [111] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(92),
        [ts_aux_sym_2] = SHIFT(93),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [112] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [113] = {
        [ts_sym_var_name] = SHIFT(114),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(115),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(116),
        [ts_aux_sym_6] = SHIFT(117),
    },
    [114] = {
        [ts_sym_type_expression] = SHIFT(119),
        [ts_sym_pointer_type] = SHIFT(120),
        [ts_sym_map_type] = SHIFT(120),
        [ts_sym_slice_type] = SHIFT(120),
        [ts_sym_struct_type] = SHIFT(120),
        [ts_sym_interface_type] = SHIFT(120),
        [ts_sym_type_name] = SHIFT(120),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(64),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(121),
        [ts_aux_sym_map] = SHIFT(122),
        [ts_aux_sym_8] = SHIFT(123),
        [ts_aux_sym_struct] = SHIFT(124),
        [ts_aux_sym_interface] = SHIFT(125),
    },
    [115] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
    },
    [116] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(118),
    },
    [117] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_struct_type, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_struct_type, 3),
    },
    [118] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_struct_type, 4),
    },
    [119] = {
        [ts_sym_var_name] = SHIFT(114),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(115),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(163),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 2),
    },
    [120] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_expression, 1),
    },
    [121] = {
        [ts_sym_type_expression] = SHIFT(162),
        [ts_sym_pointer_type] = SHIFT(120),
        [ts_sym_map_type] = SHIFT(120),
        [ts_sym_slice_type] = SHIFT(120),
        [ts_sym_struct_type] = SHIFT(120),
        [ts_sym_interface_type] = SHIFT(120),
        [ts_sym_type_name] = SHIFT(120),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(64),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(121),
        [ts_aux_sym_map] = SHIFT(122),
        [ts_aux_sym_8] = SHIFT(123),
        [ts_aux_sym_struct] = SHIFT(124),
        [ts_aux_sym_interface] = SHIFT(125),
    },
    [122] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(136),
    },
    [123] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(134),
    },
    [124] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(130),
    },
    [125] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(126),
    },
    [126] = {
        [ts_sym_var_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(127),
        [ts_aux_sym_6] = SHIFT(128),
    },
    [127] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(129),
    },
    [128] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_interface_type, 3),
    },
    [129] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_interface_type, 4),
    },
    [130] = {
        [ts_sym_var_name] = SHIFT(114),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(115),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(131),
        [ts_aux_sym_6] = SHIFT(132),
    },
    [131] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(133),
    },
    [132] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_struct_type, 3),
    },
    [133] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_struct_type, 4),
    },
    [134] = {
        [ts_sym_type_expression] = SHIFT(135),
        [ts_sym_pointer_type] = SHIFT(120),
        [ts_sym_map_type] = SHIFT(120),
        [ts_sym_slice_type] = SHIFT(120),
        [ts_sym_struct_type] = SHIFT(120),
        [ts_sym_interface_type] = SHIFT(120),
        [ts_sym_type_name] = SHIFT(120),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(64),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(121),
        [ts_aux_sym_map] = SHIFT(122),
        [ts_aux_sym_8] = SHIFT(123),
        [ts_aux_sym_struct] = SHIFT(124),
        [ts_aux_sym_interface] = SHIFT(125),
    },
    [135] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_slice_type, 3),
    },
    [136] = {
        [ts_sym_type_expression] = SHIFT(137),
        [ts_sym_pointer_type] = SHIFT(138),
        [ts_sym_map_type] = SHIFT(138),
        [ts_sym_slice_type] = SHIFT(138),
        [ts_sym_struct_type] = SHIFT(138),
        [ts_sym_interface_type] = SHIFT(138),
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(139),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(140),
        [ts_aux_sym_map] = SHIFT(141),
        [ts_aux_sym_8] = SHIFT(142),
        [ts_aux_sym_struct] = SHIFT(143),
        [ts_aux_sym_interface] = SHIFT(144),
    },
    [137] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(160),
    },
    [138] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_expression, 1),
    },
    [139] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_name, 1),
    },
    [140] = {
        [ts_sym_type_expression] = SHIFT(159),
        [ts_sym_pointer_type] = SHIFT(138),
        [ts_sym_map_type] = SHIFT(138),
        [ts_sym_slice_type] = SHIFT(138),
        [ts_sym_struct_type] = SHIFT(138),
        [ts_sym_interface_type] = SHIFT(138),
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(139),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(140),
        [ts_aux_sym_map] = SHIFT(141),
        [ts_aux_sym_8] = SHIFT(142),
        [ts_aux_sym_struct] = SHIFT(143),
        [ts_aux_sym_interface] = SHIFT(144),
    },
    [141] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(155),
    },
    [142] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(153),
    },
    [143] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(149),
    },
    [144] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(145),
    },
    [145] = {
        [ts_sym_var_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(146),
        [ts_aux_sym_6] = SHIFT(147),
    },
    [146] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(148),
    },
    [147] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_interface_type, 3),
    },
    [148] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_interface_type, 4),
    },
    [149] = {
        [ts_sym_var_name] = SHIFT(114),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(115),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(150),
        [ts_aux_sym_6] = SHIFT(151),
    },
    [150] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(152),
    },
    [151] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_struct_type, 3),
    },
    [152] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_struct_type, 4),
    },
    [153] = {
        [ts_sym_type_expression] = SHIFT(154),
        [ts_sym_pointer_type] = SHIFT(138),
        [ts_sym_map_type] = SHIFT(138),
        [ts_sym_slice_type] = SHIFT(138),
        [ts_sym_struct_type] = SHIFT(138),
        [ts_sym_interface_type] = SHIFT(138),
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(139),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(140),
        [ts_aux_sym_map] = SHIFT(141),
        [ts_aux_sym_8] = SHIFT(142),
        [ts_aux_sym_struct] = SHIFT(143),
        [ts_aux_sym_interface] = SHIFT(144),
    },
    [154] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_slice_type, 3),
    },
    [155] = {
        [ts_sym_type_expression] = SHIFT(156),
        [ts_sym_pointer_type] = SHIFT(138),
        [ts_sym_map_type] = SHIFT(138),
        [ts_sym_slice_type] = SHIFT(138),
        [ts_sym_struct_type] = SHIFT(138),
        [ts_sym_interface_type] = SHIFT(138),
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(139),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(140),
        [ts_aux_sym_map] = SHIFT(141),
        [ts_aux_sym_8] = SHIFT(142),
        [ts_aux_sym_struct] = SHIFT(143),
        [ts_aux_sym_interface] = SHIFT(144),
    },
    [156] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(157),
    },
    [157] = {
        [ts_sym_type_expression] = SHIFT(158),
        [ts_sym_pointer_type] = SHIFT(138),
        [ts_sym_map_type] = SHIFT(138),
        [ts_sym_slice_type] = SHIFT(138),
        [ts_sym_struct_type] = SHIFT(138),
        [ts_sym_interface_type] = SHIFT(138),
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(139),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(140),
        [ts_aux_sym_map] = SHIFT(141),
        [ts_aux_sym_8] = SHIFT(142),
        [ts_aux_sym_struct] = SHIFT(143),
        [ts_aux_sym_interface] = SHIFT(144),
    },
    [158] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_map_type, 5),
    },
    [159] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_pointer_type, 2),
    },
    [160] = {
        [ts_sym_type_expression] = SHIFT(161),
        [ts_sym_pointer_type] = SHIFT(120),
        [ts_sym_map_type] = SHIFT(120),
        [ts_sym_slice_type] = SHIFT(120),
        [ts_sym_struct_type] = SHIFT(120),
        [ts_sym_interface_type] = SHIFT(120),
        [ts_sym_type_name] = SHIFT(120),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(64),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(121),
        [ts_aux_sym_map] = SHIFT(122),
        [ts_aux_sym_8] = SHIFT(123),
        [ts_aux_sym_struct] = SHIFT(124),
        [ts_aux_sym_interface] = SHIFT(125),
    },
    [161] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_map_type, 5),
    },
    [162] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_pointer_type, 2),
    },
    [163] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 3),
    },
    [164] = {
        [ts_sym_type_expression] = SHIFT(165),
        [ts_sym_pointer_type] = SHIFT(44),
        [ts_sym_map_type] = SHIFT(44),
        [ts_sym_slice_type] = SHIFT(44),
        [ts_sym_struct_type] = SHIFT(44),
        [ts_sym_interface_type] = SHIFT(44),
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(46),
        [ts_aux_sym_map] = SHIFT(47),
        [ts_aux_sym_8] = SHIFT(48),
        [ts_aux_sym_struct] = SHIFT(49),
        [ts_aux_sym_interface] = SHIFT(50),
    },
    [165] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_slice_type, 3),
    },
    [166] = {
        [ts_sym_type_expression] = SHIFT(167),
        [ts_sym_pointer_type] = SHIFT(138),
        [ts_sym_map_type] = SHIFT(138),
        [ts_sym_slice_type] = SHIFT(138),
        [ts_sym_struct_type] = SHIFT(138),
        [ts_sym_interface_type] = SHIFT(138),
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(139),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(140),
        [ts_aux_sym_map] = SHIFT(141),
        [ts_aux_sym_8] = SHIFT(142),
        [ts_aux_sym_struct] = SHIFT(143),
        [ts_aux_sym_interface] = SHIFT(144),
    },
    [167] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(168),
    },
    [168] = {
        [ts_sym_type_expression] = SHIFT(169),
        [ts_sym_pointer_type] = SHIFT(44),
        [ts_sym_map_type] = SHIFT(44),
        [ts_sym_slice_type] = SHIFT(44),
        [ts_sym_struct_type] = SHIFT(44),
        [ts_sym_interface_type] = SHIFT(44),
        [ts_sym_type_name] = SHIFT(44),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(46),
        [ts_aux_sym_map] = SHIFT(47),
        [ts_aux_sym_8] = SHIFT(48),
        [ts_aux_sym_struct] = SHIFT(49),
        [ts_aux_sym_interface] = SHIFT(50),
    },
    [169] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_map_type, 5),
    },
    [170] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_pointer_type, 2),
    },
    [171] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(172),
        [ts_aux_sym_2] = SHIFT(173),
        [ts_aux_sym_10] = SHIFT(79),
    },
    [172] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(183),
    },
    [173] = {
        [ts_sym_type_name] = SHIFT(34),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(174),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 5),
    },
    [174] = {
        [ts_sym_var_name] = SHIFT(175),
        [ts_sym_type_name] = SHIFT(176),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [175] = {
        [ts_sym_type_name] = SHIFT(180),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [176] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(177),
        [ts_aux_sym_2] = SHIFT(178),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [177] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(179),
    },
    [178] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 8),
    },
    [179] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 9),
    },
    [180] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(181),
        [ts_aux_sym_2] = SHIFT(179),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [181] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(182),
    },
    [182] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 10),
    },
    [183] = {
        [ts_sym_type_name] = SHIFT(42),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(184),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [184] = {
        [ts_sym_var_name] = SHIFT(185),
        [ts_sym_type_name] = SHIFT(186),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [185] = {
        [ts_sym_type_name] = SHIFT(187),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [186] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(181),
        [ts_aux_sym_2] = SHIFT(179),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [187] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(188),
        [ts_aux_sym_2] = SHIFT(182),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [188] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(189),
    },
    [189] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 11),
    },
    [190] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(173),
    },
    [191] = {
        [ts_sym_type_name] = SHIFT(29),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(192),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 4),
    },
    [192] = {
        [ts_sym_var_name] = SHIFT(193),
        [ts_sym_type_name] = SHIFT(194),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [193] = {
        [ts_sym_type_name] = SHIFT(196),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(32),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [194] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(195),
        [ts_aux_sym_2] = SHIFT(42),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [195] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(178),
    },
    [196] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(177),
        [ts_aux_sym_2] = SHIFT(178),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [197] = {
        [ts_sym__line_break] = SHIFT(383),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(383),
    },
    [198] = {
        [ts_sym_var_declaration] = SHIFT(199),
        [ts_sym_statement] = SHIFT(200),
        [ts_sym_return_statement] = SHIFT(201),
        [ts_sym_declaration_statement] = SHIFT(201),
        [ts_sym_range_statement] = SHIFT(201),
        [ts_sym_if_statement] = SHIFT(201),
        [ts_sym_expression_statement] = SHIFT(201),
        [ts_sym_expression] = SHIFT(202),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(204),
        [ts_builtin_sym_error] = SHIFT(205),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(205),
        [ts_aux_sym_var] = SHIFT(207),
        [ts_aux_sym_6] = SHIFT(208),
        [ts_aux_sym_return] = SHIFT(209),
        [ts_aux_sym_11] = SHIFT(210),
        [ts_aux_sym_for] = SHIFT(211),
        [ts_aux_sym_if] = SHIFT(212),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [199] = {
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
    [200] = {
        [ts_sym_var_declaration] = SHIFT(199),
        [ts_sym_statement] = SHIFT(200),
        [ts_sym_return_statement] = SHIFT(201),
        [ts_sym_declaration_statement] = SHIFT(201),
        [ts_sym_range_statement] = SHIFT(201),
        [ts_sym_if_statement] = SHIFT(201),
        [ts_sym_expression_statement] = SHIFT(201),
        [ts_sym_expression] = SHIFT(202),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(204),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(382),
        [ts_aux_sym_var] = SHIFT(207),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 1),
        [ts_aux_sym_return] = SHIFT(209),
        [ts_aux_sym_11] = SHIFT(210),
        [ts_aux_sym_for] = SHIFT(211),
        [ts_aux_sym_if] = SHIFT(212),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [201] = {
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
    [202] = {
        [ts_sym__line_break] = SHIFT(381),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(290),
        [ts_aux_sym_3] = SHIFT(381),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [203] = {
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
    [204] = {
        [ts_sym__line_break] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(371),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_10] = SHIFT(372),
        [ts_aux_sym_11] = SHIFT(373),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(370),
    },
    [206] = {
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
    [207] = {
        [ts_sym_var_name] = SHIFT(338),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(339),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [208] = {
        [ts_sym__line_break] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_block_statement, 2),
    },
    [209] = {
        [ts_sym_expression] = SHIFT(308),
        [ts_sym_call_expression] = SHIFT(309),
        [ts_sym_selector_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(309),
        [ts_sym_bool_op] = SHIFT(309),
        [ts_sym_var_name] = SHIFT(309),
        [ts_sym__line_break] = SHIFT(310),
        [ts_sym_string] = SHIFT(309),
        [ts_sym__identifier] = SHIFT(311),
        [ts_sym_number] = SHIFT(309),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(310),
        [ts_aux_sym_23] = SHIFT(312),
    },
    [210] = {
        [ts_sym_expression] = SHIFT(288),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [211] = {
        [ts_sym_var_name] = SHIFT(275),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(276),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [212] = {
        [ts_sym_expression] = SHIFT(216),
        [ts_sym_call_expression] = SHIFT(217),
        [ts_sym_selector_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(217),
        [ts_sym_bool_op] = SHIFT(217),
        [ts_sym_var_name] = SHIFT(217),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(217),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_number] = SHIFT(217),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(219),
    },
    [213] = {
        [ts_sym_expression] = SHIFT(214),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [214] = {
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
    [215] = {
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
    [216] = {
        [ts_sym_block_statement] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(222),
        [ts_aux_sym_5] = SHIFT(223),
        [ts_aux_sym_7] = SHIFT(224),
        [ts_aux_sym_12] = SHIFT(225),
        [ts_aux_sym_13] = SHIFT(224),
        [ts_aux_sym_14] = SHIFT(226),
        [ts_aux_sym_15] = SHIFT(226),
        [ts_aux_sym_16] = SHIFT(227),
        [ts_aux_sym_17] = SHIFT(228),
        [ts_aux_sym_18] = SHIFT(229),
        [ts_aux_sym_19] = SHIFT(229),
        [ts_aux_sym_20] = SHIFT(229),
        [ts_aux_sym_21] = SHIFT(229),
        [ts_aux_sym_22] = SHIFT(229),
    },
    [217] = {
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
    [218] = {
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
    [219] = {
        [ts_sym_expression] = SHIFT(220),
        [ts_sym_call_expression] = SHIFT(217),
        [ts_sym_selector_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(217),
        [ts_sym_bool_op] = SHIFT(217),
        [ts_sym_var_name] = SHIFT(217),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(217),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_number] = SHIFT(217),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(219),
    },
    [220] = {
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
    [221] = {
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
        [ts_aux_sym_else] = SHIFT(269),
        [ts_aux_sym_23] = REDUCE(ts_sym_if_statement, 3),
    },
    [222] = {
        [ts_sym_expression] = SHIFT(239),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(242),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [223] = {
        [ts_sym_var_declaration] = SHIFT(199),
        [ts_sym_statement] = SHIFT(200),
        [ts_sym_return_statement] = SHIFT(201),
        [ts_sym_declaration_statement] = SHIFT(201),
        [ts_sym_range_statement] = SHIFT(201),
        [ts_sym_if_statement] = SHIFT(201),
        [ts_sym_expression_statement] = SHIFT(201),
        [ts_sym_expression] = SHIFT(202),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(204),
        [ts_builtin_sym_error] = SHIFT(236),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(236),
        [ts_aux_sym_var] = SHIFT(207),
        [ts_aux_sym_6] = SHIFT(237),
        [ts_aux_sym_return] = SHIFT(209),
        [ts_aux_sym_11] = SHIFT(210),
        [ts_aux_sym_for] = SHIFT(211),
        [ts_aux_sym_if] = SHIFT(212),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [224] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_call_expression] = SHIFT(217),
        [ts_sym_selector_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(217),
        [ts_sym_bool_op] = SHIFT(217),
        [ts_sym_var_name] = SHIFT(217),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(217),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_number] = SHIFT(217),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(219),
    },
    [225] = {
        [ts_sym_var_name] = SHIFT(234),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [226] = {
        [ts_sym_expression] = SHIFT(233),
        [ts_sym_call_expression] = SHIFT(217),
        [ts_sym_selector_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(217),
        [ts_sym_bool_op] = SHIFT(217),
        [ts_sym_var_name] = SHIFT(217),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(217),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_number] = SHIFT(217),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(219),
    },
    [227] = {
        [ts_sym_expression] = SHIFT(232),
        [ts_sym_call_expression] = SHIFT(217),
        [ts_sym_selector_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(217),
        [ts_sym_bool_op] = SHIFT(217),
        [ts_sym_var_name] = SHIFT(217),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(217),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_number] = SHIFT(217),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(219),
    },
    [228] = {
        [ts_sym_expression] = SHIFT(231),
        [ts_sym_call_expression] = SHIFT(217),
        [ts_sym_selector_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(217),
        [ts_sym_bool_op] = SHIFT(217),
        [ts_sym_var_name] = SHIFT(217),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(217),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_number] = SHIFT(217),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(219),
    },
    [229] = {
        [ts_sym_expression] = SHIFT(230),
        [ts_sym_call_expression] = SHIFT(217),
        [ts_sym_selector_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(217),
        [ts_sym_bool_op] = SHIFT(217),
        [ts_sym_var_name] = SHIFT(217),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(217),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_number] = SHIFT(217),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(219),
    },
    [230] = {
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
        [ts_aux_sym_18] = SHIFT(229),
        [ts_aux_sym_19] = SHIFT(229),
        [ts_aux_sym_20] = SHIFT(229),
        [ts_aux_sym_21] = SHIFT(229),
        [ts_aux_sym_22] = SHIFT(229),
    },
    [231] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(224),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(224),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(228),
        [ts_aux_sym_18] = SHIFT(229),
        [ts_aux_sym_19] = SHIFT(229),
        [ts_aux_sym_20] = SHIFT(229),
        [ts_aux_sym_21] = SHIFT(229),
        [ts_aux_sym_22] = SHIFT(229),
    },
    [232] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(224),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(224),
        [ts_aux_sym_14] = SHIFT(226),
        [ts_aux_sym_15] = SHIFT(226),
        [ts_aux_sym_16] = SHIFT(227),
        [ts_aux_sym_17] = SHIFT(228),
        [ts_aux_sym_18] = SHIFT(229),
        [ts_aux_sym_19] = SHIFT(229),
        [ts_aux_sym_20] = SHIFT(229),
        [ts_aux_sym_21] = SHIFT(229),
        [ts_aux_sym_22] = SHIFT(229),
    },
    [233] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(224),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(224),
        [ts_aux_sym_14] = SHIFT(226),
        [ts_aux_sym_15] = SHIFT(226),
        [ts_aux_sym_16] = SHIFT(227),
        [ts_aux_sym_17] = SHIFT(228),
        [ts_aux_sym_18] = SHIFT(229),
        [ts_aux_sym_19] = SHIFT(229),
        [ts_aux_sym_20] = SHIFT(229),
        [ts_aux_sym_21] = SHIFT(229),
        [ts_aux_sym_22] = SHIFT(229),
    },
    [234] = {
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
    [235] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(224),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(224),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(228),
        [ts_aux_sym_18] = SHIFT(229),
        [ts_aux_sym_19] = SHIFT(229),
        [ts_aux_sym_20] = SHIFT(229),
        [ts_aux_sym_21] = SHIFT(229),
        [ts_aux_sym_22] = SHIFT(229),
    },
    [236] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(238),
    },
    [237] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_for] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_else] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_23] = REDUCE(ts_sym_block_statement, 2),
    },
    [238] = {
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
    [239] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(245),
        [ts_aux_sym_1] = SHIFT(246),
        [ts_aux_sym_2] = SHIFT(247),
        [ts_aux_sym_7] = SHIFT(248),
        [ts_aux_sym_10] = SHIFT(249),
        [ts_aux_sym_12] = SHIFT(250),
        [ts_aux_sym_13] = SHIFT(248),
        [ts_aux_sym_14] = SHIFT(251),
        [ts_aux_sym_15] = SHIFT(251),
        [ts_aux_sym_16] = SHIFT(252),
        [ts_aux_sym_17] = SHIFT(253),
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [240] = {
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
    [241] = {
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
    [242] = {
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
    [243] = {
        [ts_sym_expression] = SHIFT(244),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [244] = {
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
    [245] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(268),
    },
    [246] = {
        [ts_sym_expression] = SHIFT(263),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(264),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [247] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_5] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_22] = REDUCE(ts_sym_call_expression, 4),
    },
    [248] = {
        [ts_sym_expression] = SHIFT(262),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [249] = {
        [ts_sym_expression] = SHIFT(260),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [250] = {
        [ts_sym_var_name] = SHIFT(259),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [251] = {
        [ts_sym_expression] = SHIFT(258),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [252] = {
        [ts_sym_expression] = SHIFT(257),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [253] = {
        [ts_sym_expression] = SHIFT(256),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [254] = {
        [ts_sym_expression] = SHIFT(255),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [255] = {
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
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [256] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(248),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(248),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(253),
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [257] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(248),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(248),
        [ts_aux_sym_14] = SHIFT(251),
        [ts_aux_sym_15] = SHIFT(251),
        [ts_aux_sym_16] = SHIFT(252),
        [ts_aux_sym_17] = SHIFT(253),
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [258] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(248),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(248),
        [ts_aux_sym_14] = SHIFT(251),
        [ts_aux_sym_15] = SHIFT(251),
        [ts_aux_sym_16] = SHIFT(252),
        [ts_aux_sym_17] = SHIFT(253),
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [259] = {
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
    [260] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(261),
        [ts_aux_sym_1] = SHIFT(246),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 2),
        [ts_aux_sym_7] = SHIFT(248),
        [ts_aux_sym_10] = SHIFT(249),
        [ts_aux_sym_12] = SHIFT(250),
        [ts_aux_sym_13] = SHIFT(248),
        [ts_aux_sym_14] = SHIFT(251),
        [ts_aux_sym_15] = SHIFT(251),
        [ts_aux_sym_16] = SHIFT(252),
        [ts_aux_sym_17] = SHIFT(253),
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [261] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 3),
    },
    [262] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(248),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(248),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(253),
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [263] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(265),
        [ts_aux_sym_1] = SHIFT(246),
        [ts_aux_sym_2] = SHIFT(266),
        [ts_aux_sym_7] = SHIFT(248),
        [ts_aux_sym_10] = SHIFT(249),
        [ts_aux_sym_12] = SHIFT(250),
        [ts_aux_sym_13] = SHIFT(248),
        [ts_aux_sym_14] = SHIFT(251),
        [ts_aux_sym_15] = SHIFT(251),
        [ts_aux_sym_16] = SHIFT(252),
        [ts_aux_sym_17] = SHIFT(253),
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [264] = {
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
    [265] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(267),
    },
    [266] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_2] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_22] = REDUCE(ts_sym_call_expression, 4),
    },
    [267] = {
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
    [268] = {
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
    [269] = {
        [ts_sym_block_statement] = SHIFT(270),
        [ts_sym_if_statement] = SHIFT(270),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(271),
        [ts_aux_sym_if] = SHIFT(212),
    },
    [270] = {
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
    [271] = {
        [ts_sym_var_declaration] = SHIFT(199),
        [ts_sym_statement] = SHIFT(200),
        [ts_sym_return_statement] = SHIFT(201),
        [ts_sym_declaration_statement] = SHIFT(201),
        [ts_sym_range_statement] = SHIFT(201),
        [ts_sym_if_statement] = SHIFT(201),
        [ts_sym_expression_statement] = SHIFT(201),
        [ts_sym_expression] = SHIFT(202),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(204),
        [ts_builtin_sym_error] = SHIFT(272),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(206),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(272),
        [ts_aux_sym_var] = SHIFT(207),
        [ts_aux_sym_6] = SHIFT(273),
        [ts_aux_sym_return] = SHIFT(209),
        [ts_aux_sym_11] = SHIFT(210),
        [ts_aux_sym_for] = SHIFT(211),
        [ts_aux_sym_if] = SHIFT(212),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [272] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(274),
    },
    [273] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_for] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_23] = REDUCE(ts_sym_block_statement, 2),
    },
    [274] = {
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
    [275] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = SHIFT(277),
        [ts_aux_sym_11] = SHIFT(278),
    },
    [276] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [277] = {
        [ts_sym_var_name] = SHIFT(282),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(283),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [278] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_range] = SHIFT(279),
    },
    [279] = {
        [ts_sym_expression] = SHIFT(280),
        [ts_sym_call_expression] = SHIFT(217),
        [ts_sym_selector_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(217),
        [ts_sym_bool_op] = SHIFT(217),
        [ts_sym_var_name] = SHIFT(217),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(217),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_number] = SHIFT(217),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(219),
    },
    [280] = {
        [ts_sym_block_statement] = SHIFT(281),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(222),
        [ts_aux_sym_5] = SHIFT(271),
        [ts_aux_sym_7] = SHIFT(224),
        [ts_aux_sym_12] = SHIFT(225),
        [ts_aux_sym_13] = SHIFT(224),
        [ts_aux_sym_14] = SHIFT(226),
        [ts_aux_sym_15] = SHIFT(226),
        [ts_aux_sym_16] = SHIFT(227),
        [ts_aux_sym_17] = SHIFT(228),
        [ts_aux_sym_18] = SHIFT(229),
        [ts_aux_sym_19] = SHIFT(229),
        [ts_aux_sym_20] = SHIFT(229),
        [ts_aux_sym_21] = SHIFT(229),
        [ts_aux_sym_22] = SHIFT(229),
    },
    [281] = {
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
    [282] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(284),
    },
    [283] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [284] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_range] = SHIFT(285),
    },
    [285] = {
        [ts_sym_expression] = SHIFT(286),
        [ts_sym_call_expression] = SHIFT(217),
        [ts_sym_selector_expression] = SHIFT(217),
        [ts_sym_math_op] = SHIFT(217),
        [ts_sym_bool_op] = SHIFT(217),
        [ts_sym_var_name] = SHIFT(217),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(217),
        [ts_sym__identifier] = SHIFT(218),
        [ts_sym_number] = SHIFT(217),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(219),
    },
    [286] = {
        [ts_sym_block_statement] = SHIFT(287),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(222),
        [ts_aux_sym_5] = SHIFT(271),
        [ts_aux_sym_7] = SHIFT(224),
        [ts_aux_sym_12] = SHIFT(225),
        [ts_aux_sym_13] = SHIFT(224),
        [ts_aux_sym_14] = SHIFT(226),
        [ts_aux_sym_15] = SHIFT(226),
        [ts_aux_sym_16] = SHIFT(227),
        [ts_aux_sym_17] = SHIFT(228),
        [ts_aux_sym_18] = SHIFT(229),
        [ts_aux_sym_19] = SHIFT(229),
        [ts_aux_sym_20] = SHIFT(229),
        [ts_aux_sym_21] = SHIFT(229),
        [ts_aux_sym_22] = SHIFT(229),
    },
    [287] = {
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
    [288] = {
        [ts_sym__line_break] = SHIFT(289),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(290),
        [ts_aux_sym_3] = SHIFT(289),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [289] = {
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
    [290] = {
        [ts_sym_expression] = SHIFT(303),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(304),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [291] = {
        [ts_sym_expression] = SHIFT(302),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [292] = {
        [ts_sym_var_name] = SHIFT(301),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [293] = {
        [ts_sym_expression] = SHIFT(300),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [294] = {
        [ts_sym_expression] = SHIFT(299),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [295] = {
        [ts_sym_expression] = SHIFT(298),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [296] = {
        [ts_sym_expression] = SHIFT(297),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [297] = {
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
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [298] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [299] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [300] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [301] = {
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
    [302] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [303] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(305),
        [ts_aux_sym_1] = SHIFT(246),
        [ts_aux_sym_2] = SHIFT(306),
        [ts_aux_sym_7] = SHIFT(248),
        [ts_aux_sym_10] = SHIFT(249),
        [ts_aux_sym_12] = SHIFT(250),
        [ts_aux_sym_13] = SHIFT(248),
        [ts_aux_sym_14] = SHIFT(251),
        [ts_aux_sym_15] = SHIFT(251),
        [ts_aux_sym_16] = SHIFT(252),
        [ts_aux_sym_17] = SHIFT(253),
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [304] = {
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
    [305] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(307),
    },
    [306] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_3] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_22] = REDUCE(ts_sym_call_expression, 4),
    },
    [307] = {
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
    [308] = {
        [ts_sym__line_break] = SHIFT(314),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(315),
        [ts_aux_sym_1] = SHIFT(316),
        [ts_aux_sym_3] = SHIFT(314),
        [ts_aux_sym_7] = SHIFT(317),
        [ts_aux_sym_10] = SHIFT(318),
        [ts_aux_sym_12] = SHIFT(319),
        [ts_aux_sym_13] = SHIFT(317),
        [ts_aux_sym_14] = SHIFT(320),
        [ts_aux_sym_15] = SHIFT(320),
        [ts_aux_sym_16] = SHIFT(321),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(323),
        [ts_aux_sym_19] = SHIFT(323),
        [ts_aux_sym_20] = SHIFT(323),
        [ts_aux_sym_21] = SHIFT(323),
        [ts_aux_sym_22] = SHIFT(323),
    },
    [309] = {
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
    [310] = {
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
    [311] = {
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
    [312] = {
        [ts_sym_expression] = SHIFT(313),
        [ts_sym_call_expression] = SHIFT(309),
        [ts_sym_selector_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(309),
        [ts_sym_bool_op] = SHIFT(309),
        [ts_sym_var_name] = SHIFT(309),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(309),
        [ts_sym__identifier] = SHIFT(311),
        [ts_sym_number] = SHIFT(309),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(312),
    },
    [313] = {
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
    [314] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_1] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_7] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_return] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_10] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_11] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_for] = REDUCE(ts_sym_return_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_return_statement, 3),
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
        [ts_aux_sym_23] = REDUCE(ts_sym_return_statement, 3),
    },
    [315] = {
        [ts_sym__line_break] = SHIFT(337),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(337),
    },
    [316] = {
        [ts_sym_expression] = SHIFT(332),
        [ts_sym_call_expression] = SHIFT(240),
        [ts_sym_selector_expression] = SHIFT(240),
        [ts_sym_math_op] = SHIFT(240),
        [ts_sym_bool_op] = SHIFT(240),
        [ts_sym_var_name] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(240),
        [ts_sym__identifier] = SHIFT(241),
        [ts_sym_number] = SHIFT(240),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(333),
        [ts_aux_sym_23] = SHIFT(243),
    },
    [317] = {
        [ts_sym_expression] = SHIFT(331),
        [ts_sym_call_expression] = SHIFT(309),
        [ts_sym_selector_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(309),
        [ts_sym_bool_op] = SHIFT(309),
        [ts_sym_var_name] = SHIFT(309),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(309),
        [ts_sym__identifier] = SHIFT(311),
        [ts_sym_number] = SHIFT(309),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(312),
    },
    [318] = {
        [ts_sym_expression] = SHIFT(329),
        [ts_sym_call_expression] = SHIFT(309),
        [ts_sym_selector_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(309),
        [ts_sym_bool_op] = SHIFT(309),
        [ts_sym_var_name] = SHIFT(309),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(309),
        [ts_sym__identifier] = SHIFT(311),
        [ts_sym_number] = SHIFT(309),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(312),
    },
    [319] = {
        [ts_sym_var_name] = SHIFT(328),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(311),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [320] = {
        [ts_sym_expression] = SHIFT(327),
        [ts_sym_call_expression] = SHIFT(309),
        [ts_sym_selector_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(309),
        [ts_sym_bool_op] = SHIFT(309),
        [ts_sym_var_name] = SHIFT(309),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(309),
        [ts_sym__identifier] = SHIFT(311),
        [ts_sym_number] = SHIFT(309),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(312),
    },
    [321] = {
        [ts_sym_expression] = SHIFT(326),
        [ts_sym_call_expression] = SHIFT(309),
        [ts_sym_selector_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(309),
        [ts_sym_bool_op] = SHIFT(309),
        [ts_sym_var_name] = SHIFT(309),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(309),
        [ts_sym__identifier] = SHIFT(311),
        [ts_sym_number] = SHIFT(309),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(312),
    },
    [322] = {
        [ts_sym_expression] = SHIFT(325),
        [ts_sym_call_expression] = SHIFT(309),
        [ts_sym_selector_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(309),
        [ts_sym_bool_op] = SHIFT(309),
        [ts_sym_var_name] = SHIFT(309),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(309),
        [ts_sym__identifier] = SHIFT(311),
        [ts_sym_number] = SHIFT(309),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(312),
    },
    [323] = {
        [ts_sym_expression] = SHIFT(324),
        [ts_sym_call_expression] = SHIFT(309),
        [ts_sym_selector_expression] = SHIFT(309),
        [ts_sym_math_op] = SHIFT(309),
        [ts_sym_bool_op] = SHIFT(309),
        [ts_sym_var_name] = SHIFT(309),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(309),
        [ts_sym__identifier] = SHIFT(311),
        [ts_sym_number] = SHIFT(309),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(312),
    },
    [324] = {
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
        [ts_aux_sym_18] = SHIFT(323),
        [ts_aux_sym_19] = SHIFT(323),
        [ts_aux_sym_20] = SHIFT(323),
        [ts_aux_sym_21] = SHIFT(323),
        [ts_aux_sym_22] = SHIFT(323),
    },
    [325] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(317),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(317),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(323),
        [ts_aux_sym_19] = SHIFT(323),
        [ts_aux_sym_20] = SHIFT(323),
        [ts_aux_sym_21] = SHIFT(323),
        [ts_aux_sym_22] = SHIFT(323),
    },
    [326] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(317),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(317),
        [ts_aux_sym_14] = SHIFT(320),
        [ts_aux_sym_15] = SHIFT(320),
        [ts_aux_sym_16] = SHIFT(321),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(323),
        [ts_aux_sym_19] = SHIFT(323),
        [ts_aux_sym_20] = SHIFT(323),
        [ts_aux_sym_21] = SHIFT(323),
        [ts_aux_sym_22] = SHIFT(323),
    },
    [327] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(317),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(317),
        [ts_aux_sym_14] = SHIFT(320),
        [ts_aux_sym_15] = SHIFT(320),
        [ts_aux_sym_16] = SHIFT(321),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(323),
        [ts_aux_sym_19] = SHIFT(323),
        [ts_aux_sym_20] = SHIFT(323),
        [ts_aux_sym_21] = SHIFT(323),
        [ts_aux_sym_22] = SHIFT(323),
    },
    [328] = {
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
    [329] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(330),
        [ts_aux_sym_1] = SHIFT(316),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 2),
        [ts_aux_sym_7] = SHIFT(317),
        [ts_aux_sym_10] = SHIFT(318),
        [ts_aux_sym_12] = SHIFT(319),
        [ts_aux_sym_13] = SHIFT(317),
        [ts_aux_sym_14] = SHIFT(320),
        [ts_aux_sym_15] = SHIFT(320),
        [ts_aux_sym_16] = SHIFT(321),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(323),
        [ts_aux_sym_19] = SHIFT(323),
        [ts_aux_sym_20] = SHIFT(323),
        [ts_aux_sym_21] = SHIFT(323),
        [ts_aux_sym_22] = SHIFT(323),
    },
    [330] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
    },
    [331] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(317),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(317),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(322),
        [ts_aux_sym_18] = SHIFT(323),
        [ts_aux_sym_19] = SHIFT(323),
        [ts_aux_sym_20] = SHIFT(323),
        [ts_aux_sym_21] = SHIFT(323),
        [ts_aux_sym_22] = SHIFT(323),
    },
    [332] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(334),
        [ts_aux_sym_1] = SHIFT(246),
        [ts_aux_sym_2] = SHIFT(335),
        [ts_aux_sym_7] = SHIFT(248),
        [ts_aux_sym_10] = SHIFT(249),
        [ts_aux_sym_12] = SHIFT(250),
        [ts_aux_sym_13] = SHIFT(248),
        [ts_aux_sym_14] = SHIFT(251),
        [ts_aux_sym_15] = SHIFT(251),
        [ts_aux_sym_16] = SHIFT(252),
        [ts_aux_sym_17] = SHIFT(253),
        [ts_aux_sym_18] = SHIFT(254),
        [ts_aux_sym_19] = SHIFT(254),
        [ts_aux_sym_20] = SHIFT(254),
        [ts_aux_sym_21] = SHIFT(254),
        [ts_aux_sym_22] = SHIFT(254),
    },
    [333] = {
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
    [334] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(336),
    },
    [335] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_3] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_7] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_12] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_13] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_14] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_15] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_16] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_17] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_18] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_19] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_20] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_21] = REDUCE(ts_sym_call_expression, 4),
        [ts_aux_sym_22] = REDUCE(ts_sym_call_expression, 4),
    },
    [336] = {
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
    [337] = {
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
    [338] = {
        [ts_sym_type_expression] = SHIFT(340),
        [ts_sym_pointer_type] = SHIFT(341),
        [ts_sym_map_type] = SHIFT(341),
        [ts_sym_slice_type] = SHIFT(341),
        [ts_sym_struct_type] = SHIFT(341),
        [ts_sym_interface_type] = SHIFT(341),
        [ts_sym_type_name] = SHIFT(341),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(342),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(343),
        [ts_aux_sym_7] = SHIFT(344),
        [ts_aux_sym_map] = SHIFT(345),
        [ts_aux_sym_8] = SHIFT(346),
        [ts_aux_sym_struct] = SHIFT(347),
        [ts_aux_sym_interface] = SHIFT(348),
    },
    [339] = {
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
    [340] = {
        [ts_sym__line_break] = SHIFT(366),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(366),
        [ts_aux_sym_4] = SHIFT(367),
    },
    [341] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_expression, 1),
    },
    [342] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_name, 1),
    },
    [343] = {
        [ts_sym_expression] = SHIFT(364),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [344] = {
        [ts_sym_type_expression] = SHIFT(363),
        [ts_sym_pointer_type] = SHIFT(341),
        [ts_sym_map_type] = SHIFT(341),
        [ts_sym_slice_type] = SHIFT(341),
        [ts_sym_struct_type] = SHIFT(341),
        [ts_sym_interface_type] = SHIFT(341),
        [ts_sym_type_name] = SHIFT(341),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(342),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(344),
        [ts_aux_sym_map] = SHIFT(345),
        [ts_aux_sym_8] = SHIFT(346),
        [ts_aux_sym_struct] = SHIFT(347),
        [ts_aux_sym_interface] = SHIFT(348),
    },
    [345] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(359),
    },
    [346] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(357),
    },
    [347] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(353),
    },
    [348] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(349),
    },
    [349] = {
        [ts_sym_var_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(350),
        [ts_aux_sym_6] = SHIFT(351),
    },
    [350] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(352),
    },
    [351] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_interface_type, 3),
    },
    [352] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_interface_type, 4),
    },
    [353] = {
        [ts_sym_var_name] = SHIFT(114),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(115),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(354),
        [ts_aux_sym_6] = SHIFT(355),
    },
    [354] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(356),
    },
    [355] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_struct_type, 3),
    },
    [356] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_struct_type, 4),
    },
    [357] = {
        [ts_sym_type_expression] = SHIFT(358),
        [ts_sym_pointer_type] = SHIFT(341),
        [ts_sym_map_type] = SHIFT(341),
        [ts_sym_slice_type] = SHIFT(341),
        [ts_sym_struct_type] = SHIFT(341),
        [ts_sym_interface_type] = SHIFT(341),
        [ts_sym_type_name] = SHIFT(341),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(342),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(344),
        [ts_aux_sym_map] = SHIFT(345),
        [ts_aux_sym_8] = SHIFT(346),
        [ts_aux_sym_struct] = SHIFT(347),
        [ts_aux_sym_interface] = SHIFT(348),
    },
    [358] = {
        [ts_sym__line_break] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_slice_type, 3),
    },
    [359] = {
        [ts_sym_type_expression] = SHIFT(360),
        [ts_sym_pointer_type] = SHIFT(138),
        [ts_sym_map_type] = SHIFT(138),
        [ts_sym_slice_type] = SHIFT(138),
        [ts_sym_struct_type] = SHIFT(138),
        [ts_sym_interface_type] = SHIFT(138),
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(139),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(140),
        [ts_aux_sym_map] = SHIFT(141),
        [ts_aux_sym_8] = SHIFT(142),
        [ts_aux_sym_struct] = SHIFT(143),
        [ts_aux_sym_interface] = SHIFT(144),
    },
    [360] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(361),
    },
    [361] = {
        [ts_sym_type_expression] = SHIFT(362),
        [ts_sym_pointer_type] = SHIFT(341),
        [ts_sym_map_type] = SHIFT(341),
        [ts_sym_slice_type] = SHIFT(341),
        [ts_sym_struct_type] = SHIFT(341),
        [ts_sym_interface_type] = SHIFT(341),
        [ts_sym_type_name] = SHIFT(341),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(342),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(344),
        [ts_aux_sym_map] = SHIFT(345),
        [ts_aux_sym_8] = SHIFT(346),
        [ts_aux_sym_struct] = SHIFT(347),
        [ts_aux_sym_interface] = SHIFT(348),
    },
    [362] = {
        [ts_sym__line_break] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_4] = REDUCE(ts_sym_map_type, 5),
    },
    [363] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_pointer_type, 2),
    },
    [364] = {
        [ts_sym__line_break] = SHIFT(365),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(290),
        [ts_aux_sym_3] = SHIFT(365),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [365] = {
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
    [366] = {
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
    [367] = {
        [ts_sym_expression] = SHIFT(368),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [368] = {
        [ts_sym__line_break] = SHIFT(369),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(290),
        [ts_aux_sym_3] = SHIFT(369),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [369] = {
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
    [370] = {
        [ts_sym__line_break] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_block_statement, 3),
    },
    [371] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(378),
    },
    [372] = {
        [ts_sym_var_name] = SHIFT(376),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(276),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [373] = {
        [ts_sym_expression] = SHIFT(374),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [374] = {
        [ts_sym__line_break] = SHIFT(375),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(290),
        [ts_aux_sym_3] = SHIFT(375),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [375] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_7] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_return] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_11] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_for] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_aux_sym_if] = REDUCE(ts_sym_declaration_statement, 4),
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
        [ts_aux_sym_23] = REDUCE(ts_sym_declaration_statement, 4),
    },
    [376] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(377),
        [ts_aux_sym_10] = SHIFT(372),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 2),
    },
    [377] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 3),
    },
    [378] = {
        [ts_sym_expression] = SHIFT(379),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [379] = {
        [ts_sym__line_break] = SHIFT(380),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(290),
        [ts_aux_sym_3] = SHIFT(380),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [380] = {
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
    [381] = {
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
    [382] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 2),
    },
    [383] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_func] = REDUCE(ts_sym_func_declaration, 5),
    },
    [384] = {
        [ts_sym_type_expression] = SHIFT(385),
        [ts_sym_pointer_type] = SHIFT(341),
        [ts_sym_map_type] = SHIFT(341),
        [ts_sym_slice_type] = SHIFT(341),
        [ts_sym_struct_type] = SHIFT(341),
        [ts_sym_interface_type] = SHIFT(341),
        [ts_sym_type_name] = SHIFT(341),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(342),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(386),
        [ts_aux_sym_7] = SHIFT(344),
        [ts_aux_sym_map] = SHIFT(345),
        [ts_aux_sym_8] = SHIFT(346),
        [ts_aux_sym_struct] = SHIFT(347),
        [ts_aux_sym_interface] = SHIFT(348),
    },
    [385] = {
        [ts_sym__line_break] = SHIFT(389),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(389),
        [ts_aux_sym_4] = SHIFT(390),
    },
    [386] = {
        [ts_sym_expression] = SHIFT(387),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [387] = {
        [ts_sym__line_break] = SHIFT(388),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(290),
        [ts_aux_sym_3] = SHIFT(388),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [388] = {
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
    [389] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_4] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_func] = REDUCE(ts_sym_var_declaration, 4),
    },
    [390] = {
        [ts_sym_expression] = SHIFT(391),
        [ts_sym_call_expression] = SHIFT(203),
        [ts_sym_selector_expression] = SHIFT(203),
        [ts_sym_math_op] = SHIFT(203),
        [ts_sym_bool_op] = SHIFT(203),
        [ts_sym_var_name] = SHIFT(203),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(203),
        [ts_sym__identifier] = SHIFT(215),
        [ts_sym_number] = SHIFT(203),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(213),
    },
    [391] = {
        [ts_sym__line_break] = SHIFT(392),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(290),
        [ts_aux_sym_3] = SHIFT(392),
        [ts_aux_sym_7] = SHIFT(291),
        [ts_aux_sym_12] = SHIFT(292),
        [ts_aux_sym_13] = SHIFT(291),
        [ts_aux_sym_14] = SHIFT(293),
        [ts_aux_sym_15] = SHIFT(293),
        [ts_aux_sym_16] = SHIFT(294),
        [ts_aux_sym_17] = SHIFT(295),
        [ts_aux_sym_18] = SHIFT(296),
        [ts_aux_sym_19] = SHIFT(296),
        [ts_aux_sym_20] = SHIFT(296),
        [ts_aux_sym_21] = SHIFT(296),
        [ts_aux_sym_22] = SHIFT(296),
    },
    [392] = {
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
    [393] = {
        [ts_sym_type_expression] = SHIFT(395),
        [ts_sym_pointer_type] = SHIFT(396),
        [ts_sym_map_type] = SHIFT(396),
        [ts_sym_slice_type] = SHIFT(396),
        [ts_sym_struct_type] = SHIFT(396),
        [ts_sym_interface_type] = SHIFT(396),
        [ts_sym_type_name] = SHIFT(396),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(397),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(398),
        [ts_aux_sym_map] = SHIFT(399),
        [ts_aux_sym_8] = SHIFT(400),
        [ts_aux_sym_struct] = SHIFT(401),
        [ts_aux_sym_interface] = SHIFT(402),
    },
    [394] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_type_name, 1),
    },
    [395] = {
        [ts_sym__line_break] = SHIFT(418),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(418),
    },
    [396] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
    },
    [397] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_name, 1),
    },
    [398] = {
        [ts_sym_type_expression] = SHIFT(417),
        [ts_sym_pointer_type] = SHIFT(396),
        [ts_sym_map_type] = SHIFT(396),
        [ts_sym_slice_type] = SHIFT(396),
        [ts_sym_struct_type] = SHIFT(396),
        [ts_sym_interface_type] = SHIFT(396),
        [ts_sym_type_name] = SHIFT(396),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(397),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(398),
        [ts_aux_sym_map] = SHIFT(399),
        [ts_aux_sym_8] = SHIFT(400),
        [ts_aux_sym_struct] = SHIFT(401),
        [ts_aux_sym_interface] = SHIFT(402),
    },
    [399] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(413),
    },
    [400] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(411),
    },
    [401] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(407),
    },
    [402] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(403),
    },
    [403] = {
        [ts_sym_var_name] = SHIFT(55),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(404),
        [ts_aux_sym_6] = SHIFT(405),
    },
    [404] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(406),
    },
    [405] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 3),
    },
    [406] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
    },
    [407] = {
        [ts_sym_var_name] = SHIFT(114),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(115),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(408),
        [ts_aux_sym_6] = SHIFT(409),
    },
    [408] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(410),
    },
    [409] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 3),
    },
    [410] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 4),
    },
    [411] = {
        [ts_sym_type_expression] = SHIFT(412),
        [ts_sym_pointer_type] = SHIFT(396),
        [ts_sym_map_type] = SHIFT(396),
        [ts_sym_slice_type] = SHIFT(396),
        [ts_sym_struct_type] = SHIFT(396),
        [ts_sym_interface_type] = SHIFT(396),
        [ts_sym_type_name] = SHIFT(396),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(397),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(398),
        [ts_aux_sym_map] = SHIFT(399),
        [ts_aux_sym_8] = SHIFT(400),
        [ts_aux_sym_struct] = SHIFT(401),
        [ts_aux_sym_interface] = SHIFT(402),
    },
    [412] = {
        [ts_sym__line_break] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_slice_type, 3),
    },
    [413] = {
        [ts_sym_type_expression] = SHIFT(414),
        [ts_sym_pointer_type] = SHIFT(138),
        [ts_sym_map_type] = SHIFT(138),
        [ts_sym_slice_type] = SHIFT(138),
        [ts_sym_struct_type] = SHIFT(138),
        [ts_sym_interface_type] = SHIFT(138),
        [ts_sym_type_name] = SHIFT(138),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(139),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(140),
        [ts_aux_sym_map] = SHIFT(141),
        [ts_aux_sym_8] = SHIFT(142),
        [ts_aux_sym_struct] = SHIFT(143),
        [ts_aux_sym_interface] = SHIFT(144),
    },
    [414] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(415),
    },
    [415] = {
        [ts_sym_type_expression] = SHIFT(416),
        [ts_sym_pointer_type] = SHIFT(396),
        [ts_sym_map_type] = SHIFT(396),
        [ts_sym_slice_type] = SHIFT(396),
        [ts_sym_struct_type] = SHIFT(396),
        [ts_sym_interface_type] = SHIFT(396),
        [ts_sym_type_name] = SHIFT(396),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(397),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(398),
        [ts_aux_sym_map] = SHIFT(399),
        [ts_aux_sym_8] = SHIFT(400),
        [ts_aux_sym_struct] = SHIFT(401),
        [ts_aux_sym_interface] = SHIFT(402),
    },
    [416] = {
        [ts_sym__line_break] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
    },
    [417] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
    },
    [418] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_type_declaration, 4),
    },
    [419] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 2),
    },
    [420] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_import, 1),
    },
    [421] = {
        [ts_sym_package_import] = SHIFT(422),
        [ts_builtin_sym_error] = SHIFT(423),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(424),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(423),
        [ts_aux_sym_2] = SHIFT(425),
    },
    [422] = {
        [ts_sym_package_import] = SHIFT(422),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(424),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(427),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 1),
    },
    [423] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(426),
    },
    [424] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_package_import, 1),
    },
    [425] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 3),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 3),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 3),
    },
    [426] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 4),
    },
    [427] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 2),
    },
    [428] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [429] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [430] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_golang);
