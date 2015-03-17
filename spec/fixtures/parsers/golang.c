#include "tree_sitter/parser.h"

#define STATE_COUNT 435
#define SYMBOL_COUNT 88

enum {
    sym_program = ts_builtin_sym_start,
    sym_package_directive,
    sym_imports_block,
    sym_package_import,
    sym_declaration,
    sym_type_declaration,
    sym_var_declaration,
    sym_func_declaration,
    sym_block_statement,
    sym_type_expression,
    sym_pointer_type,
    sym_map_type,
    sym_slice_type,
    sym_struct_type,
    sym_interface_type,
    sym_statement,
    sym_return_statement,
    sym_declaration_statement,
    sym_range_statement,
    sym_if_statement,
    sym_expression_statement,
    sym_expression,
    sym_call_expression,
    sym_selector_expression,
    sym_math_op,
    sym_bool_op,
    sym__func_signature,
    sym_package_name,
    sym_var_name,
    sym_type_name,
    sym__line_break,
    sym_string,
    sym__identifier,
    sym_number,
    sym_comment,
    aux_sym_program_repeat0,
    aux_sym_program_repeat1,
    aux_sym_imports_block_repeat0,
    aux_sym_block_statement_repeat0,
    aux_sym_struct_type_repeat0,
    aux_sym_interface_type_repeat0,
    aux_sym_return_statement_repeat0,
    aux_sym_declaration_statement_repeat0,
    aux_sym_call_expression_repeat0,
    aux_sym__func_signature_repeat0,
    aux_sym__func_signature_repeat1,
    aux_sym__func_signature_repeat2,
    aux_sym__func_signature_repeat3,
    aux_sym__func_signature_repeat4,
    aux_sym_STR_package,
    aux_sym_STR_import,
    aux_sym_STR_LPAREN,
    aux_sym_STR_RPAREN,
    aux_sym_STR_type,
    aux_sym_STR_SEMI,
    aux_sym_STR_var,
    aux_sym_STR_EQ,
    aux_sym_STR_func,
    aux_sym_STR_LBRACE,
    aux_sym_STR_RBRACE,
    aux_sym_STR_STAR,
    aux_sym_STR_map,
    aux_sym_STR_LBRACK,
    aux_sym_STR_RBRACK,
    aux_sym_STR_struct,
    aux_sym_STR_interface,
    aux_sym_STR_return,
    aux_sym_STR_COMMA,
    aux_sym_STR_COLON_EQ,
    aux_sym_STR_for,
    aux_sym_STR_range,
    aux_sym_STR_if,
    aux_sym_STR_else,
    aux_sym_STR_DOT,
    aux_sym_STR_SLASH,
    aux_sym_STR_PLUS,
    aux_sym_STR_DASH,
    aux_sym_STR_PIPE_PIPE,
    aux_sym_STR_AMP_AMP,
    aux_sym_STR_EQ_EQ,
    aux_sym_STR_LT_EQ,
    aux_sym_STR_LT,
    aux_sym_STR_GT_EQ,
    aux_sym_STR_GT,
    aux_sym_STR_BANG,
};

static const char *ts_symbol_names[] = {
    [ts_builtin_sym_document] = "DOCUMENT",
    [sym_program] = "program",
    [sym_package_directive] = "package_directive",
    [sym_imports_block] = "imports_block",
    [sym_package_import] = "package_import",
    [sym_declaration] = "declaration",
    [sym_type_declaration] = "type_declaration",
    [sym_var_declaration] = "var_declaration",
    [sym_func_declaration] = "func_declaration",
    [sym_block_statement] = "block_statement",
    [sym_type_expression] = "type_expression",
    [sym_pointer_type] = "pointer_type",
    [sym_map_type] = "map_type",
    [sym_slice_type] = "slice_type",
    [sym_struct_type] = "struct_type",
    [sym_interface_type] = "interface_type",
    [sym_statement] = "statement",
    [sym_return_statement] = "return_statement",
    [sym_declaration_statement] = "declaration_statement",
    [sym_range_statement] = "range_statement",
    [sym_if_statement] = "if_statement",
    [sym_expression_statement] = "expression_statement",
    [sym_expression] = "expression",
    [sym_call_expression] = "call_expression",
    [sym_selector_expression] = "selector_expression",
    [sym_math_op] = "math_op",
    [sym_bool_op] = "bool_op",
    [sym__func_signature] = "_func_signature",
    [sym_package_name] = "package_name",
    [sym_var_name] = "var_name",
    [sym_type_name] = "type_name",
    [ts_builtin_sym_error] = "error",
    [ts_builtin_sym_end] = "end",
    [sym__line_break] = "_line_break",
    [sym_string] = "string",
    [sym__identifier] = "_identifier",
    [sym_number] = "number",
    [sym_comment] = "comment",
    [aux_sym_program_repeat0] = "program_repeat0",
    [aux_sym_program_repeat1] = "program_repeat1",
    [aux_sym_imports_block_repeat0] = "imports_block_repeat0",
    [aux_sym_block_statement_repeat0] = "block_statement_repeat0",
    [aux_sym_struct_type_repeat0] = "struct_type_repeat0",
    [aux_sym_interface_type_repeat0] = "interface_type_repeat0",
    [aux_sym_return_statement_repeat0] = "return_statement_repeat0",
    [aux_sym_declaration_statement_repeat0] = "declaration_statement_repeat0",
    [aux_sym_call_expression_repeat0] = "call_expression_repeat0",
    [aux_sym__func_signature_repeat0] = "_func_signature_repeat0",
    [aux_sym__func_signature_repeat1] = "_func_signature_repeat1",
    [aux_sym__func_signature_repeat2] = "_func_signature_repeat2",
    [aux_sym__func_signature_repeat3] = "_func_signature_repeat3",
    [aux_sym__func_signature_repeat4] = "_func_signature_repeat4",
    [aux_sym_STR_package] = "STR_package",
    [aux_sym_STR_import] = "STR_import",
    [aux_sym_STR_LPAREN] = "STR_(",
    [aux_sym_STR_RPAREN] = "STR_)",
    [aux_sym_STR_type] = "STR_type",
    [aux_sym_STR_SEMI] = "STR_;",
    [aux_sym_STR_var] = "STR_var",
    [aux_sym_STR_EQ] = "STR_=",
    [aux_sym_STR_func] = "STR_func",
    [aux_sym_STR_LBRACE] = "STR_{",
    [aux_sym_STR_RBRACE] = "STR_}",
    [aux_sym_STR_STAR] = "STR_*",
    [aux_sym_STR_map] = "STR_map",
    [aux_sym_STR_LBRACK] = "STR_[",
    [aux_sym_STR_RBRACK] = "STR_]",
    [aux_sym_STR_struct] = "STR_struct",
    [aux_sym_STR_interface] = "STR_interface",
    [aux_sym_STR_return] = "STR_return",
    [aux_sym_STR_COMMA] = "STR_,",
    [aux_sym_STR_COLON_EQ] = "STR_:=",
    [aux_sym_STR_for] = "STR_for",
    [aux_sym_STR_range] = "STR_range",
    [aux_sym_STR_if] = "STR_if",
    [aux_sym_STR_else] = "STR_else",
    [aux_sym_STR_DOT] = "STR_.",
    [aux_sym_STR_SLASH] = "STR_/",
    [aux_sym_STR_PLUS] = "STR_+",
    [aux_sym_STR_DASH] = "STR_-",
    [aux_sym_STR_PIPE_PIPE] = "STR_||",
    [aux_sym_STR_AMP_AMP] = "STR_&&",
    [aux_sym_STR_EQ_EQ] = "STR_==",
    [aux_sym_STR_LT_EQ] = "STR_<=",
    [aux_sym_STR_LT] = "STR_<",
    [aux_sym_STR_GT_EQ] = "STR_>=",
    [aux_sym_STR_GT] = "STR_>",
    [aux_sym_STR_BANG] = "STR_!",
};

