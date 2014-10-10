#include "tree_sitter/parser.h"

#define STATE_COUNT 436
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
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
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
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
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
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(36);
            LEX_ERROR();
        case 39:
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '\\')
                ADVANCE(38);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
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
    [36] = 69,
    [37] = 71,
    [38] = 32,
    [39] = 32,
    [40] = 32,
    [41] = 69,
    [42] = 71,
    [43] = 42,
    [44] = 69,
    [45] = 69,
    [46] = 69,
    [47] = 72,
    [48] = 72,
    [49] = 73,
    [50] = 74,
    [51] = 42,
    [52] = 42,
    [53] = 32,
    [54] = 46,
    [55] = 72,
    [56] = 76,
    [57] = 41,
    [58] = 78,
    [59] = 69,
    [60] = 69,
    [61] = 76,
    [62] = 44,
    [63] = 46,
    [64] = 79,
    [65] = 76,
    [66] = 76,
    [67] = 32,
    [68] = 32,
    [69] = 69,
    [70] = 71,
    [71] = 76,
    [72] = 76,
    [73] = 69,
    [74] = 71,
    [75] = 76,
    [76] = 69,
    [77] = 72,
    [78] = 69,
    [79] = 71,
    [80] = 79,
    [81] = 32,
    [82] = 46,
    [83] = 46,
    [84] = 69,
    [85] = 72,
    [86] = 32,
    [87] = 46,
    [88] = 72,
    [89] = 69,
    [90] = 71,
    [91] = 71,
    [92] = 32,
    [93] = 32,
    [94] = 69,
    [95] = 71,
    [96] = 76,
    [97] = 76,
    [98] = 69,
    [99] = 71,
    [100] = 76,
    [101] = 79,
    [102] = 32,
    [103] = 32,
    [104] = 69,
    [105] = 69,
    [106] = 71,
    [107] = 76,
    [108] = 71,
    [109] = 79,
    [110] = 32,
    [111] = 32,
    [112] = 69,
    [113] = 71,
    [114] = 69,
    [115] = 78,
    [116] = 76,
    [117] = 72,
    [118] = 72,
    [119] = 78,
    [120] = 69,
    [121] = 69,
    [122] = 76,
    [123] = 76,
    [124] = 76,
    [125] = 72,
    [126] = 73,
    [127] = 74,
    [128] = 42,
    [129] = 42,
    [130] = 76,
    [131] = 78,
    [132] = 76,
    [133] = 76,
    [134] = 76,
    [135] = 78,
    [136] = 76,
    [137] = 76,
    [138] = 72,
    [139] = 76,
    [140] = 72,
    [141] = 74,
    [142] = 74,
    [143] = 74,
    [144] = 72,
    [145] = 73,
    [146] = 74,
    [147] = 42,
    [148] = 42,
    [149] = 76,
    [150] = 78,
    [151] = 74,
    [152] = 74,
    [153] = 76,
    [154] = 78,
    [155] = 74,
    [156] = 74,
    [157] = 72,
    [158] = 74,
    [159] = 72,
    [160] = 74,
    [161] = 72,
    [162] = 74,
    [163] = 74,
    [164] = 72,
    [165] = 76,
    [166] = 76,
    [167] = 78,
    [168] = 72,
    [169] = 69,
    [170] = 72,
    [171] = 74,
    [172] = 72,
    [173] = 69,
    [174] = 69,
    [175] = 69,
    [176] = 71,
    [177] = 68,
    [178] = 32,
    [179] = 32,
    [180] = 69,
    [181] = 71,
    [182] = 42,
    [183] = 42,
    [184] = 69,
    [185] = 71,
    [186] = 42,
    [187] = 68,
    [188] = 32,
    [189] = 32,
    [190] = 69,
    [191] = 69,
    [192] = 71,
    [193] = 42,
    [194] = 71,
    [195] = 68,
    [196] = 32,
    [197] = 32,
    [198] = 69,
    [199] = 71,
    [200] = 69,
    [201] = 80,
    [202] = 82,
    [203] = 82,
    [204] = 82,
    [205] = 82,
    [206] = 103,
    [207] = 103,
    [208] = 118,
    [209] = 78,
    [210] = 118,
    [211] = 32,
    [212] = 80,
    [213] = 119,
    [214] = 120,
    [215] = 32,
    [216] = 120,
    [217] = 120,
    [218] = 103,
    [219] = 103,
    [220] = 121,
    [221] = 121,
    [222] = 121,
    [223] = 120,
    [224] = 121,
    [225] = 122,
    [226] = 127,
    [227] = 82,
    [228] = 120,
    [229] = 32,
    [230] = 120,
    [231] = 120,
    [232] = 120,
    [233] = 120,
    [234] = 121,
    [235] = 121,
    [236] = 121,
    [237] = 121,
    [238] = 121,
    [239] = 121,
    [240] = 78,
    [241] = 122,
    [242] = 122,
    [243] = 128,
    [244] = 128,
    [245] = 128,
    [246] = 121,
    [247] = 120,
    [248] = 128,
    [249] = 71,
    [250] = 127,
    [251] = 121,
    [252] = 120,
    [253] = 120,
    [254] = 32,
    [255] = 120,
    [256] = 120,
    [257] = 120,
    [258] = 120,
    [259] = 128,
    [260] = 128,
    [261] = 128,
    [262] = 128,
    [263] = 128,
    [264] = 128,
    [265] = 71,
    [266] = 128,
    [267] = 128,
    [268] = 128,
    [269] = 71,
    [270] = 128,
    [271] = 128,
    [272] = 121,
    [273] = 129,
    [274] = 82,
    [275] = 82,
    [276] = 78,
    [277] = 82,
    [278] = 82,
    [279] = 132,
    [280] = 132,
    [281] = 32,
    [282] = 133,
    [283] = 120,
    [284] = 121,
    [285] = 82,
    [286] = 139,
    [287] = 139,
    [288] = 133,
    [289] = 120,
    [290] = 121,
    [291] = 82,
    [292] = 103,
    [293] = 140,
    [294] = 127,
    [295] = 120,
    [296] = 32,
    [297] = 120,
    [298] = 120,
    [299] = 120,
    [300] = 120,
    [301] = 103,
    [302] = 103,
    [303] = 103,
    [304] = 103,
    [305] = 103,
    [306] = 103,
    [307] = 128,
    [308] = 103,
    [309] = 71,
    [310] = 103,
    [311] = 103,
    [312] = 141,
    [313] = 141,
    [314] = 142,
    [315] = 141,
    [316] = 120,
    [317] = 141,
    [318] = 143,
    [319] = 80,
    [320] = 127,
    [321] = 120,
    [322] = 120,
    [323] = 32,
    [324] = 120,
    [325] = 120,
    [326] = 120,
    [327] = 120,
    [328] = 141,
    [329] = 141,
    [330] = 141,
    [331] = 141,
    [332] = 141,
    [333] = 141,
    [334] = 80,
    [335] = 141,
    [336] = 128,
    [337] = 141,
    [338] = 71,
    [339] = 141,
    [340] = 141,
    [341] = 142,
    [342] = 144,
    [343] = 144,
    [344] = 146,
    [345] = 146,
    [346] = 146,
    [347] = 120,
    [348] = 72,
    [349] = 73,
    [350] = 74,
    [351] = 42,
    [352] = 42,
    [353] = 76,
    [354] = 78,
    [355] = 146,
    [356] = 146,
    [357] = 76,
    [358] = 78,
    [359] = 146,
    [360] = 146,
    [361] = 72,
    [362] = 146,
    [363] = 72,
    [364] = 74,
    [365] = 72,
    [366] = 146,
    [367] = 146,
    [368] = 103,
    [369] = 140,
    [370] = 147,
    [371] = 120,
    [372] = 103,
    [373] = 140,
    [374] = 80,
    [375] = 139,
    [376] = 32,
    [377] = 120,
    [378] = 103,
    [379] = 140,
    [380] = 132,
    [381] = 132,
    [382] = 139,
    [383] = 120,
    [384] = 103,
    [385] = 140,
    [386] = 140,
    [387] = 78,
    [388] = 148,
    [389] = 144,
    [390] = 146,
    [391] = 120,
    [392] = 103,
    [393] = 149,
    [394] = 150,
    [395] = 120,
    [396] = 103,
    [397] = 149,
    [398] = 72,
    [399] = 72,
    [400] = 80,
    [401] = 80,
    [402] = 80,
    [403] = 72,
    [404] = 73,
    [405] = 74,
    [406] = 42,
    [407] = 42,
    [408] = 76,
    [409] = 78,
    [410] = 80,
    [411] = 80,
    [412] = 76,
    [413] = 78,
    [414] = 80,
    [415] = 80,
    [416] = 72,
    [417] = 80,
    [418] = 72,
    [419] = 74,
    [420] = 72,
    [421] = 80,
    [422] = 80,
    [423] = 148,
    [424] = 14,
    [425] = 14,
    [426] = 151,
    [427] = 151,
    [428] = 71,
    [429] = 151,
    [430] = 14,
    [431] = 14,
    [432] = 71,
    [433] = 12,
    [434] = 12,
    [435] = 34,
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
        [ts_sym_imports_block] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym_declaration] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym_type_declaration] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym_var_declaration] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym_func_declaration] = REDUCE(ts_sym_package_directive, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_directive, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_directive, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_directive, 2),
    },
    [5] = {
        [ts_sym_imports_block] = REDUCE(ts_sym_package_name, 1),
        [ts_sym_declaration] = REDUCE(ts_sym_package_name, 1),
        [ts_sym_type_declaration] = REDUCE(ts_sym_package_name, 1),
        [ts_sym_var_declaration] = REDUCE(ts_sym_package_name, 1),
        [ts_sym_func_declaration] = REDUCE(ts_sym_package_name, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_name, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_name, 1),
    },
    [6] = {
        [ts_sym_imports_block] = SHIFT(6),
        [ts_sym_declaration] = REDUCE(ts_aux_sym_program_repeat0, 1),
        [ts_sym_type_declaration] = REDUCE(ts_aux_sym_program_repeat0, 1),
        [ts_sym_var_declaration] = REDUCE(ts_aux_sym_program_repeat0, 1),
        [ts_sym_func_declaration] = REDUCE(ts_aux_sym_program_repeat0, 1),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = SHIFT(435),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_aux_sym_program_repeat0, 1),
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
        [ts_aux_sym_program_repeat1] = SHIFT(434),
        [ts_aux_sym_type] = SHIFT(12),
        [ts_aux_sym_var] = SHIFT(13),
        [ts_aux_sym_func] = SHIFT(14),
    },
    [8] = {
        [ts_sym_declaration] = REDUCE(ts_sym_declaration, 1),
        [ts_sym_type_declaration] = REDUCE(ts_sym_declaration, 1),
        [ts_sym_var_declaration] = REDUCE(ts_sym_declaration, 1),
        [ts_sym_func_declaration] = REDUCE(ts_sym_declaration, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_declaration, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_declaration, 1),
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
        [ts_aux_sym_program_repeat1] = SHIFT(433),
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
        [ts_sym_package_import] = SHIFT(424),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(425),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(426),
    },
    [12] = {
        [ts_sym_type_name] = SHIFT(398),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(399),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [13] = {
        [ts_sym_var_name] = SHIFT(389),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(343),
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
        [ts_sym__func_signature] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_var_name, 1),
    },
    [17] = {
        [ts_sym_block_statement] = SHIFT(201),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(202),
    },
    [18] = {
        [ts_sym_var_name] = SHIFT(19),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(20),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(21),
    },
    [19] = {
        [ts_sym_type_expression] = SHIFT(44),
        [ts_sym_pointer_type] = SHIFT(45),
        [ts_sym_map_type] = SHIFT(45),
        [ts_sym_slice_type] = SHIFT(45),
        [ts_sym_struct_type] = SHIFT(45),
        [ts_sym_interface_type] = SHIFT(45),
        [ts_sym_type_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(47),
        [ts_aux_sym_7] = SHIFT(48),
        [ts_aux_sym_map] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
        [ts_aux_sym_struct] = SHIFT(51),
        [ts_aux_sym_interface] = SHIFT(52),
        [ts_aux_sym_10] = SHIFT(53),
    },
    [20] = {
        [ts_sym_type_expression] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_pointer_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_map_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_slice_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_struct_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_interface_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_type_name] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
    },
    [21] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 2),
        [ts_sym_type_name] = SHIFT(22),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(24),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 2),
    },
    [22] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 3),
    },
    [23] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_type_name, 1),
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
        [ts_sym__identifier] = SHIFT(36),
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
        [ts_sym_type_name] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [28] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(34),
    },
    [29] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 5),
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
        [ts_aux_sym__func_signature_repeat4] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [33] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat4, 3),
    },
    [34] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [35] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(37),
        [ts_aux_sym_2] = SHIFT(34),
        [ts_aux_sym_10] = SHIFT(38),
    },
    [36] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [37] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(43),
    },
    [38] = {
        [ts_sym_var_name] = SHIFT(39),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(40),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [39] = {
        [ts_sym_type_name] = SHIFT(41),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(36),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [40] = {
        [ts_sym_type_name] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [41] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(42),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 3),
        [ts_aux_sym_10] = SHIFT(38),
    },
    [42] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat3, 4),
    },
    [43] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 7),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 7),
    },
    [44] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(194),
        [ts_aux_sym_2] = SHIFT(195),
        [ts_aux_sym_10] = SHIFT(81),
    },
    [45] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_expression, 1),
    },
    [46] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_type_name, 1),
    },
    [47] = {
        [ts_sym_type_expression] = SHIFT(175),
        [ts_sym_pointer_type] = SHIFT(45),
        [ts_sym_map_type] = SHIFT(45),
        [ts_sym_slice_type] = SHIFT(45),
        [ts_sym_struct_type] = SHIFT(45),
        [ts_sym_interface_type] = SHIFT(45),
        [ts_sym_type_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(48),
        [ts_aux_sym_map] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
        [ts_aux_sym_struct] = SHIFT(51),
        [ts_aux_sym_interface] = SHIFT(52),
    },
    [48] = {
        [ts_sym_type_expression] = SHIFT(174),
        [ts_sym_pointer_type] = SHIFT(45),
        [ts_sym_map_type] = SHIFT(45),
        [ts_sym_slice_type] = SHIFT(45),
        [ts_sym_struct_type] = SHIFT(45),
        [ts_sym_interface_type] = SHIFT(45),
        [ts_sym_type_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(48),
        [ts_aux_sym_map] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
        [ts_aux_sym_struct] = SHIFT(51),
        [ts_aux_sym_interface] = SHIFT(52),
    },
    [49] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(170),
    },
    [50] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(168),
    },
    [51] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(116),
    },
    [52] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(56),
    },
    [53] = {
        [ts_sym_var_name] = SHIFT(54),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(20),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [54] = {
        [ts_sym_type_expression] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_sym_pointer_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_sym_map_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_sym_slice_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_sym_struct_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_sym_interface_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_sym_type_name] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(55),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 2),
        [ts_aux_sym_10] = SHIFT(53),
    },
    [55] = {
        [ts_sym_type_expression] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_pointer_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_map_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_slice_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_struct_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_interface_type] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_type_name] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat0, 3),
    },
    [56] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(58),
        [ts_aux_sym_6] = SHIFT(59),
    },
    [57] = {
        [ts_sym__func_signature] = SHIFT(61),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(62),
    },
    [58] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(60),
    },
    [59] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = REDUCE(ts_sym_interface_type, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_interface_type, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_interface_type, 3),
    },
    [60] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_2] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_interface_type, 4),
    },
    [61] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(115),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 2),
    },
    [62] = {
        [ts_sym_var_name] = SHIFT(63),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(20),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(64),
    },
    [63] = {
        [ts_sym_type_expression] = SHIFT(76),
        [ts_sym_pointer_type] = SHIFT(45),
        [ts_sym_map_type] = SHIFT(45),
        [ts_sym_slice_type] = SHIFT(45),
        [ts_sym_struct_type] = SHIFT(45),
        [ts_sym_interface_type] = SHIFT(45),
        [ts_sym_type_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat0] = SHIFT(77),
        [ts_aux_sym_7] = SHIFT(48),
        [ts_aux_sym_map] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
        [ts_aux_sym_struct] = SHIFT(51),
        [ts_aux_sym_interface] = SHIFT(52),
        [ts_aux_sym_10] = SHIFT(53),
    },
    [64] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 2),
        [ts_sym_type_name] = SHIFT(65),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(66),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 2),
        [ts_aux_sym_1] = SHIFT(67),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 2),
    },
    [65] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 3),
    },
    [66] = {
        [ts_sym_var_name] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_name, 1),
    },
    [67] = {
        [ts_sym_var_name] = SHIFT(68),
        [ts_sym_type_name] = SHIFT(69),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [68] = {
        [ts_sym_type_name] = SHIFT(73),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(36),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [69] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(70),
        [ts_aux_sym_2] = SHIFT(71),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [70] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(72),
    },
    [71] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 5),
    },
    [72] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 6),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [73] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(74),
        [ts_aux_sym_2] = SHIFT(72),
        [ts_aux_sym_10] = SHIFT(38),
    },
    [74] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(75),
    },
    [75] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 7),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 7),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 7),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 7),
    },
    [76] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(108),
        [ts_aux_sym_2] = SHIFT(109),
        [ts_aux_sym_10] = SHIFT(81),
    },
    [77] = {
        [ts_sym_type_expression] = SHIFT(78),
        [ts_sym_pointer_type] = SHIFT(45),
        [ts_sym_map_type] = SHIFT(45),
        [ts_sym_slice_type] = SHIFT(45),
        [ts_sym_struct_type] = SHIFT(45),
        [ts_sym_interface_type] = SHIFT(45),
        [ts_sym_type_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(48),
        [ts_aux_sym_map] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
        [ts_aux_sym_struct] = SHIFT(51),
        [ts_aux_sym_interface] = SHIFT(52),
    },
    [78] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(79),
        [ts_aux_sym_2] = SHIFT(80),
        [ts_aux_sym_10] = SHIFT(81),
    },
    [79] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(101),
    },
    [80] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 5),
        [ts_sym_type_name] = SHIFT(72),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(66),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 5),
        [ts_aux_sym_1] = SHIFT(92),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 5),
    },
    [81] = {
        [ts_sym_var_name] = SHIFT(82),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(83),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [82] = {
        [ts_sym_type_expression] = SHIFT(84),
        [ts_sym_pointer_type] = SHIFT(45),
        [ts_sym_map_type] = SHIFT(45),
        [ts_sym_slice_type] = SHIFT(45),
        [ts_sym_struct_type] = SHIFT(45),
        [ts_sym_interface_type] = SHIFT(45),
        [ts_sym_type_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(85),
        [ts_aux_sym_7] = SHIFT(48),
        [ts_aux_sym_map] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
        [ts_aux_sym_struct] = SHIFT(51),
        [ts_aux_sym_interface] = SHIFT(52),
        [ts_aux_sym_10] = SHIFT(86),
    },
    [83] = {
        [ts_sym_type_expression] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_pointer_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_map_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_slice_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_struct_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_interface_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_type_name] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat1] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
    },
    [84] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(91),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 3),
        [ts_aux_sym_10] = SHIFT(81),
    },
    [85] = {
        [ts_sym_type_expression] = SHIFT(89),
        [ts_sym_pointer_type] = SHIFT(45),
        [ts_sym_map_type] = SHIFT(45),
        [ts_sym_slice_type] = SHIFT(45),
        [ts_sym_struct_type] = SHIFT(45),
        [ts_sym_interface_type] = SHIFT(45),
        [ts_sym_type_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(48),
        [ts_aux_sym_map] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
        [ts_aux_sym_struct] = SHIFT(51),
        [ts_aux_sym_interface] = SHIFT(52),
    },
    [86] = {
        [ts_sym_var_name] = SHIFT(87),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(83),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [87] = {
        [ts_sym_type_expression] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_sym_pointer_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_sym_map_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_sym_slice_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_sym_struct_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_sym_interface_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_sym_type_name] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat1] = SHIFT(88),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 2),
        [ts_aux_sym_10] = SHIFT(86),
    },
    [88] = {
        [ts_sym_type_expression] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_pointer_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_map_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_slice_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_struct_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_interface_type] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_type_name] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_map] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_8] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_struct] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
        [ts_aux_sym_interface] = REDUCE(ts_aux_sym__func_signature_repeat1, 3),
    },
    [89] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(90),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 4),
        [ts_aux_sym_10] = SHIFT(81),
    },
    [90] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 5),
    },
    [91] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym__func_signature_repeat2, 4),
    },
    [92] = {
        [ts_sym_var_name] = SHIFT(93),
        [ts_sym_type_name] = SHIFT(94),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [93] = {
        [ts_sym_type_name] = SHIFT(98),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(36),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [94] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(95),
        [ts_aux_sym_2] = SHIFT(96),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [95] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(97),
    },
    [96] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 8),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 8),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 8),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 8),
    },
    [97] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 9),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 9),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 9),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 9),
    },
    [98] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(99),
        [ts_aux_sym_2] = SHIFT(97),
        [ts_aux_sym_10] = SHIFT(38),
    },
    [99] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(100),
    },
    [100] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 10),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 10),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 10),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 10),
    },
    [101] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym_type_name] = SHIFT(75),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(66),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 6),
        [ts_aux_sym_1] = SHIFT(102),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 6),
    },
    [102] = {
        [ts_sym_var_name] = SHIFT(103),
        [ts_sym_type_name] = SHIFT(104),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [103] = {
        [ts_sym_type_name] = SHIFT(105),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(36),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [104] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(99),
        [ts_aux_sym_2] = SHIFT(97),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [105] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(106),
        [ts_aux_sym_2] = SHIFT(100),
        [ts_aux_sym_10] = SHIFT(38),
    },
    [106] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(107),
    },
    [107] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 11),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym__func_signature, 11),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 11),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 11),
    },
    [108] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(80),
    },
    [109] = {
        [ts_sym_var_name] = REDUCE(ts_sym__func_signature, 4),
        [ts_sym_type_name] = SHIFT(71),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(66),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = REDUCE(ts_sym__func_signature, 4),
        [ts_aux_sym_1] = SHIFT(110),
        [ts_aux_sym_6] = REDUCE(ts_sym__func_signature, 4),
    },
    [110] = {
        [ts_sym_var_name] = SHIFT(111),
        [ts_sym_type_name] = SHIFT(112),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [111] = {
        [ts_sym_type_name] = SHIFT(114),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(36),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [112] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(113),
        [ts_aux_sym_2] = SHIFT(75),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [113] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(96),
    },
    [114] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(95),
        [ts_aux_sym_2] = SHIFT(96),
        [ts_aux_sym_10] = SHIFT(38),
    },
    [115] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_interface_type_repeat0, 3),
    },
    [116] = {
        [ts_sym_var_name] = SHIFT(117),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(118),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(119),
        [ts_aux_sym_6] = SHIFT(120),
    },
    [117] = {
        [ts_sym_type_expression] = SHIFT(122),
        [ts_sym_pointer_type] = SHIFT(123),
        [ts_sym_map_type] = SHIFT(123),
        [ts_sym_slice_type] = SHIFT(123),
        [ts_sym_struct_type] = SHIFT(123),
        [ts_sym_interface_type] = SHIFT(123),
        [ts_sym_type_name] = SHIFT(123),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(124),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(125),
        [ts_aux_sym_map] = SHIFT(126),
        [ts_aux_sym_8] = SHIFT(127),
        [ts_aux_sym_struct] = SHIFT(128),
        [ts_aux_sym_interface] = SHIFT(129),
    },
    [118] = {
        [ts_sym_type_expression] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_pointer_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_map_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_slice_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_struct_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_interface_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_type_name] = REDUCE(ts_sym_var_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_var_name, 1),
    },
    [119] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(121),
    },
    [120] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = REDUCE(ts_sym_struct_type, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_struct_type, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_struct_type, 3),
    },
    [121] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_2] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_10] = REDUCE(ts_sym_struct_type, 4),
    },
    [122] = {
        [ts_sym_var_name] = SHIFT(117),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(118),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(167),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 2),
    },
    [123] = {
        [ts_sym_var_name] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_expression, 1),
    },
    [124] = {
        [ts_sym_var_name] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_type_name, 1),
    },
    [125] = {
        [ts_sym_type_expression] = SHIFT(166),
        [ts_sym_pointer_type] = SHIFT(123),
        [ts_sym_map_type] = SHIFT(123),
        [ts_sym_slice_type] = SHIFT(123),
        [ts_sym_struct_type] = SHIFT(123),
        [ts_sym_interface_type] = SHIFT(123),
        [ts_sym_type_name] = SHIFT(123),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(124),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(125),
        [ts_aux_sym_map] = SHIFT(126),
        [ts_aux_sym_8] = SHIFT(127),
        [ts_aux_sym_struct] = SHIFT(128),
        [ts_aux_sym_interface] = SHIFT(129),
    },
    [126] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(140),
    },
    [127] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(138),
    },
    [128] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(134),
    },
    [129] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(130),
    },
    [130] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(131),
        [ts_aux_sym_6] = SHIFT(132),
    },
    [131] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(133),
    },
    [132] = {
        [ts_sym_var_name] = REDUCE(ts_sym_interface_type, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = REDUCE(ts_sym_interface_type, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_interface_type, 3),
    },
    [133] = {
        [ts_sym_var_name] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_interface_type, 4),
    },
    [134] = {
        [ts_sym_var_name] = SHIFT(117),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(118),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(135),
        [ts_aux_sym_6] = SHIFT(136),
    },
    [135] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(137),
    },
    [136] = {
        [ts_sym_var_name] = REDUCE(ts_sym_struct_type, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = REDUCE(ts_sym_struct_type, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_struct_type, 3),
    },
    [137] = {
        [ts_sym_var_name] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_struct_type, 4),
    },
    [138] = {
        [ts_sym_type_expression] = SHIFT(139),
        [ts_sym_pointer_type] = SHIFT(123),
        [ts_sym_map_type] = SHIFT(123),
        [ts_sym_slice_type] = SHIFT(123),
        [ts_sym_struct_type] = SHIFT(123),
        [ts_sym_interface_type] = SHIFT(123),
        [ts_sym_type_name] = SHIFT(123),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(124),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(125),
        [ts_aux_sym_map] = SHIFT(126),
        [ts_aux_sym_8] = SHIFT(127),
        [ts_aux_sym_struct] = SHIFT(128),
        [ts_aux_sym_interface] = SHIFT(129),
    },
    [139] = {
        [ts_sym_var_name] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_slice_type, 3),
    },
    [140] = {
        [ts_sym_type_expression] = SHIFT(141),
        [ts_sym_pointer_type] = SHIFT(142),
        [ts_sym_map_type] = SHIFT(142),
        [ts_sym_slice_type] = SHIFT(142),
        [ts_sym_struct_type] = SHIFT(142),
        [ts_sym_interface_type] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(143),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(144),
        [ts_aux_sym_map] = SHIFT(145),
        [ts_aux_sym_8] = SHIFT(146),
        [ts_aux_sym_struct] = SHIFT(147),
        [ts_aux_sym_interface] = SHIFT(148),
    },
    [141] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(164),
    },
    [142] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_expression, 1),
    },
    [143] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_type_name, 1),
    },
    [144] = {
        [ts_sym_type_expression] = SHIFT(163),
        [ts_sym_pointer_type] = SHIFT(142),
        [ts_sym_map_type] = SHIFT(142),
        [ts_sym_slice_type] = SHIFT(142),
        [ts_sym_struct_type] = SHIFT(142),
        [ts_sym_interface_type] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(143),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(144),
        [ts_aux_sym_map] = SHIFT(145),
        [ts_aux_sym_8] = SHIFT(146),
        [ts_aux_sym_struct] = SHIFT(147),
        [ts_aux_sym_interface] = SHIFT(148),
    },
    [145] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(159),
    },
    [146] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(157),
    },
    [147] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(153),
    },
    [148] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(149),
    },
    [149] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(150),
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
        [ts_aux_sym_9] = REDUCE(ts_sym_interface_type, 3),
    },
    [152] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_interface_type, 4),
    },
    [153] = {
        [ts_sym_var_name] = SHIFT(117),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(118),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(154),
        [ts_aux_sym_6] = SHIFT(155),
    },
    [154] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(156),
    },
    [155] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_struct_type, 3),
    },
    [156] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_struct_type, 4),
    },
    [157] = {
        [ts_sym_type_expression] = SHIFT(158),
        [ts_sym_pointer_type] = SHIFT(142),
        [ts_sym_map_type] = SHIFT(142),
        [ts_sym_slice_type] = SHIFT(142),
        [ts_sym_struct_type] = SHIFT(142),
        [ts_sym_interface_type] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(143),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(144),
        [ts_aux_sym_map] = SHIFT(145),
        [ts_aux_sym_8] = SHIFT(146),
        [ts_aux_sym_struct] = SHIFT(147),
        [ts_aux_sym_interface] = SHIFT(148),
    },
    [158] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_slice_type, 3),
    },
    [159] = {
        [ts_sym_type_expression] = SHIFT(160),
        [ts_sym_pointer_type] = SHIFT(142),
        [ts_sym_map_type] = SHIFT(142),
        [ts_sym_slice_type] = SHIFT(142),
        [ts_sym_struct_type] = SHIFT(142),
        [ts_sym_interface_type] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(143),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(144),
        [ts_aux_sym_map] = SHIFT(145),
        [ts_aux_sym_8] = SHIFT(146),
        [ts_aux_sym_struct] = SHIFT(147),
        [ts_aux_sym_interface] = SHIFT(148),
    },
    [160] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(161),
    },
    [161] = {
        [ts_sym_type_expression] = SHIFT(162),
        [ts_sym_pointer_type] = SHIFT(142),
        [ts_sym_map_type] = SHIFT(142),
        [ts_sym_slice_type] = SHIFT(142),
        [ts_sym_struct_type] = SHIFT(142),
        [ts_sym_interface_type] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(143),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(144),
        [ts_aux_sym_map] = SHIFT(145),
        [ts_aux_sym_8] = SHIFT(146),
        [ts_aux_sym_struct] = SHIFT(147),
        [ts_aux_sym_interface] = SHIFT(148),
    },
    [162] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_map_type, 5),
    },
    [163] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = REDUCE(ts_sym_pointer_type, 2),
    },
    [164] = {
        [ts_sym_type_expression] = SHIFT(165),
        [ts_sym_pointer_type] = SHIFT(123),
        [ts_sym_map_type] = SHIFT(123),
        [ts_sym_slice_type] = SHIFT(123),
        [ts_sym_struct_type] = SHIFT(123),
        [ts_sym_interface_type] = SHIFT(123),
        [ts_sym_type_name] = SHIFT(123),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(124),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(125),
        [ts_aux_sym_map] = SHIFT(126),
        [ts_aux_sym_8] = SHIFT(127),
        [ts_aux_sym_struct] = SHIFT(128),
        [ts_aux_sym_interface] = SHIFT(129),
    },
    [165] = {
        [ts_sym_var_name] = REDUCE(ts_sym_map_type, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_map_type, 5),
    },
    [166] = {
        [ts_sym_var_name] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_pointer_type, 2),
    },
    [167] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_struct_type_repeat0, 3),
    },
    [168] = {
        [ts_sym_type_expression] = SHIFT(169),
        [ts_sym_pointer_type] = SHIFT(45),
        [ts_sym_map_type] = SHIFT(45),
        [ts_sym_slice_type] = SHIFT(45),
        [ts_sym_struct_type] = SHIFT(45),
        [ts_sym_interface_type] = SHIFT(45),
        [ts_sym_type_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(48),
        [ts_aux_sym_map] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
        [ts_aux_sym_struct] = SHIFT(51),
        [ts_aux_sym_interface] = SHIFT(52),
    },
    [169] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_10] = REDUCE(ts_sym_slice_type, 3),
    },
    [170] = {
        [ts_sym_type_expression] = SHIFT(171),
        [ts_sym_pointer_type] = SHIFT(142),
        [ts_sym_map_type] = SHIFT(142),
        [ts_sym_slice_type] = SHIFT(142),
        [ts_sym_struct_type] = SHIFT(142),
        [ts_sym_interface_type] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(143),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(144),
        [ts_aux_sym_map] = SHIFT(145),
        [ts_aux_sym_8] = SHIFT(146),
        [ts_aux_sym_struct] = SHIFT(147),
        [ts_aux_sym_interface] = SHIFT(148),
    },
    [171] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(172),
    },
    [172] = {
        [ts_sym_type_expression] = SHIFT(173),
        [ts_sym_pointer_type] = SHIFT(45),
        [ts_sym_map_type] = SHIFT(45),
        [ts_sym_slice_type] = SHIFT(45),
        [ts_sym_struct_type] = SHIFT(45),
        [ts_sym_interface_type] = SHIFT(45),
        [ts_sym_type_name] = SHIFT(45),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(46),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(48),
        [ts_aux_sym_map] = SHIFT(49),
        [ts_aux_sym_8] = SHIFT(50),
        [ts_aux_sym_struct] = SHIFT(51),
        [ts_aux_sym_interface] = SHIFT(52),
    },
    [173] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_2] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_10] = REDUCE(ts_sym_map_type, 5),
    },
    [174] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_2] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_10] = REDUCE(ts_sym_pointer_type, 2),
    },
    [175] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat2] = SHIFT(176),
        [ts_aux_sym_2] = SHIFT(177),
        [ts_aux_sym_10] = SHIFT(81),
    },
    [176] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(187),
    },
    [177] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 5),
        [ts_sym_type_name] = SHIFT(34),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(178),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 5),
    },
    [178] = {
        [ts_sym_var_name] = SHIFT(179),
        [ts_sym_type_name] = SHIFT(180),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [179] = {
        [ts_sym_type_name] = SHIFT(184),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(36),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [180] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(181),
        [ts_aux_sym_2] = SHIFT(182),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [181] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(183),
    },
    [182] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 8),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 8),
    },
    [183] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 9),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 9),
    },
    [184] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(185),
        [ts_aux_sym_2] = SHIFT(183),
        [ts_aux_sym_10] = SHIFT(38),
    },
    [185] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(186),
    },
    [186] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 10),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 10),
    },
    [187] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 6),
        [ts_sym_type_name] = SHIFT(43),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(188),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 6),
    },
    [188] = {
        [ts_sym_var_name] = SHIFT(189),
        [ts_sym_type_name] = SHIFT(190),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [189] = {
        [ts_sym_type_name] = SHIFT(191),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(36),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [190] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(185),
        [ts_aux_sym_2] = SHIFT(183),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [191] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(192),
        [ts_aux_sym_2] = SHIFT(186),
        [ts_aux_sym_10] = SHIFT(38),
    },
    [192] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(193),
    },
    [193] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 11),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 11),
    },
    [194] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(177),
    },
    [195] = {
        [ts_sym_block_statement] = REDUCE(ts_sym__func_signature, 4),
        [ts_sym_type_name] = SHIFT(29),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(23),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(196),
        [ts_aux_sym_5] = REDUCE(ts_sym__func_signature, 4),
    },
    [196] = {
        [ts_sym_var_name] = SHIFT(197),
        [ts_sym_type_name] = SHIFT(198),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(27),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [197] = {
        [ts_sym_type_name] = SHIFT(200),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(36),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [198] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat4] = SHIFT(199),
        [ts_aux_sym_2] = SHIFT(43),
        [ts_aux_sym_10] = SHIFT(30),
    },
    [199] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(182),
    },
    [200] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym__func_signature_repeat3] = SHIFT(181),
        [ts_aux_sym_2] = SHIFT(182),
        [ts_aux_sym_10] = SHIFT(38),
    },
    [201] = {
        [ts_sym__line_break] = SHIFT(388),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(388),
    },
    [202] = {
        [ts_sym_var_declaration] = SHIFT(203),
        [ts_sym_statement] = SHIFT(204),
        [ts_sym_return_statement] = SHIFT(205),
        [ts_sym_declaration_statement] = SHIFT(205),
        [ts_sym_range_statement] = SHIFT(205),
        [ts_sym_if_statement] = SHIFT(205),
        [ts_sym_expression_statement] = SHIFT(205),
        [ts_sym_expression] = SHIFT(206),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(208),
        [ts_builtin_sym_error] = SHIFT(209),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(209),
        [ts_aux_sym_var] = SHIFT(211),
        [ts_aux_sym_6] = SHIFT(212),
        [ts_aux_sym_return] = SHIFT(213),
        [ts_aux_sym_11] = SHIFT(214),
        [ts_aux_sym_for] = SHIFT(215),
        [ts_aux_sym_if] = SHIFT(216),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [203] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_statement] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_return_statement] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_range_statement] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_if_statement] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_expression_statement] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_expression] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_call_expression] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_selector_expression] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_math_op] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_bool_op] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_var_name] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_for] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_declaration_statement, 1),
        [ts_aux_sym_23] = REDUCE(ts_sym_declaration_statement, 1),
    },
    [204] = {
        [ts_sym_var_declaration] = SHIFT(203),
        [ts_sym_statement] = SHIFT(204),
        [ts_sym_return_statement] = SHIFT(205),
        [ts_sym_declaration_statement] = SHIFT(205),
        [ts_sym_range_statement] = SHIFT(205),
        [ts_sym_if_statement] = SHIFT(205),
        [ts_sym_expression_statement] = SHIFT(205),
        [ts_sym_expression] = SHIFT(206),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(208),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(387),
        [ts_aux_sym_var] = SHIFT(211),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 1),
        [ts_aux_sym_return] = SHIFT(213),
        [ts_aux_sym_11] = SHIFT(214),
        [ts_aux_sym_for] = SHIFT(215),
        [ts_aux_sym_if] = SHIFT(216),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [205] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_statement, 1),
        [ts_sym_statement] = REDUCE(ts_sym_statement, 1),
        [ts_sym_return_statement] = REDUCE(ts_sym_statement, 1),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_statement, 1),
        [ts_sym_range_statement] = REDUCE(ts_sym_statement, 1),
        [ts_sym_if_statement] = REDUCE(ts_sym_statement, 1),
        [ts_sym_expression_statement] = REDUCE(ts_sym_statement, 1),
        [ts_sym_expression] = REDUCE(ts_sym_statement, 1),
        [ts_sym_call_expression] = REDUCE(ts_sym_statement, 1),
        [ts_sym_selector_expression] = REDUCE(ts_sym_statement, 1),
        [ts_sym_math_op] = REDUCE(ts_sym_statement, 1),
        [ts_sym_bool_op] = REDUCE(ts_sym_statement, 1),
        [ts_sym_var_name] = REDUCE(ts_sym_statement, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_statement, 1),
        [ts_sym__identifier] = REDUCE(ts_sym_statement, 1),
        [ts_sym_number] = REDUCE(ts_sym_statement, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_6] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_return] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_for] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_if] = REDUCE(ts_sym_statement, 1),
        [ts_aux_sym_23] = REDUCE(ts_sym_statement, 1),
    },
    [206] = {
        [ts_sym__line_break] = SHIFT(386),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(294),
        [ts_aux_sym_3] = SHIFT(386),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = SHIFT(296),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [207] = {
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
    [208] = {
        [ts_sym__line_break] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(375),
        [ts_aux_sym_1] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_3] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_7] = REDUCE(ts_sym_expression, 1),
        [ts_aux_sym_10] = SHIFT(376),
        [ts_aux_sym_11] = SHIFT(377),
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
    [209] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(374),
    },
    [210] = {
        [ts_sym__line_break] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = REDUCE(ts_sym_var_name, 1),
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
    [211] = {
        [ts_sym_var_name] = SHIFT(342),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(343),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [212] = {
        [ts_sym__line_break] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_block_statement, 2),
    },
    [213] = {
        [ts_sym_expression] = SHIFT(312),
        [ts_sym_call_expression] = SHIFT(313),
        [ts_sym_selector_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(313),
        [ts_sym_bool_op] = SHIFT(313),
        [ts_sym_var_name] = SHIFT(313),
        [ts_sym__line_break] = SHIFT(314),
        [ts_sym_string] = SHIFT(313),
        [ts_sym__identifier] = SHIFT(315),
        [ts_sym_number] = SHIFT(313),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(314),
        [ts_aux_sym_23] = SHIFT(316),
    },
    [214] = {
        [ts_sym_expression] = SHIFT(292),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [215] = {
        [ts_sym_var_name] = SHIFT(279),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(280),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [216] = {
        [ts_sym_expression] = SHIFT(220),
        [ts_sym_call_expression] = SHIFT(221),
        [ts_sym_selector_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(221),
        [ts_sym_bool_op] = SHIFT(221),
        [ts_sym_var_name] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(221),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_number] = SHIFT(221),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(223),
    },
    [217] = {
        [ts_sym_expression] = SHIFT(218),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [218] = {
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
    [219] = {
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
    [220] = {
        [ts_sym_block_statement] = SHIFT(225),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(226),
        [ts_aux_sym_5] = SHIFT(227),
        [ts_aux_sym_7] = SHIFT(228),
        [ts_aux_sym_12] = SHIFT(229),
        [ts_aux_sym_13] = SHIFT(228),
        [ts_aux_sym_14] = SHIFT(230),
        [ts_aux_sym_15] = SHIFT(230),
        [ts_aux_sym_16] = SHIFT(231),
        [ts_aux_sym_17] = SHIFT(232),
        [ts_aux_sym_18] = SHIFT(233),
        [ts_aux_sym_19] = SHIFT(233),
        [ts_aux_sym_20] = SHIFT(233),
        [ts_aux_sym_21] = SHIFT(233),
        [ts_aux_sym_22] = SHIFT(233),
    },
    [221] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_expression, 1),
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
    [222] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_var_name, 1),
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
    [223] = {
        [ts_sym_expression] = SHIFT(224),
        [ts_sym_call_expression] = SHIFT(221),
        [ts_sym_selector_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(221),
        [ts_sym_bool_op] = SHIFT(221),
        [ts_sym_var_name] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(221),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_number] = SHIFT(221),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(223),
    },
    [224] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_bool_op, 2),
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
    [225] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_statement] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_return_statement] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_range_statement] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_if_statement] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_expression_statement] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_expression] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_call_expression] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_selector_expression] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_math_op] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_bool_op] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_var_name] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_for] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_if_statement, 3),
        [ts_aux_sym_else] = SHIFT(273),
        [ts_aux_sym_23] = REDUCE(ts_sym_if_statement, 3),
    },
    [226] = {
        [ts_sym_expression] = SHIFT(243),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(246),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [227] = {
        [ts_sym_var_declaration] = SHIFT(203),
        [ts_sym_statement] = SHIFT(204),
        [ts_sym_return_statement] = SHIFT(205),
        [ts_sym_declaration_statement] = SHIFT(205),
        [ts_sym_range_statement] = SHIFT(205),
        [ts_sym_if_statement] = SHIFT(205),
        [ts_sym_expression_statement] = SHIFT(205),
        [ts_sym_expression] = SHIFT(206),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(208),
        [ts_builtin_sym_error] = SHIFT(240),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(240),
        [ts_aux_sym_var] = SHIFT(211),
        [ts_aux_sym_6] = SHIFT(241),
        [ts_aux_sym_return] = SHIFT(213),
        [ts_aux_sym_11] = SHIFT(214),
        [ts_aux_sym_for] = SHIFT(215),
        [ts_aux_sym_if] = SHIFT(216),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [228] = {
        [ts_sym_expression] = SHIFT(239),
        [ts_sym_call_expression] = SHIFT(221),
        [ts_sym_selector_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(221),
        [ts_sym_bool_op] = SHIFT(221),
        [ts_sym_var_name] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(221),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_number] = SHIFT(221),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(223),
    },
    [229] = {
        [ts_sym_var_name] = SHIFT(238),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [230] = {
        [ts_sym_expression] = SHIFT(237),
        [ts_sym_call_expression] = SHIFT(221),
        [ts_sym_selector_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(221),
        [ts_sym_bool_op] = SHIFT(221),
        [ts_sym_var_name] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(221),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_number] = SHIFT(221),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(223),
    },
    [231] = {
        [ts_sym_expression] = SHIFT(236),
        [ts_sym_call_expression] = SHIFT(221),
        [ts_sym_selector_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(221),
        [ts_sym_bool_op] = SHIFT(221),
        [ts_sym_var_name] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(221),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_number] = SHIFT(221),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(223),
    },
    [232] = {
        [ts_sym_expression] = SHIFT(235),
        [ts_sym_call_expression] = SHIFT(221),
        [ts_sym_selector_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(221),
        [ts_sym_bool_op] = SHIFT(221),
        [ts_sym_var_name] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(221),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_number] = SHIFT(221),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(223),
    },
    [233] = {
        [ts_sym_expression] = SHIFT(234),
        [ts_sym_call_expression] = SHIFT(221),
        [ts_sym_selector_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(221),
        [ts_sym_bool_op] = SHIFT(221),
        [ts_sym_var_name] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(221),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_number] = SHIFT(221),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(223),
    },
    [234] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_bool_op, 3),
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
        [ts_aux_sym_18] = SHIFT(233),
        [ts_aux_sym_19] = SHIFT(233),
        [ts_aux_sym_20] = SHIFT(233),
        [ts_aux_sym_21] = SHIFT(233),
        [ts_aux_sym_22] = SHIFT(233),
    },
    [235] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(228),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(228),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(232),
        [ts_aux_sym_18] = SHIFT(233),
        [ts_aux_sym_19] = SHIFT(233),
        [ts_aux_sym_20] = SHIFT(233),
        [ts_aux_sym_21] = SHIFT(233),
        [ts_aux_sym_22] = SHIFT(233),
    },
    [236] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(228),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(228),
        [ts_aux_sym_14] = SHIFT(230),
        [ts_aux_sym_15] = SHIFT(230),
        [ts_aux_sym_16] = SHIFT(231),
        [ts_aux_sym_17] = SHIFT(232),
        [ts_aux_sym_18] = SHIFT(233),
        [ts_aux_sym_19] = SHIFT(233),
        [ts_aux_sym_20] = SHIFT(233),
        [ts_aux_sym_21] = SHIFT(233),
        [ts_aux_sym_22] = SHIFT(233),
    },
    [237] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(228),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(228),
        [ts_aux_sym_14] = SHIFT(230),
        [ts_aux_sym_15] = SHIFT(230),
        [ts_aux_sym_16] = SHIFT(231),
        [ts_aux_sym_17] = SHIFT(232),
        [ts_aux_sym_18] = SHIFT(233),
        [ts_aux_sym_19] = SHIFT(233),
        [ts_aux_sym_20] = SHIFT(233),
        [ts_aux_sym_21] = SHIFT(233),
        [ts_aux_sym_22] = SHIFT(233),
    },
    [238] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_selector_expression, 3),
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
    [239] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_math_op, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_5] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(228),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(228),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(232),
        [ts_aux_sym_18] = SHIFT(233),
        [ts_aux_sym_19] = SHIFT(233),
        [ts_aux_sym_20] = SHIFT(233),
        [ts_aux_sym_21] = SHIFT(233),
        [ts_aux_sym_22] = SHIFT(233),
    },
    [240] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(242),
    },
    [241] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_return_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_range_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_if_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_expression_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_expression] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_call_expression] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_selector_expression] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_math_op] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_bool_op] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_var_name] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_for] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_else] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_23] = REDUCE(ts_sym_block_statement, 2),
    },
    [242] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_return_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_range_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_if_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_expression_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_expression] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_call_expression] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_selector_expression] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_math_op] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_bool_op] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_var_name] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_for] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_else] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_23] = REDUCE(ts_sym_block_statement, 3),
    },
    [243] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(249),
        [ts_aux_sym_1] = SHIFT(250),
        [ts_aux_sym_2] = SHIFT(251),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_10] = SHIFT(253),
        [ts_aux_sym_12] = SHIFT(254),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(255),
        [ts_aux_sym_15] = SHIFT(255),
        [ts_aux_sym_16] = SHIFT(256),
        [ts_aux_sym_17] = SHIFT(257),
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [244] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_expression, 1),
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
    [245] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_var_name, 1),
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
    [246] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_call_expression, 3),
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
    [247] = {
        [ts_sym_expression] = SHIFT(248),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [248] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_bool_op, 2),
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
    [249] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(272),
    },
    [250] = {
        [ts_sym_expression] = SHIFT(267),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(268),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [251] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_call_expression, 4),
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
    [252] = {
        [ts_sym_expression] = SHIFT(266),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [253] = {
        [ts_sym_expression] = SHIFT(264),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [254] = {
        [ts_sym_var_name] = SHIFT(263),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [255] = {
        [ts_sym_expression] = SHIFT(262),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [256] = {
        [ts_sym_expression] = SHIFT(261),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [257] = {
        [ts_sym_expression] = SHIFT(260),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [258] = {
        [ts_sym_expression] = SHIFT(259),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [259] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_bool_op, 3),
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
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [260] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(257),
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [261] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(255),
        [ts_aux_sym_15] = SHIFT(255),
        [ts_aux_sym_16] = SHIFT(256),
        [ts_aux_sym_17] = SHIFT(257),
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [262] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(255),
        [ts_aux_sym_15] = SHIFT(255),
        [ts_aux_sym_16] = SHIFT(256),
        [ts_aux_sym_17] = SHIFT(257),
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [263] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_selector_expression, 3),
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
    [264] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(265),
        [ts_aux_sym_1] = SHIFT(250),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 2),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_10] = SHIFT(253),
        [ts_aux_sym_12] = SHIFT(254),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(255),
        [ts_aux_sym_15] = SHIFT(255),
        [ts_aux_sym_16] = SHIFT(256),
        [ts_aux_sym_17] = SHIFT(257),
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [265] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_call_expression_repeat0, 3),
    },
    [266] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_2] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(257),
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [267] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(269),
        [ts_aux_sym_1] = SHIFT(250),
        [ts_aux_sym_2] = SHIFT(270),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_10] = SHIFT(253),
        [ts_aux_sym_12] = SHIFT(254),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(255),
        [ts_aux_sym_15] = SHIFT(255),
        [ts_aux_sym_16] = SHIFT(256),
        [ts_aux_sym_17] = SHIFT(257),
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [268] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_call_expression, 3),
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
    [269] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(271),
    },
    [270] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_call_expression, 4),
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
    [271] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = REDUCE(ts_sym_call_expression, 5),
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
    [272] = {
        [ts_sym_block_statement] = REDUCE(ts_sym_call_expression, 5),
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
    [273] = {
        [ts_sym_block_statement] = SHIFT(274),
        [ts_sym_if_statement] = SHIFT(274),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(275),
        [ts_aux_sym_if] = SHIFT(216),
    },
    [274] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_statement] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_return_statement] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_range_statement] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_if_statement] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_expression_statement] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_expression] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_call_expression] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_selector_expression] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_math_op] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_bool_op] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_var_name] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_if_statement, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_var] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_6] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_return] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_11] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_for] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_if] = REDUCE(ts_sym_if_statement, 5),
        [ts_aux_sym_23] = REDUCE(ts_sym_if_statement, 5),
    },
    [275] = {
        [ts_sym_var_declaration] = SHIFT(203),
        [ts_sym_statement] = SHIFT(204),
        [ts_sym_return_statement] = SHIFT(205),
        [ts_sym_declaration_statement] = SHIFT(205),
        [ts_sym_range_statement] = SHIFT(205),
        [ts_sym_if_statement] = SHIFT(205),
        [ts_sym_expression_statement] = SHIFT(205),
        [ts_sym_expression] = SHIFT(206),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(208),
        [ts_builtin_sym_error] = SHIFT(276),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(210),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = SHIFT(276),
        [ts_aux_sym_var] = SHIFT(211),
        [ts_aux_sym_6] = SHIFT(277),
        [ts_aux_sym_return] = SHIFT(213),
        [ts_aux_sym_11] = SHIFT(214),
        [ts_aux_sym_for] = SHIFT(215),
        [ts_aux_sym_if] = SHIFT(216),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [276] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(278),
    },
    [277] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_return_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_range_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_if_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_expression_statement] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_expression] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_call_expression] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_selector_expression] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_math_op] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_bool_op] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_var_name] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_for] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 2),
        [ts_aux_sym_23] = REDUCE(ts_sym_block_statement, 2),
    },
    [278] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_return_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_range_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_if_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_expression_statement] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_expression] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_call_expression] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_selector_expression] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_math_op] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_bool_op] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_var_name] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_6] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_return] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_11] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_for] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_if] = REDUCE(ts_sym_block_statement, 3),
        [ts_aux_sym_23] = REDUCE(ts_sym_block_statement, 3),
    },
    [279] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = SHIFT(281),
        [ts_aux_sym_11] = SHIFT(282),
    },
    [280] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [281] = {
        [ts_sym_var_name] = SHIFT(286),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(287),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [282] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_range] = SHIFT(283),
    },
    [283] = {
        [ts_sym_expression] = SHIFT(284),
        [ts_sym_call_expression] = SHIFT(221),
        [ts_sym_selector_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(221),
        [ts_sym_bool_op] = SHIFT(221),
        [ts_sym_var_name] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(221),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_number] = SHIFT(221),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(223),
    },
    [284] = {
        [ts_sym_block_statement] = SHIFT(285),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(226),
        [ts_aux_sym_5] = SHIFT(275),
        [ts_aux_sym_7] = SHIFT(228),
        [ts_aux_sym_12] = SHIFT(229),
        [ts_aux_sym_13] = SHIFT(228),
        [ts_aux_sym_14] = SHIFT(230),
        [ts_aux_sym_15] = SHIFT(230),
        [ts_aux_sym_16] = SHIFT(231),
        [ts_aux_sym_17] = SHIFT(232),
        [ts_aux_sym_18] = SHIFT(233),
        [ts_aux_sym_19] = SHIFT(233),
        [ts_aux_sym_20] = SHIFT(233),
        [ts_aux_sym_21] = SHIFT(233),
        [ts_aux_sym_22] = SHIFT(233),
    },
    [285] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_statement] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_return_statement] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_range_statement] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_if_statement] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_expression_statement] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_expression] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_call_expression] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_selector_expression] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_math_op] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_bool_op] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_var_name] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym__identifier] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_number] = REDUCE(ts_sym_range_statement, 6),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_var] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_6] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_return] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_11] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_for] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_if] = REDUCE(ts_sym_range_statement, 6),
        [ts_aux_sym_23] = REDUCE(ts_sym_range_statement, 6),
    },
    [286] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(288),
    },
    [287] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [288] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_range] = SHIFT(289),
    },
    [289] = {
        [ts_sym_expression] = SHIFT(290),
        [ts_sym_call_expression] = SHIFT(221),
        [ts_sym_selector_expression] = SHIFT(221),
        [ts_sym_math_op] = SHIFT(221),
        [ts_sym_bool_op] = SHIFT(221),
        [ts_sym_var_name] = SHIFT(221),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(221),
        [ts_sym__identifier] = SHIFT(222),
        [ts_sym_number] = SHIFT(221),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(223),
    },
    [290] = {
        [ts_sym_block_statement] = SHIFT(291),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(226),
        [ts_aux_sym_5] = SHIFT(275),
        [ts_aux_sym_7] = SHIFT(228),
        [ts_aux_sym_12] = SHIFT(229),
        [ts_aux_sym_13] = SHIFT(228),
        [ts_aux_sym_14] = SHIFT(230),
        [ts_aux_sym_15] = SHIFT(230),
        [ts_aux_sym_16] = SHIFT(231),
        [ts_aux_sym_17] = SHIFT(232),
        [ts_aux_sym_18] = SHIFT(233),
        [ts_aux_sym_19] = SHIFT(233),
        [ts_aux_sym_20] = SHIFT(233),
        [ts_aux_sym_21] = SHIFT(233),
        [ts_aux_sym_22] = SHIFT(233),
    },
    [291] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_statement] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_return_statement] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_range_statement] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_if_statement] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_expression_statement] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_expression] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_call_expression] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_selector_expression] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_math_op] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_bool_op] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_var_name] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym__identifier] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_number] = REDUCE(ts_sym_range_statement, 8),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_var] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_6] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_return] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_11] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_for] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_if] = REDUCE(ts_sym_range_statement, 8),
        [ts_aux_sym_23] = REDUCE(ts_sym_range_statement, 8),
    },
    [292] = {
        [ts_sym__line_break] = SHIFT(293),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(294),
        [ts_aux_sym_3] = SHIFT(293),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = SHIFT(296),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [293] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_statement] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_return_statement] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_range_statement] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_if_statement] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_expression_statement] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_expression] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_call_expression] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_selector_expression] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_math_op] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_bool_op] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_var_name] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_declaration_statement, 3),
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
    [294] = {
        [ts_sym_expression] = SHIFT(307),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(308),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [295] = {
        [ts_sym_expression] = SHIFT(306),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [296] = {
        [ts_sym_var_name] = SHIFT(305),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [297] = {
        [ts_sym_expression] = SHIFT(304),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [298] = {
        [ts_sym_expression] = SHIFT(303),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [299] = {
        [ts_sym_expression] = SHIFT(302),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [300] = {
        [ts_sym_expression] = SHIFT(301),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [301] = {
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
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [302] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [303] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [304] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [305] = {
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
    [306] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [307] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(309),
        [ts_aux_sym_1] = SHIFT(250),
        [ts_aux_sym_2] = SHIFT(310),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_10] = SHIFT(253),
        [ts_aux_sym_12] = SHIFT(254),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(255),
        [ts_aux_sym_15] = SHIFT(255),
        [ts_aux_sym_16] = SHIFT(256),
        [ts_aux_sym_17] = SHIFT(257),
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [308] = {
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
    [309] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(311),
    },
    [310] = {
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
    [311] = {
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
    [312] = {
        [ts_sym__line_break] = SHIFT(318),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(319),
        [ts_aux_sym_1] = SHIFT(320),
        [ts_aux_sym_3] = SHIFT(318),
        [ts_aux_sym_7] = SHIFT(321),
        [ts_aux_sym_10] = SHIFT(322),
        [ts_aux_sym_12] = SHIFT(323),
        [ts_aux_sym_13] = SHIFT(321),
        [ts_aux_sym_14] = SHIFT(324),
        [ts_aux_sym_15] = SHIFT(324),
        [ts_aux_sym_16] = SHIFT(325),
        [ts_aux_sym_17] = SHIFT(326),
        [ts_aux_sym_18] = SHIFT(327),
        [ts_aux_sym_19] = SHIFT(327),
        [ts_aux_sym_20] = SHIFT(327),
        [ts_aux_sym_21] = SHIFT(327),
        [ts_aux_sym_22] = SHIFT(327),
    },
    [313] = {
        [ts_sym__line_break] = REDUCE(ts_sym_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_expression, 1),
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
    [314] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_statement] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_return_statement] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_range_statement] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_if_statement] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_expression_statement] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_expression] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_call_expression] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_selector_expression] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_math_op] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_bool_op] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_var_name] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_6] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_return] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_11] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_for] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_if] = REDUCE(ts_sym_return_statement, 2),
        [ts_aux_sym_23] = REDUCE(ts_sym_return_statement, 2),
    },
    [315] = {
        [ts_sym__line_break] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_var_name, 1),
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
    [316] = {
        [ts_sym_expression] = SHIFT(317),
        [ts_sym_call_expression] = SHIFT(313),
        [ts_sym_selector_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(313),
        [ts_sym_bool_op] = SHIFT(313),
        [ts_sym_var_name] = SHIFT(313),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(313),
        [ts_sym__identifier] = SHIFT(315),
        [ts_sym_number] = SHIFT(313),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(316),
    },
    [317] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_bool_op, 2),
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
    [318] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_statement] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_return_statement] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_range_statement] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_if_statement] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_expression_statement] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_expression] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_call_expression] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_selector_expression] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_math_op] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_bool_op] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_var_name] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym__identifier] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_return_statement, 3),
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
    [319] = {
        [ts_sym__line_break] = SHIFT(341),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(341),
    },
    [320] = {
        [ts_sym_expression] = SHIFT(336),
        [ts_sym_call_expression] = SHIFT(244),
        [ts_sym_selector_expression] = SHIFT(244),
        [ts_sym_math_op] = SHIFT(244),
        [ts_sym_bool_op] = SHIFT(244),
        [ts_sym_var_name] = SHIFT(244),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(244),
        [ts_sym__identifier] = SHIFT(245),
        [ts_sym_number] = SHIFT(244),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(337),
        [ts_aux_sym_23] = SHIFT(247),
    },
    [321] = {
        [ts_sym_expression] = SHIFT(335),
        [ts_sym_call_expression] = SHIFT(313),
        [ts_sym_selector_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(313),
        [ts_sym_bool_op] = SHIFT(313),
        [ts_sym_var_name] = SHIFT(313),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(313),
        [ts_sym__identifier] = SHIFT(315),
        [ts_sym_number] = SHIFT(313),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(316),
    },
    [322] = {
        [ts_sym_expression] = SHIFT(333),
        [ts_sym_call_expression] = SHIFT(313),
        [ts_sym_selector_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(313),
        [ts_sym_bool_op] = SHIFT(313),
        [ts_sym_var_name] = SHIFT(313),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(313),
        [ts_sym__identifier] = SHIFT(315),
        [ts_sym_number] = SHIFT(313),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(316),
    },
    [323] = {
        [ts_sym_var_name] = SHIFT(332),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(315),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [324] = {
        [ts_sym_expression] = SHIFT(331),
        [ts_sym_call_expression] = SHIFT(313),
        [ts_sym_selector_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(313),
        [ts_sym_bool_op] = SHIFT(313),
        [ts_sym_var_name] = SHIFT(313),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(313),
        [ts_sym__identifier] = SHIFT(315),
        [ts_sym_number] = SHIFT(313),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(316),
    },
    [325] = {
        [ts_sym_expression] = SHIFT(330),
        [ts_sym_call_expression] = SHIFT(313),
        [ts_sym_selector_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(313),
        [ts_sym_bool_op] = SHIFT(313),
        [ts_sym_var_name] = SHIFT(313),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(313),
        [ts_sym__identifier] = SHIFT(315),
        [ts_sym_number] = SHIFT(313),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(316),
    },
    [326] = {
        [ts_sym_expression] = SHIFT(329),
        [ts_sym_call_expression] = SHIFT(313),
        [ts_sym_selector_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(313),
        [ts_sym_bool_op] = SHIFT(313),
        [ts_sym_var_name] = SHIFT(313),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(313),
        [ts_sym__identifier] = SHIFT(315),
        [ts_sym_number] = SHIFT(313),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(316),
    },
    [327] = {
        [ts_sym_expression] = SHIFT(328),
        [ts_sym_call_expression] = SHIFT(313),
        [ts_sym_selector_expression] = SHIFT(313),
        [ts_sym_math_op] = SHIFT(313),
        [ts_sym_bool_op] = SHIFT(313),
        [ts_sym_var_name] = SHIFT(313),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(313),
        [ts_sym__identifier] = SHIFT(315),
        [ts_sym_number] = SHIFT(313),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(316),
    },
    [328] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_bool_op, 3),
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
        [ts_aux_sym_18] = SHIFT(327),
        [ts_aux_sym_19] = SHIFT(327),
        [ts_aux_sym_20] = SHIFT(327),
        [ts_aux_sym_21] = SHIFT(327),
        [ts_aux_sym_22] = SHIFT(327),
    },
    [329] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(321),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(321),
        [ts_aux_sym_14] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_17] = SHIFT(326),
        [ts_aux_sym_18] = SHIFT(327),
        [ts_aux_sym_19] = SHIFT(327),
        [ts_aux_sym_20] = SHIFT(327),
        [ts_aux_sym_21] = SHIFT(327),
        [ts_aux_sym_22] = SHIFT(327),
    },
    [330] = {
        [ts_sym__line_break] = REDUCE(ts_sym_bool_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_1] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_7] = SHIFT(321),
        [ts_aux_sym_10] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_bool_op, 3),
        [ts_aux_sym_13] = SHIFT(321),
        [ts_aux_sym_14] = SHIFT(324),
        [ts_aux_sym_15] = SHIFT(324),
        [ts_aux_sym_16] = SHIFT(325),
        [ts_aux_sym_17] = SHIFT(326),
        [ts_aux_sym_18] = SHIFT(327),
        [ts_aux_sym_19] = SHIFT(327),
        [ts_aux_sym_20] = SHIFT(327),
        [ts_aux_sym_21] = SHIFT(327),
        [ts_aux_sym_22] = SHIFT(327),
    },
    [331] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(321),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(321),
        [ts_aux_sym_14] = SHIFT(324),
        [ts_aux_sym_15] = SHIFT(324),
        [ts_aux_sym_16] = SHIFT(325),
        [ts_aux_sym_17] = SHIFT(326),
        [ts_aux_sym_18] = SHIFT(327),
        [ts_aux_sym_19] = SHIFT(327),
        [ts_aux_sym_20] = SHIFT(327),
        [ts_aux_sym_21] = SHIFT(327),
        [ts_aux_sym_22] = SHIFT(327),
    },
    [332] = {
        [ts_sym__line_break] = REDUCE(ts_sym_selector_expression, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_selector_expression, 3),
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
    [333] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = SHIFT(334),
        [ts_aux_sym_1] = SHIFT(320),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 2),
        [ts_aux_sym_7] = SHIFT(321),
        [ts_aux_sym_10] = SHIFT(322),
        [ts_aux_sym_12] = SHIFT(323),
        [ts_aux_sym_13] = SHIFT(321),
        [ts_aux_sym_14] = SHIFT(324),
        [ts_aux_sym_15] = SHIFT(324),
        [ts_aux_sym_16] = SHIFT(325),
        [ts_aux_sym_17] = SHIFT(326),
        [ts_aux_sym_18] = SHIFT(327),
        [ts_aux_sym_19] = SHIFT(327),
        [ts_aux_sym_20] = SHIFT(327),
        [ts_aux_sym_21] = SHIFT(327),
        [ts_aux_sym_22] = SHIFT(327),
    },
    [334] = {
        [ts_sym__line_break] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_aux_sym_return_statement_repeat0, 3),
    },
    [335] = {
        [ts_sym__line_break] = REDUCE(ts_sym_math_op, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_1] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_3] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_7] = SHIFT(321),
        [ts_aux_sym_10] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_12] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_13] = SHIFT(321),
        [ts_aux_sym_14] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_15] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_16] = REDUCE(ts_sym_math_op, 3),
        [ts_aux_sym_17] = SHIFT(326),
        [ts_aux_sym_18] = SHIFT(327),
        [ts_aux_sym_19] = SHIFT(327),
        [ts_aux_sym_20] = SHIFT(327),
        [ts_aux_sym_21] = SHIFT(327),
        [ts_aux_sym_22] = SHIFT(327),
    },
    [336] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_call_expression_repeat0] = SHIFT(338),
        [ts_aux_sym_1] = SHIFT(250),
        [ts_aux_sym_2] = SHIFT(339),
        [ts_aux_sym_7] = SHIFT(252),
        [ts_aux_sym_10] = SHIFT(253),
        [ts_aux_sym_12] = SHIFT(254),
        [ts_aux_sym_13] = SHIFT(252),
        [ts_aux_sym_14] = SHIFT(255),
        [ts_aux_sym_15] = SHIFT(255),
        [ts_aux_sym_16] = SHIFT(256),
        [ts_aux_sym_17] = SHIFT(257),
        [ts_aux_sym_18] = SHIFT(258),
        [ts_aux_sym_19] = SHIFT(258),
        [ts_aux_sym_20] = SHIFT(258),
        [ts_aux_sym_21] = SHIFT(258),
        [ts_aux_sym_22] = SHIFT(258),
    },
    [337] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_call_expression, 3),
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
    [338] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(340),
    },
    [339] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_call_expression, 4),
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
    [340] = {
        [ts_sym__line_break] = REDUCE(ts_sym_call_expression, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_return_statement_repeat0] = REDUCE(ts_sym_call_expression, 5),
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
    [341] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_statement] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_return_statement] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_range_statement] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_if_statement] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_expression_statement] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_expression] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_call_expression] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_selector_expression] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_math_op] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_bool_op] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_var_name] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym__identifier] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_number] = REDUCE(ts_sym_return_statement, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_6] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_return] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_11] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_for] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_if] = REDUCE(ts_sym_return_statement, 4),
        [ts_aux_sym_23] = REDUCE(ts_sym_return_statement, 4),
    },
    [342] = {
        [ts_sym_type_expression] = SHIFT(344),
        [ts_sym_pointer_type] = SHIFT(345),
        [ts_sym_map_type] = SHIFT(345),
        [ts_sym_slice_type] = SHIFT(345),
        [ts_sym_struct_type] = SHIFT(345),
        [ts_sym_interface_type] = SHIFT(345),
        [ts_sym_type_name] = SHIFT(345),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(346),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(347),
        [ts_aux_sym_7] = SHIFT(348),
        [ts_aux_sym_map] = SHIFT(349),
        [ts_aux_sym_8] = SHIFT(350),
        [ts_aux_sym_struct] = SHIFT(351),
        [ts_aux_sym_interface] = SHIFT(352),
    },
    [343] = {
        [ts_sym_type_expression] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_pointer_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_map_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_slice_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_struct_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_interface_type] = REDUCE(ts_sym_var_name, 1),
        [ts_sym_type_name] = REDUCE(ts_sym_var_name, 1),
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
    [344] = {
        [ts_sym__line_break] = SHIFT(370),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(370),
        [ts_aux_sym_4] = SHIFT(371),
    },
    [345] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_expression, 1),
    },
    [346] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_4] = REDUCE(ts_sym_type_name, 1),
    },
    [347] = {
        [ts_sym_expression] = SHIFT(368),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [348] = {
        [ts_sym_type_expression] = SHIFT(367),
        [ts_sym_pointer_type] = SHIFT(345),
        [ts_sym_map_type] = SHIFT(345),
        [ts_sym_slice_type] = SHIFT(345),
        [ts_sym_struct_type] = SHIFT(345),
        [ts_sym_interface_type] = SHIFT(345),
        [ts_sym_type_name] = SHIFT(345),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(346),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(348),
        [ts_aux_sym_map] = SHIFT(349),
        [ts_aux_sym_8] = SHIFT(350),
        [ts_aux_sym_struct] = SHIFT(351),
        [ts_aux_sym_interface] = SHIFT(352),
    },
    [349] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(363),
    },
    [350] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(361),
    },
    [351] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(357),
    },
    [352] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(353),
    },
    [353] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(354),
        [ts_aux_sym_6] = SHIFT(355),
    },
    [354] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(356),
    },
    [355] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_interface_type, 3),
    },
    [356] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_interface_type, 4),
    },
    [357] = {
        [ts_sym_var_name] = SHIFT(117),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(118),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(358),
        [ts_aux_sym_6] = SHIFT(359),
    },
    [358] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(360),
    },
    [359] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_struct_type, 3),
    },
    [360] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 4),
        [ts_aux_sym_4] = REDUCE(ts_sym_struct_type, 4),
    },
    [361] = {
        [ts_sym_type_expression] = SHIFT(362),
        [ts_sym_pointer_type] = SHIFT(345),
        [ts_sym_map_type] = SHIFT(345),
        [ts_sym_slice_type] = SHIFT(345),
        [ts_sym_struct_type] = SHIFT(345),
        [ts_sym_interface_type] = SHIFT(345),
        [ts_sym_type_name] = SHIFT(345),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(346),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(348),
        [ts_aux_sym_map] = SHIFT(349),
        [ts_aux_sym_8] = SHIFT(350),
        [ts_aux_sym_struct] = SHIFT(351),
        [ts_aux_sym_interface] = SHIFT(352),
    },
    [362] = {
        [ts_sym__line_break] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_slice_type, 3),
        [ts_aux_sym_4] = REDUCE(ts_sym_slice_type, 3),
    },
    [363] = {
        [ts_sym_type_expression] = SHIFT(364),
        [ts_sym_pointer_type] = SHIFT(142),
        [ts_sym_map_type] = SHIFT(142),
        [ts_sym_slice_type] = SHIFT(142),
        [ts_sym_struct_type] = SHIFT(142),
        [ts_sym_interface_type] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(143),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(144),
        [ts_aux_sym_map] = SHIFT(145),
        [ts_aux_sym_8] = SHIFT(146),
        [ts_aux_sym_struct] = SHIFT(147),
        [ts_aux_sym_interface] = SHIFT(148),
    },
    [364] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(365),
    },
    [365] = {
        [ts_sym_type_expression] = SHIFT(366),
        [ts_sym_pointer_type] = SHIFT(345),
        [ts_sym_map_type] = SHIFT(345),
        [ts_sym_slice_type] = SHIFT(345),
        [ts_sym_struct_type] = SHIFT(345),
        [ts_sym_interface_type] = SHIFT(345),
        [ts_sym_type_name] = SHIFT(345),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(346),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(348),
        [ts_aux_sym_map] = SHIFT(349),
        [ts_aux_sym_8] = SHIFT(350),
        [ts_aux_sym_struct] = SHIFT(351),
        [ts_aux_sym_interface] = SHIFT(352),
    },
    [366] = {
        [ts_sym__line_break] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
        [ts_aux_sym_4] = REDUCE(ts_sym_map_type, 5),
    },
    [367] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
        [ts_aux_sym_4] = REDUCE(ts_sym_pointer_type, 2),
    },
    [368] = {
        [ts_sym__line_break] = SHIFT(369),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(294),
        [ts_aux_sym_3] = SHIFT(369),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = SHIFT(296),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [369] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_statement] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_return_statement] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_range_statement] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_if_statement] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_expression_statement] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_expression] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_call_expression] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_selector_expression] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_math_op] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_bool_op] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_var_name] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_var_declaration, 5),
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
    [370] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_statement] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_return_statement] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_range_statement] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_if_statement] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_expression_statement] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_expression] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_call_expression] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_selector_expression] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_math_op] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_bool_op] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_var_name] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__identifier] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_var_declaration, 4),
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
    [371] = {
        [ts_sym_expression] = SHIFT(372),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [372] = {
        [ts_sym__line_break] = SHIFT(373),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(294),
        [ts_aux_sym_3] = SHIFT(373),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = SHIFT(296),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [373] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_statement] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_return_statement] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_range_statement] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_if_statement] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_expression_statement] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_expression] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_call_expression] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_selector_expression] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_math_op] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_bool_op] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_var_name] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym__identifier] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_number] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_var_declaration, 6),
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
    [374] = {
        [ts_sym__line_break] = REDUCE(ts_sym_block_statement, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_block_statement, 3),
    },
    [375] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = SHIFT(383),
    },
    [376] = {
        [ts_sym_var_name] = SHIFT(380),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(381),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [377] = {
        [ts_sym_expression] = SHIFT(378),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [378] = {
        [ts_sym__line_break] = SHIFT(379),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(294),
        [ts_aux_sym_3] = SHIFT(379),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = SHIFT(296),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [379] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_statement] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_return_statement] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_range_statement] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_if_statement] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_expression_statement] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_expression] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_call_expression] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_selector_expression] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_math_op] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_bool_op] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_var_name] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_declaration_statement, 4),
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
    [380] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = SHIFT(382),
        [ts_aux_sym_10] = SHIFT(376),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 2),
    },
    [381] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_declaration_statement_repeat0] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_10] = REDUCE(ts_sym_var_name, 1),
        [ts_aux_sym_11] = REDUCE(ts_sym_var_name, 1),
    },
    [382] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_11] = REDUCE(ts_aux_sym_declaration_statement_repeat0, 3),
    },
    [383] = {
        [ts_sym_expression] = SHIFT(384),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [384] = {
        [ts_sym__line_break] = SHIFT(385),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(294),
        [ts_aux_sym_3] = SHIFT(385),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = SHIFT(296),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [385] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_statement] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_return_statement] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_range_statement] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_if_statement] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_expression_statement] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_expression] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_call_expression] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_selector_expression] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_math_op] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_bool_op] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_var_name] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym__identifier] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_number] = REDUCE(ts_sym_declaration_statement, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_declaration_statement, 5),
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
    [386] = {
        [ts_sym_var_declaration] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_statement] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_return_statement] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_declaration_statement] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_range_statement] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_if_statement] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_expression_statement] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_expression] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_call_expression] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_selector_expression] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_math_op] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_bool_op] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_var_name] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym__identifier] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_number] = REDUCE(ts_sym_expression_statement, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_block_statement_repeat0] = REDUCE(ts_sym_expression_statement, 2),
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
    [387] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = REDUCE(ts_aux_sym_block_statement_repeat0, 2),
    },
    [388] = {
        [ts_sym_declaration] = REDUCE(ts_sym_func_declaration, 5),
        [ts_sym_type_declaration] = REDUCE(ts_sym_func_declaration, 5),
        [ts_sym_var_declaration] = REDUCE(ts_sym_func_declaration, 5),
        [ts_sym_func_declaration] = REDUCE(ts_sym_func_declaration, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_func_declaration, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_type] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_func_declaration, 5),
        [ts_aux_sym_func] = REDUCE(ts_sym_func_declaration, 5),
    },
    [389] = {
        [ts_sym_type_expression] = SHIFT(390),
        [ts_sym_pointer_type] = SHIFT(345),
        [ts_sym_map_type] = SHIFT(345),
        [ts_sym_slice_type] = SHIFT(345),
        [ts_sym_struct_type] = SHIFT(345),
        [ts_sym_interface_type] = SHIFT(345),
        [ts_sym_type_name] = SHIFT(345),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(346),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_4] = SHIFT(391),
        [ts_aux_sym_7] = SHIFT(348),
        [ts_aux_sym_map] = SHIFT(349),
        [ts_aux_sym_8] = SHIFT(350),
        [ts_aux_sym_struct] = SHIFT(351),
        [ts_aux_sym_interface] = SHIFT(352),
    },
    [390] = {
        [ts_sym__line_break] = SHIFT(394),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(394),
        [ts_aux_sym_4] = SHIFT(395),
    },
    [391] = {
        [ts_sym_expression] = SHIFT(392),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [392] = {
        [ts_sym__line_break] = SHIFT(393),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(294),
        [ts_aux_sym_3] = SHIFT(393),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = SHIFT(296),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [393] = {
        [ts_sym_declaration] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_type_declaration] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_var_declaration] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym_func_declaration] = REDUCE(ts_sym_var_declaration, 5),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 5),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_var_declaration, 5),
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
    [394] = {
        [ts_sym_declaration] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_type_declaration] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_var_declaration] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym_func_declaration] = REDUCE(ts_sym_var_declaration, 4),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_type] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_var_declaration, 4),
        [ts_aux_sym_4] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_func] = REDUCE(ts_sym_var_declaration, 4),
    },
    [395] = {
        [ts_sym_expression] = SHIFT(396),
        [ts_sym_call_expression] = SHIFT(207),
        [ts_sym_selector_expression] = SHIFT(207),
        [ts_sym_math_op] = SHIFT(207),
        [ts_sym_bool_op] = SHIFT(207),
        [ts_sym_var_name] = SHIFT(207),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(207),
        [ts_sym__identifier] = SHIFT(219),
        [ts_sym_number] = SHIFT(207),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_23] = SHIFT(217),
    },
    [396] = {
        [ts_sym__line_break] = SHIFT(397),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_1] = SHIFT(294),
        [ts_aux_sym_3] = SHIFT(397),
        [ts_aux_sym_7] = SHIFT(295),
        [ts_aux_sym_12] = SHIFT(296),
        [ts_aux_sym_13] = SHIFT(295),
        [ts_aux_sym_14] = SHIFT(297),
        [ts_aux_sym_15] = SHIFT(297),
        [ts_aux_sym_16] = SHIFT(298),
        [ts_aux_sym_17] = SHIFT(299),
        [ts_aux_sym_18] = SHIFT(300),
        [ts_aux_sym_19] = SHIFT(300),
        [ts_aux_sym_20] = SHIFT(300),
        [ts_aux_sym_21] = SHIFT(300),
        [ts_aux_sym_22] = SHIFT(300),
    },
    [397] = {
        [ts_sym_declaration] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_type_declaration] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_var_declaration] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym_func_declaration] = REDUCE(ts_sym_var_declaration, 6),
        [ts_builtin_sym_end] = REDUCE(ts_sym_var_declaration, 6),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_var_declaration, 6),
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
    [398] = {
        [ts_sym_type_expression] = SHIFT(400),
        [ts_sym_pointer_type] = SHIFT(401),
        [ts_sym_map_type] = SHIFT(401),
        [ts_sym_slice_type] = SHIFT(401),
        [ts_sym_struct_type] = SHIFT(401),
        [ts_sym_interface_type] = SHIFT(401),
        [ts_sym_type_name] = SHIFT(401),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(402),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(403),
        [ts_aux_sym_map] = SHIFT(404),
        [ts_aux_sym_8] = SHIFT(405),
        [ts_aux_sym_struct] = SHIFT(406),
        [ts_aux_sym_interface] = SHIFT(407),
    },
    [399] = {
        [ts_sym_type_expression] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_pointer_type] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_map_type] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_slice_type] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_struct_type] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_interface_type] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_type_name] = REDUCE(ts_sym_type_name, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_map] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_8] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_struct] = REDUCE(ts_sym_type_name, 1),
        [ts_aux_sym_interface] = REDUCE(ts_sym_type_name, 1),
    },
    [400] = {
        [ts_sym__line_break] = SHIFT(423),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = SHIFT(423),
    },
    [401] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_expression, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_expression, 1),
    },
    [402] = {
        [ts_sym__line_break] = REDUCE(ts_sym_type_name, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_type_name, 1),
    },
    [403] = {
        [ts_sym_type_expression] = SHIFT(422),
        [ts_sym_pointer_type] = SHIFT(401),
        [ts_sym_map_type] = SHIFT(401),
        [ts_sym_slice_type] = SHIFT(401),
        [ts_sym_struct_type] = SHIFT(401),
        [ts_sym_interface_type] = SHIFT(401),
        [ts_sym_type_name] = SHIFT(401),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(402),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(403),
        [ts_aux_sym_map] = SHIFT(404),
        [ts_aux_sym_8] = SHIFT(405),
        [ts_aux_sym_struct] = SHIFT(406),
        [ts_aux_sym_interface] = SHIFT(407),
    },
    [404] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_8] = SHIFT(418),
    },
    [405] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(416),
    },
    [406] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(412),
    },
    [407] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_5] = SHIFT(408),
    },
    [408] = {
        [ts_sym_var_name] = SHIFT(57),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(16),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_interface_type_repeat0] = SHIFT(409),
        [ts_aux_sym_6] = SHIFT(410),
    },
    [409] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(411),
    },
    [410] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 3),
    },
    [411] = {
        [ts_sym__line_break] = REDUCE(ts_sym_interface_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_interface_type, 4),
    },
    [412] = {
        [ts_sym_var_name] = SHIFT(117),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(118),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_struct_type_repeat0] = SHIFT(413),
        [ts_aux_sym_6] = SHIFT(414),
    },
    [413] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_6] = SHIFT(415),
    },
    [414] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 3),
    },
    [415] = {
        [ts_sym__line_break] = REDUCE(ts_sym_struct_type, 4),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_struct_type, 4),
    },
    [416] = {
        [ts_sym_type_expression] = SHIFT(417),
        [ts_sym_pointer_type] = SHIFT(401),
        [ts_sym_map_type] = SHIFT(401),
        [ts_sym_slice_type] = SHIFT(401),
        [ts_sym_struct_type] = SHIFT(401),
        [ts_sym_interface_type] = SHIFT(401),
        [ts_sym_type_name] = SHIFT(401),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(402),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(403),
        [ts_aux_sym_map] = SHIFT(404),
        [ts_aux_sym_8] = SHIFT(405),
        [ts_aux_sym_struct] = SHIFT(406),
        [ts_aux_sym_interface] = SHIFT(407),
    },
    [417] = {
        [ts_sym__line_break] = REDUCE(ts_sym_slice_type, 3),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_slice_type, 3),
    },
    [418] = {
        [ts_sym_type_expression] = SHIFT(419),
        [ts_sym_pointer_type] = SHIFT(142),
        [ts_sym_map_type] = SHIFT(142),
        [ts_sym_slice_type] = SHIFT(142),
        [ts_sym_struct_type] = SHIFT(142),
        [ts_sym_interface_type] = SHIFT(142),
        [ts_sym_type_name] = SHIFT(142),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(143),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(144),
        [ts_aux_sym_map] = SHIFT(145),
        [ts_aux_sym_8] = SHIFT(146),
        [ts_aux_sym_struct] = SHIFT(147),
        [ts_aux_sym_interface] = SHIFT(148),
    },
    [419] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_9] = SHIFT(420),
    },
    [420] = {
        [ts_sym_type_expression] = SHIFT(421),
        [ts_sym_pointer_type] = SHIFT(401),
        [ts_sym_map_type] = SHIFT(401),
        [ts_sym_slice_type] = SHIFT(401),
        [ts_sym_struct_type] = SHIFT(401),
        [ts_sym_interface_type] = SHIFT(401),
        [ts_sym_type_name] = SHIFT(401),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym__identifier] = SHIFT(402),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_7] = SHIFT(403),
        [ts_aux_sym_map] = SHIFT(404),
        [ts_aux_sym_8] = SHIFT(405),
        [ts_aux_sym_struct] = SHIFT(406),
        [ts_aux_sym_interface] = SHIFT(407),
    },
    [421] = {
        [ts_sym__line_break] = REDUCE(ts_sym_map_type, 5),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_map_type, 5),
    },
    [422] = {
        [ts_sym__line_break] = REDUCE(ts_sym_pointer_type, 2),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_3] = REDUCE(ts_sym_pointer_type, 2),
    },
    [423] = {
        [ts_sym_declaration] = REDUCE(ts_sym_type_declaration, 4),
        [ts_sym_type_declaration] = REDUCE(ts_sym_type_declaration, 4),
        [ts_sym_var_declaration] = REDUCE(ts_sym_type_declaration, 4),
        [ts_sym_func_declaration] = REDUCE(ts_sym_type_declaration, 4),
        [ts_builtin_sym_end] = REDUCE(ts_sym_type_declaration, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_type] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_3] = REDUCE_EXTRA(ts_sym__line_break),
        [ts_aux_sym_var] = REDUCE(ts_sym_type_declaration, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_type_declaration, 4),
    },
    [424] = {
        [ts_sym_imports_block] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym_declaration] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym_type_declaration] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym_var_declaration] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym_func_declaration] = REDUCE(ts_sym_imports_block, 2),
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 2),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 2),
    },
    [425] = {
        [ts_sym_imports_block] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_declaration] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_type_declaration] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_var_declaration] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_func_declaration] = REDUCE(ts_sym_package_import, 1),
        [ts_builtin_sym_end] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_import] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_type] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_var] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_func] = REDUCE(ts_sym_package_import, 1),
    },
    [426] = {
        [ts_sym_package_import] = SHIFT(427),
        [ts_builtin_sym_error] = SHIFT(428),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(429),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(428),
        [ts_aux_sym_2] = SHIFT(430),
    },
    [427] = {
        [ts_sym_package_import] = SHIFT(427),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = SHIFT(429),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = SHIFT(432),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 1),
    },
    [428] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = SHIFT(431),
    },
    [429] = {
        [ts_sym_package_import] = REDUCE(ts_sym_package_import, 1),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_string] = REDUCE(ts_sym_package_import, 1),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_imports_block_repeat0] = REDUCE(ts_sym_package_import, 1),
        [ts_aux_sym_2] = REDUCE(ts_sym_package_import, 1),
    },
    [430] = {
        [ts_sym_imports_block] = REDUCE(ts_sym_imports_block, 3),
        [ts_sym_declaration] = REDUCE(ts_sym_imports_block, 3),
        [ts_sym_type_declaration] = REDUCE(ts_sym_imports_block, 3),
        [ts_sym_var_declaration] = REDUCE(ts_sym_imports_block, 3),
        [ts_sym_func_declaration] = REDUCE(ts_sym_imports_block, 3),
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = REDUCE(ts_sym_imports_block, 3),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_imports_block, 3),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 3),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 3),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 3),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 3),
    },
    [431] = {
        [ts_sym_imports_block] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym_declaration] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym_type_declaration] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym_var_declaration] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym_func_declaration] = REDUCE(ts_sym_imports_block, 4),
        [ts_builtin_sym_end] = REDUCE(ts_sym_imports_block, 4),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat0] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_import] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_type] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_var] = REDUCE(ts_sym_imports_block, 4),
        [ts_aux_sym_func] = REDUCE(ts_sym_imports_block, 4),
    },
    [432] = {
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_2] = REDUCE(ts_aux_sym_imports_block_repeat0, 2),
    },
    [433] = {
        [ts_builtin_sym_end] = REDUCE(ts_sym_program, 3),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [434] = {
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat1, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
    },
    [435] = {
        [ts_sym_declaration] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym_type_declaration] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym_var_declaration] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym_func_declaration] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_builtin_sym_end] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_sym__line_break] = SHIFT_EXTRA(),
        [ts_sym_comment] = SHIFT_EXTRA(),
        [ts_aux_sym_program_repeat1] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_type] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_var] = REDUCE(ts_aux_sym_program_repeat0, 2),
        [ts_aux_sym_func] = REDUCE(ts_aux_sym_program_repeat0, 2),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_golang);
