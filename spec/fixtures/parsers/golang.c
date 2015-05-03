#include "tree_sitter/parser.h"

#define STATE_COUNT 431
#define SYMBOL_COUNT 85

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
    aux_sym_program_repeat1,
    aux_sym_program_repeat2,
    aux_sym_imports_block_repeat1,
    aux_sym_block_statement_repeat1,
    aux_sym_struct_type_repeat1,
    aux_sym_interface_type_repeat1,
    aux_sym_return_statement_repeat1,
    aux_sym_declaration_statement_repeat1,
    aux_sym__func_signature_repeat1,
    aux_sym__func_signature_repeat2,
    aux_sym__func_signature_repeat3,
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
    [aux_sym_program_repeat1] = "program_repeat1",
    [aux_sym_program_repeat2] = "program_repeat2",
    [aux_sym_imports_block_repeat1] = "imports_block_repeat1",
    [aux_sym_block_statement_repeat1] = "block_statement_repeat1",
    [aux_sym_struct_type_repeat1] = "struct_type_repeat1",
    [aux_sym_interface_type_repeat1] = "interface_type_repeat1",
    [aux_sym_return_statement_repeat1] = "return_statement_repeat1",
    [aux_sym_declaration_statement_repeat1] = "declaration_statement_repeat1",
    [aux_sym__func_signature_repeat1] = "_func_signature_repeat1",
    [aux_sym__func_signature_repeat2] = "_func_signature_repeat2",
    [aux_sym__func_signature_repeat3] = "_func_signature_repeat3",
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
    [aux_sym_program_repeat1] = 1,
    [aux_sym_program_repeat2] = 1,
    [aux_sym_imports_block_repeat1] = 1,
    [aux_sym_block_statement_repeat1] = 1,
    [aux_sym_struct_type_repeat1] = 1,
    [aux_sym_interface_type_repeat1] = 1,
    [aux_sym_return_statement_repeat1] = 1,
    [aux_sym_declaration_statement_repeat1] = 1,
    [aux_sym__func_signature_repeat1] = 1,
    [aux_sym__func_signature_repeat2] = 1,
    [aux_sym__func_signature_repeat3] = 1,
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
                ADVANCE(41);
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
                ADVANCE(40);
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
                ADVANCE(40);
            LEX_ERROR();
        case 39:
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '\\')
                ADVANCE(38);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(40);
            ACCEPT_TOKEN(sym_string);
        case 40:
            if (lookahead == '\"')
                ADVANCE(37);
            if (lookahead == '\\')
                ADVANCE(38);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(40);
            LEX_ERROR();
        case 41:
            ACCEPT_TOKEN(aux_sym_STR_LPAREN);
        case 42:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(42);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 43:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(43);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '{')
                ADVANCE(44);
            LEX_ERROR();
        case 44:
            ACCEPT_TOKEN(aux_sym_STR_LBRACE);
        case 45:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(45);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(46);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            LEX_ERROR();
        case 46:
            ACCEPT_TOKEN(aux_sym_STR_RPAREN);
        case 47:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(47);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(48);
            if (lookahead == ',')
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
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(51);
            if (lookahead == 'm')
                ADVANCE(60);
            if (lookahead == 's')
                ADVANCE(63);
            LEX_ERROR();
        case 48:
            ACCEPT_TOKEN(aux_sym_STR_STAR);
        case 49:
            ACCEPT_TOKEN(aux_sym_STR_COMMA);
        case 50:
            ACCEPT_TOKEN(aux_sym_STR_LBRACK);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(52);
            ACCEPT_TOKEN(sym__identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(53);
            ACCEPT_TOKEN(sym__identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(54);
            ACCEPT_TOKEN(sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(55);
            ACCEPT_TOKEN(sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(56);
            ACCEPT_TOKEN(sym__identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(57);
            ACCEPT_TOKEN(sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(58);
            ACCEPT_TOKEN(sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(59);
            ACCEPT_TOKEN(sym__identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_interface);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(61);
            ACCEPT_TOKEN(sym__identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(62);
            ACCEPT_TOKEN(sym__identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_map);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(64);
            ACCEPT_TOKEN(sym__identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(65);
            ACCEPT_TOKEN(sym__identifier);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(66);
            ACCEPT_TOKEN(sym__identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(67);
            ACCEPT_TOKEN(sym__identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(68);
            ACCEPT_TOKEN(sym__identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_struct);
        case 69:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(69);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '{')
                ADVANCE(44);
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
                ADVANCE(46);
            if (lookahead == ',')
                ADVANCE(49);
            if (lookahead == '/')
                ADVANCE(3);
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
                ADVANCE(46);
            if (lookahead == ',')
                ADVANCE(49);
            if (lookahead == '/')
                ADVANCE(3);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
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
                ADVANCE(46);
            if (lookahead == '/')
                ADVANCE(3);
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
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(51);
            if (lookahead == 'm')
                ADVANCE(60);
            if (lookahead == 's')
                ADVANCE(63);
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
                ADVANCE(50);
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
            ACCEPT_TOKEN(aux_sym_STR_RBRACK);
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
            ACCEPT_TOKEN(aux_sym_STR_RBRACE);
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
                ADVANCE(41);
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
            ACCEPT_TOKEN(aux_sym_STR_SEMI);
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
            ACCEPT_TOKEN(aux_sym_STR_BANG);
        case 85:
            if (lookahead == '.')
                ADVANCE(86);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(85);
            ACCEPT_TOKEN(sym_number);
        case 86:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(87);
            LEX_ERROR();
        case 87:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(87);
            ACCEPT_TOKEN(sym_number);
        case 88:
            if (lookahead == '=')
                ADVANCE(89);
            LEX_ERROR();
        case 89:
            ACCEPT_TOKEN(aux_sym_STR_COLON_EQ);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(91);
            ACCEPT_TOKEN(sym__identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(92);
            ACCEPT_TOKEN(sym__identifier);
        case 92:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_for);
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(94);
            ACCEPT_TOKEN(sym__identifier);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_if);
        case 95:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(96);
            ACCEPT_TOKEN(sym__identifier);
        case 96:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(97);
            ACCEPT_TOKEN(sym__identifier);
        case 97:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(98);
            ACCEPT_TOKEN(sym__identifier);
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(99);
            ACCEPT_TOKEN(sym__identifier);
        case 99:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(100);
            ACCEPT_TOKEN(sym__identifier);
        case 100:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_return);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(102);
            ACCEPT_TOKEN(sym__identifier);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(103);
            ACCEPT_TOKEN(sym__identifier);
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_var);
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
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(48);
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
            ACCEPT_TOKEN(aux_sym_STR_AMP_AMP);
        case 107:
            ACCEPT_TOKEN(aux_sym_STR_PLUS);
        case 108:
            ACCEPT_TOKEN(aux_sym_STR_DASH);
        case 109:
            ACCEPT_TOKEN(aux_sym_STR_DOT);
        case 110:
            if (lookahead == '/')
                ADVANCE(4);
            ACCEPT_TOKEN(aux_sym_STR_SLASH);
        case 111:
            if (lookahead == '=')
                ADVANCE(112);
            ACCEPT_TOKEN(aux_sym_STR_LT);
        case 112:
            ACCEPT_TOKEN(aux_sym_STR_LT_EQ);
        case 113:
            if (lookahead == '=')
                ADVANCE(114);
            LEX_ERROR();
        case 114:
            ACCEPT_TOKEN(aux_sym_STR_EQ_EQ);
        case 115:
            if (lookahead == '=')
                ADVANCE(116);
            ACCEPT_TOKEN(aux_sym_STR_GT);
        case 116:
            ACCEPT_TOKEN(aux_sym_STR_GT_EQ);
        case 117:
            if (lookahead == '|')
                ADVANCE(118);
            LEX_ERROR();
        case 118:
            ACCEPT_TOKEN(aux_sym_STR_PIPE_PIPE);
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
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(48);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(49);
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
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(48);
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
                ADVANCE(44);
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
            ACCEPT_TOKEN(sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(126);
            ACCEPT_TOKEN(sym__identifier);
        case 126:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(127);
            ACCEPT_TOKEN(sym__identifier);
        case 127:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_else);
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
                ADVANCE(46);
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
                ADVANCE(41);
            if (lookahead == ')')
                ADVANCE(46);
            if (lookahead == '*')
                ADVANCE(48);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(49);
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
                ADVANCE(44);
            LEX_ERROR();
        case 131:
            if (lookahead == 'f')
                ADVANCE(132);
            LEX_ERROR();
        case 132:
            ACCEPT_TOKEN(aux_sym_STR_if);
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(49);
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
            ACCEPT_TOKEN(aux_sym_STR_range);
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
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(48);
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
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(48);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(49);
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
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(48);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(49);
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
        case 145:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(145);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(48);
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == '=')
                ADVANCE(146);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == '[')
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(51);
            if (lookahead == 'm')
                ADVANCE(60);
            if (lookahead == 's')
                ADVANCE(63);
            LEX_ERROR();
        case 146:
            ACCEPT_TOKEN(aux_sym_STR_EQ);
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
            if (lookahead == ';')
                ADVANCE(82);
            if (lookahead == '=')
                ADVANCE(146);
            LEX_ERROR();
        case 148:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(148);
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
                ADVANCE(146);
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
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == '*')
                ADVANCE(48);
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
            if (lookahead == '/')
                ADVANCE(3);
            if (lookahead == ';')
                ADVANCE(82);
            if (lookahead == '=')
                ADVANCE(146);
            if (lookahead == 'f')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(25);
            if (lookahead == 'v')
                ADVANCE(29);
            LEX_ERROR();
        case 152:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(152);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == ')')
                ADVANCE(46);
            if (lookahead == '/')
                ADVANCE(3);
            LEX_ERROR();
        case 153:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(13);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(153);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == ')')
                ADVANCE(46);
            if (lookahead == '*')
                ADVANCE(48);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(49);
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
                ADVANCE(154);
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
                ADVANCE(50);
            if (lookahead == ']')
                ADVANCE(76);
            if (lookahead == 'e')
                ADVANCE(124);
            if (lookahead == 'f')
                ADVANCE(155);
            if (lookahead == 'i')
                ADVANCE(159);
            if (lookahead == 'm')
                ADVANCE(60);
            if (lookahead == 'p')
                ADVANCE(165);
            if (lookahead == 'r')
                ADVANCE(172);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(177);
            if (lookahead == 'v')
                ADVANCE(101);
            if (lookahead == '{')
                ADVANCE(44);
            if (lookahead == '|')
                ADVANCE(117);
            if (lookahead == '}')
                ADVANCE(78);
            LEX_ERROR();
        case 154:
            if (lookahead == '=')
                ADVANCE(114);
            ACCEPT_TOKEN(aux_sym_STR_EQ);
        case 155:
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
                ADVANCE(156);
            ACCEPT_TOKEN(sym__identifier);
        case 156:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(157);
            ACCEPT_TOKEN(sym__identifier);
        case 157:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(158);
            ACCEPT_TOKEN(sym__identifier);
        case 158:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_func);
        case 159:
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
                ADVANCE(160);
            if (lookahead == 'n')
                ADVANCE(52);
            ACCEPT_TOKEN(sym__identifier);
        case 160:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(161);
            ACCEPT_TOKEN(sym__identifier);
        case 161:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(162);
            ACCEPT_TOKEN(sym__identifier);
        case 162:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(163);
            ACCEPT_TOKEN(sym__identifier);
        case 163:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(164);
            ACCEPT_TOKEN(sym__identifier);
        case 164:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_import);
        case 165:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(166);
            ACCEPT_TOKEN(sym__identifier);
        case 166:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'c')
                ADVANCE(167);
            ACCEPT_TOKEN(sym__identifier);
        case 167:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'k')
                ADVANCE(168);
            ACCEPT_TOKEN(sym__identifier);
        case 168:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(169);
            ACCEPT_TOKEN(sym__identifier);
        case 169:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(170);
            ACCEPT_TOKEN(sym__identifier);
        case 170:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(171);
            ACCEPT_TOKEN(sym__identifier);
        case 171:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_package);
        case 172:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(173);
            if (lookahead == 'e')
                ADVANCE(96);
            ACCEPT_TOKEN(sym__identifier);
        case 173:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(174);
            ACCEPT_TOKEN(sym__identifier);
        case 174:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(175);
            ACCEPT_TOKEN(sym__identifier);
        case 175:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(176);
            ACCEPT_TOKEN(sym__identifier);
        case 176:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            ACCEPT_TOKEN(aux_sym_STR_range);
        case 177:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(33);
            if (lookahead == 'y')
                ADVANCE(178);
            ACCEPT_TOKEN(sym__identifier);
        case 178:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(179);
            ACCEPT_TOKEN(sym__identifier);
        case 179:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(180);
            ACCEPT_TOKEN(sym__identifier);
        case 180:
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
                ADVANCE(153);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(84);
            if (lookahead == '\"')
                ADVANCE(36);
            if (lookahead == '&')
                ADVANCE(105);
            if (lookahead == '(')
                ADVANCE(41);
            if (lookahead == ')')
                ADVANCE(46);
            if (lookahead == '*')
                ADVANCE(48);
            if (lookahead == '+')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(49);
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
                ADVANCE(154);
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
                ADVANCE(50);
            if (lookahead == ']')
                ADVANCE(76);
            if (lookahead == 'e')
                ADVANCE(124);
            if (lookahead == 'f')
                ADVANCE(155);
            if (lookahead == 'i')
                ADVANCE(159);
            if (lookahead == 'm')
                ADVANCE(60);
            if (lookahead == 'p')
                ADVANCE(165);
            if (lookahead == 'r')
                ADVANCE(172);
            if (lookahead == 's')
                ADVANCE(63);
            if (lookahead == 't')
                ADVANCE(177);
            if (lookahead == 'v')
                ADVANCE(101);
            if (lookahead == '{')
                ADVANCE(44);
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
    [8] = 34,
    [9] = 34,
    [10] = 12,
    [11] = 35,
    [12] = 32,
    [13] = 32,
    [14] = 32,
    [15] = 42,
    [16] = 42,
    [17] = 43,
    [18] = 45,
    [19] = 47,
    [20] = 47,
    [21] = 69,
    [22] = 43,
    [23] = 43,
    [24] = 32,
    [25] = 32,
    [26] = 70,
    [27] = 71,
    [28] = 72,
    [29] = 43,
    [30] = 32,
    [31] = 70,
    [32] = 70,
    [33] = 72,
    [34] = 43,
    [35] = 70,
    [36] = 70,
    [37] = 72,
    [38] = 32,
    [39] = 32,
    [40] = 32,
    [41] = 70,
    [42] = 72,
    [43] = 43,
    [44] = 70,
    [45] = 70,
    [46] = 70,
    [47] = 73,
    [48] = 73,
    [49] = 74,
    [50] = 75,
    [51] = 43,
    [52] = 43,
    [53] = 32,
    [54] = 47,
    [55] = 73,
    [56] = 77,
    [57] = 42,
    [58] = 79,
    [59] = 70,
    [60] = 70,
    [61] = 77,
    [62] = 45,
    [63] = 47,
    [64] = 80,
    [65] = 77,
    [66] = 32,
    [67] = 32,
    [68] = 70,
    [69] = 72,
    [70] = 77,
    [71] = 77,
    [72] = 70,
    [73] = 72,
    [74] = 77,
    [75] = 70,
    [76] = 73,
    [77] = 70,
    [78] = 72,
    [79] = 80,
    [80] = 32,
    [81] = 47,
    [82] = 70,
    [83] = 73,
    [84] = 70,
    [85] = 72,
    [86] = 72,
    [87] = 32,
    [88] = 32,
    [89] = 70,
    [90] = 72,
    [91] = 77,
    [92] = 77,
    [93] = 70,
    [94] = 72,
    [95] = 77,
    [96] = 80,
    [97] = 32,
    [98] = 32,
    [99] = 70,
    [100] = 70,
    [101] = 72,
    [102] = 77,
    [103] = 72,
    [104] = 80,
    [105] = 32,
    [106] = 32,
    [107] = 70,
    [108] = 72,
    [109] = 70,
    [110] = 79,
    [111] = 77,
    [112] = 73,
    [113] = 73,
    [114] = 79,
    [115] = 70,
    [116] = 70,
    [117] = 77,
    [118] = 77,
    [119] = 77,
    [120] = 73,
    [121] = 74,
    [122] = 75,
    [123] = 43,
    [124] = 43,
    [125] = 77,
    [126] = 79,
    [127] = 77,
    [128] = 77,
    [129] = 77,
    [130] = 79,
    [131] = 77,
    [132] = 77,
    [133] = 73,
    [134] = 77,
    [135] = 73,
    [136] = 75,
    [137] = 75,
    [138] = 75,
    [139] = 73,
    [140] = 74,
    [141] = 75,
    [142] = 43,
    [143] = 43,
    [144] = 77,
    [145] = 79,
    [146] = 75,
    [147] = 75,
    [148] = 77,
    [149] = 79,
    [150] = 75,
    [151] = 75,
    [152] = 73,
    [153] = 75,
    [154] = 73,
    [155] = 75,
    [156] = 73,
    [157] = 75,
    [158] = 75,
    [159] = 73,
    [160] = 77,
    [161] = 77,
    [162] = 79,
    [163] = 73,
    [164] = 70,
    [165] = 73,
    [166] = 75,
    [167] = 73,
    [168] = 70,
    [169] = 70,
    [170] = 70,
    [171] = 72,
    [172] = 69,
    [173] = 32,
    [174] = 32,
    [175] = 70,
    [176] = 72,
    [177] = 43,
    [178] = 43,
    [179] = 70,
    [180] = 72,
    [181] = 43,
    [182] = 69,
    [183] = 32,
    [184] = 32,
    [185] = 70,
    [186] = 70,
    [187] = 72,
    [188] = 43,
    [189] = 72,
    [190] = 69,
    [191] = 32,
    [192] = 32,
    [193] = 70,
    [194] = 72,
    [195] = 70,
    [196] = 81,
    [197] = 83,
    [198] = 83,
    [199] = 83,
    [200] = 83,
    [201] = 104,
    [202] = 104,
    [203] = 119,
    [204] = 79,
    [205] = 119,
    [206] = 32,
    [207] = 81,
    [208] = 120,
    [209] = 121,
    [210] = 32,
    [211] = 121,
    [212] = 121,
    [213] = 104,
    [214] = 104,
    [215] = 122,
    [216] = 122,
    [217] = 122,
    [218] = 121,
    [219] = 122,
    [220] = 123,
    [221] = 128,
    [222] = 83,
    [223] = 121,
    [224] = 32,
    [225] = 121,
    [226] = 121,
    [227] = 121,
    [228] = 121,
    [229] = 122,
    [230] = 122,
    [231] = 122,
    [232] = 122,
    [233] = 122,
    [234] = 122,
    [235] = 79,
    [236] = 123,
    [237] = 123,
    [238] = 129,
    [239] = 129,
    [240] = 129,
    [241] = 122,
    [242] = 121,
    [243] = 129,
    [244] = 72,
    [245] = 128,
    [246] = 122,
    [247] = 121,
    [248] = 121,
    [249] = 32,
    [250] = 121,
    [251] = 121,
    [252] = 121,
    [253] = 121,
    [254] = 129,
    [255] = 129,
    [256] = 129,
    [257] = 129,
    [258] = 129,
    [259] = 129,
    [260] = 72,
    [261] = 129,
    [262] = 129,
    [263] = 129,
    [264] = 72,
    [265] = 129,
    [266] = 129,
    [267] = 122,
    [268] = 130,
    [269] = 83,
    [270] = 83,
    [271] = 79,
    [272] = 83,
    [273] = 83,
    [274] = 133,
    [275] = 133,
    [276] = 32,
    [277] = 134,
    [278] = 121,
    [279] = 122,
    [280] = 83,
    [281] = 140,
    [282] = 140,
    [283] = 134,
    [284] = 121,
    [285] = 122,
    [286] = 83,
    [287] = 104,
    [288] = 141,
    [289] = 128,
    [290] = 121,
    [291] = 32,
    [292] = 121,
    [293] = 121,
    [294] = 121,
    [295] = 121,
    [296] = 104,
    [297] = 104,
    [298] = 104,
    [299] = 104,
    [300] = 104,
    [301] = 104,
    [302] = 129,
    [303] = 104,
    [304] = 72,
    [305] = 104,
    [306] = 104,
    [307] = 142,
    [308] = 142,
    [309] = 143,
    [310] = 142,
    [311] = 121,
    [312] = 142,
    [313] = 144,
    [314] = 81,
    [315] = 128,
    [316] = 121,
    [317] = 121,
    [318] = 32,
    [319] = 121,
    [320] = 121,
    [321] = 121,
    [322] = 121,
    [323] = 142,
    [324] = 142,
    [325] = 142,
    [326] = 142,
    [327] = 142,
    [328] = 142,
    [329] = 81,
    [330] = 142,
    [331] = 129,
    [332] = 142,
    [333] = 72,
    [334] = 142,
    [335] = 142,
    [336] = 143,
    [337] = 145,
    [338] = 145,
    [339] = 147,
    [340] = 147,
    [341] = 147,
    [342] = 121,
    [343] = 73,
    [344] = 74,
    [345] = 75,
    [346] = 43,
    [347] = 43,
    [348] = 77,
    [349] = 79,
    [350] = 147,
    [351] = 147,
    [352] = 77,
    [353] = 79,
    [354] = 147,
    [355] = 147,
    [356] = 73,
    [357] = 147,
    [358] = 73,
    [359] = 75,
    [360] = 73,
    [361] = 147,
    [362] = 147,
    [363] = 104,
    [364] = 141,
    [365] = 148,
    [366] = 121,
    [367] = 104,
    [368] = 141,
    [369] = 81,
    [370] = 140,
    [371] = 32,
    [372] = 121,
    [373] = 104,
    [374] = 141,
    [375] = 133,
    [376] = 133,
    [377] = 140,
    [378] = 121,
    [379] = 104,
    [380] = 141,
    [381] = 141,
    [382] = 79,
    [383] = 149,
    [384] = 145,
    [385] = 147,
    [386] = 121,
    [387] = 104,
    [388] = 150,
    [389] = 151,
    [390] = 121,
    [391] = 104,
    [392] = 150,
    [393] = 73,
    [394] = 73,
    [395] = 81,
    [396] = 81,
    [397] = 81,
    [398] = 73,
    [399] = 74,
    [400] = 75,
    [401] = 43,
    [402] = 43,
    [403] = 77,
    [404] = 79,
    [405] = 81,
    [406] = 81,
    [407] = 77,
    [408] = 79,
    [409] = 81,
    [410] = 81,
    [411] = 73,
    [412] = 81,
    [413] = 73,
    [414] = 75,
    [415] = 73,
    [416] = 81,
    [417] = 81,
    [418] = 149,
    [419] = 14,
    [420] = 14,
    [421] = 152,
    [422] = 152,
    [423] = 72,
    [424] = 152,
    [425] = 14,
    [426] = 14,
    [427] = 72,
    [428] = 12,
    [429] = 12,
    [430] = 34,
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
        [aux_sym_program_repeat1] = SHIFT(9),
        [aux_sym_program_repeat2] = SHIFT(10),
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
        [aux_sym_program_repeat1] = REDUCE(sym_package_directive, 2),
        [aux_sym_program_repeat2] = REDUCE(sym_package_directive, 2),
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
        [aux_sym_program_repeat1] = REDUCE(sym_package_name, 1),
        [aux_sym_program_repeat2] = REDUCE(sym_package_name, 1),
        [aux_sym_STR_import] = REDUCE(sym_package_name, 1),
        [aux_sym_STR_type] = REDUCE(sym_package_name, 1),
        [aux_sym_STR_var] = REDUCE(sym_package_name, 1),
        [aux_sym_STR_func] = REDUCE(sym_package_name, 1),
    },
    [6] = {
        [sym_imports_block] = SHIFT(6),
        [sym_declaration] = REDUCE(aux_sym_program_repeat1, 1),
        [sym_type_declaration] = REDUCE(aux_sym_program_repeat1, 1),
        [sym_var_declaration] = REDUCE(aux_sym_program_repeat1, 1),
        [sym_func_declaration] = REDUCE(aux_sym_program_repeat1, 1),
        [ts_builtin_sym_end] = REDUCE(aux_sym_program_repeat1, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = SHIFT(430),
        [aux_sym_program_repeat2] = REDUCE(aux_sym_program_repeat1, 1),
        [aux_sym_STR_import] = SHIFT(11),
        [aux_sym_STR_type] = REDUCE(aux_sym_program_repeat1, 1),
        [aux_sym_STR_var] = REDUCE(aux_sym_program_repeat1, 1),
        [aux_sym_STR_func] = REDUCE(aux_sym_program_repeat1, 1),
    },
    [7] = {
        [sym_declaration] = SHIFT(7),
        [sym_type_declaration] = SHIFT(8),
        [sym_var_declaration] = SHIFT(8),
        [sym_func_declaration] = SHIFT(8),
        [ts_builtin_sym_end] = REDUCE(aux_sym_program_repeat2, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat2] = SHIFT(429),
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
        [aux_sym_program_repeat2] = REDUCE(sym_declaration, 1),
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
        [aux_sym_program_repeat2] = SHIFT(428),
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
        [sym_package_import] = SHIFT(419),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(420),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(421),
    },
    [12] = {
        [sym_type_name] = SHIFT(393),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(394),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [13] = {
        [sym_var_name] = SHIFT(384),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(338),
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
        [sym_block_statement] = SHIFT(196),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(197),
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
        [aux_sym_declaration_statement_repeat1] = SHIFT(47),
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
        [aux_sym_declaration_statement_repeat1] = REDUCE(sym_var_name, 1),
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
        [aux_sym__func_signature_repeat3] = SHIFT(28),
        [aux_sym_STR_RPAREN] = SHIFT(29),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [27] = {
        [sym_type_name] = REDUCE(sym_var_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = REDUCE(sym_type_name, 1),
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
        [aux_sym__func_signature_repeat3] = SHIFT(33),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat3, 2),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [32] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_type_name, 1),
    },
    [33] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat3, 3),
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
        [aux_sym__func_signature_repeat2] = SHIFT(37),
        [aux_sym_STR_RPAREN] = SHIFT(34),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [36] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = REDUCE(sym_type_name, 1),
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
        [aux_sym__func_signature_repeat2] = SHIFT(42),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 3),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [42] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat2, 4),
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
        [aux_sym__func_signature_repeat1] = SHIFT(189),
        [aux_sym_STR_RPAREN] = SHIFT(190),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [45] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_type_expression, 1),
    },
    [46] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_type_name, 1),
    },
    [47] = {
        [sym_type_expression] = SHIFT(170),
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
    [49] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(165),
    },
    [50] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(163),
    },
    [51] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(111),
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
        [sym_type_expression] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [sym_pointer_type] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [sym_map_type] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [sym_slice_type] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [sym_struct_type] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [sym_interface_type] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [sym_type_name] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat1] = SHIFT(55),
        [aux_sym_STR_STAR] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [aux_sym_STR_map] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [aux_sym_STR_LBRACK] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [aux_sym_STR_struct] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [aux_sym_STR_interface] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
        [aux_sym_STR_COMMA] = SHIFT(53),
    },
    [55] = {
        [sym_type_expression] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [sym_pointer_type] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [sym_map_type] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [sym_slice_type] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [sym_struct_type] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [sym_interface_type] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [sym_type_name] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [aux_sym_STR_map] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [aux_sym_STR_LBRACK] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [aux_sym_STR_struct] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
        [aux_sym_STR_interface] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
    },
    [56] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = SHIFT(58),
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
        [aux_sym__func_signature_repeat1] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_interface_type, 3),
    },
    [60] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_RPAREN] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_interface_type, 4),
    },
    [61] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = SHIFT(110),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_interface_type_repeat1, 2),
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
        [aux_sym_declaration_statement_repeat1] = SHIFT(76),
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
        [aux_sym_interface_type_repeat1] = REDUCE_FRAGILE(sym__func_signature, 2),
        [aux_sym_STR_LPAREN] = SHIFT(66),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 2),
    },
    [65] = {
        [sym_var_name] = REDUCE(sym__func_signature, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = REDUCE(sym__func_signature, 3),
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
        [aux_sym__func_signature_repeat3] = SHIFT(69),
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
        [aux_sym_interface_type_repeat1] = REDUCE(sym__func_signature, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 5),
    },
    [71] = {
        [sym_var_name] = REDUCE(sym__func_signature, 6),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 6),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = REDUCE(sym__func_signature, 6),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 6),
    },
    [72] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(73),
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
        [aux_sym_interface_type_repeat1] = REDUCE(sym__func_signature, 7),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 7),
    },
    [75] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = SHIFT(103),
        [aux_sym_STR_RPAREN] = SHIFT(104),
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
        [aux_sym__func_signature_repeat1] = SHIFT(78),
        [aux_sym_STR_RPAREN] = SHIFT(79),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [78] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(96),
    },
    [79] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 5),
        [sym_type_name] = SHIFT(71),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE_FRAGILE(sym__func_signature, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = REDUCE_FRAGILE(sym__func_signature, 5),
        [aux_sym_STR_LPAREN] = SHIFT(87),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 5),
    },
    [80] = {
        [sym_var_name] = SHIFT(81),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(20),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [81] = {
        [sym_type_expression] = SHIFT(82),
        [sym_pointer_type] = SHIFT(45),
        [sym_map_type] = SHIFT(45),
        [sym_slice_type] = SHIFT(45),
        [sym_struct_type] = SHIFT(45),
        [sym_interface_type] = SHIFT(45),
        [sym_type_name] = SHIFT(45),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(46),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat1] = SHIFT(83),
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
        [aux_sym_STR_COMMA] = SHIFT(53),
    },
    [82] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = SHIFT(86),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat1, 3),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [83] = {
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
        [aux_sym_STR_STAR] = SHIFT(48),
        [aux_sym_STR_map] = SHIFT(49),
        [aux_sym_STR_LBRACK] = SHIFT(50),
        [aux_sym_STR_struct] = SHIFT(51),
        [aux_sym_STR_interface] = SHIFT(52),
    },
    [84] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = SHIFT(85),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat1, 4),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [85] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat1, 5),
    },
    [86] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym__func_signature_repeat1, 4),
    },
    [87] = {
        [sym_var_name] = SHIFT(88),
        [sym_type_name] = SHIFT(89),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [88] = {
        [sym_type_name] = SHIFT(93),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [89] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(90),
        [aux_sym_STR_RPAREN] = SHIFT(91),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [90] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(92),
    },
    [91] = {
        [sym_var_name] = REDUCE(sym__func_signature, 8),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 8),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = REDUCE(sym__func_signature, 8),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 8),
    },
    [92] = {
        [sym_var_name] = REDUCE(sym__func_signature, 9),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 9),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = REDUCE(sym__func_signature, 9),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 9),
    },
    [93] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(94),
        [aux_sym_STR_RPAREN] = SHIFT(92),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [94] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(95),
    },
    [95] = {
        [sym_var_name] = REDUCE(sym__func_signature, 10),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 10),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = REDUCE(sym__func_signature, 10),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 10),
    },
    [96] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 6),
        [sym_type_name] = SHIFT(74),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE_FRAGILE(sym__func_signature, 6),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = REDUCE_FRAGILE(sym__func_signature, 6),
        [aux_sym_STR_LPAREN] = SHIFT(97),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 6),
    },
    [97] = {
        [sym_var_name] = SHIFT(98),
        [sym_type_name] = SHIFT(99),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [98] = {
        [sym_type_name] = SHIFT(100),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [99] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(94),
        [aux_sym_STR_RPAREN] = SHIFT(92),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [100] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(101),
        [aux_sym_STR_RPAREN] = SHIFT(95),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [101] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(102),
    },
    [102] = {
        [sym_var_name] = REDUCE(sym__func_signature, 11),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym__func_signature, 11),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = REDUCE(sym__func_signature, 11),
        [aux_sym_STR_RBRACE] = REDUCE(sym__func_signature, 11),
    },
    [103] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(79),
    },
    [104] = {
        [sym_var_name] = REDUCE_FRAGILE(sym__func_signature, 4),
        [sym_type_name] = SHIFT(70),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE_FRAGILE(sym__func_signature, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = REDUCE_FRAGILE(sym__func_signature, 4),
        [aux_sym_STR_LPAREN] = SHIFT(105),
        [aux_sym_STR_RBRACE] = REDUCE_FRAGILE(sym__func_signature, 4),
    },
    [105] = {
        [sym_var_name] = SHIFT(106),
        [sym_type_name] = SHIFT(107),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [106] = {
        [sym_type_name] = SHIFT(109),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [107] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(108),
        [aux_sym_STR_RPAREN] = SHIFT(74),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [108] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(91),
    },
    [109] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(90),
        [aux_sym_STR_RPAREN] = SHIFT(91),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [110] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_interface_type_repeat1, 3),
    },
    [111] = {
        [sym_var_name] = SHIFT(112),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(113),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = SHIFT(114),
        [aux_sym_STR_RBRACE] = SHIFT(115),
    },
    [112] = {
        [sym_type_expression] = SHIFT(117),
        [sym_pointer_type] = SHIFT(118),
        [sym_map_type] = SHIFT(118),
        [sym_slice_type] = SHIFT(118),
        [sym_struct_type] = SHIFT(118),
        [sym_interface_type] = SHIFT(118),
        [sym_type_name] = SHIFT(118),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(119),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(120),
        [aux_sym_STR_map] = SHIFT(121),
        [aux_sym_STR_LBRACK] = SHIFT(122),
        [aux_sym_STR_struct] = SHIFT(123),
        [aux_sym_STR_interface] = SHIFT(124),
    },
    [113] = {
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
    [114] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(116),
    },
    [115] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_struct_type, 3),
    },
    [116] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_RPAREN] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_struct_type, 4),
    },
    [117] = {
        [sym_var_name] = SHIFT(112),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(113),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = SHIFT(162),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_struct_type_repeat1, 2),
    },
    [118] = {
        [sym_var_name] = REDUCE(sym_type_expression, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_type_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_type_expression, 1),
    },
    [119] = {
        [sym_var_name] = REDUCE(sym_type_name, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_type_name, 1),
    },
    [120] = {
        [sym_type_expression] = SHIFT(161),
        [sym_pointer_type] = SHIFT(118),
        [sym_map_type] = SHIFT(118),
        [sym_slice_type] = SHIFT(118),
        [sym_struct_type] = SHIFT(118),
        [sym_interface_type] = SHIFT(118),
        [sym_type_name] = SHIFT(118),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(119),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(120),
        [aux_sym_STR_map] = SHIFT(121),
        [aux_sym_STR_LBRACK] = SHIFT(122),
        [aux_sym_STR_struct] = SHIFT(123),
        [aux_sym_STR_interface] = SHIFT(124),
    },
    [121] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(135),
    },
    [122] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(133),
    },
    [123] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(129),
    },
    [124] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(125),
    },
    [125] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = SHIFT(126),
        [aux_sym_STR_RBRACE] = SHIFT(127),
    },
    [126] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(128),
    },
    [127] = {
        [sym_var_name] = REDUCE(sym_interface_type, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_interface_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_interface_type, 3),
    },
    [128] = {
        [sym_var_name] = REDUCE(sym_interface_type, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_interface_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_interface_type, 4),
    },
    [129] = {
        [sym_var_name] = SHIFT(112),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(113),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = SHIFT(130),
        [aux_sym_STR_RBRACE] = SHIFT(131),
    },
    [130] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(132),
    },
    [131] = {
        [sym_var_name] = REDUCE(sym_struct_type, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_struct_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_struct_type, 3),
    },
    [132] = {
        [sym_var_name] = REDUCE(sym_struct_type, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_struct_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_struct_type, 4),
    },
    [133] = {
        [sym_type_expression] = SHIFT(134),
        [sym_pointer_type] = SHIFT(118),
        [sym_map_type] = SHIFT(118),
        [sym_slice_type] = SHIFT(118),
        [sym_struct_type] = SHIFT(118),
        [sym_interface_type] = SHIFT(118),
        [sym_type_name] = SHIFT(118),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(119),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(120),
        [aux_sym_STR_map] = SHIFT(121),
        [aux_sym_STR_LBRACK] = SHIFT(122),
        [aux_sym_STR_struct] = SHIFT(123),
        [aux_sym_STR_interface] = SHIFT(124),
    },
    [134] = {
        [sym_var_name] = REDUCE(sym_slice_type, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_slice_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_slice_type, 3),
    },
    [135] = {
        [sym_type_expression] = SHIFT(136),
        [sym_pointer_type] = SHIFT(137),
        [sym_map_type] = SHIFT(137),
        [sym_slice_type] = SHIFT(137),
        [sym_struct_type] = SHIFT(137),
        [sym_interface_type] = SHIFT(137),
        [sym_type_name] = SHIFT(137),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(138),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(139),
        [aux_sym_STR_map] = SHIFT(140),
        [aux_sym_STR_LBRACK] = SHIFT(141),
        [aux_sym_STR_struct] = SHIFT(142),
        [aux_sym_STR_interface] = SHIFT(143),
    },
    [136] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(159),
    },
    [137] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_type_expression, 1),
    },
    [138] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_type_name, 1),
    },
    [139] = {
        [sym_type_expression] = SHIFT(158),
        [sym_pointer_type] = SHIFT(137),
        [sym_map_type] = SHIFT(137),
        [sym_slice_type] = SHIFT(137),
        [sym_struct_type] = SHIFT(137),
        [sym_interface_type] = SHIFT(137),
        [sym_type_name] = SHIFT(137),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(138),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(139),
        [aux_sym_STR_map] = SHIFT(140),
        [aux_sym_STR_LBRACK] = SHIFT(141),
        [aux_sym_STR_struct] = SHIFT(142),
        [aux_sym_STR_interface] = SHIFT(143),
    },
    [140] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(154),
    },
    [141] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(152),
    },
    [142] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(148),
    },
    [143] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(144),
    },
    [144] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = SHIFT(145),
        [aux_sym_STR_RBRACE] = SHIFT(146),
    },
    [145] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(147),
    },
    [146] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_interface_type, 3),
    },
    [147] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_interface_type, 4),
    },
    [148] = {
        [sym_var_name] = SHIFT(112),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(113),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = SHIFT(149),
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
        [aux_sym_STR_RBRACK] = REDUCE(sym_struct_type, 3),
    },
    [151] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_struct_type, 4),
    },
    [152] = {
        [sym_type_expression] = SHIFT(153),
        [sym_pointer_type] = SHIFT(137),
        [sym_map_type] = SHIFT(137),
        [sym_slice_type] = SHIFT(137),
        [sym_struct_type] = SHIFT(137),
        [sym_interface_type] = SHIFT(137),
        [sym_type_name] = SHIFT(137),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(138),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(139),
        [aux_sym_STR_map] = SHIFT(140),
        [aux_sym_STR_LBRACK] = SHIFT(141),
        [aux_sym_STR_struct] = SHIFT(142),
        [aux_sym_STR_interface] = SHIFT(143),
    },
    [153] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_slice_type, 3),
    },
    [154] = {
        [sym_type_expression] = SHIFT(155),
        [sym_pointer_type] = SHIFT(137),
        [sym_map_type] = SHIFT(137),
        [sym_slice_type] = SHIFT(137),
        [sym_struct_type] = SHIFT(137),
        [sym_interface_type] = SHIFT(137),
        [sym_type_name] = SHIFT(137),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(138),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(139),
        [aux_sym_STR_map] = SHIFT(140),
        [aux_sym_STR_LBRACK] = SHIFT(141),
        [aux_sym_STR_struct] = SHIFT(142),
        [aux_sym_STR_interface] = SHIFT(143),
    },
    [155] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(156),
    },
    [156] = {
        [sym_type_expression] = SHIFT(157),
        [sym_pointer_type] = SHIFT(137),
        [sym_map_type] = SHIFT(137),
        [sym_slice_type] = SHIFT(137),
        [sym_struct_type] = SHIFT(137),
        [sym_interface_type] = SHIFT(137),
        [sym_type_name] = SHIFT(137),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(138),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(139),
        [aux_sym_STR_map] = SHIFT(140),
        [aux_sym_STR_LBRACK] = SHIFT(141),
        [aux_sym_STR_struct] = SHIFT(142),
        [aux_sym_STR_interface] = SHIFT(143),
    },
    [157] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_map_type, 5),
    },
    [158] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = REDUCE(sym_pointer_type, 2),
    },
    [159] = {
        [sym_type_expression] = SHIFT(160),
        [sym_pointer_type] = SHIFT(118),
        [sym_map_type] = SHIFT(118),
        [sym_slice_type] = SHIFT(118),
        [sym_struct_type] = SHIFT(118),
        [sym_interface_type] = SHIFT(118),
        [sym_type_name] = SHIFT(118),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(119),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(120),
        [aux_sym_STR_map] = SHIFT(121),
        [aux_sym_STR_LBRACK] = SHIFT(122),
        [aux_sym_STR_struct] = SHIFT(123),
        [aux_sym_STR_interface] = SHIFT(124),
    },
    [160] = {
        [sym_var_name] = REDUCE(sym_map_type, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_map_type, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym_map_type, 5),
    },
    [161] = {
        [sym_var_name] = REDUCE(sym_pointer_type, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = REDUCE(sym_pointer_type, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_pointer_type, 2),
    },
    [162] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_struct_type_repeat1, 3),
    },
    [163] = {
        [sym_type_expression] = SHIFT(164),
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
    [164] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_RPAREN] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_slice_type, 3),
    },
    [165] = {
        [sym_type_expression] = SHIFT(166),
        [sym_pointer_type] = SHIFT(137),
        [sym_map_type] = SHIFT(137),
        [sym_slice_type] = SHIFT(137),
        [sym_struct_type] = SHIFT(137),
        [sym_interface_type] = SHIFT(137),
        [sym_type_name] = SHIFT(137),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(138),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(139),
        [aux_sym_STR_map] = SHIFT(140),
        [aux_sym_STR_LBRACK] = SHIFT(141),
        [aux_sym_STR_struct] = SHIFT(142),
        [aux_sym_STR_interface] = SHIFT(143),
    },
    [166] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(167),
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
        [aux_sym__func_signature_repeat1] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_RPAREN] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_COMMA] = REDUCE(sym_map_type, 5),
    },
    [169] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_RPAREN] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_COMMA] = REDUCE(sym_pointer_type, 2),
    },
    [170] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat1] = SHIFT(171),
        [aux_sym_STR_RPAREN] = SHIFT(172),
        [aux_sym_STR_COMMA] = SHIFT(80),
    },
    [171] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(182),
    },
    [172] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 5),
        [sym_type_name] = SHIFT(34),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(173),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 5),
    },
    [173] = {
        [sym_var_name] = SHIFT(174),
        [sym_type_name] = SHIFT(175),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [174] = {
        [sym_type_name] = SHIFT(179),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [175] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(176),
        [aux_sym_STR_RPAREN] = SHIFT(177),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [176] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(178),
    },
    [177] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 8),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 8),
    },
    [178] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 9),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 9),
    },
    [179] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(180),
        [aux_sym_STR_RPAREN] = SHIFT(178),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [180] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(181),
    },
    [181] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 10),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 10),
    },
    [182] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 6),
        [sym_type_name] = SHIFT(43),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(183),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 6),
    },
    [183] = {
        [sym_var_name] = SHIFT(184),
        [sym_type_name] = SHIFT(185),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [184] = {
        [sym_type_name] = SHIFT(186),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [185] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(180),
        [aux_sym_STR_RPAREN] = SHIFT(178),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [186] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(187),
        [aux_sym_STR_RPAREN] = SHIFT(181),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [187] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(188),
    },
    [188] = {
        [sym_block_statement] = REDUCE(sym__func_signature, 11),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = REDUCE(sym__func_signature, 11),
    },
    [189] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(172),
    },
    [190] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym__func_signature, 4),
        [sym_type_name] = SHIFT(29),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(23),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(191),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym__func_signature, 4),
    },
    [191] = {
        [sym_var_name] = SHIFT(192),
        [sym_type_name] = SHIFT(193),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(27),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [192] = {
        [sym_type_name] = SHIFT(195),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(36),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [193] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat3] = SHIFT(194),
        [aux_sym_STR_RPAREN] = SHIFT(43),
        [aux_sym_STR_COMMA] = SHIFT(30),
    },
    [194] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(177),
    },
    [195] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym__func_signature_repeat2] = SHIFT(176),
        [aux_sym_STR_RPAREN] = SHIFT(177),
        [aux_sym_STR_COMMA] = SHIFT(38),
    },
    [196] = {
        [sym__line_break] = SHIFT(383),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(383),
    },
    [197] = {
        [sym_var_declaration] = SHIFT(198),
        [sym_statement] = SHIFT(199),
        [sym_return_statement] = SHIFT(200),
        [sym_declaration_statement] = SHIFT(200),
        [sym_range_statement] = SHIFT(200),
        [sym_if_statement] = SHIFT(200),
        [sym_expression_statement] = SHIFT(200),
        [sym_expression] = SHIFT(201),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(203),
        [ts_builtin_sym_error] = SHIFT(204),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(205),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat1] = SHIFT(204),
        [aux_sym_STR_var] = SHIFT(206),
        [aux_sym_STR_RBRACE] = SHIFT(207),
        [aux_sym_STR_return] = SHIFT(208),
        [aux_sym_STR_COLON_EQ] = SHIFT(209),
        [aux_sym_STR_for] = SHIFT(210),
        [aux_sym_STR_if] = SHIFT(211),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [198] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_var] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_return] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_for] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_if] = REDUCE(sym_declaration_statement, 1),
        [aux_sym_STR_BANG] = REDUCE(sym_declaration_statement, 1),
    },
    [199] = {
        [sym_var_declaration] = SHIFT(198),
        [sym_statement] = SHIFT(199),
        [sym_return_statement] = SHIFT(200),
        [sym_declaration_statement] = SHIFT(200),
        [sym_range_statement] = SHIFT(200),
        [sym_if_statement] = SHIFT(200),
        [sym_expression_statement] = SHIFT(200),
        [sym_expression] = SHIFT(201),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(203),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(205),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat1] = SHIFT(382),
        [aux_sym_STR_var] = SHIFT(206),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_block_statement_repeat1, 1),
        [aux_sym_STR_return] = SHIFT(208),
        [aux_sym_STR_COLON_EQ] = SHIFT(209),
        [aux_sym_STR_for] = SHIFT(210),
        [aux_sym_STR_if] = SHIFT(211),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [200] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_statement, 1),
        [aux_sym_STR_var] = REDUCE(sym_statement, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_statement, 1),
        [aux_sym_STR_return] = REDUCE(sym_statement, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_statement, 1),
        [aux_sym_STR_for] = REDUCE(sym_statement, 1),
        [aux_sym_STR_if] = REDUCE(sym_statement, 1),
        [aux_sym_STR_BANG] = REDUCE(sym_statement, 1),
    },
    [201] = {
        [sym__line_break] = SHIFT(381),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(289),
        [aux_sym_STR_SEMI] = SHIFT(381),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = SHIFT(291),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = SHIFT(292),
        [aux_sym_STR_DASH] = SHIFT(292),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(293),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [202] = {
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
    [203] = {
        [sym__line_break] = REDUCE(sym_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat1] = SHIFT(370),
        [aux_sym_STR_LPAREN] = REDUCE(sym_expression, 1),
        [aux_sym_STR_SEMI] = REDUCE(sym_expression, 1),
        [aux_sym_STR_STAR] = REDUCE(sym_expression, 1),
        [aux_sym_STR_COMMA] = SHIFT(371),
        [aux_sym_STR_COLON_EQ] = SHIFT(372),
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
    [204] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(369),
    },
    [205] = {
        [sym__line_break] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat1] = REDUCE(sym_var_name, 1),
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
    [206] = {
        [sym_var_name] = SHIFT(337),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(338),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [207] = {
        [sym__line_break] = REDUCE(sym_block_statement, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_block_statement, 2),
    },
    [208] = {
        [sym_expression] = SHIFT(307),
        [sym_call_expression] = SHIFT(308),
        [sym_selector_expression] = SHIFT(308),
        [sym_math_op] = SHIFT(308),
        [sym_bool_op] = SHIFT(308),
        [sym_var_name] = SHIFT(308),
        [sym__line_break] = SHIFT(309),
        [sym_string] = SHIFT(308),
        [sym__identifier] = SHIFT(310),
        [sym_number] = SHIFT(308),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(309),
        [aux_sym_STR_BANG] = SHIFT(311),
    },
    [209] = {
        [sym_expression] = SHIFT(287),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [210] = {
        [sym_var_name] = SHIFT(274),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(275),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [211] = {
        [sym_expression] = SHIFT(215),
        [sym_call_expression] = SHIFT(216),
        [sym_selector_expression] = SHIFT(216),
        [sym_math_op] = SHIFT(216),
        [sym_bool_op] = SHIFT(216),
        [sym_var_name] = SHIFT(216),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(216),
        [sym__identifier] = SHIFT(217),
        [sym_number] = SHIFT(216),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(218),
    },
    [212] = {
        [sym_expression] = SHIFT(213),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [213] = {
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
    [214] = {
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
    [215] = {
        [sym_block_statement] = SHIFT(220),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(221),
        [aux_sym_STR_LBRACE] = SHIFT(222),
        [aux_sym_STR_STAR] = SHIFT(223),
        [aux_sym_STR_DOT] = SHIFT(224),
        [aux_sym_STR_SLASH] = SHIFT(223),
        [aux_sym_STR_PLUS] = SHIFT(225),
        [aux_sym_STR_DASH] = SHIFT(225),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(226),
        [aux_sym_STR_AMP_AMP] = SHIFT(227),
        [aux_sym_STR_EQ_EQ] = SHIFT(228),
        [aux_sym_STR_LT_EQ] = SHIFT(228),
        [aux_sym_STR_LT] = SHIFT(228),
        [aux_sym_STR_GT_EQ] = SHIFT(228),
        [aux_sym_STR_GT] = SHIFT(228),
    },
    [216] = {
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
    [217] = {
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
    [218] = {
        [sym_expression] = SHIFT(219),
        [sym_call_expression] = SHIFT(216),
        [sym_selector_expression] = SHIFT(216),
        [sym_math_op] = SHIFT(216),
        [sym_bool_op] = SHIFT(216),
        [sym_var_name] = SHIFT(216),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(216),
        [sym__identifier] = SHIFT(217),
        [sym_number] = SHIFT(216),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(218),
    },
    [219] = {
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
    [220] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_var] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_return] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_for] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_if] = REDUCE(sym_if_statement, 3),
        [aux_sym_STR_else] = SHIFT(268),
        [aux_sym_STR_BANG] = REDUCE(sym_if_statement, 3),
    },
    [221] = {
        [sym_expression] = SHIFT(238),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(241),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [222] = {
        [sym_var_declaration] = SHIFT(198),
        [sym_statement] = SHIFT(199),
        [sym_return_statement] = SHIFT(200),
        [sym_declaration_statement] = SHIFT(200),
        [sym_range_statement] = SHIFT(200),
        [sym_if_statement] = SHIFT(200),
        [sym_expression_statement] = SHIFT(200),
        [sym_expression] = SHIFT(201),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(203),
        [ts_builtin_sym_error] = SHIFT(235),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(205),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat1] = SHIFT(235),
        [aux_sym_STR_var] = SHIFT(206),
        [aux_sym_STR_RBRACE] = SHIFT(236),
        [aux_sym_STR_return] = SHIFT(208),
        [aux_sym_STR_COLON_EQ] = SHIFT(209),
        [aux_sym_STR_for] = SHIFT(210),
        [aux_sym_STR_if] = SHIFT(211),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [223] = {
        [sym_expression] = SHIFT(234),
        [sym_call_expression] = SHIFT(216),
        [sym_selector_expression] = SHIFT(216),
        [sym_math_op] = SHIFT(216),
        [sym_bool_op] = SHIFT(216),
        [sym_var_name] = SHIFT(216),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(216),
        [sym__identifier] = SHIFT(217),
        [sym_number] = SHIFT(216),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(218),
    },
    [224] = {
        [sym_var_name] = SHIFT(233),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(217),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [225] = {
        [sym_expression] = SHIFT(232),
        [sym_call_expression] = SHIFT(216),
        [sym_selector_expression] = SHIFT(216),
        [sym_math_op] = SHIFT(216),
        [sym_bool_op] = SHIFT(216),
        [sym_var_name] = SHIFT(216),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(216),
        [sym__identifier] = SHIFT(217),
        [sym_number] = SHIFT(216),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(218),
    },
    [226] = {
        [sym_expression] = SHIFT(231),
        [sym_call_expression] = SHIFT(216),
        [sym_selector_expression] = SHIFT(216),
        [sym_math_op] = SHIFT(216),
        [sym_bool_op] = SHIFT(216),
        [sym_var_name] = SHIFT(216),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(216),
        [sym__identifier] = SHIFT(217),
        [sym_number] = SHIFT(216),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(218),
    },
    [227] = {
        [sym_expression] = SHIFT(230),
        [sym_call_expression] = SHIFT(216),
        [sym_selector_expression] = SHIFT(216),
        [sym_math_op] = SHIFT(216),
        [sym_bool_op] = SHIFT(216),
        [sym_var_name] = SHIFT(216),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(216),
        [sym__identifier] = SHIFT(217),
        [sym_number] = SHIFT(216),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(218),
    },
    [228] = {
        [sym_expression] = SHIFT(229),
        [sym_call_expression] = SHIFT(216),
        [sym_selector_expression] = SHIFT(216),
        [sym_math_op] = SHIFT(216),
        [sym_bool_op] = SHIFT(216),
        [sym_var_name] = SHIFT(216),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(216),
        [sym__identifier] = SHIFT(217),
        [sym_number] = SHIFT(216),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(218),
    },
    [229] = {
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
    [230] = {
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
        [aux_sym_STR_EQ_EQ] = SHIFT(228),
        [aux_sym_STR_LT_EQ] = SHIFT(228),
        [aux_sym_STR_LT] = SHIFT(228),
        [aux_sym_STR_GT_EQ] = SHIFT(228),
        [aux_sym_STR_GT] = SHIFT(228),
    },
    [231] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(223),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(223),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(227),
        [aux_sym_STR_EQ_EQ] = SHIFT(228),
        [aux_sym_STR_LT_EQ] = SHIFT(228),
        [aux_sym_STR_LT] = SHIFT(228),
        [aux_sym_STR_GT_EQ] = SHIFT(228),
        [aux_sym_STR_GT] = SHIFT(228),
    },
    [232] = {
        [sym_block_statement] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LBRACE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(223),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(223),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(227),
        [aux_sym_STR_EQ_EQ] = SHIFT(228),
        [aux_sym_STR_LT_EQ] = SHIFT(228),
        [aux_sym_STR_LT] = SHIFT(228),
        [aux_sym_STR_GT_EQ] = SHIFT(228),
        [aux_sym_STR_GT] = SHIFT(228),
    },
    [233] = {
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
    [234] = {
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
        [aux_sym_STR_EQ_EQ] = SHIFT(228),
        [aux_sym_STR_LT_EQ] = SHIFT(228),
        [aux_sym_STR_LT] = SHIFT(228),
        [aux_sym_STR_GT_EQ] = SHIFT(228),
        [aux_sym_STR_GT] = SHIFT(228),
    },
    [235] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(237),
    },
    [236] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_var] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_return] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_for] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_if] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_else] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_BANG] = REDUCE(sym_block_statement, 2),
    },
    [237] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_var] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_return] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_for] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_if] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_else] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_BANG] = REDUCE(sym_block_statement, 3),
    },
    [238] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = SHIFT(244),
        [aux_sym_STR_LPAREN] = SHIFT(245),
        [aux_sym_STR_RPAREN] = SHIFT(246),
        [aux_sym_STR_STAR] = SHIFT(247),
        [aux_sym_STR_COMMA] = SHIFT(248),
        [aux_sym_STR_DOT] = SHIFT(249),
        [aux_sym_STR_SLASH] = SHIFT(247),
        [aux_sym_STR_PLUS] = SHIFT(250),
        [aux_sym_STR_DASH] = SHIFT(250),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(251),
        [aux_sym_STR_AMP_AMP] = SHIFT(252),
        [aux_sym_STR_EQ_EQ] = SHIFT(253),
        [aux_sym_STR_LT_EQ] = SHIFT(253),
        [aux_sym_STR_LT] = SHIFT(253),
        [aux_sym_STR_GT_EQ] = SHIFT(253),
        [aux_sym_STR_GT] = SHIFT(253),
    },
    [239] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_expression, 1),
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
    [240] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_var_name, 1),
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
    [241] = {
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
    [242] = {
        [sym_expression] = SHIFT(243),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [243] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_bool_op, 2),
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
    [244] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(267),
    },
    [245] = {
        [sym_expression] = SHIFT(262),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(263),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [246] = {
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
    [247] = {
        [sym_expression] = SHIFT(261),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [248] = {
        [sym_expression] = SHIFT(259),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [249] = {
        [sym_var_name] = SHIFT(258),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(240),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [250] = {
        [sym_expression] = SHIFT(257),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [251] = {
        [sym_expression] = SHIFT(256),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [252] = {
        [sym_expression] = SHIFT(255),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [253] = {
        [sym_expression] = SHIFT(254),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [254] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_bool_op, 3),
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
    [255] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_bool_op, 3),
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
        [aux_sym_STR_EQ_EQ] = SHIFT(253),
        [aux_sym_STR_LT_EQ] = SHIFT(253),
        [aux_sym_STR_LT] = SHIFT(253),
        [aux_sym_STR_GT_EQ] = SHIFT(253),
        [aux_sym_STR_GT] = SHIFT(253),
    },
    [256] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(247),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(247),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(252),
        [aux_sym_STR_EQ_EQ] = SHIFT(253),
        [aux_sym_STR_LT_EQ] = SHIFT(253),
        [aux_sym_STR_LT] = SHIFT(253),
        [aux_sym_STR_GT_EQ] = SHIFT(253),
        [aux_sym_STR_GT] = SHIFT(253),
    },
    [257] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_RPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(247),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(247),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(252),
        [aux_sym_STR_EQ_EQ] = SHIFT(253),
        [aux_sym_STR_LT_EQ] = SHIFT(253),
        [aux_sym_STR_LT] = SHIFT(253),
        [aux_sym_STR_GT_EQ] = SHIFT(253),
        [aux_sym_STR_GT] = SHIFT(253),
    },
    [258] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_selector_expression, 3),
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
    [259] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = SHIFT(260),
        [aux_sym_STR_LPAREN] = SHIFT(245),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_return_statement_repeat1, 2),
        [aux_sym_STR_STAR] = SHIFT(247),
        [aux_sym_STR_COMMA] = SHIFT(248),
        [aux_sym_STR_DOT] = SHIFT(249),
        [aux_sym_STR_SLASH] = SHIFT(247),
        [aux_sym_STR_PLUS] = SHIFT(250),
        [aux_sym_STR_DASH] = SHIFT(250),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(251),
        [aux_sym_STR_AMP_AMP] = SHIFT(252),
        [aux_sym_STR_EQ_EQ] = SHIFT(253),
        [aux_sym_STR_LT_EQ] = SHIFT(253),
        [aux_sym_STR_LT] = SHIFT(253),
        [aux_sym_STR_GT_EQ] = SHIFT(253),
        [aux_sym_STR_GT] = SHIFT(253),
    },
    [260] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_return_statement_repeat1, 3),
    },
    [261] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_math_op, 3),
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
        [aux_sym_STR_EQ_EQ] = SHIFT(253),
        [aux_sym_STR_LT_EQ] = SHIFT(253),
        [aux_sym_STR_LT] = SHIFT(253),
        [aux_sym_STR_GT_EQ] = SHIFT(253),
        [aux_sym_STR_GT] = SHIFT(253),
    },
    [262] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = SHIFT(264),
        [aux_sym_STR_LPAREN] = SHIFT(245),
        [aux_sym_STR_RPAREN] = SHIFT(265),
        [aux_sym_STR_STAR] = SHIFT(247),
        [aux_sym_STR_COMMA] = SHIFT(248),
        [aux_sym_STR_DOT] = SHIFT(249),
        [aux_sym_STR_SLASH] = SHIFT(247),
        [aux_sym_STR_PLUS] = SHIFT(250),
        [aux_sym_STR_DASH] = SHIFT(250),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(251),
        [aux_sym_STR_AMP_AMP] = SHIFT(252),
        [aux_sym_STR_EQ_EQ] = SHIFT(253),
        [aux_sym_STR_LT_EQ] = SHIFT(253),
        [aux_sym_STR_LT] = SHIFT(253),
        [aux_sym_STR_GT_EQ] = SHIFT(253),
        [aux_sym_STR_GT] = SHIFT(253),
    },
    [263] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_call_expression, 3),
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
    [264] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(266),
    },
    [265] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_call_expression, 4),
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
    [266] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_call_expression, 5),
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
    [267] = {
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
    [268] = {
        [sym_block_statement] = SHIFT(269),
        [sym_if_statement] = SHIFT(269),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(270),
        [aux_sym_STR_if] = SHIFT(211),
    },
    [269] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_var] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_return] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_for] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_if] = REDUCE(sym_if_statement, 5),
        [aux_sym_STR_BANG] = REDUCE(sym_if_statement, 5),
    },
    [270] = {
        [sym_var_declaration] = SHIFT(198),
        [sym_statement] = SHIFT(199),
        [sym_return_statement] = SHIFT(200),
        [sym_declaration_statement] = SHIFT(200),
        [sym_range_statement] = SHIFT(200),
        [sym_if_statement] = SHIFT(200),
        [sym_expression_statement] = SHIFT(200),
        [sym_expression] = SHIFT(201),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(203),
        [ts_builtin_sym_error] = SHIFT(271),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(205),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_block_statement_repeat1] = SHIFT(271),
        [aux_sym_STR_var] = SHIFT(206),
        [aux_sym_STR_RBRACE] = SHIFT(272),
        [aux_sym_STR_return] = SHIFT(208),
        [aux_sym_STR_COLON_EQ] = SHIFT(209),
        [aux_sym_STR_for] = SHIFT(210),
        [aux_sym_STR_if] = SHIFT(211),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [271] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(273),
    },
    [272] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_var] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_return] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_for] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_if] = REDUCE(sym_block_statement, 2),
        [aux_sym_STR_BANG] = REDUCE(sym_block_statement, 2),
    },
    [273] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_var] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_return] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_for] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_if] = REDUCE(sym_block_statement, 3),
        [aux_sym_STR_BANG] = REDUCE(sym_block_statement, 3),
    },
    [274] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COMMA] = SHIFT(276),
        [aux_sym_STR_COLON_EQ] = SHIFT(277),
    },
    [275] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
    },
    [276] = {
        [sym_var_name] = SHIFT(281),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(282),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [277] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_range] = SHIFT(278),
    },
    [278] = {
        [sym_expression] = SHIFT(279),
        [sym_call_expression] = SHIFT(216),
        [sym_selector_expression] = SHIFT(216),
        [sym_math_op] = SHIFT(216),
        [sym_bool_op] = SHIFT(216),
        [sym_var_name] = SHIFT(216),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(216),
        [sym__identifier] = SHIFT(217),
        [sym_number] = SHIFT(216),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(218),
    },
    [279] = {
        [sym_block_statement] = SHIFT(280),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(221),
        [aux_sym_STR_LBRACE] = SHIFT(270),
        [aux_sym_STR_STAR] = SHIFT(223),
        [aux_sym_STR_DOT] = SHIFT(224),
        [aux_sym_STR_SLASH] = SHIFT(223),
        [aux_sym_STR_PLUS] = SHIFT(225),
        [aux_sym_STR_DASH] = SHIFT(225),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(226),
        [aux_sym_STR_AMP_AMP] = SHIFT(227),
        [aux_sym_STR_EQ_EQ] = SHIFT(228),
        [aux_sym_STR_LT_EQ] = SHIFT(228),
        [aux_sym_STR_LT] = SHIFT(228),
        [aux_sym_STR_GT_EQ] = SHIFT(228),
        [aux_sym_STR_GT] = SHIFT(228),
    },
    [280] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_var] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_RBRACE] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_return] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_for] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_if] = REDUCE(sym_range_statement, 6),
        [aux_sym_STR_BANG] = REDUCE(sym_range_statement, 6),
    },
    [281] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = SHIFT(283),
    },
    [282] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
    },
    [283] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_range] = SHIFT(284),
    },
    [284] = {
        [sym_expression] = SHIFT(285),
        [sym_call_expression] = SHIFT(216),
        [sym_selector_expression] = SHIFT(216),
        [sym_math_op] = SHIFT(216),
        [sym_bool_op] = SHIFT(216),
        [sym_var_name] = SHIFT(216),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(216),
        [sym__identifier] = SHIFT(217),
        [sym_number] = SHIFT(216),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(218),
    },
    [285] = {
        [sym_block_statement] = SHIFT(286),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(221),
        [aux_sym_STR_LBRACE] = SHIFT(270),
        [aux_sym_STR_STAR] = SHIFT(223),
        [aux_sym_STR_DOT] = SHIFT(224),
        [aux_sym_STR_SLASH] = SHIFT(223),
        [aux_sym_STR_PLUS] = SHIFT(225),
        [aux_sym_STR_DASH] = SHIFT(225),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(226),
        [aux_sym_STR_AMP_AMP] = SHIFT(227),
        [aux_sym_STR_EQ_EQ] = SHIFT(228),
        [aux_sym_STR_LT_EQ] = SHIFT(228),
        [aux_sym_STR_LT] = SHIFT(228),
        [aux_sym_STR_GT_EQ] = SHIFT(228),
        [aux_sym_STR_GT] = SHIFT(228),
    },
    [286] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_var] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_RBRACE] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_return] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_for] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_if] = REDUCE(sym_range_statement, 8),
        [aux_sym_STR_BANG] = REDUCE(sym_range_statement, 8),
    },
    [287] = {
        [sym__line_break] = SHIFT(288),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(289),
        [aux_sym_STR_SEMI] = SHIFT(288),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = SHIFT(291),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = SHIFT(292),
        [aux_sym_STR_DASH] = SHIFT(292),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(293),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [288] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_declaration_statement, 3),
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
    [289] = {
        [sym_expression] = SHIFT(302),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(303),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [290] = {
        [sym_expression] = SHIFT(301),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [291] = {
        [sym_var_name] = SHIFT(300),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(214),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [292] = {
        [sym_expression] = SHIFT(299),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [293] = {
        [sym_expression] = SHIFT(298),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [294] = {
        [sym_expression] = SHIFT(297),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [295] = {
        [sym_expression] = SHIFT(296),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [296] = {
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
    [297] = {
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
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [298] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [299] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [300] = {
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
    [301] = {
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
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [302] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = SHIFT(304),
        [aux_sym_STR_LPAREN] = SHIFT(245),
        [aux_sym_STR_RPAREN] = SHIFT(305),
        [aux_sym_STR_STAR] = SHIFT(247),
        [aux_sym_STR_COMMA] = SHIFT(248),
        [aux_sym_STR_DOT] = SHIFT(249),
        [aux_sym_STR_SLASH] = SHIFT(247),
        [aux_sym_STR_PLUS] = SHIFT(250),
        [aux_sym_STR_DASH] = SHIFT(250),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(251),
        [aux_sym_STR_AMP_AMP] = SHIFT(252),
        [aux_sym_STR_EQ_EQ] = SHIFT(253),
        [aux_sym_STR_LT_EQ] = SHIFT(253),
        [aux_sym_STR_LT] = SHIFT(253),
        [aux_sym_STR_GT_EQ] = SHIFT(253),
        [aux_sym_STR_GT] = SHIFT(253),
    },
    [303] = {
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
    [304] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(306),
    },
    [305] = {
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
    [306] = {
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
    [307] = {
        [sym__line_break] = SHIFT(313),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = SHIFT(314),
        [aux_sym_STR_LPAREN] = SHIFT(315),
        [aux_sym_STR_SEMI] = SHIFT(313),
        [aux_sym_STR_STAR] = SHIFT(316),
        [aux_sym_STR_COMMA] = SHIFT(317),
        [aux_sym_STR_DOT] = SHIFT(318),
        [aux_sym_STR_SLASH] = SHIFT(316),
        [aux_sym_STR_PLUS] = SHIFT(319),
        [aux_sym_STR_DASH] = SHIFT(319),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(320),
        [aux_sym_STR_AMP_AMP] = SHIFT(321),
        [aux_sym_STR_EQ_EQ] = SHIFT(322),
        [aux_sym_STR_LT_EQ] = SHIFT(322),
        [aux_sym_STR_LT] = SHIFT(322),
        [aux_sym_STR_GT_EQ] = SHIFT(322),
        [aux_sym_STR_GT] = SHIFT(322),
    },
    [308] = {
        [sym__line_break] = REDUCE(sym_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_expression, 1),
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
    [309] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_return] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_for] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_if] = REDUCE(sym_return_statement, 2),
        [aux_sym_STR_BANG] = REDUCE(sym_return_statement, 2),
    },
    [310] = {
        [sym__line_break] = REDUCE(sym_var_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_var_name, 1),
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
    [311] = {
        [sym_expression] = SHIFT(312),
        [sym_call_expression] = SHIFT(308),
        [sym_selector_expression] = SHIFT(308),
        [sym_math_op] = SHIFT(308),
        [sym_bool_op] = SHIFT(308),
        [sym_var_name] = SHIFT(308),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(308),
        [sym__identifier] = SHIFT(310),
        [sym_number] = SHIFT(308),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(311),
    },
    [312] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_bool_op, 2),
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
    [313] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_return_statement, 3),
        [aux_sym_return_statement_repeat1] = REDUCE_EXTRA(sym__line_break),
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
    [314] = {
        [sym__line_break] = SHIFT(336),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(336),
    },
    [315] = {
        [sym_expression] = SHIFT(331),
        [sym_call_expression] = SHIFT(239),
        [sym_selector_expression] = SHIFT(239),
        [sym_math_op] = SHIFT(239),
        [sym_bool_op] = SHIFT(239),
        [sym_var_name] = SHIFT(239),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(239),
        [sym__identifier] = SHIFT(240),
        [sym_number] = SHIFT(239),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(332),
        [aux_sym_STR_BANG] = SHIFT(242),
    },
    [316] = {
        [sym_expression] = SHIFT(330),
        [sym_call_expression] = SHIFT(308),
        [sym_selector_expression] = SHIFT(308),
        [sym_math_op] = SHIFT(308),
        [sym_bool_op] = SHIFT(308),
        [sym_var_name] = SHIFT(308),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(308),
        [sym__identifier] = SHIFT(310),
        [sym_number] = SHIFT(308),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(311),
    },
    [317] = {
        [sym_expression] = SHIFT(328),
        [sym_call_expression] = SHIFT(308),
        [sym_selector_expression] = SHIFT(308),
        [sym_math_op] = SHIFT(308),
        [sym_bool_op] = SHIFT(308),
        [sym_var_name] = SHIFT(308),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(308),
        [sym__identifier] = SHIFT(310),
        [sym_number] = SHIFT(308),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(311),
    },
    [318] = {
        [sym_var_name] = SHIFT(327),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(310),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [319] = {
        [sym_expression] = SHIFT(326),
        [sym_call_expression] = SHIFT(308),
        [sym_selector_expression] = SHIFT(308),
        [sym_math_op] = SHIFT(308),
        [sym_bool_op] = SHIFT(308),
        [sym_var_name] = SHIFT(308),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(308),
        [sym__identifier] = SHIFT(310),
        [sym_number] = SHIFT(308),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(311),
    },
    [320] = {
        [sym_expression] = SHIFT(325),
        [sym_call_expression] = SHIFT(308),
        [sym_selector_expression] = SHIFT(308),
        [sym_math_op] = SHIFT(308),
        [sym_bool_op] = SHIFT(308),
        [sym_var_name] = SHIFT(308),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(308),
        [sym__identifier] = SHIFT(310),
        [sym_number] = SHIFT(308),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(311),
    },
    [321] = {
        [sym_expression] = SHIFT(324),
        [sym_call_expression] = SHIFT(308),
        [sym_selector_expression] = SHIFT(308),
        [sym_math_op] = SHIFT(308),
        [sym_bool_op] = SHIFT(308),
        [sym_var_name] = SHIFT(308),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(308),
        [sym__identifier] = SHIFT(310),
        [sym_number] = SHIFT(308),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(311),
    },
    [322] = {
        [sym_expression] = SHIFT(323),
        [sym_call_expression] = SHIFT(308),
        [sym_selector_expression] = SHIFT(308),
        [sym_math_op] = SHIFT(308),
        [sym_bool_op] = SHIFT(308),
        [sym_var_name] = SHIFT(308),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(308),
        [sym__identifier] = SHIFT(310),
        [sym_number] = SHIFT(308),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(311),
    },
    [323] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_bool_op, 3),
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
    [324] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_bool_op, 3),
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
        [aux_sym_STR_EQ_EQ] = SHIFT(322),
        [aux_sym_STR_LT_EQ] = SHIFT(322),
        [aux_sym_STR_LT] = SHIFT(322),
        [aux_sym_STR_GT_EQ] = SHIFT(322),
        [aux_sym_STR_GT] = SHIFT(322),
    },
    [325] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_bool_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_STAR] = SHIFT(316),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(316),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_bool_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(321),
        [aux_sym_STR_EQ_EQ] = SHIFT(322),
        [aux_sym_STR_LT_EQ] = SHIFT(322),
        [aux_sym_STR_LT] = SHIFT(322),
        [aux_sym_STR_GT_EQ] = SHIFT(322),
        [aux_sym_STR_GT] = SHIFT(322),
    },
    [326] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_LPAREN] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SEMI] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_STAR] = SHIFT(316),
        [aux_sym_STR_COMMA] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DOT] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_SLASH] = SHIFT(316),
        [aux_sym_STR_PLUS] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_DASH] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_PIPE_PIPE] = REDUCE_FRAGILE(sym_math_op, 3),
        [aux_sym_STR_AMP_AMP] = SHIFT(321),
        [aux_sym_STR_EQ_EQ] = SHIFT(322),
        [aux_sym_STR_LT_EQ] = SHIFT(322),
        [aux_sym_STR_LT] = SHIFT(322),
        [aux_sym_STR_GT_EQ] = SHIFT(322),
        [aux_sym_STR_GT] = SHIFT(322),
    },
    [327] = {
        [sym__line_break] = REDUCE(sym_selector_expression, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_selector_expression, 3),
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
    [328] = {
        [sym__line_break] = REDUCE(aux_sym_return_statement_repeat1, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = SHIFT(329),
        [aux_sym_STR_LPAREN] = SHIFT(315),
        [aux_sym_STR_SEMI] = REDUCE(aux_sym_return_statement_repeat1, 2),
        [aux_sym_STR_STAR] = SHIFT(316),
        [aux_sym_STR_COMMA] = SHIFT(317),
        [aux_sym_STR_DOT] = SHIFT(318),
        [aux_sym_STR_SLASH] = SHIFT(316),
        [aux_sym_STR_PLUS] = SHIFT(319),
        [aux_sym_STR_DASH] = SHIFT(319),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(320),
        [aux_sym_STR_AMP_AMP] = SHIFT(321),
        [aux_sym_STR_EQ_EQ] = SHIFT(322),
        [aux_sym_STR_LT_EQ] = SHIFT(322),
        [aux_sym_STR_LT] = SHIFT(322),
        [aux_sym_STR_GT_EQ] = SHIFT(322),
        [aux_sym_STR_GT] = SHIFT(322),
    },
    [329] = {
        [sym__line_break] = REDUCE(aux_sym_return_statement_repeat1, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(aux_sym_return_statement_repeat1, 3),
    },
    [330] = {
        [sym__line_break] = REDUCE_FRAGILE(sym_math_op, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE_FRAGILE(sym_math_op, 3),
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
        [aux_sym_STR_EQ_EQ] = SHIFT(322),
        [aux_sym_STR_LT_EQ] = SHIFT(322),
        [aux_sym_STR_LT] = SHIFT(322),
        [aux_sym_STR_GT_EQ] = SHIFT(322),
        [aux_sym_STR_GT] = SHIFT(322),
    },
    [331] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = SHIFT(333),
        [aux_sym_STR_LPAREN] = SHIFT(245),
        [aux_sym_STR_RPAREN] = SHIFT(334),
        [aux_sym_STR_STAR] = SHIFT(247),
        [aux_sym_STR_COMMA] = SHIFT(248),
        [aux_sym_STR_DOT] = SHIFT(249),
        [aux_sym_STR_SLASH] = SHIFT(247),
        [aux_sym_STR_PLUS] = SHIFT(250),
        [aux_sym_STR_DASH] = SHIFT(250),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(251),
        [aux_sym_STR_AMP_AMP] = SHIFT(252),
        [aux_sym_STR_EQ_EQ] = SHIFT(253),
        [aux_sym_STR_LT_EQ] = SHIFT(253),
        [aux_sym_STR_LT] = SHIFT(253),
        [aux_sym_STR_GT_EQ] = SHIFT(253),
        [aux_sym_STR_GT] = SHIFT(253),
    },
    [332] = {
        [sym__line_break] = REDUCE(sym_call_expression, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_call_expression, 3),
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
    [333] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(335),
    },
    [334] = {
        [sym__line_break] = REDUCE(sym_call_expression, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_call_expression, 4),
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
    [335] = {
        [sym__line_break] = REDUCE(sym_call_expression, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_return_statement_repeat1] = REDUCE(sym_call_expression, 5),
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
    [336] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_return] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_for] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_if] = REDUCE(sym_return_statement, 4),
        [aux_sym_STR_BANG] = REDUCE(sym_return_statement, 4),
    },
    [337] = {
        [sym_type_expression] = SHIFT(339),
        [sym_pointer_type] = SHIFT(340),
        [sym_map_type] = SHIFT(340),
        [sym_slice_type] = SHIFT(340),
        [sym_struct_type] = SHIFT(340),
        [sym_interface_type] = SHIFT(340),
        [sym_type_name] = SHIFT(340),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(341),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_EQ] = SHIFT(342),
        [aux_sym_STR_STAR] = SHIFT(343),
        [aux_sym_STR_map] = SHIFT(344),
        [aux_sym_STR_LBRACK] = SHIFT(345),
        [aux_sym_STR_struct] = SHIFT(346),
        [aux_sym_STR_interface] = SHIFT(347),
    },
    [338] = {
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
    [339] = {
        [sym__line_break] = SHIFT(365),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(365),
        [aux_sym_STR_EQ] = SHIFT(366),
    },
    [340] = {
        [sym__line_break] = REDUCE(sym_type_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_expression, 1),
        [aux_sym_STR_EQ] = REDUCE(sym_type_expression, 1),
    },
    [341] = {
        [sym__line_break] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_name, 1),
        [aux_sym_STR_EQ] = REDUCE(sym_type_name, 1),
    },
    [342] = {
        [sym_expression] = SHIFT(363),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [343] = {
        [sym_type_expression] = SHIFT(362),
        [sym_pointer_type] = SHIFT(340),
        [sym_map_type] = SHIFT(340),
        [sym_slice_type] = SHIFT(340),
        [sym_struct_type] = SHIFT(340),
        [sym_interface_type] = SHIFT(340),
        [sym_type_name] = SHIFT(340),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(341),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(343),
        [aux_sym_STR_map] = SHIFT(344),
        [aux_sym_STR_LBRACK] = SHIFT(345),
        [aux_sym_STR_struct] = SHIFT(346),
        [aux_sym_STR_interface] = SHIFT(347),
    },
    [344] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(358),
    },
    [345] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(356),
    },
    [346] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(352),
    },
    [347] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(348),
    },
    [348] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = SHIFT(349),
        [aux_sym_STR_RBRACE] = SHIFT(350),
    },
    [349] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(351),
    },
    [350] = {
        [sym__line_break] = REDUCE(sym_interface_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 3),
        [aux_sym_STR_EQ] = REDUCE(sym_interface_type, 3),
    },
    [351] = {
        [sym__line_break] = REDUCE(sym_interface_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 4),
        [aux_sym_STR_EQ] = REDUCE(sym_interface_type, 4),
    },
    [352] = {
        [sym_var_name] = SHIFT(112),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(113),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = SHIFT(353),
        [aux_sym_STR_RBRACE] = SHIFT(354),
    },
    [353] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(355),
    },
    [354] = {
        [sym__line_break] = REDUCE(sym_struct_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 3),
        [aux_sym_STR_EQ] = REDUCE(sym_struct_type, 3),
    },
    [355] = {
        [sym__line_break] = REDUCE(sym_struct_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 4),
        [aux_sym_STR_EQ] = REDUCE(sym_struct_type, 4),
    },
    [356] = {
        [sym_type_expression] = SHIFT(357),
        [sym_pointer_type] = SHIFT(340),
        [sym_map_type] = SHIFT(340),
        [sym_slice_type] = SHIFT(340),
        [sym_struct_type] = SHIFT(340),
        [sym_interface_type] = SHIFT(340),
        [sym_type_name] = SHIFT(340),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(341),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(343),
        [aux_sym_STR_map] = SHIFT(344),
        [aux_sym_STR_LBRACK] = SHIFT(345),
        [aux_sym_STR_struct] = SHIFT(346),
        [aux_sym_STR_interface] = SHIFT(347),
    },
    [357] = {
        [sym__line_break] = REDUCE(sym_slice_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_slice_type, 3),
        [aux_sym_STR_EQ] = REDUCE(sym_slice_type, 3),
    },
    [358] = {
        [sym_type_expression] = SHIFT(359),
        [sym_pointer_type] = SHIFT(137),
        [sym_map_type] = SHIFT(137),
        [sym_slice_type] = SHIFT(137),
        [sym_struct_type] = SHIFT(137),
        [sym_interface_type] = SHIFT(137),
        [sym_type_name] = SHIFT(137),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(138),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(139),
        [aux_sym_STR_map] = SHIFT(140),
        [aux_sym_STR_LBRACK] = SHIFT(141),
        [aux_sym_STR_struct] = SHIFT(142),
        [aux_sym_STR_interface] = SHIFT(143),
    },
    [359] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(360),
    },
    [360] = {
        [sym_type_expression] = SHIFT(361),
        [sym_pointer_type] = SHIFT(340),
        [sym_map_type] = SHIFT(340),
        [sym_slice_type] = SHIFT(340),
        [sym_struct_type] = SHIFT(340),
        [sym_interface_type] = SHIFT(340),
        [sym_type_name] = SHIFT(340),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(341),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(343),
        [aux_sym_STR_map] = SHIFT(344),
        [aux_sym_STR_LBRACK] = SHIFT(345),
        [aux_sym_STR_struct] = SHIFT(346),
        [aux_sym_STR_interface] = SHIFT(347),
    },
    [361] = {
        [sym__line_break] = REDUCE(sym_map_type, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_map_type, 5),
        [aux_sym_STR_EQ] = REDUCE(sym_map_type, 5),
    },
    [362] = {
        [sym__line_break] = REDUCE(sym_pointer_type, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_pointer_type, 2),
        [aux_sym_STR_EQ] = REDUCE(sym_pointer_type, 2),
    },
    [363] = {
        [sym__line_break] = SHIFT(364),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(289),
        [aux_sym_STR_SEMI] = SHIFT(364),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = SHIFT(291),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = SHIFT(292),
        [aux_sym_STR_DASH] = SHIFT(292),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(293),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [364] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_var_declaration, 5),
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
    [365] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_var_declaration, 4),
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
    [366] = {
        [sym_expression] = SHIFT(367),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [367] = {
        [sym__line_break] = SHIFT(368),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(289),
        [aux_sym_STR_SEMI] = SHIFT(368),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = SHIFT(291),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = SHIFT(292),
        [aux_sym_STR_DASH] = SHIFT(292),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(293),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [368] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_var_declaration, 6),
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
    [369] = {
        [sym__line_break] = REDUCE(sym_block_statement, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_block_statement, 3),
    },
    [370] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = SHIFT(378),
    },
    [371] = {
        [sym_var_name] = SHIFT(375),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(376),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [372] = {
        [sym_expression] = SHIFT(373),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [373] = {
        [sym__line_break] = SHIFT(374),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(289),
        [aux_sym_STR_SEMI] = SHIFT(374),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = SHIFT(291),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = SHIFT(292),
        [aux_sym_STR_DASH] = SHIFT(292),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(293),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [374] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_declaration_statement, 4),
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
    [375] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat1] = SHIFT(377),
        [aux_sym_STR_COMMA] = SHIFT(371),
        [aux_sym_STR_COLON_EQ] = REDUCE(aux_sym_declaration_statement_repeat1, 2),
    },
    [376] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_declaration_statement_repeat1] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_var_name, 1),
        [aux_sym_STR_COLON_EQ] = REDUCE(sym_var_name, 1),
    },
    [377] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_COLON_EQ] = REDUCE(aux_sym_declaration_statement_repeat1, 3),
    },
    [378] = {
        [sym_expression] = SHIFT(379),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [379] = {
        [sym__line_break] = SHIFT(380),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(289),
        [aux_sym_STR_SEMI] = SHIFT(380),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = SHIFT(291),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = SHIFT(292),
        [aux_sym_STR_DASH] = SHIFT(292),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(293),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [380] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_declaration_statement, 5),
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
    [381] = {
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
        [aux_sym_block_statement_repeat1] = REDUCE(sym_expression_statement, 2),
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
    [382] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_block_statement_repeat1, 2),
    },
    [383] = {
        [sym_declaration] = REDUCE(sym_func_declaration, 5),
        [sym_type_declaration] = REDUCE(sym_func_declaration, 5),
        [sym_var_declaration] = REDUCE(sym_func_declaration, 5),
        [sym_func_declaration] = REDUCE(sym_func_declaration, 5),
        [ts_builtin_sym_end] = REDUCE(sym_func_declaration, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat2] = REDUCE(sym_func_declaration, 5),
        [aux_sym_STR_type] = REDUCE(sym_func_declaration, 5),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_func_declaration, 5),
        [aux_sym_STR_func] = REDUCE(sym_func_declaration, 5),
    },
    [384] = {
        [sym_type_expression] = SHIFT(385),
        [sym_pointer_type] = SHIFT(340),
        [sym_map_type] = SHIFT(340),
        [sym_slice_type] = SHIFT(340),
        [sym_struct_type] = SHIFT(340),
        [sym_interface_type] = SHIFT(340),
        [sym_type_name] = SHIFT(340),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(341),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_EQ] = SHIFT(386),
        [aux_sym_STR_STAR] = SHIFT(343),
        [aux_sym_STR_map] = SHIFT(344),
        [aux_sym_STR_LBRACK] = SHIFT(345),
        [aux_sym_STR_struct] = SHIFT(346),
        [aux_sym_STR_interface] = SHIFT(347),
    },
    [385] = {
        [sym__line_break] = SHIFT(389),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(389),
        [aux_sym_STR_EQ] = SHIFT(390),
    },
    [386] = {
        [sym_expression] = SHIFT(387),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [387] = {
        [sym__line_break] = SHIFT(388),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(289),
        [aux_sym_STR_SEMI] = SHIFT(388),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = SHIFT(291),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = SHIFT(292),
        [aux_sym_STR_DASH] = SHIFT(292),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(293),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [388] = {
        [sym_declaration] = REDUCE(sym_var_declaration, 5),
        [sym_type_declaration] = REDUCE(sym_var_declaration, 5),
        [sym_var_declaration] = REDUCE(sym_var_declaration, 5),
        [sym_func_declaration] = REDUCE(sym_var_declaration, 5),
        [ts_builtin_sym_end] = REDUCE(sym_var_declaration, 5),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat2] = REDUCE(sym_var_declaration, 5),
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
    [389] = {
        [sym_declaration] = REDUCE(sym_var_declaration, 4),
        [sym_type_declaration] = REDUCE(sym_var_declaration, 4),
        [sym_var_declaration] = REDUCE(sym_var_declaration, 4),
        [sym_func_declaration] = REDUCE(sym_var_declaration, 4),
        [ts_builtin_sym_end] = REDUCE(sym_var_declaration, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat2] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_type] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_var_declaration, 4),
        [aux_sym_STR_EQ] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_func] = REDUCE(sym_var_declaration, 4),
    },
    [390] = {
        [sym_expression] = SHIFT(391),
        [sym_call_expression] = SHIFT(202),
        [sym_selector_expression] = SHIFT(202),
        [sym_math_op] = SHIFT(202),
        [sym_bool_op] = SHIFT(202),
        [sym_var_name] = SHIFT(202),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(202),
        [sym__identifier] = SHIFT(214),
        [sym_number] = SHIFT(202),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_BANG] = SHIFT(212),
    },
    [391] = {
        [sym__line_break] = SHIFT(392),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LPAREN] = SHIFT(289),
        [aux_sym_STR_SEMI] = SHIFT(392),
        [aux_sym_STR_STAR] = SHIFT(290),
        [aux_sym_STR_DOT] = SHIFT(291),
        [aux_sym_STR_SLASH] = SHIFT(290),
        [aux_sym_STR_PLUS] = SHIFT(292),
        [aux_sym_STR_DASH] = SHIFT(292),
        [aux_sym_STR_PIPE_PIPE] = SHIFT(293),
        [aux_sym_STR_AMP_AMP] = SHIFT(294),
        [aux_sym_STR_EQ_EQ] = SHIFT(295),
        [aux_sym_STR_LT_EQ] = SHIFT(295),
        [aux_sym_STR_LT] = SHIFT(295),
        [aux_sym_STR_GT_EQ] = SHIFT(295),
        [aux_sym_STR_GT] = SHIFT(295),
    },
    [392] = {
        [sym_declaration] = REDUCE(sym_var_declaration, 6),
        [sym_type_declaration] = REDUCE(sym_var_declaration, 6),
        [sym_var_declaration] = REDUCE(sym_var_declaration, 6),
        [sym_func_declaration] = REDUCE(sym_var_declaration, 6),
        [ts_builtin_sym_end] = REDUCE(sym_var_declaration, 6),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat2] = REDUCE(sym_var_declaration, 6),
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
    [393] = {
        [sym_type_expression] = SHIFT(395),
        [sym_pointer_type] = SHIFT(396),
        [sym_map_type] = SHIFT(396),
        [sym_slice_type] = SHIFT(396),
        [sym_struct_type] = SHIFT(396),
        [sym_interface_type] = SHIFT(396),
        [sym_type_name] = SHIFT(396),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(397),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(398),
        [aux_sym_STR_map] = SHIFT(399),
        [aux_sym_STR_LBRACK] = SHIFT(400),
        [aux_sym_STR_struct] = SHIFT(401),
        [aux_sym_STR_interface] = SHIFT(402),
    },
    [394] = {
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
    [395] = {
        [sym__line_break] = SHIFT(418),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = SHIFT(418),
    },
    [396] = {
        [sym__line_break] = REDUCE(sym_type_expression, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_expression, 1),
    },
    [397] = {
        [sym__line_break] = REDUCE(sym_type_name, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_type_name, 1),
    },
    [398] = {
        [sym_type_expression] = SHIFT(417),
        [sym_pointer_type] = SHIFT(396),
        [sym_map_type] = SHIFT(396),
        [sym_slice_type] = SHIFT(396),
        [sym_struct_type] = SHIFT(396),
        [sym_interface_type] = SHIFT(396),
        [sym_type_name] = SHIFT(396),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(397),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(398),
        [aux_sym_STR_map] = SHIFT(399),
        [aux_sym_STR_LBRACK] = SHIFT(400),
        [aux_sym_STR_struct] = SHIFT(401),
        [aux_sym_STR_interface] = SHIFT(402),
    },
    [399] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACK] = SHIFT(413),
    },
    [400] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(411),
    },
    [401] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(407),
    },
    [402] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_LBRACE] = SHIFT(403),
    },
    [403] = {
        [sym_var_name] = SHIFT(57),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(16),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_interface_type_repeat1] = SHIFT(404),
        [aux_sym_STR_RBRACE] = SHIFT(405),
    },
    [404] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(406),
    },
    [405] = {
        [sym__line_break] = REDUCE(sym_interface_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 3),
    },
    [406] = {
        [sym__line_break] = REDUCE(sym_interface_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_interface_type, 4),
    },
    [407] = {
        [sym_var_name] = SHIFT(112),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(113),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_struct_type_repeat1] = SHIFT(408),
        [aux_sym_STR_RBRACE] = SHIFT(409),
    },
    [408] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACE] = SHIFT(410),
    },
    [409] = {
        [sym__line_break] = REDUCE(sym_struct_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 3),
    },
    [410] = {
        [sym__line_break] = REDUCE(sym_struct_type, 4),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_struct_type, 4),
    },
    [411] = {
        [sym_type_expression] = SHIFT(412),
        [sym_pointer_type] = SHIFT(396),
        [sym_map_type] = SHIFT(396),
        [sym_slice_type] = SHIFT(396),
        [sym_struct_type] = SHIFT(396),
        [sym_interface_type] = SHIFT(396),
        [sym_type_name] = SHIFT(396),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(397),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(398),
        [aux_sym_STR_map] = SHIFT(399),
        [aux_sym_STR_LBRACK] = SHIFT(400),
        [aux_sym_STR_struct] = SHIFT(401),
        [aux_sym_STR_interface] = SHIFT(402),
    },
    [412] = {
        [sym__line_break] = REDUCE(sym_slice_type, 3),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_slice_type, 3),
    },
    [413] = {
        [sym_type_expression] = SHIFT(414),
        [sym_pointer_type] = SHIFT(137),
        [sym_map_type] = SHIFT(137),
        [sym_slice_type] = SHIFT(137),
        [sym_struct_type] = SHIFT(137),
        [sym_interface_type] = SHIFT(137),
        [sym_type_name] = SHIFT(137),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(138),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(139),
        [aux_sym_STR_map] = SHIFT(140),
        [aux_sym_STR_LBRACK] = SHIFT(141),
        [aux_sym_STR_struct] = SHIFT(142),
        [aux_sym_STR_interface] = SHIFT(143),
    },
    [414] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RBRACK] = SHIFT(415),
    },
    [415] = {
        [sym_type_expression] = SHIFT(416),
        [sym_pointer_type] = SHIFT(396),
        [sym_map_type] = SHIFT(396),
        [sym_slice_type] = SHIFT(396),
        [sym_struct_type] = SHIFT(396),
        [sym_interface_type] = SHIFT(396),
        [sym_type_name] = SHIFT(396),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym__identifier] = SHIFT(397),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_STAR] = SHIFT(398),
        [aux_sym_STR_map] = SHIFT(399),
        [aux_sym_STR_LBRACK] = SHIFT(400),
        [aux_sym_STR_struct] = SHIFT(401),
        [aux_sym_STR_interface] = SHIFT(402),
    },
    [416] = {
        [sym__line_break] = REDUCE(sym_map_type, 5),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_map_type, 5),
    },
    [417] = {
        [sym__line_break] = REDUCE(sym_pointer_type, 2),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_SEMI] = REDUCE(sym_pointer_type, 2),
    },
    [418] = {
        [sym_declaration] = REDUCE(sym_type_declaration, 4),
        [sym_type_declaration] = REDUCE(sym_type_declaration, 4),
        [sym_var_declaration] = REDUCE(sym_type_declaration, 4),
        [sym_func_declaration] = REDUCE(sym_type_declaration, 4),
        [ts_builtin_sym_end] = REDUCE(sym_type_declaration, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat2] = REDUCE(sym_type_declaration, 4),
        [aux_sym_STR_type] = REDUCE(sym_type_declaration, 4),
        [aux_sym_STR_SEMI] = REDUCE_EXTRA(sym__line_break),
        [aux_sym_STR_var] = REDUCE(sym_type_declaration, 4),
        [aux_sym_STR_func] = REDUCE(sym_type_declaration, 4),
    },
    [419] = {
        [sym_imports_block] = REDUCE(sym_imports_block, 2),
        [sym_declaration] = REDUCE(sym_imports_block, 2),
        [sym_type_declaration] = REDUCE(sym_imports_block, 2),
        [sym_var_declaration] = REDUCE(sym_imports_block, 2),
        [sym_func_declaration] = REDUCE(sym_imports_block, 2),
        [ts_builtin_sym_end] = REDUCE(sym_imports_block, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_imports_block, 2),
        [aux_sym_program_repeat2] = REDUCE(sym_imports_block, 2),
        [aux_sym_STR_import] = REDUCE(sym_imports_block, 2),
        [aux_sym_STR_type] = REDUCE(sym_imports_block, 2),
        [aux_sym_STR_var] = REDUCE(sym_imports_block, 2),
        [aux_sym_STR_func] = REDUCE(sym_imports_block, 2),
    },
    [420] = {
        [sym_imports_block] = REDUCE(sym_package_import, 1),
        [sym_declaration] = REDUCE(sym_package_import, 1),
        [sym_type_declaration] = REDUCE(sym_package_import, 1),
        [sym_var_declaration] = REDUCE(sym_package_import, 1),
        [sym_func_declaration] = REDUCE(sym_package_import, 1),
        [ts_builtin_sym_end] = REDUCE(sym_package_import, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_package_import, 1),
        [aux_sym_program_repeat2] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_import] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_type] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_var] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_func] = REDUCE(sym_package_import, 1),
    },
    [421] = {
        [sym_package_import] = SHIFT(422),
        [ts_builtin_sym_error] = SHIFT(423),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(424),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_imports_block_repeat1] = SHIFT(423),
        [aux_sym_STR_RPAREN] = SHIFT(425),
    },
    [422] = {
        [sym_package_import] = SHIFT(422),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = SHIFT(424),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_imports_block_repeat1] = SHIFT(427),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_imports_block_repeat1, 1),
    },
    [423] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = SHIFT(426),
    },
    [424] = {
        [sym_package_import] = REDUCE(sym_package_import, 1),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_string] = REDUCE(sym_package_import, 1),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_imports_block_repeat1] = REDUCE(sym_package_import, 1),
        [aux_sym_STR_RPAREN] = REDUCE(sym_package_import, 1),
    },
    [425] = {
        [sym_imports_block] = REDUCE(sym_imports_block, 3),
        [sym_declaration] = REDUCE(sym_imports_block, 3),
        [sym_type_declaration] = REDUCE(sym_imports_block, 3),
        [sym_var_declaration] = REDUCE(sym_imports_block, 3),
        [sym_func_declaration] = REDUCE(sym_imports_block, 3),
        [ts_builtin_sym_end] = REDUCE(sym_imports_block, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_imports_block, 3),
        [aux_sym_program_repeat2] = REDUCE(sym_imports_block, 3),
        [aux_sym_STR_import] = REDUCE(sym_imports_block, 3),
        [aux_sym_STR_type] = REDUCE(sym_imports_block, 3),
        [aux_sym_STR_var] = REDUCE(sym_imports_block, 3),
        [aux_sym_STR_func] = REDUCE(sym_imports_block, 3),
    },
    [426] = {
        [sym_imports_block] = REDUCE(sym_imports_block, 4),
        [sym_declaration] = REDUCE(sym_imports_block, 4),
        [sym_type_declaration] = REDUCE(sym_imports_block, 4),
        [sym_var_declaration] = REDUCE(sym_imports_block, 4),
        [sym_func_declaration] = REDUCE(sym_imports_block, 4),
        [ts_builtin_sym_end] = REDUCE(sym_imports_block, 4),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat1] = REDUCE(sym_imports_block, 4),
        [aux_sym_program_repeat2] = REDUCE(sym_imports_block, 4),
        [aux_sym_STR_import] = REDUCE(sym_imports_block, 4),
        [aux_sym_STR_type] = REDUCE(sym_imports_block, 4),
        [aux_sym_STR_var] = REDUCE(sym_imports_block, 4),
        [aux_sym_STR_func] = REDUCE(sym_imports_block, 4),
    },
    [427] = {
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_STR_RPAREN] = REDUCE(aux_sym_imports_block_repeat1, 2),
    },
    [428] = {
        [ts_builtin_sym_end] = REDUCE(sym_program, 3),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [429] = {
        [ts_builtin_sym_end] = REDUCE(aux_sym_program_repeat2, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
    },
    [430] = {
        [sym_declaration] = REDUCE(aux_sym_program_repeat1, 2),
        [sym_type_declaration] = REDUCE(aux_sym_program_repeat1, 2),
        [sym_var_declaration] = REDUCE(aux_sym_program_repeat1, 2),
        [sym_func_declaration] = REDUCE(aux_sym_program_repeat1, 2),
        [ts_builtin_sym_end] = REDUCE(aux_sym_program_repeat1, 2),
        [sym__line_break] = SHIFT_EXTRA(),
        [sym_comment] = SHIFT_EXTRA(),
        [aux_sym_program_repeat2] = REDUCE(aux_sym_program_repeat1, 2),
        [aux_sym_STR_type] = REDUCE(aux_sym_program_repeat1, 2),
        [aux_sym_STR_var] = REDUCE(aux_sym_program_repeat1, 2),
        [aux_sym_STR_func] = REDUCE(aux_sym_program_repeat1, 2),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_golang);
