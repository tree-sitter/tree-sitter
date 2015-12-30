#include "tree_sitter/parser.h"

#define STATE_COUNT 445
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
    [sym_program] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_package_directive] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_imports_block] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_package_import] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__declaration] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_type_declaration] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_var_declaration] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_func_declaration] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_block_statement] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__type_expression] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_pointer_type] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_map_type] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_slice_type] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_struct_type] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_interface_type] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__statement] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_return_statement] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_short_var_declaration] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_range_statement] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_if_statement] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_expression_statement] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__expression] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_call_expression] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_selector_expression] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_math_op] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_bool_op] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__func_signature] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_package_name] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_var_name] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_type_name] = {.visible = true, .named = true, .structural = true, .extra = false},
    [aux_sym_program_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_program_repeat2] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_imports_block_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_block_statement_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_struct_type_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_interface_type_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_return_statement_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_short_var_declaration_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym__func_signature_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym__func_signature_repeat2] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym__func_signature_repeat3] = {.visible = false, .named = false, .structural = true, .extra = false},
    [ts_builtin_sym_error] = {.visible = true, .named = true, .structural = true, .extra = false},
    [ts_builtin_sym_end] = {.visible = false, .named = false, .structural = true, .extra = false},
    [anon_sym_package] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_import] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LPAREN] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_RPAREN] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_type] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_SEMI] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_var] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_EQ] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_func] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LBRACE] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_RBRACE] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_STAR] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_map] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LBRACK] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_RBRACK] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_struct] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_interface] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_return] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_COMMA] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_COLON_EQ] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_for] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_range] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_if] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_else] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_DOT] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_SLASH] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_PLUS] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_DASH] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_PIPE_PIPE] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_AMP_AMP] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_EQ_EQ] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LT_EQ] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LT] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_GT_EQ] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_GT] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_BANG] = {.visible = true, .named = false, .structural = true, .extra = false},
    [sym__line_break] = {.visible = false, .named = false, .structural = true, .extra = true},
    [sym_string] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__identifier] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_number] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_comment] = {.visible = true, .named = true, .structural = false, .extra = true},
};