static const int ts_hidden_symbol_flags[SYMBOL_COUNT] = {
    [sym__func_signature] = 1,
    [sym__line_break] = 1,
    [sym__identifier] = 1,
    [aux_sym_program_repeat0] = 1,
    [aux_sym_program_repeat1] = 1,
    [aux_sym_imports_block_repeat0] = 1,
    [aux_sym_block_statement_repeat0] = 1,
    [aux_sym_struct_type_repeat0] = 1,
    [aux_sym_interface_type_repeat0] = 1,
    [aux_sym_return_statement_repeat0] = 1,
    [aux_sym_declaration_statement_repeat0] = 1,
    [aux_sym_call_expression_repeat0] = 1,
    [aux_sym__func_signature_repeat0] = 1,
    [aux_sym__func_signature_repeat1] = 1,
    [aux_sym__func_signature_repeat2] = 1,
    [aux_sym__func_signature_repeat3] = 1,
    [aux_sym__func_signature_repeat4] = 1,
    [aux_sym_STR_package] = 1,
    [aux_sym_STR_import] = 1,
    [aux_sym_STR_LPAREN] = 1,
    [aux_sym_STR_RPAREN] = 1,
    [aux_sym_STR_type] = 1,
    [aux_sym_STR_SEMI] = 1,
    [aux_sym_STR_var] = 1,
    [aux_sym_STR_EQ] = 1,
    [aux_sym_STR_func] = 1,
    [aux_sym_STR_LBRACE] = 1,
    [aux_sym_STR_RBRACE] = 1,
    [aux_sym_STR_STAR] = 1,
    [aux_sym_STR_map] = 1,
    [aux_sym_STR_LBRACK] = 1,
    [aux_sym_STR_RBRACK] = 1,
    [aux_sym_STR_struct] = 1,
    [aux_sym_STR_interface] = 1,
    [aux_sym_STR_return] = 1,
    [aux_sym_STR_COMMA] = 1,
    [aux_sym_STR_COLON_EQ] = 1,
    [aux_sym_STR_for] = 1,
    [aux_sym_STR_range] = 1,
    [aux_sym_STR_if] = 1,
    [aux_sym_STR_else] = 1,
    [aux_sym_STR_DOT] = 1,
    [aux_sym_STR_SLASH] = 1,
    [aux_sym_STR_PLUS] = 1,
    [aux_sym_STR_DASH] = 1,
    [aux_sym_STR_PIPE_PIPE] = 1,
    [aux_sym_STR_AMP_AMP] = 1,
    [aux_sym_STR_EQ_EQ] = 1,
    [aux_sym_STR_LT_EQ] = 1,
    [aux_sym_STR_LT] = 1,
    [aux_sym_STR_GT_EQ] = 1,
    [aux_sym_STR_GT] = 1,
    [aux_sym_STR_BANG] = 1,
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
            ACCEPT_TOKEN(aux_sym_STR_package);
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
            ACCEPT_TOKEN(aux_sym_STR_func);
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
            ACCEPT_TOKEN(aux_sym_STR_import);
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
            ACCEPT_TOKEN(aux_sym_STR_type);
        case 29:
            if (lookahead == 'a')
                ADVANCE(30);
            LEX_ERROR();
        case 30:
            if (lookahead == 'r')
                ADVANCE(31);
            LEX_ERROR();
        case 31:
            ACCEPT_TOKEN(aux_sym_STR_var);
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
            ACCEPT_TOKEN(aux_sym_STR_LPAREN);
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
            ACCEPT_TOKEN(aux_sym_STR_LBRACE);
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
            ACCEPT_TOKEN(aux_sym_STR_RPAREN);
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
            ACCEPT_TOKEN(aux_sym_STR_STAR);
        case 48:
            ACCEPT_TOKEN(aux_sym_STR_COMMA);
        case 49:
            ACCEPT_TOKEN(aux_sym_STR_LBRACK);
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
            ACCEPT_TOKEN(aux_sym_STR_interface);
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
            ACCEPT_TOKEN(aux_sym_STR_map);
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
            ACCEPT_TOKEN(aux_sym_STR_struct);
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
            ACCEPT_TOKEN(aux_sym_STR_RBRACK);
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
            ACCEPT_TOKEN(aux_sym_STR_RBRACE);
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
            ACCEPT_TOKEN(aux_sym_STR_SEMI);
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
            ACCEPT_TOKEN(aux_sym_STR_BANG);
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
            ACCEPT_TOKEN(aux_sym_STR_COLON_EQ);
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
            ACCEPT_TOKEN(aux_sym_STR_for);
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
            ACCEPT_TOKEN(aux_sym_STR_if);
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
            ACCEPT_TOKEN(aux_sym_STR_return);
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
            ACCEPT_TOKEN(aux_sym_STR_var);
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
            ACCEPT_TOKEN(aux_sym_STR_AMP_AMP);
        case 106:
            ACCEPT_TOKEN(aux_sym_STR_PLUS);
        case 107:
            ACCEPT_TOKEN(aux_sym_STR_DASH);
        case 108:
            ACCEPT_TOKEN(aux_sym_STR_DOT);
        case 109:
            if (lookahead == '/')
                ADVANCE(4);
            ACCEPT_TOKEN(aux_sym_STR_SLASH);
        case 110:
            if (lookahead == '=')
                ADVANCE(111);
            ACCEPT_TOKEN(aux_sym_STR_LT);
        case 111:
            ACCEPT_TOKEN(aux_sym_STR_LT_EQ);
        case 112:
            if (lookahead == '=')
                ADVANCE(113);
            LEX_ERROR();
        case 113:
            ACCEPT_TOKEN(aux_sym_STR_EQ_EQ);
        case 114:
            if (lookahead == '=')
                ADVANCE(115);
            ACCEPT_TOKEN(aux_sym_STR_GT);
        case 115:
            ACCEPT_TOKEN(aux_sym_STR_GT_EQ);
        case 116:
            if (lookahead == '|')
                ADVANCE(117);
            LEX_ERROR();
        case 117:
            ACCEPT_TOKEN(aux_sym_STR_PIPE_PIPE);
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
            ACCEPT_TOKEN(aux_sym_STR_else);
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
            ACCEPT_TOKEN(aux_sym_STR_if);
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
            ACCEPT_TOKEN(aux_sym_STR_range);
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
            ACCEPT_TOKEN(aux_sym_STR_EQ);
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
            ACCEPT_TOKEN(aux_sym_STR_EQ);
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
            ACCEPT_TOKEN(aux_sym_STR_func);
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
            ACCEPT_TOKEN(aux_sym_STR_import);
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
            ACCEPT_TOKEN(aux_sym_STR_package);
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
            ACCEPT_TOKEN(aux_sym_STR_range);
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
            ACCEPT_TOKEN(aux_sym_STR_type);
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
    [82] = 46,
    [83] = 69,
    [84] = 72,
    [85] = 32,
    [86] = 46,
    [87] = 72,
    [88] = 69,
    [89] = 71,
    [90] = 71,
    [91] = 32,
    [92] = 32,
    [93] = 69,
    [94] = 71,
    [95] = 76,
    [96] = 76,
    [97] = 69,
    [98] = 71,
    [99] = 76,
    [100] = 79,
    [101] = 32,
    [102] = 32,
    [103] = 69,
    [104] = 69,
    [105] = 71,
    [106] = 76,
    [107] = 71,
    [108] = 79,
    [109] = 32,
    [110] = 32,
    [111] = 69,
    [112] = 71,
    [113] = 69,
    [114] = 78,
    [115] = 76,
    [116] = 72,
    [117] = 72,
    [118] = 78,
    [119] = 69,
    [120] = 69,
    [121] = 76,
    [122] = 76,
    [123] = 76,
    [124] = 72,
    [125] = 73,
    [126] = 74,
    [127] = 42,
    [128] = 42,
    [129] = 76,
    [130] = 78,
    [131] = 76,
    [132] = 76,
    [133] = 76,
    [134] = 78,
    [135] = 76,
    [136] = 76,
    [137] = 72,
    [138] = 76,
    [139] = 72,
    [140] = 74,
    [141] = 74,
    [142] = 74,
    [143] = 72,
    [144] = 73,
    [145] = 74,
    [146] = 42,
    [147] = 42,
    [148] = 76,
    [149] = 78,
    [150] = 74,
    [151] = 74,
    [152] = 76,
    [153] = 78,
    [154] = 74,
    [155] = 74,
    [156] = 72,
    [157] = 74,
    [158] = 72,
    [159] = 74,
    [160] = 72,
    [161] = 74,
    [162] = 74,
    [163] = 72,
    [164] = 76,
    [165] = 76,
    [166] = 78,
    [167] = 72,
    [168] = 69,
    [169] = 72,
    [170] = 74,
    [171] = 72,
    [172] = 69,
    [173] = 69,
    [174] = 69,
    [175] = 71,
    [176] = 68,
    [177] = 32,
    [178] = 32,
    [179] = 69,
    [180] = 71,
    [181] = 42,
    [182] = 42,
    [183] = 69,
    [184] = 71,
    [185] = 42,
    [186] = 68,
    [187] = 32,
    [188] = 32,
    [189] = 69,
    [190] = 69,
    [191] = 71,
    [192] = 42,
    [193] = 71,
    [194] = 68,
    [195] = 32,
    [196] = 32,
    [197] = 69,
    [198] = 71,
    [199] = 69,
    [200] = 80,
    [201] = 82,
    [202] = 82,
    [203] = 82,
    [204] = 82,
    [205] = 103,
    [206] = 103,
    [207] = 118,
    [208] = 78,
    [209] = 118,
    [210] = 32,
    [211] = 80,
    [212] = 119,
    [213] = 120,
    [214] = 32,
    [215] = 120,
    [216] = 120,
    [217] = 103,
    [218] = 103,
    [219] = 121,
    [220] = 121,
    [221] = 121,
    [222] = 120,
    [223] = 121,
    [224] = 122,
    [225] = 127,
    [226] = 82,
    [227] = 120,
    [228] = 32,
    [229] = 120,
    [230] = 120,
    [231] = 120,
    [232] = 120,
    [233] = 121,
    [234] = 121,
    [235] = 121,
    [236] = 121,
    [237] = 121,
    [238] = 121,
    [239] = 78,
    [240] = 122,
    [241] = 122,
    [242] = 128,
    [243] = 128,
    [244] = 128,
    [245] = 121,
    [246] = 120,
    [247] = 128,
    [248] = 71,
    [249] = 127,
    [250] = 121,
    [251] = 120,
    [252] = 120,
    [253] = 32,
    [254] = 120,
    [255] = 120,
    [256] = 120,
    [257] = 120,
    [258] = 128,
    [259] = 128,
    [260] = 128,
    [261] = 128,
    [262] = 128,
    [263] = 128,
    [264] = 71,
    [265] = 128,
    [266] = 128,
    [267] = 128,
    [268] = 71,
    [269] = 128,
    [270] = 128,
    [271] = 121,
    [272] = 129,
    [273] = 82,
    [274] = 82,
    [275] = 78,
    [276] = 82,
    [277] = 82,
    [278] = 132,
    [279] = 132,
    [280] = 32,
    [281] = 133,
    [282] = 120,
    [283] = 121,
    [284] = 82,
    [285] = 139,
    [286] = 139,
    [287] = 133,
    [288] = 120,
    [289] = 121,
    [290] = 82,
    [291] = 103,
    [292] = 140,
    [293] = 127,
    [294] = 120,
    [295] = 32,
    [296] = 120,
    [297] = 120,
    [298] = 120,
    [299] = 120,
    [300] = 103,
    [301] = 103,
    [302] = 103,
    [303] = 103,
    [304] = 103,
    [305] = 103,
    [306] = 128,
    [307] = 103,
    [308] = 71,
    [309] = 103,
    [310] = 103,
    [311] = 141,
    [312] = 141,
    [313] = 142,
    [314] = 141,
    [315] = 120,
    [316] = 141,
    [317] = 143,
    [318] = 80,
    [319] = 127,
    [320] = 120,
    [321] = 120,
    [322] = 32,
    [323] = 120,
    [324] = 120,
    [325] = 120,
    [326] = 120,
    [327] = 141,
    [328] = 141,
    [329] = 141,
    [330] = 141,
    [331] = 141,
    [332] = 141,
    [333] = 80,
    [334] = 141,
    [335] = 128,
    [336] = 141,
    [337] = 71,
    [338] = 141,
    [339] = 141,
    [340] = 142,
    [341] = 144,
    [342] = 144,
    [343] = 146,
    [344] = 146,
    [345] = 146,
    [346] = 120,
    [347] = 72,
    [348] = 73,
    [349] = 74,
    [350] = 42,
    [351] = 42,
    [352] = 76,
    [353] = 78,
    [354] = 146,
    [355] = 146,
    [356] = 76,
    [357] = 78,
    [358] = 146,
    [359] = 146,
    [360] = 72,
    [361] = 146,
    [362] = 72,
    [363] = 74,
    [364] = 72,
    [365] = 146,
    [366] = 146,
    [367] = 103,
    [368] = 140,
    [369] = 147,
    [370] = 120,
    [371] = 103,
    [372] = 140,
    [373] = 80,
    [374] = 139,
    [375] = 32,
    [376] = 120,
    [377] = 103,
    [378] = 140,
    [379] = 132,
    [380] = 132,
    [381] = 139,
    [382] = 120,
    [383] = 103,
    [384] = 140,
    [385] = 140,
    [386] = 78,
    [387] = 148,
    [388] = 144,
    [389] = 146,
    [390] = 120,
    [391] = 103,
    [392] = 149,
    [393] = 150,
    [394] = 120,
    [395] = 103,
    [396] = 149,
    [397] = 72,
    [398] = 72,
    [399] = 80,
    [400] = 80,
    [401] = 80,
    [402] = 72,
    [403] = 73,
    [404] = 74,
    [405] = 42,
    [406] = 42,
    [407] = 76,
    [408] = 78,
    [409] = 80,
    [410] = 80,
    [411] = 76,
    [412] = 78,
    [413] = 80,
    [414] = 80,
    [415] = 72,
    [416] = 80,
    [417] = 72,
    [418] = 74,
    [419] = 72,
    [420] = 80,
    [421] = 80,
    [422] = 148,
    [423] = 14,
    [424] = 14,
    [425] = 151,
    [426] = 151,
    [427] = 71,
    [428] = 151,
    [429] = 14,
    [430] = 14,
    [431] = 71,
    [432] = 12,
    [433] = 12,
    [434] = 34,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = SHIFT(1),
        [sym_package_directive] = SHIFT(2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_package] = SHIFT(3),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [2] = {
        [sym_imports_block] = SHIFT(6),
        [sym_declaration] = SHIFT(7),
        [sym_type_declaration] = SHIFT(8),
        [sym_var_declaration] = SHIFT(8),
        [sym_func_declaration] = SHIFT(8),
        [ts_builtin_sym_end] = REDUCE(sym_program, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat0] = SHIFT(9),
        [aux_sym_program_repeat1] = SHIFT(10),
        [aux_sym_STR_import] = SHIFT(11),
        [aux_sym_STR_type] = SHIFT(12),
        [aux_sym_STR_var] = SHIFT(13),
        [aux_sym_STR_func] = SHIFT(14),
    },
    [3] = {
        [sym_package_name] = SHIFT(4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(5),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [4] = {
        [sym_imports_block] = REDUCE(sym_package_directive, 2),
        [sym_declaration] = REDUCE(sym_package_directive, 2),
        [sym_type_declaration] = REDUCE(sym_package_directive, 2),
        [sym_var_declaration] = REDUCE(sym_package_directive, 2),
        [sym_func_declaration] = REDUCE(sym_package_directive, 2),
        [ts_builtin_sym_end] = REDUCE(sym_package_directive, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat0] = REDUCE(sym_package_directive, 2),
        [aux_sym_program_repeat1] = REDUCE(sym_package_directive, 2),
        [aux_sym_STR_import] = REDUCE(sym_package_directive, 2),
        [aux_sym_STR_type] = REDUCE(sym_package_directive, 2),
        [aux_sym_STR_var] = REDUCE(sym_package_directive, 2),
        [aux_sym_STR_func] = REDUCE(sym_package_directive, 2),
    },
    [5] = {
        [sym_imports_block] = REDUCE(sym_package_name, 1),
        [sym_declaration] = REDUCE(sym_package_name, 1),
        [sym_type_declaration] = REDUCE(sym_package_name, 1),
        [sym_var_declaration] = REDUCE(sym_package_name, 1),
        [sym_func_declaration] = REDUCE(sym_package_name, 1),
        [ts_builtin_sym_end] = REDUCE(sym_package_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat0] = REDUCE(sym_package_name, 1),
        [aux_sym_program_repeat1] = REDUCE(sym_package_name, 1),
        [aux_sym_STR_import] = REDUCE(sym_package_name, 1),
        [aux_sym_STR_type] = REDUCE(sym_package_name, 1),
        [aux_sym_STR_var] = REDUCE(sym_package_name, 1),
        [aux_sym_STR_func] = REDUCE(sym_package_name, 1),
    },
    [6] = {
        [sym_imports_block] = SHIFT(6),
        [sym_declaration] = REDUCE(aux_sym_program_repeat0, 1),
        [sym_type_declaration] = REDUCE(aux_sym_program_repeat0, 1),
        [sym_var_declaration] = REDUCE(aux_sym_program_repeat0, 1),
        [sym_func_declaration] = REDUCE(aux_sym_program_repeat0, 1),
        [ts_builtin_sym_end] = REDUCE(aux_sym_program_repeat0, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat0] = SHIFT(434),
        [aux_sym_program_repeat1] = REDUCE(aux_sym_program_repeat0, 1),
        [aux_sym_STR_import] = SHIFT(11),
        [aux_sym_STR_type] = REDUCE(aux_sym_program_repeat0, 1),
        [aux_sym_STR_var] = REDUCE(aux_sym_program_repeat0, 1),
        [aux_sym_STR_func] = REDUCE(aux_sym_program_repeat0, 1),
    },
    [7] = {
        [sym_declaration] = SHIFT(7),
        [sym_type_declaration] = SHIFT(8),
        [sym_var_declaration] = SHIFT(8),
        [sym_func_declaration] = SHIFT(8),
        [ts_builtin_sym_end] = REDUCE(aux_sym_program_repeat1, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = SHIFT(433),
        [aux_sym_STR_type] = SHIFT(12),
        [aux_sym_STR_var] = SHIFT(13),
        [aux_sym_STR_func] = SHIFT(14),
    },
    [8] = {
        [sym_declaration] = REDUCE(sym_declaration, 1),
        [sym_type_declaration] = REDUCE(sym_declaration, 1),
        [sym_var_declaration] = REDUCE(sym_declaration, 1),
        [sym_func_declaration] = REDUCE(sym_declaration, 1),
        [ts_builtin_sym_end] = REDUCE(sym_declaration, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_declaration, 1),
        [aux_sym_STR_type] = REDUCE(sym_declaration, 1),
        [aux_sym_STR_var] = REDUCE(sym_declaration, 1),
        [aux_sym_STR_func] = REDUCE(sym_declaration, 1),
    },
    [9] = {
        [sym_declaration] = SHIFT(7),
        [sym_type_declaration] = SHIFT(8),
        [sym_var_declaration] = SHIFT(8),
        [sym_func_declaration] = SHIFT(8),
        [ts_builtin_sym_end] = REDUCE(sym_program, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = SHIFT(432),
        [aux_sym_STR_type] = SHIFT(12),
        [aux_sym_STR_var] = SHIFT(13),
        [aux_sym_STR_func] = SHIFT(14),
    },
    [10] = {
        [ts_builtin_sym_end] = REDUCE(sym_program, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [11] = {
        [sym_package_import] = SHIFT(423),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(424),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(425),
    },
    [12] = {
        [sym_type_name] = SHIFT(397),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(398),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [13] = {
        [sym_var_name] = SHIFT(388),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(342),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [14] = {
        [sym_var_name] = SHIFT(15),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [15] = {
        [sym__func_signature] = SHIFT(17),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(18),
    },
    [16] = {
        [sym__func_signature] = REDUCE(sym_var_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_var_name, 1),
    },
    [17] = {
        [sym_block_statement] = SHIFT(200),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(201),
    },
    [18] = {
        [sym_var_name] = SHIFT(19),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(20),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(21),
    },
    [19] = {
        [sym_type_expression] = SHIFT(44),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat0] = SHIFT(47),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
        [aux_sym_STR_COMMA] = SHIFT(53),
    },
    [20] = {
        [sym_type_expression] = REDUCE(sym_var_name, 1),
        [sym_pointer_type] = REDUCE(sym_var_name, 1),
        [sym_map_type] = REDUCE(sym_var_name, 1),
        [sym_slice_type] = REDUCE(sym_var_name, 1),
        [sym_struct_type] = REDUCE(sym_var_name, 1),
        [sym_interface_type] = REDUCE(sym_var_name, 1),
        [sym_type_name] = REDUCE(sym_var_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat0] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_map] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LBRACK] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_struct] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_interface] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
    },
    [21] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 2),
        [sym_type_name] = SHIFT(22),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(24),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 2),
    },
    [22] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 3),
    },
    [23] = {
        [sym_block_statement] = REDUCE(sym_type_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym_type_name, 1),
    },
    [24] = {
        [sym_var_name] = SHIFT(25),
        [sym_type_name] = SHIFT(26),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [25] = {
        [sym_type_name] = SHIFT(35),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [26] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(28),
        [aux_sym_STR_RPAREN] = SHIFT(29),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [27] = {
        [sym_type_name] = REDUCE(sym_var_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_type_name, 1),
    },
    [28] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(34),
    },
    [29] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 5),
    },
    [30] = {
        [sym_type_name] = SHIFT(31),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(32),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [31] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(33),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat4, 2),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [32] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_type_name, 1),
    },
    [33] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat4, 3),
    },
    [34] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 6),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 6),
    },
    [35] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(37),
        [aux_sym_STR_RPAREN] = SHIFT(34),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [36] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_type_name, 1),
    },
    [37] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(43),
    },
    [38] = {
        [sym_var_name] = SHIFT(39),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(40),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [39] = {
        [sym_type_name] = SHIFT(41),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [40] = {
        [sym_type_name] = REDUCE(sym_var_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [41] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(42),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat3, 3),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [42] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat3, 4),
    },
    [43] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 7),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 7),
    },
    [44] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(193),
        [aux_sym_STR_RPAREN] = SHIFT(194),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [45] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_type_expression, 1),
    },
    [46] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_type_name, 1),
    },
    [47] = {
        [sym_type_expression] = SHIFT(174),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
    },
    [48] = {
        [sym_type_expression] = SHIFT(173),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
    },
    [49] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(169),
    },
    [50] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(167),
    },
    [51] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(115),
    },
    [52] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(56),
    },
    [53] = {
        [sym_var_name] = SHIFT(54),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(20),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [54] = {
        [sym_type_expression] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [sym_pointer_type] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [sym_map_type] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [sym_slice_type] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [sym_struct_type] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [sym_interface_type] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [sym_type_name] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat0] = SHIFT(55),
        [aux_sym_STR_STAR] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [aux_sym_STR_map] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [aux_sym_STR_LBRACK] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [aux_sym_STR_struct] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [aux_sym_STR_interface] = REDUCE(aux_sym__func_signature_repeat0, 2),
        [aux_sym_STR_COMMA] = SHIFT(53),
    },
    [55] = {
        [sym_type_expression] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [sym_pointer_type] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [sym_map_type] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [sym_slice_type] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [sym_struct_type] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [sym_interface_type] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [sym_type_name] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [aux_sym_STR_map] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [aux_sym_STR_LBRACK] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [aux_sym_STR_struct] = REDUCE(aux_sym__func_signature_repeat0, 3),
        [aux_sym_STR_interface] = REDUCE(aux_sym__func_signature_repeat0, 3),
    },
    [56] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(58),
        [aux_sym_STR_RBRACE] = SHIFT(59),
    },
    [57] = {
        [sym__func_signature] = SHIFT(61),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(62),
    },
    [58] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(60),
    },
    [59] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_interface_type, 3),
    },
    [60] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_RPAREN] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_interface_type, 4),
    },
    [61] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(114),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_interface_type_repeat0, 2),
    },
    [62] = {
        [sym_var_name] = SHIFT(63),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(20),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(64),
    },
    [63] = {
        [sym_type_expression] = SHIFT(75),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat0] = SHIFT(76),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
        [aux_sym_STR_COMMA] = SHIFT(53),
    },
    [64] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 2),
        [sym_type_name] = SHIFT(65),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE_FRAGILE(sym__func_signature, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE_FRAGILE(sym__func_signature, 2),
        [aux_sym_STR_LPAREN] = SHIFT(66),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 2),
    },
    [65] = {
        [sym_var_name] = REDUCE(sym__func_signature, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 3),
    },
    [66] = {
        [sym_var_name] = SHIFT(67),
        [sym_type_name] = SHIFT(68),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [67] = {
        [sym_type_name] = SHIFT(72),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [68] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(69),
        [aux_sym_STR_RPAREN] = SHIFT(70),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [69] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(71),
    },
    [70] = {
        [sym_var_name] = REDUCE(sym__func_signature, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 5),
    },
    [71] = {
        [sym_var_name] = REDUCE(sym__func_signature, 6),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 6),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 6),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 6),
    },
    [72] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(73),
        [aux_sym_STR_RPAREN] = SHIFT(71),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [73] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(74),
    },
    [74] = {
        [sym_var_name] = REDUCE(sym__func_signature, 7),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 7),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 7),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 7),
    },
    [75] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(107),
        [aux_sym_STR_RPAREN] = SHIFT(108),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [76] = {
        [sym_type_expression] = SHIFT(77),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
    },
    [77] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(78),
        [aux_sym_STR_RPAREN] = SHIFT(79),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [78] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(100),
    },
    [79] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 5),
        [sym_type_name] = SHIFT(71),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE_FRAGILE(sym__func_signature, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE_FRAGILE(sym__func_signature, 5),
        [aux_sym_STR_LPAREN] = SHIFT(91),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 5),
    },
    [80] = {
        [sym_var_name] = SHIFT(81),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(82),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [81] = {
        [sym_type_expression] = SHIFT(83),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = SHIFT(84),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
        [aux_sym_STR_COMMA] = SHIFT(85),
    },
    [82] = {
        [sym_type_expression] = REDUCE(sym_var_name, 1),
        [sym_pointer_type] = REDUCE(sym_var_name, 1),
        [sym_map_type] = REDUCE(sym_var_name, 1),
        [sym_slice_type] = REDUCE(sym_var_name, 1),
        [sym_struct_type] = REDUCE(sym_var_name, 1),
        [sym_interface_type] = REDUCE(sym_var_name, 1),
        [sym_type_name] = REDUCE(sym_var_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_map] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LBRACK] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_struct] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_interface] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
    },
    [83] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(90),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 3),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [84] = {
        [sym_type_expression] = SHIFT(88),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
    },
    [85] = {
        [sym_var_name] = SHIFT(86),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(82),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [86] = {
        [sym_type_expression] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [sym_pointer_type] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [sym_map_type] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [sym_slice_type] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [sym_struct_type] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [sym_interface_type] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [sym_type_name] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = SHIFT(87),
        [aux_sym_STR_STAR] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_map] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_LBRACK] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_struct] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_interface] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_COMMA] = SHIFT(85),
    },
    [87] = {
        [sym_type_expression] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [sym_pointer_type] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [sym_map_type] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [sym_slice_type] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [sym_struct_type] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [sym_interface_type] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [sym_type_name] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [aux_sym_STR_map] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [aux_sym_STR_LBRACK] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [aux_sym_STR_struct] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [aux_sym_STR_interface] = REDUCE(aux_sym__func_signature_repeat1, 3),
    },
    [88] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(89),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 4),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [89] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 5),
    },
    [90] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 4),
    },
    [91] = {
        [sym_var_name] = SHIFT(92),
        [sym_type_name] = SHIFT(93),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [92] = {
        [sym_type_name] = SHIFT(97),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [93] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(94),
        [aux_sym_STR_RPAREN] = SHIFT(95),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [94] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(96),
    },
    [95] = {
        [sym_var_name] = REDUCE(sym__func_signature, 8),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 8),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 8),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 8),
    },
    [96] = {
        [sym_var_name] = REDUCE(sym__func_signature, 9),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 9),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 9),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 9),
    },
    [97] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(98),
        [aux_sym_STR_RPAREN] = SHIFT(96),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [98] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(99),
    },
    [99] = {
        [sym_var_name] = REDUCE(sym__func_signature, 10),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 10),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 10),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 10),
    },
    [100] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 6),
        [sym_type_name] = SHIFT(74),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE_FRAGILE(sym__func_signature, 6),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE_FRAGILE(sym__func_signature, 6),
        [aux_sym_STR_LPAREN] = SHIFT(101),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 6),
    },
    [101] = {
        [sym_var_name] = SHIFT(102),
        [sym_type_name] = SHIFT(103),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [102] = {
        [sym_type_name] = SHIFT(104),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [103] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(98),
        [aux_sym_STR_RPAREN] = SHIFT(96),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [104] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(105),
        [aux_sym_STR_RPAREN] = SHIFT(99),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [105] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(106),
    },
    [106] = {
        [sym_var_name] = REDUCE(sym__func_signature, 11),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 11),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 11),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 11),
    },
    [107] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(79),
    },
    [108] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 4),
        [sym_type_name] = SHIFT(70),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE_FRAGILE(sym__func_signature, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE_FRAGILE(sym__func_signature, 4),
        [aux_sym_STR_LPAREN] = SHIFT(109),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 4),
    },
    [109] = {
        [sym_var_name] = SHIFT(110),
        [sym_type_name] = SHIFT(111),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [110] = {
        [sym_type_name] = SHIFT(113),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [111] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(112),
        [aux_sym_STR_RPAREN] = SHIFT(74),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [112] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(95),
    },
    [113] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(94),
        [aux_sym_STR_RPAREN] = SHIFT(95),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [114] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_interface_type_repeat0, 3),
    },
    [115] = {
        [sym_var_name] = SHIFT(116),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(117),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(118),
        [aux_sym_STR_RBRACE] = SHIFT(119),
    },
    [116] = {
        [sym_type_expression] = SHIFT(121),
        [sym_pointer_type] = SHIFT(122),
        [sym_map_type] = SHIFT(122),
        [sym_slice_type] = SHIFT(122),
        [sym_struct_type] = SHIFT(122),
        [sym_interface_type] = SHIFT(122),
        [sym_type_name] = SHIFT(122),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(123),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(124),
        [aux_sym_STR_map] = SHIFT(125),
        [aux_sym_STR_LBRACK] = SHIFT(126),
        [aux_sym_STR_struct] = SHIFT(127),
        [aux_sym_STR_interface] = SHIFT(128),
    },
    [117] = {
        [sym_type_expression] = REDUCE(sym_var_name, 1),
        [sym_pointer_type] = REDUCE(sym_var_name, 1),
        [sym_map_type] = REDUCE(sym_var_name, 1),
        [sym_slice_type] = REDUCE(sym_var_name, 1),
        [sym_struct_type] = REDUCE(sym_var_name, 1),
        [sym_interface_type] = REDUCE(sym_var_name, 1),
        [sym_type_name] = REDUCE(sym_var_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_map] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LBRACK] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_struct] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_interface] = REDUCE(sym_var_name, 1),
    },
    [118] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(120),
    },
    [119] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_struct_type, 3),
    },
    [120] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_RPAREN] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_struct_type, 4),
    },
    [121] = {
        [sym_var_name] = SHIFT(116),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(117),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(166),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_struct_type_repeat0, 2),
    },
    [122] = {
        [sym_var_name] = REDUCE(sym_type_expression, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_type_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_type_expression, 1),
    },
    [123] = {
        [sym_var_name] = REDUCE(sym_type_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_type_name, 1),
    },
    [124] = {
        [sym_type_expression] = SHIFT(165),
        [sym_pointer_type] = SHIFT(122),
        [sym_map_type] = SHIFT(122),
        [sym_slice_type] = SHIFT(122),
        [sym_struct_type] = SHIFT(122),
        [sym_interface_type] = SHIFT(122),
        [sym_type_name] = SHIFT(122),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(123),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(124),
        [aux_sym_STR_map] = SHIFT(125),
        [aux_sym_STR_LBRACK] = SHIFT(126),
        [aux_sym_STR_struct] = SHIFT(127),
        [aux_sym_STR_interface] = SHIFT(128),
    },
    [125] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(139),
    },
    [126] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(137),
    },
    [127] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(133),
    },
    [128] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(129),
    },
    [129] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(130),
        [aux_sym_STR_RBRACE] = SHIFT(131),
    },
    [130] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(132),
    },
    [131] = {
        [sym_var_name] = REDUCE(sym_interface_type, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_interface_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_interface_type, 3),
    },
    [132] = {
        [sym_var_name] = REDUCE(sym_interface_type, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_interface_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_interface_type, 4),
    },
    [133] = {
        [sym_var_name] = SHIFT(116),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(117),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(134),
        [aux_sym_STR_RBRACE] = SHIFT(135),
    },
    [134] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(136),
    },
    [135] = {
        [sym_var_name] = REDUCE(sym_struct_type, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_struct_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_struct_type, 3),
    },
    [136] = {
        [sym_var_name] = REDUCE(sym_struct_type, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_struct_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_struct_type, 4),
    },
    [137] = {
        [sym_type_expression] = SHIFT(138),
        [sym_pointer_type] = SHIFT(122),
        [sym_map_type] = SHIFT(122),
        [sym_slice_type] = SHIFT(122),
        [sym_struct_type] = SHIFT(122),
        [sym_interface_type] = SHIFT(122),
        [sym_type_name] = SHIFT(122),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(123),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(124),
        [aux_sym_STR_map] = SHIFT(125),
        [aux_sym_STR_LBRACK] = SHIFT(126),
        [aux_sym_STR_struct] = SHIFT(127),
        [aux_sym_STR_interface] = SHIFT(128),
    },
    [138] = {
        [sym_var_name] = REDUCE(sym_slice_type, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_slice_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_slice_type, 3),
    },
    [139] = {
        [sym_type_expression] = SHIFT(140),
        [sym_pointer_type] = SHIFT(141),
        [sym_map_type] = SHIFT(141),
        [sym_slice_type] = SHIFT(141),
        [sym_struct_type] = SHIFT(141),
        [sym_interface_type] = SHIFT(141),
        [sym_type_name] = SHIFT(141),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(142),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(143),
        [aux_sym_STR_map] = SHIFT(144),
        [aux_sym_STR_LBRACK] = SHIFT(145),
        [aux_sym_STR_struct] = SHIFT(146),
        [aux_sym_STR_interface] = SHIFT(147),
    },
    [140] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(163),
    },
    [141] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_type_expression, 1),
    },
    [142] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_type_name, 1),
    },
    [143] = {
        [sym_type_expression] = SHIFT(162),
        [sym_pointer_type] = SHIFT(141),
        [sym_map_type] = SHIFT(141),
        [sym_slice_type] = SHIFT(141),
        [sym_struct_type] = SHIFT(141),
        [sym_interface_type] = SHIFT(141),
        [sym_type_name] = SHIFT(141),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(142),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(143),
        [aux_sym_STR_map] = SHIFT(144),
        [aux_sym_STR_LBRACK] = SHIFT(145),
        [aux_sym_STR_struct] = SHIFT(146),
        [aux_sym_STR_interface] = SHIFT(147),
    },
    [144] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(158),
    },
    [145] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(156),
    },
    [146] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(152),
    },
    [147] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(148),
    },
    [148] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(149),
        [aux_sym_STR_RBRACE] = SHIFT(150),
    },
    [149] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(151),
    },
    [150] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_interface_type, 3),
    },
    [151] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_interface_type, 4),
    },
    [152] = {
        [sym_var_name] = SHIFT(116),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(117),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(153),
        [aux_sym_STR_RBRACE] = SHIFT(154),
    },
    [153] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(155),
    },
    [154] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_struct_type, 3),
    },
    [155] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_struct_type, 4),
    },
    [156] = {
        [sym_type_expression] = SHIFT(157),
        [sym_pointer_type] = SHIFT(141),
        [sym_map_type] = SHIFT(141),
        [sym_slice_type] = SHIFT(141),
        [sym_struct_type] = SHIFT(141),
        [sym_interface_type] = SHIFT(141),
        [sym_type_name] = SHIFT(141),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(142),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(143),
        [aux_sym_STR_map] = SHIFT(144),
        [aux_sym_STR_LBRACK] = SHIFT(145),
        [aux_sym_STR_struct] = SHIFT(146),
        [aux_sym_STR_interface] = SHIFT(147),
    },
    [157] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_slice_type, 3),
    },
    [158] = {
        [sym_type_expression] = SHIFT(159),
        [sym_pointer_type] = SHIFT(141),
        [sym_map_type] = SHIFT(141),
        [sym_slice_type] = SHIFT(141),
        [sym_struct_type] = SHIFT(141),
        [sym_interface_type] = SHIFT(141),
        [sym_type_name] = SHIFT(141),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(142),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(143),
        [aux_sym_STR_map] = SHIFT(144),
        [aux_sym_STR_LBRACK] = SHIFT(145),
        [aux_sym_STR_struct] = SHIFT(146),
        [aux_sym_STR_interface] = SHIFT(147),
    },
    [159] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(160),
    },
    [160] = {
        [sym_type_expression] = SHIFT(161),
        [sym_pointer_type] = SHIFT(141),
        [sym_map_type] = SHIFT(141),
        [sym_slice_type] = SHIFT(141),
        [sym_struct_type] = SHIFT(141),
        [sym_interface_type] = SHIFT(141),
        [sym_type_name] = SHIFT(141),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(142),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(143),
        [aux_sym_STR_map] = SHIFT(144),
        [aux_sym_STR_LBRACK] = SHIFT(145),
        [aux_sym_STR_struct] = SHIFT(146),
        [aux_sym_STR_interface] = SHIFT(147),
    },
    [161] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_map_type, 5),
    },
    [162] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_pointer_type, 2),
    },
    [163] = {
        [sym_type_expression] = SHIFT(164),
        [sym_pointer_type] = SHIFT(122),
        [sym_map_type] = SHIFT(122),
        [sym_slice_type] = SHIFT(122),
        [sym_struct_type] = SHIFT(122),
        [sym_interface_type] = SHIFT(122),
        [sym_type_name] = SHIFT(122),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(123),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(124),
        [aux_sym_STR_map] = SHIFT(125),
        [aux_sym_STR_LBRACK] = SHIFT(126),
        [aux_sym_STR_struct] = SHIFT(127),
        [aux_sym_STR_interface] = SHIFT(128),
    },
    [164] = {
        [sym_var_name] = REDUCE(sym_map_type, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_map_type, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym_map_type, 5),
    },
    [165] = {
        [sym_var_name] = REDUCE(sym_pointer_type, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_pointer_type, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_pointer_type, 2),
    },
    [166] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_struct_type_repeat0, 3),
    },
    [167] = {
        [sym_type_expression] = SHIFT(168),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
    },
    [168] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_slice_type, 3),
    },
    [169] = {
        [sym_type_expression] = SHIFT(170),
        [sym_pointer_type] = SHIFT(141),
        [sym_map_type] = SHIFT(141),
        [sym_slice_type] = SHIFT(141),
        [sym_struct_type] = SHIFT(141),
        [sym_interface_type] = SHIFT(141),
        [sym_type_name] = SHIFT(141),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(142),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(143),
        [aux_sym_STR_map] = SHIFT(144),
        [aux_sym_STR_LBRACK] = SHIFT(145),
        [aux_sym_STR_struct] = SHIFT(146),
        [aux_sym_STR_interface] = SHIFT(147),
    },
    [170] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(171),
    },
    [171] = {
        [sym_type_expression] = SHIFT(172),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
    },
    [172] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_RPAREN] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_COMMA] = REDUCE(sym_map_type, 5),
    },
    [173] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_RPAREN] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_COMMA] = REDUCE(sym_pointer_type, 2),
    },
    [174] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(175),
        [aux_sym_STR_RPAREN] = SHIFT(176),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [175] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(186),
    },
    [176] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 5),
        [sym_type_name] = SHIFT(34),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(177),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 5),
    },
    [177] = {
        [sym_var_name] = SHIFT(178),
        [sym_type_name] = SHIFT(179),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [178] = {
        [sym_type_name] = SHIFT(183),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [179] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(180),
        [aux_sym_STR_RPAREN] = SHIFT(181),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [180] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(182),
    },
    [181] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 8),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 8),
    },
    [182] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 9),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 9),
    },
    [183] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(184),
        [aux_sym_STR_RPAREN] = SHIFT(182),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [184] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(185),
    },
    [185] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 10),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 10),
    },
    [186] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 6),
        [sym_type_name] = SHIFT(43),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(187),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 6),
    },
    [187] = {
        [sym_var_name] = SHIFT(188),
        [sym_type_name] = SHIFT(189),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [188] = {
        [sym_type_name] = SHIFT(190),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [189] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(184),
        [aux_sym_STR_RPAREN] = SHIFT(182),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [190] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(191),
        [aux_sym_STR_RPAREN] = SHIFT(185),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [191] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(192),
    },
    [192] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 11),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 11),
    },
    [193] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(176),
    },
    [194] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 4),
        [sym_type_name] = SHIFT(29),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(195),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 4),
    },
    [195] = {
        [sym_var_name] = SHIFT(196),
        [sym_type_name] = SHIFT(197),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [196] = {
        [sym_type_name] = SHIFT(199),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [197] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(198),
        [aux_sym_STR_RPAREN] = SHIFT(43),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [198] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(181),
    },
    [199] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(180),
        [aux_sym_STR_RPAREN] = SHIFT(181),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [200] = {
        [sym__line_break] = SHIFT(387),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(387),
    },
    [201] = {
        [sym_var_declaration] = SHIFT(202),
        [sym_statement] = SHIFT(203),
        [sym_return_statement] = SHIFT(204),
        [sym_declaration_statement] = SHIFT(204),
        [sym_range_statement] = SHIFT(204),
        [sym_if_statement] = SHIFT(204),
        [sym_expression_statement] = SHIFT(204),
        [sym_expression] = SHIFT(205),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(208),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(209),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = SHIFT(208),
        [aux_sym_STR_var] = SHIFT(210),
        [aux_sym_STR_RBRACE] = SHIFT(211),
        [aux_sym_STR_return] = SHIFT(212),
        [aux_sym_STR_COLON_EQ] = SHIFT(213),
        [aux_sym_STR_for] = SHIFT(214),
        [aux_sym_STR_if] = SHIFT(215),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [202] = {
        [sym_var_declaration] = REDUCE(sym_declaration_statement, 1),
        [sym_statement] = REDUCE(sym_declaration_statement, 1),
        [sym_return_statement] = REDUCE(sym_declaration_statement, 1),
        [sym_declaration_statement] = REDUCE(sym_declaration_statement, 1),
        [sym_range_statement] = REDUCE(sym_declaration_statement, 1),
        [sym_if_statement] = REDUCE(sym_declaration_statement, 1),
        [sym_expression_statement] = REDUCE(sym_declaration_statement, 1),
        [sym_expression] = REDUCE(sym_declaration_statement, 1),
        [sym_call_expression] = REDUCE(sym_declaration_statement, 1),
        [sym_selector_expression] = REDUCE(sym_declaration_statement, 1),
        [sym_math_op] = REDUCE(sym_declaration_statement, 1),
        [sym_bool_op] = REDUCE(sym_declaration_statement, 1),
        [sym_var_name] = REDUCE(sym_declaration_statement, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_declaration_statement, 1),
        [sym__identifier] = REDUCE(sym_declaration_statement, 1),
        [sym_number] = REDUCE(sym_declaration_statement, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_var] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_return] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_for] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_if] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_BANG] = REDUCE(sym_declaration_statement, 1),
    },
    [203] = {
        [sym_var_declaration] = SHIFT(202),
        [sym_statement] = SHIFT(203),
        [sym_return_statement] = SHIFT(204),
        [sym_declaration_statement] = SHIFT(204),
        [sym_range_statement] = SHIFT(204),
        [sym_if_statement] = SHIFT(204),
        [sym_expression_statement] = SHIFT(204),
        [sym_expression] = SHIFT(205),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(209),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = SHIFT(386),
        [aux_sym_STR_var] = SHIFT(210),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_block_statement_repeat0, 1),
        [aux_sym_STR_return] = SHIFT(212),
        [aux_sym_STR_COLON_EQ] = SHIFT(213),
        [aux_sym_STR_for] = SHIFT(214),
        [aux_sym_STR_if] = SHIFT(215),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [204] = {
        [sym_var_declaration] = REDUCE(sym_statement, 1),
        [sym_statement] = REDUCE(sym_statement, 1),
        [sym_return_statement] = REDUCE(sym_statement, 1),
        [sym_declaration_statement] = REDUCE(sym_statement, 1),
        [sym_range_statement] = REDUCE(sym_statement, 1),
        [sym_if_statement] = REDUCE(sym_statement, 1),
        [sym_expression_statement] = REDUCE(sym_statement, 1),
        [sym_expression] = REDUCE(sym_statement, 1),
        [sym_call_expression] = REDUCE(sym_statement, 1),
        [sym_selector_expression] = REDUCE(sym_statement, 1),
        [sym_math_op] = REDUCE(sym_statement, 1),
        [sym_bool_op] = REDUCE(sym_statement, 1),
        [sym_var_name] = REDUCE(sym_statement, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_statement, 1),
        [sym__identifier] = REDUCE(sym_statement, 1),
        [sym_number] = REDUCE(sym_statement, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_statement, 1),
        [aux_sym_STR_var] = REDUCE(sym_statement, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_statement, 1),
        [aux_sym_STR_return] = REDUCE(sym_statement, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_statement, 1),
        [aux_sym_STR_for] = REDUCE(sym_statement, 1),
        [aux_sym_STR_if] = REDUCE(sym_statement, 1),
        [aux_sym_STR_BANG] = REDUCE(sym_statement, 1),
    },
    [205] = {
        [sym__line_break] = SHIFT(385),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(293),
        [aux_sym_STR_SEMI] = SHIFT(385),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = SHIFT(295),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = SHIFT(296),
        [aux_sym_STR_DASH] = SHIFT(296),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(297),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [206] = {
        [sym__line_break] = REDUCE(sym_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SEMI] = REDUCE(sym_expression, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DOT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_expression, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_expression, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT] = REDUCE(sym_expression, 1),
    },
    [207] = {
        [sym__line_break] = REDUCE(sym_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat0] = SHIFT(374),
        [aux_sym_STR_LPAREN] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SEMI] = REDUCE(sym_expression, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_expression, 1),
        [aux_sym_STR_COMMA] = SHIFT(375),
        [aux_sym_STR_COLON_EQ] = SHIFT(376),
        [aux_sym_STR_DOT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_expression, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_expression, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT] = REDUCE(sym_expression, 1),
    },
    [208] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(373),
    },
    [209] = {
        [sym__line_break] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat0] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LPAREN] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_SEMI] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DOT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT] = REDUCE(sym_var_name, 1),
    },
    [210] = {
        [sym_var_name] = SHIFT(341),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(342),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [211] = {
        [sym__line_break] = REDUCE(sym_block_statement, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_block_statement, 2),
    },
    [212] = {
        [sym_expression] = SHIFT(311),
        [sym_call_expression] = SHIFT(312),
        [sym_selector_expression] = SHIFT(312),
        [sym_math_op] = SHIFT(312),
        [sym_bool_op] = SHIFT(312),
        [sym_var_name] = SHIFT(312),
        [sym__line_break] = SHIFT(313),
        [sym_string] = SHIFT(312),
        [sym__identifier] = SHIFT(314),
        [sym_number] = SHIFT(312),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(313),
        [aux_sym_STR_BANG] = SHIFT(315),
    },
    [213] = {
        [sym_expression] = SHIFT(291),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [214] = {
        [sym_var_name] = SHIFT(278),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(279),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [215] = {
        [sym_expression] = SHIFT(219),
        [sym_call_expression] = SHIFT(220),
        [sym_selector_expression] = SHIFT(220),
        [sym_math_op] = SHIFT(220),
        [sym_bool_op] = SHIFT(220),
        [sym_var_name] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(220),
        [sym__identifier] = SHIFT(221),
        [sym_number] = SHIFT(220),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(222),
    },
    [216] = {
        [sym_expression] = SHIFT(217),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [217] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_EQ_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LT_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LT] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_GT_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_GT] = REDUCE_FRAGILE(sym_bool_op, 2),
    },
    [218] = {
        [sym__line_break] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_SEMI] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DOT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT] = REDUCE(sym_var_name, 1),
    },
    [219] = {
        [sym_block_statement] = SHIFT(224),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(225),
        [aux_sym_STR_LBRACE] = SHIFT(226),
        [aux_sym_STR_STAR] = SHIFT(227),
        [aux_sym_STR_DOT] = SHIFT(228),
        [aux_sym_STR_SLASH] = SHIFT(227),
        [aux_sym_STR_PLUS] = SHIFT(229),
        [aux_sym_STR_DASH] = SHIFT(229),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(230),
        [aux_sym_STR_AMP_AMP] = SHIFT(231),
        [aux_sym_STR_EQ_EQ] = SHIFT(232),
        [aux_sym_STR_LT_EQ] = SHIFT(232),
        [aux_sym_STR_LT] = SHIFT(232),
        [aux_sym_STR_GT_EQ] = SHIFT(232),
        [aux_sym_STR_GT] = SHIFT(232),
    },
    [220] = {
        [sym_block_statement] = REDUCE(sym_expression, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LBRACE] = REDUCE(sym_expression, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DOT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_expression, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_expression, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT] = REDUCE(sym_expression, 1),
    },
    [221] = {
        [sym_block_statement] = REDUCE(sym_var_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LBRACE] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DOT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT] = REDUCE(sym_var_name, 1),
    },
    [222] = {
        [sym_expression] = SHIFT(223),
        [sym_call_expression] = SHIFT(220),
        [sym_selector_expression] = SHIFT(220),
        [sym_math_op] = SHIFT(220),
        [sym_bool_op] = SHIFT(220),
        [sym_var_name] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(220),
        [sym__identifier] = SHIFT(221),
        [sym_number] = SHIFT(220),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(222),
    },
    [223] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_bool_op, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_EQ_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LT_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LT] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_GT_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_GT] = REDUCE_FRAGILE(sym_bool_op, 2),
    },
    [224] = {
        [sym_var_declaration] = REDUCE(sym_if_statement, 3),
        [sym_statement] = REDUCE(sym_if_statement, 3),
        [sym_return_statement] = REDUCE(sym_if_statement, 3),
        [sym_declaration_statement] = REDUCE(sym_if_statement, 3),
        [sym_range_statement] = REDUCE(sym_if_statement, 3),
        [sym_if_statement] = REDUCE(sym_if_statement, 3),
        [sym_expression_statement] = REDUCE(sym_if_statement, 3),
        [sym_expression] = REDUCE(sym_if_statement, 3),
        [sym_call_expression] = REDUCE(sym_if_statement, 3),
        [sym_selector_expression] = REDUCE(sym_if_statement, 3),
        [sym_math_op] = REDUCE(sym_if_statement, 3),
        [sym_bool_op] = REDUCE(sym_if_statement, 3),
        [sym_var_name] = REDUCE(sym_if_statement, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_if_statement, 3),
        [sym__identifier] = REDUCE(sym_if_statement, 3),
        [sym_number] = REDUCE(sym_if_statement, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_var] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_return] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_for] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_if] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_else] = SHIFT(272),
        [aux_sym_STR_BANG] = REDUCE(sym_if_statement, 3),
    },
    [225] = {
        [sym_expression] = SHIFT(242),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(245),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [226] = {
        [sym_var_declaration] = SHIFT(202),
        [sym_statement] = SHIFT(203),
        [sym_return_statement] = SHIFT(204),
        [sym_declaration_statement] = SHIFT(204),
        [sym_range_statement] = SHIFT(204),
        [sym_if_statement] = SHIFT(204),
        [sym_expression_statement] = SHIFT(204),
        [sym_expression] = SHIFT(205),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(209),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = SHIFT(239),
        [aux_sym_STR_var] = SHIFT(210),
        [aux_sym_STR_RBRACE] = SHIFT(240),
        [aux_sym_STR_return] = SHIFT(212),
        [aux_sym_STR_COLON_EQ] = SHIFT(213),
        [aux_sym_STR_for] = SHIFT(214),
        [aux_sym_STR_if] = SHIFT(215),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [227] = {
        [sym_expression] = SHIFT(238),
        [sym_call_expression] = SHIFT(220),
        [sym_selector_expression] = SHIFT(220),
        [sym_math_op] = SHIFT(220),
        [sym_bool_op] = SHIFT(220),
        [sym_var_name] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(220),
        [sym__identifier] = SHIFT(221),
        [sym_number] = SHIFT(220),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(222),
    },
    [228] = {
        [sym_var_name] = SHIFT(237),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [229] = {
        [sym_expression] = SHIFT(236),
        [sym_call_expression] = SHIFT(220),
        [sym_selector_expression] = SHIFT(220),
        [sym_math_op] = SHIFT(220),
        [sym_bool_op] = SHIFT(220),
        [sym_var_name] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(220),
        [sym__identifier] = SHIFT(221),
        [sym_number] = SHIFT(220),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(222),
    },
    [230] = {
        [sym_expression] = SHIFT(235),
        [sym_call_expression] = SHIFT(220),
        [sym_selector_expression] = SHIFT(220),
        [sym_math_op] = SHIFT(220),
        [sym_bool_op] = SHIFT(220),
        [sym_var_name] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(220),
        [sym__identifier] = SHIFT(221),
        [sym_number] = SHIFT(220),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(222),
    },
    [231] = {
        [sym_expression] = SHIFT(234),
        [sym_call_expression] = SHIFT(220),
        [sym_selector_expression] = SHIFT(220),
        [sym_math_op] = SHIFT(220),
        [sym_bool_op] = SHIFT(220),
        [sym_var_name] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(220),
        [sym__identifier] = SHIFT(221),
        [sym_number] = SHIFT(220),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(222),
    },
    [232] = {
        [sym_expression] = SHIFT(233),
        [sym_call_expression] = SHIFT(220),
        [sym_selector_expression] = SHIFT(220),
        [sym_math_op] = SHIFT(220),
        [sym_bool_op] = SHIFT(220),
        [sym_var_name] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(220),
        [sym__identifier] = SHIFT(221),
        [sym_number] = SHIFT(220),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(222),
    },
    [233] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LT_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_GT_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_GT] = REDUCE_FRAGILE(sym_bool_op, 3),
    },
    [234] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_EQ_EQ] = SHIFT(232),
        [aux_sym_STR_LT_EQ] = SHIFT(232),
        [aux_sym_STR_LT] = SHIFT(232),
        [aux_sym_STR_GT_EQ] = SHIFT(232),
        [aux_sym_STR_GT] = SHIFT(232),
    },
    [235] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(227),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(227),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(231),
        [aux_sym_STR_EQ_EQ] = SHIFT(232),
        [aux_sym_STR_LT_EQ] = SHIFT(232),
        [aux_sym_STR_LT] = SHIFT(232),
        [aux_sym_STR_GT_EQ] = SHIFT(232),
        [aux_sym_STR_GT] = SHIFT(232),
    },
    [236] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(227),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(227),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(231),
        [aux_sym_STR_EQ_EQ] = SHIFT(232),
        [aux_sym_STR_LT_EQ] = SHIFT(232),
        [aux_sym_STR_LT] = SHIFT(232),
        [aux_sym_STR_GT_EQ] = SHIFT(232),
        [aux_sym_STR_GT] = SHIFT(232),
    },
    [237] = {
        [sym_block_statement] = REDUCE(sym_selector_expression, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LBRACE] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_DOT] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_PLUS] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LT] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_GT] = REDUCE(sym_selector_expression, 3),
    },
    [238] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_EQ_EQ] = SHIFT(232),
        [aux_sym_STR_LT_EQ] = SHIFT(232),
        [aux_sym_STR_LT] = SHIFT(232),
        [aux_sym_STR_GT_EQ] = SHIFT(232),
        [aux_sym_STR_GT] = SHIFT(232),
    },
    [239] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(241),
    },
    [240] = {
        [sym_var_declaration] = REDUCE(sym_block_statement, 2),
        [sym_statement] = REDUCE(sym_block_statement, 2),
        [sym_return_statement] = REDUCE(sym_block_statement, 2),
        [sym_declaration_statement] = REDUCE(sym_block_statement, 2),
        [sym_range_statement] = REDUCE(sym_block_statement, 2),
        [sym_if_statement] = REDUCE(sym_block_statement, 2),
        [sym_expression_statement] = REDUCE(sym_block_statement, 2),
        [sym_expression] = REDUCE(sym_block_statement, 2),
        [sym_call_expression] = REDUCE(sym_block_statement, 2),
        [sym_selector_expression] = REDUCE(sym_block_statement, 2),
        [sym_math_op] = REDUCE(sym_block_statement, 2),
        [sym_bool_op] = REDUCE(sym_block_statement, 2),
        [sym_var_name] = REDUCE(sym_block_statement, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_block_statement, 2),
        [sym__identifier] = REDUCE(sym_block_statement, 2),
        [sym_number] = REDUCE(sym_block_statement, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_var] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_return] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_for] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_if] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_else] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_BANG] = REDUCE(sym_block_statement, 2),
    },
    [241] = {
        [sym_var_declaration] = REDUCE(sym_block_statement, 3),
        [sym_statement] = REDUCE(sym_block_statement, 3),
        [sym_return_statement] = REDUCE(sym_block_statement, 3),
        [sym_declaration_statement] = REDUCE(sym_block_statement, 3),
        [sym_range_statement] = REDUCE(sym_block_statement, 3),
        [sym_if_statement] = REDUCE(sym_block_statement, 3),
        [sym_expression_statement] = REDUCE(sym_block_statement, 3),
        [sym_expression] = REDUCE(sym_block_statement, 3),
        [sym_call_expression] = REDUCE(sym_block_statement, 3),
        [sym_selector_expression] = REDUCE(sym_block_statement, 3),
        [sym_math_op] = REDUCE(sym_block_statement, 3),
        [sym_bool_op] = REDUCE(sym_block_statement, 3),
        [sym_var_name] = REDUCE(sym_block_statement, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_block_statement, 3),
        [sym__identifier] = REDUCE(sym_block_statement, 3),
        [sym_number] = REDUCE(sym_block_statement, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_var] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_return] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_for] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_if] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_else] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_BANG] = REDUCE(sym_block_statement, 3),
    },
    [242] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(248),
        [aux_sym_STR_LPAREN] = SHIFT(249),
        [aux_sym_STR_RPAREN] = SHIFT(250),
        [aux_sym_STR_STAR] = SHIFT(251),
        [aux_sym_STR_COMMA] = SHIFT(252),
        [aux_sym_STR_DOT] = SHIFT(253),
        [aux_sym_STR_SLASH] = SHIFT(251),
        [aux_sym_STR_PLUS] = SHIFT(254),
        [aux_sym_STR_DASH] = SHIFT(254),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(255),
        [aux_sym_STR_AMP_AMP] = SHIFT(256),
        [aux_sym_STR_EQ_EQ] = SHIFT(257),
        [aux_sym_STR_LT_EQ] = SHIFT(257),
        [aux_sym_STR_LT] = SHIFT(257),
        [aux_sym_STR_GT_EQ] = SHIFT(257),
        [aux_sym_STR_GT] = SHIFT(257),
    },
    [243] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LPAREN] = REDUCE(sym_expression, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_expression, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_expression, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DOT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_expression, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_expression, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT] = REDUCE(sym_expression, 1),
    },
    [244] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LPAREN] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DOT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT] = REDUCE(sym_var_name, 1),
    },
    [245] = {
        [sym_block_statement] = REDUCE(sym_call_expression, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LBRACE] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 3),
    },
    [246] = {
        [sym_expression] = SHIFT(247),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [247] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_EQ_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LT_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LT] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_GT_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_GT] = REDUCE_FRAGILE(sym_bool_op, 2),
    },
    [248] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(271),
    },
    [249] = {
        [sym_expression] = SHIFT(266),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(267),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [250] = {
        [sym_block_statement] = REDUCE(sym_call_expression, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LBRACE] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 4),
    },
    [251] = {
        [sym_expression] = SHIFT(265),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [252] = {
        [sym_expression] = SHIFT(263),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [253] = {
        [sym_var_name] = SHIFT(262),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [254] = {
        [sym_expression] = SHIFT(261),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [255] = {
        [sym_expression] = SHIFT(260),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [256] = {
        [sym_expression] = SHIFT(259),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [257] = {
        [sym_expression] = SHIFT(258),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [258] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LT_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_GT_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_GT] = REDUCE_FRAGILE(sym_bool_op, 3),
    },
    [259] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_EQ_EQ] = SHIFT(257),
        [aux_sym_STR_LT_EQ] = SHIFT(257),
        [aux_sym_STR_LT] = SHIFT(257),
        [aux_sym_STR_GT_EQ] = SHIFT(257),
        [aux_sym_STR_GT] = SHIFT(257),
    },
    [260] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(251),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(251),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(256),
        [aux_sym_STR_EQ_EQ] = SHIFT(257),
        [aux_sym_STR_LT_EQ] = SHIFT(257),
        [aux_sym_STR_LT] = SHIFT(257),
        [aux_sym_STR_GT_EQ] = SHIFT(257),
        [aux_sym_STR_GT] = SHIFT(257),
    },
    [261] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(251),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(251),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(256),
        [aux_sym_STR_EQ_EQ] = SHIFT(257),
        [aux_sym_STR_LT_EQ] = SHIFT(257),
        [aux_sym_STR_LT] = SHIFT(257),
        [aux_sym_STR_GT_EQ] = SHIFT(257),
        [aux_sym_STR_GT] = SHIFT(257),
    },
    [262] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LPAREN] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_DOT] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_PLUS] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LT] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_GT] = REDUCE(sym_selector_expression, 3),
    },
    [263] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(264),
        [aux_sym_STR_LPAREN] = SHIFT(249),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_call_expression_repeat0, 2),
        [aux_sym_STR_STAR] = SHIFT(251),
        [aux_sym_STR_COMMA] = SHIFT(252),
        [aux_sym_STR_DOT] = SHIFT(253),
        [aux_sym_STR_SLASH] = SHIFT(251),
        [aux_sym_STR_PLUS] = SHIFT(254),
        [aux_sym_STR_DASH] = SHIFT(254),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(255),
        [aux_sym_STR_AMP_AMP] = SHIFT(256),
        [aux_sym_STR_EQ_EQ] = SHIFT(257),
        [aux_sym_STR_LT_EQ] = SHIFT(257),
        [aux_sym_STR_LT] = SHIFT(257),
        [aux_sym_STR_GT_EQ] = SHIFT(257),
        [aux_sym_STR_GT] = SHIFT(257),
    },
    [264] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_call_expression_repeat0, 3),
    },
    [265] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_EQ_EQ] = SHIFT(257),
        [aux_sym_STR_LT_EQ] = SHIFT(257),
        [aux_sym_STR_LT] = SHIFT(257),
        [aux_sym_STR_GT_EQ] = SHIFT(257),
        [aux_sym_STR_GT] = SHIFT(257),
    },
    [266] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(268),
        [aux_sym_STR_LPAREN] = SHIFT(249),
        [aux_sym_STR_RPAREN] = SHIFT(269),
        [aux_sym_STR_STAR] = SHIFT(251),
        [aux_sym_STR_COMMA] = SHIFT(252),
        [aux_sym_STR_DOT] = SHIFT(253),
        [aux_sym_STR_SLASH] = SHIFT(251),
        [aux_sym_STR_PLUS] = SHIFT(254),
        [aux_sym_STR_DASH] = SHIFT(254),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(255),
        [aux_sym_STR_AMP_AMP] = SHIFT(256),
        [aux_sym_STR_EQ_EQ] = SHIFT(257),
        [aux_sym_STR_LT_EQ] = SHIFT(257),
        [aux_sym_STR_LT] = SHIFT(257),
        [aux_sym_STR_GT_EQ] = SHIFT(257),
        [aux_sym_STR_GT] = SHIFT(257),
    },
    [267] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 3),
    },
    [268] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(270),
    },
    [269] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_RPAREN] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 4),
    },
    [270] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_RPAREN] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_COMMA] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 5),
    },
    [271] = {
        [sym_block_statement] = REDUCE(sym_call_expression, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LBRACE] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 5),
    },
    [272] = {
        [sym_block_statement] = SHIFT(273),
        [sym_if_statement] = SHIFT(273),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(274),
        [aux_sym_STR_if] = SHIFT(215),
    },
    [273] = {
        [sym_var_declaration] = REDUCE(sym_if_statement, 5),
        [sym_statement] = REDUCE(sym_if_statement, 5),
        [sym_return_statement] = REDUCE(sym_if_statement, 5),
        [sym_declaration_statement] = REDUCE(sym_if_statement, 5),
        [sym_range_statement] = REDUCE(sym_if_statement, 5),
        [sym_if_statement] = REDUCE(sym_if_statement, 5),
        [sym_expression_statement] = REDUCE(sym_if_statement, 5),
        [sym_expression] = REDUCE(sym_if_statement, 5),
        [sym_call_expression] = REDUCE(sym_if_statement, 5),
        [sym_selector_expression] = REDUCE(sym_if_statement, 5),
        [sym_math_op] = REDUCE(sym_if_statement, 5),
        [sym_bool_op] = REDUCE(sym_if_statement, 5),
        [sym_var_name] = REDUCE(sym_if_statement, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_if_statement, 5),
        [sym__identifier] = REDUCE(sym_if_statement, 5),
        [sym_number] = REDUCE(sym_if_statement, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_var] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_return] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_for] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_if] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_BANG] = REDUCE(sym_if_statement, 5),
    },
    [274] = {
        [sym_var_declaration] = SHIFT(202),
        [sym_statement] = SHIFT(203),
        [sym_return_statement] = SHIFT(204),
        [sym_declaration_statement] = SHIFT(204),
        [sym_range_statement] = SHIFT(204),
        [sym_if_statement] = SHIFT(204),
        [sym_expression_statement] = SHIFT(204),
        [sym_expression] = SHIFT(205),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(207),
        [ts_builtin_sym_error] = SHIFT(275),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(209),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = SHIFT(275),
        [aux_sym_STR_var] = SHIFT(210),
        [aux_sym_STR_RBRACE] = SHIFT(276),
        [aux_sym_STR_return] = SHIFT(212),
        [aux_sym_STR_COLON_EQ] = SHIFT(213),
        [aux_sym_STR_for] = SHIFT(214),
        [aux_sym_STR_if] = SHIFT(215),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [275] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(277),
    },
    [276] = {
        [sym_var_declaration] = REDUCE(sym_block_statement, 2),
        [sym_statement] = REDUCE(sym_block_statement, 2),
        [sym_return_statement] = REDUCE(sym_block_statement, 2),
        [sym_declaration_statement] = REDUCE(sym_block_statement, 2),
        [sym_range_statement] = REDUCE(sym_block_statement, 2),
        [sym_if_statement] = REDUCE(sym_block_statement, 2),
        [sym_expression_statement] = REDUCE(sym_block_statement, 2),
        [sym_expression] = REDUCE(sym_block_statement, 2),
        [sym_call_expression] = REDUCE(sym_block_statement, 2),
        [sym_selector_expression] = REDUCE(sym_block_statement, 2),
        [sym_math_op] = REDUCE(sym_block_statement, 2),
        [sym_bool_op] = REDUCE(sym_block_statement, 2),
        [sym_var_name] = REDUCE(sym_block_statement, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_block_statement, 2),
        [sym__identifier] = REDUCE(sym_block_statement, 2),
        [sym_number] = REDUCE(sym_block_statement, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_var] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_return] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_for] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_if] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_BANG] = REDUCE(sym_block_statement, 2),
    },
    [277] = {
        [sym_var_declaration] = REDUCE(sym_block_statement, 3),
        [sym_statement] = REDUCE(sym_block_statement, 3),
        [sym_return_statement] = REDUCE(sym_block_statement, 3),
        [sym_declaration_statement] = REDUCE(sym_block_statement, 3),
        [sym_range_statement] = REDUCE(sym_block_statement, 3),
        [sym_if_statement] = REDUCE(sym_block_statement, 3),
        [sym_expression_statement] = REDUCE(sym_block_statement, 3),
        [sym_expression] = REDUCE(sym_block_statement, 3),
        [sym_call_expression] = REDUCE(sym_block_statement, 3),
        [sym_selector_expression] = REDUCE(sym_block_statement, 3),
        [sym_math_op] = REDUCE(sym_block_statement, 3),
        [sym_bool_op] = REDUCE(sym_block_statement, 3),
        [sym_var_name] = REDUCE(sym_block_statement, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_block_statement, 3),
        [sym__identifier] = REDUCE(sym_block_statement, 3),
        [sym_number] = REDUCE(sym_block_statement, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_var] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_return] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_for] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_if] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_BANG] = REDUCE(sym_block_statement, 3),
    },
    [278] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COMMA] = SHIFT(280),
        [aux_sym_STR_COLON_EQ] = SHIFT(281),
    },
    [279] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
    },
    [280] = {
        [sym_var_name] = SHIFT(285),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(286),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [281] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_range] = SHIFT(282),
    },
    [282] = {
        [sym_expression] = SHIFT(283),
        [sym_call_expression] = SHIFT(220),
        [sym_selector_expression] = SHIFT(220),
        [sym_math_op] = SHIFT(220),
        [sym_bool_op] = SHIFT(220),
        [sym_var_name] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(220),
        [sym__identifier] = SHIFT(221),
        [sym_number] = SHIFT(220),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(222),
    },
    [283] = {
        [sym_block_statement] = SHIFT(284),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(225),
        [aux_sym_STR_LBRACE] = SHIFT(274),
        [aux_sym_STR_STAR] = SHIFT(227),
        [aux_sym_STR_DOT] = SHIFT(228),
        [aux_sym_STR_SLASH] = SHIFT(227),
        [aux_sym_STR_PLUS] = SHIFT(229),
        [aux_sym_STR_DASH] = SHIFT(229),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(230),
        [aux_sym_STR_AMP_AMP] = SHIFT(231),
        [aux_sym_STR_EQ_EQ] = SHIFT(232),
        [aux_sym_STR_LT_EQ] = SHIFT(232),
        [aux_sym_STR_LT] = SHIFT(232),
        [aux_sym_STR_GT_EQ] = SHIFT(232),
        [aux_sym_STR_GT] = SHIFT(232),
    },
    [284] = {
        [sym_var_declaration] = REDUCE(sym_range_statement, 6),
        [sym_statement] = REDUCE(sym_range_statement, 6),
        [sym_return_statement] = REDUCE(sym_range_statement, 6),
        [sym_declaration_statement] = REDUCE(sym_range_statement, 6),
        [sym_range_statement] = REDUCE(sym_range_statement, 6),
        [sym_if_statement] = REDUCE(sym_range_statement, 6),
        [sym_expression_statement] = REDUCE(sym_range_statement, 6),
        [sym_expression] = REDUCE(sym_range_statement, 6),
        [sym_call_expression] = REDUCE(sym_range_statement, 6),
        [sym_selector_expression] = REDUCE(sym_range_statement, 6),
        [sym_math_op] = REDUCE(sym_range_statement, 6),
        [sym_bool_op] = REDUCE(sym_range_statement, 6),
        [sym_var_name] = REDUCE(sym_range_statement, 6),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_range_statement, 6),
        [sym__identifier] = REDUCE(sym_range_statement, 6),
        [sym_number] = REDUCE(sym_range_statement, 6),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_var] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_RBRACE] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_return] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_for] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_if] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_BANG] = REDUCE(sym_range_statement, 6),
    },
    [285] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = SHIFT(287),
    },
    [286] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
    },
    [287] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_range] = SHIFT(288),
    },
    [288] = {
        [sym_expression] = SHIFT(289),
        [sym_call_expression] = SHIFT(220),
        [sym_selector_expression] = SHIFT(220),
        [sym_math_op] = SHIFT(220),
        [sym_bool_op] = SHIFT(220),
        [sym_var_name] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(220),
        [sym__identifier] = SHIFT(221),
        [sym_number] = SHIFT(220),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(222),
    },
    [289] = {
        [sym_block_statement] = SHIFT(290),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(225),
        [aux_sym_STR_LBRACE] = SHIFT(274),
        [aux_sym_STR_STAR] = SHIFT(227),
        [aux_sym_STR_DOT] = SHIFT(228),
        [aux_sym_STR_SLASH] = SHIFT(227),
        [aux_sym_STR_PLUS] = SHIFT(229),
        [aux_sym_STR_DASH] = SHIFT(229),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(230),
        [aux_sym_STR_AMP_AMP] = SHIFT(231),
        [aux_sym_STR_EQ_EQ] = SHIFT(232),
        [aux_sym_STR_LT_EQ] = SHIFT(232),
        [aux_sym_STR_LT] = SHIFT(232),
        [aux_sym_STR_GT_EQ] = SHIFT(232),
        [aux_sym_STR_GT] = SHIFT(232),
    },
    [290] = {
        [sym_var_declaration] = REDUCE(sym_range_statement, 8),
        [sym_statement] = REDUCE(sym_range_statement, 8),
        [sym_return_statement] = REDUCE(sym_range_statement, 8),
        [sym_declaration_statement] = REDUCE(sym_range_statement, 8),
        [sym_range_statement] = REDUCE(sym_range_statement, 8),
        [sym_if_statement] = REDUCE(sym_range_statement, 8),
        [sym_expression_statement] = REDUCE(sym_range_statement, 8),
        [sym_expression] = REDUCE(sym_range_statement, 8),
        [sym_call_expression] = REDUCE(sym_range_statement, 8),
        [sym_selector_expression] = REDUCE(sym_range_statement, 8),
        [sym_math_op] = REDUCE(sym_range_statement, 8),
        [sym_bool_op] = REDUCE(sym_range_statement, 8),
        [sym_var_name] = REDUCE(sym_range_statement, 8),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_range_statement, 8),
        [sym__identifier] = REDUCE(sym_range_statement, 8),
        [sym_number] = REDUCE(sym_range_statement, 8),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_var] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_RBRACE] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_return] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_for] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_if] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_BANG] = REDUCE(sym_range_statement, 8),
    },
    [291] = {
        [sym__line_break] = SHIFT(292),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(293),
        [aux_sym_STR_SEMI] = SHIFT(292),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = SHIFT(295),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = SHIFT(296),
        [aux_sym_STR_DASH] = SHIFT(296),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(297),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [292] = {
        [sym_var_declaration] = REDUCE(sym_declaration_statement, 3),
        [sym_statement] = REDUCE(sym_declaration_statement, 3),
        [sym_return_statement] = REDUCE(sym_declaration_statement, 3),
        [sym_declaration_statement] = REDUCE(sym_declaration_statement, 3),
        [sym_range_statement] = REDUCE(sym_declaration_statement, 3),
        [sym_if_statement] = REDUCE(sym_declaration_statement, 3),
        [sym_expression_statement] = REDUCE(sym_declaration_statement, 3),
        [sym_expression] = REDUCE(sym_declaration_statement, 3),
        [sym_call_expression] = REDUCE(sym_declaration_statement, 3),
        [sym_selector_expression] = REDUCE(sym_declaration_statement, 3),
        [sym_math_op] = REDUCE(sym_declaration_statement, 3),
        [sym_bool_op] = REDUCE(sym_declaration_statement, 3),
        [sym_var_name] = REDUCE(sym_declaration_statement, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_declaration_statement, 3),
        [sym__identifier] = REDUCE(sym_declaration_statement, 3),
        [sym_number] = REDUCE(sym_declaration_statement, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_declaration_statement, 3),
        [aux_sym_STR_LPAREN] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_declaration_statement, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_declaration_statement, 3),
        [aux_sym_STR_STAR] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_return] = REDUCE(sym_declaration_statement, 3),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_declaration_statement, 3),
        [aux_sym_STR_for] = REDUCE(sym_declaration_statement, 3),
        [aux_sym_STR_if] = REDUCE(sym_declaration_statement, 3),
        [aux_sym_STR_DOT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SLASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PLUS] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_AMP_AMP] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_EQ_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_BANG] = REDUCE(sym_declaration_statement, 3),
    },
    [293] = {
        [sym_expression] = SHIFT(306),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(307),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [294] = {
        [sym_expression] = SHIFT(305),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [295] = {
        [sym_var_name] = SHIFT(304),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(218),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [296] = {
        [sym_expression] = SHIFT(303),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [297] = {
        [sym_expression] = SHIFT(302),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [298] = {
        [sym_expression] = SHIFT(301),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [299] = {
        [sym_expression] = SHIFT(300),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [300] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LT_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_GT_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_GT] = REDUCE_FRAGILE(sym_bool_op, 3),
    },
    [301] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [302] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [303] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [304] = {
        [sym__line_break] = REDUCE(sym_selector_expression, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_SEMI] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_DOT] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_PLUS] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LT] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_GT] = REDUCE(sym_selector_expression, 3),
    },
    [305] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [306] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(308),
        [aux_sym_STR_LPAREN] = SHIFT(249),
        [aux_sym_STR_RPAREN] = SHIFT(309),
        [aux_sym_STR_STAR] = SHIFT(251),
        [aux_sym_STR_COMMA] = SHIFT(252),
        [aux_sym_STR_DOT] = SHIFT(253),
        [aux_sym_STR_SLASH] = SHIFT(251),
        [aux_sym_STR_PLUS] = SHIFT(254),
        [aux_sym_STR_DASH] = SHIFT(254),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(255),
        [aux_sym_STR_AMP_AMP] = SHIFT(256),
        [aux_sym_STR_EQ_EQ] = SHIFT(257),
        [aux_sym_STR_LT_EQ] = SHIFT(257),
        [aux_sym_STR_LT] = SHIFT(257),
        [aux_sym_STR_GT_EQ] = SHIFT(257),
        [aux_sym_STR_GT] = SHIFT(257),
    },
    [307] = {
        [sym__line_break] = REDUCE(sym_call_expression, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_SEMI] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 3),
    },
    [308] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(310),
    },
    [309] = {
        [sym__line_break] = REDUCE(sym_call_expression, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_SEMI] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 4),
    },
    [310] = {
        [sym__line_break] = REDUCE(sym_call_expression, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_SEMI] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 5),
    },
    [311] = {
        [sym__line_break] = SHIFT(317),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = SHIFT(318),
        [aux_sym_STR_LPAREN] = SHIFT(319),
        [aux_sym_STR_SEMI] = SHIFT(317),
        [aux_sym_STR_STAR] = SHIFT(320),
        [aux_sym_STR_COMMA] = SHIFT(321),
        [aux_sym_STR_DOT] = SHIFT(322),
        [aux_sym_STR_SLASH] = SHIFT(320),
        [aux_sym_STR_PLUS] = SHIFT(323),
        [aux_sym_STR_DASH] = SHIFT(323),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(324),
        [aux_sym_STR_AMP_AMP] = SHIFT(325),
        [aux_sym_STR_EQ_EQ] = SHIFT(326),
        [aux_sym_STR_LT_EQ] = SHIFT(326),
        [aux_sym_STR_LT] = SHIFT(326),
        [aux_sym_STR_GT_EQ] = SHIFT(326),
        [aux_sym_STR_GT] = SHIFT(326),
    },
    [312] = {
        [sym__line_break] = REDUCE(sym_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LPAREN] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SEMI] = REDUCE(sym_expression, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_expression, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DOT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_expression, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_expression, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_expression, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_expression, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_LT] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_expression, 1),
        [aux_sym_STR_GT] = REDUCE(sym_expression, 1),
    },
    [313] = {
        [sym_var_declaration] = REDUCE(sym_return_statement, 2),
        [sym_statement] = REDUCE(sym_return_statement, 2),
        [sym_return_statement] = REDUCE(sym_return_statement, 2),
        [sym_declaration_statement] = REDUCE(sym_return_statement, 2),
        [sym_range_statement] = REDUCE(sym_return_statement, 2),
        [sym_if_statement] = REDUCE(sym_return_statement, 2),
        [sym_expression_statement] = REDUCE(sym_return_statement, 2),
        [sym_expression] = REDUCE(sym_return_statement, 2),
        [sym_call_expression] = REDUCE(sym_return_statement, 2),
        [sym_selector_expression] = REDUCE(sym_return_statement, 2),
        [sym_math_op] = REDUCE(sym_return_statement, 2),
        [sym_bool_op] = REDUCE(sym_return_statement, 2),
        [sym_var_name] = REDUCE(sym_return_statement, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_return_statement, 2),
        [sym__identifier] = REDUCE(sym_return_statement, 2),
        [sym_number] = REDUCE(sym_return_statement, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_return] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_for] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_if] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_BANG] = REDUCE(sym_return_statement, 2),
    },
    [314] = {
        [sym__line_break] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LPAREN] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_SEMI] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DOT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_SLASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PLUS] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_DASH] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LT] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_GT] = REDUCE(sym_var_name, 1),
    },
    [315] = {
        [sym_expression] = SHIFT(316),
        [sym_call_expression] = SHIFT(312),
        [sym_selector_expression] = SHIFT(312),
        [sym_math_op] = SHIFT(312),
        [sym_bool_op] = SHIFT(312),
        [sym_var_name] = SHIFT(312),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(312),
        [sym__identifier] = SHIFT(314),
        [sym_number] = SHIFT(312),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(315),
    },
    [316] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_EQ_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LT_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_LT] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_GT_EQ] = REDUCE_FRAGILE(sym_bool_op, 2),
        [aux_sym_STR_GT] = REDUCE_FRAGILE(sym_bool_op, 2),
    },
    [317] = {
        [sym_var_declaration] = REDUCE(sym_return_statement, 3),
        [sym_statement] = REDUCE(sym_return_statement, 3),
        [sym_return_statement] = REDUCE(sym_return_statement, 3),
        [sym_declaration_statement] = REDUCE(sym_return_statement, 3),
        [sym_range_statement] = REDUCE(sym_return_statement, 3),
        [sym_if_statement] = REDUCE(sym_return_statement, 3),
        [sym_expression_statement] = REDUCE(sym_return_statement, 3),
        [sym_expression] = REDUCE(sym_return_statement, 3),
        [sym_call_expression] = REDUCE(sym_return_statement, 3),
        [sym_selector_expression] = REDUCE(sym_return_statement, 3),
        [sym_math_op] = REDUCE(sym_return_statement, 3),
        [sym_bool_op] = REDUCE(sym_return_statement, 3),
        [sym_var_name] = REDUCE(sym_return_statement, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_return_statement, 3),
        [sym__identifier] = REDUCE(sym_return_statement, 3),
        [sym_number] = REDUCE(sym_return_statement, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_return_statement, 3),
        [aux_sym_return_statement_repeat0] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LPAREN] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_return_statement, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_return_statement, 3),
        [aux_sym_STR_STAR] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_return] = REDUCE(sym_return_statement, 3),
        [aux_sym_STR_COMMA] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_return_statement, 3),
        [aux_sym_STR_for] = REDUCE(sym_return_statement, 3),
        [aux_sym_STR_if] = REDUCE(sym_return_statement, 3),
        [aux_sym_STR_DOT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SLASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PLUS] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_AMP_AMP] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_EQ_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_BANG] = REDUCE(sym_return_statement, 3),
    },
    [318] = {
        [sym__line_break] = SHIFT(340),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(340),
    },
    [319] = {
        [sym_expression] = SHIFT(335),
        [sym_call_expression] = SHIFT(243),
        [sym_selector_expression] = SHIFT(243),
        [sym_math_op] = SHIFT(243),
        [sym_bool_op] = SHIFT(243),
        [sym_var_name] = SHIFT(243),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(243),
        [sym__identifier] = SHIFT(244),
        [sym_number] = SHIFT(243),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(336),
        [aux_sym_STR_BANG] = SHIFT(246),
    },
    [320] = {
        [sym_expression] = SHIFT(334),
        [sym_call_expression] = SHIFT(312),
        [sym_selector_expression] = SHIFT(312),
        [sym_math_op] = SHIFT(312),
        [sym_bool_op] = SHIFT(312),
        [sym_var_name] = SHIFT(312),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(312),
        [sym__identifier] = SHIFT(314),
        [sym_number] = SHIFT(312),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(315),
    },
    [321] = {
        [sym_expression] = SHIFT(332),
        [sym_call_expression] = SHIFT(312),
        [sym_selector_expression] = SHIFT(312),
        [sym_math_op] = SHIFT(312),
        [sym_bool_op] = SHIFT(312),
        [sym_var_name] = SHIFT(312),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(312),
        [sym__identifier] = SHIFT(314),
        [sym_number] = SHIFT(312),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(315),
    },
    [322] = {
        [sym_var_name] = SHIFT(331),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(314),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [323] = {
        [sym_expression] = SHIFT(330),
        [sym_call_expression] = SHIFT(312),
        [sym_selector_expression] = SHIFT(312),
        [sym_math_op] = SHIFT(312),
        [sym_bool_op] = SHIFT(312),
        [sym_var_name] = SHIFT(312),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(312),
        [sym__identifier] = SHIFT(314),
        [sym_number] = SHIFT(312),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(315),
    },
    [324] = {
        [sym_expression] = SHIFT(329),
        [sym_call_expression] = SHIFT(312),
        [sym_selector_expression] = SHIFT(312),
        [sym_math_op] = SHIFT(312),
        [sym_bool_op] = SHIFT(312),
        [sym_var_name] = SHIFT(312),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(312),
        [sym__identifier] = SHIFT(314),
        [sym_number] = SHIFT(312),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(315),
    },
    [325] = {
        [sym_expression] = SHIFT(328),
        [sym_call_expression] = SHIFT(312),
        [sym_selector_expression] = SHIFT(312),
        [sym_math_op] = SHIFT(312),
        [sym_bool_op] = SHIFT(312),
        [sym_var_name] = SHIFT(312),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(312),
        [sym__identifier] = SHIFT(314),
        [sym_number] = SHIFT(312),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(315),
    },
    [326] = {
        [sym_expression] = SHIFT(327),
        [sym_call_expression] = SHIFT(312),
        [sym_selector_expression] = SHIFT(312),
        [sym_math_op] = SHIFT(312),
        [sym_bool_op] = SHIFT(312),
        [sym_var_name] = SHIFT(312),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(312),
        [sym__identifier] = SHIFT(314),
        [sym_number] = SHIFT(312),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(315),
    },
    [327] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LT_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_GT_EQ] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_GT] = REDUCE_FRAGILE(sym_bool_op, 3),
    },
    [328] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_EQ_EQ] = SHIFT(326),
        [aux_sym_STR_LT_EQ] = SHIFT(326),
        [aux_sym_STR_LT] = SHIFT(326),
        [aux_sym_STR_GT_EQ] = SHIFT(326),
        [aux_sym_STR_GT] = SHIFT(326),
    },
    [329] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(320),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(320),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(325),
        [aux_sym_STR_EQ_EQ] = SHIFT(326),
        [aux_sym_STR_LT_EQ] = SHIFT(326),
        [aux_sym_STR_LT] = SHIFT(326),
        [aux_sym_STR_GT_EQ] = SHIFT(326),
        [aux_sym_STR_GT] = SHIFT(326),
    },
    [330] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(320),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(320),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(325),
        [aux_sym_STR_EQ_EQ] = SHIFT(326),
        [aux_sym_STR_LT_EQ] = SHIFT(326),
        [aux_sym_STR_LT] = SHIFT(326),
        [aux_sym_STR_GT_EQ] = SHIFT(326),
        [aux_sym_STR_GT] = SHIFT(326),
    },
    [331] = {
        [sym__line_break] = REDUCE(sym_selector_expression, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LPAREN] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_SEMI] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_DOT] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_PLUS] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_LT] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_selector_expression, 3),
        [aux_sym_STR_GT] = REDUCE(sym_selector_expression, 3),
    },
    [332] = {
        [sym__line_break] = REDUCE(aux_sym_return_statement_repeat0, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = SHIFT(333),
        [aux_sym_STR_LPAREN] = SHIFT(319),
        [aux_sym_STR_SEMI] = REDUCE(aux_sym_return_statement_repeat0, 2),
        [aux_sym_STR_STAR] = SHIFT(320),
        [aux_sym_STR_COMMA] = SHIFT(321),
        [aux_sym_STR_DOT] = SHIFT(322),
        [aux_sym_STR_SLASH] = SHIFT(320),
        [aux_sym_STR_PLUS] = SHIFT(323),
        [aux_sym_STR_DASH] = SHIFT(323),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(324),
        [aux_sym_STR_AMP_AMP] = SHIFT(325),
        [aux_sym_STR_EQ_EQ] = SHIFT(326),
        [aux_sym_STR_LT_EQ] = SHIFT(326),
        [aux_sym_STR_LT] = SHIFT(326),
        [aux_sym_STR_GT_EQ] = SHIFT(326),
        [aux_sym_STR_GT] = SHIFT(326),
    },
    [333] = {
        [sym__line_break] = REDUCE(aux_sym_return_statement_repeat0, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(aux_sym_return_statement_repeat0, 3),
    },
    [334] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_EQ_EQ] = SHIFT(326),
        [aux_sym_STR_LT_EQ] = SHIFT(326),
        [aux_sym_STR_LT] = SHIFT(326),
        [aux_sym_STR_GT_EQ] = SHIFT(326),
        [aux_sym_STR_GT] = SHIFT(326),
    },
    [335] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(337),
        [aux_sym_STR_LPAREN] = SHIFT(249),
        [aux_sym_STR_RPAREN] = SHIFT(338),
        [aux_sym_STR_STAR] = SHIFT(251),
        [aux_sym_STR_COMMA] = SHIFT(252),
        [aux_sym_STR_DOT] = SHIFT(253),
        [aux_sym_STR_SLASH] = SHIFT(251),
        [aux_sym_STR_PLUS] = SHIFT(254),
        [aux_sym_STR_DASH] = SHIFT(254),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(255),
        [aux_sym_STR_AMP_AMP] = SHIFT(256),
        [aux_sym_STR_EQ_EQ] = SHIFT(257),
        [aux_sym_STR_LT_EQ] = SHIFT(257),
        [aux_sym_STR_LT] = SHIFT(257),
        [aux_sym_STR_GT_EQ] = SHIFT(257),
        [aux_sym_STR_GT] = SHIFT(257),
    },
    [336] = {
        [sym__line_break] = REDUCE(sym_call_expression, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_SEMI] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 3),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 3),
    },
    [337] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(339),
    },
    [338] = {
        [sym__line_break] = REDUCE(sym_call_expression, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_SEMI] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 4),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 4),
    },
    [339] = {
        [sym__line_break] = REDUCE(sym_call_expression, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LPAREN] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_SEMI] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_STAR] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_COMMA] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_DOT] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_SLASH] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_PLUS] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_DASH] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_LT] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_call_expression, 5),
        [aux_sym_STR_GT] = REDUCE(sym_call_expression, 5),
    },
    [340] = {
        [sym_var_declaration] = REDUCE(sym_return_statement, 4),
        [sym_statement] = REDUCE(sym_return_statement, 4),
        [sym_return_statement] = REDUCE(sym_return_statement, 4),
        [sym_declaration_statement] = REDUCE(sym_return_statement, 4),
        [sym_range_statement] = REDUCE(sym_return_statement, 4),
        [sym_if_statement] = REDUCE(sym_return_statement, 4),
        [sym_expression_statement] = REDUCE(sym_return_statement, 4),
        [sym_expression] = REDUCE(sym_return_statement, 4),
        [sym_call_expression] = REDUCE(sym_return_statement, 4),
        [sym_selector_expression] = REDUCE(sym_return_statement, 4),
        [sym_math_op] = REDUCE(sym_return_statement, 4),
        [sym_bool_op] = REDUCE(sym_return_statement, 4),
        [sym_var_name] = REDUCE(sym_return_statement, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_return_statement, 4),
        [sym__identifier] = REDUCE(sym_return_statement, 4),
        [sym_number] = REDUCE(sym_return_statement, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_return] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_for] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_if] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_BANG] = REDUCE(sym_return_statement, 4),
    },
    [341] = {
        [sym_type_expression] = SHIFT(343),
        [sym_pointer_type] = SHIFT(344),
        [sym_map_type] = SHIFT(344),
        [sym_slice_type] = SHIFT(344),
        [sym_struct_type] = SHIFT(344),
        [sym_interface_type] = SHIFT(344),
        [sym_type_name] = SHIFT(344),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(345),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_EQ] = SHIFT(346),
        [aux_sym_STR_STAR] = SHIFT(347),
        [aux_sym_STR_map] = SHIFT(348),
        [aux_sym_STR_LBRACK] = SHIFT(349),
        [aux_sym_STR_struct] = SHIFT(350),
        [aux_sym_STR_interface] = SHIFT(351),
    },
    [342] = {
        [sym_type_expression] = REDUCE(sym_var_name, 1),
        [sym_pointer_type] = REDUCE(sym_var_name, 1),
        [sym_map_type] = REDUCE(sym_var_name, 1),
        [sym_slice_type] = REDUCE(sym_var_name, 1),
        [sym_struct_type] = REDUCE(sym_var_name, 1),
        [sym_interface_type] = REDUCE(sym_var_name, 1),
        [sym_type_name] = REDUCE(sym_var_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_EQ] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_map] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_LBRACK] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_struct] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_interface] = REDUCE(sym_var_name, 1),
    },
    [343] = {
        [sym__line_break] = SHIFT(369),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(369),
        [aux_sym_STR_EQ] = SHIFT(370),
    },
    [344] = {
        [sym__line_break] = REDUCE(sym_type_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_EQ] = REDUCE(sym_type_expression, 1),
    },
    [345] = {
        [sym__line_break] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_EQ] = REDUCE(sym_type_name, 1),
    },
    [346] = {
        [sym_expression] = SHIFT(367),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [347] = {
        [sym_type_expression] = SHIFT(366),
        [sym_pointer_type] = SHIFT(344),
        [sym_map_type] = SHIFT(344),
        [sym_slice_type] = SHIFT(344),
        [sym_struct_type] = SHIFT(344),
        [sym_interface_type] = SHIFT(344),
        [sym_type_name] = SHIFT(344),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(345),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(347),
        [aux_sym_STR_map] = SHIFT(348),
        [aux_sym_STR_LBRACK] = SHIFT(349),
        [aux_sym_STR_struct] = SHIFT(350),
        [aux_sym_STR_interface] = SHIFT(351),
    },
    [348] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(362),
    },
    [349] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(360),
    },
    [350] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(356),
    },
    [351] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(352),
    },
    [352] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(353),
        [aux_sym_STR_RBRACE] = SHIFT(354),
    },
    [353] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(355),
    },
    [354] = {
        [sym__line_break] = REDUCE(sym_interface_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_EQ] = REDUCE(sym_interface_type, 3),
    },
    [355] = {
        [sym__line_break] = REDUCE(sym_interface_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_EQ] = REDUCE(sym_interface_type, 4),
    },
    [356] = {
        [sym_var_name] = SHIFT(116),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(117),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(357),
        [aux_sym_STR_RBRACE] = SHIFT(358),
    },
    [357] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(359),
    },
    [358] = {
        [sym__line_break] = REDUCE(sym_struct_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_EQ] = REDUCE(sym_struct_type, 3),
    },
    [359] = {
        [sym__line_break] = REDUCE(sym_struct_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_EQ] = REDUCE(sym_struct_type, 4),
    },
    [360] = {
        [sym_type_expression] = SHIFT(361),
        [sym_pointer_type] = SHIFT(344),
        [sym_map_type] = SHIFT(344),
        [sym_slice_type] = SHIFT(344),
        [sym_struct_type] = SHIFT(344),
        [sym_interface_type] = SHIFT(344),
        [sym_type_name] = SHIFT(344),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(345),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(347),
        [aux_sym_STR_map] = SHIFT(348),
        [aux_sym_STR_LBRACK] = SHIFT(349),
        [aux_sym_STR_struct] = SHIFT(350),
        [aux_sym_STR_interface] = SHIFT(351),
    },
    [361] = {
        [sym__line_break] = REDUCE(sym_slice_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_EQ] = REDUCE(sym_slice_type, 3),
    },
    [362] = {
        [sym_type_expression] = SHIFT(363),
        [sym_pointer_type] = SHIFT(141),
        [sym_map_type] = SHIFT(141),
        [sym_slice_type] = SHIFT(141),
        [sym_struct_type] = SHIFT(141),
        [sym_interface_type] = SHIFT(141),
        [sym_type_name] = SHIFT(141),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(142),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(143),
        [aux_sym_STR_map] = SHIFT(144),
        [aux_sym_STR_LBRACK] = SHIFT(145),
        [aux_sym_STR_struct] = SHIFT(146),
        [aux_sym_STR_interface] = SHIFT(147),
    },
    [363] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(364),
    },
    [364] = {
        [sym_type_expression] = SHIFT(365),
        [sym_pointer_type] = SHIFT(344),
        [sym_map_type] = SHIFT(344),
        [sym_slice_type] = SHIFT(344),
        [sym_struct_type] = SHIFT(344),
        [sym_interface_type] = SHIFT(344),
        [sym_type_name] = SHIFT(344),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(345),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(347),
        [aux_sym_STR_map] = SHIFT(348),
        [aux_sym_STR_LBRACK] = SHIFT(349),
        [aux_sym_STR_struct] = SHIFT(350),
        [aux_sym_STR_interface] = SHIFT(351),
    },
    [365] = {
        [sym__line_break] = REDUCE(sym_map_type, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_EQ] = REDUCE(sym_map_type, 5),
    },
    [366] = {
        [sym__line_break] = REDUCE(sym_pointer_type, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_EQ] = REDUCE(sym_pointer_type, 2),
    },
    [367] = {
        [sym__line_break] = SHIFT(368),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(293),
        [aux_sym_STR_SEMI] = SHIFT(368),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = SHIFT(295),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = SHIFT(296),
        [aux_sym_STR_DASH] = SHIFT(296),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(297),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [368] = {
        [sym_var_declaration] = REDUCE(sym_var_declaration, 5),
        [sym_statement] = REDUCE(sym_var_declaration, 5),
        [sym_return_statement] = REDUCE(sym_var_declaration, 5),
        [sym_declaration_statement] = REDUCE(sym_var_declaration, 5),
        [sym_range_statement] = REDUCE(sym_var_declaration, 5),
        [sym_if_statement] = REDUCE(sym_var_declaration, 5),
        [sym_expression_statement] = REDUCE(sym_var_declaration, 5),
        [sym_expression] = REDUCE(sym_var_declaration, 5),
        [sym_call_expression] = REDUCE(sym_var_declaration, 5),
        [sym_selector_expression] = REDUCE(sym_var_declaration, 5),
        [sym_math_op] = REDUCE(sym_var_declaration, 5),
        [sym_bool_op] = REDUCE(sym_var_declaration, 5),
        [sym_var_name] = REDUCE(sym_var_declaration, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_var_declaration, 5),
        [sym__identifier] = REDUCE(sym_var_declaration, 5),
        [sym_number] = REDUCE(sym_var_declaration, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_LPAREN] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_STAR] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_return] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_for] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_if] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_DOT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SLASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PLUS] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_AMP_AMP] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_EQ_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_BANG] = REDUCE(sym_var_declaration, 5),
    },
    [369] = {
        [sym_var_declaration] = REDUCE(sym_var_declaration, 4),
        [sym_statement] = REDUCE(sym_var_declaration, 4),
        [sym_return_statement] = REDUCE(sym_var_declaration, 4),
        [sym_declaration_statement] = REDUCE(sym_var_declaration, 4),
        [sym_range_statement] = REDUCE(sym_var_declaration, 4),
        [sym_if_statement] = REDUCE(sym_var_declaration, 4),
        [sym_expression_statement] = REDUCE(sym_var_declaration, 4),
        [sym_expression] = REDUCE(sym_var_declaration, 4),
        [sym_call_expression] = REDUCE(sym_var_declaration, 4),
        [sym_selector_expression] = REDUCE(sym_var_declaration, 4),
        [sym_math_op] = REDUCE(sym_var_declaration, 4),
        [sym_bool_op] = REDUCE(sym_var_declaration, 4),
        [sym_var_name] = REDUCE(sym_var_declaration, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_var_declaration, 4),
        [sym__identifier] = REDUCE(sym_var_declaration, 4),
        [sym_number] = REDUCE(sym_var_declaration, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_RBRACE] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_return] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_for] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_if] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_BANG] = REDUCE(sym_var_declaration, 4),
    },
    [370] = {
        [sym_expression] = SHIFT(371),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [371] = {
        [sym__line_break] = SHIFT(372),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(293),
        [aux_sym_STR_SEMI] = SHIFT(372),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = SHIFT(295),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = SHIFT(296),
        [aux_sym_STR_DASH] = SHIFT(296),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(297),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [372] = {
        [sym_var_declaration] = REDUCE(sym_var_declaration, 6),
        [sym_statement] = REDUCE(sym_var_declaration, 6),
        [sym_return_statement] = REDUCE(sym_var_declaration, 6),
        [sym_declaration_statement] = REDUCE(sym_var_declaration, 6),
        [sym_range_statement] = REDUCE(sym_var_declaration, 6),
        [sym_if_statement] = REDUCE(sym_var_declaration, 6),
        [sym_expression_statement] = REDUCE(sym_var_declaration, 6),
        [sym_expression] = REDUCE(sym_var_declaration, 6),
        [sym_call_expression] = REDUCE(sym_var_declaration, 6),
        [sym_selector_expression] = REDUCE(sym_var_declaration, 6),
        [sym_math_op] = REDUCE(sym_var_declaration, 6),
        [sym_bool_op] = REDUCE(sym_var_declaration, 6),
        [sym_var_name] = REDUCE(sym_var_declaration, 6),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_var_declaration, 6),
        [sym__identifier] = REDUCE(sym_var_declaration, 6),
        [sym_number] = REDUCE(sym_var_declaration, 6),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_LPAREN] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_RBRACE] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_STAR] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_return] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_for] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_if] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_DOT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SLASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PLUS] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_AMP_AMP] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_EQ_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_BANG] = REDUCE(sym_var_declaration, 6),
    },
    [373] = {
        [sym__line_break] = REDUCE(sym_block_statement, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_block_statement, 3),
    },
    [374] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = SHIFT(382),
    },
    [375] = {
        [sym_var_name] = SHIFT(379),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(380),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [376] = {
        [sym_expression] = SHIFT(377),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [377] = {
        [sym__line_break] = SHIFT(378),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(293),
        [aux_sym_STR_SEMI] = SHIFT(378),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = SHIFT(295),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = SHIFT(296),
        [aux_sym_STR_DASH] = SHIFT(296),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(297),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [378] = {
        [sym_var_declaration] = REDUCE(sym_declaration_statement, 4),
        [sym_statement] = REDUCE(sym_declaration_statement, 4),
        [sym_return_statement] = REDUCE(sym_declaration_statement, 4),
        [sym_declaration_statement] = REDUCE(sym_declaration_statement, 4),
        [sym_range_statement] = REDUCE(sym_declaration_statement, 4),
        [sym_if_statement] = REDUCE(sym_declaration_statement, 4),
        [sym_expression_statement] = REDUCE(sym_declaration_statement, 4),
        [sym_expression] = REDUCE(sym_declaration_statement, 4),
        [sym_call_expression] = REDUCE(sym_declaration_statement, 4),
        [sym_selector_expression] = REDUCE(sym_declaration_statement, 4),
        [sym_math_op] = REDUCE(sym_declaration_statement, 4),
        [sym_bool_op] = REDUCE(sym_declaration_statement, 4),
        [sym_var_name] = REDUCE(sym_declaration_statement, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_declaration_statement, 4),
        [sym__identifier] = REDUCE(sym_declaration_statement, 4),
        [sym_number] = REDUCE(sym_declaration_statement, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_declaration_statement, 4),
        [aux_sym_STR_LPAREN] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_declaration_statement, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_declaration_statement, 4),
        [aux_sym_STR_STAR] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_return] = REDUCE(sym_declaration_statement, 4),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_declaration_statement, 4),
        [aux_sym_STR_for] = REDUCE(sym_declaration_statement, 4),
        [aux_sym_STR_if] = REDUCE(sym_declaration_statement, 4),
        [aux_sym_STR_DOT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SLASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PLUS] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_AMP_AMP] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_EQ_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_BANG] = REDUCE(sym_declaration_statement, 4),
    },
    [379] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat0] = SHIFT(381),
        [aux_sym_STR_COMMA] = SHIFT(375),
        [aux_sym_STR_COLON_EQ] = REDUCE(aux_sym_declaration_statement_repeat0, 2),
    },
    [380] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat0] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
    },
    [381] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = REDUCE(aux_sym_declaration_statement_repeat0, 3),
    },
    [382] = {
        [sym_expression] = SHIFT(383),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [383] = {
        [sym__line_break] = SHIFT(384),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(293),
        [aux_sym_STR_SEMI] = SHIFT(384),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = SHIFT(295),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = SHIFT(296),
        [aux_sym_STR_DASH] = SHIFT(296),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(297),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [384] = {
        [sym_var_declaration] = REDUCE(sym_declaration_statement, 5),
        [sym_statement] = REDUCE(sym_declaration_statement, 5),
        [sym_return_statement] = REDUCE(sym_declaration_statement, 5),
        [sym_declaration_statement] = REDUCE(sym_declaration_statement, 5),
        [sym_range_statement] = REDUCE(sym_declaration_statement, 5),
        [sym_if_statement] = REDUCE(sym_declaration_statement, 5),
        [sym_expression_statement] = REDUCE(sym_declaration_statement, 5),
        [sym_expression] = REDUCE(sym_declaration_statement, 5),
        [sym_call_expression] = REDUCE(sym_declaration_statement, 5),
        [sym_selector_expression] = REDUCE(sym_declaration_statement, 5),
        [sym_math_op] = REDUCE(sym_declaration_statement, 5),
        [sym_bool_op] = REDUCE(sym_declaration_statement, 5),
        [sym_var_name] = REDUCE(sym_declaration_statement, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_declaration_statement, 5),
        [sym__identifier] = REDUCE(sym_declaration_statement, 5),
        [sym_number] = REDUCE(sym_declaration_statement, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_declaration_statement, 5),
        [aux_sym_STR_LPAREN] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_declaration_statement, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym_declaration_statement, 5),
        [aux_sym_STR_STAR] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_return] = REDUCE(sym_declaration_statement, 5),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_declaration_statement, 5),
        [aux_sym_STR_for] = REDUCE(sym_declaration_statement, 5),
        [aux_sym_STR_if] = REDUCE(sym_declaration_statement, 5),
        [aux_sym_STR_DOT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SLASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PLUS] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_AMP_AMP] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_EQ_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_BANG] = REDUCE(sym_declaration_statement, 5),
    },
    [385] = {
        [sym_var_declaration] = REDUCE(sym_expression_statement, 2),
        [sym_statement] = REDUCE(sym_expression_statement, 2),
        [sym_return_statement] = REDUCE(sym_expression_statement, 2),
        [sym_declaration_statement] = REDUCE(sym_expression_statement, 2),
        [sym_range_statement] = REDUCE(sym_expression_statement, 2),
        [sym_if_statement] = REDUCE(sym_expression_statement, 2),
        [sym_expression_statement] = REDUCE(sym_expression_statement, 2),
        [sym_expression] = REDUCE(sym_expression_statement, 2),
        [sym_call_expression] = REDUCE(sym_expression_statement, 2),
        [sym_selector_expression] = REDUCE(sym_expression_statement, 2),
        [sym_math_op] = REDUCE(sym_expression_statement, 2),
        [sym_bool_op] = REDUCE(sym_expression_statement, 2),
        [sym_var_name] = REDUCE(sym_expression_statement, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_expression_statement, 2),
        [sym__identifier] = REDUCE(sym_expression_statement, 2),
        [sym_number] = REDUCE(sym_expression_statement, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = REDUCE(sym_expression_statement, 2),
        [aux_sym_STR_LPAREN] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_expression_statement, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_expression_statement, 2),
        [aux_sym_STR_STAR] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_return] = REDUCE(sym_expression_statement, 2),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_expression_statement, 2),
        [aux_sym_STR_for] = REDUCE(sym_expression_statement, 2),
        [aux_sym_STR_if] = REDUCE(sym_expression_statement, 2),
        [aux_sym_STR_DOT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SLASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PLUS] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_AMP_AMP] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_EQ_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_BANG] = REDUCE(sym_expression_statement, 2),
    },
    [386] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_block_statement_repeat0, 2),
    },
    [387] = {
        [sym_declaration] = REDUCE(sym_func_declaration, 5),
        [sym_type_declaration] = REDUCE(sym_func_declaration, 5),
        [sym_var_declaration] = REDUCE(sym_func_declaration, 5),
        [sym_func_declaration] = REDUCE(sym_func_declaration, 5),
        [ts_builtin_sym_end] = REDUCE(sym_func_declaration, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_func_declaration, 5),
        [aux_sym_STR_type] = REDUCE(sym_func_declaration, 5),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_func_declaration, 5),
        [aux_sym_STR_func] = REDUCE(sym_func_declaration, 5),
    },
    [388] = {
        [sym_type_expression] = SHIFT(389),
        [sym_pointer_type] = SHIFT(344),
        [sym_map_type] = SHIFT(344),
        [sym_slice_type] = SHIFT(344),
        [sym_struct_type] = SHIFT(344),
        [sym_interface_type] = SHIFT(344),
        [sym_type_name] = SHIFT(344),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(345),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_EQ] = SHIFT(390),
        [aux_sym_STR_STAR] = SHIFT(347),
        [aux_sym_STR_map] = SHIFT(348),
        [aux_sym_STR_LBRACK] = SHIFT(349),
        [aux_sym_STR_struct] = SHIFT(350),
        [aux_sym_STR_interface] = SHIFT(351),
    },
    [389] = {
        [sym__line_break] = SHIFT(393),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(393),
        [aux_sym_STR_EQ] = SHIFT(394),
    },
    [390] = {
        [sym_expression] = SHIFT(391),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [391] = {
        [sym__line_break] = SHIFT(392),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(293),
        [aux_sym_STR_SEMI] = SHIFT(392),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = SHIFT(295),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = SHIFT(296),
        [aux_sym_STR_DASH] = SHIFT(296),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(297),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [392] = {
        [sym_declaration] = REDUCE(sym_var_declaration, 5),
        [sym_type_declaration] = REDUCE(sym_var_declaration, 5),
        [sym_var_declaration] = REDUCE(sym_var_declaration, 5),
        [sym_func_declaration] = REDUCE(sym_var_declaration, 5),
        [ts_builtin_sym_end] = REDUCE(sym_var_declaration, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_LPAREN] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_type] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_func] = REDUCE(sym_var_declaration, 5),
        [aux_sym_STR_STAR] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DOT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SLASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PLUS] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_AMP_AMP] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_EQ_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT] = REDUCE_EXTRA(sym__line_break),
    },
    [393] = {
        [sym_declaration] = REDUCE(sym_var_declaration, 4),
        [sym_type_declaration] = REDUCE(sym_var_declaration, 4),
        [sym_var_declaration] = REDUCE(sym_var_declaration, 4),
        [sym_func_declaration] = REDUCE(sym_var_declaration, 4),
        [ts_builtin_sym_end] = REDUCE(sym_var_declaration, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_type] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_func] = REDUCE(sym_var_declaration, 4),
    },
    [394] = {
        [sym_expression] = SHIFT(395),
        [sym_call_expression] = SHIFT(206),
        [sym_selector_expression] = SHIFT(206),
        [sym_math_op] = SHIFT(206),
        [sym_bool_op] = SHIFT(206),
        [sym_var_name] = SHIFT(206),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(206),
        [sym__identifier] = SHIFT(218),
        [sym_number] = SHIFT(206),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(216),
    },
    [395] = {
        [sym__line_break] = SHIFT(396),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(293),
        [aux_sym_STR_SEMI] = SHIFT(396),
        [aux_sym_STR_STAR] = SHIFT(294),
        [aux_sym_STR_DOT] = SHIFT(295),
        [aux_sym_STR_SLASH] = SHIFT(294),
        [aux_sym_STR_PLUS] = SHIFT(296),
        [aux_sym_STR_DASH] = SHIFT(296),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(297),
        [aux_sym_STR_AMP_AMP] = SHIFT(298),
        [aux_sym_STR_EQ_EQ] = SHIFT(299),
        [aux_sym_STR_LT_EQ] = SHIFT(299),
        [aux_sym_STR_LT] = SHIFT(299),
        [aux_sym_STR_GT_EQ] = SHIFT(299),
        [aux_sym_STR_GT] = SHIFT(299),
    },
    [396] = {
        [sym_declaration] = REDUCE(sym_var_declaration, 6),
        [sym_type_declaration] = REDUCE(sym_var_declaration, 6),
        [sym_var_declaration] = REDUCE(sym_var_declaration, 6),
        [sym_func_declaration] = REDUCE(sym_var_declaration, 6),
        [ts_builtin_sym_end] = REDUCE(sym_var_declaration, 6),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_LPAREN] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_type] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_func] = REDUCE(sym_var_declaration, 6),
        [aux_sym_STR_STAR] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DOT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_SLASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PLUS] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_DASH] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_AMP_AMP] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_EQ_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_LT] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_GT] = REDUCE_EXTRA(sym__line_break),
    },
    [397] = {
        [sym_type_expression] = SHIFT(399),
        [sym_pointer_type] = SHIFT(400),
        [sym_map_type] = SHIFT(400),
        [sym_slice_type] = SHIFT(400),
        [sym_struct_type] = SHIFT(400),
        [sym_interface_type] = SHIFT(400),
        [sym_type_name] = SHIFT(400),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(401),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(402),
        [aux_sym_STR_map] = SHIFT(403),
        [aux_sym_STR_LBRACK] = SHIFT(404),
        [aux_sym_STR_struct] = SHIFT(405),
        [aux_sym_STR_interface] = SHIFT(406),
    },
    [398] = {
        [sym_type_expression] = REDUCE(sym_type_name, 1),
        [sym_pointer_type] = REDUCE(sym_type_name, 1),
        [sym_map_type] = REDUCE(sym_type_name, 1),
        [sym_slice_type] = REDUCE(sym_type_name, 1),
        [sym_struct_type] = REDUCE(sym_type_name, 1),
        [sym_interface_type] = REDUCE(sym_type_name, 1),
        [sym_type_name] = REDUCE(sym_type_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_map] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_LBRACK] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_struct] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_interface] = REDUCE(sym_type_name, 1),
    },
    [399] = {
        [sym__line_break] = SHIFT(422),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(422),
    },
    [400] = {
        [sym__line_break] = REDUCE(sym_type_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_expression, 1),
    },
    [401] = {
        [sym__line_break] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_name, 1),
    },
    [402] = {
        [sym_type_expression] = SHIFT(421),
        [sym_pointer_type] = SHIFT(400),
        [sym_map_type] = SHIFT(400),
        [sym_slice_type] = SHIFT(400),
        [sym_struct_type] = SHIFT(400),
        [sym_interface_type] = SHIFT(400),
        [sym_type_name] = SHIFT(400),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(401),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(402),
        [aux_sym_STR_map] = SHIFT(403),
        [aux_sym_STR_LBRACK] = SHIFT(404),
        [aux_sym_STR_struct] = SHIFT(405),
        [aux_sym_STR_interface] = SHIFT(406),
    },
    [403] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(417),
    },
    [404] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(415),
    },
    [405] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(411),
    },
    [406] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(407),
    },
    [407] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(408),
        [aux_sym_STR_RBRACE] = SHIFT(409),
    },
    [408] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(410),
    },
    [409] = {
        [sym__line_break] = REDUCE(sym_interface_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 3),
    },
    [410] = {
        [sym__line_break] = REDUCE(sym_interface_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 4),
    },
    [411] = {
        [sym_var_name] = SHIFT(116),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(117),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(412),
        [aux_sym_STR_RBRACE] = SHIFT(413),
    },
    [412] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(414),
    },
    [413] = {
        [sym__line_break] = REDUCE(sym_struct_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 3),
    },
    [414] = {
        [sym__line_break] = REDUCE(sym_struct_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 4),
    },
    [415] = {
        [sym_type_expression] = SHIFT(416),
        [sym_pointer_type] = SHIFT(400),
        [sym_map_type] = SHIFT(400),
        [sym_slice_type] = SHIFT(400),
        [sym_struct_type] = SHIFT(400),
        [sym_interface_type] = SHIFT(400),
        [sym_type_name] = SHIFT(400),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(401),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(402),
        [aux_sym_STR_map] = SHIFT(403),
        [aux_sym_STR_LBRACK] = SHIFT(404),
        [aux_sym_STR_struct] = SHIFT(405),
        [aux_sym_STR_interface] = SHIFT(406),
    },
    [416] = {
        [sym__line_break] = REDUCE(sym_slice_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_slice_type, 3),
    },
    [417] = {
        [sym_type_expression] = SHIFT(418),
        [sym_pointer_type] = SHIFT(141),
        [sym_map_type] = SHIFT(141),
        [sym_slice_type] = SHIFT(141),
        [sym_struct_type] = SHIFT(141),
        [sym_interface_type] = SHIFT(141),
        [sym_type_name] = SHIFT(141),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(142),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(143),
        [aux_sym_STR_map] = SHIFT(144),
        [aux_sym_STR_LBRACK] = SHIFT(145),
        [aux_sym_STR_struct] = SHIFT(146),
        [aux_sym_STR_interface] = SHIFT(147),
    },
    [418] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(419),
    },
    [419] = {
        [sym_type_expression] = SHIFT(420),
        [sym_pointer_type] = SHIFT(400),
        [sym_map_type] = SHIFT(400),
        [sym_slice_type] = SHIFT(400),
        [sym_struct_type] = SHIFT(400),
        [sym_interface_type] = SHIFT(400),
        [sym_type_name] = SHIFT(400),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(401),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(402),
        [aux_sym_STR_map] = SHIFT(403),
        [aux_sym_STR_LBRACK] = SHIFT(404),
        [aux_sym_STR_struct] = SHIFT(405),
        [aux_sym_STR_interface] = SHIFT(406),
    },
    [420] = {
        [sym__line_break] = REDUCE(sym_map_type, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_map_type, 5),
    },
    [421] = {
        [sym__line_break] = REDUCE(sym_pointer_type, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_pointer_type, 2),
    },
    [422] = {
        [sym_declaration] = REDUCE(sym_type_declaration, 4),
        [sym_type_declaration] = REDUCE(sym_type_declaration, 4),
        [sym_var_declaration] = REDUCE(sym_type_declaration, 4),
        [sym_func_declaration] = REDUCE(sym_type_declaration, 4),
        [ts_builtin_sym_end] = REDUCE(sym_type_declaration, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_type_declaration, 4),
        [aux_sym_STR_type] = REDUCE(sym_type_declaration, 4),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_type_declaration, 4),
        [aux_sym_STR_func] = REDUCE(sym_type_declaration, 4),
    },
    [423] = {
        [sym_imports_block] = REDUCE(sym_imports_block, 2),
        [sym_declaration] = REDUCE(sym_imports_block, 2),
        [sym_type_declaration] = REDUCE(sym_imports_block, 2),
        [sym_var_declaration] = REDUCE(sym_imports_block, 2),
        [sym_func_declaration] = REDUCE(sym_imports_block, 2),
        [ts_builtin_sym_end] = REDUCE(sym_imports_block, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat0] = REDUCE(sym_imports_block, 2),
        [aux_sym_program_repeat1] = REDUCE(sym_imports_block, 2),
        [aux_sym_STR_import] = REDUCE(sym_imports_block, 2),
        [aux_sym_STR_type] = REDUCE(sym_imports_block, 2),
        [aux_sym_STR_var] = REDUCE(sym_imports_block, 2),
        [aux_sym_STR_func] = REDUCE(sym_imports_block, 2),
    },
    [424] = {
        [sym_imports_block] = REDUCE(sym_package_import, 1),
        [sym_declaration] = REDUCE(sym_package_import, 1),
        [sym_type_declaration] = REDUCE(sym_package_import, 1),
        [sym_var_declaration] = REDUCE(sym_package_import, 1),
        [sym_func_declaration] = REDUCE(sym_package_import, 1),
        [ts_builtin_sym_end] = REDUCE(sym_package_import, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat0] = REDUCE(sym_package_import, 1),
        [aux_sym_program_repeat1] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_import] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_type] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_var] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_func] = REDUCE(sym_package_import, 1),
    },
    [425] = {
        [sym_package_import] = SHIFT(426),
        [ts_builtin_sym_error] = SHIFT(427),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(428),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_imports_block_repeat0] = SHIFT(427),
        [aux_sym_STR_RPAREN] = SHIFT(429),
    },
    [426] = {
        [sym_package_import] = SHIFT(426),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(428),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_imports_block_repeat0] = SHIFT(431),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_imports_block_repeat0, 1),
    },
    [427] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(430),
    },
    [428] = {
        [sym_package_import] = REDUCE(sym_package_import, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_package_import, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_imports_block_repeat0] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_package_import, 1),
    },
    [429] = {
        [sym_imports_block] = REDUCE(sym_imports_block, 3),
        [sym_declaration] = REDUCE(sym_imports_block, 3),
        [sym_type_declaration] = REDUCE(sym_imports_block, 3),
        [sym_var_declaration] = REDUCE(sym_imports_block, 3),
        [sym_func_declaration] = REDUCE(sym_imports_block, 3),
        [ts_builtin_sym_end] = REDUCE(sym_imports_block, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat0] = REDUCE(sym_imports_block, 3),
        [aux_sym_program_repeat1] = REDUCE(sym_imports_block, 3),
        [aux_sym_STR_import] = REDUCE(sym_imports_block, 3),
        [aux_sym_STR_type] = REDUCE(sym_imports_block, 3),
        [aux_sym_STR_var] = REDUCE(sym_imports_block, 3),
        [aux_sym_STR_func] = REDUCE(sym_imports_block, 3),
    },
    [430] = {
        [sym_imports_block] = REDUCE(sym_imports_block, 4),
        [sym_declaration] = REDUCE(sym_imports_block, 4),
        [sym_type_declaration] = REDUCE(sym_imports_block, 4),
        [sym_var_declaration] = REDUCE(sym_imports_block, 4),
        [sym_func_declaration] = REDUCE(sym_imports_block, 4),
        [ts_builtin_sym_end] = REDUCE(sym_imports_block, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat0] = REDUCE(sym_imports_block, 4),
        [aux_sym_program_repeat1] = REDUCE(sym_imports_block, 4),
        [aux_sym_STR_import] = REDUCE(sym_imports_block, 4),
        [aux_sym_STR_type] = REDUCE(sym_imports_block, 4),
        [aux_sym_STR_var] = REDUCE(sym_imports_block, 4),
        [aux_sym_STR_func] = REDUCE(sym_imports_block, 4),
    },
    [431] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_imports_block_repeat0, 2),
    },
    [432] = {
        [ts_builtin_sym_end] = REDUCE(sym_program, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [433] = {
        [ts_builtin_sym_end] = REDUCE(aux_sym_program_repeat1, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [434] = {
        [sym_declaration] = REDUCE(aux_sym_program_repeat0, 2),
        [sym_type_declaration] = REDUCE(aux_sym_program_repeat0, 2),
        [sym_var_declaration] = REDUCE(aux_sym_program_repeat0, 2),
        [sym_func_declaration] = REDUCE(aux_sym_program_repeat0, 2),
        [ts_builtin_sym_end] = REDUCE(aux_sym_program_repeat0, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(aux_sym_program_repeat0, 2),
        [aux_sym_STR_type] = REDUCE(aux_sym_program_repeat0, 2),
        [aux_sym_STR_var] = REDUCE(aux_sym_program_repeat0, 2),
        [aux_sym_STR_func] = REDUCE(aux_sym_program_repeat0, 2),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_golang);
