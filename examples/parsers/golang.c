#include "tree_sitter/parser.h"

#define STATE_COUNT 372
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
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == ')')
                ADVANCE(42);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 42:
            ACCEPT_TOKEN(ts_aux_sym_2);
        case 43:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(43);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(42);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 44:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(44);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 45:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(45);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '{')
                ADVANCE(46);
            LEX_ERROR();
        case 46:
            ACCEPT_TOKEN(ts_aux_sym_5);
        case 47:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(47);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(42);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 48:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(48);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == ',')
                ADVANCE(50);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(51);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'm')
                ADVANCE(61);
            if (lookahead == 's')
                ADVANCE(64);
            LEX_ERROR();
        case 49:
            ACCEPT_TOKEN(ts_aux_sym_7);
        case 50:
            ACCEPT_TOKEN(ts_aux_sym_10);
        case 51:
            ACCEPT_TOKEN(ts_aux_sym_8);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(54);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(55);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(56);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(57);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(58);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(59);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(60);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_interface);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(62);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(63);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_map);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(65);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(66);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(67);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(68);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(69);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_struct);
        case 70:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(70);
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
                ADVANCE(46);
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
                ADVANCE(42);
            if (lookahead == ',')
                ADVANCE(50);
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
            if (lookahead == ')')
                ADVANCE(42);
            if (lookahead == ',')
                ADVANCE(50);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 73:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(73);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(51);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'm')
                ADVANCE(61);
            if (lookahead == 's')
                ADVANCE(64);
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
            if (lookahead == '[')
                ADVANCE(51);
            LEX_ERROR();
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
            if (lookahead == ']')
                ADVANCE(76);
            LEX_ERROR();
        case 76:
            ACCEPT_TOKEN(ts_aux_sym_9);
        case 77:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(77);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 78:
            ACCEPT_TOKEN(ts_aux_sym_6);
        case 79:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(79);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 80:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(80);
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
                ADVANCE(78);
            LEX_ERROR();
        case 81:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(81);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(82);
            LEX_ERROR();
        case 82:
            ACCEPT_TOKEN(ts_aux_sym_3);
        case 83:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(83);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == ':')
                ADVANCE(88);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(90);
            if (lookahead == 'i')
                ADVANCE(93);
            if (lookahead == 'r')
                ADVANCE(95);
            if (lookahead == 'v')
                ADVANCE(101);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 84:
            ACCEPT_TOKEN(ts_aux_sym_23);
        case 85:
            if (lookahead == '.')
                ADVANCE(86);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            ACCEPT_TOKEN(ts_sym_number);
        case 86:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(87);
            LEX_ERROR();
        case 87:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(87);
            ACCEPT_TOKEN(ts_sym_number);
        case 88:
            if (lookahead == '=')
                ADVANCE(89);
            LEX_ERROR();
        case 89:
            ACCEPT_TOKEN(ts_aux_sym_11);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(91);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(92);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 92:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_for);
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(94);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 95:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 96:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(97);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 97:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(98);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(99);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 99:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(100);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 100:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_return);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(102);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(103);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_var);
        case 104:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == '-')
                ADVANCE(108);
            if (lookahead == '.')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(110);
            if (lookahead == ';')
                ADVANCE(82);
            if (lookahead == '<')
                ADVANCE(111);
            if (lookahead == '=')
                ADVANCE(113);
            if (lookahead == '>')
                ADVANCE(115);
            if (lookahead == '|')
                ADVANCE(117);
            LEX_ERROR();
        case 105:
            if (lookahead == '&')
                ADVANCE(106);
            LEX_ERROR();
        case 106:
            ACCEPT_TOKEN(ts_aux_sym_17);
        case 107:
            ACCEPT_TOKEN(ts_aux_sym_14);
        case 108:
            ACCEPT_TOKEN(ts_aux_sym_15);
        case 109:
            ACCEPT_TOKEN(ts_aux_sym_12);
        case 110:
            if (lookahead == '/')
                ADVANCE(4);
            ACCEPT_TOKEN(ts_aux_sym_13);
        case 111:
            if (lookahead == '=')
                ADVANCE(112);
            ACCEPT_TOKEN(ts_aux_sym_20);
        case 112:
            ACCEPT_TOKEN(ts_aux_sym_19);
        case 113:
            if (lookahead == '=')
                ADVANCE(114);
            LEX_ERROR();
        case 114:
            ACCEPT_TOKEN(ts_aux_sym_18);
        case 115:
            if (lookahead == '=')
                ADVANCE(116);
            ACCEPT_TOKEN(ts_aux_sym_22);
        case 116:
            ACCEPT_TOKEN(ts_aux_sym_21);
        case 117:
            if (lookahead == '|')
                ADVANCE(118);
            LEX_ERROR();
        case 118:
            ACCEPT_TOKEN(ts_aux_sym_16);
        case 119:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(119);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(50);
            if (lookahead == '-')
                ADVANCE(108);
            if (lookahead == '.')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(110);
            if (lookahead == ':')
                ADVANCE(88);
            if (lookahead == ';')
                ADVANCE(82);
            if (lookahead == '<')
                ADVANCE(111);
            if (lookahead == '=')
                ADVANCE(113);
            if (lookahead == '>')
                ADVANCE(115);
            if (lookahead == '|')
                ADVANCE(117);
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
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == ';')
                ADVANCE(82);
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
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 122:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(122);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == '-')
                ADVANCE(108);
            if (lookahead == '.')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(110);
            if (lookahead == '<')
                ADVANCE(111);
            if (lookahead == '=')
                ADVANCE(113);
            if (lookahead == '>')
                ADVANCE(115);
            if (lookahead == '{')
                ADVANCE(46);
            if (lookahead == '|')
                ADVANCE(117);
            LEX_ERROR();
        case 123:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(123);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == ':')
                ADVANCE(88);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(124);
            if (lookahead == 'f')
                ADVANCE(90);
            if (lookahead == 'i')
                ADVANCE(93);
            if (lookahead == 'r')
                ADVANCE(95);
            if (lookahead == 'v')
                ADVANCE(101);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'l')
                ADVANCE(125);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(126);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 126:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(127);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 127:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_else);
        case 128:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == ')')
                ADVANCE(42);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 129:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == ')')
                ADVANCE(42);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(50);
            if (lookahead == '-')
                ADVANCE(108);
            if (lookahead == '.')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(110);
            if (lookahead == '<')
                ADVANCE(111);
            if (lookahead == '=')
                ADVANCE(113);
            if (lookahead == '>')
                ADVANCE(115);
            if (lookahead == '|')
                ADVANCE(117);
            LEX_ERROR();
        case 130:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'i')
                ADVANCE(131);
            if (lookahead == '{')
                ADVANCE(46);
            LEX_ERROR();
        case 131:
            if (lookahead == 'f')
                ADVANCE(132);
            LEX_ERROR();
        case 132:
            ACCEPT_TOKEN(ts_aux_sym_if);
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(50);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(88);
            LEX_ERROR();
        case 134:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == 'r')
                ADVANCE(135);
            LEX_ERROR();
        case 135:
            if (lookahead == 'a')
                ADVANCE(136);
            LEX_ERROR();
        case 136:
            if (lookahead == 'n')
                ADVANCE(137);
            LEX_ERROR();
        case 137:
            if (lookahead == 'g')
                ADVANCE(138);
            LEX_ERROR();
        case 138:
            if (lookahead == 'e')
                ADVANCE(139);
            LEX_ERROR();
        case 139:
            ACCEPT_TOKEN(ts_aux_sym_range);
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ':')
                ADVANCE(88);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == '-')
                ADVANCE(108);
            if (lookahead == '.')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(110);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == ':')
                ADVANCE(88);
            if (lookahead == ';')
                ADVANCE(82);
            if (lookahead == '<')
                ADVANCE(111);
            if (lookahead == '=')
                ADVANCE(113);
            if (lookahead == '>')
                ADVANCE(115);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(90);
            if (lookahead == 'i')
                ADVANCE(93);
            if (lookahead == 'r')
                ADVANCE(95);
            if (lookahead == 'v')
                ADVANCE(101);
            if (lookahead == '|')
                ADVANCE(117);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(50);
            if (lookahead == '-')
                ADVANCE(108);
            if (lookahead == '.')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(110);
            if (lookahead == ';')
                ADVANCE(82);
            if (lookahead == '<')
                ADVANCE(111);
            if (lookahead == '=')
                ADVANCE(113);
            if (lookahead == '>')
                ADVANCE(115);
            if (lookahead == '|')
                ADVANCE(117);
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
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == ':')
                ADVANCE(88);
            if (lookahead == ';')
                ADVANCE(82);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(90);
            if (lookahead == 'i')
                ADVANCE(93);
            if (lookahead == 'r')
                ADVANCE(95);
            if (lookahead == 'v')
                ADVANCE(101);
            if (lookahead == '}')
                ADVANCE(78);
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
                ADVANCE(49);
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
                ADVANCE(51);
            if (lookahead == 'i')
                ADVANCE(52);
            if (lookahead == 'm')
                ADVANCE(61);
            if (lookahead == 's')
                ADVANCE(64);
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
                ADVANCE(82);
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
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '/')
                ADVANCE(3);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == ':')
                ADVANCE(88);
            if (lookahead == ';')
                ADVANCE(82);
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
                ADVANCE(90);
            if (lookahead == 'i')
                ADVANCE(93);
            if (lookahead == 'r')
                ADVANCE(95);
            if (lookahead == 'v')
                ADVANCE(101);
            if (lookahead == '}')
                ADVANCE(78);
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
                ADVANCE(82);
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
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == '-')
                ADVANCE(108);
            if (lookahead == '.')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(110);
            if (lookahead == ';')
                ADVANCE(82);
            if (lookahead == '<')
                ADVANCE(111);
            if (lookahead == '=')
                ADVANCE(113);
            if (lookahead == '>')
                ADVANCE(115);
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            if (lookahead == '|')
                ADVANCE(117);
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
                ADVANCE(82);
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
            if (lookahead == 0)
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(151);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == ')')
                ADVANCE(42);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(50);
            if (lookahead == '-')
                ADVANCE(108);
            if (lookahead == '.')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(110);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == ':')
                ADVANCE(88);
            if (lookahead == ';')
                ADVANCE(82);
            if (lookahead == '<')
                ADVANCE(111);
            if (lookahead == '=')
                ADVANCE(152);
            if (lookahead == '>')
                ADVANCE(115);
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
                ADVANCE(51);
            if (lookahead == ']')
                ADVANCE(76);
            if (lookahead == 'e')
                ADVANCE(124);
            if (lookahead == 'f')
                ADVANCE(153);
            if (lookahead == 'i')
                ADVANCE(157);
            if (lookahead == 'm')
                ADVANCE(61);
            if (lookahead == 'p')
                ADVANCE(163);
            if (lookahead == 'r')
                ADVANCE(170);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(175);
            if (lookahead == 'v')
                ADVANCE(101);
            if (lookahead == '{')
                ADVANCE(46);
            if (lookahead == '|')
                ADVANCE(117);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 152:
            if (lookahead == '=')
                ADVANCE(114);
            ACCEPT_TOKEN(ts_aux_sym_4);
        case 153:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(91);
            if (lookahead == 'u')
                ADVANCE(154);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 154:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
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
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(156);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 156:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_func);
        case 157:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(94);
            if (lookahead == 'm')
                ADVANCE(158);
            if (lookahead == 'n')
                ADVANCE(53);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 158:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(159);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 159:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(160);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 160:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(161);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 161:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(162);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 162:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_import);
        case 163:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
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
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(165);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 165:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'k')
                ADVANCE(166);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 166:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(167);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 167:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(168);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 168:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(169);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 169:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_package);
        case 170:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(171);
            if (lookahead == 'e')
                ADVANCE(96);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 171:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(172);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 172:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(173);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 173:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(174);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 174:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(ts_aux_sym_range);
        case 175:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(33);
            if (lookahead == 'y')
                ADVANCE(176);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 176:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(177);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 177:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(178);
            ACCEPT_TOKEN(ts_sym__identifier);
        case 178:
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
                ADVANCE(151);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(40);
            if (lookahead == ')')
                ADVANCE(42);
            if (lookahead == '*')
                ADVANCE(49);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(50);
            if (lookahead == '-')
                ADVANCE(108);
            if (lookahead == '.')
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(110);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            if (lookahead == ':')
                ADVANCE(88);
            if (lookahead == ';')
                ADVANCE(82);
            if (lookahead == '<')
                ADVANCE(111);
            if (lookahead == '=')
                ADVANCE(152);
            if (lookahead == '>')
                ADVANCE(115);
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
                ADVANCE(51);
            if (lookahead == ']')
                ADVANCE(76);
            if (lookahead == 'e')
                ADVANCE(124);
            if (lookahead == 'f')
                ADVANCE(153);
            if (lookahead == 'i')
                ADVANCE(157);
            if (lookahead == 'm')
                ADVANCE(61);
            if (lookahead == 'p')
                ADVANCE(163);
            if (lookahead == 'r')
                ADVANCE(170);
            if (lookahead == 's')
                ADVANCE(64);
            if (lookahead == 't')
                ADVANCE(175);
            if (lookahead == 'v')
                ADVANCE(101);
            if (lookahead == '{')
                ADVANCE(46);
            if (lookahead == '|')
                ADVANCE(117);
            if (lookahead == '}')
                ADVANCE(78);
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
    [8] = 35,
    [9] = 14,
    [10] = 14,
    [11] = 41,
    [12] = 41,
    [13] = 43,
    [14] = 41,
    [15] = 14,
    [16] = 43,
    [17] = 34,
    [18] = 34,
    [19] = 12,
    [20] = 32,
    [21] = 32,
    [22] = 32,
    [23] = 44,
    [24] = 44,
    [25] = 45,
    [26] = 47,
    [27] = 48,
    [28] = 48,
    [29] = 70,
    [30] = 45,
    [31] = 45,
    [32] = 32,
    [33] = 32,
    [34] = 71,
    [35] = 72,
    [36] = 43,
    [37] = 32,
    [38] = 71,
    [39] = 71,
    [40] = 43,
    [41] = 45,
    [42] = 71,
    [43] = 43,
    [44] = 32,
    [45] = 32,
    [46] = 32,
    [47] = 71,
    [48] = 43,
    [49] = 45,
    [50] = 73,
    [51] = 32,
    [52] = 48,
    [53] = 73,
    [54] = 71,
    [55] = 71,
    [56] = 73,
    [57] = 74,
    [58] = 75,
    [59] = 45,
    [60] = 45,
    [61] = 77,
    [62] = 44,
    [63] = 79,
    [64] = 71,
    [65] = 77,
    [66] = 47,
    [67] = 48,
    [68] = 80,
    [69] = 77,
    [70] = 77,
    [71] = 32,
    [72] = 32,
    [73] = 71,
    [74] = 43,
    [75] = 77,
    [76] = 71,
    [77] = 43,
    [78] = 77,
    [79] = 73,
    [80] = 71,
    [81] = 43,
    [82] = 32,
    [83] = 48,
    [84] = 73,
    [85] = 32,
    [86] = 48,
    [87] = 73,
    [88] = 71,
    [89] = 43,
    [90] = 80,
    [91] = 32,
    [92] = 32,
    [93] = 71,
    [94] = 43,
    [95] = 77,
    [96] = 71,
    [97] = 43,
    [98] = 77,
    [99] = 79,
    [100] = 77,
    [101] = 73,
    [102] = 73,
    [103] = 79,
    [104] = 71,
    [105] = 77,
    [106] = 77,
    [107] = 73,
    [108] = 74,
    [109] = 75,
    [110] = 45,
    [111] = 45,
    [112] = 77,
    [113] = 79,
    [114] = 77,
    [115] = 77,
    [116] = 79,
    [117] = 77,
    [118] = 73,
    [119] = 77,
    [120] = 73,
    [121] = 75,
    [122] = 75,
    [123] = 75,
    [124] = 73,
    [125] = 74,
    [126] = 75,
    [127] = 45,
    [128] = 45,
    [129] = 77,
    [130] = 79,
    [131] = 75,
    [132] = 77,
    [133] = 79,
    [134] = 75,
    [135] = 73,
    [136] = 75,
    [137] = 73,
    [138] = 75,
    [139] = 73,
    [140] = 75,
    [141] = 75,
    [142] = 73,
    [143] = 77,
    [144] = 77,
    [145] = 79,
    [146] = 73,
    [147] = 71,
    [148] = 73,
    [149] = 75,
    [150] = 73,
    [151] = 71,
    [152] = 71,
    [153] = 43,
    [154] = 70,
    [155] = 32,
    [156] = 32,
    [157] = 71,
    [158] = 43,
    [159] = 45,
    [160] = 71,
    [161] = 43,
    [162] = 45,
    [163] = 81,
    [164] = 83,
    [165] = 83,
    [166] = 83,
    [167] = 83,
    [168] = 104,
    [169] = 104,
    [170] = 119,
    [171] = 79,
    [172] = 119,
    [173] = 32,
    [174] = 120,
    [175] = 121,
    [176] = 32,
    [177] = 121,
    [178] = 121,
    [179] = 104,
    [180] = 104,
    [181] = 122,
    [182] = 122,
    [183] = 122,
    [184] = 121,
    [185] = 122,
    [186] = 123,
    [187] = 128,
    [188] = 83,
    [189] = 121,
    [190] = 32,
    [191] = 121,
    [192] = 121,
    [193] = 121,
    [194] = 121,
    [195] = 122,
    [196] = 122,
    [197] = 122,
    [198] = 122,
    [199] = 122,
    [200] = 122,
    [201] = 79,
    [202] = 123,
    [203] = 129,
    [204] = 129,
    [205] = 129,
    [206] = 122,
    [207] = 121,
    [208] = 129,
    [209] = 43,
    [210] = 128,
    [211] = 121,
    [212] = 121,
    [213] = 32,
    [214] = 121,
    [215] = 121,
    [216] = 121,
    [217] = 121,
    [218] = 129,
    [219] = 129,
    [220] = 129,
    [221] = 129,
    [222] = 129,
    [223] = 129,
    [224] = 43,
    [225] = 129,
    [226] = 129,
    [227] = 129,
    [228] = 43,
    [229] = 129,
    [230] = 122,
    [231] = 130,
    [232] = 83,
    [233] = 83,
    [234] = 79,
    [235] = 83,
    [236] = 133,
    [237] = 133,
    [238] = 32,
    [239] = 134,
    [240] = 121,
    [241] = 122,
    [242] = 83,
    [243] = 140,
    [244] = 140,
    [245] = 134,
    [246] = 121,
    [247] = 122,
    [248] = 83,
    [249] = 104,
    [250] = 141,
    [251] = 128,
    [252] = 121,
    [253] = 32,
    [254] = 121,
    [255] = 121,
    [256] = 121,
    [257] = 121,
    [258] = 104,
    [259] = 104,
    [260] = 104,
    [261] = 104,
    [262] = 104,
    [263] = 104,
    [264] = 129,
    [265] = 104,
    [266] = 43,
    [267] = 104,
    [268] = 142,
    [269] = 142,
    [270] = 143,
    [271] = 142,
    [272] = 121,
    [273] = 142,
    [274] = 81,
    [275] = 128,
    [276] = 121,
    [277] = 121,
    [278] = 32,
    [279] = 121,
    [280] = 121,
    [281] = 121,
    [282] = 121,
    [283] = 142,
    [284] = 142,
    [285] = 142,
    [286] = 142,
    [287] = 142,
    [288] = 142,
    [289] = 81,
    [290] = 142,
    [291] = 129,
    [292] = 142,
    [293] = 43,
    [294] = 142,
    [295] = 143,
    [296] = 144,
    [297] = 144,
    [298] = 146,
    [299] = 146,
    [300] = 146,
    [301] = 121,
    [302] = 73,
    [303] = 74,
    [304] = 75,
    [305] = 45,
    [306] = 45,
    [307] = 77,
    [308] = 79,
    [309] = 146,
    [310] = 77,
    [311] = 79,
    [312] = 146,
    [313] = 73,
    [314] = 146,
    [315] = 73,
    [316] = 75,
    [317] = 73,
    [318] = 146,
    [319] = 146,
    [320] = 104,
    [321] = 141,
    [322] = 147,
    [323] = 121,
    [324] = 104,
    [325] = 141,
    [326] = 81,
    [327] = 140,
    [328] = 32,
    [329] = 133,
    [330] = 140,
    [331] = 121,
    [332] = 104,
    [333] = 141,
    [334] = 141,
    [335] = 79,
    [336] = 148,
    [337] = 144,
    [338] = 146,
    [339] = 121,
    [340] = 104,
    [341] = 149,
    [342] = 150,
    [343] = 121,
    [344] = 104,
    [345] = 149,
    [346] = 73,
    [347] = 73,
    [348] = 81,
    [349] = 81,
    [350] = 81,
    [351] = 73,
    [352] = 74,
    [353] = 75,
    [354] = 45,
    [355] = 45,
    [356] = 77,
    [357] = 79,
    [358] = 81,
    [359] = 77,
    [360] = 79,
    [361] = 81,
    [362] = 73,
    [363] = 81,
    [364] = 73,
    [365] = 75,
    [366] = 73,
    [367] = 81,
    [368] = 81,
    [369] = 148,
    [370] = 12,
    [371] = 34,
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
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 0),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = SHIFT(19),
        [ts_aux_sym_type] = SHIFT(20),
        [ts_aux_sym_var] = SHIFT(21),
        [ts_aux_sym_func] = SHIFT(22),
    },
    [8] = {
        [ts_sym_package_import] = SHIFT(9),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(10),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(11),
    },
    [9] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 2),
    },
    [10] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(14),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(13),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [12] = {
        [ts_sym_package_import] = SHIFT(12),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(14),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(16),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 0),
    },
    [13] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(15),
    },
    [14] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_package_import, 1),
    },
    [15] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 4),
    },
    [16] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = SHIFT(370),
        [ts_aux_sym_type] = SHIFT(20),
        [ts_aux_sym_var] = SHIFT(21),
        [ts_aux_sym_func] = SHIFT(22),
    },
    [18] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_declaration, 1),
    },
    [19] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [20] = {
        [ts_sym_type_name] = SHIFT(346),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(347),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [21] = {
        [ts_sym_var_name] = SHIFT(337),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(297),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [22] = {
        [ts_sym_var_name] = SHIFT(23),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [23] = {
        [ts_sym__func_signature] = SHIFT(25),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(26),
    },
    [24] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
    },
    [25] = {
        [ts_sym_block_statement] = SHIFT(163),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(164),
    },
    [26] = {
        [ts_sym_var_name] = SHIFT(27),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(29),
    },
    [27] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym__identifier] = SHIFT(31),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(32),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 2),
    },
    [30] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 3),
    },
    [31] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym_type_name, 1),
    },
    [32] = {
        [ts_sym_var_name] = SHIFT(33),
        [ts_sym_type_name] = SHIFT(34),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(35),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [33] = {
        [ts_sym_type_name] = SHIFT(42),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [34] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(36),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [35] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [36] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(41),
    },
    [37] = {
        [ts_sym_type_name] = SHIFT(38),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [38] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(40),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [39] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [40] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [41] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [42] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(43),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [43] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(49),
    },
    [44] = {
        [ts_sym_var_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [45] = {
        [ts_sym_type_name] = SHIFT(47),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [46] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [47] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(48),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [48] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [49] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [52] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(153),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_10] = SHIFT(82),
    },
    [55] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(148),
    },
    [58] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(146),
    },
    [59] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(100),
    },
    [60] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(61),
    },
    [61] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(63),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [62] = {
        [ts_sym__func_signature] = SHIFT(65),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(66),
    },
    [63] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(64),
    },
    [64] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_interface_type, 4),
    },
    [65] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(99),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [66] = {
        [ts_sym_var_name] = SHIFT(67),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(68),
    },
    [67] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym__identifier] = SHIFT(70),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(71),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 2),
    },
    [69] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 3),
    },
    [70] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_name, 1),
    },
    [71] = {
        [ts_sym_var_name] = SHIFT(72),
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(35),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [72] = {
        [ts_sym_type_name] = SHIFT(76),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [73] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(74),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [74] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(75),
    },
    [75] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [76] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(77),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [77] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(78),
    },
    [78] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(81),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_10] = SHIFT(82),
    },
    [81] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(90),
    },
    [82] = {
        [ts_sym_var_name] = SHIFT(83),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [83] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym__identifier] = SHIFT(28),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [86] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(89),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 0),
        [ts_aux_sym_10] = SHIFT(82),
    },
    [89] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [90] = {
        [ts_sym_type_name] = SHIFT(78),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(70),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(91),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [91] = {
        [ts_sym_var_name] = SHIFT(92),
        [ts_sym_type_name] = SHIFT(93),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(35),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [92] = {
        [ts_sym_type_name] = SHIFT(96),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [93] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(94),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [94] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(95),
    },
    [95] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 10),
    },
    [96] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(97),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [97] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(98),
    },
    [98] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 11),
    },
    [99] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [100] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(104),
    },
    [104] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_struct_type, 4),
    },
    [105] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(145),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [106] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(120),
    },
    [109] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(118),
    },
    [110] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(115),
    },
    [111] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(112),
    },
    [112] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(113),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [113] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(114),
    },
    [114] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_interface_type, 4),
    },
    [115] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(116),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [116] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(117),
    },
    [117] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(142),
    },
    [122] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_expression, 1),
    },
    [123] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(137),
    },
    [126] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(135),
    },
    [127] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(132),
    },
    [128] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(129),
    },
    [129] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(130),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [130] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(131),
    },
    [131] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_interface_type, 4),
    },
    [132] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(133),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [133] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(134),
    },
    [134] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_map_type, 5),
    },
    [141] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_map_type, 5),
    },
    [144] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_sym_pointer_type, 2),
    },
    [145] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_map_type, 5),
    },
    [152] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_pointer_type, 2),
    },
    [153] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(154),
    },
    [154] = {
        [ts_sym_type_name] = SHIFT(49),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(31),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(155),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [155] = {
        [ts_sym_var_name] = SHIFT(156),
        [ts_sym_type_name] = SHIFT(157),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(35),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [156] = {
        [ts_sym_type_name] = SHIFT(160),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(39),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [157] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(158),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 0),
        [ts_aux_sym_10] = SHIFT(37),
    },
    [158] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(159),
    },
    [159] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 10),
    },
    [160] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(161),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 0),
        [ts_aux_sym_10] = SHIFT(44),
    },
    [161] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(162),
    },
    [162] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 11),
    },
    [163] = {
        [ts_sym__line_break] = SHIFT(336),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(326),
    },
    [172] = {
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
    [173] = {
        [ts_sym_var_name] = SHIFT(296),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [176] = {
        [ts_sym_var_name] = SHIFT(236),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [179] = {
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
    [180] = {
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
    [181] = {
        [ts_sym_block_statement] = SHIFT(186),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [185] = {
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
    [186] = {
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
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [190] = {
        [ts_sym_var_name] = SHIFT(199),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [195] = {
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
        [ts_aux_sym_18] = SHIFT(194),
        [ts_aux_sym_19] = SHIFT(194),
        [ts_aux_sym_20] = SHIFT(194),
        [ts_aux_sym_21] = SHIFT(194),
        [ts_aux_sym_22] = SHIFT(194),
    },
    [196] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(202),
    },
    [202] = {
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
    [203] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [208] = {
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
    [209] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [213] = {
        [ts_sym_var_name] = SHIFT(222),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(204),
        [ts_sym__identifier] = SHIFT(205),
        [ts_sym_number] = SHIFT(204),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(207),
    },
    [218] = {
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
        [ts_aux_sym_18] = SHIFT(217),
        [ts_aux_sym_19] = SHIFT(217),
        [ts_aux_sym_20] = SHIFT(217),
        [ts_aux_sym_21] = SHIFT(217),
        [ts_aux_sym_22] = SHIFT(217),
    },
    [219] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 3),
    },
    [225] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(229),
    },
    [229] = {
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
    [230] = {
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
    [231] = {
        [ts_sym_block_statement] = SHIFT(232),
        [ts_sym_if_statement] = SHIFT(232),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(233),
        [ts_aux_sym_if] = SHIFT(177),
    },
    [232] = {
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(235),
    },
    [235] = {
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
    [236] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = SHIFT(238),
        [ts_aux_sym_11] = SHIFT(239),
    },
    [237] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [238] = {
        [ts_sym_var_name] = SHIFT(243),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [239] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [241] = {
        [ts_sym_block_statement] = SHIFT(242),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(245),
    },
    [244] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [245] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(182),
        [ts_sym__identifier] = SHIFT(183),
        [ts_sym_number] = SHIFT(182),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(184),
    },
    [247] = {
        [ts_sym_block_statement] = SHIFT(248),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [253] = {
        [ts_sym_var_name] = SHIFT(262),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [258] = {
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
        [ts_aux_sym_18] = SHIFT(257),
        [ts_aux_sym_19] = SHIFT(257),
        [ts_aux_sym_20] = SHIFT(257),
        [ts_aux_sym_21] = SHIFT(257),
        [ts_aux_sym_22] = SHIFT(257),
    },
    [259] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(267),
    },
    [267] = {
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
    [268] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 0),
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
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [273] = {
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
    [274] = {
        [ts_sym__line_break] = SHIFT(295),
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
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [278] = {
        [ts_sym_var_name] = SHIFT(287),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(269),
        [ts_sym__identifier] = SHIFT(271),
        [ts_sym_number] = SHIFT(269),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(272),
    },
    [283] = {
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
        [ts_aux_sym_18] = SHIFT(282),
        [ts_aux_sym_19] = SHIFT(282),
        [ts_aux_sym_20] = SHIFT(282),
        [ts_aux_sym_21] = SHIFT(282),
        [ts_aux_sym_22] = SHIFT(282),
    },
    [284] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
    },
    [290] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(294),
    },
    [294] = {
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
    [295] = {
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
    [296] = {
        [ts_sym_type_expression] = SHIFT(298),
        [ts_sym_pointer_type] = SHIFT(299),
        [ts_sym_map_type] = SHIFT(299),
        [ts_sym_slice_type] = SHIFT(299),
        [ts_sym_struct_type] = SHIFT(299),
        [ts_sym_interface_type] = SHIFT(299),
        [ts_sym_type_name] = SHIFT(299),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(322),
        [ts_aux_sym_4] = SHIFT(323),
    },
    [299] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_expression, 1),
    },
    [300] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(315),
    },
    [304] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(313),
    },
    [305] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(310),
    },
    [306] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(307),
    },
    [307] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(308),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [308] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(309),
    },
    [309] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_interface_type, 4),
    },
    [310] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(311),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [311] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(312),
    },
    [312] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_4] = REDUCE(ts_sym_map_type, 5),
    },
    [319] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_pointer_type, 2),
    },
    [320] = {
        [ts_sym__line_break] = SHIFT(321),
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
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [324] = {
        [ts_sym__line_break] = SHIFT(325),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_block_statement, 3),
    },
    [327] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(331),
    },
    [328] = {
        [ts_sym_var_name] = SHIFT(329),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(237),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [329] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(330),
        [ts_aux_sym_10] = SHIFT(328),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 0),
    },
    [330] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [332] = {
        [ts_sym__line_break] = SHIFT(333),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 2),
    },
    [336] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
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
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [340] = {
        [ts_sym__line_break] = SHIFT(341),
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
        [ts_sym_string] = SHIFT(169),
        [ts_sym__identifier] = SHIFT(180),
        [ts_sym_number] = SHIFT(169),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(178),
    },
    [344] = {
        [ts_sym__line_break] = SHIFT(345),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(369),
    },
    [349] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
    },
    [350] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(364),
    },
    [353] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(362),
    },
    [354] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(359),
    },
    [355] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(356),
    },
    [356] = {
        [ts_sym_var_name] = SHIFT(62),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(24),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(357),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 0),
    },
    [357] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(358),
    },
    [358] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
    },
    [359] = {
        [ts_sym_var_name] = SHIFT(101),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(102),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(360),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 0),
    },
    [360] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(361),
    },
    [361] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
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
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
    },
    [368] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
    },
    [369] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_type] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_type_declaration, 4),
    },
    [370] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [371] = {
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
