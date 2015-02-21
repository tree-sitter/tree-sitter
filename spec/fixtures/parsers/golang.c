#include "tree_sitter/parser.h"

#define STATE_COUNT 436
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
        [aux_sym_program_repeat0] = SHIFT(435),
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
        [aux_sym_program_repeat1] = SHIFT(434),
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
        [aux_sym_program_repeat1] = SHIFT(433),
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
        [sym_package_import] = SHIFT(424),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(425),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(426),
    },
    [12] = {
        [sym_type_name] = SHIFT(398),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(399),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [13] = {
        [sym_var_name] = SHIFT(389),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(343),
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
        [sym_block_statement] = SHIFT(201),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(202),
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
        [aux_sym__func_signature_repeat2] = SHIFT(194),
        [aux_sym_STR_RPAREN] = SHIFT(195),
        [aux_sym_STR_COMMA] = SHIFT(81),
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
        [sym_type_expression] = SHIFT(175),
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
    [49] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(170),
    },
    [50] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(168),
    },
    [51] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(116),
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
        [aux_sym_interface_type_repeat0] = SHIFT(115),
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
        [sym_type_expression] = SHIFT(76),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat0] = SHIFT(77),
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
        [sym__identifier] = SHIFT(66),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE_FRAGILE(sym__func_signature, 2),
        [aux_sym_STR_LPAREN] = SHIFT(67),
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
        [sym_var_name] = REDUCE(sym_type_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_type_name, 1),
    },
    [67] = {
        [sym_var_name] = SHIFT(68),
        [sym_type_name] = SHIFT(69),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [68] = {
        [sym_type_name] = SHIFT(73),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [69] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(70),
        [aux_sym_STR_RPAREN] = SHIFT(71),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [70] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(72),
    },
    [71] = {
        [sym_var_name] = REDUCE(sym__func_signature, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 5),
    },
    [72] = {
        [sym_var_name] = REDUCE(sym__func_signature, 6),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 6),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 6),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 6),
    },
    [73] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(74),
        [aux_sym_STR_RPAREN] = SHIFT(72),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [74] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(75),
    },
    [75] = {
        [sym_var_name] = REDUCE(sym__func_signature, 7),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 7),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 7),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 7),
    },
    [76] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(108),
        [aux_sym_STR_RPAREN] = SHIFT(109),
        [aux_sym_STR_COMMA] = SHIFT(81),
    },
    [77] = {
        [sym_type_expression] = SHIFT(78),
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
    [78] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(79),
        [aux_sym_STR_RPAREN] = SHIFT(80),
        [aux_sym_STR_COMMA] = SHIFT(81),
    },
    [79] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(101),
    },
    [80] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 5),
        [sym_type_name] = SHIFT(72),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(66),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE_FRAGILE(sym__func_signature, 5),
        [aux_sym_STR_LPAREN] = SHIFT(92),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 5),
    },
    [81] = {
        [sym_var_name] = SHIFT(82),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(83),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [82] = {
        [sym_type_expression] = SHIFT(84),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = SHIFT(85),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
        [aux_sym_STR_COMMA] = SHIFT(86),
    },
    [83] = {
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
    [84] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(91),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 3),
        [aux_sym_STR_COMMA] = SHIFT(81),
    },
    [85] = {
        [sym_type_expression] = SHIFT(89),
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
    [86] = {
        [sym_var_name] = SHIFT(87),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(83),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [87] = {
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
        [aux_sym__func_signature_repeat1] = SHIFT(88),
        [aux_sym_STR_STAR] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_map] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_LBRACK] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_struct] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_interface] = REDUCE(aux_sym__func_signature_repeat1, 2),
        [aux_sym_STR_COMMA] = SHIFT(86),
    },
    [88] = {
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
    [89] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(90),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 4),
        [aux_sym_STR_COMMA] = SHIFT(81),
    },
    [90] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 5),
    },
    [91] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 4),
    },
    [92] = {
        [sym_var_name] = SHIFT(93),
        [sym_type_name] = SHIFT(94),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [93] = {
        [sym_type_name] = SHIFT(98),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [94] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(95),
        [aux_sym_STR_RPAREN] = SHIFT(96),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [95] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(97),
    },
    [96] = {
        [sym_var_name] = REDUCE(sym__func_signature, 8),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 8),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 8),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 8),
    },
    [97] = {
        [sym_var_name] = REDUCE(sym__func_signature, 9),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 9),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 9),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 9),
    },
    [98] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(99),
        [aux_sym_STR_RPAREN] = SHIFT(97),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [99] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(100),
    },
    [100] = {
        [sym_var_name] = REDUCE(sym__func_signature, 10),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 10),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 10),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 10),
    },
    [101] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 6),
        [sym_type_name] = SHIFT(75),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(66),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE_FRAGILE(sym__func_signature, 6),
        [aux_sym_STR_LPAREN] = SHIFT(102),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 6),
    },
    [102] = {
        [sym_var_name] = SHIFT(103),
        [sym_type_name] = SHIFT(104),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [103] = {
        [sym_type_name] = SHIFT(105),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [104] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(99),
        [aux_sym_STR_RPAREN] = SHIFT(97),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [105] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(106),
        [aux_sym_STR_RPAREN] = SHIFT(100),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [106] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(107),
    },
    [107] = {
        [sym_var_name] = REDUCE(sym__func_signature, 11),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 11),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE(sym__func_signature, 11),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 11),
    },
    [108] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(80),
    },
    [109] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 4),
        [sym_type_name] = SHIFT(71),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(66),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = REDUCE_FRAGILE(sym__func_signature, 4),
        [aux_sym_STR_LPAREN] = SHIFT(110),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 4),
    },
    [110] = {
        [sym_var_name] = SHIFT(111),
        [sym_type_name] = SHIFT(112),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [111] = {
        [sym_type_name] = SHIFT(114),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [112] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(113),
        [aux_sym_STR_RPAREN] = SHIFT(75),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [113] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(96),
    },
    [114] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(95),
        [aux_sym_STR_RPAREN] = SHIFT(96),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [115] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_interface_type_repeat0, 3),
    },
    [116] = {
        [sym_var_name] = SHIFT(117),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(118),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(119),
        [aux_sym_STR_RBRACE] = SHIFT(120),
    },
    [117] = {
        [sym_type_expression] = SHIFT(122),
        [sym_pointer_type] = SHIFT(123),
        [sym_map_type] = SHIFT(123),
        [sym_slice_type] = SHIFT(123),
        [sym_struct_type] = SHIFT(123),
        [sym_interface_type] = SHIFT(123),
        [sym_type_name] = SHIFT(123),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(124),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(125),
        [aux_sym_STR_map] = SHIFT(126),
        [aux_sym_STR_LBRACK] = SHIFT(127),
        [aux_sym_STR_struct] = SHIFT(128),
        [aux_sym_STR_interface] = SHIFT(129),
    },
    [118] = {
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
    [119] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(121),
    },
    [120] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_struct_type, 3),
    },
    [121] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_RPAREN] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_struct_type, 4),
    },
    [122] = {
        [sym_var_name] = SHIFT(117),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(118),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(167),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_struct_type_repeat0, 2),
    },
    [123] = {
        [sym_var_name] = REDUCE(sym_type_expression, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_type_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_type_expression, 1),
    },
    [124] = {
        [sym_var_name] = REDUCE(sym_type_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_type_name, 1),
    },
    [125] = {
        [sym_type_expression] = SHIFT(166),
        [sym_pointer_type] = SHIFT(123),
        [sym_map_type] = SHIFT(123),
        [sym_slice_type] = SHIFT(123),
        [sym_struct_type] = SHIFT(123),
        [sym_interface_type] = SHIFT(123),
        [sym_type_name] = SHIFT(123),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(124),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(125),
        [aux_sym_STR_map] = SHIFT(126),
        [aux_sym_STR_LBRACK] = SHIFT(127),
        [aux_sym_STR_struct] = SHIFT(128),
        [aux_sym_STR_interface] = SHIFT(129),
    },
    [126] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(140),
    },
    [127] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(138),
    },
    [128] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(134),
    },
    [129] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(130),
    },
    [130] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(131),
        [aux_sym_STR_RBRACE] = SHIFT(132),
    },
    [131] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(133),
    },
    [132] = {
        [sym_var_name] = REDUCE(sym_interface_type, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_interface_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_interface_type, 3),
    },
    [133] = {
        [sym_var_name] = REDUCE(sym_interface_type, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_interface_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_interface_type, 4),
    },
    [134] = {
        [sym_var_name] = SHIFT(117),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(118),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(135),
        [aux_sym_STR_RBRACE] = SHIFT(136),
    },
    [135] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(137),
    },
    [136] = {
        [sym_var_name] = REDUCE(sym_struct_type, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_struct_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_struct_type, 3),
    },
    [137] = {
        [sym_var_name] = REDUCE(sym_struct_type, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_struct_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_struct_type, 4),
    },
    [138] = {
        [sym_type_expression] = SHIFT(139),
        [sym_pointer_type] = SHIFT(123),
        [sym_map_type] = SHIFT(123),
        [sym_slice_type] = SHIFT(123),
        [sym_struct_type] = SHIFT(123),
        [sym_interface_type] = SHIFT(123),
        [sym_type_name] = SHIFT(123),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(124),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(125),
        [aux_sym_STR_map] = SHIFT(126),
        [aux_sym_STR_LBRACK] = SHIFT(127),
        [aux_sym_STR_struct] = SHIFT(128),
        [aux_sym_STR_interface] = SHIFT(129),
    },
    [139] = {
        [sym_var_name] = REDUCE(sym_slice_type, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_slice_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_slice_type, 3),
    },
    [140] = {
        [sym_type_expression] = SHIFT(141),
        [sym_pointer_type] = SHIFT(142),
        [sym_map_type] = SHIFT(142),
        [sym_slice_type] = SHIFT(142),
        [sym_struct_type] = SHIFT(142),
        [sym_interface_type] = SHIFT(142),
        [sym_type_name] = SHIFT(142),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(143),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(144),
        [aux_sym_STR_map] = SHIFT(145),
        [aux_sym_STR_LBRACK] = SHIFT(146),
        [aux_sym_STR_struct] = SHIFT(147),
        [aux_sym_STR_interface] = SHIFT(148),
    },
    [141] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(164),
    },
    [142] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_type_expression, 1),
    },
    [143] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_type_name, 1),
    },
    [144] = {
        [sym_type_expression] = SHIFT(163),
        [sym_pointer_type] = SHIFT(142),
        [sym_map_type] = SHIFT(142),
        [sym_slice_type] = SHIFT(142),
        [sym_struct_type] = SHIFT(142),
        [sym_interface_type] = SHIFT(142),
        [sym_type_name] = SHIFT(142),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(143),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(144),
        [aux_sym_STR_map] = SHIFT(145),
        [aux_sym_STR_LBRACK] = SHIFT(146),
        [aux_sym_STR_struct] = SHIFT(147),
        [aux_sym_STR_interface] = SHIFT(148),
    },
    [145] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(159),
    },
    [146] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(157),
    },
    [147] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(153),
    },
    [148] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(149),
    },
    [149] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(150),
        [aux_sym_STR_RBRACE] = SHIFT(151),
    },
    [150] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(152),
    },
    [151] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_interface_type, 3),
    },
    [152] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_interface_type, 4),
    },
    [153] = {
        [sym_var_name] = SHIFT(117),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(118),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(154),
        [aux_sym_STR_RBRACE] = SHIFT(155),
    },
    [154] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(156),
    },
    [155] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_struct_type, 3),
    },
    [156] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_struct_type, 4),
    },
    [157] = {
        [sym_type_expression] = SHIFT(158),
        [sym_pointer_type] = SHIFT(142),
        [sym_map_type] = SHIFT(142),
        [sym_slice_type] = SHIFT(142),
        [sym_struct_type] = SHIFT(142),
        [sym_interface_type] = SHIFT(142),
        [sym_type_name] = SHIFT(142),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(143),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(144),
        [aux_sym_STR_map] = SHIFT(145),
        [aux_sym_STR_LBRACK] = SHIFT(146),
        [aux_sym_STR_struct] = SHIFT(147),
        [aux_sym_STR_interface] = SHIFT(148),
    },
    [158] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_slice_type, 3),
    },
    [159] = {
        [sym_type_expression] = SHIFT(160),
        [sym_pointer_type] = SHIFT(142),
        [sym_map_type] = SHIFT(142),
        [sym_slice_type] = SHIFT(142),
        [sym_struct_type] = SHIFT(142),
        [sym_interface_type] = SHIFT(142),
        [sym_type_name] = SHIFT(142),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(143),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(144),
        [aux_sym_STR_map] = SHIFT(145),
        [aux_sym_STR_LBRACK] = SHIFT(146),
        [aux_sym_STR_struct] = SHIFT(147),
        [aux_sym_STR_interface] = SHIFT(148),
    },
    [160] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(161),
    },
    [161] = {
        [sym_type_expression] = SHIFT(162),
        [sym_pointer_type] = SHIFT(142),
        [sym_map_type] = SHIFT(142),
        [sym_slice_type] = SHIFT(142),
        [sym_struct_type] = SHIFT(142),
        [sym_interface_type] = SHIFT(142),
        [sym_type_name] = SHIFT(142),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(143),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(144),
        [aux_sym_STR_map] = SHIFT(145),
        [aux_sym_STR_LBRACK] = SHIFT(146),
        [aux_sym_STR_struct] = SHIFT(147),
        [aux_sym_STR_interface] = SHIFT(148),
    },
    [162] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_map_type, 5),
    },
    [163] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_pointer_type, 2),
    },
    [164] = {
        [sym_type_expression] = SHIFT(165),
        [sym_pointer_type] = SHIFT(123),
        [sym_map_type] = SHIFT(123),
        [sym_slice_type] = SHIFT(123),
        [sym_struct_type] = SHIFT(123),
        [sym_interface_type] = SHIFT(123),
        [sym_type_name] = SHIFT(123),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(124),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(125),
        [aux_sym_STR_map] = SHIFT(126),
        [aux_sym_STR_LBRACK] = SHIFT(127),
        [aux_sym_STR_struct] = SHIFT(128),
        [aux_sym_STR_interface] = SHIFT(129),
    },
    [165] = {
        [sym_var_name] = REDUCE(sym_map_type, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_map_type, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym_map_type, 5),
    },
    [166] = {
        [sym_var_name] = REDUCE(sym_pointer_type, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_pointer_type, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_pointer_type, 2),
    },
    [167] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_struct_type_repeat0, 3),
    },
    [168] = {
        [sym_type_expression] = SHIFT(169),
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
    [169] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_slice_type, 3),
    },
    [170] = {
        [sym_type_expression] = SHIFT(171),
        [sym_pointer_type] = SHIFT(142),
        [sym_map_type] = SHIFT(142),
        [sym_slice_type] = SHIFT(142),
        [sym_struct_type] = SHIFT(142),
        [sym_interface_type] = SHIFT(142),
        [sym_type_name] = SHIFT(142),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(143),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(144),
        [aux_sym_STR_map] = SHIFT(145),
        [aux_sym_STR_LBRACK] = SHIFT(146),
        [aux_sym_STR_struct] = SHIFT(147),
        [aux_sym_STR_interface] = SHIFT(148),
    },
    [171] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(172),
    },
    [172] = {
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
    [173] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_RPAREN] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_COMMA] = REDUCE(sym_map_type, 5),
    },
    [174] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_RPAREN] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_COMMA] = REDUCE(sym_pointer_type, 2),
    },
    [175] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(176),
        [aux_sym_STR_RPAREN] = SHIFT(177),
        [aux_sym_STR_COMMA] = SHIFT(81),
    },
    [176] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(187),
    },
    [177] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 5),
        [sym_type_name] = SHIFT(34),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(178),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 5),
    },
    [178] = {
        [sym_var_name] = SHIFT(179),
        [sym_type_name] = SHIFT(180),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [179] = {
        [sym_type_name] = SHIFT(184),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [180] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(181),
        [aux_sym_STR_RPAREN] = SHIFT(182),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [181] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(183),
    },
    [182] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 8),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 8),
    },
    [183] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 9),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 9),
    },
    [184] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(185),
        [aux_sym_STR_RPAREN] = SHIFT(183),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [185] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(186),
    },
    [186] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 10),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 10),
    },
    [187] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 6),
        [sym_type_name] = SHIFT(43),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(188),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 6),
    },
    [188] = {
        [sym_var_name] = SHIFT(189),
        [sym_type_name] = SHIFT(190),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [189] = {
        [sym_type_name] = SHIFT(191),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [190] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(185),
        [aux_sym_STR_RPAREN] = SHIFT(183),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [191] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(192),
        [aux_sym_STR_RPAREN] = SHIFT(186),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [192] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(193),
    },
    [193] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 11),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 11),
    },
    [194] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(177),
    },
    [195] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 4),
        [sym_type_name] = SHIFT(29),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(196),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 4),
    },
    [196] = {
        [sym_var_name] = SHIFT(197),
        [sym_type_name] = SHIFT(198),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [197] = {
        [sym_type_name] = SHIFT(200),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [198] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat4] = SHIFT(199),
        [aux_sym_STR_RPAREN] = SHIFT(43),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [199] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(182),
    },
    [200] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(181),
        [aux_sym_STR_RPAREN] = SHIFT(182),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [201] = {
        [sym__line_break] = SHIFT(388),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(388),
    },
    [202] = {
        [sym_var_declaration] = SHIFT(203),
        [sym_statement] = SHIFT(204),
        [sym_return_statement] = SHIFT(205),
        [sym_declaration_statement] = SHIFT(205),
        [sym_range_statement] = SHIFT(205),
        [sym_if_statement] = SHIFT(205),
        [sym_expression_statement] = SHIFT(205),
        [sym_expression] = SHIFT(206),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(208),
        [ts_builtin_sym_error] = SHIFT(209),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(210),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = SHIFT(209),
        [aux_sym_STR_var] = SHIFT(211),
        [aux_sym_STR_RBRACE] = SHIFT(212),
        [aux_sym_STR_return] = SHIFT(213),
        [aux_sym_STR_COLON_EQ] = SHIFT(214),
        [aux_sym_STR_for] = SHIFT(215),
        [aux_sym_STR_if] = SHIFT(216),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [203] = {
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
    [204] = {
        [sym_var_declaration] = SHIFT(203),
        [sym_statement] = SHIFT(204),
        [sym_return_statement] = SHIFT(205),
        [sym_declaration_statement] = SHIFT(205),
        [sym_range_statement] = SHIFT(205),
        [sym_if_statement] = SHIFT(205),
        [sym_expression_statement] = SHIFT(205),
        [sym_expression] = SHIFT(206),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(208),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(210),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = SHIFT(387),
        [aux_sym_STR_var] = SHIFT(211),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_block_statement_repeat0, 1),
        [aux_sym_STR_return] = SHIFT(213),
        [aux_sym_STR_COLON_EQ] = SHIFT(214),
        [aux_sym_STR_for] = SHIFT(215),
        [aux_sym_STR_if] = SHIFT(216),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [205] = {
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
    [206] = {
        [sym__line_break] = SHIFT(386),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(294),
        [aux_sym_STR_SEMI] = SHIFT(386),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = SHIFT(296),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [207] = {
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
    [208] = {
        [sym__line_break] = REDUCE(sym_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat0] = SHIFT(375),
        [aux_sym_STR_LPAREN] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SEMI] = REDUCE(sym_expression, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_expression, 1),
        [aux_sym_STR_COMMA] = SHIFT(376),
        [aux_sym_STR_COLON_EQ] = SHIFT(377),
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
    [209] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(374),
    },
    [210] = {
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
    [211] = {
        [sym_var_name] = SHIFT(342),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(343),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [212] = {
        [sym__line_break] = REDUCE(sym_block_statement, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_block_statement, 2),
    },
    [213] = {
        [sym_expression] = SHIFT(312),
        [sym_call_expression] = SHIFT(313),
        [sym_selector_expression] = SHIFT(313),
        [sym_math_op] = SHIFT(313),
        [sym_bool_op] = SHIFT(313),
        [sym_var_name] = SHIFT(313),
        [sym__line_break] = SHIFT(314),
        [sym_string] = SHIFT(313),
        [sym__identifier] = SHIFT(315),
        [sym_number] = SHIFT(313),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(314),
        [aux_sym_STR_BANG] = SHIFT(316),
    },
    [214] = {
        [sym_expression] = SHIFT(292),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [215] = {
        [sym_var_name] = SHIFT(279),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(280),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [216] = {
        [sym_expression] = SHIFT(220),
        [sym_call_expression] = SHIFT(221),
        [sym_selector_expression] = SHIFT(221),
        [sym_math_op] = SHIFT(221),
        [sym_bool_op] = SHIFT(221),
        [sym_var_name] = SHIFT(221),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(221),
        [sym__identifier] = SHIFT(222),
        [sym_number] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(223),
    },
    [217] = {
        [sym_expression] = SHIFT(218),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [218] = {
        [sym__line_break] = REDUCE(sym_bool_op, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_SEMI] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_STAR] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_DOT] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_SLASH] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_PLUS] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_DASH] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LT] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_GT] = REDUCE(sym_bool_op, 2),
    },
    [219] = {
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
    [220] = {
        [sym_block_statement] = SHIFT(225),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(226),
        [aux_sym_STR_LBRACE] = SHIFT(227),
        [aux_sym_STR_STAR] = SHIFT(228),
        [aux_sym_STR_DOT] = SHIFT(229),
        [aux_sym_STR_SLASH] = SHIFT(228),
        [aux_sym_STR_PLUS] = SHIFT(230),
        [aux_sym_STR_DASH] = SHIFT(230),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(231),
        [aux_sym_STR_AMP_AMP] = SHIFT(232),
        [aux_sym_STR_EQ_EQ] = SHIFT(233),
        [aux_sym_STR_LT_EQ] = SHIFT(233),
        [aux_sym_STR_LT] = SHIFT(233),
        [aux_sym_STR_GT_EQ] = SHIFT(233),
        [aux_sym_STR_GT] = SHIFT(233),
    },
    [221] = {
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
    [222] = {
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
    [223] = {
        [sym_expression] = SHIFT(224),
        [sym_call_expression] = SHIFT(221),
        [sym_selector_expression] = SHIFT(221),
        [sym_math_op] = SHIFT(221),
        [sym_bool_op] = SHIFT(221),
        [sym_var_name] = SHIFT(221),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(221),
        [sym__identifier] = SHIFT(222),
        [sym_number] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(223),
    },
    [224] = {
        [sym_block_statement] = REDUCE(sym_bool_op, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LBRACE] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_STAR] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_DOT] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_SLASH] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_PLUS] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_DASH] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LT] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_GT] = REDUCE(sym_bool_op, 2),
    },
    [225] = {
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
        [aux_sym_STR_else] = SHIFT(273),
        [aux_sym_STR_BANG] = REDUCE(sym_if_statement, 3),
    },
    [226] = {
        [sym_expression] = SHIFT(243),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(246),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [227] = {
        [sym_var_declaration] = SHIFT(203),
        [sym_statement] = SHIFT(204),
        [sym_return_statement] = SHIFT(205),
        [sym_declaration_statement] = SHIFT(205),
        [sym_range_statement] = SHIFT(205),
        [sym_if_statement] = SHIFT(205),
        [sym_expression_statement] = SHIFT(205),
        [sym_expression] = SHIFT(206),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(208),
        [ts_builtin_sym_error] = SHIFT(240),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(210),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = SHIFT(240),
        [aux_sym_STR_var] = SHIFT(211),
        [aux_sym_STR_RBRACE] = SHIFT(241),
        [aux_sym_STR_return] = SHIFT(213),
        [aux_sym_STR_COLON_EQ] = SHIFT(214),
        [aux_sym_STR_for] = SHIFT(215),
        [aux_sym_STR_if] = SHIFT(216),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [228] = {
        [sym_expression] = SHIFT(239),
        [sym_call_expression] = SHIFT(221),
        [sym_selector_expression] = SHIFT(221),
        [sym_math_op] = SHIFT(221),
        [sym_bool_op] = SHIFT(221),
        [sym_var_name] = SHIFT(221),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(221),
        [sym__identifier] = SHIFT(222),
        [sym_number] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(223),
    },
    [229] = {
        [sym_var_name] = SHIFT(238),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(222),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [230] = {
        [sym_expression] = SHIFT(237),
        [sym_call_expression] = SHIFT(221),
        [sym_selector_expression] = SHIFT(221),
        [sym_math_op] = SHIFT(221),
        [sym_bool_op] = SHIFT(221),
        [sym_var_name] = SHIFT(221),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(221),
        [sym__identifier] = SHIFT(222),
        [sym_number] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(223),
    },
    [231] = {
        [sym_expression] = SHIFT(236),
        [sym_call_expression] = SHIFT(221),
        [sym_selector_expression] = SHIFT(221),
        [sym_math_op] = SHIFT(221),
        [sym_bool_op] = SHIFT(221),
        [sym_var_name] = SHIFT(221),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(221),
        [sym__identifier] = SHIFT(222),
        [sym_number] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(223),
    },
    [232] = {
        [sym_expression] = SHIFT(235),
        [sym_call_expression] = SHIFT(221),
        [sym_selector_expression] = SHIFT(221),
        [sym_math_op] = SHIFT(221),
        [sym_bool_op] = SHIFT(221),
        [sym_var_name] = SHIFT(221),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(221),
        [sym__identifier] = SHIFT(222),
        [sym_number] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(223),
    },
    [233] = {
        [sym_expression] = SHIFT(234),
        [sym_call_expression] = SHIFT(221),
        [sym_selector_expression] = SHIFT(221),
        [sym_math_op] = SHIFT(221),
        [sym_bool_op] = SHIFT(221),
        [sym_var_name] = SHIFT(221),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(221),
        [sym__identifier] = SHIFT(222),
        [sym_number] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(223),
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
        [aux_sym_STR_EQ_EQ] = SHIFT(233),
        [aux_sym_STR_LT_EQ] = SHIFT(233),
        [aux_sym_STR_LT] = SHIFT(233),
        [aux_sym_STR_GT_EQ] = SHIFT(233),
        [aux_sym_STR_GT] = SHIFT(233),
    },
    [235] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(228),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(228),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(232),
        [aux_sym_STR_EQ_EQ] = SHIFT(233),
        [aux_sym_STR_LT_EQ] = SHIFT(233),
        [aux_sym_STR_LT] = SHIFT(233),
        [aux_sym_STR_GT_EQ] = SHIFT(233),
        [aux_sym_STR_GT] = SHIFT(233),
    },
    [236] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(228),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(228),
        [aux_sym_STR_PLUS] = SHIFT(230),
        [aux_sym_STR_DASH] = SHIFT(230),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(231),
        [aux_sym_STR_AMP_AMP] = SHIFT(232),
        [aux_sym_STR_EQ_EQ] = SHIFT(233),
        [aux_sym_STR_LT_EQ] = SHIFT(233),
        [aux_sym_STR_LT] = SHIFT(233),
        [aux_sym_STR_GT_EQ] = SHIFT(233),
        [aux_sym_STR_GT] = SHIFT(233),
    },
    [237] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(228),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(228),
        [aux_sym_STR_PLUS] = SHIFT(230),
        [aux_sym_STR_DASH] = SHIFT(230),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(231),
        [aux_sym_STR_AMP_AMP] = SHIFT(232),
        [aux_sym_STR_EQ_EQ] = SHIFT(233),
        [aux_sym_STR_LT_EQ] = SHIFT(233),
        [aux_sym_STR_LT] = SHIFT(233),
        [aux_sym_STR_GT_EQ] = SHIFT(233),
        [aux_sym_STR_GT] = SHIFT(233),
    },
    [238] = {
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
    [239] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(228),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(228),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(232),
        [aux_sym_STR_EQ_EQ] = SHIFT(233),
        [aux_sym_STR_LT_EQ] = SHIFT(233),
        [aux_sym_STR_LT] = SHIFT(233),
        [aux_sym_STR_GT_EQ] = SHIFT(233),
        [aux_sym_STR_GT] = SHIFT(233),
    },
    [240] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(242),
    },
    [241] = {
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
    [242] = {
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
    [243] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(249),
        [aux_sym_STR_LPAREN] = SHIFT(250),
        [aux_sym_STR_RPAREN] = SHIFT(251),
        [aux_sym_STR_STAR] = SHIFT(252),
        [aux_sym_STR_COMMA] = SHIFT(253),
        [aux_sym_STR_DOT] = SHIFT(254),
        [aux_sym_STR_SLASH] = SHIFT(252),
        [aux_sym_STR_PLUS] = SHIFT(255),
        [aux_sym_STR_DASH] = SHIFT(255),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(256),
        [aux_sym_STR_AMP_AMP] = SHIFT(257),
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [244] = {
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
    [245] = {
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
    [246] = {
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
    [247] = {
        [sym_expression] = SHIFT(248),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [248] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LPAREN] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_RPAREN] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_STAR] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_COMMA] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_DOT] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_SLASH] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_PLUS] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_DASH] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LT] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_GT] = REDUCE(sym_bool_op, 2),
    },
    [249] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(272),
    },
    [250] = {
        [sym_expression] = SHIFT(267),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(268),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [251] = {
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
    [252] = {
        [sym_expression] = SHIFT(266),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [253] = {
        [sym_expression] = SHIFT(264),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [254] = {
        [sym_var_name] = SHIFT(263),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(245),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [255] = {
        [sym_expression] = SHIFT(262),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [256] = {
        [sym_expression] = SHIFT(261),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [257] = {
        [sym_expression] = SHIFT(260),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [258] = {
        [sym_expression] = SHIFT(259),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(247),
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
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [260] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(252),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(252),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(257),
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [261] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(252),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(252),
        [aux_sym_STR_PLUS] = SHIFT(255),
        [aux_sym_STR_DASH] = SHIFT(255),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(256),
        [aux_sym_STR_AMP_AMP] = SHIFT(257),
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [262] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(252),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(252),
        [aux_sym_STR_PLUS] = SHIFT(255),
        [aux_sym_STR_DASH] = SHIFT(255),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(256),
        [aux_sym_STR_AMP_AMP] = SHIFT(257),
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [263] = {
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
    [264] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(265),
        [aux_sym_STR_LPAREN] = SHIFT(250),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_call_expression_repeat0, 2),
        [aux_sym_STR_STAR] = SHIFT(252),
        [aux_sym_STR_COMMA] = SHIFT(253),
        [aux_sym_STR_DOT] = SHIFT(254),
        [aux_sym_STR_SLASH] = SHIFT(252),
        [aux_sym_STR_PLUS] = SHIFT(255),
        [aux_sym_STR_DASH] = SHIFT(255),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(256),
        [aux_sym_STR_AMP_AMP] = SHIFT(257),
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [265] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_call_expression_repeat0, 3),
    },
    [266] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(252),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(252),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(257),
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [267] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(269),
        [aux_sym_STR_LPAREN] = SHIFT(250),
        [aux_sym_STR_RPAREN] = SHIFT(270),
        [aux_sym_STR_STAR] = SHIFT(252),
        [aux_sym_STR_COMMA] = SHIFT(253),
        [aux_sym_STR_DOT] = SHIFT(254),
        [aux_sym_STR_SLASH] = SHIFT(252),
        [aux_sym_STR_PLUS] = SHIFT(255),
        [aux_sym_STR_DASH] = SHIFT(255),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(256),
        [aux_sym_STR_AMP_AMP] = SHIFT(257),
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [268] = {
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
    [269] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(271),
    },
    [270] = {
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
    [271] = {
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
    [272] = {
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
    [273] = {
        [sym_block_statement] = SHIFT(274),
        [sym_if_statement] = SHIFT(274),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(275),
        [aux_sym_STR_if] = SHIFT(216),
    },
    [274] = {
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
    [275] = {
        [sym_var_declaration] = SHIFT(203),
        [sym_statement] = SHIFT(204),
        [sym_return_statement] = SHIFT(205),
        [sym_declaration_statement] = SHIFT(205),
        [sym_range_statement] = SHIFT(205),
        [sym_if_statement] = SHIFT(205),
        [sym_expression_statement] = SHIFT(205),
        [sym_expression] = SHIFT(206),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(208),
        [ts_builtin_sym_error] = SHIFT(276),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(210),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat0] = SHIFT(276),
        [aux_sym_STR_var] = SHIFT(211),
        [aux_sym_STR_RBRACE] = SHIFT(277),
        [aux_sym_STR_return] = SHIFT(213),
        [aux_sym_STR_COLON_EQ] = SHIFT(214),
        [aux_sym_STR_for] = SHIFT(215),
        [aux_sym_STR_if] = SHIFT(216),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [276] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(278),
    },
    [277] = {
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
    [278] = {
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
    [279] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COMMA] = SHIFT(281),
        [aux_sym_STR_COLON_EQ] = SHIFT(282),
    },
    [280] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
    },
    [281] = {
        [sym_var_name] = SHIFT(286),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(287),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [282] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_range] = SHIFT(283),
    },
    [283] = {
        [sym_expression] = SHIFT(284),
        [sym_call_expression] = SHIFT(221),
        [sym_selector_expression] = SHIFT(221),
        [sym_math_op] = SHIFT(221),
        [sym_bool_op] = SHIFT(221),
        [sym_var_name] = SHIFT(221),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(221),
        [sym__identifier] = SHIFT(222),
        [sym_number] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(223),
    },
    [284] = {
        [sym_block_statement] = SHIFT(285),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(226),
        [aux_sym_STR_LBRACE] = SHIFT(275),
        [aux_sym_STR_STAR] = SHIFT(228),
        [aux_sym_STR_DOT] = SHIFT(229),
        [aux_sym_STR_SLASH] = SHIFT(228),
        [aux_sym_STR_PLUS] = SHIFT(230),
        [aux_sym_STR_DASH] = SHIFT(230),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(231),
        [aux_sym_STR_AMP_AMP] = SHIFT(232),
        [aux_sym_STR_EQ_EQ] = SHIFT(233),
        [aux_sym_STR_LT_EQ] = SHIFT(233),
        [aux_sym_STR_LT] = SHIFT(233),
        [aux_sym_STR_GT_EQ] = SHIFT(233),
        [aux_sym_STR_GT] = SHIFT(233),
    },
    [285] = {
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
    [286] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = SHIFT(288),
    },
    [287] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
    },
    [288] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_range] = SHIFT(289),
    },
    [289] = {
        [sym_expression] = SHIFT(290),
        [sym_call_expression] = SHIFT(221),
        [sym_selector_expression] = SHIFT(221),
        [sym_math_op] = SHIFT(221),
        [sym_bool_op] = SHIFT(221),
        [sym_var_name] = SHIFT(221),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(221),
        [sym__identifier] = SHIFT(222),
        [sym_number] = SHIFT(221),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(223),
    },
    [290] = {
        [sym_block_statement] = SHIFT(291),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(226),
        [aux_sym_STR_LBRACE] = SHIFT(275),
        [aux_sym_STR_STAR] = SHIFT(228),
        [aux_sym_STR_DOT] = SHIFT(229),
        [aux_sym_STR_SLASH] = SHIFT(228),
        [aux_sym_STR_PLUS] = SHIFT(230),
        [aux_sym_STR_DASH] = SHIFT(230),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(231),
        [aux_sym_STR_AMP_AMP] = SHIFT(232),
        [aux_sym_STR_EQ_EQ] = SHIFT(233),
        [aux_sym_STR_LT_EQ] = SHIFT(233),
        [aux_sym_STR_LT] = SHIFT(233),
        [aux_sym_STR_GT_EQ] = SHIFT(233),
        [aux_sym_STR_GT] = SHIFT(233),
    },
    [291] = {
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
    [292] = {
        [sym__line_break] = SHIFT(293),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(294),
        [aux_sym_STR_SEMI] = SHIFT(293),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = SHIFT(296),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [293] = {
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
    [294] = {
        [sym_expression] = SHIFT(307),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(308),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [295] = {
        [sym_expression] = SHIFT(306),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [296] = {
        [sym_var_name] = SHIFT(305),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(219),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [297] = {
        [sym_expression] = SHIFT(304),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [298] = {
        [sym_expression] = SHIFT(303),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [299] = {
        [sym_expression] = SHIFT(302),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [300] = {
        [sym_expression] = SHIFT(301),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
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
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [302] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [303] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [304] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [305] = {
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
    [306] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [307] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(309),
        [aux_sym_STR_LPAREN] = SHIFT(250),
        [aux_sym_STR_RPAREN] = SHIFT(310),
        [aux_sym_STR_STAR] = SHIFT(252),
        [aux_sym_STR_COMMA] = SHIFT(253),
        [aux_sym_STR_DOT] = SHIFT(254),
        [aux_sym_STR_SLASH] = SHIFT(252),
        [aux_sym_STR_PLUS] = SHIFT(255),
        [aux_sym_STR_DASH] = SHIFT(255),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(256),
        [aux_sym_STR_AMP_AMP] = SHIFT(257),
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [308] = {
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
    [309] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(311),
    },
    [310] = {
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
    [311] = {
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
    [312] = {
        [sym__line_break] = SHIFT(318),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = SHIFT(319),
        [aux_sym_STR_LPAREN] = SHIFT(320),
        [aux_sym_STR_SEMI] = SHIFT(318),
        [aux_sym_STR_STAR] = SHIFT(321),
        [aux_sym_STR_COMMA] = SHIFT(322),
        [aux_sym_STR_DOT] = SHIFT(323),
        [aux_sym_STR_SLASH] = SHIFT(321),
        [aux_sym_STR_PLUS] = SHIFT(324),
        [aux_sym_STR_DASH] = SHIFT(324),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(325),
        [aux_sym_STR_AMP_AMP] = SHIFT(326),
        [aux_sym_STR_EQ_EQ] = SHIFT(327),
        [aux_sym_STR_LT_EQ] = SHIFT(327),
        [aux_sym_STR_LT] = SHIFT(327),
        [aux_sym_STR_GT_EQ] = SHIFT(327),
        [aux_sym_STR_GT] = SHIFT(327),
    },
    [313] = {
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
    [314] = {
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
    [315] = {
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
    [316] = {
        [sym_expression] = SHIFT(317),
        [sym_call_expression] = SHIFT(313),
        [sym_selector_expression] = SHIFT(313),
        [sym_math_op] = SHIFT(313),
        [sym_bool_op] = SHIFT(313),
        [sym_var_name] = SHIFT(313),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(313),
        [sym__identifier] = SHIFT(315),
        [sym_number] = SHIFT(313),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(316),
    },
    [317] = {
        [sym__line_break] = REDUCE(sym_bool_op, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LPAREN] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_SEMI] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_STAR] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_COMMA] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_DOT] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_SLASH] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_PLUS] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_DASH] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_PIPE_PIPE] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_AMP_AMP] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_EQ_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LT_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_LT] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_GT_EQ] = REDUCE(sym_bool_op, 2),
        [aux_sym_STR_GT] = REDUCE(sym_bool_op, 2),
    },
    [318] = {
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
    [319] = {
        [sym__line_break] = SHIFT(341),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(341),
    },
    [320] = {
        [sym_expression] = SHIFT(336),
        [sym_call_expression] = SHIFT(244),
        [sym_selector_expression] = SHIFT(244),
        [sym_math_op] = SHIFT(244),
        [sym_bool_op] = SHIFT(244),
        [sym_var_name] = SHIFT(244),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(244),
        [sym__identifier] = SHIFT(245),
        [sym_number] = SHIFT(244),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(337),
        [aux_sym_STR_BANG] = SHIFT(247),
    },
    [321] = {
        [sym_expression] = SHIFT(335),
        [sym_call_expression] = SHIFT(313),
        [sym_selector_expression] = SHIFT(313),
        [sym_math_op] = SHIFT(313),
        [sym_bool_op] = SHIFT(313),
        [sym_var_name] = SHIFT(313),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(313),
        [sym__identifier] = SHIFT(315),
        [sym_number] = SHIFT(313),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(316),
    },
    [322] = {
        [sym_expression] = SHIFT(333),
        [sym_call_expression] = SHIFT(313),
        [sym_selector_expression] = SHIFT(313),
        [sym_math_op] = SHIFT(313),
        [sym_bool_op] = SHIFT(313),
        [sym_var_name] = SHIFT(313),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(313),
        [sym__identifier] = SHIFT(315),
        [sym_number] = SHIFT(313),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(316),
    },
    [323] = {
        [sym_var_name] = SHIFT(332),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(315),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [324] = {
        [sym_expression] = SHIFT(331),
        [sym_call_expression] = SHIFT(313),
        [sym_selector_expression] = SHIFT(313),
        [sym_math_op] = SHIFT(313),
        [sym_bool_op] = SHIFT(313),
        [sym_var_name] = SHIFT(313),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(313),
        [sym__identifier] = SHIFT(315),
        [sym_number] = SHIFT(313),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(316),
    },
    [325] = {
        [sym_expression] = SHIFT(330),
        [sym_call_expression] = SHIFT(313),
        [sym_selector_expression] = SHIFT(313),
        [sym_math_op] = SHIFT(313),
        [sym_bool_op] = SHIFT(313),
        [sym_var_name] = SHIFT(313),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(313),
        [sym__identifier] = SHIFT(315),
        [sym_number] = SHIFT(313),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(316),
    },
    [326] = {
        [sym_expression] = SHIFT(329),
        [sym_call_expression] = SHIFT(313),
        [sym_selector_expression] = SHIFT(313),
        [sym_math_op] = SHIFT(313),
        [sym_bool_op] = SHIFT(313),
        [sym_var_name] = SHIFT(313),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(313),
        [sym__identifier] = SHIFT(315),
        [sym_number] = SHIFT(313),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(316),
    },
    [327] = {
        [sym_expression] = SHIFT(328),
        [sym_call_expression] = SHIFT(313),
        [sym_selector_expression] = SHIFT(313),
        [sym_math_op] = SHIFT(313),
        [sym_bool_op] = SHIFT(313),
        [sym_var_name] = SHIFT(313),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(313),
        [sym__identifier] = SHIFT(315),
        [sym_number] = SHIFT(313),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(316),
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
        [aux_sym_STR_EQ_EQ] = SHIFT(327),
        [aux_sym_STR_LT_EQ] = SHIFT(327),
        [aux_sym_STR_LT] = SHIFT(327),
        [aux_sym_STR_GT_EQ] = SHIFT(327),
        [aux_sym_STR_GT] = SHIFT(327),
    },
    [329] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(321),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(321),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(326),
        [aux_sym_STR_EQ_EQ] = SHIFT(327),
        [aux_sym_STR_LT_EQ] = SHIFT(327),
        [aux_sym_STR_LT] = SHIFT(327),
        [aux_sym_STR_GT_EQ] = SHIFT(327),
        [aux_sym_STR_GT] = SHIFT(327),
    },
    [330] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(321),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(321),
        [aux_sym_STR_PLUS] = SHIFT(324),
        [aux_sym_STR_DASH] = SHIFT(324),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(325),
        [aux_sym_STR_AMP_AMP] = SHIFT(326),
        [aux_sym_STR_EQ_EQ] = SHIFT(327),
        [aux_sym_STR_LT_EQ] = SHIFT(327),
        [aux_sym_STR_LT] = SHIFT(327),
        [aux_sym_STR_GT_EQ] = SHIFT(327),
        [aux_sym_STR_GT] = SHIFT(327),
    },
    [331] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(321),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(321),
        [aux_sym_STR_PLUS] = SHIFT(324),
        [aux_sym_STR_DASH] = SHIFT(324),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(325),
        [aux_sym_STR_AMP_AMP] = SHIFT(326),
        [aux_sym_STR_EQ_EQ] = SHIFT(327),
        [aux_sym_STR_LT_EQ] = SHIFT(327),
        [aux_sym_STR_LT] = SHIFT(327),
        [aux_sym_STR_GT_EQ] = SHIFT(327),
        [aux_sym_STR_GT] = SHIFT(327),
    },
    [332] = {
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
    [333] = {
        [sym__line_break] = REDUCE(aux_sym_return_statement_repeat0, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = SHIFT(334),
        [aux_sym_STR_LPAREN] = SHIFT(320),
        [aux_sym_STR_SEMI] = REDUCE(aux_sym_return_statement_repeat0, 2),
        [aux_sym_STR_STAR] = SHIFT(321),
        [aux_sym_STR_COMMA] = SHIFT(322),
        [aux_sym_STR_DOT] = SHIFT(323),
        [aux_sym_STR_SLASH] = SHIFT(321),
        [aux_sym_STR_PLUS] = SHIFT(324),
        [aux_sym_STR_DASH] = SHIFT(324),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(325),
        [aux_sym_STR_AMP_AMP] = SHIFT(326),
        [aux_sym_STR_EQ_EQ] = SHIFT(327),
        [aux_sym_STR_LT_EQ] = SHIFT(327),
        [aux_sym_STR_LT] = SHIFT(327),
        [aux_sym_STR_GT_EQ] = SHIFT(327),
        [aux_sym_STR_GT] = SHIFT(327),
    },
    [334] = {
        [sym__line_break] = REDUCE(aux_sym_return_statement_repeat0, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(aux_sym_return_statement_repeat0, 3),
    },
    [335] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat0] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(321),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(321),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(326),
        [aux_sym_STR_EQ_EQ] = SHIFT(327),
        [aux_sym_STR_LT_EQ] = SHIFT(327),
        [aux_sym_STR_LT] = SHIFT(327),
        [aux_sym_STR_GT_EQ] = SHIFT(327),
        [aux_sym_STR_GT] = SHIFT(327),
    },
    [336] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_call_expression_repeat0] = SHIFT(338),
        [aux_sym_STR_LPAREN] = SHIFT(250),
        [aux_sym_STR_RPAREN] = SHIFT(339),
        [aux_sym_STR_STAR] = SHIFT(252),
        [aux_sym_STR_COMMA] = SHIFT(253),
        [aux_sym_STR_DOT] = SHIFT(254),
        [aux_sym_STR_SLASH] = SHIFT(252),
        [aux_sym_STR_PLUS] = SHIFT(255),
        [aux_sym_STR_DASH] = SHIFT(255),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(256),
        [aux_sym_STR_AMP_AMP] = SHIFT(257),
        [aux_sym_STR_EQ_EQ] = SHIFT(258),
        [aux_sym_STR_LT_EQ] = SHIFT(258),
        [aux_sym_STR_LT] = SHIFT(258),
        [aux_sym_STR_GT_EQ] = SHIFT(258),
        [aux_sym_STR_GT] = SHIFT(258),
    },
    [337] = {
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
    [338] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(340),
    },
    [339] = {
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
    [340] = {
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
    [341] = {
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
    [342] = {
        [sym_type_expression] = SHIFT(344),
        [sym_pointer_type] = SHIFT(345),
        [sym_map_type] = SHIFT(345),
        [sym_slice_type] = SHIFT(345),
        [sym_struct_type] = SHIFT(345),
        [sym_interface_type] = SHIFT(345),
        [sym_type_name] = SHIFT(345),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(346),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_EQ] = SHIFT(347),
        [aux_sym_STR_STAR] = SHIFT(348),
        [aux_sym_STR_map] = SHIFT(349),
        [aux_sym_STR_LBRACK] = SHIFT(350),
        [aux_sym_STR_struct] = SHIFT(351),
        [aux_sym_STR_interface] = SHIFT(352),
    },
    [343] = {
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
    [344] = {
        [sym__line_break] = SHIFT(370),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(370),
        [aux_sym_STR_EQ] = SHIFT(371),
    },
    [345] = {
        [sym__line_break] = REDUCE(sym_type_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_EQ] = REDUCE(sym_type_expression, 1),
    },
    [346] = {
        [sym__line_break] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_EQ] = REDUCE(sym_type_name, 1),
    },
    [347] = {
        [sym_expression] = SHIFT(368),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [348] = {
        [sym_type_expression] = SHIFT(367),
        [sym_pointer_type] = SHIFT(345),
        [sym_map_type] = SHIFT(345),
        [sym_slice_type] = SHIFT(345),
        [sym_struct_type] = SHIFT(345),
        [sym_interface_type] = SHIFT(345),
        [sym_type_name] = SHIFT(345),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(346),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(348),
        [aux_sym_STR_map] = SHIFT(349),
        [aux_sym_STR_LBRACK] = SHIFT(350),
        [aux_sym_STR_struct] = SHIFT(351),
        [aux_sym_STR_interface] = SHIFT(352),
    },
    [349] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(363),
    },
    [350] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(361),
    },
    [351] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(357),
    },
    [352] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(353),
    },
    [353] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(354),
        [aux_sym_STR_RBRACE] = SHIFT(355),
    },
    [354] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(356),
    },
    [355] = {
        [sym__line_break] = REDUCE(sym_interface_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_EQ] = REDUCE(sym_interface_type, 3),
    },
    [356] = {
        [sym__line_break] = REDUCE(sym_interface_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_EQ] = REDUCE(sym_interface_type, 4),
    },
    [357] = {
        [sym_var_name] = SHIFT(117),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(118),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(358),
        [aux_sym_STR_RBRACE] = SHIFT(359),
    },
    [358] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(360),
    },
    [359] = {
        [sym__line_break] = REDUCE(sym_struct_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_EQ] = REDUCE(sym_struct_type, 3),
    },
    [360] = {
        [sym__line_break] = REDUCE(sym_struct_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_EQ] = REDUCE(sym_struct_type, 4),
    },
    [361] = {
        [sym_type_expression] = SHIFT(362),
        [sym_pointer_type] = SHIFT(345),
        [sym_map_type] = SHIFT(345),
        [sym_slice_type] = SHIFT(345),
        [sym_struct_type] = SHIFT(345),
        [sym_interface_type] = SHIFT(345),
        [sym_type_name] = SHIFT(345),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(346),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(348),
        [aux_sym_STR_map] = SHIFT(349),
        [aux_sym_STR_LBRACK] = SHIFT(350),
        [aux_sym_STR_struct] = SHIFT(351),
        [aux_sym_STR_interface] = SHIFT(352),
    },
    [362] = {
        [sym__line_break] = REDUCE(sym_slice_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_EQ] = REDUCE(sym_slice_type, 3),
    },
    [363] = {
        [sym_type_expression] = SHIFT(364),
        [sym_pointer_type] = SHIFT(142),
        [sym_map_type] = SHIFT(142),
        [sym_slice_type] = SHIFT(142),
        [sym_struct_type] = SHIFT(142),
        [sym_interface_type] = SHIFT(142),
        [sym_type_name] = SHIFT(142),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(143),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(144),
        [aux_sym_STR_map] = SHIFT(145),
        [aux_sym_STR_LBRACK] = SHIFT(146),
        [aux_sym_STR_struct] = SHIFT(147),
        [aux_sym_STR_interface] = SHIFT(148),
    },
    [364] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(365),
    },
    [365] = {
        [sym_type_expression] = SHIFT(366),
        [sym_pointer_type] = SHIFT(345),
        [sym_map_type] = SHIFT(345),
        [sym_slice_type] = SHIFT(345),
        [sym_struct_type] = SHIFT(345),
        [sym_interface_type] = SHIFT(345),
        [sym_type_name] = SHIFT(345),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(346),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(348),
        [aux_sym_STR_map] = SHIFT(349),
        [aux_sym_STR_LBRACK] = SHIFT(350),
        [aux_sym_STR_struct] = SHIFT(351),
        [aux_sym_STR_interface] = SHIFT(352),
    },
    [366] = {
        [sym__line_break] = REDUCE(sym_map_type, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_EQ] = REDUCE(sym_map_type, 5),
    },
    [367] = {
        [sym__line_break] = REDUCE(sym_pointer_type, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_EQ] = REDUCE(sym_pointer_type, 2),
    },
    [368] = {
        [sym__line_break] = SHIFT(369),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(294),
        [aux_sym_STR_SEMI] = SHIFT(369),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = SHIFT(296),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [369] = {
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
    [370] = {
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
    [371] = {
        [sym_expression] = SHIFT(372),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [372] = {
        [sym__line_break] = SHIFT(373),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(294),
        [aux_sym_STR_SEMI] = SHIFT(373),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = SHIFT(296),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [373] = {
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
    [374] = {
        [sym__line_break] = REDUCE(sym_block_statement, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_block_statement, 3),
    },
    [375] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = SHIFT(383),
    },
    [376] = {
        [sym_var_name] = SHIFT(380),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(381),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [377] = {
        [sym_expression] = SHIFT(378),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [378] = {
        [sym__line_break] = SHIFT(379),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(294),
        [aux_sym_STR_SEMI] = SHIFT(379),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = SHIFT(296),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [379] = {
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
    [380] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat0] = SHIFT(382),
        [aux_sym_STR_COMMA] = SHIFT(376),
        [aux_sym_STR_COLON_EQ] = REDUCE(aux_sym_declaration_statement_repeat0, 2),
    },
    [381] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat0] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
    },
    [382] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = REDUCE(aux_sym_declaration_statement_repeat0, 3),
    },
    [383] = {
        [sym_expression] = SHIFT(384),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [384] = {
        [sym__line_break] = SHIFT(385),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(294),
        [aux_sym_STR_SEMI] = SHIFT(385),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = SHIFT(296),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [385] = {
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
    [386] = {
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
    [387] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_block_statement_repeat0, 2),
    },
    [388] = {
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
    [389] = {
        [sym_type_expression] = SHIFT(390),
        [sym_pointer_type] = SHIFT(345),
        [sym_map_type] = SHIFT(345),
        [sym_slice_type] = SHIFT(345),
        [sym_struct_type] = SHIFT(345),
        [sym_interface_type] = SHIFT(345),
        [sym_type_name] = SHIFT(345),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(346),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_EQ] = SHIFT(391),
        [aux_sym_STR_STAR] = SHIFT(348),
        [aux_sym_STR_map] = SHIFT(349),
        [aux_sym_STR_LBRACK] = SHIFT(350),
        [aux_sym_STR_struct] = SHIFT(351),
        [aux_sym_STR_interface] = SHIFT(352),
    },
    [390] = {
        [sym__line_break] = SHIFT(394),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(394),
        [aux_sym_STR_EQ] = SHIFT(395),
    },
    [391] = {
        [sym_expression] = SHIFT(392),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [392] = {
        [sym__line_break] = SHIFT(393),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(294),
        [aux_sym_STR_SEMI] = SHIFT(393),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = SHIFT(296),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [393] = {
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
    [394] = {
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
    [395] = {
        [sym_expression] = SHIFT(396),
        [sym_call_expression] = SHIFT(207),
        [sym_selector_expression] = SHIFT(207),
        [sym_math_op] = SHIFT(207),
        [sym_bool_op] = SHIFT(207),
        [sym_var_name] = SHIFT(207),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(207),
        [sym__identifier] = SHIFT(219),
        [sym_number] = SHIFT(207),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(217),
    },
    [396] = {
        [sym__line_break] = SHIFT(397),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(294),
        [aux_sym_STR_SEMI] = SHIFT(397),
        [aux_sym_STR_STAR] = SHIFT(295),
        [aux_sym_STR_DOT] = SHIFT(296),
        [aux_sym_STR_SLASH] = SHIFT(295),
        [aux_sym_STR_PLUS] = SHIFT(297),
        [aux_sym_STR_DASH] = SHIFT(297),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(298),
        [aux_sym_STR_AMP_AMP] = SHIFT(299),
        [aux_sym_STR_EQ_EQ] = SHIFT(300),
        [aux_sym_STR_LT_EQ] = SHIFT(300),
        [aux_sym_STR_LT] = SHIFT(300),
        [aux_sym_STR_GT_EQ] = SHIFT(300),
        [aux_sym_STR_GT] = SHIFT(300),
    },
    [397] = {
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
    [398] = {
        [sym_type_expression] = SHIFT(400),
        [sym_pointer_type] = SHIFT(401),
        [sym_map_type] = SHIFT(401),
        [sym_slice_type] = SHIFT(401),
        [sym_struct_type] = SHIFT(401),
        [sym_interface_type] = SHIFT(401),
        [sym_type_name] = SHIFT(401),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(402),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(403),
        [aux_sym_STR_map] = SHIFT(404),
        [aux_sym_STR_LBRACK] = SHIFT(405),
        [aux_sym_STR_struct] = SHIFT(406),
        [aux_sym_STR_interface] = SHIFT(407),
    },
    [399] = {
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
    [400] = {
        [sym__line_break] = SHIFT(423),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(423),
    },
    [401] = {
        [sym__line_break] = REDUCE(sym_type_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_expression, 1),
    },
    [402] = {
        [sym__line_break] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_name, 1),
    },
    [403] = {
        [sym_type_expression] = SHIFT(422),
        [sym_pointer_type] = SHIFT(401),
        [sym_map_type] = SHIFT(401),
        [sym_slice_type] = SHIFT(401),
        [sym_struct_type] = SHIFT(401),
        [sym_interface_type] = SHIFT(401),
        [sym_type_name] = SHIFT(401),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(402),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(403),
        [aux_sym_STR_map] = SHIFT(404),
        [aux_sym_STR_LBRACK] = SHIFT(405),
        [aux_sym_STR_struct] = SHIFT(406),
        [aux_sym_STR_interface] = SHIFT(407),
    },
    [404] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(418),
    },
    [405] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(416),
    },
    [406] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(412),
    },
    [407] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(408),
    },
    [408] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat0] = SHIFT(409),
        [aux_sym_STR_RBRACE] = SHIFT(410),
    },
    [409] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(411),
    },
    [410] = {
        [sym__line_break] = REDUCE(sym_interface_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 3),
    },
    [411] = {
        [sym__line_break] = REDUCE(sym_interface_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 4),
    },
    [412] = {
        [sym_var_name] = SHIFT(117),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(118),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat0] = SHIFT(413),
        [aux_sym_STR_RBRACE] = SHIFT(414),
    },
    [413] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(415),
    },
    [414] = {
        [sym__line_break] = REDUCE(sym_struct_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 3),
    },
    [415] = {
        [sym__line_break] = REDUCE(sym_struct_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 4),
    },
    [416] = {
        [sym_type_expression] = SHIFT(417),
        [sym_pointer_type] = SHIFT(401),
        [sym_map_type] = SHIFT(401),
        [sym_slice_type] = SHIFT(401),
        [sym_struct_type] = SHIFT(401),
        [sym_interface_type] = SHIFT(401),
        [sym_type_name] = SHIFT(401),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(402),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(403),
        [aux_sym_STR_map] = SHIFT(404),
        [aux_sym_STR_LBRACK] = SHIFT(405),
        [aux_sym_STR_struct] = SHIFT(406),
        [aux_sym_STR_interface] = SHIFT(407),
    },
    [417] = {
        [sym__line_break] = REDUCE(sym_slice_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_slice_type, 3),
    },
    [418] = {
        [sym_type_expression] = SHIFT(419),
        [sym_pointer_type] = SHIFT(142),
        [sym_map_type] = SHIFT(142),
        [sym_slice_type] = SHIFT(142),
        [sym_struct_type] = SHIFT(142),
        [sym_interface_type] = SHIFT(142),
        [sym_type_name] = SHIFT(142),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(143),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(144),
        [aux_sym_STR_map] = SHIFT(145),
        [aux_sym_STR_LBRACK] = SHIFT(146),
        [aux_sym_STR_struct] = SHIFT(147),
        [aux_sym_STR_interface] = SHIFT(148),
    },
    [419] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(420),
    },
    [420] = {
        [sym_type_expression] = SHIFT(421),
        [sym_pointer_type] = SHIFT(401),
        [sym_map_type] = SHIFT(401),
        [sym_slice_type] = SHIFT(401),
        [sym_struct_type] = SHIFT(401),
        [sym_interface_type] = SHIFT(401),
        [sym_type_name] = SHIFT(401),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(402),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(403),
        [aux_sym_STR_map] = SHIFT(404),
        [aux_sym_STR_LBRACK] = SHIFT(405),
        [aux_sym_STR_struct] = SHIFT(406),
        [aux_sym_STR_interface] = SHIFT(407),
    },
    [421] = {
        [sym__line_break] = REDUCE(sym_map_type, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_map_type, 5),
    },
    [422] = {
        [sym__line_break] = REDUCE(sym_pointer_type, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_pointer_type, 2),
    },
    [423] = {
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
    [424] = {
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
    [425] = {
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
    [426] = {
        [sym_package_import] = SHIFT(427),
        [ts_builtin_sym_error] = SHIFT(428),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(429),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_imports_block_repeat0] = SHIFT(428),
        [aux_sym_STR_RPAREN] = SHIFT(430),
    },
    [427] = {
        [sym_package_import] = SHIFT(427),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(429),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_imports_block_repeat0] = SHIFT(432),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_imports_block_repeat0, 1),
    },
    [428] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(431),
    },
    [429] = {
        [sym_package_import] = REDUCE(sym_package_import, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_package_import, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_imports_block_repeat0] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_package_import, 1),
    },
    [430] = {
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
    [431] = {
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
    [432] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_imports_block_repeat0, 2),
    },
    [433] = {
        [ts_builtin_sym_end] = REDUCE(sym_program, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [434] = {
        [ts_builtin_sym_end] = REDUCE(aux_sym_program_repeat1, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [435] = {
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
