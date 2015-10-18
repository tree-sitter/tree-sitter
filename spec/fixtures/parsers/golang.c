#include "tree_sitter/parser.h"

#define STATE_COUNT 430
#define SYMBOL_COUNT 84

enum {
    sym_program = ts_builtin_sym_start,
    sym_package_directive,
    sym_imports_block,
    sym_package_import,
    sym__declaration,
    sym_type_declaration,
    sym_var_declaration,
    sym_func_declaration,
    sym_block_statement,
    sym__type_expression,
    sym_pointer_type,
    sym_map_type,
    sym_slice_type,
    sym_struct_type,
    sym_interface_type,
    sym__statement,
    sym_return_statement,
    sym_short_var_declaration,
    sym_range_statement,
    sym_if_statement,
    sym_expression_statement,
    sym__expression,
    sym_call_expression,
    sym_selector_expression,
    sym_math_op,
    sym_bool_op,
    sym__func_signature,
    sym_package_name,
    sym_var_name,
    sym_type_name,
    aux_sym_program_repeat1,
    aux_sym_program_repeat2,
    aux_sym_imports_block_repeat1,
    aux_sym_block_statement_repeat1,
    aux_sym_struct_type_repeat1,
    aux_sym_interface_type_repeat1,
    aux_sym_return_statement_repeat1,
    aux_sym_short_var_declaration_repeat1,
    aux_sym__func_signature_repeat1,
    aux_sym__func_signature_repeat2,
    aux_sym__func_signature_repeat3,
    anon_sym_package,
    anon_sym_import,
    anon_sym_LPAREN,
    anon_sym_RPAREN,
    anon_sym_type,
    anon_sym_SEMI,
    anon_sym_var,
    anon_sym_EQ,
    anon_sym_func,
    anon_sym_LBRACE,
    anon_sym_RBRACE,
    anon_sym_STAR,
    anon_sym_map,
    anon_sym_LBRACK,
    anon_sym_RBRACK,
    anon_sym_struct,
    anon_sym_interface,
    anon_sym_return,
    anon_sym_COMMA,
    anon_sym_COLON_EQ,
    anon_sym_for,
    anon_sym_range,
    anon_sym_if,
    anon_sym_else,
    anon_sym_DOT,
    anon_sym_SLASH,
    anon_sym_PLUS,
    anon_sym_DASH,
    anon_sym_PIPE_PIPE,
    anon_sym_AMP_AMP,
    anon_sym_EQ_EQ,
    anon_sym_LT_EQ,
    anon_sym_LT,
    anon_sym_GT_EQ,
    anon_sym_GT,
    anon_sym_BANG,
    sym__line_break,
    sym_string,
    sym__identifier,
    sym_number,
    sym_comment,
};

static const char *ts_symbol_names[] = {
    [sym_program] = "program",
    [sym_package_directive] = "package_directive",
    [sym_imports_block] = "imports_block",
    [sym_package_import] = "package_import",
    [sym__declaration] = "_declaration",
    [sym_type_declaration] = "type_declaration",
    [sym_var_declaration] = "var_declaration",
    [sym_func_declaration] = "func_declaration",
    [sym_block_statement] = "block_statement",
    [sym__type_expression] = "_type_expression",
    [sym_pointer_type] = "pointer_type",
    [sym_map_type] = "map_type",
    [sym_slice_type] = "slice_type",
    [sym_struct_type] = "struct_type",
    [sym_interface_type] = "interface_type",
    [sym__statement] = "_statement",
    [sym_return_statement] = "return_statement",
    [sym_short_var_declaration] = "short_var_declaration",
    [sym_range_statement] = "range_statement",
    [sym_if_statement] = "if_statement",
    [sym_expression_statement] = "expression_statement",
    [sym__expression] = "_expression",
    [sym_call_expression] = "call_expression",
    [sym_selector_expression] = "selector_expression",
    [sym_math_op] = "math_op",
    [sym_bool_op] = "bool_op",
    [sym__func_signature] = "_func_signature",
    [sym_package_name] = "package_name",
    [sym_var_name] = "var_name",
    [sym_type_name] = "type_name",
    [aux_sym_program_repeat1] = "program_repeat1",
    [aux_sym_program_repeat2] = "program_repeat2",
    [aux_sym_imports_block_repeat1] = "imports_block_repeat1",
    [aux_sym_block_statement_repeat1] = "block_statement_repeat1",
    [aux_sym_struct_type_repeat1] = "struct_type_repeat1",
    [aux_sym_interface_type_repeat1] = "interface_type_repeat1",
    [aux_sym_return_statement_repeat1] = "return_statement_repeat1",
    [aux_sym_short_var_declaration_repeat1] = "short_var_declaration_repeat1",
    [aux_sym__func_signature_repeat1] = "_func_signature_repeat1",
    [aux_sym__func_signature_repeat2] = "_func_signature_repeat2",
    [aux_sym__func_signature_repeat3] = "_func_signature_repeat3",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
    [anon_sym_package] = "package",
    [anon_sym_import] = "import",
    [anon_sym_LPAREN] = "(",
    [anon_sym_RPAREN] = ")",
    [anon_sym_type] = "type",
    [anon_sym_SEMI] = ";",
    [anon_sym_var] = "var",
    [anon_sym_EQ] = "=",
    [anon_sym_func] = "func",
    [anon_sym_LBRACE] = "{",
    [anon_sym_RBRACE] = "}",
    [anon_sym_STAR] = "*",
    [anon_sym_map] = "map",
    [anon_sym_LBRACK] = "[",
    [anon_sym_RBRACK] = "]",
    [anon_sym_struct] = "struct",
    [anon_sym_interface] = "interface",
    [anon_sym_return] = "return",
    [anon_sym_COMMA] = ",",
    [anon_sym_COLON_EQ] = ":=",
    [anon_sym_for] = "for",
    [anon_sym_range] = "range",
    [anon_sym_if] = "if",
    [anon_sym_else] = "else",
    [anon_sym_DOT] = ".",
    [anon_sym_SLASH] = "/",
    [anon_sym_PLUS] = "+",
    [anon_sym_DASH] = "-",
    [anon_sym_PIPE_PIPE] = "||",
    [anon_sym_AMP_AMP] = "&&",
    [anon_sym_EQ_EQ] = "==",
    [anon_sym_LT_EQ] = "<=",
    [anon_sym_LT] = "<",
    [anon_sym_GT_EQ] = ">=",
    [anon_sym_GT] = ">",
    [anon_sym_BANG] = "!",
    [sym__line_break] = "_line_break",
    [sym_string] = "string",
    [sym__identifier] = "_identifier",
    [sym_number] = "number",
    [sym_comment] = "comment",
};

