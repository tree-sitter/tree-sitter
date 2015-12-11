#include "tree_sitter/parser.h"

#define STATE_COUNT 446
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

static const TSSymbolMetadata ts_symbol_metadata[SYMBOL_COUNT] = {
    [sym_program] = {.visible = true, .named = true, .extra = false},
    [sym_package_directive] = {.visible = true, .named = true, .extra = false},
    [sym_imports_block] = {.visible = true, .named = true, .extra = false},
    [sym_package_import] = {.visible = true, .named = true, .extra = false},
    [sym__declaration] = {.visible = false, .named = false, .extra = false},
    [sym_type_declaration] = {.visible = true, .named = true, .extra = false},
    [sym_var_declaration] = {.visible = true, .named = true, .extra = false},
    [sym_func_declaration] = {.visible = true, .named = true, .extra = false},
    [sym_block_statement] = {.visible = true, .named = true, .extra = false},
    [sym__type_expression] = {.visible = false, .named = false, .extra = false},
    [sym_pointer_type] = {.visible = true, .named = true, .extra = false},
    [sym_map_type] = {.visible = true, .named = true, .extra = false},
    [sym_slice_type] = {.visible = true, .named = true, .extra = false},
    [sym_struct_type] = {.visible = true, .named = true, .extra = false},
    [sym_interface_type] = {.visible = true, .named = true, .extra = false},
    [sym__statement] = {.visible = false, .named = false, .extra = false},
    [sym_return_statement] = {.visible = true, .named = true, .extra = false},
    [sym_short_var_declaration] = {.visible = true, .named = true, .extra = false},
    [sym_range_statement] = {.visible = true, .named = true, .extra = false},
    [sym_if_statement] = {.visible = true, .named = true, .extra = false},
    [sym_expression_statement] = {.visible = true, .named = true, .extra = false},
    [sym__expression] = {.visible = false, .named = false, .extra = false},
    [sym_call_expression] = {.visible = true, .named = true, .extra = false},
    [sym_selector_expression] = {.visible = true, .named = true, .extra = false},
    [sym_math_op] = {.visible = true, .named = true, .extra = false},
    [sym_bool_op] = {.visible = true, .named = true, .extra = false},
    [sym__func_signature] = {.visible = false, .named = false, .extra = false},
    [sym_package_name] = {.visible = true, .named = true, .extra = false},
    [sym_var_name] = {.visible = true, .named = true, .extra = false},
    [sym_type_name] = {.visible = true, .named = true, .extra = false},
    [aux_sym_program_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_program_repeat2] = {.visible = false, .named = false, .extra = false},
    [aux_sym_imports_block_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_block_statement_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_struct_type_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_interface_type_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_return_statement_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_short_var_declaration_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym__func_signature_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym__func_signature_repeat2] = {.visible = false, .named = false, .extra = false},
    [aux_sym__func_signature_repeat3] = {.visible = false, .named = false, .extra = false},
    [ts_builtin_sym_error] = {.visible = true, .named = true, .extra = false},
    [ts_builtin_sym_end] = {.visible = false, .named = false, .extra = false},
    [anon_sym_package] = {.visible = true, .named = false, .extra = false},
    [anon_sym_import] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LPAREN] = {.visible = true, .named = false, .extra = false},
    [anon_sym_RPAREN] = {.visible = true, .named = false, .extra = false},
    [anon_sym_type] = {.visible = true, .named = false, .extra = false},
    [anon_sym_SEMI] = {.visible = true, .named = false, .extra = false},
    [anon_sym_var] = {.visible = true, .named = false, .extra = false},
    [anon_sym_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_func] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LBRACE] = {.visible = true, .named = false, .extra = false},
    [anon_sym_RBRACE] = {.visible = true, .named = false, .extra = false},
    [anon_sym_STAR] = {.visible = true, .named = false, .extra = false},
    [anon_sym_map] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LBRACK] = {.visible = true, .named = false, .extra = false},
    [anon_sym_RBRACK] = {.visible = true, .named = false, .extra = false},
    [anon_sym_struct] = {.visible = true, .named = false, .extra = false},
    [anon_sym_interface] = {.visible = true, .named = false, .extra = false},
    [anon_sym_return] = {.visible = true, .named = false, .extra = false},
    [anon_sym_COMMA] = {.visible = true, .named = false, .extra = false},
    [anon_sym_COLON_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_for] = {.visible = true, .named = false, .extra = false},
    [anon_sym_range] = {.visible = true, .named = false, .extra = false},
    [anon_sym_if] = {.visible = true, .named = false, .extra = false},
    [anon_sym_else] = {.visible = true, .named = false, .extra = false},
    [anon_sym_DOT] = {.visible = true, .named = false, .extra = false},
    [anon_sym_SLASH] = {.visible = true, .named = false, .extra = false},
    [anon_sym_PLUS] = {.visible = true, .named = false, .extra = false},
    [anon_sym_DASH] = {.visible = true, .named = false, .extra = false},
    [anon_sym_PIPE_PIPE] = {.visible = true, .named = false, .extra = false},
    [anon_sym_AMP_AMP] = {.visible = true, .named = false, .extra = false},
    [anon_sym_EQ_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LT_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LT] = {.visible = true, .named = false, .extra = false},
    [anon_sym_GT_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_GT] = {.visible = true, .named = false, .extra = false},
    [anon_sym_BANG] = {.visible = true, .named = false, .extra = false},
    [sym__line_break] = {.visible = false, .named = false, .extra = false},
    [sym_string] = {.visible = true, .named = true, .extra = false},
    [sym__identifier] = {.visible = false, .named = false, .extra = false},
    [sym_number] = {.visible = true, .named = true, .extra = false},
    [sym_comment] = {.visible = true, .named = true, .extra = false},
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(52);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(53);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(54);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'f')
                ADVANCE(55);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(56);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(58);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(61);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(64);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(65);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(67);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(91);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 95:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(96);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 96:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'u')
                ADVANCE(97);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 97:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(98);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(99);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(102);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 124:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 's')
                ADVANCE(125);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 125:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(126);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 155:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(156);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 159:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(160);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 160:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'o')
                ADVANCE(161);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 161:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'r')
                ADVANCE(162);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 162:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 't')
                ADVANCE(163);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 166:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'k')
                ADVANCE(167);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 167:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'a')
                ADVANCE(168);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 168:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(169);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 169:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(170);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 172:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'n')
                ADVANCE(173);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 173:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'g')
                ADVANCE(174);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 174:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(175);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 177:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'p')
                ADVANCE(178);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 178:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(179);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
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
    [211] = 103,
    [212] = 118,
    [213] = 103,
    [214] = 103,
    [215] = 121,
    [216] = 121,
    [217] = 120,
    [218] = 121,
    [219] = 121,
    [220] = 122,
    [221] = 127,
    [222] = 82,
    [223] = 120,
    [224] = 32,
    [225] = 120,
    [226] = 120,
    [227] = 120,
    [228] = 120,
    [229] = 121,
    [230] = 121,
    [231] = 121,
    [232] = 121,
    [233] = 121,
    [234] = 121,
    [235] = 78,
    [236] = 122,
    [237] = 122,
    [238] = 128,
    [239] = 128,
    [240] = 121,
    [241] = 120,
    [242] = 128,
    [243] = 128,
    [244] = 71,
    [245] = 127,
    [246] = 121,
    [247] = 120,
    [248] = 120,
    [249] = 32,
    [250] = 120,
    [251] = 120,
    [252] = 120,
    [253] = 120,
    [254] = 128,
    [255] = 128,
    [256] = 128,
    [257] = 128,
    [258] = 128,
    [259] = 128,
    [260] = 128,
    [261] = 71,
    [262] = 128,
    [263] = 128,
    [264] = 71,
    [265] = 128,
    [266] = 128,
    [267] = 121,
    [268] = 129,
    [269] = 82,
    [270] = 82,
    [271] = 78,
    [272] = 82,
    [273] = 82,
    [274] = 132,
    [275] = 132,
    [276] = 32,
    [277] = 133,
    [278] = 120,
    [279] = 121,
    [280] = 82,
    [281] = 139,
    [282] = 139,
    [283] = 133,
    [284] = 120,
    [285] = 121,
    [286] = 82,
    [287] = 103,
    [288] = 127,
    [289] = 82,
    [290] = 120,
    [291] = 32,
    [292] = 120,
    [293] = 120,
    [294] = 120,
    [295] = 120,
    [296] = 140,
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
    [310] = 82,
    [311] = 120,
    [312] = 142,
    [313] = 141,
    [314] = 141,
    [315] = 80,
    [316] = 127,
    [317] = 82,
    [318] = 120,
    [319] = 120,
    [320] = 32,
    [321] = 120,
    [322] = 120,
    [323] = 120,
    [324] = 120,
    [325] = 143,
    [326] = 141,
    [327] = 141,
    [328] = 141,
    [329] = 141,
    [330] = 141,
    [331] = 141,
    [332] = 141,
    [333] = 80,
    [334] = 128,
    [335] = 141,
    [336] = 71,
    [337] = 141,
    [338] = 141,
    [339] = 82,
    [340] = 142,
    [341] = 144,
    [342] = 144,
    [343] = 146,
    [344] = 146,
    [345] = 120,
    [346] = 72,
    [347] = 73,
    [348] = 74,
    [349] = 42,
    [350] = 42,
    [351] = 146,
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
    [368] = 82,
    [369] = 140,
    [370] = 82,
    [371] = 120,
    [372] = 147,
    [373] = 103,
    [374] = 82,
    [375] = 140,
    [376] = 80,
    [377] = 139,
    [378] = 32,
    [379] = 120,
    [380] = 103,
    [381] = 82,
    [382] = 140,
    [383] = 132,
    [384] = 132,
    [385] = 139,
    [386] = 120,
    [387] = 103,
    [388] = 82,
    [389] = 140,
    [390] = 82,
    [391] = 140,
    [392] = 78,
    [393] = 34,
    [394] = 148,
    [395] = 144,
    [396] = 146,
    [397] = 120,
    [398] = 103,
    [399] = 34,
    [400] = 149,
    [401] = 34,
    [402] = 120,
    [403] = 150,
    [404] = 103,
    [405] = 34,
    [406] = 149,
    [407] = 72,
    [408] = 72,
    [409] = 80,
    [410] = 80,
    [411] = 72,
    [412] = 73,
    [413] = 74,
    [414] = 42,
    [415] = 42,
    [416] = 80,
    [417] = 76,
    [418] = 78,
    [419] = 80,
    [420] = 80,
    [421] = 76,
    [422] = 78,
    [423] = 80,
    [424] = 80,
    [425] = 72,
    [426] = 80,
    [427] = 72,
    [428] = 74,
    [429] = 72,
    [430] = 80,
    [431] = 80,
    [432] = 34,
    [433] = 148,
    [434] = 14,
    [435] = 151,
    [436] = 14,
    [437] = 151,
    [438] = 71,
    [439] = 14,
    [440] = 151,
    [441] = 14,
    [442] = 71,
    [443] = 12,
    [444] = 12,
    [445] = 34,
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
        [aux_sym_program_repeat1] = ACTIONS(SHIFT(445)),
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
        [aux_sym_program_repeat2] = ACTIONS(SHIFT(444)),
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
        [aux_sym_program_repeat2] = ACTIONS(SHIFT(443)),
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
        [sym_package_import] = ACTIONS(SHIFT(434)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(435)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(436)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym_type_name] = ACTIONS(SHIFT(407)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(408)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [sym_var_name] = ACTIONS(SHIFT(395)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(342)),
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
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 2)),
        [sym_type_name] = ACTIONS(SHIFT(22)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(23)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 2)),
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
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 2)),
        [sym_type_name] = ACTIONS(SHIFT(65)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(66)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 2)),
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
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [sym_type_name] = ACTIONS(SHIFT(71)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 5)),
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
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [sym_type_name] = ACTIONS(SHIFT(74)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 6)),
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
        [sym_var_name] = ACTIONS(REDUCE(sym__func_signature, 4)),
        [sym_type_name] = ACTIONS(SHIFT(70)),
        [aux_sym_interface_type_repeat1] = ACTIONS(REDUCE(sym__func_signature, 4)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(105)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__func_signature, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(REDUCE(sym__func_signature, 4)),
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
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 5)),
        [sym_type_name] = ACTIONS(SHIFT(34)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(173)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 5)),
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
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 6)),
        [sym_type_name] = ACTIONS(SHIFT(43)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(183)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 6)),
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
        [sym_block_statement] = ACTIONS(REDUCE(sym__func_signature, 4)),
        [sym_type_name] = ACTIONS(SHIFT(29)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(191)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__func_signature, 4)),
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
        [anon_sym_SEMI] = ACTIONS(SHIFT(393)),
        [sym__line_break] = ACTIONS(SHIFT(394)),
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
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(212)),
        [sym_number] = ACTIONS(SHIFT(211)),
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
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(392)),
        [anon_sym_var] = ACTIONS(SHIFT(204)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_block_statement_repeat1, 1)),
        [anon_sym_return] = ACTIONS(SHIFT(206)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(207)),
        [anon_sym_for] = ACTIONS(SHIFT(208)),
        [anon_sym_if] = ACTIONS(SHIFT(209)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(212)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(288)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(390)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(SHIFT(291)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(292)),
        [anon_sym_DASH] = ACTIONS(SHIFT(292)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(293)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(SHIFT(391)),
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
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(377)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(378)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(379)),
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
        [anon_sym_RBRACE] = ACTIONS(SHIFT(376)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
        [sym_var_name] = ACTIONS(SHIFT(341)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(342)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym__line_break] = ACTIONS(REDUCE(sym_block_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [sym__expression] = ACTIONS(SHIFT(308)),
        [sym_call_expression] = ACTIONS(SHIFT(309)),
        [sym_selector_expression] = ACTIONS(SHIFT(309)),
        [sym_math_op] = ACTIONS(SHIFT(309)),
        [sym_bool_op] = ACTIONS(SHIFT(309)),
        [sym_var_name] = ACTIONS(SHIFT(309)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(310)),
        [anon_sym_BANG] = ACTIONS(SHIFT(311)),
        [sym__line_break] = ACTIONS(SHIFT(312)),
        [sym_string] = ACTIONS(SHIFT(309)),
        [sym__identifier] = ACTIONS(SHIFT(313)),
        [sym_number] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [sym__expression] = ACTIONS(SHIFT(287)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
        [sym_var_name] = ACTIONS(SHIFT(274)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [209] = {
        [sym__expression] = ACTIONS(SHIFT(215)),
        [sym_call_expression] = ACTIONS(SHIFT(216)),
        [sym_selector_expression] = ACTIONS(SHIFT(216)),
        [sym_math_op] = ACTIONS(SHIFT(216)),
        [sym_bool_op] = ACTIONS(SHIFT(216)),
        [sym_var_name] = ACTIONS(SHIFT(216)),
        [anon_sym_BANG] = ACTIONS(SHIFT(217)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(216)),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_number] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [sym__expression] = ACTIONS(SHIFT(213)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
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
    [212] = {
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
    [213] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [sym__line_break] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
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
    [215] = {
        [sym_block_statement] = ACTIONS(SHIFT(220)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(221)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(222)),
        [anon_sym_STAR] = ACTIONS(SHIFT(223)),
        [anon_sym_DOT] = ACTIONS(SHIFT(224)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(223)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(225)),
        [anon_sym_DASH] = ACTIONS(SHIFT(225)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(226)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(227)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT] = ACTIONS(SHIFT(228)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_GT] = ACTIONS(SHIFT(228)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
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
    [217] = {
        [sym__expression] = ACTIONS(SHIFT(219)),
        [sym_call_expression] = ACTIONS(SHIFT(216)),
        [sym_selector_expression] = ACTIONS(SHIFT(216)),
        [sym_math_op] = ACTIONS(SHIFT(216)),
        [sym_bool_op] = ACTIONS(SHIFT(216)),
        [sym_var_name] = ACTIONS(SHIFT(216)),
        [anon_sym_BANG] = ACTIONS(SHIFT(217)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(216)),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_number] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
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
    [219] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
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
        [anon_sym_else] = ACTIONS(SHIFT(268)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_if_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [sym__expression] = ACTIONS(SHIFT(238)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(240)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
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
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(235)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(235)),
        [anon_sym_var] = ACTIONS(SHIFT(204)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(236)),
        [anon_sym_return] = ACTIONS(SHIFT(206)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(207)),
        [anon_sym_for] = ACTIONS(SHIFT(208)),
        [anon_sym_if] = ACTIONS(SHIFT(209)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(212)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
        [sym__expression] = ACTIONS(SHIFT(233)),
        [sym_call_expression] = ACTIONS(SHIFT(216)),
        [sym_selector_expression] = ACTIONS(SHIFT(216)),
        [sym_math_op] = ACTIONS(SHIFT(216)),
        [sym_bool_op] = ACTIONS(SHIFT(216)),
        [sym_var_name] = ACTIONS(SHIFT(216)),
        [anon_sym_BANG] = ACTIONS(SHIFT(217)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(216)),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_number] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym_var_name] = ACTIONS(SHIFT(234)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [225] = {
        [sym__expression] = ACTIONS(SHIFT(232)),
        [sym_call_expression] = ACTIONS(SHIFT(216)),
        [sym_selector_expression] = ACTIONS(SHIFT(216)),
        [sym_math_op] = ACTIONS(SHIFT(216)),
        [sym_bool_op] = ACTIONS(SHIFT(216)),
        [sym_var_name] = ACTIONS(SHIFT(216)),
        [anon_sym_BANG] = ACTIONS(SHIFT(217)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(216)),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_number] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
        [sym__expression] = ACTIONS(SHIFT(231)),
        [sym_call_expression] = ACTIONS(SHIFT(216)),
        [sym_selector_expression] = ACTIONS(SHIFT(216)),
        [sym_math_op] = ACTIONS(SHIFT(216)),
        [sym_bool_op] = ACTIONS(SHIFT(216)),
        [sym_var_name] = ACTIONS(SHIFT(216)),
        [anon_sym_BANG] = ACTIONS(SHIFT(217)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(216)),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_number] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [sym__expression] = ACTIONS(SHIFT(230)),
        [sym_call_expression] = ACTIONS(SHIFT(216)),
        [sym_selector_expression] = ACTIONS(SHIFT(216)),
        [sym_math_op] = ACTIONS(SHIFT(216)),
        [sym_bool_op] = ACTIONS(SHIFT(216)),
        [sym_var_name] = ACTIONS(SHIFT(216)),
        [anon_sym_BANG] = ACTIONS(SHIFT(217)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(216)),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_number] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [228] = {
        [sym__expression] = ACTIONS(SHIFT(229)),
        [sym_call_expression] = ACTIONS(SHIFT(216)),
        [sym_selector_expression] = ACTIONS(SHIFT(216)),
        [sym_math_op] = ACTIONS(SHIFT(216)),
        [sym_bool_op] = ACTIONS(SHIFT(216)),
        [sym_var_name] = ACTIONS(SHIFT(216)),
        [anon_sym_BANG] = ACTIONS(SHIFT(217)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(216)),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_number] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [sym_block_statement] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
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
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT] = ACTIONS(SHIFT(228)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_GT] = ACTIONS(SHIFT(228)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [231] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(223)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(223)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(227)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT] = ACTIONS(SHIFT(228)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_GT] = ACTIONS(SHIFT(228)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [sym_block_statement] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(223)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(223)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(227)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT] = ACTIONS(SHIFT(228)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_GT] = ACTIONS(SHIFT(228)),
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
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT] = ACTIONS(SHIFT(228)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_GT] = ACTIONS(SHIFT(228)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
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
    [235] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(237)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
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
    [237] = {
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
    [238] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(244)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(245)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(246)),
        [anon_sym_STAR] = ACTIONS(SHIFT(247)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(248)),
        [anon_sym_DOT] = ACTIONS(SHIFT(249)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(247)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(250)),
        [anon_sym_DASH] = ACTIONS(SHIFT(250)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(251)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(252)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT] = ACTIONS(SHIFT(253)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_GT] = ACTIONS(SHIFT(253)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
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
    [240] = {
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
    [241] = {
        [sym__expression] = ACTIONS(SHIFT(243)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
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
    [243] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(267)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
        [sym__expression] = ACTIONS(SHIFT(262)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(263)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [246] = {
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
    [247] = {
        [sym__expression] = ACTIONS(SHIFT(258)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym__expression] = ACTIONS(SHIFT(260)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [sym_var_name] = ACTIONS(SHIFT(259)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [250] = {
        [sym__expression] = ACTIONS(SHIFT(257)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [sym__expression] = ACTIONS(SHIFT(256)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [sym__expression] = ACTIONS(SHIFT(255)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [sym__expression] = ACTIONS(SHIFT(254)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
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
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT] = ACTIONS(SHIFT(253)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_GT] = ACTIONS(SHIFT(253)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(247)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(247)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(252)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT] = ACTIONS(SHIFT(253)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_GT] = ACTIONS(SHIFT(253)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(247)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(247)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(252)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT] = ACTIONS(SHIFT(253)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_GT] = ACTIONS(SHIFT(253)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
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
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT] = ACTIONS(SHIFT(253)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_GT] = ACTIONS(SHIFT(253)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [259] = {
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
    [260] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(261)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(245)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(247)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(248)),
        [anon_sym_DOT] = ACTIONS(SHIFT(249)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(247)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(250)),
        [anon_sym_DASH] = ACTIONS(SHIFT(250)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(251)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(252)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT] = ACTIONS(SHIFT(253)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_GT] = ACTIONS(SHIFT(253)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [261] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [262] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(264)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(245)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(265)),
        [anon_sym_STAR] = ACTIONS(SHIFT(247)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(248)),
        [anon_sym_DOT] = ACTIONS(SHIFT(249)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(247)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(250)),
        [anon_sym_DASH] = ACTIONS(SHIFT(250)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(251)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(252)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT] = ACTIONS(SHIFT(253)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_GT] = ACTIONS(SHIFT(253)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
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
    [264] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(266)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [265] = {
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
    [266] = {
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
    [267] = {
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
    [268] = {
        [sym_block_statement] = ACTIONS(SHIFT(269)),
        [sym_if_statement] = ACTIONS(SHIFT(269)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(270)),
        [anon_sym_if] = ACTIONS(SHIFT(209)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [269] = {
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
    [270] = {
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
        [aux_sym_block_statement_repeat1] = ACTIONS(SHIFT(271)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(271)),
        [anon_sym_var] = ACTIONS(SHIFT(204)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(272)),
        [anon_sym_return] = ACTIONS(SHIFT(206)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(207)),
        [anon_sym_for] = ACTIONS(SHIFT(208)),
        [anon_sym_if] = ACTIONS(SHIFT(209)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(212)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [271] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(273)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [272] = {
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
    [273] = {
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
    [274] = {
        [anon_sym_COMMA] = ACTIONS(SHIFT(276)),
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(277)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [275] = {
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [276] = {
        [sym_var_name] = ACTIONS(SHIFT(281)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(282)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [277] = {
        [anon_sym_range] = ACTIONS(SHIFT(278)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [278] = {
        [sym__expression] = ACTIONS(SHIFT(279)),
        [sym_call_expression] = ACTIONS(SHIFT(216)),
        [sym_selector_expression] = ACTIONS(SHIFT(216)),
        [sym_math_op] = ACTIONS(SHIFT(216)),
        [sym_bool_op] = ACTIONS(SHIFT(216)),
        [sym_var_name] = ACTIONS(SHIFT(216)),
        [anon_sym_BANG] = ACTIONS(SHIFT(217)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(216)),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_number] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [279] = {
        [sym_block_statement] = ACTIONS(SHIFT(280)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(221)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(270)),
        [anon_sym_STAR] = ACTIONS(SHIFT(223)),
        [anon_sym_DOT] = ACTIONS(SHIFT(224)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(223)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(225)),
        [anon_sym_DASH] = ACTIONS(SHIFT(225)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(226)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(227)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT] = ACTIONS(SHIFT(228)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_GT] = ACTIONS(SHIFT(228)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [280] = {
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
    [281] = {
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(283)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [282] = {
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [283] = {
        [anon_sym_range] = ACTIONS(SHIFT(284)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [284] = {
        [sym__expression] = ACTIONS(SHIFT(285)),
        [sym_call_expression] = ACTIONS(SHIFT(216)),
        [sym_selector_expression] = ACTIONS(SHIFT(216)),
        [sym_math_op] = ACTIONS(SHIFT(216)),
        [sym_bool_op] = ACTIONS(SHIFT(216)),
        [sym_var_name] = ACTIONS(SHIFT(216)),
        [anon_sym_BANG] = ACTIONS(SHIFT(217)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(216)),
        [sym__identifier] = ACTIONS(SHIFT(218)),
        [sym_number] = ACTIONS(SHIFT(216)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [285] = {
        [sym_block_statement] = ACTIONS(SHIFT(286)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(221)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(270)),
        [anon_sym_STAR] = ACTIONS(SHIFT(223)),
        [anon_sym_DOT] = ACTIONS(SHIFT(224)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(223)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(225)),
        [anon_sym_DASH] = ACTIONS(SHIFT(225)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(226)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(227)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_LT] = ACTIONS(SHIFT(228)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(228)),
        [anon_sym_GT] = ACTIONS(SHIFT(228)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [286] = {
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
    [287] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(288)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(289)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(SHIFT(291)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(292)),
        [anon_sym_DASH] = ACTIONS(SHIFT(292)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(293)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(SHIFT(296)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [288] = {
        [sym__expression] = ACTIONS(SHIFT(303)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(304)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [289] = {
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
        [anon_sym_var] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_short_var_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [290] = {
        [sym__expression] = ACTIONS(SHIFT(301)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [291] = {
        [sym_var_name] = ACTIONS(SHIFT(302)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [292] = {
        [sym__expression] = ACTIONS(SHIFT(300)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [293] = {
        [sym__expression] = ACTIONS(SHIFT(299)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [294] = {
        [sym__expression] = ACTIONS(SHIFT(298)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [295] = {
        [sym__expression] = ACTIONS(SHIFT(297)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [296] = {
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
    [297] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [298] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [299] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [300] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [301] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [302] = {
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
    [303] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(305)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(245)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(306)),
        [anon_sym_STAR] = ACTIONS(SHIFT(247)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(248)),
        [anon_sym_DOT] = ACTIONS(SHIFT(249)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(247)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(250)),
        [anon_sym_DASH] = ACTIONS(SHIFT(250)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(251)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(252)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT] = ACTIONS(SHIFT(253)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_GT] = ACTIONS(SHIFT(253)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [304] = {
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
    [305] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(307)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [306] = {
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
    [307] = {
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
    [308] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(315)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(316)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(317)),
        [anon_sym_STAR] = ACTIONS(SHIFT(318)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(319)),
        [anon_sym_DOT] = ACTIONS(SHIFT(320)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(318)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(321)),
        [anon_sym_DASH] = ACTIONS(SHIFT(321)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(322)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(323)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT] = ACTIONS(SHIFT(324)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_GT] = ACTIONS(SHIFT(324)),
        [sym__line_break] = ACTIONS(SHIFT(325)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [309] = {
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
    [310] = {
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
    [311] = {
        [sym__expression] = ACTIONS(SHIFT(314)),
        [sym_call_expression] = ACTIONS(SHIFT(309)),
        [sym_selector_expression] = ACTIONS(SHIFT(309)),
        [sym_math_op] = ACTIONS(SHIFT(309)),
        [sym_bool_op] = ACTIONS(SHIFT(309)),
        [sym_var_name] = ACTIONS(SHIFT(309)),
        [anon_sym_BANG] = ACTIONS(SHIFT(311)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(309)),
        [sym__identifier] = ACTIONS(SHIFT(313)),
        [sym_number] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [312] = {
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
    [313] = {
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
    [314] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [sym__line_break] = ACTIONS(REDUCE(sym_bool_op, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [315] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(339)),
        [sym__line_break] = ACTIONS(SHIFT(340)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [316] = {
        [sym__expression] = ACTIONS(SHIFT(334)),
        [sym_call_expression] = ACTIONS(SHIFT(239)),
        [sym_selector_expression] = ACTIONS(SHIFT(239)),
        [sym_math_op] = ACTIONS(SHIFT(239)),
        [sym_bool_op] = ACTIONS(SHIFT(239)),
        [sym_var_name] = ACTIONS(SHIFT(239)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(335)),
        [anon_sym_BANG] = ACTIONS(SHIFT(241)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(239)),
        [sym__identifier] = ACTIONS(SHIFT(242)),
        [sym_number] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [317] = {
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
        [anon_sym_var] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym__identifier] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_return_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [318] = {
        [sym__expression] = ACTIONS(SHIFT(330)),
        [sym_call_expression] = ACTIONS(SHIFT(309)),
        [sym_selector_expression] = ACTIONS(SHIFT(309)),
        [sym_math_op] = ACTIONS(SHIFT(309)),
        [sym_bool_op] = ACTIONS(SHIFT(309)),
        [sym_var_name] = ACTIONS(SHIFT(309)),
        [anon_sym_BANG] = ACTIONS(SHIFT(311)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(309)),
        [sym__identifier] = ACTIONS(SHIFT(313)),
        [sym_number] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [319] = {
        [sym__expression] = ACTIONS(SHIFT(332)),
        [sym_call_expression] = ACTIONS(SHIFT(309)),
        [sym_selector_expression] = ACTIONS(SHIFT(309)),
        [sym_math_op] = ACTIONS(SHIFT(309)),
        [sym_bool_op] = ACTIONS(SHIFT(309)),
        [sym_var_name] = ACTIONS(SHIFT(309)),
        [anon_sym_BANG] = ACTIONS(SHIFT(311)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(309)),
        [sym__identifier] = ACTIONS(SHIFT(313)),
        [sym_number] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [320] = {
        [sym_var_name] = ACTIONS(SHIFT(331)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(313)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [321] = {
        [sym__expression] = ACTIONS(SHIFT(329)),
        [sym_call_expression] = ACTIONS(SHIFT(309)),
        [sym_selector_expression] = ACTIONS(SHIFT(309)),
        [sym_math_op] = ACTIONS(SHIFT(309)),
        [sym_bool_op] = ACTIONS(SHIFT(309)),
        [sym_var_name] = ACTIONS(SHIFT(309)),
        [anon_sym_BANG] = ACTIONS(SHIFT(311)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(309)),
        [sym__identifier] = ACTIONS(SHIFT(313)),
        [sym_number] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [322] = {
        [sym__expression] = ACTIONS(SHIFT(328)),
        [sym_call_expression] = ACTIONS(SHIFT(309)),
        [sym_selector_expression] = ACTIONS(SHIFT(309)),
        [sym_math_op] = ACTIONS(SHIFT(309)),
        [sym_bool_op] = ACTIONS(SHIFT(309)),
        [sym_var_name] = ACTIONS(SHIFT(309)),
        [anon_sym_BANG] = ACTIONS(SHIFT(311)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(309)),
        [sym__identifier] = ACTIONS(SHIFT(313)),
        [sym_number] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [323] = {
        [sym__expression] = ACTIONS(SHIFT(327)),
        [sym_call_expression] = ACTIONS(SHIFT(309)),
        [sym_selector_expression] = ACTIONS(SHIFT(309)),
        [sym_math_op] = ACTIONS(SHIFT(309)),
        [sym_bool_op] = ACTIONS(SHIFT(309)),
        [sym_var_name] = ACTIONS(SHIFT(309)),
        [anon_sym_BANG] = ACTIONS(SHIFT(311)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(309)),
        [sym__identifier] = ACTIONS(SHIFT(313)),
        [sym_number] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [324] = {
        [sym__expression] = ACTIONS(SHIFT(326)),
        [sym_call_expression] = ACTIONS(SHIFT(309)),
        [sym_selector_expression] = ACTIONS(SHIFT(309)),
        [sym_math_op] = ACTIONS(SHIFT(309)),
        [sym_bool_op] = ACTIONS(SHIFT(309)),
        [sym_var_name] = ACTIONS(SHIFT(309)),
        [anon_sym_BANG] = ACTIONS(SHIFT(311)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(309)),
        [sym__identifier] = ACTIONS(SHIFT(313)),
        [sym_number] = ACTIONS(SHIFT(309)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [325] = {
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
    [326] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_EQ_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LT_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_LT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_GT_EQ] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [anon_sym_GT] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [327] = {
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
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT] = ACTIONS(SHIFT(324)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_GT] = ACTIONS(SHIFT(324)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [328] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(318)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(318)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(323)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT] = ACTIONS(SHIFT(324)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_GT] = ACTIONS(SHIFT(324)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_bool_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [329] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(318)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DOT] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(318)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_DASH] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_PIPE_PIPE] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(323)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT] = ACTIONS(SHIFT(324)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_GT] = ACTIONS(SHIFT(324)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [330] = {
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
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT] = ACTIONS(SHIFT(324)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_GT] = ACTIONS(SHIFT(324)),
        [sym__line_break] = ACTIONS(REDUCE_FRAGILE(sym_math_op, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [331] = {
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
    [332] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(333)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(316)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(318)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(319)),
        [anon_sym_DOT] = ACTIONS(SHIFT(320)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(318)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(321)),
        [anon_sym_DASH] = ACTIONS(SHIFT(321)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(322)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(323)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_LT] = ACTIONS(SHIFT(324)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(324)),
        [anon_sym_GT] = ACTIONS(SHIFT(324)),
        [sym__line_break] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [333] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 3)),
        [sym__line_break] = ACTIONS(REDUCE(aux_sym_return_statement_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [334] = {
        [aux_sym_return_statement_repeat1] = ACTIONS(SHIFT(336)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(245)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(337)),
        [anon_sym_STAR] = ACTIONS(SHIFT(247)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(248)),
        [anon_sym_DOT] = ACTIONS(SHIFT(249)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(247)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(250)),
        [anon_sym_DASH] = ACTIONS(SHIFT(250)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(251)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(252)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_LT] = ACTIONS(SHIFT(253)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(253)),
        [anon_sym_GT] = ACTIONS(SHIFT(253)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [335] = {
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
    [336] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(338)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [337] = {
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
    [338] = {
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
    [339] = {
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
    [340] = {
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
    [341] = {
        [sym__type_expression] = ACTIONS(SHIFT(343)),
        [sym_pointer_type] = ACTIONS(SHIFT(344)),
        [sym_map_type] = ACTIONS(SHIFT(344)),
        [sym_slice_type] = ACTIONS(SHIFT(344)),
        [sym_struct_type] = ACTIONS(SHIFT(344)),
        [sym_interface_type] = ACTIONS(SHIFT(344)),
        [sym_type_name] = ACTIONS(SHIFT(344)),
        [anon_sym_EQ] = ACTIONS(SHIFT(345)),
        [anon_sym_STAR] = ACTIONS(SHIFT(346)),
        [anon_sym_map] = ACTIONS(SHIFT(347)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(348)),
        [anon_sym_struct] = ACTIONS(SHIFT(349)),
        [anon_sym_interface] = ACTIONS(SHIFT(350)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(351)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [342] = {
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
    [343] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(370)),
        [anon_sym_EQ] = ACTIONS(SHIFT(371)),
        [sym__line_break] = ACTIONS(SHIFT(372)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [344] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [345] = {
        [sym__expression] = ACTIONS(SHIFT(367)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [346] = {
        [sym__type_expression] = ACTIONS(SHIFT(366)),
        [sym_pointer_type] = ACTIONS(SHIFT(344)),
        [sym_map_type] = ACTIONS(SHIFT(344)),
        [sym_slice_type] = ACTIONS(SHIFT(344)),
        [sym_struct_type] = ACTIONS(SHIFT(344)),
        [sym_interface_type] = ACTIONS(SHIFT(344)),
        [sym_type_name] = ACTIONS(SHIFT(344)),
        [anon_sym_STAR] = ACTIONS(SHIFT(346)),
        [anon_sym_map] = ACTIONS(SHIFT(347)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(348)),
        [anon_sym_struct] = ACTIONS(SHIFT(349)),
        [anon_sym_interface] = ACTIONS(SHIFT(350)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(351)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [347] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(362)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [348] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(360)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [349] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(356)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [350] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(352)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [351] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [352] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(353)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(354)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [353] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(355)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [354] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [355] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [356] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(357)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(358)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [357] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(359)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [358] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [359] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [360] = {
        [sym__type_expression] = ACTIONS(SHIFT(361)),
        [sym_pointer_type] = ACTIONS(SHIFT(344)),
        [sym_map_type] = ACTIONS(SHIFT(344)),
        [sym_slice_type] = ACTIONS(SHIFT(344)),
        [sym_struct_type] = ACTIONS(SHIFT(344)),
        [sym_interface_type] = ACTIONS(SHIFT(344)),
        [sym_type_name] = ACTIONS(SHIFT(344)),
        [anon_sym_STAR] = ACTIONS(SHIFT(346)),
        [anon_sym_map] = ACTIONS(SHIFT(347)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(348)),
        [anon_sym_struct] = ACTIONS(SHIFT(349)),
        [anon_sym_interface] = ACTIONS(SHIFT(350)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(351)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [361] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [362] = {
        [sym__type_expression] = ACTIONS(SHIFT(363)),
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
    [363] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(364)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [364] = {
        [sym__type_expression] = ACTIONS(SHIFT(365)),
        [sym_pointer_type] = ACTIONS(SHIFT(344)),
        [sym_map_type] = ACTIONS(SHIFT(344)),
        [sym_slice_type] = ACTIONS(SHIFT(344)),
        [sym_struct_type] = ACTIONS(SHIFT(344)),
        [sym_interface_type] = ACTIONS(SHIFT(344)),
        [sym_type_name] = ACTIONS(SHIFT(344)),
        [anon_sym_STAR] = ACTIONS(SHIFT(346)),
        [anon_sym_map] = ACTIONS(SHIFT(347)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(348)),
        [anon_sym_struct] = ACTIONS(SHIFT(349)),
        [anon_sym_interface] = ACTIONS(SHIFT(350)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(351)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [365] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_map_type, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym__line_break] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [366] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym__line_break] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [367] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(288)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(368)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(SHIFT(291)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(292)),
        [anon_sym_DASH] = ACTIONS(SHIFT(292)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(293)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(SHIFT(369)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [368] = {
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
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [369] = {
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
    [370] = {
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
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 4)),
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
    [371] = {
        [sym__expression] = ACTIONS(SHIFT(373)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [372] = {
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
    [373] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(288)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(374)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(SHIFT(291)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(292)),
        [anon_sym_DASH] = ACTIONS(SHIFT(292)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(293)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(SHIFT(375)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [374] = {
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
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym__identifier] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_number] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [375] = {
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
    [376] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_block_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [377] = {
        [anon_sym_COLON_EQ] = ACTIONS(SHIFT(386)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [378] = {
        [sym_var_name] = ACTIONS(SHIFT(383)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(384)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [379] = {
        [sym__expression] = ACTIONS(SHIFT(380)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [380] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(288)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(381)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(SHIFT(291)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(292)),
        [anon_sym_DASH] = ACTIONS(SHIFT(292)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(293)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(SHIFT(382)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [381] = {
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
        [anon_sym_var] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym__identifier] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_short_var_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [382] = {
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
    [383] = {
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(SHIFT(385)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(378)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [384] = {
        [aux_sym_short_var_declaration_repeat1] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_var_name, 1)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_var_name, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [385] = {
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(aux_sym_short_var_declaration_repeat1, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [386] = {
        [sym__expression] = ACTIONS(SHIFT(387)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [387] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(288)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(388)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(SHIFT(291)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(292)),
        [anon_sym_DASH] = ACTIONS(SHIFT(292)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(293)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(SHIFT(389)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [388] = {
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
        [anon_sym_var] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym__identifier] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_short_var_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [389] = {
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
    [390] = {
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
        [anon_sym_var] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_return] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_COLON_EQ] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_if] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_BANG] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [391] = {
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
    [392] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_block_statement_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [393] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_func_declaration, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [394] = {
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
    [395] = {
        [sym__type_expression] = ACTIONS(SHIFT(396)),
        [sym_pointer_type] = ACTIONS(SHIFT(344)),
        [sym_map_type] = ACTIONS(SHIFT(344)),
        [sym_slice_type] = ACTIONS(SHIFT(344)),
        [sym_struct_type] = ACTIONS(SHIFT(344)),
        [sym_interface_type] = ACTIONS(SHIFT(344)),
        [sym_type_name] = ACTIONS(SHIFT(344)),
        [anon_sym_EQ] = ACTIONS(SHIFT(397)),
        [anon_sym_STAR] = ACTIONS(SHIFT(346)),
        [anon_sym_map] = ACTIONS(SHIFT(347)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(348)),
        [anon_sym_struct] = ACTIONS(SHIFT(349)),
        [anon_sym_interface] = ACTIONS(SHIFT(350)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(351)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [396] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(401)),
        [anon_sym_EQ] = ACTIONS(SHIFT(402)),
        [sym__line_break] = ACTIONS(SHIFT(403)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [397] = {
        [sym__expression] = ACTIONS(SHIFT(398)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [398] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(288)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(399)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(SHIFT(291)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(292)),
        [anon_sym_DASH] = ACTIONS(SHIFT(292)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(293)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(SHIFT(400)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [399] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_var_declaration, 5)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [400] = {
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
    [401] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_var_declaration, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [402] = {
        [sym__expression] = ACTIONS(SHIFT(404)),
        [sym_call_expression] = ACTIONS(SHIFT(201)),
        [sym_selector_expression] = ACTIONS(SHIFT(201)),
        [sym_math_op] = ACTIONS(SHIFT(201)),
        [sym_bool_op] = ACTIONS(SHIFT(201)),
        [sym_var_name] = ACTIONS(SHIFT(211)),
        [anon_sym_BANG] = ACTIONS(SHIFT(210)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(211)),
        [sym__identifier] = ACTIONS(SHIFT(214)),
        [sym_number] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [403] = {
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
    [404] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(288)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(405)),
        [anon_sym_STAR] = ACTIONS(SHIFT(290)),
        [anon_sym_DOT] = ACTIONS(SHIFT(291)),
        [anon_sym_SLASH] = ACTIONS(SHIFT(290)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(292)),
        [anon_sym_DASH] = ACTIONS(SHIFT(292)),
        [anon_sym_PIPE_PIPE] = ACTIONS(SHIFT(293)),
        [anon_sym_AMP_AMP] = ACTIONS(SHIFT(294)),
        [anon_sym_EQ_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_LT] = ACTIONS(SHIFT(295)),
        [anon_sym_GT_EQ] = ACTIONS(SHIFT(295)),
        [anon_sym_GT] = ACTIONS(SHIFT(295)),
        [sym__line_break] = ACTIONS(SHIFT(406)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [405] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_var_declaration, 6)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [406] = {
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
    [407] = {
        [sym__type_expression] = ACTIONS(SHIFT(409)),
        [sym_pointer_type] = ACTIONS(SHIFT(410)),
        [sym_map_type] = ACTIONS(SHIFT(410)),
        [sym_slice_type] = ACTIONS(SHIFT(410)),
        [sym_struct_type] = ACTIONS(SHIFT(410)),
        [sym_interface_type] = ACTIONS(SHIFT(410)),
        [sym_type_name] = ACTIONS(SHIFT(410)),
        [anon_sym_STAR] = ACTIONS(SHIFT(411)),
        [anon_sym_map] = ACTIONS(SHIFT(412)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(413)),
        [anon_sym_struct] = ACTIONS(SHIFT(414)),
        [anon_sym_interface] = ACTIONS(SHIFT(415)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(416)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [408] = {
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
    [409] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(432)),
        [sym__line_break] = ACTIONS(SHIFT(433)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [410] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym__type_expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [411] = {
        [sym__type_expression] = ACTIONS(SHIFT(431)),
        [sym_pointer_type] = ACTIONS(SHIFT(410)),
        [sym_map_type] = ACTIONS(SHIFT(410)),
        [sym_slice_type] = ACTIONS(SHIFT(410)),
        [sym_struct_type] = ACTIONS(SHIFT(410)),
        [sym_interface_type] = ACTIONS(SHIFT(410)),
        [sym_type_name] = ACTIONS(SHIFT(410)),
        [anon_sym_STAR] = ACTIONS(SHIFT(411)),
        [anon_sym_map] = ACTIONS(SHIFT(412)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(413)),
        [anon_sym_struct] = ACTIONS(SHIFT(414)),
        [anon_sym_interface] = ACTIONS(SHIFT(415)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(416)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [412] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(427)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [413] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(425)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [414] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(421)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [415] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(417)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [416] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym__line_break] = ACTIONS(REDUCE(sym_type_name, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [417] = {
        [sym_var_name] = ACTIONS(SHIFT(57)),
        [aux_sym_interface_type_repeat1] = ACTIONS(SHIFT(418)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(419)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [418] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(420)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [419] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [420] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_interface_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [421] = {
        [sym_var_name] = ACTIONS(SHIFT(112)),
        [aux_sym_struct_type_repeat1] = ACTIONS(SHIFT(422)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(423)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [422] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(424)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [423] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [424] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym__line_break] = ACTIONS(REDUCE(sym_struct_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [425] = {
        [sym__type_expression] = ACTIONS(SHIFT(426)),
        [sym_pointer_type] = ACTIONS(SHIFT(410)),
        [sym_map_type] = ACTIONS(SHIFT(410)),
        [sym_slice_type] = ACTIONS(SHIFT(410)),
        [sym_struct_type] = ACTIONS(SHIFT(410)),
        [sym_interface_type] = ACTIONS(SHIFT(410)),
        [sym_type_name] = ACTIONS(SHIFT(410)),
        [anon_sym_STAR] = ACTIONS(SHIFT(411)),
        [anon_sym_map] = ACTIONS(SHIFT(412)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(413)),
        [anon_sym_struct] = ACTIONS(SHIFT(414)),
        [anon_sym_interface] = ACTIONS(SHIFT(415)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(416)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [426] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym__line_break] = ACTIONS(REDUCE(sym_slice_type, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [427] = {
        [sym__type_expression] = ACTIONS(SHIFT(428)),
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
    [428] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(429)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [429] = {
        [sym__type_expression] = ACTIONS(SHIFT(430)),
        [sym_pointer_type] = ACTIONS(SHIFT(410)),
        [sym_map_type] = ACTIONS(SHIFT(410)),
        [sym_slice_type] = ACTIONS(SHIFT(410)),
        [sym_struct_type] = ACTIONS(SHIFT(410)),
        [sym_interface_type] = ACTIONS(SHIFT(410)),
        [sym_type_name] = ACTIONS(SHIFT(410)),
        [anon_sym_STAR] = ACTIONS(SHIFT(411)),
        [anon_sym_map] = ACTIONS(SHIFT(412)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(413)),
        [anon_sym_struct] = ACTIONS(SHIFT(414)),
        [anon_sym_interface] = ACTIONS(SHIFT(415)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym__identifier] = ACTIONS(SHIFT(416)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [430] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym__line_break] = ACTIONS(REDUCE(sym_map_type, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [431] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym__line_break] = ACTIONS(REDUCE(sym_pointer_type, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [432] = {
        [sym__declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym_type_declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym_var_declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym_func_declaration] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [aux_sym_program_repeat2] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [anon_sym_type] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [anon_sym_var] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [anon_sym_func] = ACTIONS(REDUCE(sym_type_declaration, 4)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [433] = {
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
    [434] = {
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
    [435] = {
        [sym_package_import] = ACTIONS(SHIFT(437)),
        [aux_sym_imports_block_repeat1] = ACTIONS(SHIFT(438)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(438)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(439)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(440)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [436] = {
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
    [437] = {
        [sym_package_import] = ACTIONS(SHIFT(437)),
        [aux_sym_imports_block_repeat1] = ACTIONS(SHIFT(442)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_imports_block_repeat1, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(SHIFT(440)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [438] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(441)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [439] = {
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
    [440] = {
        [sym_package_import] = ACTIONS(REDUCE(sym_package_import, 1)),
        [aux_sym_imports_block_repeat1] = ACTIONS(REDUCE(sym_package_import, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_string] = ACTIONS(REDUCE(sym_package_import, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [441] = {
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
    [442] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_imports_block_repeat1, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [443] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_program, 3)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [444] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_program_repeat2, 2)),
        [sym__line_break] = ACTIONS(SHIFT_EXTRA()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [445] = {
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
