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
    aux_sym_short_var_declaration_repeat1,
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
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
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
    [aux_sym_short_var_declaration_repeat1] = "short_var_declaration_repeat1",
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
    [sym__declaration] = 1,
    [sym__type_expression] = 1,
    [sym__statement] = 1,
    [sym__expression] = 1,
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
    [aux_sym_short_var_declaration_repeat1] = 1,
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
    [200] = 104,
    [201] = 104,
    [202] = 119,
    [203] = 79,
    [204] = 119,
    [205] = 32,
    [206] = 81,
    [207] = 120,
    [208] = 121,
    [209] = 32,
    [210] = 121,
    [211] = 121,
    [212] = 104,
    [213] = 104,
    [214] = 122,
    [215] = 122,
    [216] = 122,
    [217] = 121,
    [218] = 122,
    [219] = 123,
    [220] = 128,
    [221] = 83,
    [222] = 121,
    [223] = 32,
    [224] = 121,
    [225] = 121,
    [226] = 121,
    [227] = 121,
    [228] = 122,
    [229] = 122,
    [230] = 122,
    [231] = 122,
    [232] = 122,
    [233] = 122,
    [234] = 79,
    [235] = 123,
    [236] = 123,
    [237] = 129,
    [238] = 129,
    [239] = 129,
    [240] = 122,
    [241] = 121,
    [242] = 129,
    [243] = 72,
    [244] = 128,
    [245] = 122,
    [246] = 121,
    [247] = 121,
    [248] = 32,
    [249] = 121,
    [250] = 121,
    [251] = 121,
    [252] = 121,
    [253] = 129,
    [254] = 129,
    [255] = 129,
    [256] = 129,
    [257] = 129,
    [258] = 129,
    [259] = 72,
    [260] = 129,
    [261] = 129,
    [262] = 129,
    [263] = 72,
    [264] = 129,
    [265] = 129,
    [266] = 122,
    [267] = 130,
    [268] = 83,
    [269] = 83,
    [270] = 79,
    [271] = 83,
    [272] = 83,
    [273] = 133,
    [274] = 133,
    [275] = 32,
    [276] = 134,
    [277] = 121,
    [278] = 122,
    [279] = 83,
    [280] = 140,
    [281] = 140,
    [282] = 134,
    [283] = 121,
    [284] = 122,
    [285] = 83,
    [286] = 104,
    [287] = 141,
    [288] = 128,
    [289] = 121,
    [290] = 32,
    [291] = 121,
    [292] = 121,
    [293] = 121,
    [294] = 121,
    [295] = 104,
    [296] = 104,
    [297] = 104,
    [298] = 104,
    [299] = 104,
    [300] = 104,
    [301] = 129,
    [302] = 104,
    [303] = 72,
    [304] = 104,
    [305] = 104,
    [306] = 142,
    [307] = 142,
    [308] = 143,
    [309] = 142,
    [310] = 121,
    [311] = 142,
    [312] = 144,
    [313] = 81,
    [314] = 128,
    [315] = 121,
    [316] = 121,
    [317] = 32,
    [318] = 121,
    [319] = 121,
    [320] = 121,
    [321] = 121,
    [322] = 142,
    [323] = 142,
    [324] = 142,
    [325] = 142,
    [326] = 142,
    [327] = 142,
    [328] = 81,
    [329] = 142,
    [330] = 129,
    [331] = 142,
    [332] = 72,
    [333] = 142,
    [334] = 142,
    [335] = 143,
    [336] = 145,
    [337] = 145,
    [338] = 147,
    [339] = 147,
    [340] = 147,
    [341] = 121,
    [342] = 73,
    [343] = 74,
    [344] = 75,
    [345] = 43,
    [346] = 43,
    [347] = 77,
    [348] = 79,
    [349] = 147,
    [350] = 147,
    [351] = 77,
    [352] = 79,
    [353] = 147,
    [354] = 147,
    [355] = 73,
    [356] = 147,
    [357] = 73,
    [358] = 75,
    [359] = 73,
    [360] = 147,
    [361] = 147,
    [362] = 104,
    [363] = 141,
    [364] = 148,
    [365] = 121,
    [366] = 104,
    [367] = 141,
    [368] = 81,
    [369] = 140,
    [370] = 32,
    [371] = 121,
    [372] = 104,
    [373] = 141,
    [374] = 133,
    [375] = 133,
    [376] = 140,
    [377] = 121,
    [378] = 104,
    [379] = 141,
    [380] = 141,
    [381] = 79,
    [382] = 149,
    [383] = 145,
    [384] = 147,
    [385] = 121,
    [386] = 104,
    [387] = 150,
    [388] = 151,
    [389] = 121,
    [390] = 104,
    [391] = 150,
    [392] = 73,
    [393] = 73,
    [394] = 81,
    [395] = 81,
    [396] = 81,
    [397] = 73,
    [398] = 74,
    [399] = 75,
    [400] = 43,
    [401] = 43,
    [402] = 77,
    [403] = 79,
    [404] = 81,
    [405] = 81,
    [406] = 77,
    [407] = 79,
    [408] = 81,
    [409] = 81,
    [410] = 73,
    [411] = 81,
    [412] = 73,
    [413] = 75,
    [414] = 73,
    [415] = 81,
    [416] = 81,
    [417] = 149,
    [418] = 14,
    [419] = 14,
    [420] = 152,
    [421] = 152,
    [422] = 72,
    [423] = 152,
    [424] = 14,
    [425] = 14,
    [426] = 72,
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_package] = ACTIONS(SHIFT(3)),
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
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_program_repeat2] = ACTIONS(SHIFT(10)),
        [aux_sym_STR_import] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_type] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_var] = ACTIONS(SHIFT(13)),
        [aux_sym_STR_func] = ACTIONS(SHIFT(14)),
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
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [aux_sym_STR_import] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_package_directive, 2)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_package_directive, 2)),
    },
    [5] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym__declaration] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_package_name, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_package_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_package_name, 1)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_package_name, 1)),
        [aux_sym_STR_import] = ACTIONS(REDUCE(sym_package_name, 1)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_package_name, 1)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_package_name, 1)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_package_name, 1)),
    },
    [6] = {
        [sym_imports_block] = ACTIONS(SHIFT(6)),
        [sym__declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [sym_type_declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [sym_var_declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [sym_func_declaration] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat1] = ACTIONS(SHIFT(429)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [aux_sym_STR_import] = ACTIONS(SHIFT(11)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(aux_sym_program_repeat1, 1)),
    },
    [7] = {
        [sym__declaration] = ACTIONS(SHIFT(7)),
        [sym_type_declaration] = ACTIONS(SHIFT(8)),
        [sym_var_declaration] = ACTIONS(SHIFT(8)),
        [sym_func_declaration] = ACTIONS(SHIFT(8)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat2, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat2] = ACTIONS(SHIFT(428)),
        [aux_sym_STR_type] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_var] = ACTIONS(SHIFT(13)),
        [aux_sym_STR_func] = ACTIONS(SHIFT(14)),
    },
    [8] = {
        [sym__declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym__declaration, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym__declaration, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym__declaration, 1)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym__declaration, 1)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym__declaration, 1)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym__declaration, 1)),
    },
    [9] = {
        [sym__declaration] = ACTIONS(SHIFT(7)),
        [sym_type_declaration] = ACTIONS(SHIFT(8)),
        [sym_var_declaration] = ACTIONS(SHIFT(8)),
        [sym_func_declaration] = ACTIONS(SHIFT(8)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat2] = ACTIONS(SHIFT(427)),
        [aux_sym_STR_type] = ACTIONS(SHIFT(12)),
        [aux_sym_STR_var] = ACTIONS(SHIFT(13)),
        [aux_sym_STR_func] = ACTIONS(SHIFT(14)),
    },
    [10] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [sym_package_import] = ACTIONS(SHIFT(418)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(419)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(420)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(18)),
    },
    [16] = {
        [sym__func_signature] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [17] = {
        [sym_block_statement] = ACTIONS(SHIFT(196)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(197)),
    },
    [18] = {
        [sym_var_name] = ACTIONS(SHIFT(19)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(20)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(21)),
    },
    [19] = {
        [sym__type_expression] = ACTIONS(SHIFT(44)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(47)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
    },
    [20] = {
        [sym__type_expression] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_pointer_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_map_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_slice_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_struct_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_interface_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_map] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_interface] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [21] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [sym_type_name] = ACTIONS(SHIFT(22)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(24)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
    },
    [22] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 3)),
    },
    [23] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [24] = {
        [sym_var_name] = ACTIONS(SHIFT(25)),
        [sym_type_name] = ACTIONS(SHIFT(26)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [sym_type_name] = ACTIONS(SHIFT(35)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(28)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(29)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(30)),
    },
    [27] = {
        [sym_type_name] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [28] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(34)),
    },
    [29] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 5)),
    },
    [30] = {
        [sym_type_name] = ACTIONS(SHIFT(31)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(32)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(33)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat3, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(30)),
    },
    [32] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [33] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat3, 3)),
    },
    [34] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 6)),
    },
    [35] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(37)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(34)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(38)),
    },
    [36] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [37] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(43)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(42)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat2, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(38)),
    },
    [42] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat2, 4)),
    },
    [43] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 7)),
    },
    [44] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(189)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(190)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(80)),
    },
    [45] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__type_expression, 1)),
    },
    [46] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [47] = {
        [sym__type_expression] = ACTIONS(SHIFT(170)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(52)),
    },
    [48] = {
        [sym__type_expression] = ACTIONS(SHIFT(169)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(52)),
    },
    [49] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(165)),
    },
    [50] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(163)),
    },
    [51] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(111)),
    },
    [52] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(56)),
    },
    [53] = {
        [sym_var_name] = ACTIONS(SHIFT(54)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(20)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(55)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [aux_sym_STR_map] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [aux_sym_STR_interface] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
    },
    [55] = {
        [sym__type_expression] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_pointer_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_map_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_slice_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_struct_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_interface_type] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_type_name] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [aux_sym_STR_map] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [aux_sym_STR_interface] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
    },
    [56] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(58)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(59)),
    },
    [57] = {
        [sym__func_signature] = ACTIONS(SHIFT(61)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(62)),
    },
    [58] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(60)),
    },
    [59] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_interface_type, 3)),
    },
    [60] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_interface_type, 4)),
    },
    [61] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(110)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_interface_type_repeat1, 2)),
    },
    [62] = {
        [sym_var_name] = ACTIONS(SHIFT(63)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(20)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(64)),
    },
    [63] = {
        [sym__type_expression] = ACTIONS(SHIFT(75)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(76)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
    },
    [64] = {
        [sym_var_name] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [sym_type_name] = ACTIONS(SHIFT(65)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(66)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 2)),
    },
    [65] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 3)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(69)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(70)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(30)),
    },
    [69] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(71)),
    },
    [70] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 5)),
    },
    [71] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 6)),
    },
    [72] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(73)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(71)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(38)),
    },
    [73] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(74)),
    },
    [74] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 7)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 7)),
    },
    [75] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(103)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(104)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(80)),
    },
    [76] = {
        [sym__type_expression] = ACTIONS(SHIFT(77)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(52)),
    },
    [77] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(78)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(79)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(80)),
    },
    [78] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(96)),
    },
    [79] = {
        [sym_var_name] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [sym_type_name] = ACTIONS(SHIFT(71)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(87)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
    },
    [80] = {
        [sym_var_name] = ACTIONS(SHIFT(81)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(20)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(83)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(52)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(53)),
    },
    [82] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(86)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat1, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(80)),
    },
    [83] = {
        [sym__type_expression] = ACTIONS(SHIFT(84)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(52)),
    },
    [84] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(85)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat1, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(80)),
    },
    [85] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat1, 5)),
    },
    [86] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym__func_signature_repeat1, 4)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(90)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(91)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(30)),
    },
    [90] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(92)),
    },
    [91] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 8)),
    },
    [92] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 9)),
    },
    [93] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(94)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(92)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(38)),
    },
    [94] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(95)),
    },
    [95] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 10)),
    },
    [96] = {
        [sym_var_name] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [sym_type_name] = ACTIONS(SHIFT(74)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(97)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(94)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(92)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(30)),
    },
    [100] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(101)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(95)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(38)),
    },
    [101] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(102)),
    },
    [102] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 11)),
    },
    [103] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(79)),
    },
    [104] = {
        [sym_var_name] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [sym_type_name] = ACTIONS(SHIFT(70)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(105)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(108)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(74)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(30)),
    },
    [108] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(91)),
    },
    [109] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(90)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(91)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(38)),
    },
    [110] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_interface_type_repeat1, 3)),
    },
    [111] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(113)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(114)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(115)),
    },
    [112] = {
        [sym__type_expression] = ACTIONS(SHIFT(117)),
        [sym_pointer_type] = ACTIONS(SHIFT(118)),
        [sym_map_type] = ACTIONS(SHIFT(118)),
        [sym_slice_type] = ACTIONS(SHIFT(118)),
        [sym_struct_type] = ACTIONS(SHIFT(118)),
        [sym_interface_type] = ACTIONS(SHIFT(118)),
        [sym_type_name] = ACTIONS(SHIFT(118)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(120)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(121)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(122)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(123)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(124)),
    },
    [113] = {
        [sym__type_expression] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_pointer_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_map_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_slice_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_struct_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_interface_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_map] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_interface] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [114] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(116)),
    },
    [115] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_struct_type, 3)),
    },
    [116] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_struct_type, 4)),
    },
    [117] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(113)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(162)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_type_repeat1, 2)),
    },
    [118] = {
        [sym_var_name] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__type_expression, 1)),
    },
    [119] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [120] = {
        [sym__type_expression] = ACTIONS(SHIFT(161)),
        [sym_pointer_type] = ACTIONS(SHIFT(118)),
        [sym_map_type] = ACTIONS(SHIFT(118)),
        [sym_slice_type] = ACTIONS(SHIFT(118)),
        [sym_struct_type] = ACTIONS(SHIFT(118)),
        [sym_interface_type] = ACTIONS(SHIFT(118)),
        [sym_type_name] = ACTIONS(SHIFT(118)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(120)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(121)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(122)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(123)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(124)),
    },
    [121] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(135)),
    },
    [122] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(133)),
    },
    [123] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(129)),
    },
    [124] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(125)),
    },
    [125] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(126)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(127)),
    },
    [126] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(128)),
    },
    [127] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_interface_type, 3)),
    },
    [128] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_interface_type, 4)),
    },
    [129] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(113)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(130)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(131)),
    },
    [130] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(132)),
    },
    [131] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_struct_type, 3)),
    },
    [132] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_struct_type, 4)),
    },
    [133] = {
        [sym__type_expression] = ACTIONS(SHIFT(134)),
        [sym_pointer_type] = ACTIONS(SHIFT(118)),
        [sym_map_type] = ACTIONS(SHIFT(118)),
        [sym_slice_type] = ACTIONS(SHIFT(118)),
        [sym_struct_type] = ACTIONS(SHIFT(118)),
        [sym_interface_type] = ACTIONS(SHIFT(118)),
        [sym_type_name] = ACTIONS(SHIFT(118)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(120)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(121)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(122)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(123)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(124)),
    },
    [134] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_slice_type, 3)),
    },
    [135] = {
        [sym__type_expression] = ACTIONS(SHIFT(136)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(138)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(141)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(142)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(143)),
    },
    [136] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(159)),
    },
    [137] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym__type_expression, 1)),
    },
    [138] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [139] = {
        [sym__type_expression] = ACTIONS(SHIFT(158)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(138)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(141)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(142)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(143)),
    },
    [140] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(154)),
    },
    [141] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(152)),
    },
    [142] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(148)),
    },
    [143] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(144)),
    },
    [144] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(145)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(146)),
    },
    [145] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(147)),
    },
    [146] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_interface_type, 3)),
    },
    [147] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_interface_type, 4)),
    },
    [148] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(113)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(149)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(150)),
    },
    [149] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(151)),
    },
    [150] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_struct_type, 3)),
    },
    [151] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_struct_type, 4)),
    },
    [152] = {
        [sym__type_expression] = ACTIONS(SHIFT(153)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(138)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(141)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(142)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(143)),
    },
    [153] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_slice_type, 3)),
    },
    [154] = {
        [sym__type_expression] = ACTIONS(SHIFT(155)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(138)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(141)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(142)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(143)),
    },
    [155] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(156)),
    },
    [156] = {
        [sym__type_expression] = ACTIONS(SHIFT(157)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(138)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(141)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(142)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(143)),
    },
    [157] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_map_type, 5)),
    },
    [158] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(REDUCE(sym_pointer_type, 2)),
    },
    [159] = {
        [sym__type_expression] = ACTIONS(SHIFT(160)),
        [sym_pointer_type] = ACTIONS(SHIFT(118)),
        [sym_map_type] = ACTIONS(SHIFT(118)),
        [sym_slice_type] = ACTIONS(SHIFT(118)),
        [sym_struct_type] = ACTIONS(SHIFT(118)),
        [sym_interface_type] = ACTIONS(SHIFT(118)),
        [sym_type_name] = ACTIONS(SHIFT(118)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(120)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(121)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(122)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(123)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(124)),
    },
    [160] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_map_type, 5)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_map_type, 5)),
    },
    [161] = {
        [sym_var_name] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_pointer_type, 2)),
    },
    [162] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_type_repeat1, 3)),
    },
    [163] = {
        [sym__type_expression] = ACTIONS(SHIFT(164)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(52)),
    },
    [164] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_slice_type, 3)),
    },
    [165] = {
        [sym__type_expression] = ACTIONS(SHIFT(166)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(138)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(141)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(142)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(143)),
    },
    [166] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(167)),
    },
    [167] = {
        [sym__type_expression] = ACTIONS(SHIFT(168)),
        [sym_pointer_type] = ACTIONS(SHIFT(45)),
        [sym_map_type] = ACTIONS(SHIFT(45)),
        [sym_slice_type] = ACTIONS(SHIFT(45)),
        [sym_struct_type] = ACTIONS(SHIFT(45)),
        [sym_interface_type] = ACTIONS(SHIFT(45)),
        [sym_type_name] = ACTIONS(SHIFT(45)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(46)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(48)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(49)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(50)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(51)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(52)),
    },
    [168] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_map_type, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_map_type, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_map_type, 5)),
    },
    [169] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_pointer_type, 2)),
    },
    [170] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat1] = ACTIONS(SHIFT(171)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(172)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(80)),
    },
    [171] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(182)),
    },
    [172] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
        [sym_type_name] = ACTIONS(SHIFT(34)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(173)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 5)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(176)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(177)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(30)),
    },
    [176] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(178)),
    },
    [177] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 8)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 8)),
    },
    [178] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 9)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 9)),
    },
    [179] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(180)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(178)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(38)),
    },
    [180] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(181)),
    },
    [181] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 10)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 10)),
    },
    [182] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
        [sym_type_name] = ACTIONS(SHIFT(43)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(183)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 6)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(180)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(178)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(30)),
    },
    [186] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(187)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(181)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(38)),
    },
    [187] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(188)),
    },
    [188] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 11)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 11)),
    },
    [189] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(172)),
    },
    [190] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
        [sym_type_name] = ACTIONS(SHIFT(29)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(23)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(191)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym__func_signature, 4)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat3] = ACTIONS(SHIFT(194)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(43)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(30)),
    },
    [194] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(177)),
    },
    [195] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym__func_signature_repeat2] = ACTIONS(SHIFT(176)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(177)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(38)),
    },
    [196] = {
        [sym__line_break] = ACTIONS(SHIFT(382)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(382)),
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
        [ts_builtin_sym_error] = ACTIONS(SHIFT(203)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(204)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(203)),
        [aux_sym_STR_var] = ACTIONS(SHIFT(205)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(206)),
        [aux_sym_STR_return] = ACTIONS(SHIFT(207)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_for] = ACTIONS(SHIFT(209)),
        [aux_sym_STR_if] = ACTIONS(SHIFT(210)),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__identifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym__statement, 1)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(204)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(381)),
        [aux_sym_STR_var] = ACTIONS(SHIFT(205)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_block_statement_repeat1, 1)),
        [aux_sym_STR_return] = ACTIONS(SHIFT(207)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_for] = ACTIONS(SHIFT(209)),
        [aux_sym_STR_if] = ACTIONS(SHIFT(210)),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [200] = {
        [sym__line_break] = ACTIONS(SHIFT(380)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(288)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(380)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(290)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
    },
    [201] = {
        [sym__line_break] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym__expression, 1)),
    },
    [202] = {
        [sym__line_break] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(369)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(370)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(SHIFT(371)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym__expression, 1)),
    },
    [203] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(368)),
    },
    [204] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [205] = {
        [sym_var_name] = ACTIONS(SHIFT(336)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_block_statement, 2)),
    },
    [207] = {
        [sym__expression] = ACTIONS(SHIFT(306)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [sym__line_break] = ACTIONS(SHIFT(308)),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(309)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(308)),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(310)),
    },
    [208] = {
        [sym__expression] = ACTIONS(SHIFT(286)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [209] = {
        [sym_var_name] = ACTIONS(SHIFT(273)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(274)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [sym__expression] = ACTIONS(SHIFT(214)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(217)),
    },
    [211] = {
        [sym__expression] = ACTIONS(SHIFT(212)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [212] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
    },
    [213] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [214] = {
        [sym_block_statement] = ACTIONS(SHIFT(219)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(220)),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(221)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(223)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(225)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(227)),
    },
    [215] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym__expression, 1)),
    },
    [216] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [217] = {
        [sym__expression] = ACTIONS(SHIFT(218)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(217)),
    },
    [218] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [aux_sym_STR_else] = ACTIONS(SHIFT(267)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_if_statement, 3)),
    },
    [220] = {
        [sym__expression] = ACTIONS(SHIFT(237)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(240)),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
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
        [ts_builtin_sym_error] = ACTIONS(SHIFT(234)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(204)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(234)),
        [aux_sym_STR_var] = ACTIONS(SHIFT(205)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(235)),
        [aux_sym_STR_return] = ACTIONS(SHIFT(207)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_for] = ACTIONS(SHIFT(209)),
        [aux_sym_STR_if] = ACTIONS(SHIFT(210)),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [222] = {
        [sym__expression] = ACTIONS(SHIFT(233)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(217)),
    },
    [223] = {
        [sym_var_name] = ACTIONS(SHIFT(232)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym__expression] = ACTIONS(SHIFT(231)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(217)),
    },
    [225] = {
        [sym__expression] = ACTIONS(SHIFT(230)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(217)),
    },
    [226] = {
        [sym__expression] = ACTIONS(SHIFT(229)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(217)),
    },
    [227] = {
        [sym__expression] = ACTIONS(SHIFT(228)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(217)),
    },
    [228] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
    },
    [229] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(227)),
    },
    [230] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(227)),
    },
    [231] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(227)),
    },
    [232] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
    },
    [233] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(227)),
    },
    [234] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(236)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__identifier] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_else] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_block_statement, 2)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_else] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_block_statement, 3)),
    },
    [237] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(243)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(244)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(245)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(247)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(248)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(251)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(252)),
    },
    [238] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym__expression, 1)),
    },
    [239] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [240] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [241] = {
        [sym__expression] = ACTIONS(SHIFT(242)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [242] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
    },
    [243] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(266)),
    },
    [244] = {
        [sym__expression] = ACTIONS(SHIFT(261)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(262)),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [245] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [246] = {
        [sym__expression] = ACTIONS(SHIFT(260)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [247] = {
        [sym__expression] = ACTIONS(SHIFT(258)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [248] = {
        [sym_var_name] = ACTIONS(SHIFT(257)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [sym__expression] = ACTIONS(SHIFT(256)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [250] = {
        [sym__expression] = ACTIONS(SHIFT(255)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [251] = {
        [sym__expression] = ACTIONS(SHIFT(254)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [252] = {
        [sym__expression] = ACTIONS(SHIFT(253)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [253] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
    },
    [254] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(252)),
    },
    [255] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(251)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(252)),
    },
    [256] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(251)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(252)),
    },
    [257] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
    },
    [258] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(259)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(244)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 2)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(247)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(248)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(251)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(252)),
    },
    [259] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 3)),
    },
    [260] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(252)),
    },
    [261] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(263)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(244)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(264)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(247)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(248)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(251)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(252)),
    },
    [262] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [263] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(265)),
    },
    [264] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [265] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [266] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [267] = {
        [sym_block_statement] = ACTIONS(SHIFT(268)),
        [sym_if_statement] = ACTIONS(SHIFT(268)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(269)),
        [aux_sym_STR_if] = ACTIONS(SHIFT(210)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym__identifier] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_if_statement, 5)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_if_statement, 5)),
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
        [ts_builtin_sym_error] = ACTIONS(SHIFT(270)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(204)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(270)),
        [aux_sym_STR_var] = ACTIONS(SHIFT(205)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(271)),
        [aux_sym_STR_return] = ACTIONS(SHIFT(207)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(SHIFT(208)),
        [aux_sym_STR_for] = ACTIONS(SHIFT(209)),
        [aux_sym_STR_if] = ACTIONS(SHIFT(210)),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [270] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(272)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__identifier] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_block_statement, 2)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_block_statement, 3)),
    },
    [273] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(275)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(SHIFT(276)),
    },
    [274] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [275] = {
        [sym_var_name] = ACTIONS(SHIFT(280)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(281)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [276] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_range] = ACTIONS(SHIFT(277)),
    },
    [277] = {
        [sym__expression] = ACTIONS(SHIFT(278)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(217)),
    },
    [278] = {
        [sym_block_statement] = ACTIONS(SHIFT(279)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(220)),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(269)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(223)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(225)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(227)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym__identifier] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_number] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_range_statement, 6)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_range_statement, 6)),
    },
    [280] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_COLON_EQ] = ACTIONS(SHIFT(282)),
    },
    [281] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [282] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_range] = ACTIONS(SHIFT(283)),
    },
    [283] = {
        [sym__expression] = ACTIONS(SHIFT(284)),
        [sym_call_expression] = ACTIONS(SHIFT(215)),
        [sym_selector_expression] = ACTIONS(SHIFT(215)),
        [sym_math_op] = ACTIONS(SHIFT(215)),
        [sym_bool_op] = ACTIONS(SHIFT(215)),
        [sym_var_name] = ACTIONS(SHIFT(215)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(215)),
        [sym__identifier] = ACTIONS(SHIFT(216)),
        [sym_number] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(217)),
    },
    [284] = {
        [sym_block_statement] = ACTIONS(SHIFT(285)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(220)),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(269)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(223)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(222)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(224)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(225)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(226)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(227)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(227)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym__identifier] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_number] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_range_statement, 8)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_range_statement, 8)),
    },
    [286] = {
        [sym__line_break] = ACTIONS(SHIFT(287)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(288)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(287)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(290)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
    },
    [287] = {
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
    },
    [288] = {
        [sym__expression] = ACTIONS(SHIFT(301)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(302)),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [289] = {
        [sym__expression] = ACTIONS(SHIFT(300)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [292] = {
        [sym__expression] = ACTIONS(SHIFT(297)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [293] = {
        [sym__expression] = ACTIONS(SHIFT(296)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [294] = {
        [sym__expression] = ACTIONS(SHIFT(295)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [295] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
    },
    [296] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
    },
    [297] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
    },
    [298] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
    },
    [299] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
    },
    [300] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
    },
    [301] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(303)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(244)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(304)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(247)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(248)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(251)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(252)),
    },
    [302] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [303] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(305)),
    },
    [304] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [305] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
    },
    [306] = {
        [sym__line_break] = ACTIONS(SHIFT(312)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(313)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(314)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(312)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(315)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(316)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(317)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(315)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(318)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(318)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(319)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(320)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(321)),
    },
    [307] = {
        [sym__line_break] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym__expression, 1)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym__identifier] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_return_statement, 2)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_return_statement, 2)),
    },
    [309] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [310] = {
        [sym__expression] = ACTIONS(SHIFT(311)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(309)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(310)),
    },
    [311] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 2)),
    },
    [312] = {
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_return_statement, 3)),
    },
    [313] = {
        [sym__line_break] = ACTIONS(SHIFT(335)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(335)),
    },
    [314] = {
        [sym__expression] = ACTIONS(SHIFT(330)),
        [sym_call_expression] = ACTIONS(SHIFT(238)),
        [sym_selector_expression] = ACTIONS(SHIFT(238)),
        [sym_math_op] = ACTIONS(SHIFT(238)),
        [sym_bool_op] = ACTIONS(SHIFT(238)),
        [sym_var_name] = ACTIONS(SHIFT(238)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(238)),
        [sym__identifier] = ACTIONS(SHIFT(239)),
        [sym_number] = ACTIONS(SHIFT(238)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(331)),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(241)),
    },
    [315] = {
        [sym__expression] = ACTIONS(SHIFT(329)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(309)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(310)),
    },
    [316] = {
        [sym__expression] = ACTIONS(SHIFT(327)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(309)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(310)),
    },
    [317] = {
        [sym_var_name] = ACTIONS(SHIFT(326)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [318] = {
        [sym__expression] = ACTIONS(SHIFT(325)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(309)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(310)),
    },
    [319] = {
        [sym__expression] = ACTIONS(SHIFT(324)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(309)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(310)),
    },
    [320] = {
        [sym__expression] = ACTIONS(SHIFT(323)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(309)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(310)),
    },
    [321] = {
        [sym__expression] = ACTIONS(SHIFT(322)),
        [sym_call_expression] = ACTIONS(SHIFT(307)),
        [sym_selector_expression] = ACTIONS(SHIFT(307)),
        [sym_math_op] = ACTIONS(SHIFT(307)),
        [sym_bool_op] = ACTIONS(SHIFT(307)),
        [sym_var_name] = ACTIONS(SHIFT(307)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(307)),
        [sym__identifier] = ACTIONS(SHIFT(309)),
        [sym_number] = ACTIONS(SHIFT(307)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(310)),
    },
    [322] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
    },
    [323] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(321)),
    },
    [324] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(315)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(315)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(320)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(321)),
    },
    [325] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(315)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(315)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(320)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(321)),
    },
    [326] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_selector_expression, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_selector_expression, 3)),
    },
    [327] = {
        [sym__line_break] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(328)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(314)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 2)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(315)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(316)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(317)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(315)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(318)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(318)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(319)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(320)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(321)),
    },
    [328] = {
        [sym__line_break] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 3)),
    },
    [329] = {
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(321)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(321)),
    },
    [330] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(332)),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(244)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(333)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(247)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(248)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(246)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(249)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(250)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(251)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(252)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(252)),
    },
    [331] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 3)),
    },
    [332] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(334)),
    },
    [333] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 4)),
    },
    [334] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE(sym_call_expression, 5)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym__identifier] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_return_statement, 4)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_return_statement, 4)),
    },
    [336] = {
        [sym__type_expression] = ACTIONS(SHIFT(338)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(340)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(341)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(342)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(343)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(344)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(345)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(346)),
    },
    [337] = {
        [sym__type_expression] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_pointer_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_map_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_slice_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_struct_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_interface_type] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_map] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_interface] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [338] = {
        [sym__line_break] = ACTIONS(SHIFT(364)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(364)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(365)),
    },
    [339] = {
        [sym__line_break] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym__type_expression, 1)),
    },
    [340] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [341] = {
        [sym__expression] = ACTIONS(SHIFT(362)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [342] = {
        [sym__type_expression] = ACTIONS(SHIFT(361)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(340)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(342)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(343)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(344)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(345)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(346)),
    },
    [343] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(357)),
    },
    [344] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(355)),
    },
    [345] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(351)),
    },
    [346] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(347)),
    },
    [347] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(348)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(349)),
    },
    [348] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(350)),
    },
    [349] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_interface_type, 3)),
    },
    [350] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_interface_type, 4)),
    },
    [351] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(113)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(352)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(353)),
    },
    [352] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(354)),
    },
    [353] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_struct_type, 3)),
    },
    [354] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_struct_type, 4)),
    },
    [355] = {
        [sym__type_expression] = ACTIONS(SHIFT(356)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(340)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(342)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(343)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(344)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(345)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(346)),
    },
    [356] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_slice_type, 3)),
    },
    [357] = {
        [sym__type_expression] = ACTIONS(SHIFT(358)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(138)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(141)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(142)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(143)),
    },
    [358] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(359)),
    },
    [359] = {
        [sym__type_expression] = ACTIONS(SHIFT(360)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(340)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(342)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(343)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(344)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(345)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(346)),
    },
    [360] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_map_type, 5)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_map_type, 5)),
    },
    [361] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE(sym_pointer_type, 2)),
    },
    [362] = {
        [sym__line_break] = ACTIONS(SHIFT(363)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(288)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(363)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(290)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_var_declaration, 5)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_var_declaration, 4)),
    },
    [365] = {
        [sym__expression] = ACTIONS(SHIFT(366)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [366] = {
        [sym__line_break] = ACTIONS(SHIFT(367)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(288)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(367)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(290)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_number] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_var_declaration, 6)),
    },
    [368] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_block_statement, 3)),
    },
    [369] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_COLON_EQ] = ACTIONS(SHIFT(377)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [372] = {
        [sym__line_break] = ACTIONS(SHIFT(373)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(288)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(373)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(290)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym__identifier] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
    },
    [374] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(376)),
        [aux_sym_STR_COMMA] = ACTIONS(SHIFT(370)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
    },
    [375] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
    },
    [376] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
    },
    [377] = {
        [sym__expression] = ACTIONS(SHIFT(378)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [378] = {
        [sym__line_break] = ACTIONS(SHIFT(379)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(288)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(379)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(290)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym__identifier] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
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
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_block_statement_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_return] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_COLON_EQ] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_for] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_if] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_BANG] = ACTIONS(REDUCE(sym_expression_statement, 2)),
    },
    [381] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(REDUCE(aux_sym_block_statement_repeat1, 2)),
    },
    [382] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_func_declaration, 5)),
    },
    [383] = {
        [sym__type_expression] = ACTIONS(SHIFT(384)),
        [sym_pointer_type] = ACTIONS(SHIFT(339)),
        [sym_map_type] = ACTIONS(SHIFT(339)),
        [sym_slice_type] = ACTIONS(SHIFT(339)),
        [sym_struct_type] = ACTIONS(SHIFT(339)),
        [sym_interface_type] = ACTIONS(SHIFT(339)),
        [sym_type_name] = ACTIONS(SHIFT(339)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(340)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(385)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(342)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(343)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(344)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(345)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(346)),
    },
    [384] = {
        [sym__line_break] = ACTIONS(SHIFT(388)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(388)),
        [aux_sym_STR_EQ] = ACTIONS(SHIFT(389)),
    },
    [385] = {
        [sym__expression] = ACTIONS(SHIFT(386)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [386] = {
        [sym__line_break] = ACTIONS(SHIFT(387)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(288)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(387)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(290)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
    },
    [387] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
    },
    [388] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_STR_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_var_declaration, 4)),
    },
    [389] = {
        [sym__expression] = ACTIONS(SHIFT(390)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(201)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(201)),
        [sym__identifier] = ACTIONS(SHIFT(213)),
        [sym_number] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_BANG] = ACTIONS(SHIFT(211)),
    },
    [390] = {
        [sym__line_break] = ACTIONS(SHIFT(391)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LPAREN] = ACTIONS(SHIFT(288)),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(391)),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_DOT] = ACTIONS(SHIFT(290)),
        [aux_sym_STR_SLASH] = ACTIONS(SHIFT(289)),
        [aux_sym_STR_PLUS] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_DASH] = ACTIONS(SHIFT(291)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(SHIFT(292)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(SHIFT(293)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_LT] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT_EQ] = ACTIONS(SHIFT(294)),
        [aux_sym_STR_GT] = ACTIONS(SHIFT(294)),
    },
    [391] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_LPAREN] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DOT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_SLASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PLUS] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_DASH] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_PIPE_PIPE] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_AMP_AMP] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_EQ_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_LT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT_EQ] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_GT] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
    },
    [392] = {
        [sym__type_expression] = ACTIONS(SHIFT(394)),
        [sym_pointer_type] = ACTIONS(SHIFT(395)),
        [sym_map_type] = ACTIONS(SHIFT(395)),
        [sym_slice_type] = ACTIONS(SHIFT(395)),
        [sym_struct_type] = ACTIONS(SHIFT(395)),
        [sym_interface_type] = ACTIONS(SHIFT(395)),
        [sym_type_name] = ACTIONS(SHIFT(395)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(396)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(397)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(398)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(399)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(400)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(401)),
    },
    [393] = {
        [sym__type_expression] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_pointer_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_map_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_slice_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_struct_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_interface_type] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_type_name] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_map] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_LBRACK] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_struct] = ACTIONS(REDUCE(sym_type_name, 1)),
        [aux_sym_STR_interface] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [394] = {
        [sym__line_break] = ACTIONS(SHIFT(417)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(SHIFT(417)),
    },
    [395] = {
        [sym__line_break] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym__type_expression, 1)),
    },
    [396] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_type_name, 1)),
    },
    [397] = {
        [sym__type_expression] = ACTIONS(SHIFT(416)),
        [sym_pointer_type] = ACTIONS(SHIFT(395)),
        [sym_map_type] = ACTIONS(SHIFT(395)),
        [sym_slice_type] = ACTIONS(SHIFT(395)),
        [sym_struct_type] = ACTIONS(SHIFT(395)),
        [sym_interface_type] = ACTIONS(SHIFT(395)),
        [sym_type_name] = ACTIONS(SHIFT(395)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(396)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(397)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(398)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(399)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(400)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(401)),
    },
    [398] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(412)),
    },
    [399] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(410)),
    },
    [400] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(406)),
    },
    [401] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_LBRACE] = ACTIONS(SHIFT(402)),
    },
    [402] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(403)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(404)),
    },
    [403] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(405)),
    },
    [404] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_interface_type, 3)),
    },
    [405] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_interface_type, 4)),
    },
    [406] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(113)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(407)),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(408)),
    },
    [407] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACE] = ACTIONS(SHIFT(409)),
    },
    [408] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_struct_type, 3)),
    },
    [409] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_struct_type, 4)),
    },
    [410] = {
        [sym__type_expression] = ACTIONS(SHIFT(411)),
        [sym_pointer_type] = ACTIONS(SHIFT(395)),
        [sym_map_type] = ACTIONS(SHIFT(395)),
        [sym_slice_type] = ACTIONS(SHIFT(395)),
        [sym_struct_type] = ACTIONS(SHIFT(395)),
        [sym_interface_type] = ACTIONS(SHIFT(395)),
        [sym_type_name] = ACTIONS(SHIFT(395)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(396)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(397)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(398)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(399)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(400)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(401)),
    },
    [411] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_slice_type, 3)),
    },
    [412] = {
        [sym__type_expression] = ACTIONS(SHIFT(413)),
        [sym_pointer_type] = ACTIONS(SHIFT(137)),
        [sym_map_type] = ACTIONS(SHIFT(137)),
        [sym_slice_type] = ACTIONS(SHIFT(137)),
        [sym_struct_type] = ACTIONS(SHIFT(137)),
        [sym_interface_type] = ACTIONS(SHIFT(137)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(138)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(139)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(140)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(141)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(142)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(143)),
    },
    [413] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RBRACK] = ACTIONS(SHIFT(414)),
    },
    [414] = {
        [sym__type_expression] = ACTIONS(SHIFT(415)),
        [sym_pointer_type] = ACTIONS(SHIFT(395)),
        [sym_map_type] = ACTIONS(SHIFT(395)),
        [sym_slice_type] = ACTIONS(SHIFT(395)),
        [sym_struct_type] = ACTIONS(SHIFT(395)),
        [sym_interface_type] = ACTIONS(SHIFT(395)),
        [sym_type_name] = ACTIONS(SHIFT(395)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(396)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_STAR] = ACTIONS(SHIFT(397)),
        [aux_sym_STR_map] = ACTIONS(SHIFT(398)),
        [aux_sym_STR_LBRACK] = ACTIONS(SHIFT(399)),
        [aux_sym_STR_struct] = ACTIONS(SHIFT(400)),
        [aux_sym_STR_interface] = ACTIONS(SHIFT(401)),
    },
    [415] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_map_type, 5)),
    },
    [416] = {
        [sym__line_break] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE(sym_pointer_type, 2)),
    },
    [417] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [aux_sym_STR_SEMI] = ACTIONS(REDUCE_EXTRA(sym__line_break)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_type_declaration, 4)),
    },
    [418] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym__declaration] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [aux_sym_STR_import] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_imports_block, 2)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_imports_block, 2)),
    },
    [419] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym__declaration] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_package_import, 1)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_STR_import] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_package_import, 1)),
    },
    [420] = {
        [sym_package_import] = ACTIONS(SHIFT(421)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(422)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(423)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_imports_block_repeat1] = ACTIONS(SHIFT(422)),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(424)),
    },
    [421] = {
        [sym_package_import] = ACTIONS(SHIFT(421)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(423)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_imports_block_repeat1] = ACTIONS(SHIFT(426)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_imports_block_repeat1, 1)),
    },
    [422] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(SHIFT(425)),
    },
    [423] = {
        [sym_package_import] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_imports_block_repeat1] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(sym_package_import, 1)),
    },
    [424] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym__declaration] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [aux_sym_STR_import] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_imports_block, 3)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_imports_block, 3)),
    },
    [425] = {
        [sym_imports_block] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym__declaration] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat1] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [aux_sym_STR_import] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(sym_imports_block, 4)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(sym_imports_block, 4)),
    },
    [426] = {
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_STR_RPAREN] = ACTIONS(REDUCE(aux_sym_imports_block_repeat1, 2)),
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
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [aux_sym_STR_type] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [aux_sym_STR_var] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
        [aux_sym_STR_func] = ACTIONS(REDUCE(aux_sym_program_repeat1, 2)),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_golang);