static TSTree *ts_lex(TSLexer *lexer, TSStateId state, bool error_mode) {
    START_LEXER();
    switch (state) {
        case 0:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(0);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '&')
                ADVANCE(8);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(11);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '+')
                ADVANCE(13);
            if (lookahead == ',')
                ADVANCE(14);
            if (lookahead == '-')
                ADVANCE(15);
            if (lookahead == '.')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (lookahead == ':')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '<')
                ADVANCE(25);
            if (lookahead == '=')
                ADVANCE(27);
            if (lookahead == '>')
                ADVANCE(29);
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
                ADVANCE(31);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == ']')
                ADVANCE(33);
            if (lookahead == 'e')
                ADVANCE(34);
            if (lookahead == 'f')
                ADVANCE(38);
            if (lookahead == 'i')
                ADVANCE(44);
            if (lookahead == 'm')
                ADVANCE(59);
            if (lookahead == 'p')
                ADVANCE(62);
            if (lookahead == 'r')
                ADVANCE(69);
            if (lookahead == 's')
                ADVANCE(79);
            if (lookahead == 't')
                ADVANCE(85);
            if (lookahead == 'v')
                ADVANCE(89);
            if (lookahead == '{')
                ADVANCE(92);
            if (lookahead == '|')
                ADVANCE(93);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            ACCEPT_TOKEN(sym__line_break);
        case 3:
            ACCEPT_TOKEN(anon_sym_BANG);
        case 4:
            if (lookahead == '\"')
                ADVANCE(5);
            if (lookahead == '\\')
                ADVANCE(6);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(4);
            LEX_ERROR();
        case 5:
            ACCEPT_TOKEN(sym_string);
        case 6:
            if (lookahead == '\"')
                ADVANCE(7);
            if (lookahead == '\\')
                ADVANCE(6);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(4);
            LEX_ERROR();
        case 7:
            if (lookahead == '\"')
                ADVANCE(5);
            if (lookahead == '\\')
                ADVANCE(6);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(4);
            ACCEPT_TOKEN(sym_string);
        case 8:
            if (lookahead == '&')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            ACCEPT_TOKEN(anon_sym_AMP_AMP);
        case 10:
            ACCEPT_TOKEN(anon_sym_LPAREN);
        case 11:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 12:
            ACCEPT_TOKEN(anon_sym_STAR);
        case 13:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 14:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 15:
            ACCEPT_TOKEN(anon_sym_DASH);
        case 16:
            ACCEPT_TOKEN(anon_sym_DOT);
        case 17:
            if (lookahead == '/')
                ADVANCE(18);
            ACCEPT_TOKEN(anon_sym_SLASH);
        case 18:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(18);
            ACCEPT_TOKEN(sym_comment);
        case 19:
            if (lookahead == '.')
                ADVANCE(20);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            ACCEPT_TOKEN(sym_number);
        case 20:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(21);
            ACCEPT_TOKEN(sym_number);
        case 22:
            if (lookahead == '=')
                ADVANCE(23);
            LEX_ERROR();
        case 23:
            ACCEPT_TOKEN(anon_sym_COLON_EQ);
        case 24:
            ACCEPT_TOKEN(anon_sym_SEMI);
        case 25:
            if (lookahead == '=')
                ADVANCE(26);
            ACCEPT_TOKEN(anon_sym_LT);
        case 26:
            ACCEPT_TOKEN(anon_sym_LT_EQ);
        case 27:
            if (lookahead == '=')
                ADVANCE(28);
            ACCEPT_TOKEN(anon_sym_EQ);
        case 28:
            ACCEPT_TOKEN(anon_sym_EQ_EQ);
        case 29:
            if (lookahead == '=')
                ADVANCE(30);
            ACCEPT_TOKEN(anon_sym_GT);
        case 30:
            ACCEPT_TOKEN(anon_sym_GT_EQ);
        case 31:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 32:
            ACCEPT_TOKEN(anon_sym_LBRACK);
        case 33:
            ACCEPT_TOKEN(anon_sym_RBRACK);
        case 34:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'l')
                ADVANCE(35);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 35:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 's')
                ADVANCE(36);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 36:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(37);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 37:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_else);
        case 38:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'o')
                ADVANCE(39);
            if (lookahead == 'u')
                ADVANCE(41);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 39:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(40);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 40:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_for);
        case 41:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(42);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 42:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'c')
                ADVANCE(43);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 43:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_func);
        case 44:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'l') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(45);
            if (lookahead == 'm')
                ADVANCE(46);
            if (lookahead == 'n')
                ADVANCE(51);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 45:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_if);
        case 46:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'p')
                ADVANCE(47);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'o')
                ADVANCE(48);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(49);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 't')
                ADVANCE(50);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_import);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 't')
                ADVANCE(52);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(53);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(54);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(55);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
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
                ADVANCE(31);
            if (lookahead == 'c')
                ADVANCE(57);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(58);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_interface);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'a')
                ADVANCE(60);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'p')
                ADVANCE(61);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_map);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'a')
                ADVANCE(63);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'c')
                ADVANCE(64);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'j') ||
                ('l' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'k')
                ADVANCE(65);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'a')
                ADVANCE(66);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'g')
                ADVANCE(67);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(68);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_package);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'a')
                ADVANCE(70);
            if (lookahead == 'e')
                ADVANCE(74);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(71);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 71:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'g')
                ADVANCE(72);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 72:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(73);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 73:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_range);
        case 74:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 't')
                ADVANCE(75);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 75:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'u')
                ADVANCE(76);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 76:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(77);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 77:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(78);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 78:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_return);
        case 79:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 't')
                ADVANCE(80);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 80:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(81);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 81:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'u')
                ADVANCE(82);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 82:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'c')
                ADVANCE(83);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 83:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 't')
                ADVANCE(84);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 84:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_struct);
        case 85:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(31);
            if (lookahead == 'y')
                ADVANCE(86);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 86:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'p')
                ADVANCE(87);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 87:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(88);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 88:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_type);
        case 89:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'a')
                ADVANCE(90);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(91);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            ACCEPT_TOKEN(anon_sym_var);
        case 92:
            ACCEPT_TOKEN(anon_sym_LBRACE);
        case 93:
            if (lookahead == '|')
                ADVANCE(94);
            LEX_ERROR();
        case 94:
            ACCEPT_TOKEN(anon_sym_PIPE_PIPE);
        case 95:
            ACCEPT_TOKEN(anon_sym_RBRACE);
        case 96:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == 'p')
                ADVANCE(98);
            LEX_ERROR();
        case 97:
            if (lookahead == '/')
                ADVANCE(18);
            LEX_ERROR();
        case 98:
            if (lookahead == 'a')
                ADVANCE(99);
            LEX_ERROR();
        case 99:
            if (lookahead == 'c')
                ADVANCE(100);
            LEX_ERROR();
        case 100:
            if (lookahead == 'k')
                ADVANCE(101);
            LEX_ERROR();
        case 101:
            if (lookahead == 'a')
                ADVANCE(102);
            LEX_ERROR();
        case 102:
            if (lookahead == 'g')
                ADVANCE(103);
            LEX_ERROR();
        case 103:
            if (lookahead == 'e')
                ADVANCE(104);
            LEX_ERROR();
        case 104:
            ACCEPT_TOKEN(anon_sym_package);
        case 105:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(105);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            LEX_ERROR();
        case 106:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(106);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == 'f')
                ADVANCE(107);
            if (lookahead == 'i')
                ADVANCE(111);
            if (lookahead == 't')
                ADVANCE(117);
            if (lookahead == 'v')
                ADVANCE(121);
            LEX_ERROR();
        case 107:
            if (lookahead == 'u')
                ADVANCE(108);
            LEX_ERROR();
        case 108:
            if (lookahead == 'n')
                ADVANCE(109);
            LEX_ERROR();
        case 109:
            if (lookahead == 'c')
                ADVANCE(110);
            LEX_ERROR();
        case 110:
            ACCEPT_TOKEN(anon_sym_func);
        case 111:
            if (lookahead == 'm')
                ADVANCE(112);
            LEX_ERROR();
        case 112:
            if (lookahead == 'p')
                ADVANCE(113);
            LEX_ERROR();
        case 113:
            if (lookahead == 'o')
                ADVANCE(114);
            LEX_ERROR();
        case 114:
            if (lookahead == 'r')
                ADVANCE(115);
            LEX_ERROR();
        case 115:
            if (lookahead == 't')
                ADVANCE(116);
            LEX_ERROR();
        case 116:
            ACCEPT_TOKEN(anon_sym_import);
        case 117:
            if (lookahead == 'y')
                ADVANCE(118);
            LEX_ERROR();
        case 118:
            if (lookahead == 'p')
                ADVANCE(119);
            LEX_ERROR();
        case 119:
            if (lookahead == 'e')
                ADVANCE(120);
            LEX_ERROR();
        case 120:
            ACCEPT_TOKEN(anon_sym_type);
        case 121:
            if (lookahead == 'a')
                ADVANCE(122);
            LEX_ERROR();
        case 122:
            if (lookahead == 'r')
                ADVANCE(123);
            LEX_ERROR();
        case 123:
            ACCEPT_TOKEN(anon_sym_var);
        case 124:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(124);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            LEX_ERROR();
        case 125:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == 'f')
                ADVANCE(107);
            if (lookahead == 't')
                ADVANCE(117);
            if (lookahead == 'v')
                ADVANCE(121);
            LEX_ERROR();
        case 126:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(97);
            LEX_ERROR();
        case 127:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(127);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(97);
            LEX_ERROR();
        case 128:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 129:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(97);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            LEX_ERROR();
        case 130:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(130);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == ',')
                ADVANCE(14);
            if (lookahead == '/')
                ADVANCE(97);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == 'i')
                ADVANCE(131);
            if (lookahead == 'm')
                ADVANCE(59);
            if (lookahead == 's')
                ADVANCE(79);
            LEX_ERROR();
        case 131:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'n')
                ADVANCE(51);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 132:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(97);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(11);
            if (lookahead == ',')
                ADVANCE(14);
            if (lookahead == '/')
                ADVANCE(97);
            LEX_ERROR();
        case 134:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(11);
            if (lookahead == ',')
                ADVANCE(14);
            if (lookahead == '/')
                ADVANCE(97);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            LEX_ERROR();
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ')')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(97);
            LEX_ERROR();
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '/')
                ADVANCE(97);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == 'i')
                ADVANCE(131);
            if (lookahead == 'm')
                ADVANCE(59);
            if (lookahead == 's')
                ADVANCE(79);
            LEX_ERROR();
        case 137:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == '[')
                ADVANCE(32);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == ']')
                ADVANCE(33);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '/')
                ADVANCE(97);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == ';')
                ADVANCE(24);
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
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(97);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (lookahead == ':')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(144);
            if (lookahead == 'i')
                ADVANCE(145);
            if (lookahead == 'r')
                ADVANCE(146);
            if (lookahead == 'v')
                ADVANCE(89);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 144:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'o')
                ADVANCE(39);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 145:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(45);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 146:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(74);
            ACCEPT_FRAGILE_TOKEN(sym__identifier);
        case 147:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(147);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(8);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '+')
                ADVANCE(13);
            if (lookahead == '-')
                ADVANCE(15);
            if (lookahead == '.')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '<')
                ADVANCE(25);
            if (lookahead == '=')
                ADVANCE(148);
            if (lookahead == '>')
                ADVANCE(29);
            if (lookahead == '|')
                ADVANCE(93);
            LEX_ERROR();
        case 148:
            if (lookahead == '=')
                ADVANCE(28);
            LEX_ERROR();
        case 149:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(149);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(8);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '+')
                ADVANCE(13);
            if (lookahead == ',')
                ADVANCE(14);
            if (lookahead == '-')
                ADVANCE(15);
            if (lookahead == '.')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if (lookahead == ':')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '<')
                ADVANCE(25);
            if (lookahead == '=')
                ADVANCE(148);
            if (lookahead == '>')
                ADVANCE(29);
            if (lookahead == '|')
                ADVANCE(93);
            LEX_ERROR();
        case 150:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(150);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(97);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (lookahead == ';')
                ADVANCE(24);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            LEX_ERROR();
        case 151:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(151);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(97);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            LEX_ERROR();
        case 152:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(152);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(8);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '+')
                ADVANCE(13);
            if (lookahead == '-')
                ADVANCE(15);
            if (lookahead == '.')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if (lookahead == '<')
                ADVANCE(25);
            if (lookahead == '=')
                ADVANCE(148);
            if (lookahead == '>')
                ADVANCE(29);
            if (lookahead == '{')
                ADVANCE(92);
            if (lookahead == '|')
                ADVANCE(93);
            LEX_ERROR();
        case 153:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(153);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(97);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (lookahead == ':')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'e')
                ADVANCE(34);
            if (lookahead == 'f')
                ADVANCE(144);
            if (lookahead == 'i')
                ADVANCE(145);
            if (lookahead == 'r')
                ADVANCE(146);
            if (lookahead == 'v')
                ADVANCE(89);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 154:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(154);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == ')')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(97);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            LEX_ERROR();
        case 155:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(155);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(8);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == ')')
                ADVANCE(11);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '+')
                ADVANCE(13);
            if (lookahead == ',')
                ADVANCE(14);
            if (lookahead == '-')
                ADVANCE(15);
            if (lookahead == '.')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if (lookahead == '<')
                ADVANCE(25);
            if (lookahead == '=')
                ADVANCE(148);
            if (lookahead == '>')
                ADVANCE(29);
            if (lookahead == '|')
                ADVANCE(93);
            LEX_ERROR();
        case 156:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(156);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == 'i')
                ADVANCE(157);
            if (lookahead == '{')
                ADVANCE(92);
            LEX_ERROR();
        case 157:
            if (lookahead == 'f')
                ADVANCE(158);
            LEX_ERROR();
        case 158:
            ACCEPT_TOKEN(anon_sym_if);
        case 159:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(14);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == ':')
                ADVANCE(22);
            LEX_ERROR();
        case 160:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(160);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == 'r')
                ADVANCE(161);
            LEX_ERROR();
        case 161:
            if (lookahead == 'a')
                ADVANCE(162);
            LEX_ERROR();
        case 162:
            if (lookahead == 'n')
                ADVANCE(163);
            LEX_ERROR();
        case 163:
            if (lookahead == 'g')
                ADVANCE(164);
            LEX_ERROR();
        case 164:
            if (lookahead == 'e')
                ADVANCE(165);
            LEX_ERROR();
        case 165:
            ACCEPT_TOKEN(anon_sym_range);
        case 166:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(166);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == ':')
                ADVANCE(22);
            LEX_ERROR();
        case 167:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(167);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '&')
                ADVANCE(8);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '+')
                ADVANCE(13);
            if (lookahead == '-')
                ADVANCE(15);
            if (lookahead == '.')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (lookahead == ':')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '<')
                ADVANCE(25);
            if (lookahead == '=')
                ADVANCE(148);
            if (lookahead == '>')
                ADVANCE(29);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(144);
            if (lookahead == 'i')
                ADVANCE(145);
            if (lookahead == 'r')
                ADVANCE(146);
            if (lookahead == 'v')
                ADVANCE(89);
            if (lookahead == '|')
                ADVANCE(93);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 168:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(168);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(8);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '+')
                ADVANCE(13);
            if (lookahead == ',')
                ADVANCE(14);
            if (lookahead == '-')
                ADVANCE(15);
            if (lookahead == '.')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '<')
                ADVANCE(25);
            if (lookahead == '=')
                ADVANCE(148);
            if (lookahead == '>')
                ADVANCE(29);
            if (lookahead == '|')
                ADVANCE(93);
            LEX_ERROR();
        case 169:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(169);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(97);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (lookahead == ':')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(24);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(144);
            if (lookahead == 'i')
                ADVANCE(145);
            if (lookahead == 'r')
                ADVANCE(146);
            if (lookahead == 'v')
                ADVANCE(89);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 170:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(170);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '&')
                ADVANCE(8);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '+')
                ADVANCE(13);
            if (lookahead == ',')
                ADVANCE(14);
            if (lookahead == '-')
                ADVANCE(15);
            if (lookahead == '.')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (lookahead == ':')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '<')
                ADVANCE(25);
            if (lookahead == '=')
                ADVANCE(148);
            if (lookahead == '>')
                ADVANCE(29);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(144);
            if (lookahead == 'i')
                ADVANCE(145);
            if (lookahead == 'r')
                ADVANCE(146);
            if (lookahead == 'v')
                ADVANCE(89);
            if (lookahead == '|')
                ADVANCE(93);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 171:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(171);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == '=')
                ADVANCE(172);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'l') ||
                ('n' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == '[')
                ADVANCE(32);
            if (lookahead == 'i')
                ADVANCE(131);
            if (lookahead == 'm')
                ADVANCE(59);
            if (lookahead == 's')
                ADVANCE(79);
            LEX_ERROR();
        case 172:
            ACCEPT_TOKEN(anon_sym_EQ);
        case 173:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(173);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '=')
                ADVANCE(172);
            LEX_ERROR();
        case 174:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(174);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '!')
                ADVANCE(3);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '/')
                ADVANCE(97);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(19);
            if (lookahead == ':')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '=')
                ADVANCE(172);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                (lookahead == 'g') ||
                (lookahead == 'h') ||
                ('j' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'u') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(31);
            if (lookahead == 'f')
                ADVANCE(144);
            if (lookahead == 'i')
                ADVANCE(145);
            if (lookahead == 'r')
                ADVANCE(146);
            if (lookahead == 'v')
                ADVANCE(89);
            if (lookahead == '}')
                ADVANCE(95);
            LEX_ERROR();
        case 175:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(175);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == 'f')
                ADVANCE(107);
            if (lookahead == 't')
                ADVANCE(117);
            if (lookahead == 'v')
                ADVANCE(121);
            LEX_ERROR();
        case 176:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(176);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '&')
                ADVANCE(8);
            if (lookahead == '(')
                ADVANCE(10);
            if (lookahead == '*')
                ADVANCE(12);
            if (lookahead == '+')
                ADVANCE(13);
            if (lookahead == '-')
                ADVANCE(15);
            if (lookahead == '.')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(17);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '<')
                ADVANCE(25);
            if (lookahead == '=')
                ADVANCE(148);
            if (lookahead == '>')
                ADVANCE(29);
            if (lookahead == 'f')
                ADVANCE(107);
            if (lookahead == 't')
                ADVANCE(117);
            if (lookahead == 'v')
                ADVANCE(121);
            if (lookahead == '|')
                ADVANCE(93);
            LEX_ERROR();
        case 177:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(177);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(97);
            if (lookahead == ';')
                ADVANCE(24);
            if (lookahead == '=')
                ADVANCE(172);
            if (lookahead == 'f')
                ADVANCE(107);
            if (lookahead == 't')
                ADVANCE(117);
            if (lookahead == 'v')
                ADVANCE(121);
            LEX_ERROR();
        case 178:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(178);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == ')')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(97);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 96,
    [1] = 105,
    [2] = 106,
    [3] = 124,
    [4] = 106,
    [5] = 106,
    [6] = 106,
    [7] = 125,
    [8] = 125,
    [9] = 125,
    [10] = 105,
    [11] = 126,
    [12] = 124,
    [13] = 124,
    [14] = 124,
    [15] = 127,
    [16] = 127,
    [17] = 128,
    [18] = 129,
    [19] = 130,
    [20] = 132,
    [21] = 130,
    [22] = 128,
    [23] = 124,
    [24] = 128,
    [25] = 124,
    [26] = 133,
    [27] = 134,
    [28] = 135,
    [29] = 128,
    [30] = 124,
    [31] = 133,
    [32] = 133,
    [33] = 135,
    [34] = 128,
    [35] = 133,
    [36] = 133,
    [37] = 135,
    [38] = 124,
    [39] = 124,
    [40] = 124,
    [41] = 133,
    [42] = 135,
    [43] = 128,
    [44] = 133,
    [45] = 133,
    [46] = 136,
    [47] = 136,
    [48] = 137,
    [49] = 138,
    [50] = 128,
    [51] = 128,
    [52] = 124,
    [53] = 133,
    [54] = 130,
    [55] = 136,
    [56] = 139,
    [57] = 127,
    [58] = 140,
    [59] = 133,
    [60] = 133,
    [61] = 139,
    [62] = 129,
    [63] = 130,
    [64] = 141,
    [65] = 139,
    [66] = 124,
    [67] = 124,
    [68] = 133,
    [69] = 135,
    [70] = 139,
    [71] = 139,
    [72] = 133,
    [73] = 135,
    [74] = 139,
    [75] = 133,
    [76] = 136,
    [77] = 133,
    [78] = 135,
    [79] = 141,
    [80] = 124,
    [81] = 130,
    [82] = 133,
    [83] = 136,
    [84] = 133,
    [85] = 135,
    [86] = 135,
    [87] = 124,
    [88] = 124,
    [89] = 133,
    [90] = 135,
    [91] = 139,
    [92] = 139,
    [93] = 133,
    [94] = 135,
    [95] = 139,
    [96] = 141,
    [97] = 124,
    [98] = 124,
    [99] = 133,
    [100] = 133,
    [101] = 135,
    [102] = 139,
    [103] = 135,
    [104] = 141,
    [105] = 124,
    [106] = 124,
    [107] = 133,
    [108] = 135,
    [109] = 133,
    [110] = 140,
    [111] = 139,
    [112] = 136,
    [113] = 140,
    [114] = 133,
    [115] = 136,
    [116] = 133,
    [117] = 139,
    [118] = 139,
    [119] = 136,
    [120] = 137,
    [121] = 138,
    [122] = 128,
    [123] = 128,
    [124] = 139,
    [125] = 139,
    [126] = 140,
    [127] = 139,
    [128] = 139,
    [129] = 139,
    [130] = 140,
    [131] = 139,
    [132] = 139,
    [133] = 136,
    [134] = 139,
    [135] = 136,
    [136] = 138,
    [137] = 138,
    [138] = 136,
    [139] = 137,
    [140] = 138,
    [141] = 128,
    [142] = 128,
    [143] = 138,
    [144] = 139,
    [145] = 140,
    [146] = 138,
    [147] = 138,
    [148] = 139,
    [149] = 140,
    [150] = 138,
    [151] = 138,
    [152] = 136,
    [153] = 138,
    [154] = 136,
    [155] = 138,
    [156] = 136,
    [157] = 138,
    [158] = 138,
    [159] = 136,
    [160] = 139,
    [161] = 139,
    [162] = 140,
    [163] = 136,
    [164] = 133,
    [165] = 136,
    [166] = 138,
    [167] = 136,
    [168] = 133,
    [169] = 133,
    [170] = 133,
    [171] = 135,
    [172] = 132,
    [173] = 124,
    [174] = 124,
    [175] = 133,
    [176] = 135,
    [177] = 128,
    [178] = 128,
    [179] = 133,
    [180] = 135,
    [181] = 128,
    [182] = 132,
    [183] = 124,
    [184] = 124,
    [185] = 133,
    [186] = 133,
    [187] = 135,
    [188] = 128,
    [189] = 135,
    [190] = 132,
    [191] = 124,
    [192] = 124,
    [193] = 133,
    [194] = 135,
    [195] = 133,
    [196] = 142,
    [197] = 143,
    [198] = 143,
    [199] = 143,
    [200] = 147,
    [201] = 147,
    [202] = 149,
    [203] = 140,
    [204] = 124,
    [205] = 142,
    [206] = 150,
    [207] = 151,
    [208] = 124,
    [209] = 151,
    [210] = 151,
    [211] = 149,
    [212] = 147,
    [213] = 147,
    [214] = 152,
    [215] = 152,
    [216] = 151,
    [217] = 152,
    [218] = 152,
    [219] = 153,
    [220] = 154,
    [221] = 143,
    [222] = 151,
    [223] = 124,
    [224] = 151,
    [225] = 151,
    [226] = 151,
    [227] = 151,
    [228] = 152,
    [229] = 152,
    [230] = 152,
    [231] = 152,
    [232] = 152,
    [233] = 152,
    [234] = 140,
    [235] = 153,
    [236] = 153,
    [237] = 155,
    [238] = 155,
    [239] = 152,
    [240] = 151,
    [241] = 155,
    [242] = 155,
    [243] = 135,
    [244] = 154,
    [245] = 152,
    [246] = 151,
    [247] = 151,
    [248] = 124,
    [249] = 151,
    [250] = 151,
    [251] = 151,
    [252] = 151,
    [253] = 155,
    [254] = 155,
    [255] = 155,
    [256] = 155,
    [257] = 155,
    [258] = 155,
    [259] = 155,
    [260] = 135,
    [261] = 155,
    [262] = 155,
    [263] = 135,
    [264] = 155,
    [265] = 155,
    [266] = 152,
    [267] = 156,
    [268] = 143,
    [269] = 143,
    [270] = 140,
    [271] = 143,
    [272] = 143,
    [273] = 159,
    [274] = 159,
    [275] = 124,
    [276] = 160,
    [277] = 151,
    [278] = 152,
    [279] = 143,
    [280] = 166,
    [281] = 166,
    [282] = 160,
    [283] = 151,
    [284] = 152,
    [285] = 143,
    [286] = 147,
    [287] = 154,
    [288] = 143,
    [289] = 151,
    [290] = 124,
    [291] = 151,
    [292] = 151,
    [293] = 151,
    [294] = 151,
    [295] = 167,
    [296] = 147,
    [297] = 147,
    [298] = 147,
    [299] = 147,
    [300] = 147,
    [301] = 147,
    [302] = 155,
    [303] = 147,
    [304] = 135,
    [305] = 147,
    [306] = 147,
    [307] = 168,
    [308] = 168,
    [309] = 143,
    [310] = 151,
    [311] = 169,
    [312] = 168,
    [313] = 168,
    [314] = 142,
    [315] = 154,
    [316] = 143,
    [317] = 151,
    [318] = 151,
    [319] = 124,
    [320] = 151,
    [321] = 151,
    [322] = 151,
    [323] = 151,
    [324] = 170,
    [325] = 168,
    [326] = 168,
    [327] = 168,
    [328] = 168,
    [329] = 168,
    [330] = 168,
    [331] = 168,
    [332] = 142,
    [333] = 155,
    [334] = 168,
    [335] = 135,
    [336] = 168,
    [337] = 168,
    [338] = 143,
    [339] = 169,
    [340] = 171,
    [341] = 171,
    [342] = 173,
    [343] = 173,
    [344] = 151,
    [345] = 136,
    [346] = 137,
    [347] = 138,
    [348] = 128,
    [349] = 128,
    [350] = 173,
    [351] = 139,
    [352] = 140,
    [353] = 173,
    [354] = 173,
    [355] = 139,
    [356] = 140,
    [357] = 173,
    [358] = 173,
    [359] = 136,
    [360] = 173,
    [361] = 136,
    [362] = 138,
    [363] = 136,
    [364] = 173,
    [365] = 173,
    [366] = 147,
    [367] = 143,
    [368] = 167,
    [369] = 143,
    [370] = 151,
    [371] = 174,
    [372] = 147,
    [373] = 143,
    [374] = 167,
    [375] = 142,
    [376] = 166,
    [377] = 124,
    [378] = 151,
    [379] = 147,
    [380] = 143,
    [381] = 167,
    [382] = 159,
    [383] = 159,
    [384] = 166,
    [385] = 151,
    [386] = 147,
    [387] = 143,
    [388] = 167,
    [389] = 143,
    [390] = 167,
    [391] = 140,
    [392] = 125,
    [393] = 175,
    [394] = 171,
    [395] = 173,
    [396] = 151,
    [397] = 147,
    [398] = 125,
    [399] = 176,
    [400] = 125,
    [401] = 151,
    [402] = 177,
    [403] = 147,
    [404] = 125,
    [405] = 176,
    [406] = 136,
    [407] = 136,
    [408] = 142,
    [409] = 142,
    [410] = 136,
    [411] = 137,
    [412] = 138,
    [413] = 128,
    [414] = 128,
    [415] = 142,
    [416] = 139,
    [417] = 140,
    [418] = 142,
    [419] = 142,
    [420] = 139,
    [421] = 140,
    [422] = 142,
    [423] = 142,
    [424] = 136,
    [425] = 142,
    [426] = 136,
    [427] = 138,
    [428] = 136,
    [429] = 142,
    [430] = 142,
    [431] = 125,
    [432] = 175,
    [433] = 106,
    [434] = 178,
    [435] = 106,
    [436] = 178,
    [437] = 135,
    [438] = 106,
    [439] = 178,
    [440] = 106,
    [441] = 135,
    [442] = 105,
    [443] = 105,
    [444] = 125,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static unsigned short ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_program] = 2,
        [sym_package_directive] = 4,
        [anon_sym_package] = 6,
        [sym__line_break] = 8,
        [sym_comment] = 8,
    },
    [1] = {
        [ts_builtin_sym_end] = 10,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [2] = {
        [sym_imports_block] = 14,
        [sym__declaration] = 16,
        [sym_type_declaration] = 18,
        [sym_var_declaration] = 18,
        [sym_func_declaration] = 18,
        [aux_sym_program_repeat1] = 20,
        [aux_sym_program_repeat2] = 22,
        [ts_builtin_sym_end] = 24,
        [anon_sym_import] = 26,
        [anon_sym_type] = 28,
        [anon_sym_var] = 30,
        [anon_sym_func] = 32,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [3] = {
        [sym_package_name] = 34,
        [sym__line_break] = 12,
        [sym__identifier] = 36,
        [sym_comment] = 12,
    },
    [4] = {
        [sym_imports_block] = 38,
        [sym__declaration] = 38,
        [sym_type_declaration] = 38,
        [sym_var_declaration] = 38,
        [sym_func_declaration] = 38,
        [aux_sym_program_repeat1] = 38,
        [aux_sym_program_repeat2] = 38,
        [ts_builtin_sym_end] = 38,
        [anon_sym_import] = 38,
        [anon_sym_type] = 38,
        [anon_sym_var] = 38,
        [anon_sym_func] = 38,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [5] = {
        [sym_imports_block] = 40,
        [sym__declaration] = 40,
        [sym_type_declaration] = 40,
        [sym_var_declaration] = 40,
        [sym_func_declaration] = 40,
        [aux_sym_program_repeat1] = 40,
        [aux_sym_program_repeat2] = 40,
        [ts_builtin_sym_end] = 40,
        [anon_sym_import] = 40,
        [anon_sym_type] = 40,
        [anon_sym_var] = 40,
        [anon_sym_func] = 40,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [6] = {
        [sym_imports_block] = 14,
        [sym__declaration] = 42,
        [sym_type_declaration] = 42,
        [sym_var_declaration] = 42,
        [sym_func_declaration] = 42,
        [aux_sym_program_repeat1] = 44,
        [aux_sym_program_repeat2] = 42,
        [ts_builtin_sym_end] = 42,
        [anon_sym_import] = 26,
        [anon_sym_type] = 42,
        [anon_sym_var] = 42,
        [anon_sym_func] = 42,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [7] = {
        [sym__declaration] = 16,
        [sym_type_declaration] = 18,
        [sym_var_declaration] = 18,
        [sym_func_declaration] = 18,
        [aux_sym_program_repeat2] = 46,
        [ts_builtin_sym_end] = 48,
        [anon_sym_type] = 28,
        [anon_sym_var] = 30,
        [anon_sym_func] = 32,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [8] = {
        [sym__declaration] = 50,
        [sym_type_declaration] = 50,
        [sym_var_declaration] = 50,
        [sym_func_declaration] = 50,
        [aux_sym_program_repeat2] = 50,
        [ts_builtin_sym_end] = 50,
        [anon_sym_type] = 50,
        [anon_sym_var] = 50,
        [anon_sym_func] = 50,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [9] = {
        [sym__declaration] = 16,
        [sym_type_declaration] = 18,
        [sym_var_declaration] = 18,
        [sym_func_declaration] = 18,
        [aux_sym_program_repeat2] = 52,
        [ts_builtin_sym_end] = 54,
        [anon_sym_type] = 28,
        [anon_sym_var] = 30,
        [anon_sym_func] = 32,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [10] = {
        [ts_builtin_sym_end] = 54,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [11] = {
        [sym_package_import] = 56,
        [anon_sym_LPAREN] = 58,
        [sym__line_break] = 12,
        [sym_string] = 60,
        [sym_comment] = 12,
    },
    [12] = {
        [sym_type_name] = 62,
        [sym__line_break] = 12,
        [sym__identifier] = 64,
        [sym_comment] = 12,
    },
    [13] = {
        [sym_var_name] = 66,
        [sym__line_break] = 12,
        [sym__identifier] = 68,
        [sym_comment] = 12,
    },
    [14] = {
        [sym_var_name] = 70,
        [sym__line_break] = 12,
        [sym__identifier] = 72,
        [sym_comment] = 12,
    },
    [15] = {
        [sym__func_signature] = 74,
        [anon_sym_LPAREN] = 76,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [16] = {
        [sym__func_signature] = 78,
        [anon_sym_LPAREN] = 78,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [17] = {
        [sym_block_statement] = 80,
        [anon_sym_LBRACE] = 82,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [18] = {
        [sym_var_name] = 84,
        [anon_sym_RPAREN] = 86,
        [sym__line_break] = 12,
        [sym__identifier] = 88,
        [sym_comment] = 12,
    },
    [19] = {
        [sym__type_expression] = 90,
        [sym_pointer_type] = 92,
        [sym_map_type] = 92,
        [sym_slice_type] = 92,
        [sym_struct_type] = 92,
        [sym_interface_type] = 92,
        [sym_type_name] = 92,
        [aux_sym_short_var_declaration_repeat1] = 94,
        [anon_sym_STAR] = 96,
        [anon_sym_map] = 98,
        [anon_sym_LBRACK] = 100,
        [anon_sym_struct] = 102,
        [anon_sym_interface] = 104,
        [anon_sym_COMMA] = 106,
        [sym__line_break] = 12,
        [sym__identifier] = 108,
        [sym_comment] = 12,
    },
    [20] = {
        [sym_block_statement] = 110,
        [sym_type_name] = 112,
        [anon_sym_LPAREN] = 114,
        [anon_sym_LBRACE] = 110,
        [sym__line_break] = 12,
        [sym__identifier] = 116,
        [sym_comment] = 12,
    },
    [21] = {
        [sym__type_expression] = 78,
        [sym_pointer_type] = 78,
        [sym_map_type] = 78,
        [sym_slice_type] = 78,
        [sym_struct_type] = 78,
        [sym_interface_type] = 78,
        [sym_type_name] = 78,
        [aux_sym_short_var_declaration_repeat1] = 78,
        [anon_sym_STAR] = 78,
        [anon_sym_map] = 78,
        [anon_sym_LBRACK] = 78,
        [anon_sym_struct] = 78,
        [anon_sym_interface] = 78,
        [anon_sym_COMMA] = 78,
        [sym__line_break] = 12,
        [sym__identifier] = 78,
        [sym_comment] = 12,
    },
    [22] = {
        [sym_block_statement] = 118,
        [anon_sym_LBRACE] = 118,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [23] = {
        [sym_var_name] = 120,
        [sym_type_name] = 122,
        [sym__line_break] = 12,
        [sym__identifier] = 124,
        [sym_comment] = 12,
    },
    [24] = {
        [sym_block_statement] = 126,
        [anon_sym_LBRACE] = 126,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [25] = {
        [sym_type_name] = 128,
        [sym__line_break] = 12,
        [sym__identifier] = 130,
        [sym_comment] = 12,
    },
    [26] = {
        [aux_sym__func_signature_repeat3] = 132,
        [anon_sym_RPAREN] = 134,
        [anon_sym_COMMA] = 136,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [27] = {
        [sym_type_name] = 78,
        [aux_sym__func_signature_repeat3] = 126,
        [anon_sym_RPAREN] = 126,
        [anon_sym_COMMA] = 126,
        [sym__line_break] = 12,
        [sym__identifier] = 78,
        [sym_comment] = 12,
    },
    [28] = {
        [anon_sym_RPAREN] = 138,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [29] = {
        [sym_block_statement] = 140,
        [anon_sym_LBRACE] = 140,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [30] = {
        [sym_type_name] = 142,
        [sym__line_break] = 12,
        [sym__identifier] = 144,
        [sym_comment] = 12,
    },
    [31] = {
        [aux_sym__func_signature_repeat3] = 146,
        [anon_sym_RPAREN] = 148,
        [anon_sym_COMMA] = 136,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [32] = {
        [aux_sym__func_signature_repeat3] = 126,
        [anon_sym_RPAREN] = 126,
        [anon_sym_COMMA] = 126,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [33] = {
        [anon_sym_RPAREN] = 150,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [34] = {
        [sym_block_statement] = 152,
        [anon_sym_LBRACE] = 152,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [35] = {
        [aux_sym__func_signature_repeat2] = 154,
        [anon_sym_RPAREN] = 138,
        [anon_sym_COMMA] = 156,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [36] = {
        [aux_sym__func_signature_repeat2] = 126,
        [anon_sym_RPAREN] = 126,
        [anon_sym_COMMA] = 126,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [37] = {
        [anon_sym_RPAREN] = 158,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [38] = {
        [sym_var_name] = 160,
        [sym__line_break] = 12,
        [sym__identifier] = 162,
        [sym_comment] = 12,
    },
    [39] = {
        [sym_type_name] = 164,
        [sym__line_break] = 12,
        [sym__identifier] = 130,
        [sym_comment] = 12,
    },
    [40] = {
        [sym_type_name] = 78,
        [sym__line_break] = 12,
        [sym__identifier] = 78,
        [sym_comment] = 12,
    },
    [41] = {
        [aux_sym__func_signature_repeat2] = 166,
        [anon_sym_RPAREN] = 168,
        [anon_sym_COMMA] = 156,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [42] = {
        [anon_sym_RPAREN] = 170,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [43] = {
        [sym_block_statement] = 172,
        [anon_sym_LBRACE] = 172,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [44] = {
        [aux_sym__func_signature_repeat1] = 174,
        [anon_sym_RPAREN] = 176,
        [anon_sym_COMMA] = 178,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [45] = {
        [aux_sym__func_signature_repeat1] = 180,
        [anon_sym_RPAREN] = 180,
        [anon_sym_COMMA] = 180,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [46] = {
        [sym__type_expression] = 182,
        [sym_pointer_type] = 92,
        [sym_map_type] = 92,
        [sym_slice_type] = 92,
        [sym_struct_type] = 92,
        [sym_interface_type] = 92,
        [sym_type_name] = 92,
        [anon_sym_STAR] = 96,
        [anon_sym_map] = 98,
        [anon_sym_LBRACK] = 100,
        [anon_sym_struct] = 102,
        [anon_sym_interface] = 104,
        [sym__line_break] = 12,
        [sym__identifier] = 108,
        [sym_comment] = 12,
    },
    [47] = {
        [sym__type_expression] = 184,
        [sym_pointer_type] = 92,
        [sym_map_type] = 92,
        [sym_slice_type] = 92,
        [sym_struct_type] = 92,
        [sym_interface_type] = 92,
        [sym_type_name] = 92,
        [anon_sym_STAR] = 96,
        [anon_sym_map] = 98,
        [anon_sym_LBRACK] = 100,
        [anon_sym_struct] = 102,
        [anon_sym_interface] = 104,
        [sym__line_break] = 12,
        [sym__identifier] = 108,
        [sym_comment] = 12,
    },
    [48] = {
        [anon_sym_LBRACK] = 186,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [49] = {
        [anon_sym_RBRACK] = 188,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [50] = {
        [anon_sym_LBRACE] = 190,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [51] = {
        [anon_sym_LBRACE] = 192,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [52] = {
        [sym_var_name] = 194,
        [sym__line_break] = 12,
        [sym__identifier] = 88,
        [sym_comment] = 12,
    },
    [53] = {
        [aux_sym__func_signature_repeat1] = 126,
        [anon_sym_RPAREN] = 126,
        [anon_sym_COMMA] = 126,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [54] = {
        [sym__type_expression] = 196,
        [sym_pointer_type] = 196,
        [sym_map_type] = 196,
        [sym_slice_type] = 196,
        [sym_struct_type] = 196,
        [sym_interface_type] = 196,
        [sym_type_name] = 196,
        [aux_sym_short_var_declaration_repeat1] = 198,
        [anon_sym_STAR] = 196,
        [anon_sym_map] = 196,
        [anon_sym_LBRACK] = 196,
        [anon_sym_struct] = 196,
        [anon_sym_interface] = 196,
        [anon_sym_COMMA] = 106,
        [sym__line_break] = 12,
        [sym__identifier] = 196,
        [sym_comment] = 12,
    },
    [55] = {
        [sym__type_expression] = 200,
        [sym_pointer_type] = 200,
        [sym_map_type] = 200,
        [sym_slice_type] = 200,
        [sym_struct_type] = 200,
        [sym_interface_type] = 200,
        [sym_type_name] = 200,
        [anon_sym_STAR] = 200,
        [anon_sym_map] = 200,
        [anon_sym_LBRACK] = 200,
        [anon_sym_struct] = 200,
        [anon_sym_interface] = 200,
        [sym__line_break] = 12,
        [sym__identifier] = 200,
        [sym_comment] = 12,
    },
    [56] = {
        [sym_var_name] = 202,
        [aux_sym_interface_type_repeat1] = 204,
        [anon_sym_RBRACE] = 206,
        [sym__line_break] = 12,
        [sym__identifier] = 72,
        [sym_comment] = 12,
    },
    [57] = {
        [sym__func_signature] = 208,
        [anon_sym_LPAREN] = 210,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [58] = {
        [anon_sym_RBRACE] = 212,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [59] = {
        [aux_sym__func_signature_repeat1] = 214,
        [anon_sym_RPAREN] = 214,
        [anon_sym_COMMA] = 214,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [60] = {
        [aux_sym__func_signature_repeat1] = 216,
        [anon_sym_RPAREN] = 216,
        [anon_sym_COMMA] = 216,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [61] = {
        [sym_var_name] = 202,
        [aux_sym_interface_type_repeat1] = 218,
        [anon_sym_RBRACE] = 220,
        [sym__line_break] = 12,
        [sym__identifier] = 72,
        [sym_comment] = 12,
    },
    [62] = {
        [sym_var_name] = 222,
        [anon_sym_RPAREN] = 224,
        [sym__line_break] = 12,
        [sym__identifier] = 88,
        [sym_comment] = 12,
    },
    [63] = {
        [sym__type_expression] = 226,
        [sym_pointer_type] = 92,
        [sym_map_type] = 92,
        [sym_slice_type] = 92,
        [sym_struct_type] = 92,
        [sym_interface_type] = 92,
        [sym_type_name] = 92,
        [aux_sym_short_var_declaration_repeat1] = 228,
        [anon_sym_STAR] = 96,
        [anon_sym_map] = 98,
        [anon_sym_LBRACK] = 100,
        [anon_sym_struct] = 102,
        [anon_sym_interface] = 104,
        [anon_sym_COMMA] = 106,
        [sym__line_break] = 12,
        [sym__identifier] = 108,
        [sym_comment] = 12,
    },
    [64] = {
        [sym_var_name] = 110,
        [sym_type_name] = 230,
        [aux_sym_interface_type_repeat1] = 110,
        [anon_sym_LPAREN] = 232,
        [anon_sym_RBRACE] = 110,
        [sym__line_break] = 12,
        [sym__identifier] = 110,
        [sym_comment] = 12,
    },
    [65] = {
        [sym_var_name] = 118,
        [aux_sym_interface_type_repeat1] = 118,
        [anon_sym_RBRACE] = 118,
        [sym__line_break] = 12,
        [sym__identifier] = 118,
        [sym_comment] = 12,
    },
    [66] = {
        [sym_var_name] = 234,
        [sym_type_name] = 236,
        [sym__line_break] = 12,
        [sym__identifier] = 124,
        [sym_comment] = 12,
    },
    [67] = {
        [sym_type_name] = 238,
        [sym__line_break] = 12,
        [sym__identifier] = 130,
        [sym_comment] = 12,
    },
    [68] = {
        [aux_sym__func_signature_repeat3] = 240,
        [anon_sym_RPAREN] = 242,
        [anon_sym_COMMA] = 136,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [69] = {
        [anon_sym_RPAREN] = 244,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [70] = {
        [sym_var_name] = 140,
        [aux_sym_interface_type_repeat1] = 140,
        [anon_sym_RBRACE] = 140,
        [sym__line_break] = 12,
        [sym__identifier] = 140,
        [sym_comment] = 12,
    },
    [71] = {
        [sym_var_name] = 152,
        [aux_sym_interface_type_repeat1] = 152,
        [anon_sym_RBRACE] = 152,
        [sym__line_break] = 12,
        [sym__identifier] = 152,
        [sym_comment] = 12,
    },
    [72] = {
        [aux_sym__func_signature_repeat2] = 246,
        [anon_sym_RPAREN] = 244,
        [anon_sym_COMMA] = 156,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [73] = {
        [anon_sym_RPAREN] = 248,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [74] = {
        [sym_var_name] = 172,
        [aux_sym_interface_type_repeat1] = 172,
        [anon_sym_RBRACE] = 172,
        [sym__line_break] = 12,
        [sym__identifier] = 172,
        [sym_comment] = 12,
    },
    [75] = {
        [aux_sym__func_signature_repeat1] = 250,
        [anon_sym_RPAREN] = 252,
        [anon_sym_COMMA] = 178,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [76] = {
        [sym__type_expression] = 254,
        [sym_pointer_type] = 92,
        [sym_map_type] = 92,
        [sym_slice_type] = 92,
        [sym_struct_type] = 92,
        [sym_interface_type] = 92,
        [sym_type_name] = 92,
        [anon_sym_STAR] = 96,
        [anon_sym_map] = 98,
        [anon_sym_LBRACK] = 100,
        [anon_sym_struct] = 102,
        [anon_sym_interface] = 104,
        [sym__line_break] = 12,
        [sym__identifier] = 108,
        [sym_comment] = 12,
    },
    [77] = {
        [aux_sym__func_signature_repeat1] = 256,
        [anon_sym_RPAREN] = 258,
        [anon_sym_COMMA] = 178,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [78] = {
        [anon_sym_RPAREN] = 260,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [79] = {
        [sym_var_name] = 140,
        [sym_type_name] = 244,
        [aux_sym_interface_type_repeat1] = 140,
        [anon_sym_LPAREN] = 262,
        [anon_sym_RBRACE] = 140,
        [sym__line_break] = 12,
        [sym__identifier] = 140,
        [sym_comment] = 12,
    },
    [80] = {
        [sym_var_name] = 264,
        [sym__line_break] = 12,
        [sym__identifier] = 88,
        [sym_comment] = 12,
    },
    [81] = {
        [sym__type_expression] = 266,
        [sym_pointer_type] = 92,
        [sym_map_type] = 92,
        [sym_slice_type] = 92,
        [sym_struct_type] = 92,
        [sym_interface_type] = 92,
        [sym_type_name] = 92,
        [aux_sym_short_var_declaration_repeat1] = 268,
        [anon_sym_STAR] = 96,
        [anon_sym_map] = 98,
        [anon_sym_LBRACK] = 100,
        [anon_sym_struct] = 102,
        [anon_sym_interface] = 104,
        [anon_sym_COMMA] = 106,
        [sym__line_break] = 12,
        [sym__identifier] = 108,
        [sym_comment] = 12,
    },
    [82] = {
        [aux_sym__func_signature_repeat1] = 270,
        [anon_sym_RPAREN] = 272,
        [anon_sym_COMMA] = 178,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [83] = {
        [sym__type_expression] = 274,
        [sym_pointer_type] = 92,
        [sym_map_type] = 92,
        [sym_slice_type] = 92,
        [sym_struct_type] = 92,
        [sym_interface_type] = 92,
        [sym_type_name] = 92,
        [anon_sym_STAR] = 96,
        [anon_sym_map] = 98,
        [anon_sym_LBRACK] = 100,
        [anon_sym_struct] = 102,
        [anon_sym_interface] = 104,
        [sym__line_break] = 12,
        [sym__identifier] = 108,
        [sym_comment] = 12,
    },
    [84] = {
        [aux_sym__func_signature_repeat1] = 276,
        [anon_sym_RPAREN] = 278,
        [anon_sym_COMMA] = 178,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [85] = {
        [anon_sym_RPAREN] = 280,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [86] = {
        [anon_sym_RPAREN] = 278,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [87] = {
        [sym_var_name] = 282,
        [sym_type_name] = 284,
        [sym__line_break] = 12,
        [sym__identifier] = 124,
        [sym_comment] = 12,
    },
    [88] = {
        [sym_type_name] = 286,
        [sym__line_break] = 12,
        [sym__identifier] = 130,
        [sym_comment] = 12,
    },
    [89] = {
        [aux_sym__func_signature_repeat3] = 288,
        [anon_sym_RPAREN] = 290,
        [anon_sym_COMMA] = 136,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [90] = {
        [anon_sym_RPAREN] = 292,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [91] = {
        [sym_var_name] = 294,
        [aux_sym_interface_type_repeat1] = 294,
        [anon_sym_RBRACE] = 294,
        [sym__line_break] = 12,
        [sym__identifier] = 294,
        [sym_comment] = 12,
    },
    [92] = {
        [sym_var_name] = 296,
        [aux_sym_interface_type_repeat1] = 296,
        [anon_sym_RBRACE] = 296,
        [sym__line_break] = 12,
        [sym__identifier] = 296,
        [sym_comment] = 12,
    },
    [93] = {
        [aux_sym__func_signature_repeat2] = 298,
        [anon_sym_RPAREN] = 292,
        [anon_sym_COMMA] = 156,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [94] = {
        [anon_sym_RPAREN] = 300,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [95] = {
        [sym_var_name] = 302,
        [aux_sym_interface_type_repeat1] = 302,
        [anon_sym_RBRACE] = 302,
        [sym__line_break] = 12,
        [sym__identifier] = 302,
        [sym_comment] = 12,
    },
    [96] = {
        [sym_var_name] = 152,
        [sym_type_name] = 248,
        [aux_sym_interface_type_repeat1] = 152,
        [anon_sym_LPAREN] = 304,
        [anon_sym_RBRACE] = 152,
        [sym__line_break] = 12,
        [sym__identifier] = 152,
        [sym_comment] = 12,
    },
    [97] = {
        [sym_var_name] = 306,
        [sym_type_name] = 308,
        [sym__line_break] = 12,
        [sym__identifier] = 124,
        [sym_comment] = 12,
    },
    [98] = {
        [sym_type_name] = 310,
        [sym__line_break] = 12,
        [sym__identifier] = 130,
        [sym_comment] = 12,
    },
    [99] = {
        [aux_sym__func_signature_repeat3] = 298,
        [anon_sym_RPAREN] = 292,
        [anon_sym_COMMA] = 136,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [100] = {
        [aux_sym__func_signature_repeat2] = 312,
        [anon_sym_RPAREN] = 300,
        [anon_sym_COMMA] = 156,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [101] = {
        [anon_sym_RPAREN] = 314,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [102] = {
        [sym_var_name] = 316,
        [aux_sym_interface_type_repeat1] = 316,
        [anon_sym_RBRACE] = 316,
        [sym__line_break] = 12,
        [sym__identifier] = 316,
        [sym_comment] = 12,
    },
    [103] = {
        [anon_sym_RPAREN] = 258,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [104] = {
        [sym_var_name] = 318,
        [sym_type_name] = 242,
        [aux_sym_interface_type_repeat1] = 318,
        [anon_sym_LPAREN] = 320,
        [anon_sym_RBRACE] = 318,
        [sym__line_break] = 12,
        [sym__identifier] = 318,
        [sym_comment] = 12,
    },
    [105] = {
        [sym_var_name] = 322,
        [sym_type_name] = 324,
        [sym__line_break] = 12,
        [sym__identifier] = 124,
        [sym_comment] = 12,
    },
    [106] = {
        [sym_type_name] = 326,
        [sym__line_break] = 12,
        [sym__identifier] = 130,
        [sym_comment] = 12,
    },
    [107] = {
        [aux_sym__func_signature_repeat3] = 328,
        [anon_sym_RPAREN] = 248,
        [anon_sym_COMMA] = 136,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [108] = {
        [anon_sym_RPAREN] = 290,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [109] = {
        [aux_sym__func_signature_repeat2] = 288,
        [anon_sym_RPAREN] = 290,
        [anon_sym_COMMA] = 156,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [110] = {
        [anon_sym_RBRACE] = 330,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [111] = {
        [sym_var_name] = 332,
        [aux_sym_struct_type_repeat1] = 334,
        [anon_sym_RBRACE] = 336,
        [sym__line_break] = 12,
        [sym__identifier] = 338,
        [sym_comment] = 12,
    },
    [112] = {
        [sym__type_expression] = 340,
        [sym_pointer_type] = 342,
        [sym_map_type] = 342,
        [sym_slice_type] = 342,
        [sym_struct_type] = 342,
        [sym_interface_type] = 342,
        [sym_type_name] = 342,
        [anon_sym_STAR] = 344,
        [anon_sym_map] = 346,
        [anon_sym_LBRACK] = 348,
        [anon_sym_struct] = 350,
        [anon_sym_interface] = 352,
        [sym__line_break] = 12,
        [sym__identifier] = 354,
        [sym_comment] = 12,
    },
    [113] = {
        [anon_sym_RBRACE] = 356,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [114] = {
        [aux_sym__func_signature_repeat1] = 358,
        [anon_sym_RPAREN] = 358,
        [anon_sym_COMMA] = 358,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [115] = {
        [sym__type_expression] = 78,
        [sym_pointer_type] = 78,
        [sym_map_type] = 78,
        [sym_slice_type] = 78,
        [sym_struct_type] = 78,
        [sym_interface_type] = 78,
        [sym_type_name] = 78,
        [anon_sym_STAR] = 78,
        [anon_sym_map] = 78,
        [anon_sym_LBRACK] = 78,
        [anon_sym_struct] = 78,
        [anon_sym_interface] = 78,
        [sym__line_break] = 12,
        [sym__identifier] = 78,
        [sym_comment] = 12,
    },
    [116] = {
        [aux_sym__func_signature_repeat1] = 360,
        [anon_sym_RPAREN] = 360,
        [anon_sym_COMMA] = 360,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [117] = {
        [sym_var_name] = 332,
        [aux_sym_struct_type_repeat1] = 362,
        [anon_sym_RBRACE] = 364,
        [sym__line_break] = 12,
        [sym__identifier] = 338,
        [sym_comment] = 12,
    },
    [118] = {
        [sym_var_name] = 180,
        [aux_sym_struct_type_repeat1] = 180,
        [anon_sym_RBRACE] = 180,
        [sym__line_break] = 12,
        [sym__identifier] = 180,
        [sym_comment] = 12,
    },
    [119] = {
        [sym__type_expression] = 366,
        [sym_pointer_type] = 342,
        [sym_map_type] = 342,
        [sym_slice_type] = 342,
        [sym_struct_type] = 342,
        [sym_interface_type] = 342,
        [sym_type_name] = 342,
        [anon_sym_STAR] = 344,
        [anon_sym_map] = 346,
        [anon_sym_LBRACK] = 348,
        [anon_sym_struct] = 350,
        [anon_sym_interface] = 352,
        [sym__line_break] = 12,
        [sym__identifier] = 354,
        [sym_comment] = 12,
    },
    [120] = {
        [anon_sym_LBRACK] = 368,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [121] = {
        [anon_sym_RBRACK] = 370,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [122] = {
        [anon_sym_LBRACE] = 372,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [123] = {
        [anon_sym_LBRACE] = 374,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [124] = {
        [sym_var_name] = 126,
        [aux_sym_struct_type_repeat1] = 126,
        [anon_sym_RBRACE] = 126,
        [sym__line_break] = 12,
        [sym__identifier] = 126,
        [sym_comment] = 12,
    },
    [125] = {
        [sym_var_name] = 202,
        [aux_sym_interface_type_repeat1] = 376,
        [anon_sym_RBRACE] = 378,
        [sym__line_break] = 12,
        [sym__identifier] = 72,
        [sym_comment] = 12,
    },
    [126] = {
        [anon_sym_RBRACE] = 380,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [127] = {
        [sym_var_name] = 214,
        [aux_sym_struct_type_repeat1] = 214,
        [anon_sym_RBRACE] = 214,
        [sym__line_break] = 12,
        [sym__identifier] = 214,
        [sym_comment] = 12,
    },
    [128] = {
        [sym_var_name] = 216,
        [aux_sym_struct_type_repeat1] = 216,
        [anon_sym_RBRACE] = 216,
        [sym__line_break] = 12,
        [sym__identifier] = 216,
        [sym_comment] = 12,
    },
    [129] = {
        [sym_var_name] = 332,
        [aux_sym_struct_type_repeat1] = 382,
        [anon_sym_RBRACE] = 384,
        [sym__line_break] = 12,
        [sym__identifier] = 338,
        [sym_comment] = 12,
    },
    [130] = {
        [anon_sym_RBRACE] = 386,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [131] = {
        [sym_var_name] = 358,
        [aux_sym_struct_type_repeat1] = 358,
        [anon_sym_RBRACE] = 358,
        [sym__line_break] = 12,
        [sym__identifier] = 358,
        [sym_comment] = 12,
    },
    [132] = {
        [sym_var_name] = 360,
        [aux_sym_struct_type_repeat1] = 360,
        [anon_sym_RBRACE] = 360,
        [sym__line_break] = 12,
        [sym__identifier] = 360,
        [sym_comment] = 12,
    },
    [133] = {
        [sym__type_expression] = 388,
        [sym_pointer_type] = 342,
        [sym_map_type] = 342,
        [sym_slice_type] = 342,
        [sym_struct_type] = 342,
        [sym_interface_type] = 342,
        [sym_type_name] = 342,
        [anon_sym_STAR] = 344,
        [anon_sym_map] = 346,
        [anon_sym_LBRACK] = 348,
        [anon_sym_struct] = 350,
        [anon_sym_interface] = 352,
        [sym__line_break] = 12,
        [sym__identifier] = 354,
        [sym_comment] = 12,
    },
    [134] = {
        [sym_var_name] = 390,
        [aux_sym_struct_type_repeat1] = 390,
        [anon_sym_RBRACE] = 390,
        [sym__line_break] = 12,
        [sym__identifier] = 390,
        [sym_comment] = 12,
    },
    [135] = {
        [sym__type_expression] = 392,
        [sym_pointer_type] = 394,
        [sym_map_type] = 394,
        [sym_slice_type] = 394,
        [sym_struct_type] = 394,
        [sym_interface_type] = 394,
        [sym_type_name] = 394,
        [anon_sym_STAR] = 396,
        [anon_sym_map] = 398,
        [anon_sym_LBRACK] = 400,
        [anon_sym_struct] = 402,
        [anon_sym_interface] = 404,
        [sym__line_break] = 12,
        [sym__identifier] = 406,
        [sym_comment] = 12,
    },
    [136] = {
        [anon_sym_RBRACK] = 408,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [137] = {
        [anon_sym_RBRACK] = 180,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [138] = {
        [sym__type_expression] = 410,
        [sym_pointer_type] = 394,
        [sym_map_type] = 394,
        [sym_slice_type] = 394,
        [sym_struct_type] = 394,
        [sym_interface_type] = 394,
        [sym_type_name] = 394,
        [anon_sym_STAR] = 396,
        [anon_sym_map] = 398,
        [anon_sym_LBRACK] = 400,
        [anon_sym_struct] = 402,
        [anon_sym_interface] = 404,
        [sym__line_break] = 12,
        [sym__identifier] = 406,
        [sym_comment] = 12,
    },
    [139] = {
        [anon_sym_LBRACK] = 412,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [140] = {
        [anon_sym_RBRACK] = 414,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [141] = {
        [anon_sym_LBRACE] = 416,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [142] = {
        [anon_sym_LBRACE] = 418,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [143] = {
        [anon_sym_RBRACK] = 126,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [144] = {
        [sym_var_name] = 202,
        [aux_sym_interface_type_repeat1] = 420,
        [anon_sym_RBRACE] = 422,
        [sym__line_break] = 12,
        [sym__identifier] = 72,
        [sym_comment] = 12,
    },
    [145] = {
        [anon_sym_RBRACE] = 424,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [146] = {
        [anon_sym_RBRACK] = 214,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [147] = {
        [anon_sym_RBRACK] = 216,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [148] = {
        [sym_var_name] = 332,
        [aux_sym_struct_type_repeat1] = 426,
        [anon_sym_RBRACE] = 428,
        [sym__line_break] = 12,
        [sym__identifier] = 338,
        [sym_comment] = 12,
    },
    [149] = {
        [anon_sym_RBRACE] = 430,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [150] = {
        [anon_sym_RBRACK] = 358,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [151] = {
        [anon_sym_RBRACK] = 360,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [152] = {
        [sym__type_expression] = 432,
        [sym_pointer_type] = 394,
        [sym_map_type] = 394,
        [sym_slice_type] = 394,
        [sym_struct_type] = 394,
        [sym_interface_type] = 394,
        [sym_type_name] = 394,
        [anon_sym_STAR] = 396,
        [anon_sym_map] = 398,
        [anon_sym_LBRACK] = 400,
        [anon_sym_struct] = 402,
        [anon_sym_interface] = 404,
        [sym__line_break] = 12,
        [sym__identifier] = 406,
        [sym_comment] = 12,
    },
    [153] = {
        [anon_sym_RBRACK] = 390,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [154] = {
        [sym__type_expression] = 434,
        [sym_pointer_type] = 394,
        [sym_map_type] = 394,
        [sym_slice_type] = 394,
        [sym_struct_type] = 394,
        [sym_interface_type] = 394,
        [sym_type_name] = 394,
        [anon_sym_STAR] = 396,
        [anon_sym_map] = 398,
        [anon_sym_LBRACK] = 400,
        [anon_sym_struct] = 402,
        [anon_sym_interface] = 404,
        [sym__line_break] = 12,
        [sym__identifier] = 406,
        [sym_comment] = 12,
    },
    [155] = {
        [anon_sym_RBRACK] = 436,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [156] = {
        [sym__type_expression] = 438,
        [sym_pointer_type] = 394,
        [sym_map_type] = 394,
        [sym_slice_type] = 394,
        [sym_struct_type] = 394,
        [sym_interface_type] = 394,
        [sym_type_name] = 394,
        [anon_sym_STAR] = 396,
        [anon_sym_map] = 398,
        [anon_sym_LBRACK] = 400,
        [anon_sym_struct] = 402,
        [anon_sym_interface] = 404,
        [sym__line_break] = 12,
        [sym__identifier] = 406,
        [sym_comment] = 12,
    },
    [157] = {
        [anon_sym_RBRACK] = 440,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [158] = {
        [anon_sym_RBRACK] = 442,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [159] = {
        [sym__type_expression] = 444,
        [sym_pointer_type] = 342,
        [sym_map_type] = 342,
        [sym_slice_type] = 342,
        [sym_struct_type] = 342,
        [sym_interface_type] = 342,
        [sym_type_name] = 342,
        [anon_sym_STAR] = 344,
        [anon_sym_map] = 346,
        [anon_sym_LBRACK] = 348,
        [anon_sym_struct] = 350,
        [anon_sym_interface] = 352,
        [sym__line_break] = 12,
        [sym__identifier] = 354,
        [sym_comment] = 12,
    },
    [160] = {
        [sym_var_name] = 440,
        [aux_sym_struct_type_repeat1] = 440,
        [anon_sym_RBRACE] = 440,
        [sym__line_break] = 12,
        [sym__identifier] = 440,
        [sym_comment] = 12,
    },
    [161] = {
        [sym_var_name] = 442,
        [aux_sym_struct_type_repeat1] = 442,
        [anon_sym_RBRACE] = 442,
        [sym__line_break] = 12,
        [sym__identifier] = 442,
        [sym_comment] = 12,
    },
    [162] = {
        [anon_sym_RBRACE] = 446,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [163] = {
        [sym__type_expression] = 448,
        [sym_pointer_type] = 92,
        [sym_map_type] = 92,
        [sym_slice_type] = 92,
        [sym_struct_type] = 92,
        [sym_interface_type] = 92,
        [sym_type_name] = 92,
        [anon_sym_STAR] = 96,
        [anon_sym_map] = 98,
        [anon_sym_LBRACK] = 100,
        [anon_sym_struct] = 102,
        [anon_sym_interface] = 104,
        [sym__line_break] = 12,
        [sym__identifier] = 108,
        [sym_comment] = 12,
    },
    [164] = {
        [aux_sym__func_signature_repeat1] = 390,
        [anon_sym_RPAREN] = 390,
        [anon_sym_COMMA] = 390,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [165] = {
        [sym__type_expression] = 450,
        [sym_pointer_type] = 394,
        [sym_map_type] = 394,
        [sym_slice_type] = 394,
        [sym_struct_type] = 394,
        [sym_interface_type] = 394,
        [sym_type_name] = 394,
        [anon_sym_STAR] = 396,
        [anon_sym_map] = 398,
        [anon_sym_LBRACK] = 400,
        [anon_sym_struct] = 402,
        [anon_sym_interface] = 404,
        [sym__line_break] = 12,
        [sym__identifier] = 406,
        [sym_comment] = 12,
    },
    [166] = {
        [anon_sym_RBRACK] = 452,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [167] = {
        [sym__type_expression] = 454,
        [sym_pointer_type] = 92,
        [sym_map_type] = 92,
        [sym_slice_type] = 92,
        [sym_struct_type] = 92,
        [sym_interface_type] = 92,
        [sym_type_name] = 92,
        [anon_sym_STAR] = 96,
        [anon_sym_map] = 98,
        [anon_sym_LBRACK] = 100,
        [anon_sym_struct] = 102,
        [anon_sym_interface] = 104,
        [sym__line_break] = 12,
        [sym__identifier] = 108,
        [sym_comment] = 12,
    },
    [168] = {
        [aux_sym__func_signature_repeat1] = 440,
        [anon_sym_RPAREN] = 440,
        [anon_sym_COMMA] = 440,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [169] = {
        [aux_sym__func_signature_repeat1] = 442,
        [anon_sym_RPAREN] = 442,
        [anon_sym_COMMA] = 442,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [170] = {
        [aux_sym__func_signature_repeat1] = 456,
        [anon_sym_RPAREN] = 458,
        [anon_sym_COMMA] = 178,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [171] = {
        [anon_sym_RPAREN] = 460,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [172] = {
        [sym_block_statement] = 140,
        [sym_type_name] = 138,
        [anon_sym_LPAREN] = 462,
        [anon_sym_LBRACE] = 140,
        [sym__line_break] = 12,
        [sym__identifier] = 116,
        [sym_comment] = 12,
    },
    [173] = {
        [sym_var_name] = 464,
        [sym_type_name] = 466,
        [sym__line_break] = 12,
        [sym__identifier] = 124,
        [sym_comment] = 12,
    },
    [174] = {
        [sym_type_name] = 468,
        [sym__line_break] = 12,
        [sym__identifier] = 130,
        [sym_comment] = 12,
    },
    [175] = {
        [aux_sym__func_signature_repeat3] = 470,
        [anon_sym_RPAREN] = 472,
        [anon_sym_COMMA] = 136,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [176] = {
        [anon_sym_RPAREN] = 474,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [177] = {
        [sym_block_statement] = 294,
        [anon_sym_LBRACE] = 294,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [178] = {
        [sym_block_statement] = 296,
        [anon_sym_LBRACE] = 296,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [179] = {
        [aux_sym__func_signature_repeat2] = 476,
        [anon_sym_RPAREN] = 474,
        [anon_sym_COMMA] = 156,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [180] = {
        [anon_sym_RPAREN] = 478,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [181] = {
        [sym_block_statement] = 302,
        [anon_sym_LBRACE] = 302,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [182] = {
        [sym_block_statement] = 152,
        [sym_type_name] = 158,
        [anon_sym_LPAREN] = 480,
        [anon_sym_LBRACE] = 152,
        [sym__line_break] = 12,
        [sym__identifier] = 116,
        [sym_comment] = 12,
    },
    [183] = {
        [sym_var_name] = 482,
        [sym_type_name] = 484,
        [sym__line_break] = 12,
        [sym__identifier] = 124,
        [sym_comment] = 12,
    },
    [184] = {
        [sym_type_name] = 486,
        [sym__line_break] = 12,
        [sym__identifier] = 130,
        [sym_comment] = 12,
    },
    [185] = {
        [aux_sym__func_signature_repeat3] = 476,
        [anon_sym_RPAREN] = 474,
        [anon_sym_COMMA] = 136,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [186] = {
        [aux_sym__func_signature_repeat2] = 488,
        [anon_sym_RPAREN] = 478,
        [anon_sym_COMMA] = 156,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [187] = {
        [anon_sym_RPAREN] = 490,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [188] = {
        [sym_block_statement] = 316,
        [anon_sym_LBRACE] = 316,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [189] = {
        [anon_sym_RPAREN] = 458,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [190] = {
        [sym_block_statement] = 318,
        [sym_type_name] = 134,
        [anon_sym_LPAREN] = 492,
        [anon_sym_LBRACE] = 318,
        [sym__line_break] = 12,
        [sym__identifier] = 116,
        [sym_comment] = 12,
    },
    [191] = {
        [sym_var_name] = 494,
        [sym_type_name] = 496,
        [sym__line_break] = 12,
        [sym__identifier] = 124,
        [sym_comment] = 12,
    },
    [192] = {
        [sym_type_name] = 498,
        [sym__line_break] = 12,
        [sym__identifier] = 130,
        [sym_comment] = 12,
    },
    [193] = {
        [aux_sym__func_signature_repeat3] = 500,
        [anon_sym_RPAREN] = 158,
        [anon_sym_COMMA] = 136,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [194] = {
        [anon_sym_RPAREN] = 472,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [195] = {
        [aux_sym__func_signature_repeat2] = 470,
        [anon_sym_RPAREN] = 472,
        [anon_sym_COMMA] = 156,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [196] = {
        [anon_sym_SEMI] = 502,
        [sym__line_break] = 504,
        [sym_comment] = 12,
    },
    [197] = {
        [sym_var_declaration] = 506,
        [sym__statement] = 508,
        [sym_return_statement] = 506,
        [sym_short_var_declaration] = 506,
        [sym_range_statement] = 506,
        [sym_if_statement] = 506,
        [sym_expression_statement] = 506,
        [sym__expression] = 510,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 514,
        [aux_sym_block_statement_repeat1] = 516,
        [ts_builtin_sym_error] = 516,
        [anon_sym_var] = 518,
        [anon_sym_RBRACE] = 520,
        [anon_sym_return] = 522,
        [anon_sym_COLON_EQ] = 524,
        [anon_sym_for] = 526,
        [anon_sym_if] = 528,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 532,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [198] = {
        [sym_var_declaration] = 534,
        [sym__statement] = 534,
        [sym_return_statement] = 534,
        [sym_short_var_declaration] = 534,
        [sym_range_statement] = 534,
        [sym_if_statement] = 534,
        [sym_expression_statement] = 534,
        [sym__expression] = 534,
        [sym_call_expression] = 534,
        [sym_selector_expression] = 534,
        [sym_math_op] = 534,
        [sym_bool_op] = 534,
        [sym_var_name] = 534,
        [aux_sym_block_statement_repeat1] = 534,
        [anon_sym_var] = 534,
        [anon_sym_RBRACE] = 534,
        [anon_sym_return] = 534,
        [anon_sym_COLON_EQ] = 534,
        [anon_sym_for] = 534,
        [anon_sym_if] = 534,
        [anon_sym_BANG] = 534,
        [sym__line_break] = 12,
        [sym_string] = 534,
        [sym__identifier] = 534,
        [sym_number] = 534,
        [sym_comment] = 12,
    },
    [199] = {
        [sym_var_declaration] = 506,
        [sym__statement] = 508,
        [sym_return_statement] = 506,
        [sym_short_var_declaration] = 506,
        [sym_range_statement] = 506,
        [sym_if_statement] = 506,
        [sym_expression_statement] = 506,
        [sym__expression] = 510,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 514,
        [aux_sym_block_statement_repeat1] = 536,
        [anon_sym_var] = 518,
        [anon_sym_RBRACE] = 538,
        [anon_sym_return] = 522,
        [anon_sym_COLON_EQ] = 524,
        [anon_sym_for] = 526,
        [anon_sym_if] = 528,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 532,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [200] = {
        [anon_sym_LPAREN] = 540,
        [anon_sym_SEMI] = 542,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 546,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 548,
        [anon_sym_DASH] = 548,
        [anon_sym_PIPE_PIPE] = 550,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 556,
        [sym_comment] = 12,
    },
    [201] = {
        [anon_sym_LPAREN] = 558,
        [anon_sym_SEMI] = 558,
        [anon_sym_STAR] = 558,
        [anon_sym_DOT] = 558,
        [anon_sym_SLASH] = 558,
        [anon_sym_PLUS] = 558,
        [anon_sym_DASH] = 558,
        [anon_sym_PIPE_PIPE] = 558,
        [anon_sym_AMP_AMP] = 558,
        [anon_sym_EQ_EQ] = 558,
        [anon_sym_LT_EQ] = 558,
        [anon_sym_LT] = 558,
        [anon_sym_GT_EQ] = 558,
        [anon_sym_GT] = 558,
        [sym__line_break] = 558,
        [sym_comment] = 12,
    },
    [202] = {
        [aux_sym_short_var_declaration_repeat1] = 560,
        [anon_sym_LPAREN] = 558,
        [anon_sym_SEMI] = 558,
        [anon_sym_STAR] = 558,
        [anon_sym_COMMA] = 562,
        [anon_sym_COLON_EQ] = 564,
        [anon_sym_DOT] = 558,
        [anon_sym_SLASH] = 558,
        [anon_sym_PLUS] = 558,
        [anon_sym_DASH] = 558,
        [anon_sym_PIPE_PIPE] = 558,
        [anon_sym_AMP_AMP] = 558,
        [anon_sym_EQ_EQ] = 558,
        [anon_sym_LT_EQ] = 558,
        [anon_sym_LT] = 558,
        [anon_sym_GT_EQ] = 558,
        [anon_sym_GT] = 558,
        [sym__line_break] = 558,
        [sym_comment] = 12,
    },
    [203] = {
        [anon_sym_RBRACE] = 566,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [204] = {
        [sym_var_name] = 568,
        [sym__line_break] = 12,
        [sym__identifier] = 68,
        [sym_comment] = 12,
    },
    [205] = {
        [anon_sym_SEMI] = 570,
        [sym__line_break] = 570,
        [sym_comment] = 12,
    },
    [206] = {
        [sym__expression] = 572,
        [sym_call_expression] = 574,
        [sym_selector_expression] = 574,
        [sym_math_op] = 574,
        [sym_bool_op] = 574,
        [sym_var_name] = 574,
        [anon_sym_SEMI] = 576,
        [anon_sym_BANG] = 578,
        [sym__line_break] = 580,
        [sym_string] = 574,
        [sym__identifier] = 582,
        [sym_number] = 574,
        [sym_comment] = 12,
    },
    [207] = {
        [sym__expression] = 584,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [208] = {
        [sym_var_name] = 588,
        [sym__line_break] = 12,
        [sym__identifier] = 590,
        [sym_comment] = 12,
    },
    [209] = {
        [sym__expression] = 592,
        [sym_call_expression] = 594,
        [sym_selector_expression] = 594,
        [sym_math_op] = 594,
        [sym_bool_op] = 594,
        [sym_var_name] = 594,
        [anon_sym_BANG] = 596,
        [sym__line_break] = 12,
        [sym_string] = 594,
        [sym__identifier] = 598,
        [sym_number] = 594,
        [sym_comment] = 12,
    },
    [210] = {
        [sym__expression] = 600,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [211] = {
        [aux_sym_short_var_declaration_repeat1] = 78,
        [anon_sym_LPAREN] = 78,
        [anon_sym_SEMI] = 78,
        [anon_sym_STAR] = 78,
        [anon_sym_COMMA] = 78,
        [anon_sym_COLON_EQ] = 78,
        [anon_sym_DOT] = 78,
        [anon_sym_SLASH] = 78,
        [anon_sym_PLUS] = 78,
        [anon_sym_DASH] = 78,
        [anon_sym_PIPE_PIPE] = 78,
        [anon_sym_AMP_AMP] = 78,
        [anon_sym_EQ_EQ] = 78,
        [anon_sym_LT_EQ] = 78,
        [anon_sym_LT] = 78,
        [anon_sym_GT_EQ] = 78,
        [anon_sym_GT] = 78,
        [sym__line_break] = 78,
        [sym_comment] = 12,
    },
    [212] = {
        [anon_sym_LPAREN] = 602,
        [anon_sym_SEMI] = 602,
        [anon_sym_STAR] = 602,
        [anon_sym_DOT] = 602,
        [anon_sym_SLASH] = 602,
        [anon_sym_PLUS] = 602,
        [anon_sym_DASH] = 602,
        [anon_sym_PIPE_PIPE] = 602,
        [anon_sym_AMP_AMP] = 602,
        [anon_sym_EQ_EQ] = 602,
        [anon_sym_LT_EQ] = 602,
        [anon_sym_LT] = 602,
        [anon_sym_GT_EQ] = 602,
        [anon_sym_GT] = 602,
        [sym__line_break] = 602,
        [sym_comment] = 12,
    },
    [213] = {
        [anon_sym_LPAREN] = 78,
        [anon_sym_SEMI] = 78,
        [anon_sym_STAR] = 78,
        [anon_sym_DOT] = 78,
        [anon_sym_SLASH] = 78,
        [anon_sym_PLUS] = 78,
        [anon_sym_DASH] = 78,
        [anon_sym_PIPE_PIPE] = 78,
        [anon_sym_AMP_AMP] = 78,
        [anon_sym_EQ_EQ] = 78,
        [anon_sym_LT_EQ] = 78,
        [anon_sym_LT] = 78,
        [anon_sym_GT_EQ] = 78,
        [anon_sym_GT] = 78,
        [sym__line_break] = 78,
        [sym_comment] = 12,
    },
    [214] = {
        [sym_block_statement] = 604,
        [anon_sym_LPAREN] = 606,
        [anon_sym_LBRACE] = 608,
        [anon_sym_STAR] = 610,
        [anon_sym_DOT] = 612,
        [anon_sym_SLASH] = 610,
        [anon_sym_PLUS] = 614,
        [anon_sym_DASH] = 614,
        [anon_sym_PIPE_PIPE] = 616,
        [anon_sym_AMP_AMP] = 618,
        [anon_sym_EQ_EQ] = 620,
        [anon_sym_LT_EQ] = 620,
        [anon_sym_LT] = 620,
        [anon_sym_GT_EQ] = 620,
        [anon_sym_GT] = 620,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [215] = {
        [sym_block_statement] = 558,
        [anon_sym_LPAREN] = 558,
        [anon_sym_LBRACE] = 558,
        [anon_sym_STAR] = 558,
        [anon_sym_DOT] = 558,
        [anon_sym_SLASH] = 558,
        [anon_sym_PLUS] = 558,
        [anon_sym_DASH] = 558,
        [anon_sym_PIPE_PIPE] = 558,
        [anon_sym_AMP_AMP] = 558,
        [anon_sym_EQ_EQ] = 558,
        [anon_sym_LT_EQ] = 558,
        [anon_sym_LT] = 558,
        [anon_sym_GT_EQ] = 558,
        [anon_sym_GT] = 558,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [216] = {
        [sym__expression] = 622,
        [sym_call_expression] = 594,
        [sym_selector_expression] = 594,
        [sym_math_op] = 594,
        [sym_bool_op] = 594,
        [sym_var_name] = 594,
        [anon_sym_BANG] = 596,
        [sym__line_break] = 12,
        [sym_string] = 594,
        [sym__identifier] = 598,
        [sym_number] = 594,
        [sym_comment] = 12,
    },
    [217] = {
        [sym_block_statement] = 78,
        [anon_sym_LPAREN] = 78,
        [anon_sym_LBRACE] = 78,
        [anon_sym_STAR] = 78,
        [anon_sym_DOT] = 78,
        [anon_sym_SLASH] = 78,
        [anon_sym_PLUS] = 78,
        [anon_sym_DASH] = 78,
        [anon_sym_PIPE_PIPE] = 78,
        [anon_sym_AMP_AMP] = 78,
        [anon_sym_EQ_EQ] = 78,
        [anon_sym_LT_EQ] = 78,
        [anon_sym_LT] = 78,
        [anon_sym_GT_EQ] = 78,
        [anon_sym_GT] = 78,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [218] = {
        [sym_block_statement] = 602,
        [anon_sym_LPAREN] = 602,
        [anon_sym_LBRACE] = 602,
        [anon_sym_STAR] = 602,
        [anon_sym_DOT] = 602,
        [anon_sym_SLASH] = 602,
        [anon_sym_PLUS] = 602,
        [anon_sym_DASH] = 602,
        [anon_sym_PIPE_PIPE] = 602,
        [anon_sym_AMP_AMP] = 602,
        [anon_sym_EQ_EQ] = 602,
        [anon_sym_LT_EQ] = 602,
        [anon_sym_LT] = 602,
        [anon_sym_GT_EQ] = 602,
        [anon_sym_GT] = 602,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [219] = {
        [sym_var_declaration] = 624,
        [sym__statement] = 624,
        [sym_return_statement] = 624,
        [sym_short_var_declaration] = 624,
        [sym_range_statement] = 624,
        [sym_if_statement] = 624,
        [sym_expression_statement] = 624,
        [sym__expression] = 624,
        [sym_call_expression] = 624,
        [sym_selector_expression] = 624,
        [sym_math_op] = 624,
        [sym_bool_op] = 624,
        [sym_var_name] = 624,
        [aux_sym_block_statement_repeat1] = 624,
        [anon_sym_var] = 624,
        [anon_sym_RBRACE] = 624,
        [anon_sym_return] = 624,
        [anon_sym_COLON_EQ] = 624,
        [anon_sym_for] = 624,
        [anon_sym_if] = 624,
        [anon_sym_else] = 626,
        [anon_sym_BANG] = 624,
        [sym__line_break] = 12,
        [sym_string] = 624,
        [sym__identifier] = 624,
        [sym_number] = 624,
        [sym_comment] = 12,
    },
    [220] = {
        [sym__expression] = 628,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_RPAREN] = 632,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [221] = {
        [sym_var_declaration] = 506,
        [sym__statement] = 508,
        [sym_return_statement] = 506,
        [sym_short_var_declaration] = 506,
        [sym_range_statement] = 506,
        [sym_if_statement] = 506,
        [sym_expression_statement] = 506,
        [sym__expression] = 510,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 514,
        [aux_sym_block_statement_repeat1] = 638,
        [ts_builtin_sym_error] = 638,
        [anon_sym_var] = 518,
        [anon_sym_RBRACE] = 640,
        [anon_sym_return] = 522,
        [anon_sym_COLON_EQ] = 524,
        [anon_sym_for] = 526,
        [anon_sym_if] = 528,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 532,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [222] = {
        [sym__expression] = 642,
        [sym_call_expression] = 594,
        [sym_selector_expression] = 594,
        [sym_math_op] = 594,
        [sym_bool_op] = 594,
        [sym_var_name] = 594,
        [anon_sym_BANG] = 596,
        [sym__line_break] = 12,
        [sym_string] = 594,
        [sym__identifier] = 598,
        [sym_number] = 594,
        [sym_comment] = 12,
    },
    [223] = {
        [sym_var_name] = 644,
        [sym__line_break] = 12,
        [sym__identifier] = 598,
        [sym_comment] = 12,
    },
    [224] = {
        [sym__expression] = 646,
        [sym_call_expression] = 594,
        [sym_selector_expression] = 594,
        [sym_math_op] = 594,
        [sym_bool_op] = 594,
        [sym_var_name] = 594,
        [anon_sym_BANG] = 596,
        [sym__line_break] = 12,
        [sym_string] = 594,
        [sym__identifier] = 598,
        [sym_number] = 594,
        [sym_comment] = 12,
    },
    [225] = {
        [sym__expression] = 648,
        [sym_call_expression] = 594,
        [sym_selector_expression] = 594,
        [sym_math_op] = 594,
        [sym_bool_op] = 594,
        [sym_var_name] = 594,
        [anon_sym_BANG] = 596,
        [sym__line_break] = 12,
        [sym_string] = 594,
        [sym__identifier] = 598,
        [sym_number] = 594,
        [sym_comment] = 12,
    },
    [226] = {
        [sym__expression] = 650,
        [sym_call_expression] = 594,
        [sym_selector_expression] = 594,
        [sym_math_op] = 594,
        [sym_bool_op] = 594,
        [sym_var_name] = 594,
        [anon_sym_BANG] = 596,
        [sym__line_break] = 12,
        [sym_string] = 594,
        [sym__identifier] = 598,
        [sym_number] = 594,
        [sym_comment] = 12,
    },
    [227] = {
        [sym__expression] = 652,
        [sym_call_expression] = 594,
        [sym_selector_expression] = 594,
        [sym_math_op] = 594,
        [sym_bool_op] = 594,
        [sym_var_name] = 594,
        [anon_sym_BANG] = 596,
        [sym__line_break] = 12,
        [sym_string] = 594,
        [sym__identifier] = 598,
        [sym_number] = 594,
        [sym_comment] = 12,
    },
    [228] = {
        [sym_block_statement] = 654,
        [anon_sym_LPAREN] = 654,
        [anon_sym_LBRACE] = 654,
        [anon_sym_STAR] = 654,
        [anon_sym_DOT] = 654,
        [anon_sym_SLASH] = 654,
        [anon_sym_PLUS] = 654,
        [anon_sym_DASH] = 654,
        [anon_sym_PIPE_PIPE] = 654,
        [anon_sym_AMP_AMP] = 654,
        [anon_sym_EQ_EQ] = 654,
        [anon_sym_LT_EQ] = 654,
        [anon_sym_LT] = 654,
        [anon_sym_GT_EQ] = 654,
        [anon_sym_GT] = 654,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [229] = {
        [sym_block_statement] = 656,
        [anon_sym_LPAREN] = 656,
        [anon_sym_LBRACE] = 656,
        [anon_sym_STAR] = 656,
        [anon_sym_DOT] = 656,
        [anon_sym_SLASH] = 656,
        [anon_sym_PLUS] = 656,
        [anon_sym_DASH] = 656,
        [anon_sym_PIPE_PIPE] = 656,
        [anon_sym_AMP_AMP] = 656,
        [anon_sym_EQ_EQ] = 620,
        [anon_sym_LT_EQ] = 620,
        [anon_sym_LT] = 620,
        [anon_sym_GT_EQ] = 620,
        [anon_sym_GT] = 620,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [230] = {
        [sym_block_statement] = 656,
        [anon_sym_LPAREN] = 656,
        [anon_sym_LBRACE] = 656,
        [anon_sym_STAR] = 610,
        [anon_sym_DOT] = 656,
        [anon_sym_SLASH] = 610,
        [anon_sym_PLUS] = 656,
        [anon_sym_DASH] = 656,
        [anon_sym_PIPE_PIPE] = 656,
        [anon_sym_AMP_AMP] = 618,
        [anon_sym_EQ_EQ] = 620,
        [anon_sym_LT_EQ] = 620,
        [anon_sym_LT] = 620,
        [anon_sym_GT_EQ] = 620,
        [anon_sym_GT] = 620,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [231] = {
        [sym_block_statement] = 658,
        [anon_sym_LPAREN] = 658,
        [anon_sym_LBRACE] = 658,
        [anon_sym_STAR] = 610,
        [anon_sym_DOT] = 658,
        [anon_sym_SLASH] = 610,
        [anon_sym_PLUS] = 658,
        [anon_sym_DASH] = 658,
        [anon_sym_PIPE_PIPE] = 658,
        [anon_sym_AMP_AMP] = 618,
        [anon_sym_EQ_EQ] = 620,
        [anon_sym_LT_EQ] = 620,
        [anon_sym_LT] = 620,
        [anon_sym_GT_EQ] = 620,
        [anon_sym_GT] = 620,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [232] = {
        [sym_block_statement] = 658,
        [anon_sym_LPAREN] = 658,
        [anon_sym_LBRACE] = 658,
        [anon_sym_STAR] = 658,
        [anon_sym_DOT] = 658,
        [anon_sym_SLASH] = 658,
        [anon_sym_PLUS] = 658,
        [anon_sym_DASH] = 658,
        [anon_sym_PIPE_PIPE] = 658,
        [anon_sym_AMP_AMP] = 658,
        [anon_sym_EQ_EQ] = 620,
        [anon_sym_LT_EQ] = 620,
        [anon_sym_LT] = 620,
        [anon_sym_GT_EQ] = 620,
        [anon_sym_GT] = 620,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [233] = {
        [sym_block_statement] = 660,
        [anon_sym_LPAREN] = 660,
        [anon_sym_LBRACE] = 660,
        [anon_sym_STAR] = 660,
        [anon_sym_DOT] = 660,
        [anon_sym_SLASH] = 660,
        [anon_sym_PLUS] = 660,
        [anon_sym_DASH] = 660,
        [anon_sym_PIPE_PIPE] = 660,
        [anon_sym_AMP_AMP] = 660,
        [anon_sym_EQ_EQ] = 660,
        [anon_sym_LT_EQ] = 660,
        [anon_sym_LT] = 660,
        [anon_sym_GT_EQ] = 660,
        [anon_sym_GT] = 660,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [234] = {
        [anon_sym_RBRACE] = 662,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [235] = {
        [sym_var_declaration] = 570,
        [sym__statement] = 570,
        [sym_return_statement] = 570,
        [sym_short_var_declaration] = 570,
        [sym_range_statement] = 570,
        [sym_if_statement] = 570,
        [sym_expression_statement] = 570,
        [sym__expression] = 570,
        [sym_call_expression] = 570,
        [sym_selector_expression] = 570,
        [sym_math_op] = 570,
        [sym_bool_op] = 570,
        [sym_var_name] = 570,
        [aux_sym_block_statement_repeat1] = 570,
        [anon_sym_var] = 570,
        [anon_sym_RBRACE] = 570,
        [anon_sym_return] = 570,
        [anon_sym_COLON_EQ] = 570,
        [anon_sym_for] = 570,
        [anon_sym_if] = 570,
        [anon_sym_else] = 570,
        [anon_sym_BANG] = 570,
        [sym__line_break] = 12,
        [sym_string] = 570,
        [sym__identifier] = 570,
        [sym_number] = 570,
        [sym_comment] = 12,
    },
    [236] = {
        [sym_var_declaration] = 664,
        [sym__statement] = 664,
        [sym_return_statement] = 664,
        [sym_short_var_declaration] = 664,
        [sym_range_statement] = 664,
        [sym_if_statement] = 664,
        [sym_expression_statement] = 664,
        [sym__expression] = 664,
        [sym_call_expression] = 664,
        [sym_selector_expression] = 664,
        [sym_math_op] = 664,
        [sym_bool_op] = 664,
        [sym_var_name] = 664,
        [aux_sym_block_statement_repeat1] = 664,
        [anon_sym_var] = 664,
        [anon_sym_RBRACE] = 664,
        [anon_sym_return] = 664,
        [anon_sym_COLON_EQ] = 664,
        [anon_sym_for] = 664,
        [anon_sym_if] = 664,
        [anon_sym_else] = 664,
        [anon_sym_BANG] = 664,
        [sym__line_break] = 12,
        [sym_string] = 664,
        [sym__identifier] = 664,
        [sym_number] = 664,
        [sym_comment] = 12,
    },
    [237] = {
        [aux_sym_return_statement_repeat1] = 666,
        [anon_sym_LPAREN] = 668,
        [anon_sym_RPAREN] = 670,
        [anon_sym_STAR] = 672,
        [anon_sym_COMMA] = 674,
        [anon_sym_DOT] = 676,
        [anon_sym_SLASH] = 672,
        [anon_sym_PLUS] = 678,
        [anon_sym_DASH] = 678,
        [anon_sym_PIPE_PIPE] = 680,
        [anon_sym_AMP_AMP] = 682,
        [anon_sym_EQ_EQ] = 684,
        [anon_sym_LT_EQ] = 684,
        [anon_sym_LT] = 684,
        [anon_sym_GT_EQ] = 684,
        [anon_sym_GT] = 684,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [238] = {
        [aux_sym_return_statement_repeat1] = 558,
        [anon_sym_LPAREN] = 558,
        [anon_sym_RPAREN] = 558,
        [anon_sym_STAR] = 558,
        [anon_sym_COMMA] = 558,
        [anon_sym_DOT] = 558,
        [anon_sym_SLASH] = 558,
        [anon_sym_PLUS] = 558,
        [anon_sym_DASH] = 558,
        [anon_sym_PIPE_PIPE] = 558,
        [anon_sym_AMP_AMP] = 558,
        [anon_sym_EQ_EQ] = 558,
        [anon_sym_LT_EQ] = 558,
        [anon_sym_LT] = 558,
        [anon_sym_GT_EQ] = 558,
        [anon_sym_GT] = 558,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [239] = {
        [sym_block_statement] = 686,
        [anon_sym_LPAREN] = 686,
        [anon_sym_LBRACE] = 686,
        [anon_sym_STAR] = 686,
        [anon_sym_DOT] = 686,
        [anon_sym_SLASH] = 686,
        [anon_sym_PLUS] = 686,
        [anon_sym_DASH] = 686,
        [anon_sym_PIPE_PIPE] = 686,
        [anon_sym_AMP_AMP] = 686,
        [anon_sym_EQ_EQ] = 686,
        [anon_sym_LT_EQ] = 686,
        [anon_sym_LT] = 686,
        [anon_sym_GT_EQ] = 686,
        [anon_sym_GT] = 686,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [240] = {
        [sym__expression] = 688,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [241] = {
        [aux_sym_return_statement_repeat1] = 78,
        [anon_sym_LPAREN] = 78,
        [anon_sym_RPAREN] = 78,
        [anon_sym_STAR] = 78,
        [anon_sym_COMMA] = 78,
        [anon_sym_DOT] = 78,
        [anon_sym_SLASH] = 78,
        [anon_sym_PLUS] = 78,
        [anon_sym_DASH] = 78,
        [anon_sym_PIPE_PIPE] = 78,
        [anon_sym_AMP_AMP] = 78,
        [anon_sym_EQ_EQ] = 78,
        [anon_sym_LT_EQ] = 78,
        [anon_sym_LT] = 78,
        [anon_sym_GT_EQ] = 78,
        [anon_sym_GT] = 78,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [242] = {
        [aux_sym_return_statement_repeat1] = 602,
        [anon_sym_LPAREN] = 602,
        [anon_sym_RPAREN] = 602,
        [anon_sym_STAR] = 602,
        [anon_sym_COMMA] = 602,
        [anon_sym_DOT] = 602,
        [anon_sym_SLASH] = 602,
        [anon_sym_PLUS] = 602,
        [anon_sym_DASH] = 602,
        [anon_sym_PIPE_PIPE] = 602,
        [anon_sym_AMP_AMP] = 602,
        [anon_sym_EQ_EQ] = 602,
        [anon_sym_LT_EQ] = 602,
        [anon_sym_LT] = 602,
        [anon_sym_GT_EQ] = 602,
        [anon_sym_GT] = 602,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [243] = {
        [anon_sym_RPAREN] = 690,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [244] = {
        [sym__expression] = 692,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_RPAREN] = 694,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [245] = {
        [sym_block_statement] = 696,
        [anon_sym_LPAREN] = 696,
        [anon_sym_LBRACE] = 696,
        [anon_sym_STAR] = 696,
        [anon_sym_DOT] = 696,
        [anon_sym_SLASH] = 696,
        [anon_sym_PLUS] = 696,
        [anon_sym_DASH] = 696,
        [anon_sym_PIPE_PIPE] = 696,
        [anon_sym_AMP_AMP] = 696,
        [anon_sym_EQ_EQ] = 696,
        [anon_sym_LT_EQ] = 696,
        [anon_sym_LT] = 696,
        [anon_sym_GT_EQ] = 696,
        [anon_sym_GT] = 696,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [246] = {
        [sym__expression] = 698,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [247] = {
        [sym__expression] = 700,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [248] = {
        [sym_var_name] = 702,
        [sym__line_break] = 12,
        [sym__identifier] = 636,
        [sym_comment] = 12,
    },
    [249] = {
        [sym__expression] = 704,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [250] = {
        [sym__expression] = 706,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [251] = {
        [sym__expression] = 708,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [252] = {
        [sym__expression] = 710,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [253] = {
        [aux_sym_return_statement_repeat1] = 654,
        [anon_sym_LPAREN] = 654,
        [anon_sym_RPAREN] = 654,
        [anon_sym_STAR] = 654,
        [anon_sym_COMMA] = 654,
        [anon_sym_DOT] = 654,
        [anon_sym_SLASH] = 654,
        [anon_sym_PLUS] = 654,
        [anon_sym_DASH] = 654,
        [anon_sym_PIPE_PIPE] = 654,
        [anon_sym_AMP_AMP] = 654,
        [anon_sym_EQ_EQ] = 654,
        [anon_sym_LT_EQ] = 654,
        [anon_sym_LT] = 654,
        [anon_sym_GT_EQ] = 654,
        [anon_sym_GT] = 654,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [254] = {
        [aux_sym_return_statement_repeat1] = 656,
        [anon_sym_LPAREN] = 656,
        [anon_sym_RPAREN] = 656,
        [anon_sym_STAR] = 656,
        [anon_sym_COMMA] = 656,
        [anon_sym_DOT] = 656,
        [anon_sym_SLASH] = 656,
        [anon_sym_PLUS] = 656,
        [anon_sym_DASH] = 656,
        [anon_sym_PIPE_PIPE] = 656,
        [anon_sym_AMP_AMP] = 656,
        [anon_sym_EQ_EQ] = 684,
        [anon_sym_LT_EQ] = 684,
        [anon_sym_LT] = 684,
        [anon_sym_GT_EQ] = 684,
        [anon_sym_GT] = 684,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [255] = {
        [aux_sym_return_statement_repeat1] = 656,
        [anon_sym_LPAREN] = 656,
        [anon_sym_RPAREN] = 656,
        [anon_sym_STAR] = 672,
        [anon_sym_COMMA] = 656,
        [anon_sym_DOT] = 656,
        [anon_sym_SLASH] = 672,
        [anon_sym_PLUS] = 656,
        [anon_sym_DASH] = 656,
        [anon_sym_PIPE_PIPE] = 656,
        [anon_sym_AMP_AMP] = 682,
        [anon_sym_EQ_EQ] = 684,
        [anon_sym_LT_EQ] = 684,
        [anon_sym_LT] = 684,
        [anon_sym_GT_EQ] = 684,
        [anon_sym_GT] = 684,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [256] = {
        [aux_sym_return_statement_repeat1] = 658,
        [anon_sym_LPAREN] = 658,
        [anon_sym_RPAREN] = 658,
        [anon_sym_STAR] = 672,
        [anon_sym_COMMA] = 658,
        [anon_sym_DOT] = 658,
        [anon_sym_SLASH] = 672,
        [anon_sym_PLUS] = 658,
        [anon_sym_DASH] = 658,
        [anon_sym_PIPE_PIPE] = 658,
        [anon_sym_AMP_AMP] = 682,
        [anon_sym_EQ_EQ] = 684,
        [anon_sym_LT_EQ] = 684,
        [anon_sym_LT] = 684,
        [anon_sym_GT_EQ] = 684,
        [anon_sym_GT] = 684,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [257] = {
        [aux_sym_return_statement_repeat1] = 658,
        [anon_sym_LPAREN] = 658,
        [anon_sym_RPAREN] = 658,
        [anon_sym_STAR] = 658,
        [anon_sym_COMMA] = 658,
        [anon_sym_DOT] = 658,
        [anon_sym_SLASH] = 658,
        [anon_sym_PLUS] = 658,
        [anon_sym_DASH] = 658,
        [anon_sym_PIPE_PIPE] = 658,
        [anon_sym_AMP_AMP] = 658,
        [anon_sym_EQ_EQ] = 684,
        [anon_sym_LT_EQ] = 684,
        [anon_sym_LT] = 684,
        [anon_sym_GT_EQ] = 684,
        [anon_sym_GT] = 684,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [258] = {
        [aux_sym_return_statement_repeat1] = 660,
        [anon_sym_LPAREN] = 660,
        [anon_sym_RPAREN] = 660,
        [anon_sym_STAR] = 660,
        [anon_sym_COMMA] = 660,
        [anon_sym_DOT] = 660,
        [anon_sym_SLASH] = 660,
        [anon_sym_PLUS] = 660,
        [anon_sym_DASH] = 660,
        [anon_sym_PIPE_PIPE] = 660,
        [anon_sym_AMP_AMP] = 660,
        [anon_sym_EQ_EQ] = 660,
        [anon_sym_LT_EQ] = 660,
        [anon_sym_LT] = 660,
        [anon_sym_GT_EQ] = 660,
        [anon_sym_GT] = 660,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [259] = {
        [aux_sym_return_statement_repeat1] = 712,
        [anon_sym_LPAREN] = 668,
        [anon_sym_RPAREN] = 714,
        [anon_sym_STAR] = 672,
        [anon_sym_COMMA] = 674,
        [anon_sym_DOT] = 676,
        [anon_sym_SLASH] = 672,
        [anon_sym_PLUS] = 678,
        [anon_sym_DASH] = 678,
        [anon_sym_PIPE_PIPE] = 680,
        [anon_sym_AMP_AMP] = 682,
        [anon_sym_EQ_EQ] = 684,
        [anon_sym_LT_EQ] = 684,
        [anon_sym_LT] = 684,
        [anon_sym_GT_EQ] = 684,
        [anon_sym_GT] = 684,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [260] = {
        [anon_sym_RPAREN] = 716,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [261] = {
        [aux_sym_return_statement_repeat1] = 718,
        [anon_sym_LPAREN] = 668,
        [anon_sym_RPAREN] = 720,
        [anon_sym_STAR] = 672,
        [anon_sym_COMMA] = 674,
        [anon_sym_DOT] = 676,
        [anon_sym_SLASH] = 672,
        [anon_sym_PLUS] = 678,
        [anon_sym_DASH] = 678,
        [anon_sym_PIPE_PIPE] = 680,
        [anon_sym_AMP_AMP] = 682,
        [anon_sym_EQ_EQ] = 684,
        [anon_sym_LT_EQ] = 684,
        [anon_sym_LT] = 684,
        [anon_sym_GT_EQ] = 684,
        [anon_sym_GT] = 684,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [262] = {
        [aux_sym_return_statement_repeat1] = 686,
        [anon_sym_LPAREN] = 686,
        [anon_sym_RPAREN] = 686,
        [anon_sym_STAR] = 686,
        [anon_sym_COMMA] = 686,
        [anon_sym_DOT] = 686,
        [anon_sym_SLASH] = 686,
        [anon_sym_PLUS] = 686,
        [anon_sym_DASH] = 686,
        [anon_sym_PIPE_PIPE] = 686,
        [anon_sym_AMP_AMP] = 686,
        [anon_sym_EQ_EQ] = 686,
        [anon_sym_LT_EQ] = 686,
        [anon_sym_LT] = 686,
        [anon_sym_GT_EQ] = 686,
        [anon_sym_GT] = 686,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [263] = {
        [anon_sym_RPAREN] = 722,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [264] = {
        [aux_sym_return_statement_repeat1] = 696,
        [anon_sym_LPAREN] = 696,
        [anon_sym_RPAREN] = 696,
        [anon_sym_STAR] = 696,
        [anon_sym_COMMA] = 696,
        [anon_sym_DOT] = 696,
        [anon_sym_SLASH] = 696,
        [anon_sym_PLUS] = 696,
        [anon_sym_DASH] = 696,
        [anon_sym_PIPE_PIPE] = 696,
        [anon_sym_AMP_AMP] = 696,
        [anon_sym_EQ_EQ] = 696,
        [anon_sym_LT_EQ] = 696,
        [anon_sym_LT] = 696,
        [anon_sym_GT_EQ] = 696,
        [anon_sym_GT] = 696,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [265] = {
        [aux_sym_return_statement_repeat1] = 724,
        [anon_sym_LPAREN] = 724,
        [anon_sym_RPAREN] = 724,
        [anon_sym_STAR] = 724,
        [anon_sym_COMMA] = 724,
        [anon_sym_DOT] = 724,
        [anon_sym_SLASH] = 724,
        [anon_sym_PLUS] = 724,
        [anon_sym_DASH] = 724,
        [anon_sym_PIPE_PIPE] = 724,
        [anon_sym_AMP_AMP] = 724,
        [anon_sym_EQ_EQ] = 724,
        [anon_sym_LT_EQ] = 724,
        [anon_sym_LT] = 724,
        [anon_sym_GT_EQ] = 724,
        [anon_sym_GT] = 724,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [266] = {
        [sym_block_statement] = 724,
        [anon_sym_LPAREN] = 724,
        [anon_sym_LBRACE] = 724,
        [anon_sym_STAR] = 724,
        [anon_sym_DOT] = 724,
        [anon_sym_SLASH] = 724,
        [anon_sym_PLUS] = 724,
        [anon_sym_DASH] = 724,
        [anon_sym_PIPE_PIPE] = 724,
        [anon_sym_AMP_AMP] = 724,
        [anon_sym_EQ_EQ] = 724,
        [anon_sym_LT_EQ] = 724,
        [anon_sym_LT] = 724,
        [anon_sym_GT_EQ] = 724,
        [anon_sym_GT] = 724,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [267] = {
        [sym_block_statement] = 726,
        [sym_if_statement] = 726,
        [anon_sym_LBRACE] = 728,
        [anon_sym_if] = 528,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [268] = {
        [sym_var_declaration] = 730,
        [sym__statement] = 730,
        [sym_return_statement] = 730,
        [sym_short_var_declaration] = 730,
        [sym_range_statement] = 730,
        [sym_if_statement] = 730,
        [sym_expression_statement] = 730,
        [sym__expression] = 730,
        [sym_call_expression] = 730,
        [sym_selector_expression] = 730,
        [sym_math_op] = 730,
        [sym_bool_op] = 730,
        [sym_var_name] = 730,
        [aux_sym_block_statement_repeat1] = 730,
        [anon_sym_var] = 730,
        [anon_sym_RBRACE] = 730,
        [anon_sym_return] = 730,
        [anon_sym_COLON_EQ] = 730,
        [anon_sym_for] = 730,
        [anon_sym_if] = 730,
        [anon_sym_BANG] = 730,
        [sym__line_break] = 12,
        [sym_string] = 730,
        [sym__identifier] = 730,
        [sym_number] = 730,
        [sym_comment] = 12,
    },
    [269] = {
        [sym_var_declaration] = 506,
        [sym__statement] = 508,
        [sym_return_statement] = 506,
        [sym_short_var_declaration] = 506,
        [sym_range_statement] = 506,
        [sym_if_statement] = 506,
        [sym_expression_statement] = 506,
        [sym__expression] = 510,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 514,
        [aux_sym_block_statement_repeat1] = 732,
        [ts_builtin_sym_error] = 732,
        [anon_sym_var] = 518,
        [anon_sym_RBRACE] = 734,
        [anon_sym_return] = 522,
        [anon_sym_COLON_EQ] = 524,
        [anon_sym_for] = 526,
        [anon_sym_if] = 528,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 532,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [270] = {
        [anon_sym_RBRACE] = 736,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [271] = {
        [sym_var_declaration] = 570,
        [sym__statement] = 570,
        [sym_return_statement] = 570,
        [sym_short_var_declaration] = 570,
        [sym_range_statement] = 570,
        [sym_if_statement] = 570,
        [sym_expression_statement] = 570,
        [sym__expression] = 570,
        [sym_call_expression] = 570,
        [sym_selector_expression] = 570,
        [sym_math_op] = 570,
        [sym_bool_op] = 570,
        [sym_var_name] = 570,
        [aux_sym_block_statement_repeat1] = 570,
        [anon_sym_var] = 570,
        [anon_sym_RBRACE] = 570,
        [anon_sym_return] = 570,
        [anon_sym_COLON_EQ] = 570,
        [anon_sym_for] = 570,
        [anon_sym_if] = 570,
        [anon_sym_BANG] = 570,
        [sym__line_break] = 12,
        [sym_string] = 570,
        [sym__identifier] = 570,
        [sym_number] = 570,
        [sym_comment] = 12,
    },
    [272] = {
        [sym_var_declaration] = 664,
        [sym__statement] = 664,
        [sym_return_statement] = 664,
        [sym_short_var_declaration] = 664,
        [sym_range_statement] = 664,
        [sym_if_statement] = 664,
        [sym_expression_statement] = 664,
        [sym__expression] = 664,
        [sym_call_expression] = 664,
        [sym_selector_expression] = 664,
        [sym_math_op] = 664,
        [sym_bool_op] = 664,
        [sym_var_name] = 664,
        [aux_sym_block_statement_repeat1] = 664,
        [anon_sym_var] = 664,
        [anon_sym_RBRACE] = 664,
        [anon_sym_return] = 664,
        [anon_sym_COLON_EQ] = 664,
        [anon_sym_for] = 664,
        [anon_sym_if] = 664,
        [anon_sym_BANG] = 664,
        [sym__line_break] = 12,
        [sym_string] = 664,
        [sym__identifier] = 664,
        [sym_number] = 664,
        [sym_comment] = 12,
    },
    [273] = {
        [anon_sym_COMMA] = 738,
        [anon_sym_COLON_EQ] = 740,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [274] = {
        [anon_sym_COMMA] = 78,
        [anon_sym_COLON_EQ] = 78,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [275] = {
        [sym_var_name] = 742,
        [sym__line_break] = 12,
        [sym__identifier] = 744,
        [sym_comment] = 12,
    },
    [276] = {
        [anon_sym_range] = 746,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [277] = {
        [sym__expression] = 748,
        [sym_call_expression] = 594,
        [sym_selector_expression] = 594,
        [sym_math_op] = 594,
        [sym_bool_op] = 594,
        [sym_var_name] = 594,
        [anon_sym_BANG] = 596,
        [sym__line_break] = 12,
        [sym_string] = 594,
        [sym__identifier] = 598,
        [sym_number] = 594,
        [sym_comment] = 12,
    },
    [278] = {
        [sym_block_statement] = 750,
        [anon_sym_LPAREN] = 606,
        [anon_sym_LBRACE] = 728,
        [anon_sym_STAR] = 610,
        [anon_sym_DOT] = 612,
        [anon_sym_SLASH] = 610,
        [anon_sym_PLUS] = 614,
        [anon_sym_DASH] = 614,
        [anon_sym_PIPE_PIPE] = 616,
        [anon_sym_AMP_AMP] = 618,
        [anon_sym_EQ_EQ] = 620,
        [anon_sym_LT_EQ] = 620,
        [anon_sym_LT] = 620,
        [anon_sym_GT_EQ] = 620,
        [anon_sym_GT] = 620,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [279] = {
        [sym_var_declaration] = 752,
        [sym__statement] = 752,
        [sym_return_statement] = 752,
        [sym_short_var_declaration] = 752,
        [sym_range_statement] = 752,
        [sym_if_statement] = 752,
        [sym_expression_statement] = 752,
        [sym__expression] = 752,
        [sym_call_expression] = 752,
        [sym_selector_expression] = 752,
        [sym_math_op] = 752,
        [sym_bool_op] = 752,
        [sym_var_name] = 752,
        [aux_sym_block_statement_repeat1] = 752,
        [anon_sym_var] = 752,
        [anon_sym_RBRACE] = 752,
        [anon_sym_return] = 752,
        [anon_sym_COLON_EQ] = 752,
        [anon_sym_for] = 752,
        [anon_sym_if] = 752,
        [anon_sym_BANG] = 752,
        [sym__line_break] = 12,
        [sym_string] = 752,
        [sym__identifier] = 752,
        [sym_number] = 752,
        [sym_comment] = 12,
    },
    [280] = {
        [anon_sym_COLON_EQ] = 754,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [281] = {
        [anon_sym_COLON_EQ] = 78,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [282] = {
        [anon_sym_range] = 756,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [283] = {
        [sym__expression] = 758,
        [sym_call_expression] = 594,
        [sym_selector_expression] = 594,
        [sym_math_op] = 594,
        [sym_bool_op] = 594,
        [sym_var_name] = 594,
        [anon_sym_BANG] = 596,
        [sym__line_break] = 12,
        [sym_string] = 594,
        [sym__identifier] = 598,
        [sym_number] = 594,
        [sym_comment] = 12,
    },
    [284] = {
        [sym_block_statement] = 760,
        [anon_sym_LPAREN] = 606,
        [anon_sym_LBRACE] = 728,
        [anon_sym_STAR] = 610,
        [anon_sym_DOT] = 612,
        [anon_sym_SLASH] = 610,
        [anon_sym_PLUS] = 614,
        [anon_sym_DASH] = 614,
        [anon_sym_PIPE_PIPE] = 616,
        [anon_sym_AMP_AMP] = 618,
        [anon_sym_EQ_EQ] = 620,
        [anon_sym_LT_EQ] = 620,
        [anon_sym_LT] = 620,
        [anon_sym_GT_EQ] = 620,
        [anon_sym_GT] = 620,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [285] = {
        [sym_var_declaration] = 762,
        [sym__statement] = 762,
        [sym_return_statement] = 762,
        [sym_short_var_declaration] = 762,
        [sym_range_statement] = 762,
        [sym_if_statement] = 762,
        [sym_expression_statement] = 762,
        [sym__expression] = 762,
        [sym_call_expression] = 762,
        [sym_selector_expression] = 762,
        [sym_math_op] = 762,
        [sym_bool_op] = 762,
        [sym_var_name] = 762,
        [aux_sym_block_statement_repeat1] = 762,
        [anon_sym_var] = 762,
        [anon_sym_RBRACE] = 762,
        [anon_sym_return] = 762,
        [anon_sym_COLON_EQ] = 762,
        [anon_sym_for] = 762,
        [anon_sym_if] = 762,
        [anon_sym_BANG] = 762,
        [sym__line_break] = 12,
        [sym_string] = 762,
        [sym__identifier] = 762,
        [sym_number] = 762,
        [sym_comment] = 12,
    },
    [286] = {
        [anon_sym_LPAREN] = 540,
        [anon_sym_SEMI] = 764,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 546,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 548,
        [anon_sym_DASH] = 548,
        [anon_sym_PIPE_PIPE] = 550,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 766,
        [sym_comment] = 12,
    },
    [287] = {
        [sym__expression] = 768,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_RPAREN] = 770,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [288] = {
        [sym_var_declaration] = 772,
        [sym__statement] = 772,
        [sym_return_statement] = 772,
        [sym_short_var_declaration] = 772,
        [sym_range_statement] = 772,
        [sym_if_statement] = 772,
        [sym_expression_statement] = 772,
        [sym__expression] = 772,
        [sym_call_expression] = 772,
        [sym_selector_expression] = 772,
        [sym_math_op] = 772,
        [sym_bool_op] = 772,
        [sym_var_name] = 772,
        [aux_sym_block_statement_repeat1] = 772,
        [anon_sym_var] = 772,
        [anon_sym_RBRACE] = 772,
        [anon_sym_return] = 772,
        [anon_sym_COLON_EQ] = 772,
        [anon_sym_for] = 772,
        [anon_sym_if] = 772,
        [anon_sym_BANG] = 772,
        [sym__line_break] = 12,
        [sym_string] = 772,
        [sym__identifier] = 772,
        [sym_number] = 772,
        [sym_comment] = 12,
    },
    [289] = {
        [sym__expression] = 774,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [290] = {
        [sym_var_name] = 776,
        [sym__line_break] = 12,
        [sym__identifier] = 586,
        [sym_comment] = 12,
    },
    [291] = {
        [sym__expression] = 778,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [292] = {
        [sym__expression] = 780,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [293] = {
        [sym__expression] = 782,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [294] = {
        [sym__expression] = 784,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [295] = {
        [sym_var_declaration] = 772,
        [sym__statement] = 772,
        [sym_return_statement] = 772,
        [sym_short_var_declaration] = 772,
        [sym_range_statement] = 772,
        [sym_if_statement] = 772,
        [sym_expression_statement] = 772,
        [sym__expression] = 772,
        [sym_call_expression] = 772,
        [sym_selector_expression] = 772,
        [sym_math_op] = 772,
        [sym_bool_op] = 772,
        [sym_var_name] = 772,
        [aux_sym_block_statement_repeat1] = 772,
        [anon_sym_LPAREN] = 786,
        [anon_sym_SEMI] = 786,
        [anon_sym_var] = 772,
        [anon_sym_RBRACE] = 772,
        [anon_sym_STAR] = 786,
        [anon_sym_return] = 772,
        [anon_sym_COLON_EQ] = 772,
        [anon_sym_for] = 772,
        [anon_sym_if] = 772,
        [anon_sym_DOT] = 786,
        [anon_sym_SLASH] = 786,
        [anon_sym_PLUS] = 786,
        [anon_sym_DASH] = 786,
        [anon_sym_PIPE_PIPE] = 786,
        [anon_sym_AMP_AMP] = 786,
        [anon_sym_EQ_EQ] = 786,
        [anon_sym_LT_EQ] = 786,
        [anon_sym_LT] = 786,
        [anon_sym_GT_EQ] = 786,
        [anon_sym_GT] = 786,
        [anon_sym_BANG] = 772,
        [sym__line_break] = 12,
        [sym_string] = 772,
        [sym__identifier] = 772,
        [sym_number] = 772,
        [sym_comment] = 12,
    },
    [296] = {
        [anon_sym_LPAREN] = 654,
        [anon_sym_SEMI] = 654,
        [anon_sym_STAR] = 654,
        [anon_sym_DOT] = 654,
        [anon_sym_SLASH] = 654,
        [anon_sym_PLUS] = 654,
        [anon_sym_DASH] = 654,
        [anon_sym_PIPE_PIPE] = 654,
        [anon_sym_AMP_AMP] = 654,
        [anon_sym_EQ_EQ] = 654,
        [anon_sym_LT_EQ] = 654,
        [anon_sym_LT] = 654,
        [anon_sym_GT_EQ] = 654,
        [anon_sym_GT] = 654,
        [sym__line_break] = 654,
        [sym_comment] = 12,
    },
    [297] = {
        [anon_sym_LPAREN] = 656,
        [anon_sym_SEMI] = 656,
        [anon_sym_STAR] = 656,
        [anon_sym_DOT] = 656,
        [anon_sym_SLASH] = 656,
        [anon_sym_PLUS] = 656,
        [anon_sym_DASH] = 656,
        [anon_sym_PIPE_PIPE] = 656,
        [anon_sym_AMP_AMP] = 656,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 656,
        [sym_comment] = 12,
    },
    [298] = {
        [anon_sym_LPAREN] = 656,
        [anon_sym_SEMI] = 656,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 656,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 656,
        [anon_sym_DASH] = 656,
        [anon_sym_PIPE_PIPE] = 656,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 656,
        [sym_comment] = 12,
    },
    [299] = {
        [anon_sym_LPAREN] = 658,
        [anon_sym_SEMI] = 658,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 658,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 658,
        [anon_sym_DASH] = 658,
        [anon_sym_PIPE_PIPE] = 658,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 658,
        [sym_comment] = 12,
    },
    [300] = {
        [anon_sym_LPAREN] = 658,
        [anon_sym_SEMI] = 658,
        [anon_sym_STAR] = 658,
        [anon_sym_DOT] = 658,
        [anon_sym_SLASH] = 658,
        [anon_sym_PLUS] = 658,
        [anon_sym_DASH] = 658,
        [anon_sym_PIPE_PIPE] = 658,
        [anon_sym_AMP_AMP] = 658,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 658,
        [sym_comment] = 12,
    },
    [301] = {
        [anon_sym_LPAREN] = 660,
        [anon_sym_SEMI] = 660,
        [anon_sym_STAR] = 660,
        [anon_sym_DOT] = 660,
        [anon_sym_SLASH] = 660,
        [anon_sym_PLUS] = 660,
        [anon_sym_DASH] = 660,
        [anon_sym_PIPE_PIPE] = 660,
        [anon_sym_AMP_AMP] = 660,
        [anon_sym_EQ_EQ] = 660,
        [anon_sym_LT_EQ] = 660,
        [anon_sym_LT] = 660,
        [anon_sym_GT_EQ] = 660,
        [anon_sym_GT] = 660,
        [sym__line_break] = 660,
        [sym_comment] = 12,
    },
    [302] = {
        [aux_sym_return_statement_repeat1] = 788,
        [anon_sym_LPAREN] = 668,
        [anon_sym_RPAREN] = 790,
        [anon_sym_STAR] = 672,
        [anon_sym_COMMA] = 674,
        [anon_sym_DOT] = 676,
        [anon_sym_SLASH] = 672,
        [anon_sym_PLUS] = 678,
        [anon_sym_DASH] = 678,
        [anon_sym_PIPE_PIPE] = 680,
        [anon_sym_AMP_AMP] = 682,
        [anon_sym_EQ_EQ] = 684,
        [anon_sym_LT_EQ] = 684,
        [anon_sym_LT] = 684,
        [anon_sym_GT_EQ] = 684,
        [anon_sym_GT] = 684,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [303] = {
        [anon_sym_LPAREN] = 686,
        [anon_sym_SEMI] = 686,
        [anon_sym_STAR] = 686,
        [anon_sym_DOT] = 686,
        [anon_sym_SLASH] = 686,
        [anon_sym_PLUS] = 686,
        [anon_sym_DASH] = 686,
        [anon_sym_PIPE_PIPE] = 686,
        [anon_sym_AMP_AMP] = 686,
        [anon_sym_EQ_EQ] = 686,
        [anon_sym_LT_EQ] = 686,
        [anon_sym_LT] = 686,
        [anon_sym_GT_EQ] = 686,
        [anon_sym_GT] = 686,
        [sym__line_break] = 686,
        [sym_comment] = 12,
    },
    [304] = {
        [anon_sym_RPAREN] = 792,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [305] = {
        [anon_sym_LPAREN] = 696,
        [anon_sym_SEMI] = 696,
        [anon_sym_STAR] = 696,
        [anon_sym_DOT] = 696,
        [anon_sym_SLASH] = 696,
        [anon_sym_PLUS] = 696,
        [anon_sym_DASH] = 696,
        [anon_sym_PIPE_PIPE] = 696,
        [anon_sym_AMP_AMP] = 696,
        [anon_sym_EQ_EQ] = 696,
        [anon_sym_LT_EQ] = 696,
        [anon_sym_LT] = 696,
        [anon_sym_GT_EQ] = 696,
        [anon_sym_GT] = 696,
        [sym__line_break] = 696,
        [sym_comment] = 12,
    },
    [306] = {
        [anon_sym_LPAREN] = 724,
        [anon_sym_SEMI] = 724,
        [anon_sym_STAR] = 724,
        [anon_sym_DOT] = 724,
        [anon_sym_SLASH] = 724,
        [anon_sym_PLUS] = 724,
        [anon_sym_DASH] = 724,
        [anon_sym_PIPE_PIPE] = 724,
        [anon_sym_AMP_AMP] = 724,
        [anon_sym_EQ_EQ] = 724,
        [anon_sym_LT_EQ] = 724,
        [anon_sym_LT] = 724,
        [anon_sym_GT_EQ] = 724,
        [anon_sym_GT] = 724,
        [sym__line_break] = 724,
        [sym_comment] = 12,
    },
    [307] = {
        [aux_sym_return_statement_repeat1] = 794,
        [anon_sym_LPAREN] = 796,
        [anon_sym_SEMI] = 798,
        [anon_sym_STAR] = 800,
        [anon_sym_COMMA] = 802,
        [anon_sym_DOT] = 804,
        [anon_sym_SLASH] = 800,
        [anon_sym_PLUS] = 806,
        [anon_sym_DASH] = 806,
        [anon_sym_PIPE_PIPE] = 808,
        [anon_sym_AMP_AMP] = 810,
        [anon_sym_EQ_EQ] = 812,
        [anon_sym_LT_EQ] = 812,
        [anon_sym_LT] = 812,
        [anon_sym_GT_EQ] = 812,
        [anon_sym_GT] = 812,
        [sym__line_break] = 814,
        [sym_comment] = 12,
    },
    [308] = {
        [aux_sym_return_statement_repeat1] = 558,
        [anon_sym_LPAREN] = 558,
        [anon_sym_SEMI] = 558,
        [anon_sym_STAR] = 558,
        [anon_sym_COMMA] = 558,
        [anon_sym_DOT] = 558,
        [anon_sym_SLASH] = 558,
        [anon_sym_PLUS] = 558,
        [anon_sym_DASH] = 558,
        [anon_sym_PIPE_PIPE] = 558,
        [anon_sym_AMP_AMP] = 558,
        [anon_sym_EQ_EQ] = 558,
        [anon_sym_LT_EQ] = 558,
        [anon_sym_LT] = 558,
        [anon_sym_GT_EQ] = 558,
        [anon_sym_GT] = 558,
        [sym__line_break] = 558,
        [sym_comment] = 12,
    },
    [309] = {
        [sym_var_declaration] = 816,
        [sym__statement] = 816,
        [sym_return_statement] = 816,
        [sym_short_var_declaration] = 816,
        [sym_range_statement] = 816,
        [sym_if_statement] = 816,
        [sym_expression_statement] = 816,
        [sym__expression] = 816,
        [sym_call_expression] = 816,
        [sym_selector_expression] = 816,
        [sym_math_op] = 816,
        [sym_bool_op] = 816,
        [sym_var_name] = 816,
        [aux_sym_block_statement_repeat1] = 816,
        [anon_sym_var] = 816,
        [anon_sym_RBRACE] = 816,
        [anon_sym_return] = 816,
        [anon_sym_COLON_EQ] = 816,
        [anon_sym_for] = 816,
        [anon_sym_if] = 816,
        [anon_sym_BANG] = 816,
        [sym__line_break] = 12,
        [sym_string] = 816,
        [sym__identifier] = 816,
        [sym_number] = 816,
        [sym_comment] = 12,
    },
    [310] = {
        [sym__expression] = 818,
        [sym_call_expression] = 574,
        [sym_selector_expression] = 574,
        [sym_math_op] = 574,
        [sym_bool_op] = 574,
        [sym_var_name] = 574,
        [anon_sym_BANG] = 578,
        [sym__line_break] = 12,
        [sym_string] = 574,
        [sym__identifier] = 582,
        [sym_number] = 574,
        [sym_comment] = 12,
    },
    [311] = {
        [sym_var_declaration] = 816,
        [sym__statement] = 816,
        [sym_return_statement] = 816,
        [sym_short_var_declaration] = 816,
        [sym_range_statement] = 816,
        [sym_if_statement] = 816,
        [sym_expression_statement] = 816,
        [sym__expression] = 816,
        [sym_call_expression] = 816,
        [sym_selector_expression] = 816,
        [sym_math_op] = 816,
        [sym_bool_op] = 816,
        [sym_var_name] = 816,
        [aux_sym_block_statement_repeat1] = 816,
        [anon_sym_SEMI] = 820,
        [anon_sym_var] = 816,
        [anon_sym_RBRACE] = 816,
        [anon_sym_return] = 816,
        [anon_sym_COLON_EQ] = 816,
        [anon_sym_for] = 816,
        [anon_sym_if] = 816,
        [anon_sym_BANG] = 816,
        [sym__line_break] = 12,
        [sym_string] = 816,
        [sym__identifier] = 816,
        [sym_number] = 816,
        [sym_comment] = 12,
    },
    [312] = {
        [aux_sym_return_statement_repeat1] = 78,
        [anon_sym_LPAREN] = 78,
        [anon_sym_SEMI] = 78,
        [anon_sym_STAR] = 78,
        [anon_sym_COMMA] = 78,
        [anon_sym_DOT] = 78,
        [anon_sym_SLASH] = 78,
        [anon_sym_PLUS] = 78,
        [anon_sym_DASH] = 78,
        [anon_sym_PIPE_PIPE] = 78,
        [anon_sym_AMP_AMP] = 78,
        [anon_sym_EQ_EQ] = 78,
        [anon_sym_LT_EQ] = 78,
        [anon_sym_LT] = 78,
        [anon_sym_GT_EQ] = 78,
        [anon_sym_GT] = 78,
        [sym__line_break] = 78,
        [sym_comment] = 12,
    },
    [313] = {
        [aux_sym_return_statement_repeat1] = 602,
        [anon_sym_LPAREN] = 602,
        [anon_sym_SEMI] = 602,
        [anon_sym_STAR] = 602,
        [anon_sym_COMMA] = 602,
        [anon_sym_DOT] = 602,
        [anon_sym_SLASH] = 602,
        [anon_sym_PLUS] = 602,
        [anon_sym_DASH] = 602,
        [anon_sym_PIPE_PIPE] = 602,
        [anon_sym_AMP_AMP] = 602,
        [anon_sym_EQ_EQ] = 602,
        [anon_sym_LT_EQ] = 602,
        [anon_sym_LT] = 602,
        [anon_sym_GT_EQ] = 602,
        [anon_sym_GT] = 602,
        [sym__line_break] = 602,
        [sym_comment] = 12,
    },
    [314] = {
        [anon_sym_SEMI] = 822,
        [sym__line_break] = 824,
        [sym_comment] = 12,
    },
    [315] = {
        [sym__expression] = 826,
        [sym_call_expression] = 630,
        [sym_selector_expression] = 630,
        [sym_math_op] = 630,
        [sym_bool_op] = 630,
        [sym_var_name] = 630,
        [anon_sym_RPAREN] = 828,
        [anon_sym_BANG] = 634,
        [sym__line_break] = 12,
        [sym_string] = 630,
        [sym__identifier] = 636,
        [sym_number] = 630,
        [sym_comment] = 12,
    },
    [316] = {
        [sym_var_declaration] = 830,
        [sym__statement] = 830,
        [sym_return_statement] = 830,
        [sym_short_var_declaration] = 830,
        [sym_range_statement] = 830,
        [sym_if_statement] = 830,
        [sym_expression_statement] = 830,
        [sym__expression] = 830,
        [sym_call_expression] = 830,
        [sym_selector_expression] = 830,
        [sym_math_op] = 830,
        [sym_bool_op] = 830,
        [sym_var_name] = 830,
        [aux_sym_block_statement_repeat1] = 830,
        [anon_sym_var] = 830,
        [anon_sym_RBRACE] = 830,
        [anon_sym_return] = 830,
        [anon_sym_COLON_EQ] = 830,
        [anon_sym_for] = 830,
        [anon_sym_if] = 830,
        [anon_sym_BANG] = 830,
        [sym__line_break] = 12,
        [sym_string] = 830,
        [sym__identifier] = 830,
        [sym_number] = 830,
        [sym_comment] = 12,
    },
    [317] = {
        [sym__expression] = 832,
        [sym_call_expression] = 574,
        [sym_selector_expression] = 574,
        [sym_math_op] = 574,
        [sym_bool_op] = 574,
        [sym_var_name] = 574,
        [anon_sym_BANG] = 578,
        [sym__line_break] = 12,
        [sym_string] = 574,
        [sym__identifier] = 582,
        [sym_number] = 574,
        [sym_comment] = 12,
    },
    [318] = {
        [sym__expression] = 834,
        [sym_call_expression] = 574,
        [sym_selector_expression] = 574,
        [sym_math_op] = 574,
        [sym_bool_op] = 574,
        [sym_var_name] = 574,
        [anon_sym_BANG] = 578,
        [sym__line_break] = 12,
        [sym_string] = 574,
        [sym__identifier] = 582,
        [sym_number] = 574,
        [sym_comment] = 12,
    },
    [319] = {
        [sym_var_name] = 836,
        [sym__line_break] = 12,
        [sym__identifier] = 582,
        [sym_comment] = 12,
    },
    [320] = {
        [sym__expression] = 838,
        [sym_call_expression] = 574,
        [sym_selector_expression] = 574,
        [sym_math_op] = 574,
        [sym_bool_op] = 574,
        [sym_var_name] = 574,
        [anon_sym_BANG] = 578,
        [sym__line_break] = 12,
        [sym_string] = 574,
        [sym__identifier] = 582,
        [sym_number] = 574,
        [sym_comment] = 12,
    },
    [321] = {
        [sym__expression] = 840,
        [sym_call_expression] = 574,
        [sym_selector_expression] = 574,
        [sym_math_op] = 574,
        [sym_bool_op] = 574,
        [sym_var_name] = 574,
        [anon_sym_BANG] = 578,
        [sym__line_break] = 12,
        [sym_string] = 574,
        [sym__identifier] = 582,
        [sym_number] = 574,
        [sym_comment] = 12,
    },
    [322] = {
        [sym__expression] = 842,
        [sym_call_expression] = 574,
        [sym_selector_expression] = 574,
        [sym_math_op] = 574,
        [sym_bool_op] = 574,
        [sym_var_name] = 574,
        [anon_sym_BANG] = 578,
        [sym__line_break] = 12,
        [sym_string] = 574,
        [sym__identifier] = 582,
        [sym_number] = 574,
        [sym_comment] = 12,
    },
    [323] = {
        [sym__expression] = 844,
        [sym_call_expression] = 574,
        [sym_selector_expression] = 574,
        [sym_math_op] = 574,
        [sym_bool_op] = 574,
        [sym_var_name] = 574,
        [anon_sym_BANG] = 578,
        [sym__line_break] = 12,
        [sym_string] = 574,
        [sym__identifier] = 582,
        [sym_number] = 574,
        [sym_comment] = 12,
    },
    [324] = {
        [sym_var_declaration] = 830,
        [sym__statement] = 830,
        [sym_return_statement] = 830,
        [sym_short_var_declaration] = 830,
        [sym_range_statement] = 830,
        [sym_if_statement] = 830,
        [sym_expression_statement] = 830,
        [sym__expression] = 830,
        [sym_call_expression] = 830,
        [sym_selector_expression] = 830,
        [sym_math_op] = 830,
        [sym_bool_op] = 830,
        [sym_var_name] = 830,
        [aux_sym_block_statement_repeat1] = 830,
        [aux_sym_return_statement_repeat1] = 846,
        [anon_sym_LPAREN] = 846,
        [anon_sym_SEMI] = 846,
        [anon_sym_var] = 830,
        [anon_sym_RBRACE] = 830,
        [anon_sym_STAR] = 846,
        [anon_sym_return] = 830,
        [anon_sym_COMMA] = 846,
        [anon_sym_COLON_EQ] = 830,
        [anon_sym_for] = 830,
        [anon_sym_if] = 830,
        [anon_sym_DOT] = 846,
        [anon_sym_SLASH] = 846,
        [anon_sym_PLUS] = 846,
        [anon_sym_DASH] = 846,
        [anon_sym_PIPE_PIPE] = 846,
        [anon_sym_AMP_AMP] = 846,
        [anon_sym_EQ_EQ] = 846,
        [anon_sym_LT_EQ] = 846,
        [anon_sym_LT] = 846,
        [anon_sym_GT_EQ] = 846,
        [anon_sym_GT] = 846,
        [anon_sym_BANG] = 830,
        [sym__line_break] = 12,
        [sym_string] = 830,
        [sym__identifier] = 830,
        [sym_number] = 830,
        [sym_comment] = 12,
    },
    [325] = {
        [aux_sym_return_statement_repeat1] = 654,
        [anon_sym_LPAREN] = 654,
        [anon_sym_SEMI] = 654,
        [anon_sym_STAR] = 654,
        [anon_sym_COMMA] = 654,
        [anon_sym_DOT] = 654,
        [anon_sym_SLASH] = 654,
        [anon_sym_PLUS] = 654,
        [anon_sym_DASH] = 654,
        [anon_sym_PIPE_PIPE] = 654,
        [anon_sym_AMP_AMP] = 654,
        [anon_sym_EQ_EQ] = 654,
        [anon_sym_LT_EQ] = 654,
        [anon_sym_LT] = 654,
        [anon_sym_GT_EQ] = 654,
        [anon_sym_GT] = 654,
        [sym__line_break] = 654,
        [sym_comment] = 12,
    },
    [326] = {
        [aux_sym_return_statement_repeat1] = 656,
        [anon_sym_LPAREN] = 656,
        [anon_sym_SEMI] = 656,
        [anon_sym_STAR] = 656,
        [anon_sym_COMMA] = 656,
        [anon_sym_DOT] = 656,
        [anon_sym_SLASH] = 656,
        [anon_sym_PLUS] = 656,
        [anon_sym_DASH] = 656,
        [anon_sym_PIPE_PIPE] = 656,
        [anon_sym_AMP_AMP] = 656,
        [anon_sym_EQ_EQ] = 812,
        [anon_sym_LT_EQ] = 812,
        [anon_sym_LT] = 812,
        [anon_sym_GT_EQ] = 812,
        [anon_sym_GT] = 812,
        [sym__line_break] = 656,
        [sym_comment] = 12,
    },
    [327] = {
        [aux_sym_return_statement_repeat1] = 656,
        [anon_sym_LPAREN] = 656,
        [anon_sym_SEMI] = 656,
        [anon_sym_STAR] = 800,
        [anon_sym_COMMA] = 656,
        [anon_sym_DOT] = 656,
        [anon_sym_SLASH] = 800,
        [anon_sym_PLUS] = 656,
        [anon_sym_DASH] = 656,
        [anon_sym_PIPE_PIPE] = 656,
        [anon_sym_AMP_AMP] = 810,
        [anon_sym_EQ_EQ] = 812,
        [anon_sym_LT_EQ] = 812,
        [anon_sym_LT] = 812,
        [anon_sym_GT_EQ] = 812,
        [anon_sym_GT] = 812,
        [sym__line_break] = 656,
        [sym_comment] = 12,
    },
    [328] = {
        [aux_sym_return_statement_repeat1] = 658,
        [anon_sym_LPAREN] = 658,
        [anon_sym_SEMI] = 658,
        [anon_sym_STAR] = 800,
        [anon_sym_COMMA] = 658,
        [anon_sym_DOT] = 658,
        [anon_sym_SLASH] = 800,
        [anon_sym_PLUS] = 658,
        [anon_sym_DASH] = 658,
        [anon_sym_PIPE_PIPE] = 658,
        [anon_sym_AMP_AMP] = 810,
        [anon_sym_EQ_EQ] = 812,
        [anon_sym_LT_EQ] = 812,
        [anon_sym_LT] = 812,
        [anon_sym_GT_EQ] = 812,
        [anon_sym_GT] = 812,
        [sym__line_break] = 658,
        [sym_comment] = 12,
    },
    [329] = {
        [aux_sym_return_statement_repeat1] = 658,
        [anon_sym_LPAREN] = 658,
        [anon_sym_SEMI] = 658,
        [anon_sym_STAR] = 658,
        [anon_sym_COMMA] = 658,
        [anon_sym_DOT] = 658,
        [anon_sym_SLASH] = 658,
        [anon_sym_PLUS] = 658,
        [anon_sym_DASH] = 658,
        [anon_sym_PIPE_PIPE] = 658,
        [anon_sym_AMP_AMP] = 658,
        [anon_sym_EQ_EQ] = 812,
        [anon_sym_LT_EQ] = 812,
        [anon_sym_LT] = 812,
        [anon_sym_GT_EQ] = 812,
        [anon_sym_GT] = 812,
        [sym__line_break] = 658,
        [sym_comment] = 12,
    },
    [330] = {
        [aux_sym_return_statement_repeat1] = 660,
        [anon_sym_LPAREN] = 660,
        [anon_sym_SEMI] = 660,
        [anon_sym_STAR] = 660,
        [anon_sym_COMMA] = 660,
        [anon_sym_DOT] = 660,
        [anon_sym_SLASH] = 660,
        [anon_sym_PLUS] = 660,
        [anon_sym_DASH] = 660,
        [anon_sym_PIPE_PIPE] = 660,
        [anon_sym_AMP_AMP] = 660,
        [anon_sym_EQ_EQ] = 660,
        [anon_sym_LT_EQ] = 660,
        [anon_sym_LT] = 660,
        [anon_sym_GT_EQ] = 660,
        [anon_sym_GT] = 660,
        [sym__line_break] = 660,
        [sym_comment] = 12,
    },
    [331] = {
        [aux_sym_return_statement_repeat1] = 848,
        [anon_sym_LPAREN] = 796,
        [anon_sym_SEMI] = 714,
        [anon_sym_STAR] = 800,
        [anon_sym_COMMA] = 802,
        [anon_sym_DOT] = 804,
        [anon_sym_SLASH] = 800,
        [anon_sym_PLUS] = 806,
        [anon_sym_DASH] = 806,
        [anon_sym_PIPE_PIPE] = 808,
        [anon_sym_AMP_AMP] = 810,
        [anon_sym_EQ_EQ] = 812,
        [anon_sym_LT_EQ] = 812,
        [anon_sym_LT] = 812,
        [anon_sym_GT_EQ] = 812,
        [anon_sym_GT] = 812,
        [sym__line_break] = 714,
        [sym_comment] = 12,
    },
    [332] = {
        [anon_sym_SEMI] = 716,
        [sym__line_break] = 716,
        [sym_comment] = 12,
    },
    [333] = {
        [aux_sym_return_statement_repeat1] = 850,
        [anon_sym_LPAREN] = 668,
        [anon_sym_RPAREN] = 852,
        [anon_sym_STAR] = 672,
        [anon_sym_COMMA] = 674,
        [anon_sym_DOT] = 676,
        [anon_sym_SLASH] = 672,
        [anon_sym_PLUS] = 678,
        [anon_sym_DASH] = 678,
        [anon_sym_PIPE_PIPE] = 680,
        [anon_sym_AMP_AMP] = 682,
        [anon_sym_EQ_EQ] = 684,
        [anon_sym_LT_EQ] = 684,
        [anon_sym_LT] = 684,
        [anon_sym_GT_EQ] = 684,
        [anon_sym_GT] = 684,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [334] = {
        [aux_sym_return_statement_repeat1] = 686,
        [anon_sym_LPAREN] = 686,
        [anon_sym_SEMI] = 686,
        [anon_sym_STAR] = 686,
        [anon_sym_COMMA] = 686,
        [anon_sym_DOT] = 686,
        [anon_sym_SLASH] = 686,
        [anon_sym_PLUS] = 686,
        [anon_sym_DASH] = 686,
        [anon_sym_PIPE_PIPE] = 686,
        [anon_sym_AMP_AMP] = 686,
        [anon_sym_EQ_EQ] = 686,
        [anon_sym_LT_EQ] = 686,
        [anon_sym_LT] = 686,
        [anon_sym_GT_EQ] = 686,
        [anon_sym_GT] = 686,
        [sym__line_break] = 686,
        [sym_comment] = 12,
    },
    [335] = {
        [anon_sym_RPAREN] = 854,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [336] = {
        [aux_sym_return_statement_repeat1] = 696,
        [anon_sym_LPAREN] = 696,
        [anon_sym_SEMI] = 696,
        [anon_sym_STAR] = 696,
        [anon_sym_COMMA] = 696,
        [anon_sym_DOT] = 696,
        [anon_sym_SLASH] = 696,
        [anon_sym_PLUS] = 696,
        [anon_sym_DASH] = 696,
        [anon_sym_PIPE_PIPE] = 696,
        [anon_sym_AMP_AMP] = 696,
        [anon_sym_EQ_EQ] = 696,
        [anon_sym_LT_EQ] = 696,
        [anon_sym_LT] = 696,
        [anon_sym_GT_EQ] = 696,
        [anon_sym_GT] = 696,
        [sym__line_break] = 696,
        [sym_comment] = 12,
    },
    [337] = {
        [aux_sym_return_statement_repeat1] = 724,
        [anon_sym_LPAREN] = 724,
        [anon_sym_SEMI] = 724,
        [anon_sym_STAR] = 724,
        [anon_sym_COMMA] = 724,
        [anon_sym_DOT] = 724,
        [anon_sym_SLASH] = 724,
        [anon_sym_PLUS] = 724,
        [anon_sym_DASH] = 724,
        [anon_sym_PIPE_PIPE] = 724,
        [anon_sym_AMP_AMP] = 724,
        [anon_sym_EQ_EQ] = 724,
        [anon_sym_LT_EQ] = 724,
        [anon_sym_LT] = 724,
        [anon_sym_GT_EQ] = 724,
        [anon_sym_GT] = 724,
        [sym__line_break] = 724,
        [sym_comment] = 12,
    },
    [338] = {
        [sym_var_declaration] = 856,
        [sym__statement] = 856,
        [sym_return_statement] = 856,
        [sym_short_var_declaration] = 856,
        [sym_range_statement] = 856,
        [sym_if_statement] = 856,
        [sym_expression_statement] = 856,
        [sym__expression] = 856,
        [sym_call_expression] = 856,
        [sym_selector_expression] = 856,
        [sym_math_op] = 856,
        [sym_bool_op] = 856,
        [sym_var_name] = 856,
        [aux_sym_block_statement_repeat1] = 856,
        [anon_sym_var] = 856,
        [anon_sym_RBRACE] = 856,
        [anon_sym_return] = 856,
        [anon_sym_COLON_EQ] = 856,
        [anon_sym_for] = 856,
        [anon_sym_if] = 856,
        [anon_sym_BANG] = 856,
        [sym__line_break] = 12,
        [sym_string] = 856,
        [sym__identifier] = 856,
        [sym_number] = 856,
        [sym_comment] = 12,
    },
    [339] = {
        [sym_var_declaration] = 856,
        [sym__statement] = 856,
        [sym_return_statement] = 856,
        [sym_short_var_declaration] = 856,
        [sym_range_statement] = 856,
        [sym_if_statement] = 856,
        [sym_expression_statement] = 856,
        [sym__expression] = 856,
        [sym_call_expression] = 856,
        [sym_selector_expression] = 856,
        [sym_math_op] = 856,
        [sym_bool_op] = 856,
        [sym_var_name] = 856,
        [aux_sym_block_statement_repeat1] = 856,
        [anon_sym_SEMI] = 858,
        [anon_sym_var] = 856,
        [anon_sym_RBRACE] = 856,
        [anon_sym_return] = 856,
        [anon_sym_COLON_EQ] = 856,
        [anon_sym_for] = 856,
        [anon_sym_if] = 856,
        [anon_sym_BANG] = 856,
        [sym__line_break] = 12,
        [sym_string] = 856,
        [sym__identifier] = 856,
        [sym_number] = 856,
        [sym_comment] = 12,
    },
    [340] = {
        [sym__type_expression] = 860,
        [sym_pointer_type] = 862,
        [sym_map_type] = 862,
        [sym_slice_type] = 862,
        [sym_struct_type] = 862,
        [sym_interface_type] = 862,
        [sym_type_name] = 862,
        [anon_sym_EQ] = 864,
        [anon_sym_STAR] = 866,
        [anon_sym_map] = 868,
        [anon_sym_LBRACK] = 870,
        [anon_sym_struct] = 872,
        [anon_sym_interface] = 874,
        [sym__line_break] = 12,
        [sym__identifier] = 876,
        [sym_comment] = 12,
    },
    [341] = {
        [sym__type_expression] = 78,
        [sym_pointer_type] = 78,
        [sym_map_type] = 78,
        [sym_slice_type] = 78,
        [sym_struct_type] = 78,
        [sym_interface_type] = 78,
        [sym_type_name] = 78,
        [anon_sym_EQ] = 78,
        [anon_sym_STAR] = 78,
        [anon_sym_map] = 78,
        [anon_sym_LBRACK] = 78,
        [anon_sym_struct] = 78,
        [anon_sym_interface] = 78,
        [sym__line_break] = 12,
        [sym__identifier] = 78,
        [sym_comment] = 12,
    },
    [342] = {
        [anon_sym_SEMI] = 878,
        [anon_sym_EQ] = 880,
        [sym__line_break] = 882,
        [sym_comment] = 12,
    },
    [343] = {
        [anon_sym_SEMI] = 180,
        [anon_sym_EQ] = 180,
        [sym__line_break] = 180,
        [sym_comment] = 12,
    },
    [344] = {
        [sym__expression] = 884,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [345] = {
        [sym__type_expression] = 886,
        [sym_pointer_type] = 862,
        [sym_map_type] = 862,
        [sym_slice_type] = 862,
        [sym_struct_type] = 862,
        [sym_interface_type] = 862,
        [sym_type_name] = 862,
        [anon_sym_STAR] = 866,
        [anon_sym_map] = 868,
        [anon_sym_LBRACK] = 870,
        [anon_sym_struct] = 872,
        [anon_sym_interface] = 874,
        [sym__line_break] = 12,
        [sym__identifier] = 876,
        [sym_comment] = 12,
    },
    [346] = {
        [anon_sym_LBRACK] = 888,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [347] = {
        [anon_sym_RBRACK] = 890,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [348] = {
        [anon_sym_LBRACE] = 892,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [349] = {
        [anon_sym_LBRACE] = 894,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [350] = {
        [anon_sym_SEMI] = 126,
        [anon_sym_EQ] = 126,
        [sym__line_break] = 126,
        [sym_comment] = 12,
    },
    [351] = {
        [sym_var_name] = 202,
        [aux_sym_interface_type_repeat1] = 896,
        [anon_sym_RBRACE] = 898,
        [sym__line_break] = 12,
        [sym__identifier] = 72,
        [sym_comment] = 12,
    },
    [352] = {
        [anon_sym_RBRACE] = 900,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [353] = {
        [anon_sym_SEMI] = 214,
        [anon_sym_EQ] = 214,
        [sym__line_break] = 214,
        [sym_comment] = 12,
    },
    [354] = {
        [anon_sym_SEMI] = 216,
        [anon_sym_EQ] = 216,
        [sym__line_break] = 216,
        [sym_comment] = 12,
    },
    [355] = {
        [sym_var_name] = 332,
        [aux_sym_struct_type_repeat1] = 902,
        [anon_sym_RBRACE] = 904,
        [sym__line_break] = 12,
        [sym__identifier] = 338,
        [sym_comment] = 12,
    },
    [356] = {
        [anon_sym_RBRACE] = 906,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [357] = {
        [anon_sym_SEMI] = 358,
        [anon_sym_EQ] = 358,
        [sym__line_break] = 358,
        [sym_comment] = 12,
    },
    [358] = {
        [anon_sym_SEMI] = 360,
        [anon_sym_EQ] = 360,
        [sym__line_break] = 360,
        [sym_comment] = 12,
    },
    [359] = {
        [sym__type_expression] = 908,
        [sym_pointer_type] = 862,
        [sym_map_type] = 862,
        [sym_slice_type] = 862,
        [sym_struct_type] = 862,
        [sym_interface_type] = 862,
        [sym_type_name] = 862,
        [anon_sym_STAR] = 866,
        [anon_sym_map] = 868,
        [anon_sym_LBRACK] = 870,
        [anon_sym_struct] = 872,
        [anon_sym_interface] = 874,
        [sym__line_break] = 12,
        [sym__identifier] = 876,
        [sym_comment] = 12,
    },
    [360] = {
        [anon_sym_SEMI] = 390,
        [anon_sym_EQ] = 390,
        [sym__line_break] = 390,
        [sym_comment] = 12,
    },
    [361] = {
        [sym__type_expression] = 910,
        [sym_pointer_type] = 394,
        [sym_map_type] = 394,
        [sym_slice_type] = 394,
        [sym_struct_type] = 394,
        [sym_interface_type] = 394,
        [sym_type_name] = 394,
        [anon_sym_STAR] = 396,
        [anon_sym_map] = 398,
        [anon_sym_LBRACK] = 400,
        [anon_sym_struct] = 402,
        [anon_sym_interface] = 404,
        [sym__line_break] = 12,
        [sym__identifier] = 406,
        [sym_comment] = 12,
    },
    [362] = {
        [anon_sym_RBRACK] = 912,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [363] = {
        [sym__type_expression] = 914,
        [sym_pointer_type] = 862,
        [sym_map_type] = 862,
        [sym_slice_type] = 862,
        [sym_struct_type] = 862,
        [sym_interface_type] = 862,
        [sym_type_name] = 862,
        [anon_sym_STAR] = 866,
        [anon_sym_map] = 868,
        [anon_sym_LBRACK] = 870,
        [anon_sym_struct] = 872,
        [anon_sym_interface] = 874,
        [sym__line_break] = 12,
        [sym__identifier] = 876,
        [sym_comment] = 12,
    },
    [364] = {
        [anon_sym_SEMI] = 440,
        [anon_sym_EQ] = 440,
        [sym__line_break] = 440,
        [sym_comment] = 12,
    },
    [365] = {
        [anon_sym_SEMI] = 442,
        [anon_sym_EQ] = 442,
        [sym__line_break] = 442,
        [sym_comment] = 12,
    },
    [366] = {
        [anon_sym_LPAREN] = 540,
        [anon_sym_SEMI] = 916,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 546,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 548,
        [anon_sym_DASH] = 548,
        [anon_sym_PIPE_PIPE] = 550,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 918,
        [sym_comment] = 12,
    },
    [367] = {
        [sym_var_declaration] = 920,
        [sym__statement] = 920,
        [sym_return_statement] = 920,
        [sym_short_var_declaration] = 920,
        [sym_range_statement] = 920,
        [sym_if_statement] = 920,
        [sym_expression_statement] = 920,
        [sym__expression] = 920,
        [sym_call_expression] = 920,
        [sym_selector_expression] = 920,
        [sym_math_op] = 920,
        [sym_bool_op] = 920,
        [sym_var_name] = 920,
        [aux_sym_block_statement_repeat1] = 920,
        [anon_sym_var] = 920,
        [anon_sym_RBRACE] = 920,
        [anon_sym_return] = 920,
        [anon_sym_COLON_EQ] = 920,
        [anon_sym_for] = 920,
        [anon_sym_if] = 920,
        [anon_sym_BANG] = 920,
        [sym__line_break] = 12,
        [sym_string] = 920,
        [sym__identifier] = 920,
        [sym_number] = 920,
        [sym_comment] = 12,
    },
    [368] = {
        [sym_var_declaration] = 920,
        [sym__statement] = 920,
        [sym_return_statement] = 920,
        [sym_short_var_declaration] = 920,
        [sym_range_statement] = 920,
        [sym_if_statement] = 920,
        [sym_expression_statement] = 920,
        [sym__expression] = 920,
        [sym_call_expression] = 920,
        [sym_selector_expression] = 920,
        [sym_math_op] = 920,
        [sym_bool_op] = 920,
        [sym_var_name] = 920,
        [aux_sym_block_statement_repeat1] = 920,
        [anon_sym_LPAREN] = 922,
        [anon_sym_SEMI] = 922,
        [anon_sym_var] = 920,
        [anon_sym_RBRACE] = 920,
        [anon_sym_STAR] = 922,
        [anon_sym_return] = 920,
        [anon_sym_COLON_EQ] = 920,
        [anon_sym_for] = 920,
        [anon_sym_if] = 920,
        [anon_sym_DOT] = 922,
        [anon_sym_SLASH] = 922,
        [anon_sym_PLUS] = 922,
        [anon_sym_DASH] = 922,
        [anon_sym_PIPE_PIPE] = 922,
        [anon_sym_AMP_AMP] = 922,
        [anon_sym_EQ_EQ] = 922,
        [anon_sym_LT_EQ] = 922,
        [anon_sym_LT] = 922,
        [anon_sym_GT_EQ] = 922,
        [anon_sym_GT] = 922,
        [anon_sym_BANG] = 920,
        [sym__line_break] = 12,
        [sym_string] = 920,
        [sym__identifier] = 920,
        [sym_number] = 920,
        [sym_comment] = 12,
    },
    [369] = {
        [sym_var_declaration] = 924,
        [sym__statement] = 924,
        [sym_return_statement] = 924,
        [sym_short_var_declaration] = 924,
        [sym_range_statement] = 924,
        [sym_if_statement] = 924,
        [sym_expression_statement] = 924,
        [sym__expression] = 924,
        [sym_call_expression] = 924,
        [sym_selector_expression] = 924,
        [sym_math_op] = 924,
        [sym_bool_op] = 924,
        [sym_var_name] = 924,
        [aux_sym_block_statement_repeat1] = 924,
        [anon_sym_var] = 924,
        [anon_sym_RBRACE] = 924,
        [anon_sym_return] = 924,
        [anon_sym_COLON_EQ] = 924,
        [anon_sym_for] = 924,
        [anon_sym_if] = 924,
        [anon_sym_BANG] = 924,
        [sym__line_break] = 12,
        [sym_string] = 924,
        [sym__identifier] = 924,
        [sym_number] = 924,
        [sym_comment] = 12,
    },
    [370] = {
        [sym__expression] = 926,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [371] = {
        [sym_var_declaration] = 924,
        [sym__statement] = 924,
        [sym_return_statement] = 924,
        [sym_short_var_declaration] = 924,
        [sym_range_statement] = 924,
        [sym_if_statement] = 924,
        [sym_expression_statement] = 924,
        [sym__expression] = 924,
        [sym_call_expression] = 924,
        [sym_selector_expression] = 924,
        [sym_math_op] = 924,
        [sym_bool_op] = 924,
        [sym_var_name] = 924,
        [aux_sym_block_statement_repeat1] = 924,
        [anon_sym_SEMI] = 928,
        [anon_sym_var] = 924,
        [anon_sym_EQ] = 928,
        [anon_sym_RBRACE] = 924,
        [anon_sym_return] = 924,
        [anon_sym_COLON_EQ] = 924,
        [anon_sym_for] = 924,
        [anon_sym_if] = 924,
        [anon_sym_BANG] = 924,
        [sym__line_break] = 12,
        [sym_string] = 924,
        [sym__identifier] = 924,
        [sym_number] = 924,
        [sym_comment] = 12,
    },
    [372] = {
        [anon_sym_LPAREN] = 540,
        [anon_sym_SEMI] = 930,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 546,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 548,
        [anon_sym_DASH] = 548,
        [anon_sym_PIPE_PIPE] = 550,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 932,
        [sym_comment] = 12,
    },
    [373] = {
        [sym_var_declaration] = 934,
        [sym__statement] = 934,
        [sym_return_statement] = 934,
        [sym_short_var_declaration] = 934,
        [sym_range_statement] = 934,
        [sym_if_statement] = 934,
        [sym_expression_statement] = 934,
        [sym__expression] = 934,
        [sym_call_expression] = 934,
        [sym_selector_expression] = 934,
        [sym_math_op] = 934,
        [sym_bool_op] = 934,
        [sym_var_name] = 934,
        [aux_sym_block_statement_repeat1] = 934,
        [anon_sym_var] = 934,
        [anon_sym_RBRACE] = 934,
        [anon_sym_return] = 934,
        [anon_sym_COLON_EQ] = 934,
        [anon_sym_for] = 934,
        [anon_sym_if] = 934,
        [anon_sym_BANG] = 934,
        [sym__line_break] = 12,
        [sym_string] = 934,
        [sym__identifier] = 934,
        [sym_number] = 934,
        [sym_comment] = 12,
    },
    [374] = {
        [sym_var_declaration] = 934,
        [sym__statement] = 934,
        [sym_return_statement] = 934,
        [sym_short_var_declaration] = 934,
        [sym_range_statement] = 934,
        [sym_if_statement] = 934,
        [sym_expression_statement] = 934,
        [sym__expression] = 934,
        [sym_call_expression] = 934,
        [sym_selector_expression] = 934,
        [sym_math_op] = 934,
        [sym_bool_op] = 934,
        [sym_var_name] = 934,
        [aux_sym_block_statement_repeat1] = 934,
        [anon_sym_LPAREN] = 936,
        [anon_sym_SEMI] = 936,
        [anon_sym_var] = 934,
        [anon_sym_RBRACE] = 934,
        [anon_sym_STAR] = 936,
        [anon_sym_return] = 934,
        [anon_sym_COLON_EQ] = 934,
        [anon_sym_for] = 934,
        [anon_sym_if] = 934,
        [anon_sym_DOT] = 936,
        [anon_sym_SLASH] = 936,
        [anon_sym_PLUS] = 936,
        [anon_sym_DASH] = 936,
        [anon_sym_PIPE_PIPE] = 936,
        [anon_sym_AMP_AMP] = 936,
        [anon_sym_EQ_EQ] = 936,
        [anon_sym_LT_EQ] = 936,
        [anon_sym_LT] = 936,
        [anon_sym_GT_EQ] = 936,
        [anon_sym_GT] = 936,
        [anon_sym_BANG] = 934,
        [sym__line_break] = 12,
        [sym_string] = 934,
        [sym__identifier] = 934,
        [sym_number] = 934,
        [sym_comment] = 12,
    },
    [375] = {
        [anon_sym_SEMI] = 664,
        [sym__line_break] = 664,
        [sym_comment] = 12,
    },
    [376] = {
        [anon_sym_COLON_EQ] = 938,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [377] = {
        [sym_var_name] = 940,
        [sym__line_break] = 12,
        [sym__identifier] = 942,
        [sym_comment] = 12,
    },
    [378] = {
        [sym__expression] = 944,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [379] = {
        [anon_sym_LPAREN] = 540,
        [anon_sym_SEMI] = 946,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 546,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 548,
        [anon_sym_DASH] = 548,
        [anon_sym_PIPE_PIPE] = 550,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 948,
        [sym_comment] = 12,
    },
    [380] = {
        [sym_var_declaration] = 950,
        [sym__statement] = 950,
        [sym_return_statement] = 950,
        [sym_short_var_declaration] = 950,
        [sym_range_statement] = 950,
        [sym_if_statement] = 950,
        [sym_expression_statement] = 950,
        [sym__expression] = 950,
        [sym_call_expression] = 950,
        [sym_selector_expression] = 950,
        [sym_math_op] = 950,
        [sym_bool_op] = 950,
        [sym_var_name] = 950,
        [aux_sym_block_statement_repeat1] = 950,
        [anon_sym_var] = 950,
        [anon_sym_RBRACE] = 950,
        [anon_sym_return] = 950,
        [anon_sym_COLON_EQ] = 950,
        [anon_sym_for] = 950,
        [anon_sym_if] = 950,
        [anon_sym_BANG] = 950,
        [sym__line_break] = 12,
        [sym_string] = 950,
        [sym__identifier] = 950,
        [sym_number] = 950,
        [sym_comment] = 12,
    },
    [381] = {
        [sym_var_declaration] = 950,
        [sym__statement] = 950,
        [sym_return_statement] = 950,
        [sym_short_var_declaration] = 950,
        [sym_range_statement] = 950,
        [sym_if_statement] = 950,
        [sym_expression_statement] = 950,
        [sym__expression] = 950,
        [sym_call_expression] = 950,
        [sym_selector_expression] = 950,
        [sym_math_op] = 950,
        [sym_bool_op] = 950,
        [sym_var_name] = 950,
        [aux_sym_block_statement_repeat1] = 950,
        [anon_sym_LPAREN] = 952,
        [anon_sym_SEMI] = 952,
        [anon_sym_var] = 950,
        [anon_sym_RBRACE] = 950,
        [anon_sym_STAR] = 952,
        [anon_sym_return] = 950,
        [anon_sym_COLON_EQ] = 950,
        [anon_sym_for] = 950,
        [anon_sym_if] = 950,
        [anon_sym_DOT] = 952,
        [anon_sym_SLASH] = 952,
        [anon_sym_PLUS] = 952,
        [anon_sym_DASH] = 952,
        [anon_sym_PIPE_PIPE] = 952,
        [anon_sym_AMP_AMP] = 952,
        [anon_sym_EQ_EQ] = 952,
        [anon_sym_LT_EQ] = 952,
        [anon_sym_LT] = 952,
        [anon_sym_GT_EQ] = 952,
        [anon_sym_GT] = 952,
        [anon_sym_BANG] = 950,
        [sym__line_break] = 12,
        [sym_string] = 950,
        [sym__identifier] = 950,
        [sym_number] = 950,
        [sym_comment] = 12,
    },
    [382] = {
        [aux_sym_short_var_declaration_repeat1] = 954,
        [anon_sym_COMMA] = 562,
        [anon_sym_COLON_EQ] = 196,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [383] = {
        [aux_sym_short_var_declaration_repeat1] = 78,
        [anon_sym_COMMA] = 78,
        [anon_sym_COLON_EQ] = 78,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [384] = {
        [anon_sym_COLON_EQ] = 200,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [385] = {
        [sym__expression] = 956,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [386] = {
        [anon_sym_LPAREN] = 540,
        [anon_sym_SEMI] = 958,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 546,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 548,
        [anon_sym_DASH] = 548,
        [anon_sym_PIPE_PIPE] = 550,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 960,
        [sym_comment] = 12,
    },
    [387] = {
        [sym_var_declaration] = 962,
        [sym__statement] = 962,
        [sym_return_statement] = 962,
        [sym_short_var_declaration] = 962,
        [sym_range_statement] = 962,
        [sym_if_statement] = 962,
        [sym_expression_statement] = 962,
        [sym__expression] = 962,
        [sym_call_expression] = 962,
        [sym_selector_expression] = 962,
        [sym_math_op] = 962,
        [sym_bool_op] = 962,
        [sym_var_name] = 962,
        [aux_sym_block_statement_repeat1] = 962,
        [anon_sym_var] = 962,
        [anon_sym_RBRACE] = 962,
        [anon_sym_return] = 962,
        [anon_sym_COLON_EQ] = 962,
        [anon_sym_for] = 962,
        [anon_sym_if] = 962,
        [anon_sym_BANG] = 962,
        [sym__line_break] = 12,
        [sym_string] = 962,
        [sym__identifier] = 962,
        [sym_number] = 962,
        [sym_comment] = 12,
    },
    [388] = {
        [sym_var_declaration] = 962,
        [sym__statement] = 962,
        [sym_return_statement] = 962,
        [sym_short_var_declaration] = 962,
        [sym_range_statement] = 962,
        [sym_if_statement] = 962,
        [sym_expression_statement] = 962,
        [sym__expression] = 962,
        [sym_call_expression] = 962,
        [sym_selector_expression] = 962,
        [sym_math_op] = 962,
        [sym_bool_op] = 962,
        [sym_var_name] = 962,
        [aux_sym_block_statement_repeat1] = 962,
        [anon_sym_LPAREN] = 964,
        [anon_sym_SEMI] = 964,
        [anon_sym_var] = 962,
        [anon_sym_RBRACE] = 962,
        [anon_sym_STAR] = 964,
        [anon_sym_return] = 962,
        [anon_sym_COLON_EQ] = 962,
        [anon_sym_for] = 962,
        [anon_sym_if] = 962,
        [anon_sym_DOT] = 964,
        [anon_sym_SLASH] = 964,
        [anon_sym_PLUS] = 964,
        [anon_sym_DASH] = 964,
        [anon_sym_PIPE_PIPE] = 964,
        [anon_sym_AMP_AMP] = 964,
        [anon_sym_EQ_EQ] = 964,
        [anon_sym_LT_EQ] = 964,
        [anon_sym_LT] = 964,
        [anon_sym_GT_EQ] = 964,
        [anon_sym_GT] = 964,
        [anon_sym_BANG] = 962,
        [sym__line_break] = 12,
        [sym_string] = 962,
        [sym__identifier] = 962,
        [sym_number] = 962,
        [sym_comment] = 12,
    },
    [389] = {
        [sym_var_declaration] = 966,
        [sym__statement] = 966,
        [sym_return_statement] = 966,
        [sym_short_var_declaration] = 966,
        [sym_range_statement] = 966,
        [sym_if_statement] = 966,
        [sym_expression_statement] = 966,
        [sym__expression] = 966,
        [sym_call_expression] = 966,
        [sym_selector_expression] = 966,
        [sym_math_op] = 966,
        [sym_bool_op] = 966,
        [sym_var_name] = 966,
        [aux_sym_block_statement_repeat1] = 966,
        [anon_sym_var] = 966,
        [anon_sym_RBRACE] = 966,
        [anon_sym_return] = 966,
        [anon_sym_COLON_EQ] = 966,
        [anon_sym_for] = 966,
        [anon_sym_if] = 966,
        [anon_sym_BANG] = 966,
        [sym__line_break] = 12,
        [sym_string] = 966,
        [sym__identifier] = 966,
        [sym_number] = 966,
        [sym_comment] = 12,
    },
    [390] = {
        [sym_var_declaration] = 966,
        [sym__statement] = 966,
        [sym_return_statement] = 966,
        [sym_short_var_declaration] = 966,
        [sym_range_statement] = 966,
        [sym_if_statement] = 966,
        [sym_expression_statement] = 966,
        [sym__expression] = 966,
        [sym_call_expression] = 966,
        [sym_selector_expression] = 966,
        [sym_math_op] = 966,
        [sym_bool_op] = 966,
        [sym_var_name] = 966,
        [aux_sym_block_statement_repeat1] = 966,
        [anon_sym_LPAREN] = 968,
        [anon_sym_SEMI] = 968,
        [anon_sym_var] = 966,
        [anon_sym_RBRACE] = 966,
        [anon_sym_STAR] = 968,
        [anon_sym_return] = 966,
        [anon_sym_COLON_EQ] = 966,
        [anon_sym_for] = 966,
        [anon_sym_if] = 966,
        [anon_sym_DOT] = 968,
        [anon_sym_SLASH] = 968,
        [anon_sym_PLUS] = 968,
        [anon_sym_DASH] = 968,
        [anon_sym_PIPE_PIPE] = 968,
        [anon_sym_AMP_AMP] = 968,
        [anon_sym_EQ_EQ] = 968,
        [anon_sym_LT_EQ] = 968,
        [anon_sym_LT] = 968,
        [anon_sym_GT_EQ] = 968,
        [anon_sym_GT] = 968,
        [anon_sym_BANG] = 966,
        [sym__line_break] = 12,
        [sym_string] = 966,
        [sym__identifier] = 966,
        [sym_number] = 966,
        [sym_comment] = 12,
    },
    [391] = {
        [anon_sym_RBRACE] = 970,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [392] = {
        [sym__declaration] = 972,
        [sym_type_declaration] = 972,
        [sym_var_declaration] = 972,
        [sym_func_declaration] = 972,
        [aux_sym_program_repeat2] = 972,
        [ts_builtin_sym_end] = 972,
        [anon_sym_type] = 972,
        [anon_sym_var] = 972,
        [anon_sym_func] = 972,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [393] = {
        [sym__declaration] = 972,
        [sym_type_declaration] = 972,
        [sym_var_declaration] = 972,
        [sym_func_declaration] = 972,
        [aux_sym_program_repeat2] = 972,
        [ts_builtin_sym_end] = 972,
        [anon_sym_type] = 972,
        [anon_sym_SEMI] = 974,
        [anon_sym_var] = 972,
        [anon_sym_func] = 972,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [394] = {
        [sym__type_expression] = 976,
        [sym_pointer_type] = 862,
        [sym_map_type] = 862,
        [sym_slice_type] = 862,
        [sym_struct_type] = 862,
        [sym_interface_type] = 862,
        [sym_type_name] = 862,
        [anon_sym_EQ] = 978,
        [anon_sym_STAR] = 866,
        [anon_sym_map] = 868,
        [anon_sym_LBRACK] = 870,
        [anon_sym_struct] = 872,
        [anon_sym_interface] = 874,
        [sym__line_break] = 12,
        [sym__identifier] = 876,
        [sym_comment] = 12,
    },
    [395] = {
        [anon_sym_SEMI] = 980,
        [anon_sym_EQ] = 982,
        [sym__line_break] = 984,
        [sym_comment] = 12,
    },
    [396] = {
        [sym__expression] = 986,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [397] = {
        [anon_sym_LPAREN] = 540,
        [anon_sym_SEMI] = 988,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 546,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 548,
        [anon_sym_DASH] = 548,
        [anon_sym_PIPE_PIPE] = 550,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 990,
        [sym_comment] = 12,
    },
    [398] = {
        [sym__declaration] = 920,
        [sym_type_declaration] = 920,
        [sym_var_declaration] = 920,
        [sym_func_declaration] = 920,
        [aux_sym_program_repeat2] = 920,
        [ts_builtin_sym_end] = 920,
        [anon_sym_type] = 920,
        [anon_sym_var] = 920,
        [anon_sym_func] = 920,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [399] = {
        [sym__declaration] = 920,
        [sym_type_declaration] = 920,
        [sym_var_declaration] = 920,
        [sym_func_declaration] = 920,
        [aux_sym_program_repeat2] = 920,
        [ts_builtin_sym_end] = 920,
        [anon_sym_LPAREN] = 992,
        [anon_sym_type] = 920,
        [anon_sym_SEMI] = 992,
        [anon_sym_var] = 920,
        [anon_sym_func] = 920,
        [anon_sym_STAR] = 992,
        [anon_sym_DOT] = 992,
        [anon_sym_SLASH] = 992,
        [anon_sym_PLUS] = 992,
        [anon_sym_DASH] = 992,
        [anon_sym_PIPE_PIPE] = 992,
        [anon_sym_AMP_AMP] = 992,
        [anon_sym_EQ_EQ] = 992,
        [anon_sym_LT_EQ] = 992,
        [anon_sym_LT] = 992,
        [anon_sym_GT_EQ] = 992,
        [anon_sym_GT] = 992,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [400] = {
        [sym__declaration] = 924,
        [sym_type_declaration] = 924,
        [sym_var_declaration] = 924,
        [sym_func_declaration] = 924,
        [aux_sym_program_repeat2] = 924,
        [ts_builtin_sym_end] = 924,
        [anon_sym_type] = 924,
        [anon_sym_var] = 924,
        [anon_sym_func] = 924,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [401] = {
        [sym__expression] = 994,
        [sym_call_expression] = 512,
        [sym_selector_expression] = 512,
        [sym_math_op] = 512,
        [sym_bool_op] = 512,
        [sym_var_name] = 512,
        [anon_sym_BANG] = 530,
        [sym__line_break] = 12,
        [sym_string] = 512,
        [sym__identifier] = 586,
        [sym_number] = 512,
        [sym_comment] = 12,
    },
    [402] = {
        [sym__declaration] = 924,
        [sym_type_declaration] = 924,
        [sym_var_declaration] = 924,
        [sym_func_declaration] = 924,
        [aux_sym_program_repeat2] = 924,
        [ts_builtin_sym_end] = 924,
        [anon_sym_type] = 924,
        [anon_sym_SEMI] = 996,
        [anon_sym_var] = 924,
        [anon_sym_EQ] = 996,
        [anon_sym_func] = 924,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [403] = {
        [anon_sym_LPAREN] = 540,
        [anon_sym_SEMI] = 998,
        [anon_sym_STAR] = 544,
        [anon_sym_DOT] = 546,
        [anon_sym_SLASH] = 544,
        [anon_sym_PLUS] = 548,
        [anon_sym_DASH] = 548,
        [anon_sym_PIPE_PIPE] = 550,
        [anon_sym_AMP_AMP] = 552,
        [anon_sym_EQ_EQ] = 554,
        [anon_sym_LT_EQ] = 554,
        [anon_sym_LT] = 554,
        [anon_sym_GT_EQ] = 554,
        [anon_sym_GT] = 554,
        [sym__line_break] = 1000,
        [sym_comment] = 12,
    },
    [404] = {
        [sym__declaration] = 934,
        [sym_type_declaration] = 934,
        [sym_var_declaration] = 934,
        [sym_func_declaration] = 934,
        [aux_sym_program_repeat2] = 934,
        [ts_builtin_sym_end] = 934,
        [anon_sym_type] = 934,
        [anon_sym_var] = 934,
        [anon_sym_func] = 934,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [405] = {
        [sym__declaration] = 934,
        [sym_type_declaration] = 934,
        [sym_var_declaration] = 934,
        [sym_func_declaration] = 934,
        [aux_sym_program_repeat2] = 934,
        [ts_builtin_sym_end] = 934,
        [anon_sym_LPAREN] = 1002,
        [anon_sym_type] = 934,
        [anon_sym_SEMI] = 1002,
        [anon_sym_var] = 934,
        [anon_sym_func] = 934,
        [anon_sym_STAR] = 1002,
        [anon_sym_DOT] = 1002,
        [anon_sym_SLASH] = 1002,
        [anon_sym_PLUS] = 1002,
        [anon_sym_DASH] = 1002,
        [anon_sym_PIPE_PIPE] = 1002,
        [anon_sym_AMP_AMP] = 1002,
        [anon_sym_EQ_EQ] = 1002,
        [anon_sym_LT_EQ] = 1002,
        [anon_sym_LT] = 1002,
        [anon_sym_GT_EQ] = 1002,
        [anon_sym_GT] = 1002,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [406] = {
        [sym__type_expression] = 1004,
        [sym_pointer_type] = 1006,
        [sym_map_type] = 1006,
        [sym_slice_type] = 1006,
        [sym_struct_type] = 1006,
        [sym_interface_type] = 1006,
        [sym_type_name] = 1006,
        [anon_sym_STAR] = 1008,
        [anon_sym_map] = 1010,
        [anon_sym_LBRACK] = 1012,
        [anon_sym_struct] = 1014,
        [anon_sym_interface] = 1016,
        [sym__line_break] = 12,
        [sym__identifier] = 1018,
        [sym_comment] = 12,
    },
    [407] = {
        [sym__type_expression] = 126,
        [sym_pointer_type] = 126,
        [sym_map_type] = 126,
        [sym_slice_type] = 126,
        [sym_struct_type] = 126,
        [sym_interface_type] = 126,
        [sym_type_name] = 126,
        [anon_sym_STAR] = 126,
        [anon_sym_map] = 126,
        [anon_sym_LBRACK] = 126,
        [anon_sym_struct] = 126,
        [anon_sym_interface] = 126,
        [sym__line_break] = 12,
        [sym__identifier] = 126,
        [sym_comment] = 12,
    },
    [408] = {
        [anon_sym_SEMI] = 1020,
        [sym__line_break] = 1022,
        [sym_comment] = 12,
    },
    [409] = {
        [anon_sym_SEMI] = 180,
        [sym__line_break] = 180,
        [sym_comment] = 12,
    },
    [410] = {
        [sym__type_expression] = 1024,
        [sym_pointer_type] = 1006,
        [sym_map_type] = 1006,
        [sym_slice_type] = 1006,
        [sym_struct_type] = 1006,
        [sym_interface_type] = 1006,
        [sym_type_name] = 1006,
        [anon_sym_STAR] = 1008,
        [anon_sym_map] = 1010,
        [anon_sym_LBRACK] = 1012,
        [anon_sym_struct] = 1014,
        [anon_sym_interface] = 1016,
        [sym__line_break] = 12,
        [sym__identifier] = 1018,
        [sym_comment] = 12,
    },
    [411] = {
        [anon_sym_LBRACK] = 1026,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [412] = {
        [anon_sym_RBRACK] = 1028,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [413] = {
        [anon_sym_LBRACE] = 1030,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [414] = {
        [anon_sym_LBRACE] = 1032,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [415] = {
        [anon_sym_SEMI] = 126,
        [sym__line_break] = 126,
        [sym_comment] = 12,
    },
    [416] = {
        [sym_var_name] = 202,
        [aux_sym_interface_type_repeat1] = 1034,
        [anon_sym_RBRACE] = 1036,
        [sym__line_break] = 12,
        [sym__identifier] = 72,
        [sym_comment] = 12,
    },
    [417] = {
        [anon_sym_RBRACE] = 1038,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [418] = {
        [anon_sym_SEMI] = 214,
        [sym__line_break] = 214,
        [sym_comment] = 12,
    },
    [419] = {
        [anon_sym_SEMI] = 216,
        [sym__line_break] = 216,
        [sym_comment] = 12,
    },
    [420] = {
        [sym_var_name] = 332,
        [aux_sym_struct_type_repeat1] = 1040,
        [anon_sym_RBRACE] = 1042,
        [sym__line_break] = 12,
        [sym__identifier] = 338,
        [sym_comment] = 12,
    },
    [421] = {
        [anon_sym_RBRACE] = 1044,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [422] = {
        [anon_sym_SEMI] = 358,
        [sym__line_break] = 358,
        [sym_comment] = 12,
    },
    [423] = {
        [anon_sym_SEMI] = 360,
        [sym__line_break] = 360,
        [sym_comment] = 12,
    },
    [424] = {
        [sym__type_expression] = 1046,
        [sym_pointer_type] = 1006,
        [sym_map_type] = 1006,
        [sym_slice_type] = 1006,
        [sym_struct_type] = 1006,
        [sym_interface_type] = 1006,
        [sym_type_name] = 1006,
        [anon_sym_STAR] = 1008,
        [anon_sym_map] = 1010,
        [anon_sym_LBRACK] = 1012,
        [anon_sym_struct] = 1014,
        [anon_sym_interface] = 1016,
        [sym__line_break] = 12,
        [sym__identifier] = 1018,
        [sym_comment] = 12,
    },
    [425] = {
        [anon_sym_SEMI] = 390,
        [sym__line_break] = 390,
        [sym_comment] = 12,
    },
    [426] = {
        [sym__type_expression] = 1048,
        [sym_pointer_type] = 394,
        [sym_map_type] = 394,
        [sym_slice_type] = 394,
        [sym_struct_type] = 394,
        [sym_interface_type] = 394,
        [sym_type_name] = 394,
        [anon_sym_STAR] = 396,
        [anon_sym_map] = 398,
        [anon_sym_LBRACK] = 400,
        [anon_sym_struct] = 402,
        [anon_sym_interface] = 404,
        [sym__line_break] = 12,
        [sym__identifier] = 406,
        [sym_comment] = 12,
    },
    [427] = {
        [anon_sym_RBRACK] = 1050,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [428] = {
        [sym__type_expression] = 1052,
        [sym_pointer_type] = 1006,
        [sym_map_type] = 1006,
        [sym_slice_type] = 1006,
        [sym_struct_type] = 1006,
        [sym_interface_type] = 1006,
        [sym_type_name] = 1006,
        [anon_sym_STAR] = 1008,
        [anon_sym_map] = 1010,
        [anon_sym_LBRACK] = 1012,
        [anon_sym_struct] = 1014,
        [anon_sym_interface] = 1016,
        [sym__line_break] = 12,
        [sym__identifier] = 1018,
        [sym_comment] = 12,
    },
    [429] = {
        [anon_sym_SEMI] = 440,
        [sym__line_break] = 440,
        [sym_comment] = 12,
    },
    [430] = {
        [anon_sym_SEMI] = 442,
        [sym__line_break] = 442,
        [sym_comment] = 12,
    },
    [431] = {
        [sym__declaration] = 1054,
        [sym_type_declaration] = 1054,
        [sym_var_declaration] = 1054,
        [sym_func_declaration] = 1054,
        [aux_sym_program_repeat2] = 1054,
        [ts_builtin_sym_end] = 1054,
        [anon_sym_type] = 1054,
        [anon_sym_var] = 1054,
        [anon_sym_func] = 1054,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [432] = {
        [sym__declaration] = 1054,
        [sym_type_declaration] = 1054,
        [sym_var_declaration] = 1054,
        [sym_func_declaration] = 1054,
        [aux_sym_program_repeat2] = 1054,
        [ts_builtin_sym_end] = 1054,
        [anon_sym_type] = 1054,
        [anon_sym_SEMI] = 1056,
        [anon_sym_var] = 1054,
        [anon_sym_func] = 1054,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [433] = {
        [sym_imports_block] = 1058,
        [sym__declaration] = 1058,
        [sym_type_declaration] = 1058,
        [sym_var_declaration] = 1058,
        [sym_func_declaration] = 1058,
        [aux_sym_program_repeat1] = 1058,
        [aux_sym_program_repeat2] = 1058,
        [ts_builtin_sym_end] = 1058,
        [anon_sym_import] = 1058,
        [anon_sym_type] = 1058,
        [anon_sym_var] = 1058,
        [anon_sym_func] = 1058,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [434] = {
        [sym_package_import] = 1060,
        [aux_sym_imports_block_repeat1] = 1062,
        [ts_builtin_sym_error] = 1062,
        [anon_sym_RPAREN] = 1064,
        [sym__line_break] = 12,
        [sym_string] = 1066,
        [sym_comment] = 12,
    },
    [435] = {
        [sym_imports_block] = 1068,
        [sym__declaration] = 1068,
        [sym_type_declaration] = 1068,
        [sym_var_declaration] = 1068,
        [sym_func_declaration] = 1068,
        [aux_sym_program_repeat1] = 1068,
        [aux_sym_program_repeat2] = 1068,
        [ts_builtin_sym_end] = 1068,
        [anon_sym_import] = 1068,
        [anon_sym_type] = 1068,
        [anon_sym_var] = 1068,
        [anon_sym_func] = 1068,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [436] = {
        [sym_package_import] = 1060,
        [aux_sym_imports_block_repeat1] = 1070,
        [anon_sym_RPAREN] = 1072,
        [sym__line_break] = 12,
        [sym_string] = 1066,
        [sym_comment] = 12,
    },
    [437] = {
        [anon_sym_RPAREN] = 1074,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [438] = {
        [sym_imports_block] = 1076,
        [sym__declaration] = 1076,
        [sym_type_declaration] = 1076,
        [sym_var_declaration] = 1076,
        [sym_func_declaration] = 1076,
        [aux_sym_program_repeat1] = 1076,
        [aux_sym_program_repeat2] = 1076,
        [ts_builtin_sym_end] = 1076,
        [anon_sym_import] = 1076,
        [anon_sym_type] = 1076,
        [anon_sym_var] = 1076,
        [anon_sym_func] = 1076,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [439] = {
        [sym_package_import] = 1068,
        [aux_sym_imports_block_repeat1] = 1068,
        [anon_sym_RPAREN] = 1068,
        [sym__line_break] = 12,
        [sym_string] = 1068,
        [sym_comment] = 12,
    },
    [440] = {
        [sym_imports_block] = 1078,
        [sym__declaration] = 1078,
        [sym_type_declaration] = 1078,
        [sym_var_declaration] = 1078,
        [sym_func_declaration] = 1078,
        [aux_sym_program_repeat1] = 1078,
        [aux_sym_program_repeat2] = 1078,
        [ts_builtin_sym_end] = 1078,
        [anon_sym_import] = 1078,
        [anon_sym_type] = 1078,
        [anon_sym_var] = 1078,
        [anon_sym_func] = 1078,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [441] = {
        [anon_sym_RPAREN] = 1080,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [442] = {
        [ts_builtin_sym_end] = 1082,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [443] = {
        [ts_builtin_sym_end] = 1084,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
    [444] = {
        [sym__declaration] = 1086,
        [sym_type_declaration] = 1086,
        [sym_var_declaration] = 1086,
        [sym_func_declaration] = 1086,
        [aux_sym_program_repeat2] = 1086,
        [ts_builtin_sym_end] = 1086,
        [anon_sym_type] = 1086,
        [anon_sym_var] = 1086,
        [anon_sym_func] = 1086,
        [sym__line_break] = 12,
        [sym_comment] = 12,
    },
};

static TSParseActionEntry ts_parse_actions[] = {
    [0] = {.count = 1}, ERROR(),
    [2] = {.count = 1}, SHIFT(1, 0),
    [4] = {.count = 1}, SHIFT(2, 0),
    [6] = {.count = 1}, SHIFT(3, 0),
    [8] = {.count = 1}, SHIFT_EXTRA(),
    [10] = {.count = 1}, ACCEPT_INPUT(),
    [12] = {.count = 1}, SHIFT_EXTRA(),
    [14] = {.count = 1}, SHIFT(6, 0),
    [16] = {.count = 1}, SHIFT(7, 0),
    [18] = {.count = 1}, SHIFT(8, 0),
    [20] = {.count = 1}, SHIFT(9, 0),
    [22] = {.count = 1}, SHIFT(10, 0),
    [24] = {.count = 1}, REDUCE(sym_program, 1, 0),
    [26] = {.count = 1}, SHIFT(11, 0),
    [28] = {.count = 1}, SHIFT(12, 0),
    [30] = {.count = 1}, SHIFT(13, 0),
    [32] = {.count = 1}, SHIFT(14, 0),
    [34] = {.count = 1}, SHIFT(4, 0),
    [36] = {.count = 1}, SHIFT(5, 0),
    [38] = {.count = 1}, REDUCE(sym_package_directive, 2, 0),
    [40] = {.count = 1}, REDUCE(sym_package_name, 1, 0),
    [42] = {.count = 1}, REDUCE(aux_sym_program_repeat1, 1, 0),
    [44] = {.count = 1}, SHIFT(444, 0),
    [46] = {.count = 1}, SHIFT(443, 0),
    [48] = {.count = 1}, REDUCE(aux_sym_program_repeat2, 1, 0),
    [50] = {.count = 1}, REDUCE(sym__declaration, 1, 0),
    [52] = {.count = 1}, SHIFT(442, 0),
    [54] = {.count = 1}, REDUCE(sym_program, 2, 0),
    [56] = {.count = 1}, SHIFT(433, 0),
    [58] = {.count = 1}, SHIFT(434, 0),
    [60] = {.count = 1}, SHIFT(435, 0),
    [62] = {.count = 1}, SHIFT(406, 0),
    [64] = {.count = 1}, SHIFT(407, 0),
    [66] = {.count = 1}, SHIFT(394, 0),
    [68] = {.count = 1}, SHIFT(341, 0),
    [70] = {.count = 1}, SHIFT(15, 0),
    [72] = {.count = 1}, SHIFT(16, 0),
    [74] = {.count = 1}, SHIFT(17, 0),
    [76] = {.count = 1}, SHIFT(18, 0),
    [78] = {.count = 1}, REDUCE(sym_var_name, 1, 0),
    [80] = {.count = 1}, SHIFT(196, 0),
    [82] = {.count = 1}, SHIFT(197, 0),
    [84] = {.count = 1}, SHIFT(19, 0),
    [86] = {.count = 1}, SHIFT(20, 0),
    [88] = {.count = 1}, SHIFT(21, 0),
    [90] = {.count = 1}, SHIFT(44, 0),
    [92] = {.count = 1}, SHIFT(45, 0),
    [94] = {.count = 1}, SHIFT(46, 0),
    [96] = {.count = 1}, SHIFT(47, 0),
    [98] = {.count = 1}, SHIFT(48, 0),
    [100] = {.count = 1}, SHIFT(49, 0),
    [102] = {.count = 1}, SHIFT(50, 0),
    [104] = {.count = 1}, SHIFT(51, 0),
    [106] = {.count = 1}, SHIFT(52, 0),
    [108] = {.count = 1}, SHIFT(53, 0),
    [110] = {.count = 1}, REDUCE(sym__func_signature, 2, 0),
    [112] = {.count = 1}, SHIFT(22, 0),
    [114] = {.count = 1}, SHIFT(23, 0),
    [116] = {.count = 1}, SHIFT(24, 0),
    [118] = {.count = 1}, REDUCE(sym__func_signature, 3, 0),
    [120] = {.count = 1}, SHIFT(25, 0),
    [122] = {.count = 1}, SHIFT(26, 0),
    [124] = {.count = 1}, SHIFT(27, 0),
    [126] = {.count = 1}, REDUCE(sym_type_name, 1, 0),
    [128] = {.count = 1}, SHIFT(35, 0),
    [130] = {.count = 1}, SHIFT(36, 0),
    [132] = {.count = 1}, SHIFT(28, 0),
    [134] = {.count = 1}, SHIFT(29, 0),
    [136] = {.count = 1}, SHIFT(30, 0),
    [138] = {.count = 1}, SHIFT(34, 0),
    [140] = {.count = 1}, REDUCE(sym__func_signature, 5, 0),
    [142] = {.count = 1}, SHIFT(31, 0),
    [144] = {.count = 1}, SHIFT(32, 0),
    [146] = {.count = 1}, SHIFT(33, 0),
    [148] = {.count = 1}, REDUCE(aux_sym__func_signature_repeat3, 2, 0),
    [150] = {.count = 1}, REDUCE(aux_sym__func_signature_repeat3, 3, 0),
    [152] = {.count = 1}, REDUCE(sym__func_signature, 6, 0),
    [154] = {.count = 1}, SHIFT(37, 0),
    [156] = {.count = 1}, SHIFT(38, 0),
    [158] = {.count = 1}, SHIFT(43, 0),
    [160] = {.count = 1}, SHIFT(39, 0),
    [162] = {.count = 1}, SHIFT(40, 0),
    [164] = {.count = 1}, SHIFT(41, 0),
    [166] = {.count = 1}, SHIFT(42, 0),
    [168] = {.count = 1}, REDUCE(aux_sym__func_signature_repeat2, 3, 0),
    [170] = {.count = 1}, REDUCE(aux_sym__func_signature_repeat2, 4, 0),
    [172] = {.count = 1}, REDUCE(sym__func_signature, 7, 0),
    [174] = {.count = 1}, SHIFT(189, 0),
    [176] = {.count = 1}, SHIFT(190, 0),
    [178] = {.count = 1}, SHIFT(80, 0),
    [180] = {.count = 1}, REDUCE(sym__type_expression, 1, 0),
    [182] = {.count = 1}, SHIFT(170, 0),
    [184] = {.count = 1}, SHIFT(169, 0),
    [186] = {.count = 1}, SHIFT(165, 0),
    [188] = {.count = 1}, SHIFT(163, 0),
    [190] = {.count = 1}, SHIFT(111, 0),
    [192] = {.count = 1}, SHIFT(56, 0),
    [194] = {.count = 1}, SHIFT(54, 0),
    [196] = {.count = 1}, REDUCE(aux_sym_short_var_declaration_repeat1, 2, 0),
    [198] = {.count = 1}, SHIFT(55, 0),
    [200] = {.count = 1}, REDUCE(aux_sym_short_var_declaration_repeat1, 3, 0),
    [202] = {.count = 1}, SHIFT(57, 0),
    [204] = {.count = 1}, SHIFT(58, 0),
    [206] = {.count = 1}, SHIFT(59, 0),
    [208] = {.count = 1}, SHIFT(61, 0),
    [210] = {.count = 1}, SHIFT(62, 0),
    [212] = {.count = 1}, SHIFT(60, 0),
    [214] = {.count = 1}, REDUCE(sym_interface_type, 3, 0),
    [216] = {.count = 1}, REDUCE(sym_interface_type, 4, 0),
    [218] = {.count = 1}, SHIFT(110, 0),
    [220] = {.count = 1}, REDUCE(aux_sym_interface_type_repeat1, 2, 0),
    [222] = {.count = 1}, SHIFT(63, 0),
    [224] = {.count = 1}, SHIFT(64, 0),
    [226] = {.count = 1}, SHIFT(75, 0),
    [228] = {.count = 1}, SHIFT(76, 0),
    [230] = {.count = 1}, SHIFT(65, 0),
    [232] = {.count = 1}, SHIFT(66, 0),
    [234] = {.count = 1}, SHIFT(67, 0),
    [236] = {.count = 1}, SHIFT(68, 0),
    [238] = {.count = 1}, SHIFT(72, 0),
    [240] = {.count = 1}, SHIFT(69, 0),
    [242] = {.count = 1}, SHIFT(70, 0),
    [244] = {.count = 1}, SHIFT(71, 0),
    [246] = {.count = 1}, SHIFT(73, 0),
    [248] = {.count = 1}, SHIFT(74, 0),
    [250] = {.count = 1}, SHIFT(103, 0),
    [252] = {.count = 1}, SHIFT(104, 0),
    [254] = {.count = 1}, SHIFT(77, 0),
    [256] = {.count = 1}, SHIFT(78, 0),
    [258] = {.count = 1}, SHIFT(79, 0),
    [260] = {.count = 1}, SHIFT(96, 0),
    [262] = {.count = 1}, SHIFT(87, 0),
    [264] = {.count = 1}, SHIFT(81, 0),
    [266] = {.count = 1}, SHIFT(82, 0),
    [268] = {.count = 1}, SHIFT(83, 0),
    [270] = {.count = 1}, SHIFT(86, 0),
    [272] = {.count = 1}, REDUCE(aux_sym__func_signature_repeat1, 3, 0),
    [274] = {.count = 1}, SHIFT(84, 0),
    [276] = {.count = 1}, SHIFT(85, 0),
    [278] = {.count = 1}, REDUCE(aux_sym__func_signature_repeat1, 4, 0),
    [280] = {.count = 1}, REDUCE(aux_sym__func_signature_repeat1, 5, 0),
    [282] = {.count = 1}, SHIFT(88, 0),
    [284] = {.count = 1}, SHIFT(89, 0),
    [286] = {.count = 1}, SHIFT(93, 0),
    [288] = {.count = 1}, SHIFT(90, 0),
    [290] = {.count = 1}, SHIFT(91, 0),
    [292] = {.count = 1}, SHIFT(92, 0),
    [294] = {.count = 1}, REDUCE(sym__func_signature, 8, 0),
    [296] = {.count = 1}, REDUCE(sym__func_signature, 9, 0),
    [298] = {.count = 1}, SHIFT(94, 0),
    [300] = {.count = 1}, SHIFT(95, 0),
    [302] = {.count = 1}, REDUCE(sym__func_signature, 10, 0),
    [304] = {.count = 1}, SHIFT(97, 0),
    [306] = {.count = 1}, SHIFT(98, 0),
    [308] = {.count = 1}, SHIFT(99, 0),
    [310] = {.count = 1}, SHIFT(100, 0),
    [312] = {.count = 1}, SHIFT(101, 0),
    [314] = {.count = 1}, SHIFT(102, 0),
    [316] = {.count = 1}, REDUCE(sym__func_signature, 11, 0),
    [318] = {.count = 1}, REDUCE(sym__func_signature, 4, 0),
    [320] = {.count = 1}, SHIFT(105, 0),
    [322] = {.count = 1}, SHIFT(106, 0),
    [324] = {.count = 1}, SHIFT(107, 0),
    [326] = {.count = 1}, SHIFT(109, 0),
    [328] = {.count = 1}, SHIFT(108, 0),
    [330] = {.count = 1}, REDUCE(aux_sym_interface_type_repeat1, 3, 0),
    [332] = {.count = 1}, SHIFT(112, 0),
    [334] = {.count = 1}, SHIFT(113, 0),
    [336] = {.count = 1}, SHIFT(114, 0),
    [338] = {.count = 1}, SHIFT(115, 0),
    [340] = {.count = 1}, SHIFT(117, 0),
    [342] = {.count = 1}, SHIFT(118, 0),
    [344] = {.count = 1}, SHIFT(119, 0),
    [346] = {.count = 1}, SHIFT(120, 0),
    [348] = {.count = 1}, SHIFT(121, 0),
    [350] = {.count = 1}, SHIFT(122, 0),
    [352] = {.count = 1}, SHIFT(123, 0),
    [354] = {.count = 1}, SHIFT(124, 0),
    [356] = {.count = 1}, SHIFT(116, 0),
    [358] = {.count = 1}, REDUCE(sym_struct_type, 3, 0),
    [360] = {.count = 1}, REDUCE(sym_struct_type, 4, 0),
    [362] = {.count = 1}, SHIFT(162, 0),
    [364] = {.count = 1}, REDUCE(aux_sym_struct_type_repeat1, 2, 0),
    [366] = {.count = 1}, SHIFT(161, 0),
    [368] = {.count = 1}, SHIFT(135, 0),
    [370] = {.count = 1}, SHIFT(133, 0),
    [372] = {.count = 1}, SHIFT(129, 0),
    [374] = {.count = 1}, SHIFT(125, 0),
    [376] = {.count = 1}, SHIFT(126, 0),
    [378] = {.count = 1}, SHIFT(127, 0),
    [380] = {.count = 1}, SHIFT(128, 0),
    [382] = {.count = 1}, SHIFT(130, 0),
    [384] = {.count = 1}, SHIFT(131, 0),
    [386] = {.count = 1}, SHIFT(132, 0),
    [388] = {.count = 1}, SHIFT(134, 0),
    [390] = {.count = 1}, REDUCE(sym_slice_type, 3, 0),
    [392] = {.count = 1}, SHIFT(136, 0),
    [394] = {.count = 1}, SHIFT(137, 0),
    [396] = {.count = 1}, SHIFT(138, 0),
    [398] = {.count = 1}, SHIFT(139, 0),
    [400] = {.count = 1}, SHIFT(140, 0),
    [402] = {.count = 1}, SHIFT(141, 0),
    [404] = {.count = 1}, SHIFT(142, 0),
    [406] = {.count = 1}, SHIFT(143, 0),
    [408] = {.count = 1}, SHIFT(159, 0),
    [410] = {.count = 1}, SHIFT(158, 0),
    [412] = {.count = 1}, SHIFT(154, 0),
    [414] = {.count = 1}, SHIFT(152, 0),
    [416] = {.count = 1}, SHIFT(148, 0),
    [418] = {.count = 1}, SHIFT(144, 0),
    [420] = {.count = 1}, SHIFT(145, 0),
    [422] = {.count = 1}, SHIFT(146, 0),
    [424] = {.count = 1}, SHIFT(147, 0),
    [426] = {.count = 1}, SHIFT(149, 0),
    [428] = {.count = 1}, SHIFT(150, 0),
    [430] = {.count = 1}, SHIFT(151, 0),
    [432] = {.count = 1}, SHIFT(153, 0),
    [434] = {.count = 1}, SHIFT(155, 0),
    [436] = {.count = 1}, SHIFT(156, 0),
    [438] = {.count = 1}, SHIFT(157, 0),
    [440] = {.count = 1}, REDUCE(sym_map_type, 5, 0),
    [442] = {.count = 1}, REDUCE(sym_pointer_type, 2, 0),
    [444] = {.count = 1}, SHIFT(160, 0),
    [446] = {.count = 1}, REDUCE(aux_sym_struct_type_repeat1, 3, 0),
    [448] = {.count = 1}, SHIFT(164, 0),
    [450] = {.count = 1}, SHIFT(166, 0),
    [452] = {.count = 1}, SHIFT(167, 0),
    [454] = {.count = 1}, SHIFT(168, 0),
    [456] = {.count = 1}, SHIFT(171, 0),
    [458] = {.count = 1}, SHIFT(172, 0),
    [460] = {.count = 1}, SHIFT(182, 0),
    [462] = {.count = 1}, SHIFT(173, 0),
    [464] = {.count = 1}, SHIFT(174, 0),
    [466] = {.count = 1}, SHIFT(175, 0),
    [468] = {.count = 1}, SHIFT(179, 0),
    [470] = {.count = 1}, SHIFT(176, 0),
    [472] = {.count = 1}, SHIFT(177, 0),
    [474] = {.count = 1}, SHIFT(178, 0),
    [476] = {.count = 1}, SHIFT(180, 0),
    [478] = {.count = 1}, SHIFT(181, 0),
    [480] = {.count = 1}, SHIFT(183, 0),
    [482] = {.count = 1}, SHIFT(184, 0),
    [484] = {.count = 1}, SHIFT(185, 0),
    [486] = {.count = 1}, SHIFT(186, 0),
    [488] = {.count = 1}, SHIFT(187, 0),
    [490] = {.count = 1}, SHIFT(188, 0),
    [492] = {.count = 1}, SHIFT(191, 0),
    [494] = {.count = 1}, SHIFT(192, 0),
    [496] = {.count = 1}, SHIFT(193, 0),
    [498] = {.count = 1}, SHIFT(195, 0),
    [500] = {.count = 1}, SHIFT(194, 0),
    [502] = {.count = 1}, SHIFT(392, 0),
    [504] = {.count = 1}, SHIFT(393, 0),
    [506] = {.count = 1}, SHIFT(198, 0),
    [508] = {.count = 1}, SHIFT(199, 0),
    [510] = {.count = 1}, SHIFT(200, 0),
    [512] = {.count = 1}, SHIFT(201, 0),
    [514] = {.count = 1}, SHIFT(202, 0),
    [516] = {.count = 1}, SHIFT(203, 0),
    [518] = {.count = 1}, SHIFT(204, 0),
    [520] = {.count = 1}, SHIFT(205, 0),
    [522] = {.count = 1}, SHIFT(206, 0),
    [524] = {.count = 1}, SHIFT(207, 0),
    [526] = {.count = 1}, SHIFT(208, 0),
    [528] = {.count = 1}, SHIFT(209, 0),
    [530] = {.count = 1}, SHIFT(210, 0),
    [532] = {.count = 1}, SHIFT(211, 0),
    [534] = {.count = 1}, REDUCE(sym__statement, 1, 0),
    [536] = {.count = 1}, SHIFT(391, 0),
    [538] = {.count = 1}, REDUCE(aux_sym_block_statement_repeat1, 1, 0),
    [540] = {.count = 1}, SHIFT(287, 0),
    [542] = {.count = 1}, SHIFT(389, 0),
    [544] = {.count = 1}, SHIFT(289, 0),
    [546] = {.count = 1}, SHIFT(290, 0),
    [548] = {.count = 1}, SHIFT(291, 0),
    [550] = {.count = 1}, SHIFT(292, 0),
    [552] = {.count = 1}, SHIFT(293, 0),
    [554] = {.count = 1}, SHIFT(294, 0),
    [556] = {.count = 1}, SHIFT(390, 0),
    [558] = {.count = 1}, REDUCE(sym__expression, 1, 0),
    [560] = {.count = 1}, SHIFT(376, 0),
    [562] = {.count = 1}, SHIFT(377, 0),
    [564] = {.count = 1}, SHIFT(378, 0),
    [566] = {.count = 1}, SHIFT(375, 0),
    [568] = {.count = 1}, SHIFT(340, 0),
    [570] = {.count = 1}, REDUCE(sym_block_statement, 2, 0),
    [572] = {.count = 1}, SHIFT(307, 0),
    [574] = {.count = 1}, SHIFT(308, 0),
    [576] = {.count = 1}, SHIFT(309, 0),
    [578] = {.count = 1}, SHIFT(310, 0),
    [580] = {.count = 1}, SHIFT(311, 0),
    [582] = {.count = 1}, SHIFT(312, 0),
    [584] = {.count = 1}, SHIFT(286, 0),
    [586] = {.count = 1}, SHIFT(213, 0),
    [588] = {.count = 1}, SHIFT(273, 0),
    [590] = {.count = 1}, SHIFT(274, 0),
    [592] = {.count = 1}, SHIFT(214, 0),
    [594] = {.count = 1}, SHIFT(215, 0),
    [596] = {.count = 1}, SHIFT(216, 0),
    [598] = {.count = 1}, SHIFT(217, 0),
    [600] = {.count = 1}, SHIFT(212, 0),
    [602] = {.count = 1}, REDUCE(sym_bool_op, 2, 0),
    [604] = {.count = 1}, SHIFT(219, 0),
    [606] = {.count = 1}, SHIFT(220, 0),
    [608] = {.count = 1}, SHIFT(221, 0),
    [610] = {.count = 1}, SHIFT(222, 0),
    [612] = {.count = 1}, SHIFT(223, 0),
    [614] = {.count = 1}, SHIFT(224, 0),
    [616] = {.count = 1}, SHIFT(225, 0),
    [618] = {.count = 1}, SHIFT(226, 0),
    [620] = {.count = 1}, SHIFT(227, 0),
    [622] = {.count = 1}, SHIFT(218, 0),
    [624] = {.count = 1}, REDUCE(sym_if_statement, 3, 0),
    [626] = {.count = 1}, SHIFT(267, 0),
    [628] = {.count = 1}, SHIFT(237, 0),
    [630] = {.count = 1}, SHIFT(238, 0),
    [632] = {.count = 1}, SHIFT(239, 0),
    [634] = {.count = 1}, SHIFT(240, 0),
    [636] = {.count = 1}, SHIFT(241, 0),
    [638] = {.count = 1}, SHIFT(234, 0),
    [640] = {.count = 1}, SHIFT(235, 0),
    [642] = {.count = 1}, SHIFT(232, 0),
    [644] = {.count = 1}, SHIFT(233, 0),
    [646] = {.count = 1}, SHIFT(231, 0),
    [648] = {.count = 1}, SHIFT(230, 0),
    [650] = {.count = 1}, SHIFT(229, 0),
    [652] = {.count = 1}, SHIFT(228, 0),
    [654] = {.count = 1}, REDUCE(sym_bool_op, 3, 0),
    [656] = {.count = 1}, REDUCE(sym_bool_op, 3, FRAGILE),
    [658] = {.count = 1}, REDUCE(sym_math_op, 3, FRAGILE),
    [660] = {.count = 1}, REDUCE(sym_selector_expression, 3, 0),
    [662] = {.count = 1}, SHIFT(236, 0),
    [664] = {.count = 1}, REDUCE(sym_block_statement, 3, 0),
    [666] = {.count = 1}, SHIFT(243, 0),
    [668] = {.count = 1}, SHIFT(244, 0),
    [670] = {.count = 1}, SHIFT(245, 0),
    [672] = {.count = 1}, SHIFT(246, 0),
    [674] = {.count = 1}, SHIFT(247, 0),
    [676] = {.count = 1}, SHIFT(248, 0),
    [678] = {.count = 1}, SHIFT(249, 0),
    [680] = {.count = 1}, SHIFT(250, 0),
    [682] = {.count = 1}, SHIFT(251, 0),
    [684] = {.count = 1}, SHIFT(252, 0),
    [686] = {.count = 1}, REDUCE(sym_call_expression, 3, 0),
    [688] = {.count = 1}, SHIFT(242, 0),
    [690] = {.count = 1}, SHIFT(266, 0),
    [692] = {.count = 1}, SHIFT(261, 0),
    [694] = {.count = 1}, SHIFT(262, 0),
    [696] = {.count = 1}, REDUCE(sym_call_expression, 4, 0),
    [698] = {.count = 1}, SHIFT(257, 0),
    [700] = {.count = 1}, SHIFT(259, 0),
    [702] = {.count = 1}, SHIFT(258, 0),
    [704] = {.count = 1}, SHIFT(256, 0),
    [706] = {.count = 1}, SHIFT(255, 0),
    [708] = {.count = 1}, SHIFT(254, 0),
    [710] = {.count = 1}, SHIFT(253, 0),
    [712] = {.count = 1}, SHIFT(260, 0),
    [714] = {.count = 1}, REDUCE(aux_sym_return_statement_repeat1, 2, 0),
    [716] = {.count = 1}, REDUCE(aux_sym_return_statement_repeat1, 3, 0),
    [718] = {.count = 1}, SHIFT(263, 0),
    [720] = {.count = 1}, SHIFT(264, 0),
    [722] = {.count = 1}, SHIFT(265, 0),
    [724] = {.count = 1}, REDUCE(sym_call_expression, 5, 0),
    [726] = {.count = 1}, SHIFT(268, 0),
    [728] = {.count = 1}, SHIFT(269, 0),
    [730] = {.count = 1}, REDUCE(sym_if_statement, 5, 0),
    [732] = {.count = 1}, SHIFT(270, 0),
    [734] = {.count = 1}, SHIFT(271, 0),
    [736] = {.count = 1}, SHIFT(272, 0),
    [738] = {.count = 1}, SHIFT(275, 0),
    [740] = {.count = 1}, SHIFT(276, 0),
    [742] = {.count = 1}, SHIFT(280, 0),
    [744] = {.count = 1}, SHIFT(281, 0),
    [746] = {.count = 1}, SHIFT(277, 0),
    [748] = {.count = 1}, SHIFT(278, 0),
    [750] = {.count = 1}, SHIFT(279, 0),
    [752] = {.count = 1}, REDUCE(sym_range_statement, 6, 0),
    [754] = {.count = 1}, SHIFT(282, 0),
    [756] = {.count = 1}, SHIFT(283, 0),
    [758] = {.count = 1}, SHIFT(284, 0),
    [760] = {.count = 1}, SHIFT(285, 0),
    [762] = {.count = 1}, REDUCE(sym_range_statement, 8, 0),
    [764] = {.count = 1}, SHIFT(288, 0),
    [766] = {.count = 1}, SHIFT(295, 0),
    [768] = {.count = 1}, SHIFT(302, 0),
    [770] = {.count = 1}, SHIFT(303, 0),
    [772] = {.count = 1}, REDUCE(sym_short_var_declaration, 3, 0),
    [774] = {.count = 1}, SHIFT(300, 0),
    [776] = {.count = 1}, SHIFT(301, 0),
    [778] = {.count = 1}, SHIFT(299, 0),
    [780] = {.count = 1}, SHIFT(298, 0),
    [782] = {.count = 1}, SHIFT(297, 0),
    [784] = {.count = 1}, SHIFT(296, 0),
    [786] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [788] = {.count = 1}, SHIFT(304, 0),
    [790] = {.count = 1}, SHIFT(305, 0),
    [792] = {.count = 1}, SHIFT(306, 0),
    [794] = {.count = 1}, SHIFT(314, 0),
    [796] = {.count = 1}, SHIFT(315, 0),
    [798] = {.count = 1}, SHIFT(316, 0),
    [800] = {.count = 1}, SHIFT(317, 0),
    [802] = {.count = 1}, SHIFT(318, 0),
    [804] = {.count = 1}, SHIFT(319, 0),
    [806] = {.count = 1}, SHIFT(320, 0),
    [808] = {.count = 1}, SHIFT(321, 0),
    [810] = {.count = 1}, SHIFT(322, 0),
    [812] = {.count = 1}, SHIFT(323, 0),
    [814] = {.count = 1}, SHIFT(324, 0),
    [816] = {.count = 1}, REDUCE(sym_return_statement, 2, 0),
    [818] = {.count = 1}, SHIFT(313, 0),
    [820] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [822] = {.count = 1}, SHIFT(338, 0),
    [824] = {.count = 1}, SHIFT(339, 0),
    [826] = {.count = 1}, SHIFT(333, 0),
    [828] = {.count = 1}, SHIFT(334, 0),
    [830] = {.count = 1}, REDUCE(sym_return_statement, 3, 0),
    [832] = {.count = 1}, SHIFT(329, 0),
    [834] = {.count = 1}, SHIFT(331, 0),
    [836] = {.count = 1}, SHIFT(330, 0),
    [838] = {.count = 1}, SHIFT(328, 0),
    [840] = {.count = 1}, SHIFT(327, 0),
    [842] = {.count = 1}, SHIFT(326, 0),
    [844] = {.count = 1}, SHIFT(325, 0),
    [846] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [848] = {.count = 1}, SHIFT(332, 0),
    [850] = {.count = 1}, SHIFT(335, 0),
    [852] = {.count = 1}, SHIFT(336, 0),
    [854] = {.count = 1}, SHIFT(337, 0),
    [856] = {.count = 1}, REDUCE(sym_return_statement, 4, 0),
    [858] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [860] = {.count = 1}, SHIFT(342, 0),
    [862] = {.count = 1}, SHIFT(343, 0),
    [864] = {.count = 1}, SHIFT(344, 0),
    [866] = {.count = 1}, SHIFT(345, 0),
    [868] = {.count = 1}, SHIFT(346, 0),
    [870] = {.count = 1}, SHIFT(347, 0),
    [872] = {.count = 1}, SHIFT(348, 0),
    [874] = {.count = 1}, SHIFT(349, 0),
    [876] = {.count = 1}, SHIFT(350, 0),
    [878] = {.count = 1}, SHIFT(369, 0),
    [880] = {.count = 1}, SHIFT(370, 0),
    [882] = {.count = 1}, SHIFT(371, 0),
    [884] = {.count = 1}, SHIFT(366, 0),
    [886] = {.count = 1}, SHIFT(365, 0),
    [888] = {.count = 1}, SHIFT(361, 0),
    [890] = {.count = 1}, SHIFT(359, 0),
    [892] = {.count = 1}, SHIFT(355, 0),
    [894] = {.count = 1}, SHIFT(351, 0),
    [896] = {.count = 1}, SHIFT(352, 0),
    [898] = {.count = 1}, SHIFT(353, 0),
    [900] = {.count = 1}, SHIFT(354, 0),
    [902] = {.count = 1}, SHIFT(356, 0),
    [904] = {.count = 1}, SHIFT(357, 0),
    [906] = {.count = 1}, SHIFT(358, 0),
    [908] = {.count = 1}, SHIFT(360, 0),
    [910] = {.count = 1}, SHIFT(362, 0),
    [912] = {.count = 1}, SHIFT(363, 0),
    [914] = {.count = 1}, SHIFT(364, 0),
    [916] = {.count = 1}, SHIFT(367, 0),
    [918] = {.count = 1}, SHIFT(368, 0),
    [920] = {.count = 1}, REDUCE(sym_var_declaration, 5, 0),
    [922] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [924] = {.count = 1}, REDUCE(sym_var_declaration, 4, 0),
    [926] = {.count = 1}, SHIFT(372, 0),
    [928] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [930] = {.count = 1}, SHIFT(373, 0),
    [932] = {.count = 1}, SHIFT(374, 0),
    [934] = {.count = 1}, REDUCE(sym_var_declaration, 6, 0),
    [936] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [938] = {.count = 1}, SHIFT(385, 0),
    [940] = {.count = 1}, SHIFT(382, 0),
    [942] = {.count = 1}, SHIFT(383, 0),
    [944] = {.count = 1}, SHIFT(379, 0),
    [946] = {.count = 1}, SHIFT(380, 0),
    [948] = {.count = 1}, SHIFT(381, 0),
    [950] = {.count = 1}, REDUCE(sym_short_var_declaration, 4, 0),
    [952] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [954] = {.count = 1}, SHIFT(384, 0),
    [956] = {.count = 1}, SHIFT(386, 0),
    [958] = {.count = 1}, SHIFT(387, 0),
    [960] = {.count = 1}, SHIFT(388, 0),
    [962] = {.count = 1}, REDUCE(sym_short_var_declaration, 5, 0),
    [964] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [966] = {.count = 1}, REDUCE(sym_expression_statement, 2, 0),
    [968] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [970] = {.count = 1}, REDUCE(aux_sym_block_statement_repeat1, 2, 0),
    [972] = {.count = 1}, REDUCE(sym_func_declaration, 5, 0),
    [974] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [976] = {.count = 1}, SHIFT(395, 0),
    [978] = {.count = 1}, SHIFT(396, 0),
    [980] = {.count = 1}, SHIFT(400, 0),
    [982] = {.count = 1}, SHIFT(401, 0),
    [984] = {.count = 1}, SHIFT(402, 0),
    [986] = {.count = 1}, SHIFT(397, 0),
    [988] = {.count = 1}, SHIFT(398, 0),
    [990] = {.count = 1}, SHIFT(399, 0),
    [992] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [994] = {.count = 1}, SHIFT(403, 0),
    [996] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [998] = {.count = 1}, SHIFT(404, 0),
    [1000] = {.count = 1}, SHIFT(405, 0),
    [1002] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [1004] = {.count = 1}, SHIFT(408, 0),
    [1006] = {.count = 1}, SHIFT(409, 0),
    [1008] = {.count = 1}, SHIFT(410, 0),
    [1010] = {.count = 1}, SHIFT(411, 0),
    [1012] = {.count = 1}, SHIFT(412, 0),
    [1014] = {.count = 1}, SHIFT(413, 0),
    [1016] = {.count = 1}, SHIFT(414, 0),
    [1018] = {.count = 1}, SHIFT(415, 0),
    [1020] = {.count = 1}, SHIFT(431, 0),
    [1022] = {.count = 1}, SHIFT(432, 0),
    [1024] = {.count = 1}, SHIFT(430, 0),
    [1026] = {.count = 1}, SHIFT(426, 0),
    [1028] = {.count = 1}, SHIFT(424, 0),
    [1030] = {.count = 1}, SHIFT(420, 0),
    [1032] = {.count = 1}, SHIFT(416, 0),
    [1034] = {.count = 1}, SHIFT(417, 0),
    [1036] = {.count = 1}, SHIFT(418, 0),
    [1038] = {.count = 1}, SHIFT(419, 0),
    [1040] = {.count = 1}, SHIFT(421, 0),
    [1042] = {.count = 1}, SHIFT(422, 0),
    [1044] = {.count = 1}, SHIFT(423, 0),
    [1046] = {.count = 1}, SHIFT(425, 0),
    [1048] = {.count = 1}, SHIFT(427, 0),
    [1050] = {.count = 1}, SHIFT(428, 0),
    [1052] = {.count = 1}, SHIFT(429, 0),
    [1054] = {.count = 1}, REDUCE(sym_type_declaration, 4, 0),
    [1056] = {.count = 1}, REDUCE_EXTRA(sym__line_break),
    [1058] = {.count = 1}, REDUCE(sym_imports_block, 2, 0),
    [1060] = {.count = 1}, SHIFT(436, 0),
    [1062] = {.count = 1}, SHIFT(437, 0),
    [1064] = {.count = 1}, SHIFT(438, 0),
    [1066] = {.count = 1}, SHIFT(439, 0),
    [1068] = {.count = 1}, REDUCE(sym_package_import, 1, 0),
    [1070] = {.count = 1}, SHIFT(441, 0),
    [1072] = {.count = 1}, REDUCE(aux_sym_imports_block_repeat1, 1, 0),
    [1074] = {.count = 1}, SHIFT(440, 0),
    [1076] = {.count = 1}, REDUCE(sym_imports_block, 3, 0),
    [1078] = {.count = 1}, REDUCE(sym_imports_block, 4, 0),
    [1080] = {.count = 1}, REDUCE(aux_sym_imports_block_repeat1, 2, 0),
    [1082] = {.count = 1}, REDUCE(sym_program, 3, 0),
    [1084] = {.count = 1}, REDUCE(aux_sym_program_repeat2, 2, 0),
    [1086] = {.count = 1}, REDUCE(aux_sym_program_repeat1, 2, 0),
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_golang);