static const TSNodeType ts_node_types[SYMBOL_COUNT] = {
    [sym_program] = TSNodeTypeNamed,
    [sym_package_directive] = TSNodeTypeNamed,
    [sym_imports_block] = TSNodeTypeNamed,
    [sym_package_import] = TSNodeTypeNamed,
    [sym__declaration] = TSNodeTypeHidden,
    [sym_type_declaration] = TSNodeTypeNamed,
    [sym_var_declaration] = TSNodeTypeNamed,
    [sym_func_declaration] = TSNodeTypeNamed,
    [sym_block_statement] = TSNodeTypeNamed,
    [sym__type_expression] = TSNodeTypeHidden,
    [sym_pointer_type] = TSNodeTypeNamed,
    [sym_map_type] = TSNodeTypeNamed,
    [sym_slice_type] = TSNodeTypeNamed,
    [sym_struct_type] = TSNodeTypeNamed,
    [sym_interface_type] = TSNodeTypeNamed,
    [sym__statement] = TSNodeTypeHidden,
    [sym_return_statement] = TSNodeTypeNamed,
    [sym_short_var_declaration] = TSNodeTypeNamed,
    [sym_range_statement] = TSNodeTypeNamed,
    [sym_if_statement] = TSNodeTypeNamed,
    [sym_expression_statement] = TSNodeTypeNamed,
    [sym__expression] = TSNodeTypeHidden,
    [sym_call_expression] = TSNodeTypeNamed,
    [sym_selector_expression] = TSNodeTypeNamed,
    [sym_math_op] = TSNodeTypeNamed,
    [sym_bool_op] = TSNodeTypeNamed,
    [sym__func_signature] = TSNodeTypeHidden,
    [sym_package_name] = TSNodeTypeNamed,
    [sym_var_name] = TSNodeTypeNamed,
    [sym_type_name] = TSNodeTypeNamed,
    [aux_sym_program_repeat1] = TSNodeTypeHidden,
    [aux_sym_program_repeat2] = TSNodeTypeHidden,
    [aux_sym_imports_block_repeat1] = TSNodeTypeHidden,
    [aux_sym_block_statement_repeat1] = TSNodeTypeHidden,
    [aux_sym_struct_type_repeat1] = TSNodeTypeHidden,
    [aux_sym_interface_type_repeat1] = TSNodeTypeHidden,
    [aux_sym_return_statement_repeat1] = TSNodeTypeHidden,
    [aux_sym_short_var_declaration_repeat1] = TSNodeTypeHidden,
    [aux_sym__func_signature_repeat1] = TSNodeTypeHidden,
    [aux_sym__func_signature_repeat2] = TSNodeTypeHidden,
    [aux_sym__func_signature_repeat3] = TSNodeTypeHidden,
    [ts_builtin_sym_error] = TSNodeTypeNamed,
    [ts_builtin_sym_end] = TSNodeTypeHidden,
    [anon_sym_package] = TSNodeTypeAnonymous,
    [anon_sym_import] = TSNodeTypeAnonymous,
    [anon_sym_LPAREN] = TSNodeTypeAnonymous,
    [anon_sym_RPAREN] = TSNodeTypeAnonymous,
    [anon_sym_type] = TSNodeTypeAnonymous,
    [anon_sym_SEMI] = TSNodeTypeAnonymous,
    [anon_sym_var] = TSNodeTypeAnonymous,
    [anon_sym_EQ] = TSNodeTypeAnonymous,
    [anon_sym_func] = TSNodeTypeAnonymous,
    [anon_sym_LBRACE] = TSNodeTypeAnonymous,
    [anon_sym_RBRACE] = TSNodeTypeAnonymous,
    [anon_sym_STAR] = TSNodeTypeAnonymous,
    [anon_sym_map] = TSNodeTypeAnonymous,
    [anon_sym_LBRACK] = TSNodeTypeAnonymous,
    [anon_sym_RBRACK] = TSNodeTypeAnonymous,
    [anon_sym_struct] = TSNodeTypeAnonymous,
    [anon_sym_interface] = TSNodeTypeAnonymous,
    [anon_sym_return] = TSNodeTypeAnonymous,
    [anon_sym_COMMA] = TSNodeTypeAnonymous,
    [anon_sym_COLON_EQ] = TSNodeTypeAnonymous,
    [anon_sym_for] = TSNodeTypeAnonymous,
    [anon_sym_range] = TSNodeTypeAnonymous,
    [anon_sym_if] = TSNodeTypeAnonymous,
    [anon_sym_else] = TSNodeTypeAnonymous,
    [anon_sym_DOT] = TSNodeTypeAnonymous,
    [anon_sym_SLASH] = TSNodeTypeAnonymous,
    [anon_sym_PLUS] = TSNodeTypeAnonymous,
    [anon_sym_DASH] = TSNodeTypeAnonymous,
    [anon_sym_PIPE_PIPE] = TSNodeTypeAnonymous,
    [anon_sym_AMP_AMP] = TSNodeTypeAnonymous,
    [anon_sym_EQ_EQ] = TSNodeTypeAnonymous,
    [anon_sym_LT_EQ] = TSNodeTypeAnonymous,
    [anon_sym_LT] = TSNodeTypeAnonymous,
    [anon_sym_GT_EQ] = TSNodeTypeAnonymous,
    [anon_sym_GT] = TSNodeTypeAnonymous,
    [anon_sym_BANG] = TSNodeTypeAnonymous,
    [sym__line_break] = TSNodeTypeHidden,
    [sym_string] = TSNodeTypeNamed,
    [sym__identifier] = TSNodeTypeHidden,
    [sym_number] = TSNodeTypeNamed,
    [sym_comment] = TSNodeTypeNamed,
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
            ACCEPT_TOKEN(sym__line_break);
        case 3:
            if (lookahead == '/')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(4);
            ACCEPT_TOKEN(sym_comment);
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
            ACCEPT_TOKEN(anon_sym_package);
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
            ACCEPT_TOKEN(anon_sym_func);
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
            ACCEPT_TOKEN(anon_sym_import);
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
            ACCEPT_TOKEN(anon_sym_type);
        case 29:
            if (lookahead == 'a')
                ADVANCE(30);
            LEX_ERROR();
        case 30:
            if (lookahead == 'r')
                ADVANCE(31);
            LEX_ERROR();
        case 31:
            ACCEPT_TOKEN(anon_sym_var);
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
            ACCEPT_TOKEN(sym__identifier);
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
            ACCEPT_TOKEN(sym_string);
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
            ACCEPT_TOKEN(sym_string);
        case 40:
            ACCEPT_TOKEN(anon_sym_LPAREN);
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
            ACCEPT_TOKEN(anon_sym_LBRACE);
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
            ACCEPT_TOKEN(anon_sym_RPAREN);
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
            ACCEPT_TOKEN(anon_sym_STAR);
        case 48:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 49:
            ACCEPT_TOKEN(anon_sym_LBRACK);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(51);
            ACCEPT_TOKEN(sym__identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(52);
            ACCEPT_TOKEN(sym__identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(53);
            ACCEPT_TOKEN(sym__identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(54);
            ACCEPT_TOKEN(sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(55);
            ACCEPT_TOKEN(sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(56);
            ACCEPT_TOKEN(sym__identifier);
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
            ACCEPT_TOKEN(sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(58);
            ACCEPT_TOKEN(sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_interface);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(60);
            ACCEPT_TOKEN(sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(61);
            ACCEPT_TOKEN(sym__identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_map);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(63);
            ACCEPT_TOKEN(sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(64);
            ACCEPT_TOKEN(sym__identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(65);
            ACCEPT_TOKEN(sym__identifier);
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
            ACCEPT_TOKEN(sym__identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(67);
            ACCEPT_TOKEN(sym__identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_struct);
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
            ACCEPT_TOKEN(anon_sym_RBRACK);
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
            ACCEPT_TOKEN(anon_sym_RBRACE);
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
            ACCEPT_TOKEN(anon_sym_SEMI);
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
            ACCEPT_TOKEN(anon_sym_BANG);
        case 84:
            if (lookahead == '.')
                ADVANCE(85);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(84);
            ACCEPT_TOKEN(sym_number);
        case 85:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            LEX_ERROR();
        case 86:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(86);
            ACCEPT_TOKEN(sym_number);
        case 87:
            if (lookahead == '=')
                ADVANCE(88);
            LEX_ERROR();
        case 88:
            ACCEPT_TOKEN(anon_sym_COLON_EQ);
        case 89:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(90);
            ACCEPT_TOKEN(sym__identifier);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(91);
            ACCEPT_TOKEN(sym__identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_for);
        case 92:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(93);
            ACCEPT_TOKEN(sym__identifier);
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_if);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(95);
            ACCEPT_TOKEN(sym__identifier);
        case 95:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(96);
            ACCEPT_TOKEN(sym__identifier);
        case 96:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(97);
            ACCEPT_TOKEN(sym__identifier);
        case 97:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(98);
            ACCEPT_TOKEN(sym__identifier);
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(99);
            ACCEPT_TOKEN(sym__identifier);
        case 99:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_return);
        case 100:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(101);
            ACCEPT_TOKEN(sym__identifier);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(102);
            ACCEPT_TOKEN(sym__identifier);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_var);
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
            ACCEPT_TOKEN(anon_sym_AMP_AMP);
        case 106:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 107:
            ACCEPT_TOKEN(anon_sym_DASH);
        case 108:
            ACCEPT_TOKEN(anon_sym_DOT);
        case 109:
            if (lookahead == '/')
                ADVANCE(4);
            ACCEPT_TOKEN(anon_sym_SLASH);
        case 110:
            if (lookahead == '=')
                ADVANCE(111);
            ACCEPT_TOKEN(anon_sym_LT);
        case 111:
            ACCEPT_TOKEN(anon_sym_LT_EQ);
        case 112:
            if (lookahead == '=')
                ADVANCE(113);
            LEX_ERROR();
        case 113:
            ACCEPT_TOKEN(anon_sym_EQ_EQ);
        case 114:
            if (lookahead == '=')
                ADVANCE(115);
            ACCEPT_TOKEN(anon_sym_GT);
        case 115:
            ACCEPT_TOKEN(anon_sym_GT_EQ);
        case 116:
            if (lookahead == '|')
                ADVANCE(117);
            LEX_ERROR();
        case 117:
            ACCEPT_TOKEN(anon_sym_PIPE_PIPE);
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
            ACCEPT_TOKEN(sym__identifier);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(125);
            ACCEPT_TOKEN(sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(126);
            ACCEPT_TOKEN(sym__identifier);
        case 126:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_else);
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
            ACCEPT_TOKEN(anon_sym_if);
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
            ACCEPT_TOKEN(anon_sym_range);
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
            ACCEPT_TOKEN(anon_sym_EQ);
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
            ACCEPT_TOKEN(anon_sym_EQ);
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
            ACCEPT_TOKEN(sym__identifier);
        case 155:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(156);
            ACCEPT_TOKEN(sym__identifier);
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
            ACCEPT_TOKEN(sym__identifier);
        case 157:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_func);
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
            ACCEPT_TOKEN(sym__identifier);
        case 159:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(160);
            ACCEPT_TOKEN(sym__identifier);
        case 160:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(161);
            ACCEPT_TOKEN(sym__identifier);
        case 161:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(162);
            ACCEPT_TOKEN(sym__identifier);
        case 162:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(163);
            ACCEPT_TOKEN(sym__identifier);
        case 163:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_import);
        case 164:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(165);
            ACCEPT_TOKEN(sym__identifier);
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
            ACCEPT_TOKEN(sym__identifier);
        case 166:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'k')
                ADVANCE(167);
            ACCEPT_TOKEN(sym__identifier);
        case 167:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(168);
            ACCEPT_TOKEN(sym__identifier);
        case 168:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(169);
            ACCEPT_TOKEN(sym__identifier);
        case 169:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(170);
            ACCEPT_TOKEN(sym__identifier);
        case 170:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_package);
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
            ACCEPT_TOKEN(sym__identifier);
        case 172:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(173);
            ACCEPT_TOKEN(sym__identifier);
        case 173:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(174);
            ACCEPT_TOKEN(sym__identifier);
        case 174:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(175);
            ACCEPT_TOKEN(sym__identifier);
        case 175:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_range);
        case 176:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(33);
            if (lookahead == 'y')
                ADVANCE(177);
            ACCEPT_TOKEN(sym__identifier);
        case 177:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(178);
            ACCEPT_TOKEN(sym__identifier);
        case 178:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(179);
            ACCEPT_TOKEN(sym__identifier);
        case 179:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(anon_sym_type);
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
    [20] = 68,
    [21] = 46,
    [22] = 42,
    [23] = 32,
    [24] = 42,
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
    [46] = 72,
    [47] = 72,
    [48] = 73,
    [49] = 74,
    [50] = 42,
    [51] = 42,
    [52] = 32,
    [53] = 69,
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
    [66] = 32,
    [67] = 32,
    [68] = 69,
    [69] = 71,
    [70] = 76,
    [71] = 76,
    [72] = 69,
    [73] = 71,
    [74] = 76,
    [75] = 69,
    [76] = 72,
    [77] = 69,
    [78] = 71,
    [79] = 79,
    [80] = 32,
    [81] = 46,
    [82] = 69,
    [83] = 72,
    [84] = 69,
    [85] = 71,
    [86] = 71,
    [87] = 32,
    [88] = 32,
    [89] = 69,
    [90] = 71,
    [91] = 76,
    [92] = 76,
    [93] = 69,
    [94] = 71,
    [95] = 76,
    [96] = 79,
    [97] = 32,
    [98] = 32,
    [99] = 69,
    [100] = 69,
    [101] = 71,
    [102] = 76,
    [103] = 71,
    [104] = 79,
    [105] = 32,
    [106] = 32,
    [107] = 69,
    [108] = 71,
    [109] = 69,
    [110] = 78,
    [111] = 76,
    [112] = 72,
    [113] = 78,
    [114] = 69,
    [115] = 72,
    [116] = 69,
    [117] = 76,
    [118] = 76,
    [119] = 72,
    [120] = 73,
    [121] = 74,
    [122] = 42,
    [123] = 42,
    [124] = 76,
    [125] = 76,
    [126] = 78,
    [127] = 76,
    [128] = 76,
    [129] = 76,
    [130] = 78,
    [131] = 76,
    [132] = 76,
    [133] = 72,
    [134] = 76,
    [135] = 72,
    [136] = 74,
    [137] = 74,
    [138] = 72,
    [139] = 73,
    [140] = 74,
    [141] = 42,
    [142] = 42,
    [143] = 74,
    [144] = 76,
    [145] = 78,
    [146] = 74,
    [147] = 74,
    [148] = 76,
    [149] = 78,
    [150] = 74,
    [151] = 74,
    [152] = 72,
    [153] = 74,
    [154] = 72,
    [155] = 74,
    [156] = 72,
    [157] = 74,
    [158] = 74,
    [159] = 72,
    [160] = 76,
    [161] = 76,
    [162] = 78,
    [163] = 72,
    [164] = 69,
    [165] = 72,
    [166] = 74,
    [167] = 72,
    [168] = 69,
    [169] = 69,
    [170] = 69,
    [171] = 71,
    [172] = 68,
    [173] = 32,
    [174] = 32,
    [175] = 69,
    [176] = 71,
    [177] = 42,
    [178] = 42,
    [179] = 69,
    [180] = 71,
    [181] = 42,
    [182] = 68,
    [183] = 32,
    [184] = 32,
    [185] = 69,
    [186] = 69,
    [187] = 71,
    [188] = 42,
    [189] = 71,
    [190] = 68,
    [191] = 32,
    [192] = 32,
    [193] = 69,
    [194] = 71,
    [195] = 69,
    [196] = 80,
    [197] = 82,
    [198] = 82,
    [199] = 82,
    [200] = 103,
    [201] = 103,
    [202] = 118,
    [203] = 78,
    [204] = 32,
    [205] = 80,
    [206] = 119,
    [207] = 120,
    [208] = 32,
    [209] = 120,
    [210] = 120,
    [211] = 118,
    [212] = 103,
    [213] = 103,
    [214] = 121,
    [215] = 121,
    [216] = 120,
    [217] = 121,
    [218] = 121,
    [219] = 122,
    [220] = 127,
    [221] = 82,
    [222] = 120,
    [223] = 32,
    [224] = 120,
    [225] = 120,
    [226] = 120,
    [227] = 120,
    [228] = 121,
    [229] = 121,
    [230] = 121,
    [231] = 121,
    [232] = 121,
    [233] = 121,
    [234] = 78,
    [235] = 122,
    [236] = 122,
    [237] = 128,
    [238] = 128,
    [239] = 121,
    [240] = 120,
    [241] = 128,
    [242] = 128,
    [243] = 71,
    [244] = 127,
    [245] = 121,
    [246] = 120,
    [247] = 120,
    [248] = 32,
    [249] = 120,
    [250] = 120,
    [251] = 120,
    [252] = 120,
    [253] = 128,
    [254] = 128,
    [255] = 128,
    [256] = 128,
    [257] = 128,
    [258] = 128,
    [259] = 71,
    [260] = 128,
    [261] = 128,
    [262] = 128,
    [263] = 71,
    [264] = 128,
    [265] = 128,
    [266] = 121,
    [267] = 129,
    [268] = 82,
    [269] = 82,
    [270] = 78,
    [271] = 82,
    [272] = 82,
    [273] = 132,
    [274] = 132,
    [275] = 32,
    [276] = 133,
    [277] = 120,
    [278] = 121,
    [279] = 82,
    [280] = 139,
    [281] = 139,
    [282] = 133,
    [283] = 120,
    [284] = 121,
    [285] = 82,
    [286] = 103,
    [287] = 127,
    [288] = 140,
    [289] = 120,
    [290] = 32,
    [291] = 120,
    [292] = 120,
    [293] = 120,
    [294] = 120,
    [295] = 103,
    [296] = 103,
    [297] = 103,
    [298] = 103,
    [299] = 103,
    [300] = 103,
    [301] = 128,
    [302] = 103,
    [303] = 71,
    [304] = 103,
    [305] = 103,
    [306] = 141,
    [307] = 141,
    [308] = 142,
    [309] = 120,
    [310] = 141,
    [311] = 141,
    [312] = 80,
    [313] = 127,
    [314] = 143,
    [315] = 120,
    [316] = 120,
    [317] = 32,
    [318] = 120,
    [319] = 120,
    [320] = 120,
    [321] = 120,
    [322] = 141,
    [323] = 141,
    [324] = 141,
    [325] = 141,
    [326] = 141,
    [327] = 141,
    [328] = 80,
    [329] = 141,
    [330] = 128,
    [331] = 141,
    [332] = 71,
    [333] = 141,
    [334] = 141,
    [335] = 142,
    [336] = 144,
    [337] = 144,
    [338] = 146,
    [339] = 146,
    [340] = 120,
    [341] = 72,
    [342] = 73,
    [343] = 74,
    [344] = 42,
    [345] = 42,
    [346] = 146,
    [347] = 76,
    [348] = 78,
    [349] = 146,
    [350] = 146,
    [351] = 76,
    [352] = 78,
    [353] = 146,
    [354] = 146,
    [355] = 72,
    [356] = 146,
    [357] = 72,
    [358] = 74,
    [359] = 72,
    [360] = 146,
    [361] = 146,
    [362] = 103,
    [363] = 140,
    [364] = 147,
    [365] = 120,
    [366] = 103,
    [367] = 140,
    [368] = 80,
    [369] = 139,
    [370] = 32,
    [371] = 120,
    [372] = 103,
    [373] = 140,
    [374] = 132,
    [375] = 132,
    [376] = 139,
    [377] = 120,
    [378] = 103,
    [379] = 140,
    [380] = 140,
    [381] = 78,
    [382] = 148,
    [383] = 144,
    [384] = 146,
    [385] = 120,
    [386] = 103,
    [387] = 149,
    [388] = 150,
    [389] = 120,
    [390] = 103,
    [391] = 149,
    [392] = 72,
    [393] = 72,
    [394] = 80,
    [395] = 80,
    [396] = 72,
    [397] = 73,
    [398] = 74,
    [399] = 42,
    [400] = 42,
    [401] = 80,
    [402] = 76,
    [403] = 78,
    [404] = 80,
    [405] = 80,
    [406] = 76,
    [407] = 78,
    [408] = 80,
    [409] = 80,
    [410] = 72,
    [411] = 80,
    [412] = 72,
    [413] = 74,
    [414] = 72,
    [415] = 80,
    [416] = 80,
    [417] = 148,
    [418] = 14,
    [419] = 151,
    [420] = 14,
    [421] = 151,
    [422] = 71,
    [423] = 14,
    [424] = 151,
    [425] = 14,
    [426] = 71,
    [427] = 12,
    [428] = 12,
    [429] = 34,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction *ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = ACTIONS(SHIFT(1)),
        [sym_package_directive] = ACTIONS(SHIFT(2)),
        [anon_sym_package] = ACTIONS(SHIFT(3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [1] = {
        [ts_builtin_sym_end] = ACTIONS(ACCEPT_INPUT()),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [2] = {
        [sym_imports_block] = ACTIONS(SHIFT(6)),
        [sym__declaration] = ACTIONS(SHIFT(7)),
        [sym_type_declaration] = ACTIONS(SHIFT(8)),
        [sym_var_declaration] = ACTIONS(SHIFT(8)),
        [sym_func_declaration] = ACTIONS(SHIFT(8)),
        [aux_sym_program_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_program_repeat2] = ACTIONS(SHIFT(10)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 1)),
        [anon_sym_import] = ACTIONS(SHIFT(11)),
        [anon_sym_type] = ACTIONS(SHIFT(12)),
        [anon_sym_var] = ACTIONS(SHIFT(13)),
        [anon_sym_func] = ACTIONS(SHIFT(14)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [3] = {
        [sym_package_name] = ACTIONS(SHIFT(4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [4] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [sym__declaration] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [anon_sym_import] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [5] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym__declaration] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_package_name, 1)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_package_name, 1)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_package_name, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_package_name, 1)),
        [anon_sym_import] = ACTIONS(REDUCE(sym_package_name, 1)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_package_name, 1)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_package_name, 1)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [sym_imports_block] = ACTIONS(SHIFT(6)),
        [sym__declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [sym_type_declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [sym_var_declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [sym_func_declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [aux_sym_program_repeat1] = ACTIONS(SHIFT(429)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [anon_sym_import] = ACTIONS(SHIFT(11)),
        [anon_sym_type] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [anon_sym_var] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [anon_sym_func] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [7] = {
        [sym__declaration] = ACTIONS(SHIFT(7)),
        [sym_type_declaration] = ACTIONS(SHIFT(8)),
        [sym_var_declaration] = ACTIONS(SHIFT(8)),
        [sym_func_declaration] = ACTIONS(SHIFT(8)),
        [aux_sym_program_repeat2] = ACTIONS(SHIFT(428)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat2, 1)),
        [anon_sym_type] = ACTIONS(SHIFT(12)),
        [anon_sym_var] = ACTIONS(SHIFT(13)),
        [anon_sym_func] = ACTIONS(SHIFT(14)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
        [sym__declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym__declaration, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_type] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_var] = ACTIONS(REDUCE(sym__declaration, 1)),
        [anon_sym_func] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [sym__declaration] = ACTIONS(SHIFT(7)),
        [sym_type_declaration] = ACTIONS(SHIFT(8)),
        [sym_var_declaration] = ACTIONS(SHIFT(8)),
        [sym_func_declaration] = ACTIONS(SHIFT(8)),
        [aux_sym_program_repeat2] = ACTIONS(SHIFT(427)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 2)),
        [anon_sym_type] = ACTIONS(SHIFT(12)),
        [anon_sym_var] = ACTIONS(SHIFT(13)),
        [anon_sym_func] = ACTIONS(SHIFT(14)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [sym_package_import] = ACTIONS(SHIFT(418)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(419)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(420)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym_type_name] = ACTIONS(SHIFT(392)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(393)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [sym_var_name] = ACTIONS(SHIFT(383)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [sym_var_name] = ACTIONS(SHIFT(15)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [15] = {
        [sym__func_signature] = ACTIONS(SHIFT(17)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(18)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym__func_signature] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [sym_block_statement] = ACTIONS(SHIFT(196)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(197)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [sym_var_name] = ACTIONS(SHIFT(19)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(20)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [sym__type_expression] = ACTIONS(SHIFT(44)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(46)),
        [anon_sym_STAR] = ACTIONS(SHIFT(47)),
        [anon_sym_map] = ACTIONS(SHIFT(48)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(49)),
        [anon_sym_struct] = ACTIONS(SHIFT(50)),
        [anon_sym_interface] = ACTIONS(SHIFT(51)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(52)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(53)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [sym_type_name] = ACTIONS(SHIFT(22)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(23)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [sym__type_expression] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_pointer_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_map_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_slice_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_struct_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_interface_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_map] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_interface] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [sym_var_name] = ACTIONS(SHIFT(25)),
        [sym_type_name] = ACTIONS(SHIFT(26)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [sym_type_name] = ACTIONS(SHIFT(35)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(28)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(29)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(30)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [sym_type_name] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym__func_signature_repeat3] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(34)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [sym_type_name] = ACTIONS(SHIFT(31)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(32)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(33)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat3, 2)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(30)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [33] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat3, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [34] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [35] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(37)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(34)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(38)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [36] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [37] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(43)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [38] = {
        [sym_var_name] = ACTIONS(SHIFT(39)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(40)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [39] = {
        [sym_type_name] = ACTIONS(SHIFT(41)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [40] = {
        [sym_type_name] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [41] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(42)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat2, 3)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(38)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [42] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat2, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [43] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [44] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(189)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(190)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(80)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [45] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [46] = {
        [sym__type_expression] = ACTIONS(SHIFT(170)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [anon_sym_STAR] = ACTIONS(SHIFT(47)),
        [anon_sym_map] = ACTIONS(SHIFT(48)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(49)),
        [anon_sym_struct] = ACTIONS(SHIFT(50)),
        [anon_sym_interface] = ACTIONS(SHIFT(51)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(53)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [47] = {
        [sym__type_expression] = ACTIONS(SHIFT(169)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [anon_sym_STAR] = ACTIONS(SHIFT(47)),
        [anon_sym_map] = ACTIONS(SHIFT(48)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(49)),
        [anon_sym_struct] = ACTIONS(SHIFT(50)),
        [anon_sym_interface] = ACTIONS(SHIFT(51)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(53)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [48] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(165)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [49] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(163)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [50] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(111)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [51] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(56)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [52] = {
        [sym_var_name] = ACTIONS(SHIFT(54)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [53] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [54] = {
        [sym__type_expression] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym_pointer_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym_map_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym_slice_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym_struct_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym_interface_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym_type_name] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(55)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [anon_sym_map] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [anon_sym_interface] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(52)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [55] = {
        [sym__type_expression] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_pointer_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_map_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_slice_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_struct_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_interface_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_type_name] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [anon_sym_map] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [anon_sym_interface] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [56] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(58)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(59)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [57] = {
        [sym__func_signature] = ACTIONS(SHIFT(61)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(62)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [58] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(60)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [59] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [60] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [61] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(110)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_interface_type_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [62] = {
        [sym_var_name] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(64)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [63] = {
        [sym__type_expression] = ACTIONS(SHIFT(75)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(76)),
        [anon_sym_STAR] = ACTIONS(SHIFT(47)),
        [anon_sym_map] = ACTIONS(SHIFT(48)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(49)),
        [anon_sym_struct] = ACTIONS(SHIFT(50)),
        [anon_sym_interface] = ACTIONS(SHIFT(51)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(52)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(53)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [64] = {
        [sym_var_name] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [sym_type_name] = ACTIONS(SHIFT(65)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(66)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [65] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [66] = {
        [sym_var_name] = ACTIONS(SHIFT(67)),
        [sym_type_name] = ACTIONS(SHIFT(68)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [67] = {
        [sym_type_name] = ACTIONS(SHIFT(72)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [68] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(69)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(30)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [69] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(71)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [70] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [71] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [72] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(73)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(71)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(38)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(74)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [75] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(103)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(104)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(80)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [sym__type_expression] = ACTIONS(SHIFT(77)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [anon_sym_STAR] = ACTIONS(SHIFT(47)),
        [anon_sym_map] = ACTIONS(SHIFT(48)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(49)),
        [anon_sym_struct] = ACTIONS(SHIFT(50)),
        [anon_sym_interface] = ACTIONS(SHIFT(51)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(53)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(78)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(79)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(80)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(96)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [sym_var_name] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [sym_type_name] = ACTIONS(SHIFT(71)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [80] = {
        [sym_var_name] = ACTIONS(SHIFT(81)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(21)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [sym__type_expression] = ACTIONS(SHIFT(82)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(47)),
        [anon_sym_map] = ACTIONS(SHIFT(48)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(49)),
        [anon_sym_struct] = ACTIONS(SHIFT(50)),
        [anon_sym_interface] = ACTIONS(SHIFT(51)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(52)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(53)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [82] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(86)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat1, 3)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(80)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [sym__type_expression] = ACTIONS(SHIFT(84)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [anon_sym_STAR] = ACTIONS(SHIFT(47)),
        [anon_sym_map] = ACTIONS(SHIFT(48)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(49)),
        [anon_sym_struct] = ACTIONS(SHIFT(50)),
        [anon_sym_interface] = ACTIONS(SHIFT(51)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(53)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(85)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat1, 4)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(80)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat1, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat1, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [sym_var_name] = ACTIONS(SHIFT(88)),
        [sym_type_name] = ACTIONS(SHIFT(89)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [sym_type_name] = ACTIONS(SHIFT(93)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(91)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(30)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(92)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(92)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(38)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(95)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [sym_var_name] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [sym_type_name] = ACTIONS(SHIFT(74)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [sym_var_name] = ACTIONS(SHIFT(98)),
        [sym_type_name] = ACTIONS(SHIFT(99)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [sym_type_name] = ACTIONS(SHIFT(100)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [99] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(92)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(30)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(101)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(38)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(102)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [103] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(79)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [sym_var_name] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [sym_type_name] = ACTIONS(SHIFT(70)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(105)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
        [sym_var_name] = ACTIONS(SHIFT(106)),
        [sym_type_name] = ACTIONS(SHIFT(107)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [106] = {
        [sym_type_name] = ACTIONS(SHIFT(109)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [107] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(108)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(30)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [108] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(91)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(90)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(91)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(38)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_interface_type_repeat1, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(113)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(114)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [sym__type_expression] = ACTIONS(SHIFT(117)),
        [sym_pointer_type] = ACTIONS(SHIFT(118)),
        [sym_map_type] = ACTIONS(SHIFT(118)),
        [sym_slice_type] = ACTIONS(SHIFT(118)),
        [sym_struct_type] = ACTIONS(SHIFT(118)),
        [sym_interface_type] = ACTIONS(SHIFT(118)),
        [sym_type_name] = ACTIONS(SHIFT(118)),
        [anon_sym_STAR] = ACTIONS(SHIFT(119)),
        [anon_sym_map] = ACTIONS(SHIFT(120)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(121)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_interface] = ACTIONS(SHIFT(123)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(124)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(116)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [sym__type_expression] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_pointer_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_map_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_slice_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_struct_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_interface_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_map] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_interface] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [116] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [117] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(162)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_type_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [119] = {
        [sym__type_expression] = ACTIONS(SHIFT(161)),
        [sym_pointer_type] = ACTIONS(SHIFT(118)),
        [sym_map_type] = ACTIONS(SHIFT(118)),
        [sym_slice_type] = ACTIONS(SHIFT(118)),
        [sym_struct_type] = ACTIONS(SHIFT(118)),
        [sym_interface_type] = ACTIONS(SHIFT(118)),
        [sym_type_name] = ACTIONS(SHIFT(118)),
        [anon_sym_STAR] = ACTIONS(SHIFT(119)),
        [anon_sym_map] = ACTIONS(SHIFT(120)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(121)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_interface] = ACTIONS(SHIFT(123)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(124)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [120] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(135)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [121] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(133)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [122] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(129)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [123] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(125)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [124] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [125] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(126)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(127)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(128)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(130)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(131)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(132)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [131] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [133] = {
        [sym__type_expression] = ACTIONS(SHIFT(134)),
        [sym_pointer_type] = ACTIONS(SHIFT(118)),
        [sym_map_type] = ACTIONS(SHIFT(118)),
        [sym_slice_type] = ACTIONS(SHIFT(118)),
        [sym_struct_type] = ACTIONS(SHIFT(118)),
        [sym_interface_type] = ACTIONS(SHIFT(118)),
        [sym_type_name] = ACTIONS(SHIFT(118)),
        [anon_sym_STAR] = ACTIONS(SHIFT(119)),
        [anon_sym_map] = ACTIONS(SHIFT(120)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(121)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_interface] = ACTIONS(SHIFT(123)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(124)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [sym__type_expression] = ACTIONS(SHIFT(136)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [anon_sym_STAR] = ACTIONS(SHIFT(138)),
        [anon_sym_map] = ACTIONS(SHIFT(139)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(140)),
        [anon_sym_struct] = ACTIONS(SHIFT(141)),
        [anon_sym_interface] = ACTIONS(SHIFT(142)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(159)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [sym__type_expression] = ACTIONS(SHIFT(158)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [anon_sym_STAR] = ACTIONS(SHIFT(138)),
        [anon_sym_map] = ACTIONS(SHIFT(139)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(140)),
        [anon_sym_struct] = ACTIONS(SHIFT(141)),
        [anon_sym_interface] = ACTIONS(SHIFT(142)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [139] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(154)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [140] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(152)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(148)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(144)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [144] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(145)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(146)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [145] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(147)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(149)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(150)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(151)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [sym__type_expression] = ACTIONS(SHIFT(153)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [anon_sym_STAR] = ACTIONS(SHIFT(138)),
        [anon_sym_map] = ACTIONS(SHIFT(139)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(140)),
        [anon_sym_struct] = ACTIONS(SHIFT(141)),
        [anon_sym_interface] = ACTIONS(SHIFT(142)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym__type_expression] = ACTIONS(SHIFT(155)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [anon_sym_STAR] = ACTIONS(SHIFT(138)),
        [anon_sym_map] = ACTIONS(SHIFT(139)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(140)),
        [anon_sym_struct] = ACTIONS(SHIFT(141)),
        [anon_sym_interface] = ACTIONS(SHIFT(142)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(156)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [sym__type_expression] = ACTIONS(SHIFT(157)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [anon_sym_STAR] = ACTIONS(SHIFT(138)),
        [anon_sym_map] = ACTIONS(SHIFT(139)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(140)),
        [anon_sym_struct] = ACTIONS(SHIFT(141)),
        [anon_sym_interface] = ACTIONS(SHIFT(142)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [sym__type_expression] = ACTIONS(SHIFT(160)),
        [sym_pointer_type] = ACTIONS(SHIFT(118)),
        [sym_map_type] = ACTIONS(SHIFT(118)),
        [sym_slice_type] = ACTIONS(SHIFT(118)),
        [sym_struct_type] = ACTIONS(SHIFT(118)),
        [sym_interface_type] = ACTIONS(SHIFT(118)),
        [sym_type_name] = ACTIONS(SHIFT(118)),
        [anon_sym_STAR] = ACTIONS(SHIFT(119)),
        [anon_sym_map] = ACTIONS(SHIFT(120)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(121)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_interface] = ACTIONS(SHIFT(123)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(124)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_map_type, 5)),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_map_type, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_type_repeat1, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [sym__type_expression] = ACTIONS(SHIFT(164)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [anon_sym_STAR] = ACTIONS(SHIFT(47)),
        [anon_sym_map] = ACTIONS(SHIFT(48)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(49)),
        [anon_sym_struct] = ACTIONS(SHIFT(50)),
        [anon_sym_interface] = ACTIONS(SHIFT(51)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(53)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [sym__type_expression] = ACTIONS(SHIFT(166)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [anon_sym_STAR] = ACTIONS(SHIFT(138)),
        [anon_sym_map] = ACTIONS(SHIFT(139)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(140)),
        [anon_sym_struct] = ACTIONS(SHIFT(141)),
        [anon_sym_interface] = ACTIONS(SHIFT(142)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(167)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [sym__type_expression] = ACTIONS(SHIFT(168)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [anon_sym_STAR] = ACTIONS(SHIFT(47)),
        [anon_sym_map] = ACTIONS(SHIFT(48)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(49)),
        [anon_sym_struct] = ACTIONS(SHIFT(50)),
        [anon_sym_interface] = ACTIONS(SHIFT(51)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(53)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_map_type, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_map_type, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(171)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(172)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(80)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(182)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [172] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [sym_type_name] = ACTIONS(SHIFT(34)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(173)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [sym_var_name] = ACTIONS(SHIFT(174)),
        [sym_type_name] = ACTIONS(SHIFT(175)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [sym_type_name] = ACTIONS(SHIFT(179)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(176)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(177)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(30)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(178)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(180)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(178)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(38)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [180] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(181)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [sym_type_name] = ACTIONS(SHIFT(43)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(183)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [sym_var_name] = ACTIONS(SHIFT(184)),
        [sym_type_name] = ACTIONS(SHIFT(185)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
        [sym_type_name] = ACTIONS(SHIFT(186)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [185] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(180)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(178)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(30)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [186] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(187)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(181)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(38)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(188)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [188] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(172)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [sym_type_name] = ACTIONS(SHIFT(29)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(191)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(24)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [sym_var_name] = ACTIONS(SHIFT(192)),
        [sym_type_name] = ACTIONS(SHIFT(193)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [sym_type_name] = ACTIONS(SHIFT(195)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(194)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(43)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(30)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(177)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(176)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(177)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(38)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(382)),
        [sym__line_break] = ACTIONS(SHIFT(382)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [sym_var_declaration] = ACTIONS(SHIFT(198)),
        [sym__statement] = ACTIONS(SHIFT(199)),
        [sym_return_statement] = ACTIONS(SHIFT(198)),
        [sym_short_var_declaration] = ACTIONS(SHIFT(198)),
        [sym_range_statement] = ACTIONS(SHIFT(198)),
        [sym_if_statement] = ACTIONS(SHIFT(198)),
        [sym_expression_statement] = ACTIONS(SHIFT(198)),
        [sym__expression] = ACTIONS(SHIFT(200)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(202)),
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(203)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(203)),
        [anon_sym_var] = ACTIONS(SHIFT(204)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(205)),
        [anon_sym_return] = ACTIONS(SHIFT(206)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(207)),
        [anon_sym_for] = ACTIONS(SHIFT(208)),
        [anon_sym_if] = ACTIONS(SHIFT(209)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(211)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_return_statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_range_statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_if_statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_call_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_math_op] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_bool_op] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_var_name] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_var] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_return] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_for] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_if] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__identifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [sym_var_declaration] = ACTIONS(SHIFT(198)),
        [sym__statement] = ACTIONS(SHIFT(199)),
        [sym_return_statement] = ACTIONS(SHIFT(198)),
        [sym_short_var_declaration] = ACTIONS(SHIFT(198)),
        [sym_range_statement] = ACTIONS(SHIFT(198)),
        [sym_if_statement] = ACTIONS(SHIFT(198)),
        [sym_expression_statement] = ACTIONS(SHIFT(198)),
        [sym__expression] = ACTIONS(SHIFT(200)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(202)),
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(381)),
        [anon_sym_var] = ACTIONS(SHIFT(204)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_block_statement_repeat1, 1)),
        [anon_sym_return] = ACTIONS(SHIFT(206)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(207)),
        [anon_sym_for] = ACTIONS(SHIFT(208)),
        [anon_sym_if] = ACTIONS(SHIFT(209)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(211)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(287)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(380)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(SHIFT(290)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(291)),
        [anon_sym_DASH] = ACTIONS(SHIFT(291)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(SHIFT(380)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(369)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(370)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(371)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(368)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
        [sym_var_name] = ACTIONS(SHIFT(336)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__line_break] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [sym__expression] = ACTIONS(SHIFT(306)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(308)),
        [anon_sym_BANG] = ACTIONS(SHIFT(309)),
        [sym__line_break] = ACTIONS(SHIFT(308)),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(310)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [sym__expression] = ACTIONS(SHIFT(286)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
        [sym_var_name] = ACTIONS(SHIFT(273)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(274)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [209] = {
        [sym__expression] = ACTIONS(SHIFT(214)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [anon_sym_BANG] = ACTIONS(SHIFT(216)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [sym__expression] = ACTIONS(SHIFT(212)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [213] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [sym_block_statement] = ACTIONS(SHIFT(219)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(220)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(221)),
        [anon_sym_STAR] = ACTIONS(SHIFT(222)),
        [anon_sym_DOT] = ACTIONS(SHIFT(223)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(222)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(224)),
        [anon_sym_DASH] = ACTIONS(SHIFT(224)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(225)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(226)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT] = ACTIONS(SHIFT(227)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_GT] = ACTIONS(SHIFT(227)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [sym__expression] = ACTIONS(SHIFT(218)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [anon_sym_BANG] = ACTIONS(SHIFT(216)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [219] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_math_op] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_var_name] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [anon_sym_else] = ACTIONS(SHIFT(267)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
        [sym__expression] = ACTIONS(SHIFT(237)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(239)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [sym_var_declaration] = ACTIONS(SHIFT(198)),
        [sym__statement] = ACTIONS(SHIFT(199)),
        [sym_return_statement] = ACTIONS(SHIFT(198)),
        [sym_short_var_declaration] = ACTIONS(SHIFT(198)),
        [sym_range_statement] = ACTIONS(SHIFT(198)),
        [sym_if_statement] = ACTIONS(SHIFT(198)),
        [sym_expression_statement] = ACTIONS(SHIFT(198)),
        [sym__expression] = ACTIONS(SHIFT(200)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(202)),
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(234)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(234)),
        [anon_sym_var] = ACTIONS(SHIFT(204)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(235)),
        [anon_sym_return] = ACTIONS(SHIFT(206)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(207)),
        [anon_sym_for] = ACTIONS(SHIFT(208)),
        [anon_sym_if] = ACTIONS(SHIFT(209)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(211)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [sym__expression] = ACTIONS(SHIFT(233)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [anon_sym_BANG] = ACTIONS(SHIFT(216)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
        [sym_var_name] = ACTIONS(SHIFT(232)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym__expression] = ACTIONS(SHIFT(231)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [anon_sym_BANG] = ACTIONS(SHIFT(216)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [225] = {
        [sym__expression] = ACTIONS(SHIFT(230)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [anon_sym_BANG] = ACTIONS(SHIFT(216)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
        [sym__expression] = ACTIONS(SHIFT(229)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [anon_sym_BANG] = ACTIONS(SHIFT(216)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [sym__expression] = ACTIONS(SHIFT(228)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [anon_sym_BANG] = ACTIONS(SHIFT(216)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [228] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT] = ACTIONS(SHIFT(227)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_GT] = ACTIONS(SHIFT(227)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(222)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(222)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(226)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT] = ACTIONS(SHIFT(227)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_GT] = ACTIONS(SHIFT(227)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [231] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(222)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(222)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(226)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT] = ACTIONS(SHIFT(227)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_GT] = ACTIONS(SHIFT(227)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [233] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT] = ACTIONS(SHIFT(227)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_GT] = ACTIONS(SHIFT(227)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(236)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_math_op] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_var_name] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_else] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__identifier] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_math_op] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_var_name] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_else] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [237] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(243)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(244)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(245)),
        [anon_sym_STAR] = ACTIONS(SHIFT(246)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(247)),
        [anon_sym_DOT] = ACTIONS(SHIFT(248)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(246)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(249)),
        [anon_sym_DASH] = ACTIONS(SHIFT(249)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(251)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT] = ACTIONS(SHIFT(252)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_GT] = ACTIONS(SHIFT(252)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [238] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [240] = {
        [sym__expression] = ACTIONS(SHIFT(242)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [241] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [243] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(266)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [sym__expression] = ACTIONS(SHIFT(261)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(262)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [246] = {
        [sym__expression] = ACTIONS(SHIFT(260)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [247] = {
        [sym__expression] = ACTIONS(SHIFT(258)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym_var_name] = ACTIONS(SHIFT(257)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [sym__expression] = ACTIONS(SHIFT(256)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [250] = {
        [sym__expression] = ACTIONS(SHIFT(255)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [sym__expression] = ACTIONS(SHIFT(254)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [sym__expression] = ACTIONS(SHIFT(253)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT] = ACTIONS(SHIFT(252)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_GT] = ACTIONS(SHIFT(252)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(246)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(246)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(251)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT] = ACTIONS(SHIFT(252)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_GT] = ACTIONS(SHIFT(252)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(246)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(246)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(251)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT] = ACTIONS(SHIFT(252)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_GT] = ACTIONS(SHIFT(252)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(259)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(244)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(246)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(247)),
        [anon_sym_DOT] = ACTIONS(SHIFT(248)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(246)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(249)),
        [anon_sym_DASH] = ACTIONS(SHIFT(249)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(251)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT] = ACTIONS(SHIFT(252)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_GT] = ACTIONS(SHIFT(252)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [259] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [260] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT] = ACTIONS(SHIFT(252)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_GT] = ACTIONS(SHIFT(252)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [261] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(263)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(244)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(264)),
        [anon_sym_STAR] = ACTIONS(SHIFT(246)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(247)),
        [anon_sym_DOT] = ACTIONS(SHIFT(248)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(246)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(249)),
        [anon_sym_DASH] = ACTIONS(SHIFT(249)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(251)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT] = ACTIONS(SHIFT(252)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_GT] = ACTIONS(SHIFT(252)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [262] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(265)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [264] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [265] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [267] = {
        [sym_block_statement] = ACTIONS(SHIFT(268)),
        [sym_if_statement] = ACTIONS(SHIFT(268)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(269)),
        [anon_sym_if] = ACTIONS(SHIFT(209)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [268] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym__statement] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym__expression] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_math_op] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_var_name] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym__identifier] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [269] = {
        [sym_var_declaration] = ACTIONS(SHIFT(198)),
        [sym__statement] = ACTIONS(SHIFT(199)),
        [sym_return_statement] = ACTIONS(SHIFT(198)),
        [sym_short_var_declaration] = ACTIONS(SHIFT(198)),
        [sym_range_statement] = ACTIONS(SHIFT(198)),
        [sym_if_statement] = ACTIONS(SHIFT(198)),
        [sym_expression_statement] = ACTIONS(SHIFT(198)),
        [sym__expression] = ACTIONS(SHIFT(200)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(202)),
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(270)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(270)),
        [anon_sym_var] = ACTIONS(SHIFT(204)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(271)),
        [anon_sym_return] = ACTIONS(SHIFT(206)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(207)),
        [anon_sym_for] = ACTIONS(SHIFT(208)),
        [anon_sym_if] = ACTIONS(SHIFT(209)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(211)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [270] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(272)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [271] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_math_op] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_var_name] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__identifier] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [272] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_math_op] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_var_name] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [273] = {
        [anon_sym_COMMA] = ACTIONS(SHIFT(275)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(276)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [274] = {
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [275] = {
        [sym_var_name] = ACTIONS(SHIFT(280)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(281)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [276] = {
        [anon_sym_range] = ACTIONS(SHIFT(277)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [277] = {
        [sym__expression] = ACTIONS(SHIFT(278)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [anon_sym_BANG] = ACTIONS(SHIFT(216)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [278] = {
        [sym_block_statement] = ACTIONS(SHIFT(279)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(220)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(269)),
        [anon_sym_STAR] = ACTIONS(SHIFT(222)),
        [anon_sym_DOT] = ACTIONS(SHIFT(223)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(222)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(224)),
        [anon_sym_DASH] = ACTIONS(SHIFT(224)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(225)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(226)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT] = ACTIONS(SHIFT(227)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_GT] = ACTIONS(SHIFT(227)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [279] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym__statement] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym__expression] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_math_op] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_var_name] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym__identifier] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_number] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [280] = {
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(282)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [281] = {
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [282] = {
        [anon_sym_range] = ACTIONS(SHIFT(283)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [283] = {
        [sym__expression] = ACTIONS(SHIFT(284)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [anon_sym_BANG] = ACTIONS(SHIFT(216)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(217)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [284] = {
        [sym_block_statement] = ACTIONS(SHIFT(285)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(220)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(269)),
        [anon_sym_STAR] = ACTIONS(SHIFT(222)),
        [anon_sym_DOT] = ACTIONS(SHIFT(223)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(222)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(224)),
        [anon_sym_DASH] = ACTIONS(SHIFT(224)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(225)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(226)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_LT] = ACTIONS(SHIFT(227)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(227)),
        [anon_sym_GT] = ACTIONS(SHIFT(227)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [285] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym__statement] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym__expression] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_math_op] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_var_name] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym__identifier] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_number] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [286] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(287)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(288)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(SHIFT(290)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(291)),
        [anon_sym_DASH] = ACTIONS(SHIFT(291)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(SHIFT(288)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [287] = {
        [sym__expression] = ACTIONS(SHIFT(301)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(302)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [288] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_math_op] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_var_name] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [289] = {
        [sym__expression] = ACTIONS(SHIFT(300)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [290] = {
        [sym_var_name] = ACTIONS(SHIFT(299)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [291] = {
        [sym__expression] = ACTIONS(SHIFT(298)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [292] = {
        [sym__expression] = ACTIONS(SHIFT(297)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [293] = {
        [sym__expression] = ACTIONS(SHIFT(296)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [294] = {
        [sym__expression] = ACTIONS(SHIFT(295)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [295] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [296] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [297] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [298] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [299] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [300] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [301] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(303)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(244)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(304)),
        [anon_sym_STAR] = ACTIONS(SHIFT(246)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(247)),
        [anon_sym_DOT] = ACTIONS(SHIFT(248)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(246)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(249)),
        [anon_sym_DASH] = ACTIONS(SHIFT(249)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(251)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT] = ACTIONS(SHIFT(252)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_GT] = ACTIONS(SHIFT(252)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [302] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [303] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(305)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [304] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [305] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [306] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(312)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(313)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(314)),
        [anon_sym_STAR] = ACTIONS(SHIFT(315)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(316)),
        [anon_sym_DOT] = ACTIONS(SHIFT(317)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(315)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(318)),
        [anon_sym_DASH] = ACTIONS(SHIFT(318)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(319)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(320)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT] = ACTIONS(SHIFT(321)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_GT] = ACTIONS(SHIFT(321)),
        [sym__line_break] = ACTIONS(SHIFT(314)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [307] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [308] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_math_op] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_var_name] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym__identifier] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [309] = {
        [sym__expression] = ACTIONS(SHIFT(311)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [anon_sym_BANG] = ACTIONS(SHIFT(309)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(310)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [310] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [311] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [312] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(335)),
        [sym__line_break] = ACTIONS(SHIFT(335)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [313] = {
        [sym__expression] = ACTIONS(SHIFT(330)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(331)),
        [anon_sym_BANG] = ACTIONS(SHIFT(240)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(241)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [314] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_math_op] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_var_name] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [315] = {
        [sym__expression] = ACTIONS(SHIFT(329)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [anon_sym_BANG] = ACTIONS(SHIFT(309)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(310)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [316] = {
        [sym__expression] = ACTIONS(SHIFT(327)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [anon_sym_BANG] = ACTIONS(SHIFT(309)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(310)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [317] = {
        [sym_var_name] = ACTIONS(SHIFT(326)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(310)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [318] = {
        [sym__expression] = ACTIONS(SHIFT(325)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [anon_sym_BANG] = ACTIONS(SHIFT(309)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(310)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [319] = {
        [sym__expression] = ACTIONS(SHIFT(324)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [anon_sym_BANG] = ACTIONS(SHIFT(309)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(310)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [320] = {
        [sym__expression] = ACTIONS(SHIFT(323)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [anon_sym_BANG] = ACTIONS(SHIFT(309)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(310)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [321] = {
        [sym__expression] = ACTIONS(SHIFT(322)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [anon_sym_BANG] = ACTIONS(SHIFT(309)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(310)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [322] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [323] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT] = ACTIONS(SHIFT(321)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_GT] = ACTIONS(SHIFT(321)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [324] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(315)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(315)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(320)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT] = ACTIONS(SHIFT(321)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_GT] = ACTIONS(SHIFT(321)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [325] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(315)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(315)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(320)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT] = ACTIONS(SHIFT(321)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_GT] = ACTIONS(SHIFT(321)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [326] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [327] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(328)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(313)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(315)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(316)),
        [anon_sym_DOT] = ACTIONS(SHIFT(317)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(315)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(318)),
        [anon_sym_DASH] = ACTIONS(SHIFT(318)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(319)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(320)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT] = ACTIONS(SHIFT(321)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_GT] = ACTIONS(SHIFT(321)),
        [sym__line_break] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [328] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 3)),
        [sym__line_break] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [329] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_LT] = ACTIONS(SHIFT(321)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(321)),
        [anon_sym_GT] = ACTIONS(SHIFT(321)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [330] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(332)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(244)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(333)),
        [anon_sym_STAR] = ACTIONS(SHIFT(246)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(247)),
        [anon_sym_DOT] = ACTIONS(SHIFT(248)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(246)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(249)),
        [anon_sym_DASH] = ACTIONS(SHIFT(249)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(251)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_LT] = ACTIONS(SHIFT(252)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(252)),
        [anon_sym_GT] = ACTIONS(SHIFT(252)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [331] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [332] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(334)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [333] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [334] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [335] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym__statement] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym__expression] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_math_op] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_var_name] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym__identifier] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [336] = {
        [sym__type_expression] = ACTIONS(SHIFT(338)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [anon_sym_EQ] = ACTIONS(SHIFT(340)),
        [anon_sym_STAR] = ACTIONS(SHIFT(341)),
        [anon_sym_map] = ACTIONS(SHIFT(342)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(343)),
        [anon_sym_struct] = ACTIONS(SHIFT(344)),
        [anon_sym_interface] = ACTIONS(SHIFT(345)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(346)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [337] = {
        [sym__type_expression] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_pointer_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_map_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_slice_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_struct_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_interface_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_map] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_interface] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [338] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(364)),
        [anon_sym_EQ] = ACTIONS(SHIFT(365)),
        [sym__line_break] = ACTIONS(SHIFT(364)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [339] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [340] = {
        [sym__expression] = ACTIONS(SHIFT(362)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [341] = {
        [sym__type_expression] = ACTIONS(SHIFT(361)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [anon_sym_STAR] = ACTIONS(SHIFT(341)),
        [anon_sym_map] = ACTIONS(SHIFT(342)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(343)),
        [anon_sym_struct] = ACTIONS(SHIFT(344)),
        [anon_sym_interface] = ACTIONS(SHIFT(345)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(346)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [342] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(357)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [343] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(355)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [344] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(351)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [345] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(347)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [346] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [347] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(348)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(349)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [348] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(350)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [349] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [350] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [351] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(352)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(353)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [352] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(354)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [353] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [354] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [355] = {
        [sym__type_expression] = ACTIONS(SHIFT(356)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [anon_sym_STAR] = ACTIONS(SHIFT(341)),
        [anon_sym_map] = ACTIONS(SHIFT(342)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(343)),
        [anon_sym_struct] = ACTIONS(SHIFT(344)),
        [anon_sym_interface] = ACTIONS(SHIFT(345)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(346)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [356] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [357] = {
        [sym__type_expression] = ACTIONS(SHIFT(358)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [anon_sym_STAR] = ACTIONS(SHIFT(138)),
        [anon_sym_map] = ACTIONS(SHIFT(139)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(140)),
        [anon_sym_struct] = ACTIONS(SHIFT(141)),
        [anon_sym_interface] = ACTIONS(SHIFT(142)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [358] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(359)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [359] = {
        [sym__type_expression] = ACTIONS(SHIFT(360)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [anon_sym_STAR] = ACTIONS(SHIFT(341)),
        [anon_sym_map] = ACTIONS(SHIFT(342)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(343)),
        [anon_sym_struct] = ACTIONS(SHIFT(344)),
        [anon_sym_interface] = ACTIONS(SHIFT(345)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(346)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [360] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_map_type, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym__line_break] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [361] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym__line_break] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [362] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(287)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(363)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(SHIFT(290)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(291)),
        [anon_sym_DASH] = ACTIONS(SHIFT(291)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(SHIFT(363)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [363] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym__statement] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym__expression] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_math_op] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_var_name] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [364] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym__statement] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym__expression] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_math_op] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_var_name] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [365] = {
        [sym__expression] = ACTIONS(SHIFT(366)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [366] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(287)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(367)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(SHIFT(290)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(291)),
        [anon_sym_DASH] = ACTIONS(SHIFT(291)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(SHIFT(367)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [367] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym__statement] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym__expression] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_math_op] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_var_name] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_number] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [368] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [369] = {
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(377)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [370] = {
        [sym_var_name] = ACTIONS(SHIFT(374)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(375)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [371] = {
        [sym__expression] = ACTIONS(SHIFT(372)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [372] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(287)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(373)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(SHIFT(290)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(291)),
        [anon_sym_DASH] = ACTIONS(SHIFT(291)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(SHIFT(373)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [373] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym__statement] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym__expression] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_math_op] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_var_name] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym__identifier] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [374] = {
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(376)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(370)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [375] = {
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [376] = {
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [377] = {
        [sym__expression] = ACTIONS(SHIFT(378)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [378] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(287)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(379)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(SHIFT(290)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(291)),
        [anon_sym_DASH] = ACTIONS(SHIFT(291)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(SHIFT(379)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [379] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym__statement] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym__expression] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_math_op] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_var_name] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym__identifier] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [380] = {
        [sym_var_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_return_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_short_var_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_range_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_if_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_selector_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_math_op] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_bool_op] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_var_name] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [381] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_block_statement_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [382] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [383] = {
        [sym__type_expression] = ACTIONS(SHIFT(384)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [anon_sym_EQ] = ACTIONS(SHIFT(385)),
        [anon_sym_STAR] = ACTIONS(SHIFT(341)),
        [anon_sym_map] = ACTIONS(SHIFT(342)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(343)),
        [anon_sym_struct] = ACTIONS(SHIFT(344)),
        [anon_sym_interface] = ACTIONS(SHIFT(345)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(346)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [384] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(388)),
        [anon_sym_EQ] = ACTIONS(SHIFT(389)),
        [sym__line_break] = ACTIONS(SHIFT(388)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [385] = {
        [sym__expression] = ACTIONS(SHIFT(386)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [386] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(287)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(387)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(SHIFT(290)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(291)),
        [anon_sym_DASH] = ACTIONS(SHIFT(291)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(SHIFT(387)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [387] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [388] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [389] = {
        [sym__expression] = ACTIONS(SHIFT(390)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [390] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(287)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(391)),
        [anon_sym_STAR] = ACTIONS(SHIFT(289)),
        [anon_sym_DOT] = ACTIONS(SHIFT(290)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(289)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(291)),
        [anon_sym_DASH] = ACTIONS(SHIFT(291)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(293)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_LT] = ACTIONS(SHIFT(294)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(294)),
        [anon_sym_GT] = ACTIONS(SHIFT(294)),
        [sym__line_break] = ACTIONS(SHIFT(391)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [391] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [392] = {
        [sym__type_expression] = ACTIONS(SHIFT(394)),
        [sym_pointer_type] = ACTIONS(SHIFT(395)),
        [sym_map_type] = ACTIONS(SHIFT(395)),
        [sym_slice_type] = ACTIONS(SHIFT(395)),
        [sym_struct_type] = ACTIONS(SHIFT(395)),
        [sym_interface_type] = ACTIONS(SHIFT(395)),
        [sym_type_name] = ACTIONS(SHIFT(395)),
        [anon_sym_STAR] = ACTIONS(SHIFT(396)),
        [anon_sym_map] = ACTIONS(SHIFT(397)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(398)),
        [anon_sym_struct] = ACTIONS(SHIFT(399)),
        [anon_sym_interface] = ACTIONS(SHIFT(400)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(401)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [393] = {
        [sym__type_expression] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_map_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_slice_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_struct_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_interface_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_map] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_interface] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [394] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(417)),
        [sym__line_break] = ACTIONS(SHIFT(417)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [395] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [396] = {
        [sym__type_expression] = ACTIONS(SHIFT(416)),
        [sym_pointer_type] = ACTIONS(SHIFT(395)),
        [sym_map_type] = ACTIONS(SHIFT(395)),
        [sym_slice_type] = ACTIONS(SHIFT(395)),
        [sym_struct_type] = ACTIONS(SHIFT(395)),
        [sym_interface_type] = ACTIONS(SHIFT(395)),
        [sym_type_name] = ACTIONS(SHIFT(395)),
        [anon_sym_STAR] = ACTIONS(SHIFT(396)),
        [anon_sym_map] = ACTIONS(SHIFT(397)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(398)),
        [anon_sym_struct] = ACTIONS(SHIFT(399)),
        [anon_sym_interface] = ACTIONS(SHIFT(400)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(401)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [397] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(412)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [398] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(410)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [399] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(406)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [400] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(402)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [401] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [402] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(403)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(404)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [403] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(405)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [404] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [405] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [406] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(407)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(408)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [407] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(409)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [408] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [409] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [410] = {
        [sym__type_expression] = ACTIONS(SHIFT(411)),
        [sym_pointer_type] = ACTIONS(SHIFT(395)),
        [sym_map_type] = ACTIONS(SHIFT(395)),
        [sym_slice_type] = ACTIONS(SHIFT(395)),
        [sym_struct_type] = ACTIONS(SHIFT(395)),
        [sym_interface_type] = ACTIONS(SHIFT(395)),
        [sym_type_name] = ACTIONS(SHIFT(395)),
        [anon_sym_STAR] = ACTIONS(SHIFT(396)),
        [anon_sym_map] = ACTIONS(SHIFT(397)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(398)),
        [anon_sym_struct] = ACTIONS(SHIFT(399)),
        [anon_sym_interface] = ACTIONS(SHIFT(400)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(401)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [411] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [412] = {
        [sym__type_expression] = ACTIONS(SHIFT(413)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [anon_sym_STAR] = ACTIONS(SHIFT(138)),
        [anon_sym_map] = ACTIONS(SHIFT(139)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(140)),
        [anon_sym_struct] = ACTIONS(SHIFT(141)),
        [anon_sym_interface] = ACTIONS(SHIFT(142)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [413] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(414)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [414] = {
        [sym__type_expression] = ACTIONS(SHIFT(415)),
        [sym_pointer_type] = ACTIONS(SHIFT(395)),
        [sym_map_type] = ACTIONS(SHIFT(395)),
        [sym_slice_type] = ACTIONS(SHIFT(395)),
        [sym_struct_type] = ACTIONS(SHIFT(395)),
        [sym_interface_type] = ACTIONS(SHIFT(395)),
        [sym_type_name] = ACTIONS(SHIFT(395)),
        [anon_sym_STAR] = ACTIONS(SHIFT(396)),
        [anon_sym_map] = ACTIONS(SHIFT(397)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(398)),
        [anon_sym_struct] = ACTIONS(SHIFT(399)),
        [anon_sym_interface] = ACTIONS(SHIFT(400)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(401)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [415] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym__line_break] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [416] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym__line_break] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [417] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [418] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym__declaration] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [anon_sym_import] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [419] = {
        [sym_package_import] = ACTIONS(SHIFT(421)),
        [aux_sym_imports_block_repeat1] = ACTIONS(SHIFT(422)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(422)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(423)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(424)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [420] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym__declaration] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_package_import, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_package_import, 1)),
        [anon_sym_import] = ACTIONS(REDUCE(sym_package_import, 1)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_package_import, 1)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_package_import, 1)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [421] = {
        [sym_package_import] = ACTIONS(SHIFT(421)),
        [aux_sym_imports_block_repeat1] = ACTIONS(SHIFT(426)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_imports_block_repeat1, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(424)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [422] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(425)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [423] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym__declaration] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [anon_sym_import] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [424] = {
        [sym_package_import] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_imports_block_repeat1] = ACTIONS(REDUCE(sym_package_import, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [425] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym__declaration] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [anon_sym_import] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [426] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_imports_block_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [427] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [428] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat2, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [429] = {
        [sym__declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [sym_type_declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [sym_var_declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [sym_func_declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [anon_sym_type] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [anon_sym_var] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [anon_sym_func] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_golang);
