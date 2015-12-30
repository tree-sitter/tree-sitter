#include "tree_sitter/parser.h"

#define STATE_COUNT 454
#define SYMBOL_COUNT 84

enum {
    sym_translation_unit = ts_builtin_sym_start,
    sym_preproc_define,
    sym_preproc_call,
    sym_function_definition,
    sym_declaration_specifiers,
    sym_storage_class_specifier,
    sym__type_specifier,
    sym_numeric_type_specifier,
    sym_struct_specifier,
    sym_type_name,
    sym_struct_declaration,
    sym_parameter_declaration,
    sym_declaration,
    sym__init_declarator,
    sym_initializer,
    sym_initializer_list,
    sym_designation,
    sym__declarator,
    sym__abstract_declarator,
    sym_pointer_declarator,
    sym_abstract_pointer_declarator,
    sym_function_declarator,
    sym_abstract_function_declarator,
    sym_array_declarator,
    sym_abstract_array_declarator,
    sym_type_qualifier,
    sym_compound_statement,
    sym__expression,
    sym_cast_expression,
    sym_math_expression,
    sym_call_expression,
    sym_pointer_expression,
    sym_assignment_expression,
    sym__statement,
    sym_for_statement,
    sym_expression_statement,
    sym_macro_type,
    aux_sym_translation_unit_repeat1,
    aux_sym_declaration_specifiers_repeat1,
    aux_sym_numeric_type_specifier_repeat1,
    aux_sym_struct_specifier_repeat1,
    aux_sym_type_name_repeat1,
    aux_sym_declaration_repeat1,
    aux_sym_designation_repeat1,
    aux_sym_function_declarator_repeat1,
    aux_sym_compound_statement_repeat1,
    aux_sym_call_expression_repeat1,
    anon_sym_POUNDdefine,
    anon_sym_LF,
    sym_preproc_arg,
    sym_preproc_directive,
    anon_sym_typedef,
    anon_sym_extern,
    anon_sym_static,
    anon_sym_auto,
    anon_sym_register,
    anon_sym_signed,
    anon_sym_unsigned,
    anon_sym_long,
    anon_sym_short,
    anon_sym_struct,
    anon_sym_LBRACE,
    anon_sym_RBRACE,
    anon_sym_COMMA,
    anon_sym_SEMI,
    anon_sym_EQ,
    anon_sym_LBRACK,
    anon_sym_RBRACK,
    anon_sym_DOT,
    anon_sym_LPAREN,
    anon_sym_RPAREN,
    anon_sym_STAR,
    anon_sym_const,
    anon_sym_restrict,
    anon_sym_volatile,
    anon_sym_PLUS,
    anon_sym_AMP,
    anon_sym_for,
    sym_string,
    sym_identifier,
    sym_number,
    sym_comment,
};

static const char *ts_symbol_names[] = {
    [sym_translation_unit] = "translation_unit",
    [sym_preproc_define] = "preproc_define",
    [sym_preproc_call] = "preproc_call",
    [sym_function_definition] = "function_definition",
    [sym_declaration_specifiers] = "declaration_specifiers",
    [sym_storage_class_specifier] = "storage_class_specifier",
    [sym__type_specifier] = "_type_specifier",
    [sym_numeric_type_specifier] = "numeric_type_specifier",
    [sym_struct_specifier] = "struct_specifier",
    [sym_type_name] = "type_name",
    [sym_struct_declaration] = "struct_declaration",
    [sym_parameter_declaration] = "parameter_declaration",
    [sym_declaration] = "declaration",
    [sym__init_declarator] = "_init_declarator",
    [sym_initializer] = "initializer",
    [sym_initializer_list] = "initializer_list",
    [sym_designation] = "designation",
    [sym__declarator] = "_declarator",
    [sym__abstract_declarator] = "_abstract_declarator",
    [sym_pointer_declarator] = "pointer_declarator",
    [sym_abstract_pointer_declarator] = "abstract_pointer_declarator",
    [sym_function_declarator] = "function_declarator",
    [sym_abstract_function_declarator] = "abstract_function_declarator",
    [sym_array_declarator] = "array_declarator",
    [sym_abstract_array_declarator] = "abstract_array_declarator",
    [sym_type_qualifier] = "type_qualifier",
    [sym_compound_statement] = "compound_statement",
    [sym__expression] = "_expression",
    [sym_cast_expression] = "cast_expression",
    [sym_math_expression] = "math_expression",
    [sym_call_expression] = "call_expression",
    [sym_pointer_expression] = "pointer_expression",
    [sym_assignment_expression] = "assignment_expression",
    [sym__statement] = "_statement",
    [sym_for_statement] = "for_statement",
    [sym_expression_statement] = "expression_statement",
    [sym_macro_type] = "macro_type",
    [aux_sym_translation_unit_repeat1] = "translation_unit_repeat1",
    [aux_sym_declaration_specifiers_repeat1] = "declaration_specifiers_repeat1",
    [aux_sym_numeric_type_specifier_repeat1] = "numeric_type_specifier_repeat1",
    [aux_sym_struct_specifier_repeat1] = "struct_specifier_repeat1",
    [aux_sym_type_name_repeat1] = "type_name_repeat1",
    [aux_sym_declaration_repeat1] = "declaration_repeat1",
    [aux_sym_designation_repeat1] = "designation_repeat1",
    [aux_sym_function_declarator_repeat1] = "function_declarator_repeat1",
    [aux_sym_compound_statement_repeat1] = "compound_statement_repeat1",
    [aux_sym_call_expression_repeat1] = "call_expression_repeat1",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
    [anon_sym_POUNDdefine] = "#define",
    [anon_sym_LF] = "\n",
    [sym_preproc_arg] = "preproc_arg",
    [sym_preproc_directive] = "preproc_directive",
    [anon_sym_typedef] = "typedef",
    [anon_sym_extern] = "extern",
    [anon_sym_static] = "static",
    [anon_sym_auto] = "auto",
    [anon_sym_register] = "register",
    [anon_sym_signed] = "signed",
    [anon_sym_unsigned] = "unsigned",
    [anon_sym_long] = "long",
    [anon_sym_short] = "short",
    [anon_sym_struct] = "struct",
    [anon_sym_LBRACE] = "{",
    [anon_sym_RBRACE] = "}",
    [anon_sym_COMMA] = ",",
    [anon_sym_SEMI] = ";",
    [anon_sym_EQ] = "=",
    [anon_sym_LBRACK] = "[",
    [anon_sym_RBRACK] = "]",
    [anon_sym_DOT] = ".",
    [anon_sym_LPAREN] = "(",
    [anon_sym_RPAREN] = ")",
    [anon_sym_STAR] = "*",
    [anon_sym_const] = "const",
    [anon_sym_restrict] = "restrict",
    [anon_sym_volatile] = "volatile",
    [anon_sym_PLUS] = "+",
    [anon_sym_AMP] = "&",
    [anon_sym_for] = "for",
    [sym_string] = "string",
    [sym_identifier] = "identifier",
    [sym_number] = "number",
    [sym_comment] = "comment",
};

static const TSSymbolMetadata ts_symbol_metadata[SYMBOL_COUNT] = {
    [sym_translation_unit] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_preproc_define] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_preproc_call] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_function_definition] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_declaration_specifiers] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_storage_class_specifier] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__type_specifier] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_numeric_type_specifier] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_struct_specifier] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_type_name] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_struct_declaration] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_parameter_declaration] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_declaration] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__init_declarator] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_initializer] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_initializer_list] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_designation] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__declarator] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym__abstract_declarator] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_pointer_declarator] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_abstract_pointer_declarator] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_function_declarator] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_abstract_function_declarator] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_array_declarator] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_abstract_array_declarator] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_type_qualifier] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_compound_statement] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__expression] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_cast_expression] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_math_expression] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_call_expression] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_pointer_expression] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_assignment_expression] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym__statement] = {.visible = false, .named = false, .structural = true, .extra = false},
    [sym_for_statement] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_expression_statement] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_macro_type] = {.visible = true, .named = true, .structural = true, .extra = false},
    [aux_sym_translation_unit_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_declaration_specifiers_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_numeric_type_specifier_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_struct_specifier_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_type_name_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_declaration_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_designation_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_function_declarator_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_compound_statement_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [aux_sym_call_expression_repeat1] = {.visible = false, .named = false, .structural = true, .extra = false},
    [ts_builtin_sym_error] = {.visible = true, .named = true, .structural = true, .extra = false},
    [ts_builtin_sym_end] = {.visible = false, .named = false, .structural = true, .extra = false},
    [anon_sym_POUNDdefine] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LF] = {.visible = true, .named = false, .structural = true, .extra = false},
    [sym_preproc_arg] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_preproc_directive] = {.visible = true, .named = true, .structural = true, .extra = false},
    [anon_sym_typedef] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_extern] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_static] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_auto] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_register] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_signed] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_unsigned] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_long] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_short] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_struct] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LBRACE] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_RBRACE] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_COMMA] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_SEMI] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_EQ] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LBRACK] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_RBRACK] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_DOT] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_LPAREN] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_RPAREN] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_STAR] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_const] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_restrict] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_volatile] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_PLUS] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_AMP] = {.visible = true, .named = false, .structural = true, .extra = false},
    [anon_sym_for] = {.visible = true, .named = false, .structural = true, .extra = false},
    [sym_string] = {.visible = true, .named = true, .structural = true, .extra = false},
    [sym_identifier] = {.visible = true, .named = true, .structural = true, .extra = false},
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
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '#')
                ADVANCE(7);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '+')
                ADVANCE(19);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '.')
                ADVANCE(21);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == ';')
                ADVANCE(30);
            if (lookahead == '=')
                ADVANCE(31);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(33);
            if (lookahead == ']')
                ADVANCE(34);
            if (lookahead == 'a')
                ADVANCE(35);
            if (lookahead == 'c')
                ADVANCE(39);
            if (lookahead == 'e')
                ADVANCE(44);
            if (lookahead == 'f')
                ADVANCE(50);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 'r')
                ADVANCE(57);
            if (lookahead == 's')
                ADVANCE(71);
            if (lookahead == 't')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == 'v')
                ADVANCE(105);
            if (lookahead == '{')
                ADVANCE(113);
            if (lookahead == '}')
                ADVANCE(114);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_LF);
        case 3:
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '\\')
                ADVANCE(5);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            LEX_ERROR();
        case 4:
            ACCEPT_TOKEN(sym_string);
        case 5:
            if (lookahead == '\"')
                ADVANCE(6);
            if (lookahead == '\\')
                ADVANCE(5);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            LEX_ERROR();
        case 6:
            if (lookahead == '\"')
                ADVANCE(4);
            if (lookahead == '\\')
                ADVANCE(5);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(3);
            ACCEPT_TOKEN(sym_string);
        case 7:
            if (lookahead == 7)
                ADVANCE(8);
            if (lookahead == 'd')
                ADVANCE(9);
            LEX_ERROR();
        case 8:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(8);
            ACCEPT_TOKEN(sym_preproc_directive);
        case 9:
            if (lookahead == 'e')
                ADVANCE(10);
            LEX_ERROR();
        case 10:
            if (lookahead == 'f')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (lookahead == 'i')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (lookahead == 'n')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            if (lookahead == 'e')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            ACCEPT_TOKEN(anon_sym_POUNDdefine);
        case 15:
            ACCEPT_TOKEN(anon_sym_AMP);
        case 16:
            ACCEPT_TOKEN(anon_sym_LPAREN);
        case 17:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 18:
            ACCEPT_TOKEN(anon_sym_STAR);
        case 19:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 20:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 21:
            ACCEPT_TOKEN(anon_sym_DOT);
        case 22:
            if (lookahead == '*')
                ADVANCE(23);
            if (lookahead == '/')
                ADVANCE(26);
            LEX_ERROR();
        case 23:
            if (lookahead == '*')
                ADVANCE(24);
            if (!((lookahead == 0) ||
                (lookahead == '*')))
                ADVANCE(23);
            LEX_ERROR();
        case 24:
            if (lookahead == '/')
                ADVANCE(25);
            if (!((lookahead == 0) ||
                (lookahead == '/')))
                ADVANCE(23);
            LEX_ERROR();
        case 25:
            ACCEPT_TOKEN(sym_comment);
        case 26:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(26);
            ACCEPT_TOKEN(sym_comment);
        case 27:
            if (lookahead == '.')
                ADVANCE(28);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            ACCEPT_TOKEN(sym_number);
        case 28:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(29);
            LEX_ERROR();
        case 29:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(29);
            ACCEPT_TOKEN(sym_number);
        case 30:
            ACCEPT_TOKEN(anon_sym_SEMI);
        case 31:
            ACCEPT_TOKEN(anon_sym_EQ);
        case 32:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 33:
            ACCEPT_TOKEN(anon_sym_LBRACK);
        case 34:
            ACCEPT_TOKEN(anon_sym_RBRACK);
        case 35:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'u')
                ADVANCE(36);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 36:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(37);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 37:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'o')
                ADVANCE(38);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 38:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_auto);
        case 39:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'o')
                ADVANCE(40);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 40:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(41);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 41:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(42);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 42:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(43);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 43:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_const);
        case 44:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'w') ||
                (lookahead == 'y') ||
                (lookahead == 'z'))
                ADVANCE(32);
            if (lookahead == 'x')
                ADVANCE(45);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 45:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(46);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 46:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(47);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'r')
                ADVANCE(48);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(49);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_extern);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'o')
                ADVANCE(51);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'r')
                ADVANCE(52);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_for);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'o')
                ADVANCE(54);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(55);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'g')
                ADVANCE(56);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_long);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(58);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'g')
                ADVANCE(59);
            if (lookahead == 's')
                ADVANCE(65);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'i')
                ADVANCE(60);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(61);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(62);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(63);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'r')
                ADVANCE(64);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_register);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(66);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'r')
                ADVANCE(67);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'i')
                ADVANCE(68);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'c')
                ADVANCE(69);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(70);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_restrict);
        case 71:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'h')
                ADVANCE(72);
            if (lookahead == 'i')
                ADVANCE(76);
            if (lookahead == 't')
                ADVANCE(81);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 72:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'o')
                ADVANCE(73);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 73:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'r')
                ADVANCE(74);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 74:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(75);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 75:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_short);
        case 76:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'g')
                ADVANCE(77);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 77:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(78);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 78:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(79);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 79:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'd')
                ADVANCE(80);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 80:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_signed);
        case 81:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'a')
                ADVANCE(82);
            if (lookahead == 'r')
                ADVANCE(86);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 82:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(83);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 83:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'i')
                ADVANCE(84);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 84:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'c')
                ADVANCE(85);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 85:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_static);
        case 86:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'u')
                ADVANCE(87);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 87:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'c')
                ADVANCE(88);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 88:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(89);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 89:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_struct);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(32);
            if (lookahead == 'y')
                ADVANCE(91);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 91:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'p')
                ADVANCE(92);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 92:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(93);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'd')
                ADVANCE(94);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(95);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 95:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'f')
                ADVANCE(96);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 96:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_typedef);
        case 97:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(98);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 98:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(99);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 99:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'i')
                ADVANCE(100);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 100:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'g')
                ADVANCE(101);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 101:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'n')
                ADVANCE(102);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 102:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(103);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'd')
                ADVANCE(104);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 104:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_unsigned);
        case 105:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'o')
                ADVANCE(106);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 106:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'l')
                ADVANCE(107);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 107:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'a')
                ADVANCE(108);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 108:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 't')
                ADVANCE(109);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 109:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'i')
                ADVANCE(110);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 110:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'l')
                ADVANCE(111);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 111:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(112);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 112:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            ACCEPT_TOKEN(anon_sym_volatile);
        case 113:
            ACCEPT_TOKEN(anon_sym_LBRACE);
        case 114:
            ACCEPT_TOKEN(anon_sym_RBRACE);
        case 115:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == '#')
                ADVANCE(7);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'a')
                ADVANCE(35);
            if (lookahead == 'c')
                ADVANCE(39);
            if (lookahead == 'e')
                ADVANCE(44);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 'r')
                ADVANCE(57);
            if (lookahead == 's')
                ADVANCE(71);
            if (lookahead == 't')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == 'v')
                ADVANCE(105);
            LEX_ERROR();
        case 116:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(116);
            if (lookahead == '/')
                ADVANCE(22);
            LEX_ERROR();
        case 117:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(117);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 's')
                ADVANCE(118);
            if (lookahead == 'u')
                ADVANCE(97);
            LEX_ERROR();
        case 118:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'h')
                ADVANCE(72);
            if (lookahead == 'i')
                ADVANCE(76);
            if (lookahead == 't')
                ADVANCE(119);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 119:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'r')
                ADVANCE(86);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 120:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(120);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'a')
                ADVANCE(35);
            if (lookahead == 'c')
                ADVANCE(39);
            if (lookahead == 'e')
                ADVANCE(44);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 'r')
                ADVANCE(57);
            if (lookahead == 's')
                ADVANCE(71);
            if (lookahead == 't')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == 'v')
                ADVANCE(105);
            LEX_ERROR();
        case 121:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(121);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            LEX_ERROR();
        case 122:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(122);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            LEX_ERROR();
        case 123:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(123);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(30);
            LEX_ERROR();
        case 124:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
            if (lookahead == '\n')
                ADVANCE(124);
            if (lookahead == '/')
                ADVANCE(126);
            if (lookahead == '\\')
                ADVANCE(131);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(132);
            LEX_ERROR();
        case 125:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
            if (lookahead == '/')
                ADVANCE(126);
            if (lookahead == '\\')
                ADVANCE(131);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(132);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 126:
            if (lookahead == '*')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(130);
            if (lookahead == '\\')
                ADVANCE(131);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(132);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 127:
            if (lookahead == '\n')
                ADVANCE(23);
            if (lookahead == '*')
                ADVANCE(128);
            if (lookahead == '\\')
                ADVANCE(129);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(127);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 128:
            if (lookahead == '\n')
                ADVANCE(23);
            if (lookahead == '/')
                ADVANCE(25);
            if (lookahead == '\\')
                ADVANCE(129);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(127);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 129:
            if (lookahead == '\n')
                ADVANCE(127);
            if (lookahead == '*')
                ADVANCE(128);
            if (lookahead == '\\')
                ADVANCE(129);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(127);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 130:
            if (lookahead == '\\')
                ADVANCE(130);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(130);
            ACCEPT_TOKEN(sym_comment);
        case 131:
            if (lookahead == '\n')
                ADVANCE(132);
            if (lookahead == '\\')
                ADVANCE(131);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(132);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 132:
            if (lookahead == '\\')
                ADVANCE(131);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(132);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 133:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(133);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 's')
                ADVANCE(134);
            if (lookahead == 'u')
                ADVANCE(97);
            LEX_ERROR();
        case 134:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'h')
                ADVANCE(72);
            if (lookahead == 'i')
                ADVANCE(76);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '/')
                ADVANCE(22);
            LEX_ERROR();
        case 137:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '/')
                ADVANCE(22);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 's')
                ADVANCE(118);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == '}')
                ADVANCE(114);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '}')
                ADVANCE(114);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(33);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 's')
                ADVANCE(118);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == '}')
                ADVANCE(114);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == ']')
                ADVANCE(34);
            LEX_ERROR();
        case 143:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(143);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'a')
                ADVANCE(35);
            if (lookahead == 'c')
                ADVANCE(39);
            if (lookahead == 'e')
                ADVANCE(44);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 'r')
                ADVANCE(57);
            if (lookahead == 's')
                ADVANCE(71);
            if (lookahead == 't')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == 'v')
                ADVANCE(105);
            LEX_ERROR();
        case 144:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '/')
                ADVANCE(22);
            LEX_ERROR();
        case 145:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(145);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '[')
                ADVANCE(33);
            LEX_ERROR();
        case 146:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(146);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '+')
                ADVANCE(19);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '=')
                ADVANCE(31);
            if (lookahead == ']')
                ADVANCE(34);
            LEX_ERROR();
        case 147:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(147);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                (lookahead == 't') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'c')
                ADVANCE(39);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 'r')
                ADVANCE(148);
            if (lookahead == 's')
                ADVANCE(118);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == 'v')
                ADVANCE(105);
            LEX_ERROR();
        case 148:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'e')
                ADVANCE(149);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 149:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 's')
                ADVANCE(65);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 150:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(150);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            LEX_ERROR();
        case 151:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(151);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            LEX_ERROR();
        case 152:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(152);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '+')
                ADVANCE(19);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '=')
                ADVANCE(31);
            LEX_ERROR();
        case 153:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(153);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            LEX_ERROR();
        case 154:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(154);
            if (lookahead == '/')
                ADVANCE(22);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                (lookahead == 't') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'c')
                ADVANCE(39);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 'r')
                ADVANCE(148);
            if (lookahead == 's')
                ADVANCE(118);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == 'v')
                ADVANCE(105);
            LEX_ERROR();
        case 155:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(155);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '+')
                ADVANCE(19);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '=')
                ADVANCE(31);
            LEX_ERROR();
        case 156:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(156);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '[')
                ADVANCE(33);
            LEX_ERROR();
        case 157:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(157);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            LEX_ERROR();
        case 158:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(158);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ')')
                ADVANCE(17);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '[')
                ADVANCE(33);
            LEX_ERROR();
        case 159:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(160);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(126);
            if (lookahead == '\\')
                ADVANCE(131);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(132);
            LEX_ERROR();
        case 160:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(160);
            if (lookahead == '/')
                ADVANCE(126);
            if (lookahead == '\\')
                ADVANCE(131);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(132);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 161:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(161);
            if (lookahead == '\n')
                ADVANCE(2);
            if (lookahead == '/')
                ADVANCE(22);
            LEX_ERROR();
        case 162:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(162);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(30);
            LEX_ERROR();
        case 163:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(163);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(30);
            if (lookahead == '=')
                ADVANCE(31);
            if (lookahead == '[')
                ADVANCE(33);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 164:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(164);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'a')
                ADVANCE(35);
            if (lookahead == 'c')
                ADVANCE(39);
            if (lookahead == 'e')
                ADVANCE(44);
            if (lookahead == 'f')
                ADVANCE(50);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 'r')
                ADVANCE(57);
            if (lookahead == 's')
                ADVANCE(71);
            if (lookahead == 't')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == 'v')
                ADVANCE(105);
            if (lookahead == '{')
                ADVANCE(113);
            if (lookahead == '}')
                ADVANCE(114);
            LEX_ERROR();
        case 165:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(165);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 166:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(166);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '+')
                ADVANCE(19);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(30);
            if (lookahead == '=')
                ADVANCE(31);
            LEX_ERROR();
        case 167:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(167);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '.')
                ADVANCE(21);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(33);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        case 168:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(168);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '}')
                ADVANCE(114);
            LEX_ERROR();
        case 169:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(169);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '+')
                ADVANCE(19);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '=')
                ADVANCE(31);
            if (lookahead == '}')
                ADVANCE(114);
            LEX_ERROR();
        case 170:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(170);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '=')
                ADVANCE(31);
            LEX_ERROR();
        case 171:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(171);
            if (lookahead == '.')
                ADVANCE(21);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == '=')
                ADVANCE(31);
            if (lookahead == '[')
                ADVANCE(33);
            LEX_ERROR();
        case 172:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(172);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '.')
                ADVANCE(21);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == '[')
                ADVANCE(33);
            if (lookahead == '{')
                ADVANCE(113);
            if (lookahead == '}')
                ADVANCE(114);
            LEX_ERROR();
        case 173:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(173);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == ',')
                ADVANCE(20);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(30);
            if (lookahead == '=')
                ADVANCE(31);
            if (lookahead == '[')
                ADVANCE(33);
            LEX_ERROR();
        case 174:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(174);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '+')
                ADVANCE(19);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(30);
            if (lookahead == '=')
                ADVANCE(31);
            LEX_ERROR();
        case 175:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(175);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(30);
            if (lookahead == '}')
                ADVANCE(114);
            LEX_ERROR();
        case 176:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(176);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '/')
                ADVANCE(22);
            LEX_ERROR();
        case 177:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(177);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '+')
                ADVANCE(19);
            if (lookahead == '/')
                ADVANCE(22);
            if (lookahead == ';')
                ADVANCE(30);
            if (lookahead == '=')
                ADVANCE(31);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            LEX_ERROR();
        case 178:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(178);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == ';')
                ADVANCE(30);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'a')
                ADVANCE(35);
            if (lookahead == 'c')
                ADVANCE(39);
            if (lookahead == 'e')
                ADVANCE(44);
            if (lookahead == 'l')
                ADVANCE(53);
            if (lookahead == 'r')
                ADVANCE(57);
            if (lookahead == 's')
                ADVANCE(71);
            if (lookahead == 't')
                ADVANCE(90);
            if (lookahead == 'u')
                ADVANCE(97);
            if (lookahead == 'v')
                ADVANCE(105);
            LEX_ERROR();
        case 179:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(179);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (lookahead == ';')
                ADVANCE(30);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            LEX_ERROR();
        case 180:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(180);
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(15);
            if (lookahead == '(')
                ADVANCE(16);
            if (lookahead == '*')
                ADVANCE(18);
            if (lookahead == '/')
                ADVANCE(22);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(27);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(32);
            if (lookahead == 'f')
                ADVANCE(50);
            if (lookahead == '{')
                ADVANCE(113);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 115,
    [1] = 116,
    [2] = 115,
    [3] = 117,
    [4] = 120,
    [5] = 121,
    [6] = 121,
    [7] = 116,
    [8] = 117,
    [9] = 122,
    [10] = 123,
    [11] = 122,
    [12] = 124,
    [13] = 120,
    [14] = 133,
    [15] = 135,
    [16] = 120,
    [17] = 121,
    [18] = 117,
    [19] = 136,
    [20] = 136,
    [21] = 122,
    [22] = 135,
    [23] = 137,
    [24] = 117,
    [25] = 136,
    [26] = 136,
    [27] = 138,
    [28] = 139,
    [29] = 138,
    [30] = 121,
    [31] = 121,
    [32] = 138,
    [33] = 122,
    [34] = 140,
    [35] = 135,
    [36] = 136,
    [37] = 121,
    [38] = 117,
    [39] = 136,
    [40] = 121,
    [41] = 138,
    [42] = 139,
    [43] = 138,
    [44] = 140,
    [45] = 121,
    [46] = 121,
    [47] = 140,
    [48] = 121,
    [49] = 136,
    [50] = 121,
    [51] = 140,
    [52] = 141,
    [53] = 141,
    [54] = 121,
    [55] = 121,
    [56] = 141,
    [57] = 142,
    [58] = 143,
    [59] = 117,
    [60] = 121,
    [61] = 144,
    [62] = 141,
    [63] = 136,
    [64] = 120,
    [65] = 141,
    [66] = 144,
    [67] = 136,
    [68] = 141,
    [69] = 145,
    [70] = 145,
    [71] = 121,
    [72] = 121,
    [73] = 145,
    [74] = 142,
    [75] = 143,
    [76] = 144,
    [77] = 145,
    [78] = 136,
    [79] = 145,
    [80] = 145,
    [81] = 146,
    [82] = 146,
    [83] = 145,
    [84] = 147,
    [85] = 150,
    [86] = 146,
    [87] = 146,
    [88] = 151,
    [89] = 150,
    [90] = 150,
    [91] = 146,
    [92] = 146,
    [93] = 152,
    [94] = 152,
    [95] = 147,
    [96] = 146,
    [97] = 150,
    [98] = 152,
    [99] = 152,
    [100] = 151,
    [101] = 150,
    [102] = 150,
    [103] = 152,
    [104] = 152,
    [105] = 152,
    [106] = 152,
    [107] = 136,
    [108] = 150,
    [109] = 150,
    [110] = 152,
    [111] = 152,
    [112] = 152,
    [113] = 136,
    [114] = 152,
    [115] = 153,
    [116] = 153,
    [117] = 136,
    [118] = 154,
    [119] = 155,
    [120] = 155,
    [121] = 122,
    [122] = 117,
    [123] = 135,
    [124] = 147,
    [125] = 150,
    [126] = 154,
    [127] = 155,
    [128] = 117,
    [129] = 136,
    [130] = 153,
    [131] = 155,
    [132] = 155,
    [133] = 151,
    [134] = 150,
    [135] = 150,
    [136] = 155,
    [137] = 155,
    [138] = 152,
    [139] = 155,
    [140] = 136,
    [141] = 155,
    [142] = 155,
    [143] = 136,
    [144] = 155,
    [145] = 150,
    [146] = 155,
    [147] = 155,
    [148] = 150,
    [149] = 155,
    [150] = 138,
    [151] = 139,
    [152] = 138,
    [153] = 140,
    [154] = 153,
    [155] = 153,
    [156] = 140,
    [157] = 153,
    [158] = 153,
    [159] = 153,
    [160] = 156,
    [161] = 156,
    [162] = 157,
    [163] = 158,
    [164] = 156,
    [165] = 142,
    [166] = 143,
    [167] = 144,
    [168] = 156,
    [169] = 136,
    [170] = 156,
    [171] = 156,
    [172] = 146,
    [173] = 156,
    [174] = 150,
    [175] = 156,
    [176] = 146,
    [177] = 156,
    [178] = 156,
    [179] = 153,
    [180] = 152,
    [181] = 117,
    [182] = 150,
    [183] = 152,
    [184] = 156,
    [185] = 136,
    [186] = 146,
    [187] = 146,
    [188] = 136,
    [189] = 155,
    [190] = 146,
    [191] = 150,
    [192] = 146,
    [193] = 145,
    [194] = 156,
    [195] = 156,
    [196] = 121,
    [197] = 121,
    [198] = 156,
    [199] = 142,
    [200] = 143,
    [201] = 144,
    [202] = 156,
    [203] = 136,
    [204] = 156,
    [205] = 156,
    [206] = 146,
    [207] = 156,
    [208] = 156,
    [209] = 156,
    [210] = 156,
    [211] = 145,
    [212] = 121,
    [213] = 145,
    [214] = 146,
    [215] = 141,
    [216] = 141,
    [217] = 156,
    [218] = 141,
    [219] = 140,
    [220] = 136,
    [221] = 136,
    [222] = 121,
    [223] = 138,
    [224] = 139,
    [225] = 138,
    [226] = 140,
    [227] = 121,
    [228] = 121,
    [229] = 140,
    [230] = 121,
    [231] = 122,
    [232] = 115,
    [233] = 159,
    [234] = 115,
    [235] = 161,
    [236] = 115,
    [237] = 115,
    [238] = 121,
    [239] = 117,
    [240] = 116,
    [241] = 162,
    [242] = 163,
    [243] = 163,
    [244] = 121,
    [245] = 121,
    [246] = 163,
    [247] = 142,
    [248] = 143,
    [249] = 144,
    [250] = 163,
    [251] = 136,
    [252] = 163,
    [253] = 163,
    [254] = 146,
    [255] = 163,
    [256] = 163,
    [257] = 156,
    [258] = 163,
    [259] = 115,
    [260] = 123,
    [261] = 164,
    [262] = 121,
    [263] = 115,
    [264] = 165,
    [265] = 162,
    [266] = 166,
    [267] = 166,
    [268] = 167,
    [269] = 147,
    [270] = 150,
    [271] = 166,
    [272] = 166,
    [273] = 151,
    [274] = 150,
    [275] = 150,
    [276] = 166,
    [277] = 166,
    [278] = 152,
    [279] = 166,
    [280] = 136,
    [281] = 166,
    [282] = 166,
    [283] = 136,
    [284] = 155,
    [285] = 166,
    [286] = 150,
    [287] = 166,
    [288] = 168,
    [289] = 168,
    [290] = 165,
    [291] = 169,
    [292] = 169,
    [293] = 170,
    [294] = 167,
    [295] = 150,
    [296] = 122,
    [297] = 147,
    [298] = 150,
    [299] = 169,
    [300] = 169,
    [301] = 151,
    [302] = 150,
    [303] = 150,
    [304] = 169,
    [305] = 169,
    [306] = 152,
    [307] = 169,
    [308] = 136,
    [309] = 169,
    [310] = 169,
    [311] = 136,
    [312] = 155,
    [313] = 169,
    [314] = 150,
    [315] = 169,
    [316] = 171,
    [317] = 170,
    [318] = 146,
    [319] = 171,
    [320] = 170,
    [321] = 168,
    [322] = 168,
    [323] = 172,
    [324] = 168,
    [325] = 165,
    [326] = 168,
    [327] = 168,
    [328] = 165,
    [329] = 150,
    [330] = 169,
    [331] = 168,
    [332] = 162,
    [333] = 172,
    [334] = 162,
    [335] = 150,
    [336] = 166,
    [337] = 162,
    [338] = 173,
    [339] = 173,
    [340] = 121,
    [341] = 121,
    [342] = 173,
    [343] = 142,
    [344] = 143,
    [345] = 144,
    [346] = 173,
    [347] = 136,
    [348] = 173,
    [349] = 173,
    [350] = 146,
    [351] = 173,
    [352] = 173,
    [353] = 156,
    [354] = 173,
    [355] = 123,
    [356] = 117,
    [357] = 121,
    [358] = 164,
    [359] = 164,
    [360] = 174,
    [361] = 174,
    [362] = 140,
    [363] = 175,
    [364] = 164,
    [365] = 115,
    [366] = 147,
    [367] = 150,
    [368] = 176,
    [369] = 177,
    [370] = 178,
    [371] = 117,
    [372] = 121,
    [373] = 179,
    [374] = 174,
    [375] = 123,
    [376] = 174,
    [377] = 151,
    [378] = 174,
    [379] = 152,
    [380] = 180,
    [381] = 164,
    [382] = 136,
    [383] = 180,
    [384] = 164,
    [385] = 180,
    [386] = 164,
    [387] = 151,
    [388] = 150,
    [389] = 151,
    [390] = 150,
    [391] = 150,
    [392] = 174,
    [393] = 174,
    [394] = 152,
    [395] = 174,
    [396] = 136,
    [397] = 174,
    [398] = 174,
    [399] = 174,
    [400] = 152,
    [401] = 136,
    [402] = 180,
    [403] = 164,
    [404] = 179,
    [405] = 179,
    [406] = 174,
    [407] = 151,
    [408] = 152,
    [409] = 136,
    [410] = 180,
    [411] = 164,
    [412] = 162,
    [413] = 173,
    [414] = 123,
    [415] = 179,
    [416] = 179,
    [417] = 121,
    [418] = 162,
    [419] = 173,
    [420] = 123,
    [421] = 179,
    [422] = 174,
    [423] = 136,
    [424] = 155,
    [425] = 174,
    [426] = 150,
    [427] = 174,
    [428] = 140,
    [429] = 175,
    [430] = 164,
    [431] = 164,
    [432] = 164,
    [433] = 115,
    [434] = 140,
    [435] = 123,
    [436] = 164,
    [437] = 162,
    [438] = 173,
    [439] = 123,
    [440] = 164,
    [441] = 164,
    [442] = 121,
    [443] = 162,
    [444] = 173,
    [445] = 123,
    [446] = 164,
    [447] = 115,
    [448] = 121,
    [449] = 162,
    [450] = 163,
    [451] = 115,
    [452] = 123,
    [453] = 115,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static unsigned short ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_translation_unit] = 2,
        [sym_preproc_define] = 4,
        [sym_preproc_call] = 4,
        [sym_function_definition] = 4,
        [sym_declaration_specifiers] = 6,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 10,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 4,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 12,
        [aux_sym_translation_unit_repeat1] = 14,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [ts_builtin_sym_error] = 20,
        [ts_builtin_sym_end] = 22,
        [anon_sym_POUNDdefine] = 24,
        [sym_preproc_directive] = 26,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 32,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 36,
        [sym_comment] = 38,
    },
    [1] = {
        [ts_builtin_sym_end] = 40,
        [sym_comment] = 42,
    },
    [2] = {
        [sym_preproc_define] = 4,
        [sym_preproc_call] = 4,
        [sym_function_definition] = 4,
        [sym_declaration_specifiers] = 6,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 10,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 4,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 12,
        [aux_sym_translation_unit_repeat1] = 44,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [ts_builtin_sym_error] = 20,
        [ts_builtin_sym_end] = 46,
        [anon_sym_POUNDdefine] = 24,
        [sym_preproc_directive] = 26,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 32,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 36,
        [sym_comment] = 42,
    },
    [3] = {
        [sym__type_specifier] = 48,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_macro_type] = 12,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 32,
        [sym_identifier] = 36,
        [sym_comment] = 42,
    },
    [4] = {
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 50,
        [sym_numeric_type_specifier] = 50,
        [sym_struct_specifier] = 50,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 50,
        [aux_sym_declaration_specifiers_repeat1] = 52,
        [aux_sym_numeric_type_specifier_repeat1] = 50,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 50,
        [anon_sym_unsigned] = 50,
        [anon_sym_long] = 50,
        [anon_sym_short] = 50,
        [anon_sym_struct] = 50,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 50,
        [sym_comment] = 42,
    },
    [5] = {
        [sym__init_declarator] = 54,
        [sym__declarator] = 56,
        [sym_pointer_declarator] = 58,
        [sym_function_declarator] = 58,
        [sym_array_declarator] = 58,
        [anon_sym_LPAREN] = 60,
        [anon_sym_STAR] = 62,
        [sym_identifier] = 58,
        [sym_comment] = 42,
    },
    [6] = {
        [sym__init_declarator] = 64,
        [sym__declarator] = 64,
        [sym_pointer_declarator] = 64,
        [sym_function_declarator] = 64,
        [sym_array_declarator] = 64,
        [anon_sym_LPAREN] = 64,
        [anon_sym_STAR] = 64,
        [sym_identifier] = 64,
        [sym_comment] = 42,
    },
    [7] = {
        [ts_builtin_sym_end] = 66,
        [sym_comment] = 42,
    },
    [8] = {
        [sym__type_specifier] = 68,
        [sym_numeric_type_specifier] = 68,
        [sym_struct_specifier] = 68,
        [sym_macro_type] = 68,
        [aux_sym_numeric_type_specifier_repeat1] = 68,
        [anon_sym_signed] = 68,
        [anon_sym_unsigned] = 68,
        [anon_sym_long] = 68,
        [anon_sym_short] = 68,
        [anon_sym_struct] = 68,
        [sym_identifier] = 68,
        [sym_comment] = 42,
    },
    [9] = {
        [sym_identifier] = 70,
        [sym_comment] = 42,
    },
    [10] = {
        [anon_sym_SEMI] = 72,
        [sym_comment] = 42,
    },
    [11] = {
        [sym_identifier] = 74,
        [sym_comment] = 42,
    },
    [12] = {
        [sym_preproc_arg] = 76,
        [sym_comment] = 42,
    },
    [13] = {
        [sym_storage_class_specifier] = 78,
        [sym__type_specifier] = 78,
        [sym_numeric_type_specifier] = 78,
        [sym_struct_specifier] = 78,
        [sym_type_qualifier] = 78,
        [sym_macro_type] = 78,
        [aux_sym_declaration_specifiers_repeat1] = 78,
        [aux_sym_numeric_type_specifier_repeat1] = 78,
        [anon_sym_typedef] = 78,
        [anon_sym_extern] = 78,
        [anon_sym_static] = 78,
        [anon_sym_auto] = 78,
        [anon_sym_register] = 78,
        [anon_sym_signed] = 78,
        [anon_sym_unsigned] = 78,
        [anon_sym_long] = 78,
        [anon_sym_short] = 78,
        [anon_sym_struct] = 78,
        [anon_sym_const] = 78,
        [anon_sym_restrict] = 78,
        [anon_sym_volatile] = 78,
        [sym_identifier] = 78,
        [sym_comment] = 42,
    },
    [14] = {
        [aux_sym_numeric_type_specifier_repeat1] = 80,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [sym_identifier] = 82,
        [sym_comment] = 42,
    },
    [15] = {
        [anon_sym_LBRACE] = 84,
        [sym_identifier] = 86,
        [sym_comment] = 42,
    },
    [16] = {
        [sym_storage_class_specifier] = 88,
        [sym__type_specifier] = 88,
        [sym_numeric_type_specifier] = 88,
        [sym_struct_specifier] = 88,
        [sym_type_qualifier] = 88,
        [sym_macro_type] = 88,
        [aux_sym_declaration_specifiers_repeat1] = 88,
        [aux_sym_numeric_type_specifier_repeat1] = 88,
        [anon_sym_typedef] = 88,
        [anon_sym_extern] = 88,
        [anon_sym_static] = 88,
        [anon_sym_auto] = 88,
        [anon_sym_register] = 88,
        [anon_sym_signed] = 88,
        [anon_sym_unsigned] = 88,
        [anon_sym_long] = 88,
        [anon_sym_short] = 88,
        [anon_sym_struct] = 88,
        [anon_sym_const] = 88,
        [anon_sym_restrict] = 88,
        [anon_sym_volatile] = 88,
        [sym_identifier] = 88,
        [sym_comment] = 42,
    },
    [17] = {
        [sym__init_declarator] = 90,
        [sym__declarator] = 90,
        [sym_pointer_declarator] = 92,
        [sym_function_declarator] = 90,
        [sym_array_declarator] = 90,
        [anon_sym_LPAREN] = 94,
        [anon_sym_STAR] = 92,
        [sym_identifier] = 92,
        [sym_comment] = 42,
    },
    [18] = {
        [sym__type_specifier] = 97,
        [sym_numeric_type_specifier] = 99,
        [sym_struct_specifier] = 99,
        [sym_macro_type] = 99,
        [aux_sym_numeric_type_specifier_repeat1] = 101,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 103,
        [sym_identifier] = 105,
        [sym_comment] = 42,
    },
    [19] = {
        [anon_sym_RPAREN] = 107,
        [sym_comment] = 42,
    },
    [20] = {
        [anon_sym_RPAREN] = 64,
        [sym_comment] = 42,
    },
    [21] = {
        [sym_identifier] = 109,
        [sym_comment] = 42,
    },
    [22] = {
        [anon_sym_LBRACE] = 111,
        [sym_identifier] = 113,
        [sym_comment] = 42,
    },
    [23] = {
        [anon_sym_LPAREN] = 115,
        [anon_sym_RPAREN] = 92,
        [sym_comment] = 42,
    },
    [24] = {
        [sym__type_specifier] = 117,
        [sym_numeric_type_specifier] = 99,
        [sym_struct_specifier] = 99,
        [sym_macro_type] = 99,
        [aux_sym_numeric_type_specifier_repeat1] = 101,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 103,
        [sym_identifier] = 105,
        [sym_comment] = 42,
    },
    [25] = {
        [anon_sym_RPAREN] = 119,
        [sym_comment] = 42,
    },
    [26] = {
        [anon_sym_RPAREN] = 121,
        [sym_comment] = 42,
    },
    [27] = {
        [sym__type_specifier] = 123,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_struct_declaration] = 127,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [aux_sym_struct_specifier_repeat1] = 131,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RBRACE] = 135,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [28] = {
        [anon_sym_LBRACE] = 139,
        [sym_comment] = 42,
    },
    [29] = {
        [sym__type_specifier] = 123,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_struct_declaration] = 127,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [aux_sym_struct_specifier_repeat1] = 141,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RBRACE] = 143,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [30] = {
        [sym__declarator] = 145,
        [sym_pointer_declarator] = 147,
        [sym_function_declarator] = 147,
        [sym_array_declarator] = 147,
        [anon_sym_LPAREN] = 149,
        [anon_sym_STAR] = 151,
        [sym_identifier] = 147,
        [sym_comment] = 42,
    },
    [31] = {
        [sym__declarator] = 64,
        [sym_pointer_declarator] = 64,
        [sym_function_declarator] = 64,
        [sym_array_declarator] = 64,
        [anon_sym_LPAREN] = 64,
        [anon_sym_STAR] = 64,
        [sym_identifier] = 64,
        [sym_comment] = 42,
    },
    [32] = {
        [sym__type_specifier] = 123,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_struct_declaration] = 127,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [aux_sym_struct_specifier_repeat1] = 153,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RBRACE] = 155,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [33] = {
        [sym_identifier] = 157,
        [sym_comment] = 42,
    },
    [34] = {
        [anon_sym_RBRACE] = 159,
        [sym_comment] = 42,
    },
    [35] = {
        [anon_sym_LBRACE] = 161,
        [sym_identifier] = 163,
        [sym_comment] = 42,
    },
    [36] = {
        [anon_sym_RPAREN] = 165,
        [sym_comment] = 42,
    },
    [37] = {
        [sym__declarator] = 90,
        [sym_pointer_declarator] = 92,
        [sym_function_declarator] = 90,
        [sym_array_declarator] = 90,
        [anon_sym_LPAREN] = 167,
        [anon_sym_STAR] = 92,
        [sym_identifier] = 92,
        [sym_comment] = 42,
    },
    [38] = {
        [sym__type_specifier] = 170,
        [sym_numeric_type_specifier] = 99,
        [sym_struct_specifier] = 99,
        [sym_macro_type] = 99,
        [aux_sym_numeric_type_specifier_repeat1] = 101,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 103,
        [sym_identifier] = 105,
        [sym_comment] = 42,
    },
    [39] = {
        [anon_sym_RPAREN] = 172,
        [sym_comment] = 42,
    },
    [40] = {
        [sym__declarator] = 121,
        [sym_pointer_declarator] = 121,
        [sym_function_declarator] = 121,
        [sym_array_declarator] = 121,
        [anon_sym_LPAREN] = 121,
        [anon_sym_STAR] = 121,
        [sym_identifier] = 121,
        [sym_comment] = 42,
    },
    [41] = {
        [sym__type_specifier] = 123,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_struct_declaration] = 127,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [aux_sym_struct_specifier_repeat1] = 174,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RBRACE] = 176,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [42] = {
        [anon_sym_LBRACE] = 178,
        [sym_comment] = 42,
    },
    [43] = {
        [sym__type_specifier] = 123,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_struct_declaration] = 127,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [aux_sym_struct_specifier_repeat1] = 180,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RBRACE] = 182,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [44] = {
        [anon_sym_RBRACE] = 184,
        [sym_comment] = 42,
    },
    [45] = {
        [sym__declarator] = 165,
        [sym_pointer_declarator] = 165,
        [sym_function_declarator] = 165,
        [sym_array_declarator] = 165,
        [anon_sym_LPAREN] = 165,
        [anon_sym_STAR] = 165,
        [sym_identifier] = 165,
        [sym_comment] = 42,
    },
    [46] = {
        [sym__declarator] = 186,
        [sym_pointer_declarator] = 186,
        [sym_function_declarator] = 186,
        [sym_array_declarator] = 186,
        [anon_sym_LPAREN] = 186,
        [anon_sym_STAR] = 186,
        [sym_identifier] = 186,
        [sym_comment] = 42,
    },
    [47] = {
        [anon_sym_RBRACE] = 182,
        [sym_comment] = 42,
    },
    [48] = {
        [sym__declarator] = 188,
        [sym_pointer_declarator] = 188,
        [sym_function_declarator] = 188,
        [sym_array_declarator] = 188,
        [anon_sym_LPAREN] = 188,
        [anon_sym_STAR] = 188,
        [sym_identifier] = 188,
        [sym_comment] = 42,
    },
    [49] = {
        [anon_sym_RPAREN] = 186,
        [sym_comment] = 42,
    },
    [50] = {
        [sym__declarator] = 190,
        [sym_pointer_declarator] = 190,
        [sym_function_declarator] = 190,
        [sym_array_declarator] = 190,
        [anon_sym_LPAREN] = 190,
        [anon_sym_STAR] = 190,
        [sym_identifier] = 190,
        [sym_comment] = 42,
    },
    [51] = {
        [anon_sym_RBRACE] = 192,
        [sym_comment] = 42,
    },
    [52] = {
        [sym__type_specifier] = 194,
        [sym_numeric_type_specifier] = 194,
        [sym_struct_specifier] = 194,
        [sym_struct_declaration] = 194,
        [sym_macro_type] = 194,
        [aux_sym_numeric_type_specifier_repeat1] = 194,
        [aux_sym_struct_specifier_repeat1] = 194,
        [anon_sym_signed] = 194,
        [anon_sym_unsigned] = 194,
        [anon_sym_long] = 194,
        [anon_sym_short] = 194,
        [anon_sym_struct] = 194,
        [anon_sym_RBRACE] = 194,
        [anon_sym_LBRACK] = 196,
        [anon_sym_LPAREN] = 198,
        [sym_identifier] = 194,
        [sym_comment] = 42,
    },
    [53] = {
        [sym__type_specifier] = 200,
        [sym_numeric_type_specifier] = 200,
        [sym_struct_specifier] = 200,
        [sym_struct_declaration] = 200,
        [sym_macro_type] = 200,
        [aux_sym_numeric_type_specifier_repeat1] = 200,
        [aux_sym_struct_specifier_repeat1] = 200,
        [anon_sym_signed] = 200,
        [anon_sym_unsigned] = 200,
        [anon_sym_long] = 200,
        [anon_sym_short] = 200,
        [anon_sym_struct] = 200,
        [anon_sym_RBRACE] = 200,
        [anon_sym_LBRACK] = 200,
        [anon_sym_LPAREN] = 200,
        [sym_identifier] = 200,
        [sym_comment] = 42,
    },
    [54] = {
        [sym__declarator] = 202,
        [sym_pointer_declarator] = 204,
        [sym_function_declarator] = 204,
        [sym_array_declarator] = 204,
        [anon_sym_LPAREN] = 206,
        [anon_sym_STAR] = 208,
        [sym_identifier] = 204,
        [sym_comment] = 42,
    },
    [55] = {
        [sym__declarator] = 210,
        [sym_pointer_declarator] = 147,
        [sym_function_declarator] = 147,
        [sym_array_declarator] = 147,
        [anon_sym_LPAREN] = 149,
        [anon_sym_STAR] = 151,
        [sym_identifier] = 147,
        [sym_comment] = 42,
    },
    [56] = {
        [sym__type_specifier] = 212,
        [sym_numeric_type_specifier] = 212,
        [sym_struct_specifier] = 212,
        [sym_struct_declaration] = 212,
        [sym_macro_type] = 212,
        [aux_sym_numeric_type_specifier_repeat1] = 212,
        [aux_sym_struct_specifier_repeat1] = 212,
        [anon_sym_signed] = 212,
        [anon_sym_unsigned] = 212,
        [anon_sym_long] = 212,
        [anon_sym_short] = 212,
        [anon_sym_struct] = 212,
        [anon_sym_RBRACE] = 212,
        [anon_sym_LBRACK] = 196,
        [anon_sym_LPAREN] = 198,
        [sym_identifier] = 212,
        [sym_comment] = 42,
    },
    [57] = {
        [sym__expression] = 214,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_RBRACK] = 218,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [58] = {
        [sym_declaration_specifiers] = 226,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 228,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_parameter_declaration] = 230,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 125,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RPAREN] = 232,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [59] = {
        [sym__type_specifier] = 234,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [60] = {
        [sym__declarator] = 236,
        [sym_pointer_declarator] = 238,
        [sym_function_declarator] = 238,
        [sym_array_declarator] = 238,
        [anon_sym_LPAREN] = 240,
        [anon_sym_STAR] = 242,
        [sym_identifier] = 238,
        [sym_comment] = 42,
    },
    [61] = {
        [aux_sym_function_declarator_repeat1] = 244,
        [anon_sym_COMMA] = 246,
        [anon_sym_RPAREN] = 248,
        [sym_comment] = 42,
    },
    [62] = {
        [sym__type_specifier] = 250,
        [sym_numeric_type_specifier] = 250,
        [sym_struct_specifier] = 250,
        [sym_struct_declaration] = 250,
        [sym_macro_type] = 250,
        [aux_sym_numeric_type_specifier_repeat1] = 250,
        [aux_sym_struct_specifier_repeat1] = 250,
        [anon_sym_signed] = 250,
        [anon_sym_unsigned] = 250,
        [anon_sym_long] = 250,
        [anon_sym_short] = 250,
        [anon_sym_struct] = 250,
        [anon_sym_RBRACE] = 250,
        [anon_sym_LBRACK] = 250,
        [anon_sym_LPAREN] = 250,
        [sym_identifier] = 250,
        [sym_comment] = 42,
    },
    [63] = {
        [anon_sym_RPAREN] = 252,
        [sym_comment] = 42,
    },
    [64] = {
        [sym_declaration_specifiers] = 226,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 228,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_parameter_declaration] = 254,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 125,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [65] = {
        [sym__type_specifier] = 256,
        [sym_numeric_type_specifier] = 256,
        [sym_struct_specifier] = 256,
        [sym_struct_declaration] = 256,
        [sym_macro_type] = 256,
        [aux_sym_numeric_type_specifier_repeat1] = 256,
        [aux_sym_struct_specifier_repeat1] = 256,
        [anon_sym_signed] = 256,
        [anon_sym_unsigned] = 256,
        [anon_sym_long] = 256,
        [anon_sym_short] = 256,
        [anon_sym_struct] = 256,
        [anon_sym_RBRACE] = 256,
        [anon_sym_LBRACK] = 256,
        [anon_sym_LPAREN] = 256,
        [sym_identifier] = 256,
        [sym_comment] = 42,
    },
    [66] = {
        [aux_sym_function_declarator_repeat1] = 258,
        [anon_sym_COMMA] = 246,
        [anon_sym_RPAREN] = 260,
        [sym_comment] = 42,
    },
    [67] = {
        [anon_sym_RPAREN] = 262,
        [sym_comment] = 42,
    },
    [68] = {
        [sym__type_specifier] = 264,
        [sym_numeric_type_specifier] = 264,
        [sym_struct_specifier] = 264,
        [sym_struct_declaration] = 264,
        [sym_macro_type] = 264,
        [aux_sym_numeric_type_specifier_repeat1] = 264,
        [aux_sym_struct_specifier_repeat1] = 264,
        [anon_sym_signed] = 264,
        [anon_sym_unsigned] = 264,
        [anon_sym_long] = 264,
        [anon_sym_short] = 264,
        [anon_sym_struct] = 264,
        [anon_sym_RBRACE] = 264,
        [anon_sym_LBRACK] = 264,
        [anon_sym_LPAREN] = 264,
        [sym_identifier] = 264,
        [sym_comment] = 42,
    },
    [69] = {
        [aux_sym_function_declarator_repeat1] = 266,
        [anon_sym_COMMA] = 266,
        [anon_sym_LBRACK] = 268,
        [anon_sym_LPAREN] = 270,
        [anon_sym_RPAREN] = 266,
        [sym_comment] = 42,
    },
    [70] = {
        [aux_sym_function_declarator_repeat1] = 200,
        [anon_sym_COMMA] = 200,
        [anon_sym_LBRACK] = 200,
        [anon_sym_LPAREN] = 200,
        [anon_sym_RPAREN] = 200,
        [sym_comment] = 42,
    },
    [71] = {
        [sym__declarator] = 272,
        [sym_pointer_declarator] = 204,
        [sym_function_declarator] = 204,
        [sym_array_declarator] = 204,
        [anon_sym_LPAREN] = 206,
        [anon_sym_STAR] = 208,
        [sym_identifier] = 204,
        [sym_comment] = 42,
    },
    [72] = {
        [sym__declarator] = 274,
        [sym_pointer_declarator] = 238,
        [sym_function_declarator] = 238,
        [sym_array_declarator] = 238,
        [anon_sym_LPAREN] = 240,
        [anon_sym_STAR] = 242,
        [sym_identifier] = 238,
        [sym_comment] = 42,
    },
    [73] = {
        [aux_sym_function_declarator_repeat1] = 212,
        [anon_sym_COMMA] = 212,
        [anon_sym_LBRACK] = 268,
        [anon_sym_LPAREN] = 270,
        [anon_sym_RPAREN] = 212,
        [sym_comment] = 42,
    },
    [74] = {
        [sym__expression] = 276,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_RBRACK] = 278,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [75] = {
        [sym_declaration_specifiers] = 226,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 228,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_parameter_declaration] = 280,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 125,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RPAREN] = 282,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [76] = {
        [aux_sym_function_declarator_repeat1] = 284,
        [anon_sym_COMMA] = 246,
        [anon_sym_RPAREN] = 286,
        [sym_comment] = 42,
    },
    [77] = {
        [aux_sym_function_declarator_repeat1] = 250,
        [anon_sym_COMMA] = 250,
        [anon_sym_LBRACK] = 250,
        [anon_sym_LPAREN] = 250,
        [anon_sym_RPAREN] = 250,
        [sym_comment] = 42,
    },
    [78] = {
        [anon_sym_RPAREN] = 288,
        [sym_comment] = 42,
    },
    [79] = {
        [aux_sym_function_declarator_repeat1] = 256,
        [anon_sym_COMMA] = 256,
        [anon_sym_LBRACK] = 256,
        [anon_sym_LPAREN] = 256,
        [anon_sym_RPAREN] = 256,
        [sym_comment] = 42,
    },
    [80] = {
        [aux_sym_function_declarator_repeat1] = 264,
        [anon_sym_COMMA] = 264,
        [anon_sym_LBRACK] = 264,
        [anon_sym_LPAREN] = 264,
        [anon_sym_RPAREN] = 264,
        [sym_comment] = 42,
    },
    [81] = {
        [anon_sym_EQ] = 290,
        [anon_sym_RBRACK] = 292,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 298,
        [sym_comment] = 42,
    },
    [82] = {
        [anon_sym_EQ] = 300,
        [anon_sym_RBRACK] = 300,
        [anon_sym_LPAREN] = 300,
        [anon_sym_STAR] = 300,
        [anon_sym_PLUS] = 300,
        [sym_comment] = 42,
    },
    [83] = {
        [aux_sym_function_declarator_repeat1] = 302,
        [anon_sym_COMMA] = 302,
        [anon_sym_LBRACK] = 302,
        [anon_sym_LPAREN] = 302,
        [anon_sym_RPAREN] = 302,
        [sym_comment] = 42,
    },
    [84] = {
        [sym__type_specifier] = 304,
        [sym_numeric_type_specifier] = 306,
        [sym_struct_specifier] = 306,
        [sym_type_name] = 308,
        [sym_type_qualifier] = 310,
        [sym__expression] = 312,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [sym_macro_type] = 306,
        [aux_sym_numeric_type_specifier_repeat1] = 316,
        [aux_sym_type_name_repeat1] = 318,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 320,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_const] = 326,
        [anon_sym_restrict] = 326,
        [anon_sym_volatile] = 326,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 328,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [85] = {
        [sym__expression] = 330,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [86] = {
        [anon_sym_EQ] = 332,
        [anon_sym_RBRACK] = 332,
        [anon_sym_LPAREN] = 332,
        [anon_sym_STAR] = 332,
        [anon_sym_PLUS] = 332,
        [sym_comment] = 42,
    },
    [87] = {
        [anon_sym_EQ] = 334,
        [anon_sym_RBRACK] = 334,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 298,
        [sym_comment] = 42,
    },
    [88] = {
        [sym__expression] = 336,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_RPAREN] = 342,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [89] = {
        [sym__expression] = 348,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [90] = {
        [sym__expression] = 350,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [91] = {
        [anon_sym_EQ] = 352,
        [anon_sym_RBRACK] = 352,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [92] = {
        [anon_sym_EQ] = 352,
        [anon_sym_RBRACK] = 352,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 352,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [93] = {
        [aux_sym_call_expression_repeat1] = 354,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 362,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [94] = {
        [aux_sym_call_expression_repeat1] = 300,
        [anon_sym_COMMA] = 300,
        [anon_sym_EQ] = 300,
        [anon_sym_LPAREN] = 300,
        [anon_sym_RPAREN] = 300,
        [anon_sym_STAR] = 300,
        [anon_sym_PLUS] = 300,
        [sym_comment] = 42,
    },
    [95] = {
        [sym__type_specifier] = 304,
        [sym_numeric_type_specifier] = 306,
        [sym_struct_specifier] = 306,
        [sym_type_name] = 368,
        [sym_type_qualifier] = 310,
        [sym__expression] = 370,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [sym_macro_type] = 306,
        [aux_sym_numeric_type_specifier_repeat1] = 316,
        [aux_sym_type_name_repeat1] = 318,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 320,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_const] = 326,
        [anon_sym_restrict] = 326,
        [anon_sym_volatile] = 326,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 328,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [96] = {
        [anon_sym_EQ] = 372,
        [anon_sym_RBRACK] = 372,
        [anon_sym_LPAREN] = 372,
        [anon_sym_STAR] = 372,
        [anon_sym_PLUS] = 372,
        [sym_comment] = 42,
    },
    [97] = {
        [sym__expression] = 374,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [98] = {
        [aux_sym_call_expression_repeat1] = 332,
        [anon_sym_COMMA] = 332,
        [anon_sym_EQ] = 332,
        [anon_sym_LPAREN] = 332,
        [anon_sym_RPAREN] = 332,
        [anon_sym_STAR] = 332,
        [anon_sym_PLUS] = 332,
        [sym_comment] = 42,
    },
    [99] = {
        [aux_sym_call_expression_repeat1] = 334,
        [anon_sym_COMMA] = 334,
        [anon_sym_EQ] = 334,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 334,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [100] = {
        [sym__expression] = 376,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_RPAREN] = 378,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [101] = {
        [sym__expression] = 380,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [102] = {
        [sym__expression] = 382,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [103] = {
        [aux_sym_call_expression_repeat1] = 352,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 352,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [104] = {
        [aux_sym_call_expression_repeat1] = 352,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 352,
        [anon_sym_STAR] = 352,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [105] = {
        [aux_sym_call_expression_repeat1] = 384,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 386,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [106] = {
        [aux_sym_call_expression_repeat1] = 372,
        [anon_sym_COMMA] = 372,
        [anon_sym_EQ] = 372,
        [anon_sym_LPAREN] = 372,
        [anon_sym_RPAREN] = 372,
        [anon_sym_STAR] = 372,
        [anon_sym_PLUS] = 372,
        [sym_comment] = 42,
    },
    [107] = {
        [anon_sym_RPAREN] = 388,
        [sym_comment] = 42,
    },
    [108] = {
        [sym__expression] = 390,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [109] = {
        [sym__expression] = 392,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [110] = {
        [aux_sym_call_expression_repeat1] = 394,
        [anon_sym_COMMA] = 394,
        [anon_sym_EQ] = 394,
        [anon_sym_LPAREN] = 394,
        [anon_sym_RPAREN] = 394,
        [anon_sym_STAR] = 394,
        [anon_sym_PLUS] = 394,
        [sym_comment] = 42,
    },
    [111] = {
        [aux_sym_call_expression_repeat1] = 396,
        [anon_sym_COMMA] = 396,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 396,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [112] = {
        [aux_sym_call_expression_repeat1] = 398,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 400,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [113] = {
        [anon_sym_RPAREN] = 402,
        [sym_comment] = 42,
    },
    [114] = {
        [aux_sym_call_expression_repeat1] = 404,
        [anon_sym_COMMA] = 404,
        [anon_sym_EQ] = 404,
        [anon_sym_LPAREN] = 404,
        [anon_sym_RPAREN] = 404,
        [anon_sym_STAR] = 404,
        [anon_sym_PLUS] = 404,
        [sym_comment] = 42,
    },
    [115] = {
        [sym__abstract_declarator] = 406,
        [sym_abstract_pointer_declarator] = 408,
        [sym_abstract_function_declarator] = 408,
        [sym_abstract_array_declarator] = 408,
        [anon_sym_LPAREN] = 410,
        [anon_sym_RPAREN] = 412,
        [anon_sym_STAR] = 414,
        [sym_comment] = 42,
    },
    [116] = {
        [sym__abstract_declarator] = 64,
        [sym_abstract_pointer_declarator] = 64,
        [sym_abstract_function_declarator] = 64,
        [sym_abstract_array_declarator] = 64,
        [anon_sym_LPAREN] = 64,
        [anon_sym_RPAREN] = 64,
        [anon_sym_STAR] = 64,
        [sym_comment] = 42,
    },
    [117] = {
        [anon_sym_RPAREN] = 416,
        [sym_comment] = 42,
    },
    [118] = {
        [sym__type_specifier] = 418,
        [sym_numeric_type_specifier] = 418,
        [sym_struct_specifier] = 418,
        [sym_type_qualifier] = 310,
        [sym_macro_type] = 418,
        [aux_sym_numeric_type_specifier_repeat1] = 418,
        [aux_sym_type_name_repeat1] = 420,
        [anon_sym_signed] = 418,
        [anon_sym_unsigned] = 418,
        [anon_sym_long] = 418,
        [anon_sym_short] = 418,
        [anon_sym_struct] = 418,
        [anon_sym_const] = 326,
        [anon_sym_restrict] = 326,
        [anon_sym_volatile] = 326,
        [sym_identifier] = 418,
        [sym_comment] = 42,
    },
    [119] = {
        [anon_sym_EQ] = 422,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 426,
        [anon_sym_STAR] = 428,
        [anon_sym_PLUS] = 430,
        [sym_comment] = 42,
    },
    [120] = {
        [anon_sym_EQ] = 300,
        [anon_sym_LPAREN] = 300,
        [anon_sym_RPAREN] = 300,
        [anon_sym_STAR] = 300,
        [anon_sym_PLUS] = 300,
        [sym_comment] = 42,
    },
    [121] = {
        [sym_identifier] = 432,
        [sym_comment] = 42,
    },
    [122] = {
        [sym__type_specifier] = 434,
        [sym_numeric_type_specifier] = 306,
        [sym_struct_specifier] = 306,
        [sym_macro_type] = 306,
        [aux_sym_numeric_type_specifier_repeat1] = 316,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 320,
        [sym_identifier] = 436,
        [sym_comment] = 42,
    },
    [123] = {
        [anon_sym_LBRACE] = 438,
        [sym_identifier] = 440,
        [sym_comment] = 42,
    },
    [124] = {
        [sym__type_specifier] = 304,
        [sym_numeric_type_specifier] = 306,
        [sym_struct_specifier] = 306,
        [sym_type_name] = 442,
        [sym_type_qualifier] = 310,
        [sym__expression] = 444,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [sym_macro_type] = 306,
        [aux_sym_numeric_type_specifier_repeat1] = 316,
        [aux_sym_type_name_repeat1] = 318,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 320,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_const] = 326,
        [anon_sym_restrict] = 326,
        [anon_sym_volatile] = 326,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 328,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [125] = {
        [sym__expression] = 446,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 448,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [126] = {
        [sym__type_specifier] = 88,
        [sym_numeric_type_specifier] = 88,
        [sym_struct_specifier] = 88,
        [sym_type_qualifier] = 88,
        [sym_macro_type] = 88,
        [aux_sym_numeric_type_specifier_repeat1] = 88,
        [aux_sym_type_name_repeat1] = 88,
        [anon_sym_signed] = 88,
        [anon_sym_unsigned] = 88,
        [anon_sym_long] = 88,
        [anon_sym_short] = 88,
        [anon_sym_struct] = 88,
        [anon_sym_const] = 88,
        [anon_sym_restrict] = 88,
        [anon_sym_volatile] = 88,
        [sym_identifier] = 88,
        [sym_comment] = 42,
    },
    [127] = {
        [sym__abstract_declarator] = 90,
        [sym_abstract_pointer_declarator] = 90,
        [sym_abstract_function_declarator] = 90,
        [sym_abstract_array_declarator] = 90,
        [anon_sym_EQ] = 332,
        [anon_sym_LPAREN] = 450,
        [anon_sym_RPAREN] = 454,
        [anon_sym_STAR] = 454,
        [anon_sym_PLUS] = 332,
        [sym_comment] = 42,
    },
    [128] = {
        [sym__type_specifier] = 457,
        [sym_numeric_type_specifier] = 99,
        [sym_struct_specifier] = 99,
        [sym_macro_type] = 99,
        [aux_sym_numeric_type_specifier_repeat1] = 101,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 103,
        [sym_identifier] = 105,
        [sym_comment] = 42,
    },
    [129] = {
        [anon_sym_RPAREN] = 459,
        [sym_comment] = 42,
    },
    [130] = {
        [sym__abstract_declarator] = 121,
        [sym_abstract_pointer_declarator] = 121,
        [sym_abstract_function_declarator] = 121,
        [sym_abstract_array_declarator] = 121,
        [anon_sym_LPAREN] = 121,
        [anon_sym_RPAREN] = 121,
        [anon_sym_STAR] = 121,
        [sym_comment] = 42,
    },
    [131] = {
        [anon_sym_EQ] = 334,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 334,
        [anon_sym_STAR] = 428,
        [anon_sym_PLUS] = 430,
        [sym_comment] = 42,
    },
    [132] = {
        [anon_sym_EQ] = 332,
        [anon_sym_LPAREN] = 332,
        [anon_sym_RPAREN] = 332,
        [anon_sym_STAR] = 332,
        [anon_sym_PLUS] = 332,
        [sym_comment] = 42,
    },
    [133] = {
        [sym__expression] = 461,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_RPAREN] = 463,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [134] = {
        [sym__expression] = 465,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 448,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [135] = {
        [sym__expression] = 467,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 448,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [136] = {
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 352,
        [anon_sym_STAR] = 428,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [137] = {
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 352,
        [anon_sym_STAR] = 352,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [138] = {
        [aux_sym_call_expression_repeat1] = 469,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 471,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [139] = {
        [anon_sym_EQ] = 372,
        [anon_sym_LPAREN] = 372,
        [anon_sym_RPAREN] = 372,
        [anon_sym_STAR] = 372,
        [anon_sym_PLUS] = 372,
        [sym_comment] = 42,
    },
    [140] = {
        [anon_sym_RPAREN] = 473,
        [sym_comment] = 42,
    },
    [141] = {
        [anon_sym_EQ] = 394,
        [anon_sym_LPAREN] = 394,
        [anon_sym_RPAREN] = 394,
        [anon_sym_STAR] = 394,
        [anon_sym_PLUS] = 394,
        [sym_comment] = 42,
    },
    [142] = {
        [anon_sym_EQ] = 404,
        [anon_sym_LPAREN] = 404,
        [anon_sym_RPAREN] = 404,
        [anon_sym_STAR] = 404,
        [anon_sym_PLUS] = 404,
        [sym_comment] = 42,
    },
    [143] = {
        [anon_sym_RPAREN] = 475,
        [sym_comment] = 42,
    },
    [144] = {
        [anon_sym_EQ] = 422,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 477,
        [anon_sym_STAR] = 428,
        [anon_sym_PLUS] = 430,
        [sym_comment] = 42,
    },
    [145] = {
        [sym__expression] = 479,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 448,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [146] = {
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_RPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 42,
    },
    [147] = {
        [anon_sym_EQ] = 422,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 396,
        [anon_sym_STAR] = 428,
        [anon_sym_PLUS] = 430,
        [sym_comment] = 42,
    },
    [148] = {
        [sym__expression] = 483,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 448,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [149] = {
        [anon_sym_EQ] = 485,
        [anon_sym_LPAREN] = 485,
        [anon_sym_RPAREN] = 485,
        [anon_sym_STAR] = 485,
        [anon_sym_PLUS] = 485,
        [sym_comment] = 42,
    },
    [150] = {
        [sym__type_specifier] = 123,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_struct_declaration] = 127,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [aux_sym_struct_specifier_repeat1] = 487,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RBRACE] = 489,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [151] = {
        [anon_sym_LBRACE] = 491,
        [sym_comment] = 42,
    },
    [152] = {
        [sym__type_specifier] = 123,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_struct_declaration] = 127,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [aux_sym_struct_specifier_repeat1] = 493,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RBRACE] = 495,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [153] = {
        [anon_sym_RBRACE] = 497,
        [sym_comment] = 42,
    },
    [154] = {
        [sym__abstract_declarator] = 165,
        [sym_abstract_pointer_declarator] = 165,
        [sym_abstract_function_declarator] = 165,
        [sym_abstract_array_declarator] = 165,
        [anon_sym_LPAREN] = 165,
        [anon_sym_RPAREN] = 165,
        [anon_sym_STAR] = 165,
        [sym_comment] = 42,
    },
    [155] = {
        [sym__abstract_declarator] = 186,
        [sym_abstract_pointer_declarator] = 186,
        [sym_abstract_function_declarator] = 186,
        [sym_abstract_array_declarator] = 186,
        [anon_sym_LPAREN] = 186,
        [anon_sym_RPAREN] = 186,
        [anon_sym_STAR] = 186,
        [sym_comment] = 42,
    },
    [156] = {
        [anon_sym_RBRACE] = 495,
        [sym_comment] = 42,
    },
    [157] = {
        [sym__abstract_declarator] = 188,
        [sym_abstract_pointer_declarator] = 188,
        [sym_abstract_function_declarator] = 188,
        [sym_abstract_array_declarator] = 188,
        [anon_sym_LPAREN] = 188,
        [anon_sym_RPAREN] = 188,
        [anon_sym_STAR] = 188,
        [sym_comment] = 42,
    },
    [158] = {
        [sym__abstract_declarator] = 499,
        [sym_abstract_pointer_declarator] = 408,
        [sym_abstract_function_declarator] = 408,
        [sym_abstract_array_declarator] = 408,
        [anon_sym_LPAREN] = 410,
        [anon_sym_RPAREN] = 501,
        [anon_sym_STAR] = 414,
        [sym_comment] = 42,
    },
    [159] = {
        [sym__abstract_declarator] = 90,
        [sym_abstract_pointer_declarator] = 92,
        [sym_abstract_function_declarator] = 90,
        [sym_abstract_array_declarator] = 90,
        [anon_sym_LPAREN] = 503,
        [anon_sym_RPAREN] = 92,
        [anon_sym_STAR] = 92,
        [sym_comment] = 42,
    },
    [160] = {
        [anon_sym_LBRACK] = 506,
        [anon_sym_LPAREN] = 508,
        [anon_sym_RPAREN] = 510,
        [sym_comment] = 42,
    },
    [161] = {
        [anon_sym_LBRACK] = 512,
        [anon_sym_LPAREN] = 512,
        [anon_sym_RPAREN] = 512,
        [sym_comment] = 42,
    },
    [162] = {
        [sym__abstract_declarator] = 514,
        [sym_abstract_pointer_declarator] = 408,
        [sym_abstract_function_declarator] = 408,
        [sym_abstract_array_declarator] = 408,
        [anon_sym_LPAREN] = 410,
        [anon_sym_STAR] = 414,
        [sym_comment] = 42,
    },
    [163] = {
        [sym__abstract_declarator] = 516,
        [sym_abstract_pointer_declarator] = 408,
        [sym_abstract_function_declarator] = 408,
        [sym_abstract_array_declarator] = 408,
        [anon_sym_LBRACK] = 518,
        [anon_sym_LPAREN] = 410,
        [anon_sym_RPAREN] = 518,
        [anon_sym_STAR] = 414,
        [sym_comment] = 42,
    },
    [164] = {
        [anon_sym_LBRACK] = 506,
        [anon_sym_LPAREN] = 508,
        [anon_sym_RPAREN] = 520,
        [sym_comment] = 42,
    },
    [165] = {
        [sym__expression] = 522,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_RBRACK] = 524,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [166] = {
        [sym_declaration_specifiers] = 226,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 228,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_parameter_declaration] = 526,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 125,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RPAREN] = 528,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [167] = {
        [aux_sym_function_declarator_repeat1] = 530,
        [anon_sym_COMMA] = 246,
        [anon_sym_RPAREN] = 532,
        [sym_comment] = 42,
    },
    [168] = {
        [anon_sym_LBRACK] = 534,
        [anon_sym_LPAREN] = 534,
        [anon_sym_RPAREN] = 534,
        [sym_comment] = 42,
    },
    [169] = {
        [anon_sym_RPAREN] = 536,
        [sym_comment] = 42,
    },
    [170] = {
        [anon_sym_LBRACK] = 538,
        [anon_sym_LPAREN] = 538,
        [anon_sym_RPAREN] = 538,
        [sym_comment] = 42,
    },
    [171] = {
        [anon_sym_LBRACK] = 540,
        [anon_sym_LPAREN] = 540,
        [anon_sym_RPAREN] = 540,
        [sym_comment] = 42,
    },
    [172] = {
        [anon_sym_EQ] = 290,
        [anon_sym_RBRACK] = 542,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 298,
        [sym_comment] = 42,
    },
    [173] = {
        [anon_sym_LBRACK] = 544,
        [anon_sym_LPAREN] = 544,
        [anon_sym_RPAREN] = 544,
        [sym_comment] = 42,
    },
    [174] = {
        [sym__expression] = 546,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [175] = {
        [anon_sym_LBRACK] = 548,
        [anon_sym_LPAREN] = 548,
        [anon_sym_RPAREN] = 548,
        [sym_comment] = 42,
    },
    [176] = {
        [anon_sym_EQ] = 290,
        [anon_sym_RBRACK] = 396,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 298,
        [sym_comment] = 42,
    },
    [177] = {
        [anon_sym_LBRACK] = 506,
        [anon_sym_LPAREN] = 508,
        [anon_sym_RPAREN] = 550,
        [sym_comment] = 42,
    },
    [178] = {
        [anon_sym_LBRACK] = 552,
        [anon_sym_LPAREN] = 552,
        [anon_sym_RPAREN] = 552,
        [sym_comment] = 42,
    },
    [179] = {
        [sym__abstract_declarator] = 190,
        [sym_abstract_pointer_declarator] = 190,
        [sym_abstract_function_declarator] = 190,
        [sym_abstract_array_declarator] = 190,
        [anon_sym_LPAREN] = 190,
        [anon_sym_RPAREN] = 190,
        [anon_sym_STAR] = 190,
        [sym_comment] = 42,
    },
    [180] = {
        [aux_sym_call_expression_repeat1] = 481,
        [anon_sym_COMMA] = 481,
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_RPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 42,
    },
    [181] = {
        [sym__type_specifier] = 554,
        [sym_numeric_type_specifier] = 554,
        [sym_struct_specifier] = 554,
        [sym_macro_type] = 554,
        [aux_sym_numeric_type_specifier_repeat1] = 554,
        [anon_sym_signed] = 554,
        [anon_sym_unsigned] = 554,
        [anon_sym_long] = 554,
        [anon_sym_short] = 554,
        [anon_sym_struct] = 554,
        [sym_identifier] = 554,
        [sym_comment] = 42,
    },
    [182] = {
        [sym__expression] = 556,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [183] = {
        [aux_sym_call_expression_repeat1] = 485,
        [anon_sym_COMMA] = 485,
        [anon_sym_EQ] = 485,
        [anon_sym_LPAREN] = 485,
        [anon_sym_RPAREN] = 485,
        [anon_sym_STAR] = 485,
        [anon_sym_PLUS] = 485,
        [sym_comment] = 42,
    },
    [184] = {
        [anon_sym_LBRACK] = 506,
        [anon_sym_LPAREN] = 508,
        [anon_sym_RPAREN] = 501,
        [sym_comment] = 42,
    },
    [185] = {
        [anon_sym_RPAREN] = 558,
        [sym_comment] = 42,
    },
    [186] = {
        [anon_sym_EQ] = 394,
        [anon_sym_RBRACK] = 394,
        [anon_sym_LPAREN] = 394,
        [anon_sym_STAR] = 394,
        [anon_sym_PLUS] = 394,
        [sym_comment] = 42,
    },
    [187] = {
        [anon_sym_EQ] = 404,
        [anon_sym_RBRACK] = 404,
        [anon_sym_LPAREN] = 404,
        [anon_sym_STAR] = 404,
        [anon_sym_PLUS] = 404,
        [sym_comment] = 42,
    },
    [188] = {
        [anon_sym_RPAREN] = 560,
        [sym_comment] = 42,
    },
    [189] = {
        [anon_sym_EQ] = 422,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 562,
        [anon_sym_STAR] = 428,
        [anon_sym_PLUS] = 430,
        [sym_comment] = 42,
    },
    [190] = {
        [anon_sym_EQ] = 481,
        [anon_sym_RBRACK] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 42,
    },
    [191] = {
        [sym__expression] = 564,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [192] = {
        [anon_sym_EQ] = 485,
        [anon_sym_RBRACK] = 485,
        [anon_sym_LPAREN] = 485,
        [anon_sym_STAR] = 485,
        [anon_sym_PLUS] = 485,
        [sym_comment] = 42,
    },
    [193] = {
        [aux_sym_function_declarator_repeat1] = 566,
        [anon_sym_COMMA] = 566,
        [anon_sym_LBRACK] = 566,
        [anon_sym_LPAREN] = 566,
        [anon_sym_RPAREN] = 566,
        [sym_comment] = 42,
    },
    [194] = {
        [anon_sym_LBRACK] = 568,
        [anon_sym_LPAREN] = 570,
        [anon_sym_RPAREN] = 572,
        [sym_comment] = 42,
    },
    [195] = {
        [anon_sym_LBRACK] = 200,
        [anon_sym_LPAREN] = 200,
        [anon_sym_RPAREN] = 200,
        [sym_comment] = 42,
    },
    [196] = {
        [sym__declarator] = 574,
        [sym_pointer_declarator] = 204,
        [sym_function_declarator] = 204,
        [sym_array_declarator] = 204,
        [anon_sym_LPAREN] = 206,
        [anon_sym_STAR] = 208,
        [sym_identifier] = 204,
        [sym_comment] = 42,
    },
    [197] = {
        [sym__declarator] = 576,
        [sym_pointer_declarator] = 204,
        [sym_function_declarator] = 204,
        [sym_array_declarator] = 204,
        [anon_sym_LPAREN] = 206,
        [anon_sym_STAR] = 208,
        [sym_identifier] = 204,
        [sym_comment] = 42,
    },
    [198] = {
        [anon_sym_LBRACK] = 568,
        [anon_sym_LPAREN] = 570,
        [anon_sym_RPAREN] = 212,
        [sym_comment] = 42,
    },
    [199] = {
        [sym__expression] = 578,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_RBRACK] = 580,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [200] = {
        [sym_declaration_specifiers] = 226,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 228,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_parameter_declaration] = 582,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 125,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RPAREN] = 584,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [201] = {
        [aux_sym_function_declarator_repeat1] = 586,
        [anon_sym_COMMA] = 246,
        [anon_sym_RPAREN] = 588,
        [sym_comment] = 42,
    },
    [202] = {
        [anon_sym_LBRACK] = 250,
        [anon_sym_LPAREN] = 250,
        [anon_sym_RPAREN] = 250,
        [sym_comment] = 42,
    },
    [203] = {
        [anon_sym_RPAREN] = 590,
        [sym_comment] = 42,
    },
    [204] = {
        [anon_sym_LBRACK] = 256,
        [anon_sym_LPAREN] = 256,
        [anon_sym_RPAREN] = 256,
        [sym_comment] = 42,
    },
    [205] = {
        [anon_sym_LBRACK] = 264,
        [anon_sym_LPAREN] = 264,
        [anon_sym_RPAREN] = 264,
        [sym_comment] = 42,
    },
    [206] = {
        [anon_sym_EQ] = 290,
        [anon_sym_RBRACK] = 592,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 298,
        [sym_comment] = 42,
    },
    [207] = {
        [anon_sym_LBRACK] = 302,
        [anon_sym_LPAREN] = 302,
        [anon_sym_RPAREN] = 302,
        [sym_comment] = 42,
    },
    [208] = {
        [anon_sym_LBRACK] = 566,
        [anon_sym_LPAREN] = 566,
        [anon_sym_RPAREN] = 566,
        [sym_comment] = 42,
    },
    [209] = {
        [anon_sym_LBRACK] = 568,
        [anon_sym_LPAREN] = 570,
        [anon_sym_RPAREN] = 594,
        [sym_comment] = 42,
    },
    [210] = {
        [anon_sym_LBRACK] = 596,
        [anon_sym_LPAREN] = 596,
        [anon_sym_RPAREN] = 596,
        [sym_comment] = 42,
    },
    [211] = {
        [aux_sym_function_declarator_repeat1] = 596,
        [anon_sym_COMMA] = 596,
        [anon_sym_LBRACK] = 596,
        [anon_sym_LPAREN] = 596,
        [anon_sym_RPAREN] = 596,
        [sym_comment] = 42,
    },
    [212] = {
        [sym__declarator] = 598,
        [sym_pointer_declarator] = 238,
        [sym_function_declarator] = 238,
        [sym_array_declarator] = 238,
        [anon_sym_LPAREN] = 240,
        [anon_sym_STAR] = 242,
        [sym_identifier] = 238,
        [sym_comment] = 42,
    },
    [213] = {
        [aux_sym_function_declarator_repeat1] = 600,
        [anon_sym_COMMA] = 600,
        [anon_sym_LBRACK] = 268,
        [anon_sym_LPAREN] = 270,
        [anon_sym_RPAREN] = 600,
        [sym_comment] = 42,
    },
    [214] = {
        [anon_sym_EQ] = 290,
        [anon_sym_RBRACK] = 602,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 298,
        [sym_comment] = 42,
    },
    [215] = {
        [sym__type_specifier] = 302,
        [sym_numeric_type_specifier] = 302,
        [sym_struct_specifier] = 302,
        [sym_struct_declaration] = 302,
        [sym_macro_type] = 302,
        [aux_sym_numeric_type_specifier_repeat1] = 302,
        [aux_sym_struct_specifier_repeat1] = 302,
        [anon_sym_signed] = 302,
        [anon_sym_unsigned] = 302,
        [anon_sym_long] = 302,
        [anon_sym_short] = 302,
        [anon_sym_struct] = 302,
        [anon_sym_RBRACE] = 302,
        [anon_sym_LBRACK] = 302,
        [anon_sym_LPAREN] = 302,
        [sym_identifier] = 302,
        [sym_comment] = 42,
    },
    [216] = {
        [sym__type_specifier] = 566,
        [sym_numeric_type_specifier] = 566,
        [sym_struct_specifier] = 566,
        [sym_struct_declaration] = 566,
        [sym_macro_type] = 566,
        [aux_sym_numeric_type_specifier_repeat1] = 566,
        [aux_sym_struct_specifier_repeat1] = 566,
        [anon_sym_signed] = 566,
        [anon_sym_unsigned] = 566,
        [anon_sym_long] = 566,
        [anon_sym_short] = 566,
        [anon_sym_struct] = 566,
        [anon_sym_RBRACE] = 566,
        [anon_sym_LBRACK] = 566,
        [anon_sym_LPAREN] = 566,
        [sym_identifier] = 566,
        [sym_comment] = 42,
    },
    [217] = {
        [anon_sym_LBRACK] = 568,
        [anon_sym_LPAREN] = 570,
        [anon_sym_RPAREN] = 604,
        [sym_comment] = 42,
    },
    [218] = {
        [sym__type_specifier] = 596,
        [sym_numeric_type_specifier] = 596,
        [sym_struct_specifier] = 596,
        [sym_struct_declaration] = 596,
        [sym_macro_type] = 596,
        [aux_sym_numeric_type_specifier_repeat1] = 596,
        [aux_sym_struct_specifier_repeat1] = 596,
        [anon_sym_signed] = 596,
        [anon_sym_unsigned] = 596,
        [anon_sym_long] = 596,
        [anon_sym_short] = 596,
        [anon_sym_struct] = 596,
        [anon_sym_RBRACE] = 596,
        [anon_sym_LBRACK] = 596,
        [anon_sym_LPAREN] = 596,
        [sym_identifier] = 596,
        [sym_comment] = 42,
    },
    [219] = {
        [anon_sym_RBRACE] = 143,
        [sym_comment] = 42,
    },
    [220] = {
        [anon_sym_RPAREN] = 188,
        [sym_comment] = 42,
    },
    [221] = {
        [anon_sym_RPAREN] = 190,
        [sym_comment] = 42,
    },
    [222] = {
        [sym__init_declarator] = 121,
        [sym__declarator] = 121,
        [sym_pointer_declarator] = 121,
        [sym_function_declarator] = 121,
        [sym_array_declarator] = 121,
        [anon_sym_LPAREN] = 121,
        [anon_sym_STAR] = 121,
        [sym_identifier] = 121,
        [sym_comment] = 42,
    },
    [223] = {
        [sym__type_specifier] = 123,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_struct_declaration] = 127,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [aux_sym_struct_specifier_repeat1] = 606,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RBRACE] = 608,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [224] = {
        [anon_sym_LBRACE] = 610,
        [sym_comment] = 42,
    },
    [225] = {
        [sym__type_specifier] = 123,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_struct_declaration] = 127,
        [sym_macro_type] = 125,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [aux_sym_struct_specifier_repeat1] = 612,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RBRACE] = 614,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [226] = {
        [anon_sym_RBRACE] = 616,
        [sym_comment] = 42,
    },
    [227] = {
        [sym__init_declarator] = 165,
        [sym__declarator] = 165,
        [sym_pointer_declarator] = 165,
        [sym_function_declarator] = 165,
        [sym_array_declarator] = 165,
        [anon_sym_LPAREN] = 165,
        [anon_sym_STAR] = 165,
        [sym_identifier] = 165,
        [sym_comment] = 42,
    },
    [228] = {
        [sym__init_declarator] = 186,
        [sym__declarator] = 186,
        [sym_pointer_declarator] = 186,
        [sym_function_declarator] = 186,
        [sym_array_declarator] = 186,
        [anon_sym_LPAREN] = 186,
        [anon_sym_STAR] = 186,
        [sym_identifier] = 186,
        [sym_comment] = 42,
    },
    [229] = {
        [anon_sym_RBRACE] = 614,
        [sym_comment] = 42,
    },
    [230] = {
        [sym__init_declarator] = 188,
        [sym__declarator] = 188,
        [sym_pointer_declarator] = 188,
        [sym_function_declarator] = 188,
        [sym_array_declarator] = 188,
        [anon_sym_LPAREN] = 188,
        [anon_sym_STAR] = 188,
        [sym_identifier] = 188,
        [sym_comment] = 42,
    },
    [231] = {
        [sym_identifier] = 618,
        [sym_comment] = 42,
    },
    [232] = {
        [sym_preproc_define] = 620,
        [sym_preproc_call] = 620,
        [sym_function_definition] = 620,
        [sym_declaration_specifiers] = 620,
        [sym_storage_class_specifier] = 620,
        [sym__type_specifier] = 620,
        [sym_numeric_type_specifier] = 620,
        [sym_struct_specifier] = 620,
        [sym_declaration] = 620,
        [sym_type_qualifier] = 620,
        [sym_macro_type] = 620,
        [aux_sym_translation_unit_repeat1] = 620,
        [aux_sym_declaration_specifiers_repeat1] = 620,
        [aux_sym_numeric_type_specifier_repeat1] = 620,
        [ts_builtin_sym_error] = 620,
        [ts_builtin_sym_end] = 620,
        [anon_sym_POUNDdefine] = 620,
        [sym_preproc_directive] = 620,
        [anon_sym_typedef] = 620,
        [anon_sym_extern] = 620,
        [anon_sym_static] = 620,
        [anon_sym_auto] = 620,
        [anon_sym_register] = 620,
        [anon_sym_signed] = 620,
        [anon_sym_unsigned] = 620,
        [anon_sym_long] = 620,
        [anon_sym_short] = 620,
        [anon_sym_struct] = 620,
        [anon_sym_const] = 620,
        [anon_sym_restrict] = 620,
        [anon_sym_volatile] = 620,
        [sym_identifier] = 620,
        [sym_comment] = 42,
    },
    [233] = {
        [anon_sym_LF] = 622,
        [sym_preproc_arg] = 624,
        [sym_comment] = 42,
    },
    [234] = {
        [sym_preproc_define] = 626,
        [sym_preproc_call] = 626,
        [sym_function_definition] = 626,
        [sym_declaration_specifiers] = 626,
        [sym_storage_class_specifier] = 626,
        [sym__type_specifier] = 626,
        [sym_numeric_type_specifier] = 626,
        [sym_struct_specifier] = 626,
        [sym_declaration] = 626,
        [sym_type_qualifier] = 626,
        [sym_macro_type] = 626,
        [aux_sym_translation_unit_repeat1] = 626,
        [aux_sym_declaration_specifiers_repeat1] = 626,
        [aux_sym_numeric_type_specifier_repeat1] = 626,
        [ts_builtin_sym_error] = 626,
        [ts_builtin_sym_end] = 626,
        [anon_sym_POUNDdefine] = 626,
        [sym_preproc_directive] = 626,
        [anon_sym_typedef] = 626,
        [anon_sym_extern] = 626,
        [anon_sym_static] = 626,
        [anon_sym_auto] = 626,
        [anon_sym_register] = 626,
        [anon_sym_signed] = 626,
        [anon_sym_unsigned] = 626,
        [anon_sym_long] = 626,
        [anon_sym_short] = 626,
        [anon_sym_struct] = 626,
        [anon_sym_const] = 626,
        [anon_sym_restrict] = 626,
        [anon_sym_volatile] = 626,
        [sym_identifier] = 626,
        [sym_comment] = 42,
    },
    [235] = {
        [anon_sym_LF] = 628,
        [sym_comment] = 42,
    },
    [236] = {
        [sym_preproc_define] = 630,
        [sym_preproc_call] = 630,
        [sym_function_definition] = 630,
        [sym_declaration_specifiers] = 630,
        [sym_storage_class_specifier] = 630,
        [sym__type_specifier] = 630,
        [sym_numeric_type_specifier] = 630,
        [sym_struct_specifier] = 630,
        [sym_declaration] = 630,
        [sym_type_qualifier] = 630,
        [sym_macro_type] = 630,
        [aux_sym_translation_unit_repeat1] = 630,
        [aux_sym_declaration_specifiers_repeat1] = 630,
        [aux_sym_numeric_type_specifier_repeat1] = 630,
        [ts_builtin_sym_error] = 630,
        [ts_builtin_sym_end] = 630,
        [anon_sym_POUNDdefine] = 630,
        [sym_preproc_directive] = 630,
        [anon_sym_typedef] = 630,
        [anon_sym_extern] = 630,
        [anon_sym_static] = 630,
        [anon_sym_auto] = 630,
        [anon_sym_register] = 630,
        [anon_sym_signed] = 630,
        [anon_sym_unsigned] = 630,
        [anon_sym_long] = 630,
        [anon_sym_short] = 630,
        [anon_sym_struct] = 630,
        [anon_sym_const] = 630,
        [anon_sym_restrict] = 630,
        [anon_sym_volatile] = 630,
        [sym_identifier] = 630,
        [sym_comment] = 42,
    },
    [237] = {
        [sym_preproc_define] = 632,
        [sym_preproc_call] = 632,
        [sym_function_definition] = 632,
        [sym_declaration_specifiers] = 632,
        [sym_storage_class_specifier] = 632,
        [sym__type_specifier] = 632,
        [sym_numeric_type_specifier] = 632,
        [sym_struct_specifier] = 632,
        [sym_declaration] = 632,
        [sym_type_qualifier] = 632,
        [sym_macro_type] = 632,
        [aux_sym_translation_unit_repeat1] = 632,
        [aux_sym_declaration_specifiers_repeat1] = 632,
        [aux_sym_numeric_type_specifier_repeat1] = 632,
        [ts_builtin_sym_error] = 632,
        [ts_builtin_sym_end] = 632,
        [anon_sym_POUNDdefine] = 632,
        [sym_preproc_directive] = 632,
        [anon_sym_typedef] = 632,
        [anon_sym_extern] = 632,
        [anon_sym_static] = 632,
        [anon_sym_auto] = 632,
        [anon_sym_register] = 632,
        [anon_sym_signed] = 632,
        [anon_sym_unsigned] = 632,
        [anon_sym_long] = 632,
        [anon_sym_short] = 632,
        [anon_sym_struct] = 632,
        [anon_sym_const] = 632,
        [anon_sym_restrict] = 632,
        [anon_sym_volatile] = 632,
        [sym_identifier] = 632,
        [sym_comment] = 42,
    },
    [238] = {
        [sym__init_declarator] = 190,
        [sym__declarator] = 190,
        [sym_pointer_declarator] = 190,
        [sym_function_declarator] = 190,
        [sym_array_declarator] = 190,
        [anon_sym_LPAREN] = 190,
        [anon_sym_STAR] = 190,
        [sym_identifier] = 190,
        [sym_comment] = 42,
    },
    [239] = {
        [sym__type_specifier] = 634,
        [sym_numeric_type_specifier] = 634,
        [sym_struct_specifier] = 634,
        [sym_macro_type] = 634,
        [aux_sym_numeric_type_specifier_repeat1] = 634,
        [anon_sym_signed] = 634,
        [anon_sym_unsigned] = 634,
        [anon_sym_long] = 634,
        [anon_sym_short] = 634,
        [anon_sym_struct] = 634,
        [sym_identifier] = 634,
        [sym_comment] = 42,
    },
    [240] = {
        [ts_builtin_sym_end] = 636,
        [sym_comment] = 42,
    },
    [241] = {
        [aux_sym_declaration_repeat1] = 638,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 642,
        [sym_comment] = 42,
    },
    [242] = {
        [sym_compound_statement] = 644,
        [aux_sym_declaration_repeat1] = 638,
        [anon_sym_LBRACE] = 646,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 642,
        [anon_sym_EQ] = 648,
        [anon_sym_LBRACK] = 650,
        [anon_sym_LPAREN] = 652,
        [sym_comment] = 42,
    },
    [243] = {
        [sym_compound_statement] = 200,
        [aux_sym_declaration_repeat1] = 200,
        [anon_sym_LBRACE] = 200,
        [anon_sym_COMMA] = 200,
        [anon_sym_SEMI] = 200,
        [anon_sym_EQ] = 200,
        [anon_sym_LBRACK] = 200,
        [anon_sym_LPAREN] = 200,
        [sym_comment] = 42,
    },
    [244] = {
        [sym__declarator] = 654,
        [sym_pointer_declarator] = 204,
        [sym_function_declarator] = 204,
        [sym_array_declarator] = 204,
        [anon_sym_LPAREN] = 206,
        [anon_sym_STAR] = 208,
        [sym_identifier] = 204,
        [sym_comment] = 42,
    },
    [245] = {
        [sym__declarator] = 656,
        [sym_pointer_declarator] = 58,
        [sym_function_declarator] = 58,
        [sym_array_declarator] = 58,
        [anon_sym_LPAREN] = 60,
        [anon_sym_STAR] = 62,
        [sym_identifier] = 58,
        [sym_comment] = 42,
    },
    [246] = {
        [sym_compound_statement] = 212,
        [aux_sym_declaration_repeat1] = 212,
        [anon_sym_LBRACE] = 212,
        [anon_sym_COMMA] = 212,
        [anon_sym_SEMI] = 212,
        [anon_sym_EQ] = 212,
        [anon_sym_LBRACK] = 650,
        [anon_sym_LPAREN] = 652,
        [sym_comment] = 42,
    },
    [247] = {
        [sym__expression] = 658,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_RBRACK] = 660,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [248] = {
        [sym_declaration_specifiers] = 226,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 228,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_parameter_declaration] = 662,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 125,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RPAREN] = 664,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [249] = {
        [aux_sym_function_declarator_repeat1] = 666,
        [anon_sym_COMMA] = 246,
        [anon_sym_RPAREN] = 668,
        [sym_comment] = 42,
    },
    [250] = {
        [sym_compound_statement] = 250,
        [aux_sym_declaration_repeat1] = 250,
        [anon_sym_LBRACE] = 250,
        [anon_sym_COMMA] = 250,
        [anon_sym_SEMI] = 250,
        [anon_sym_EQ] = 250,
        [anon_sym_LBRACK] = 250,
        [anon_sym_LPAREN] = 250,
        [sym_comment] = 42,
    },
    [251] = {
        [anon_sym_RPAREN] = 670,
        [sym_comment] = 42,
    },
    [252] = {
        [sym_compound_statement] = 256,
        [aux_sym_declaration_repeat1] = 256,
        [anon_sym_LBRACE] = 256,
        [anon_sym_COMMA] = 256,
        [anon_sym_SEMI] = 256,
        [anon_sym_EQ] = 256,
        [anon_sym_LBRACK] = 256,
        [anon_sym_LPAREN] = 256,
        [sym_comment] = 42,
    },
    [253] = {
        [sym_compound_statement] = 264,
        [aux_sym_declaration_repeat1] = 264,
        [anon_sym_LBRACE] = 264,
        [anon_sym_COMMA] = 264,
        [anon_sym_SEMI] = 264,
        [anon_sym_EQ] = 264,
        [anon_sym_LBRACK] = 264,
        [anon_sym_LPAREN] = 264,
        [sym_comment] = 42,
    },
    [254] = {
        [anon_sym_EQ] = 290,
        [anon_sym_RBRACK] = 672,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 298,
        [sym_comment] = 42,
    },
    [255] = {
        [sym_compound_statement] = 302,
        [aux_sym_declaration_repeat1] = 302,
        [anon_sym_LBRACE] = 302,
        [anon_sym_COMMA] = 302,
        [anon_sym_SEMI] = 302,
        [anon_sym_EQ] = 302,
        [anon_sym_LBRACK] = 302,
        [anon_sym_LPAREN] = 302,
        [sym_comment] = 42,
    },
    [256] = {
        [sym_compound_statement] = 566,
        [aux_sym_declaration_repeat1] = 566,
        [anon_sym_LBRACE] = 566,
        [anon_sym_COMMA] = 566,
        [anon_sym_SEMI] = 566,
        [anon_sym_EQ] = 566,
        [anon_sym_LBRACK] = 566,
        [anon_sym_LPAREN] = 566,
        [sym_comment] = 42,
    },
    [257] = {
        [anon_sym_LBRACK] = 568,
        [anon_sym_LPAREN] = 570,
        [anon_sym_RPAREN] = 674,
        [sym_comment] = 42,
    },
    [258] = {
        [sym_compound_statement] = 596,
        [aux_sym_declaration_repeat1] = 596,
        [anon_sym_LBRACE] = 596,
        [anon_sym_COMMA] = 596,
        [anon_sym_SEMI] = 596,
        [anon_sym_EQ] = 596,
        [anon_sym_LBRACK] = 596,
        [anon_sym_LPAREN] = 596,
        [sym_comment] = 42,
    },
    [259] = {
        [sym_preproc_define] = 676,
        [sym_preproc_call] = 676,
        [sym_function_definition] = 676,
        [sym_declaration_specifiers] = 676,
        [sym_storage_class_specifier] = 676,
        [sym__type_specifier] = 676,
        [sym_numeric_type_specifier] = 676,
        [sym_struct_specifier] = 676,
        [sym_declaration] = 676,
        [sym_type_qualifier] = 676,
        [sym_macro_type] = 676,
        [aux_sym_translation_unit_repeat1] = 676,
        [aux_sym_declaration_specifiers_repeat1] = 676,
        [aux_sym_numeric_type_specifier_repeat1] = 676,
        [ts_builtin_sym_error] = 676,
        [ts_builtin_sym_end] = 676,
        [anon_sym_POUNDdefine] = 676,
        [sym_preproc_directive] = 676,
        [anon_sym_typedef] = 676,
        [anon_sym_extern] = 676,
        [anon_sym_static] = 676,
        [anon_sym_auto] = 676,
        [anon_sym_register] = 676,
        [anon_sym_signed] = 676,
        [anon_sym_unsigned] = 676,
        [anon_sym_long] = 676,
        [anon_sym_short] = 676,
        [anon_sym_struct] = 676,
        [anon_sym_const] = 676,
        [anon_sym_restrict] = 676,
        [anon_sym_volatile] = 676,
        [sym_identifier] = 676,
        [sym_comment] = 42,
    },
    [260] = {
        [anon_sym_SEMI] = 678,
        [sym_comment] = 42,
    },
    [261] = {
        [sym_declaration_specifiers] = 680,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 682,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 684,
        [sym_type_qualifier] = 8,
        [sym_compound_statement] = 686,
        [sym__expression] = 688,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [sym__statement] = 684,
        [sym_for_statement] = 686,
        [sym_expression_statement] = 686,
        [sym_macro_type] = 12,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [aux_sym_compound_statement_repeat1] = 692,
        [ts_builtin_sym_error] = 694,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 32,
        [anon_sym_LBRACE] = 696,
        [anon_sym_RBRACE] = 698,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [anon_sym_AMP] = 702,
        [anon_sym_for] = 704,
        [sym_string] = 690,
        [sym_identifier] = 706,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [262] = {
        [sym__init_declarator] = 708,
        [sym__declarator] = 710,
        [sym_pointer_declarator] = 712,
        [sym_function_declarator] = 712,
        [sym_array_declarator] = 712,
        [anon_sym_LPAREN] = 714,
        [anon_sym_STAR] = 716,
        [sym_identifier] = 712,
        [sym_comment] = 42,
    },
    [263] = {
        [sym_preproc_define] = 718,
        [sym_preproc_call] = 718,
        [sym_function_definition] = 718,
        [sym_declaration_specifiers] = 718,
        [sym_storage_class_specifier] = 718,
        [sym__type_specifier] = 718,
        [sym_numeric_type_specifier] = 718,
        [sym_struct_specifier] = 718,
        [sym_declaration] = 718,
        [sym_type_qualifier] = 718,
        [sym_macro_type] = 718,
        [aux_sym_translation_unit_repeat1] = 718,
        [aux_sym_declaration_specifiers_repeat1] = 718,
        [aux_sym_numeric_type_specifier_repeat1] = 718,
        [ts_builtin_sym_error] = 718,
        [ts_builtin_sym_end] = 718,
        [anon_sym_POUNDdefine] = 718,
        [sym_preproc_directive] = 718,
        [anon_sym_typedef] = 718,
        [anon_sym_extern] = 718,
        [anon_sym_static] = 718,
        [anon_sym_auto] = 718,
        [anon_sym_register] = 718,
        [anon_sym_signed] = 718,
        [anon_sym_unsigned] = 718,
        [anon_sym_long] = 718,
        [anon_sym_short] = 718,
        [anon_sym_struct] = 718,
        [anon_sym_const] = 718,
        [anon_sym_restrict] = 718,
        [anon_sym_volatile] = 718,
        [sym_identifier] = 718,
        [sym_comment] = 42,
    },
    [264] = {
        [sym_initializer] = 720,
        [sym__expression] = 722,
        [sym_cast_expression] = 724,
        [sym_math_expression] = 724,
        [sym_call_expression] = 724,
        [sym_pointer_expression] = 724,
        [sym_assignment_expression] = 724,
        [anon_sym_LBRACE] = 726,
        [anon_sym_LPAREN] = 728,
        [anon_sym_STAR] = 730,
        [anon_sym_AMP] = 730,
        [sym_string] = 724,
        [sym_identifier] = 732,
        [sym_number] = 724,
        [sym_comment] = 42,
    },
    [265] = {
        [aux_sym_declaration_repeat1] = 734,
        [anon_sym_COMMA] = 734,
        [anon_sym_SEMI] = 734,
        [sym_comment] = 42,
    },
    [266] = {
        [aux_sym_declaration_repeat1] = 736,
        [anon_sym_COMMA] = 736,
        [anon_sym_SEMI] = 736,
        [anon_sym_EQ] = 738,
        [anon_sym_LPAREN] = 740,
        [anon_sym_STAR] = 742,
        [anon_sym_PLUS] = 744,
        [sym_comment] = 42,
    },
    [267] = {
        [aux_sym_declaration_repeat1] = 300,
        [anon_sym_COMMA] = 300,
        [anon_sym_SEMI] = 300,
        [anon_sym_EQ] = 300,
        [anon_sym_LPAREN] = 300,
        [anon_sym_STAR] = 300,
        [anon_sym_PLUS] = 300,
        [sym_comment] = 42,
    },
    [268] = {
        [sym_initializer] = 746,
        [sym_initializer_list] = 748,
        [sym_designation] = 750,
        [sym__expression] = 752,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [aux_sym_designation_repeat1] = 756,
        [anon_sym_LBRACE] = 758,
        [anon_sym_LBRACK] = 760,
        [anon_sym_DOT] = 762,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [269] = {
        [sym__type_specifier] = 304,
        [sym_numeric_type_specifier] = 306,
        [sym_struct_specifier] = 306,
        [sym_type_name] = 770,
        [sym_type_qualifier] = 310,
        [sym__expression] = 772,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [sym_macro_type] = 306,
        [aux_sym_numeric_type_specifier_repeat1] = 316,
        [aux_sym_type_name_repeat1] = 318,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 320,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_const] = 326,
        [anon_sym_restrict] = 326,
        [anon_sym_volatile] = 326,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 328,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [270] = {
        [sym__expression] = 774,
        [sym_cast_expression] = 724,
        [sym_math_expression] = 724,
        [sym_call_expression] = 724,
        [sym_pointer_expression] = 724,
        [sym_assignment_expression] = 724,
        [anon_sym_LPAREN] = 728,
        [anon_sym_STAR] = 730,
        [anon_sym_AMP] = 730,
        [sym_string] = 724,
        [sym_identifier] = 732,
        [sym_number] = 724,
        [sym_comment] = 42,
    },
    [271] = {
        [aux_sym_declaration_repeat1] = 332,
        [anon_sym_COMMA] = 332,
        [anon_sym_SEMI] = 332,
        [anon_sym_EQ] = 332,
        [anon_sym_LPAREN] = 332,
        [anon_sym_STAR] = 332,
        [anon_sym_PLUS] = 332,
        [sym_comment] = 42,
    },
    [272] = {
        [aux_sym_declaration_repeat1] = 334,
        [anon_sym_COMMA] = 334,
        [anon_sym_SEMI] = 334,
        [anon_sym_EQ] = 334,
        [anon_sym_LPAREN] = 740,
        [anon_sym_STAR] = 742,
        [anon_sym_PLUS] = 744,
        [sym_comment] = 42,
    },
    [273] = {
        [sym__expression] = 776,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_RPAREN] = 778,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [274] = {
        [sym__expression] = 780,
        [sym_cast_expression] = 724,
        [sym_math_expression] = 724,
        [sym_call_expression] = 724,
        [sym_pointer_expression] = 724,
        [sym_assignment_expression] = 724,
        [anon_sym_LPAREN] = 728,
        [anon_sym_STAR] = 730,
        [anon_sym_AMP] = 730,
        [sym_string] = 724,
        [sym_identifier] = 732,
        [sym_number] = 724,
        [sym_comment] = 42,
    },
    [275] = {
        [sym__expression] = 782,
        [sym_cast_expression] = 724,
        [sym_math_expression] = 724,
        [sym_call_expression] = 724,
        [sym_pointer_expression] = 724,
        [sym_assignment_expression] = 724,
        [anon_sym_LPAREN] = 728,
        [anon_sym_STAR] = 730,
        [anon_sym_AMP] = 730,
        [sym_string] = 724,
        [sym_identifier] = 732,
        [sym_number] = 724,
        [sym_comment] = 42,
    },
    [276] = {
        [aux_sym_declaration_repeat1] = 352,
        [anon_sym_COMMA] = 352,
        [anon_sym_SEMI] = 352,
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 740,
        [anon_sym_STAR] = 742,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [277] = {
        [aux_sym_declaration_repeat1] = 352,
        [anon_sym_COMMA] = 352,
        [anon_sym_SEMI] = 352,
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 740,
        [anon_sym_STAR] = 352,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [278] = {
        [aux_sym_call_expression_repeat1] = 784,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 786,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [279] = {
        [aux_sym_declaration_repeat1] = 372,
        [anon_sym_COMMA] = 372,
        [anon_sym_SEMI] = 372,
        [anon_sym_EQ] = 372,
        [anon_sym_LPAREN] = 372,
        [anon_sym_STAR] = 372,
        [anon_sym_PLUS] = 372,
        [sym_comment] = 42,
    },
    [280] = {
        [anon_sym_RPAREN] = 788,
        [sym_comment] = 42,
    },
    [281] = {
        [aux_sym_declaration_repeat1] = 394,
        [anon_sym_COMMA] = 394,
        [anon_sym_SEMI] = 394,
        [anon_sym_EQ] = 394,
        [anon_sym_LPAREN] = 394,
        [anon_sym_STAR] = 394,
        [anon_sym_PLUS] = 394,
        [sym_comment] = 42,
    },
    [282] = {
        [aux_sym_declaration_repeat1] = 404,
        [anon_sym_COMMA] = 404,
        [anon_sym_SEMI] = 404,
        [anon_sym_EQ] = 404,
        [anon_sym_LPAREN] = 404,
        [anon_sym_STAR] = 404,
        [anon_sym_PLUS] = 404,
        [sym_comment] = 42,
    },
    [283] = {
        [anon_sym_RPAREN] = 790,
        [sym_comment] = 42,
    },
    [284] = {
        [anon_sym_EQ] = 422,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 792,
        [anon_sym_STAR] = 428,
        [anon_sym_PLUS] = 430,
        [sym_comment] = 42,
    },
    [285] = {
        [aux_sym_declaration_repeat1] = 481,
        [anon_sym_COMMA] = 481,
        [anon_sym_SEMI] = 481,
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 42,
    },
    [286] = {
        [sym__expression] = 794,
        [sym_cast_expression] = 724,
        [sym_math_expression] = 724,
        [sym_call_expression] = 724,
        [sym_pointer_expression] = 724,
        [sym_assignment_expression] = 724,
        [anon_sym_LPAREN] = 728,
        [anon_sym_STAR] = 730,
        [anon_sym_AMP] = 730,
        [sym_string] = 724,
        [sym_identifier] = 732,
        [sym_number] = 724,
        [sym_comment] = 42,
    },
    [287] = {
        [aux_sym_declaration_repeat1] = 485,
        [anon_sym_COMMA] = 485,
        [anon_sym_SEMI] = 485,
        [anon_sym_EQ] = 485,
        [anon_sym_LPAREN] = 485,
        [anon_sym_STAR] = 485,
        [anon_sym_PLUS] = 485,
        [sym_comment] = 42,
    },
    [288] = {
        [anon_sym_RBRACE] = 796,
        [anon_sym_COMMA] = 796,
        [sym_comment] = 42,
    },
    [289] = {
        [anon_sym_RBRACE] = 798,
        [anon_sym_COMMA] = 800,
        [sym_comment] = 42,
    },
    [290] = {
        [sym_initializer] = 802,
        [sym__expression] = 752,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [anon_sym_LBRACE] = 758,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [291] = {
        [anon_sym_RBRACE] = 736,
        [anon_sym_COMMA] = 736,
        [anon_sym_EQ] = 804,
        [anon_sym_LPAREN] = 806,
        [anon_sym_STAR] = 808,
        [anon_sym_PLUS] = 810,
        [sym_comment] = 42,
    },
    [292] = {
        [anon_sym_RBRACE] = 300,
        [anon_sym_COMMA] = 300,
        [anon_sym_EQ] = 300,
        [anon_sym_LPAREN] = 300,
        [anon_sym_STAR] = 300,
        [anon_sym_PLUS] = 300,
        [sym_comment] = 42,
    },
    [293] = {
        [anon_sym_EQ] = 812,
        [sym_comment] = 42,
    },
    [294] = {
        [sym_initializer] = 746,
        [sym_initializer_list] = 814,
        [sym_designation] = 750,
        [sym__expression] = 752,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [aux_sym_designation_repeat1] = 756,
        [anon_sym_LBRACE] = 758,
        [anon_sym_LBRACK] = 760,
        [anon_sym_DOT] = 762,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [295] = {
        [sym__expression] = 816,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [296] = {
        [sym_identifier] = 818,
        [sym_comment] = 42,
    },
    [297] = {
        [sym__type_specifier] = 304,
        [sym_numeric_type_specifier] = 306,
        [sym_struct_specifier] = 306,
        [sym_type_name] = 820,
        [sym_type_qualifier] = 310,
        [sym__expression] = 822,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [sym_macro_type] = 306,
        [aux_sym_numeric_type_specifier_repeat1] = 316,
        [aux_sym_type_name_repeat1] = 318,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 320,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_const] = 326,
        [anon_sym_restrict] = 326,
        [anon_sym_volatile] = 326,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 328,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [298] = {
        [sym__expression] = 824,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [299] = {
        [anon_sym_RBRACE] = 332,
        [anon_sym_COMMA] = 332,
        [anon_sym_EQ] = 332,
        [anon_sym_LPAREN] = 332,
        [anon_sym_STAR] = 332,
        [anon_sym_PLUS] = 332,
        [sym_comment] = 42,
    },
    [300] = {
        [anon_sym_RBRACE] = 334,
        [anon_sym_COMMA] = 334,
        [anon_sym_EQ] = 334,
        [anon_sym_LPAREN] = 806,
        [anon_sym_STAR] = 808,
        [anon_sym_PLUS] = 810,
        [sym_comment] = 42,
    },
    [301] = {
        [sym__expression] = 826,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_RPAREN] = 828,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [302] = {
        [sym__expression] = 830,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [303] = {
        [sym__expression] = 832,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [304] = {
        [anon_sym_RBRACE] = 352,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 806,
        [anon_sym_STAR] = 808,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [305] = {
        [anon_sym_RBRACE] = 352,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 806,
        [anon_sym_STAR] = 352,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [306] = {
        [aux_sym_call_expression_repeat1] = 834,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 836,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [307] = {
        [anon_sym_RBRACE] = 372,
        [anon_sym_COMMA] = 372,
        [anon_sym_EQ] = 372,
        [anon_sym_LPAREN] = 372,
        [anon_sym_STAR] = 372,
        [anon_sym_PLUS] = 372,
        [sym_comment] = 42,
    },
    [308] = {
        [anon_sym_RPAREN] = 838,
        [sym_comment] = 42,
    },
    [309] = {
        [anon_sym_RBRACE] = 394,
        [anon_sym_COMMA] = 394,
        [anon_sym_EQ] = 394,
        [anon_sym_LPAREN] = 394,
        [anon_sym_STAR] = 394,
        [anon_sym_PLUS] = 394,
        [sym_comment] = 42,
    },
    [310] = {
        [anon_sym_RBRACE] = 404,
        [anon_sym_COMMA] = 404,
        [anon_sym_EQ] = 404,
        [anon_sym_LPAREN] = 404,
        [anon_sym_STAR] = 404,
        [anon_sym_PLUS] = 404,
        [sym_comment] = 42,
    },
    [311] = {
        [anon_sym_RPAREN] = 840,
        [sym_comment] = 42,
    },
    [312] = {
        [anon_sym_EQ] = 422,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 842,
        [anon_sym_STAR] = 428,
        [anon_sym_PLUS] = 430,
        [sym_comment] = 42,
    },
    [313] = {
        [anon_sym_RBRACE] = 481,
        [anon_sym_COMMA] = 481,
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 42,
    },
    [314] = {
        [sym__expression] = 844,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [315] = {
        [anon_sym_RBRACE] = 485,
        [anon_sym_COMMA] = 485,
        [anon_sym_EQ] = 485,
        [anon_sym_LPAREN] = 485,
        [anon_sym_STAR] = 485,
        [anon_sym_PLUS] = 485,
        [sym_comment] = 42,
    },
    [316] = {
        [aux_sym_designation_repeat1] = 846,
        [anon_sym_EQ] = 848,
        [anon_sym_LBRACK] = 760,
        [anon_sym_DOT] = 762,
        [sym_comment] = 42,
    },
    [317] = {
        [anon_sym_EQ] = 850,
        [sym_comment] = 42,
    },
    [318] = {
        [anon_sym_EQ] = 290,
        [anon_sym_RBRACK] = 852,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 298,
        [sym_comment] = 42,
    },
    [319] = {
        [aux_sym_designation_repeat1] = 854,
        [anon_sym_EQ] = 850,
        [anon_sym_LBRACK] = 760,
        [anon_sym_DOT] = 762,
        [sym_comment] = 42,
    },
    [320] = {
        [anon_sym_EQ] = 856,
        [sym_comment] = 42,
    },
    [321] = {
        [anon_sym_RBRACE] = 858,
        [anon_sym_COMMA] = 860,
        [sym_comment] = 42,
    },
    [322] = {
        [anon_sym_RBRACE] = 862,
        [anon_sym_COMMA] = 862,
        [sym_comment] = 42,
    },
    [323] = {
        [sym_initializer] = 864,
        [sym_designation] = 866,
        [sym__expression] = 752,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [aux_sym_designation_repeat1] = 756,
        [anon_sym_LBRACE] = 758,
        [anon_sym_RBRACE] = 868,
        [anon_sym_LBRACK] = 760,
        [anon_sym_DOT] = 762,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [324] = {
        [anon_sym_RBRACE] = 870,
        [anon_sym_COMMA] = 870,
        [sym_comment] = 42,
    },
    [325] = {
        [sym_initializer] = 872,
        [sym__expression] = 752,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [anon_sym_LBRACE] = 758,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [326] = {
        [anon_sym_RBRACE] = 874,
        [anon_sym_COMMA] = 874,
        [sym_comment] = 42,
    },
    [327] = {
        [anon_sym_RBRACE] = 876,
        [anon_sym_COMMA] = 876,
        [sym_comment] = 42,
    },
    [328] = {
        [sym_initializer] = 878,
        [sym__expression] = 878,
        [sym_cast_expression] = 878,
        [sym_math_expression] = 878,
        [sym_call_expression] = 878,
        [sym_pointer_expression] = 878,
        [sym_assignment_expression] = 878,
        [anon_sym_LBRACE] = 878,
        [anon_sym_LPAREN] = 878,
        [anon_sym_STAR] = 878,
        [anon_sym_AMP] = 878,
        [sym_string] = 878,
        [sym_identifier] = 878,
        [sym_number] = 878,
        [sym_comment] = 42,
    },
    [329] = {
        [sym__expression] = 880,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [330] = {
        [anon_sym_RBRACE] = 396,
        [anon_sym_COMMA] = 396,
        [anon_sym_EQ] = 804,
        [anon_sym_LPAREN] = 806,
        [anon_sym_STAR] = 808,
        [anon_sym_PLUS] = 810,
        [sym_comment] = 42,
    },
    [331] = {
        [anon_sym_RBRACE] = 882,
        [anon_sym_COMMA] = 882,
        [sym_comment] = 42,
    },
    [332] = {
        [aux_sym_declaration_repeat1] = 862,
        [anon_sym_COMMA] = 862,
        [anon_sym_SEMI] = 862,
        [sym_comment] = 42,
    },
    [333] = {
        [sym_initializer] = 864,
        [sym_designation] = 866,
        [sym__expression] = 752,
        [sym_cast_expression] = 754,
        [sym_math_expression] = 754,
        [sym_call_expression] = 754,
        [sym_pointer_expression] = 754,
        [sym_assignment_expression] = 754,
        [aux_sym_designation_repeat1] = 756,
        [anon_sym_LBRACE] = 758,
        [anon_sym_RBRACE] = 884,
        [anon_sym_LBRACK] = 760,
        [anon_sym_DOT] = 762,
        [anon_sym_LPAREN] = 764,
        [anon_sym_STAR] = 766,
        [anon_sym_AMP] = 766,
        [sym_string] = 754,
        [sym_identifier] = 768,
        [sym_number] = 754,
        [sym_comment] = 42,
    },
    [334] = {
        [aux_sym_declaration_repeat1] = 874,
        [anon_sym_COMMA] = 874,
        [anon_sym_SEMI] = 874,
        [sym_comment] = 42,
    },
    [335] = {
        [sym__expression] = 886,
        [sym_cast_expression] = 724,
        [sym_math_expression] = 724,
        [sym_call_expression] = 724,
        [sym_pointer_expression] = 724,
        [sym_assignment_expression] = 724,
        [anon_sym_LPAREN] = 728,
        [anon_sym_STAR] = 730,
        [anon_sym_AMP] = 730,
        [sym_string] = 724,
        [sym_identifier] = 732,
        [sym_number] = 724,
        [sym_comment] = 42,
    },
    [336] = {
        [aux_sym_declaration_repeat1] = 396,
        [anon_sym_COMMA] = 396,
        [anon_sym_SEMI] = 396,
        [anon_sym_EQ] = 738,
        [anon_sym_LPAREN] = 740,
        [anon_sym_STAR] = 742,
        [anon_sym_PLUS] = 744,
        [sym_comment] = 42,
    },
    [337] = {
        [aux_sym_declaration_repeat1] = 888,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 890,
        [sym_comment] = 42,
    },
    [338] = {
        [aux_sym_declaration_repeat1] = 888,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 890,
        [anon_sym_EQ] = 648,
        [anon_sym_LBRACK] = 892,
        [anon_sym_LPAREN] = 894,
        [sym_comment] = 42,
    },
    [339] = {
        [aux_sym_declaration_repeat1] = 200,
        [anon_sym_COMMA] = 200,
        [anon_sym_SEMI] = 200,
        [anon_sym_EQ] = 200,
        [anon_sym_LBRACK] = 200,
        [anon_sym_LPAREN] = 200,
        [sym_comment] = 42,
    },
    [340] = {
        [sym__declarator] = 896,
        [sym_pointer_declarator] = 204,
        [sym_function_declarator] = 204,
        [sym_array_declarator] = 204,
        [anon_sym_LPAREN] = 206,
        [anon_sym_STAR] = 208,
        [sym_identifier] = 204,
        [sym_comment] = 42,
    },
    [341] = {
        [sym__declarator] = 898,
        [sym_pointer_declarator] = 712,
        [sym_function_declarator] = 712,
        [sym_array_declarator] = 712,
        [anon_sym_LPAREN] = 714,
        [anon_sym_STAR] = 716,
        [sym_identifier] = 712,
        [sym_comment] = 42,
    },
    [342] = {
        [aux_sym_declaration_repeat1] = 212,
        [anon_sym_COMMA] = 212,
        [anon_sym_SEMI] = 212,
        [anon_sym_EQ] = 212,
        [anon_sym_LBRACK] = 892,
        [anon_sym_LPAREN] = 894,
        [sym_comment] = 42,
    },
    [343] = {
        [sym__expression] = 900,
        [sym_cast_expression] = 216,
        [sym_math_expression] = 216,
        [sym_call_expression] = 216,
        [sym_pointer_expression] = 216,
        [sym_assignment_expression] = 216,
        [anon_sym_RBRACK] = 902,
        [anon_sym_LPAREN] = 220,
        [anon_sym_STAR] = 222,
        [anon_sym_AMP] = 222,
        [sym_string] = 216,
        [sym_identifier] = 224,
        [sym_number] = 216,
        [sym_comment] = 42,
    },
    [344] = {
        [sym_declaration_specifiers] = 226,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 228,
        [sym_numeric_type_specifier] = 125,
        [sym_struct_specifier] = 125,
        [sym_parameter_declaration] = 904,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 125,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 129,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 133,
        [anon_sym_RPAREN] = 906,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [sym_identifier] = 137,
        [sym_comment] = 42,
    },
    [345] = {
        [aux_sym_function_declarator_repeat1] = 908,
        [anon_sym_COMMA] = 246,
        [anon_sym_RPAREN] = 910,
        [sym_comment] = 42,
    },
    [346] = {
        [aux_sym_declaration_repeat1] = 250,
        [anon_sym_COMMA] = 250,
        [anon_sym_SEMI] = 250,
        [anon_sym_EQ] = 250,
        [anon_sym_LBRACK] = 250,
        [anon_sym_LPAREN] = 250,
        [sym_comment] = 42,
    },
    [347] = {
        [anon_sym_RPAREN] = 912,
        [sym_comment] = 42,
    },
    [348] = {
        [aux_sym_declaration_repeat1] = 256,
        [anon_sym_COMMA] = 256,
        [anon_sym_SEMI] = 256,
        [anon_sym_EQ] = 256,
        [anon_sym_LBRACK] = 256,
        [anon_sym_LPAREN] = 256,
        [sym_comment] = 42,
    },
    [349] = {
        [aux_sym_declaration_repeat1] = 264,
        [anon_sym_COMMA] = 264,
        [anon_sym_SEMI] = 264,
        [anon_sym_EQ] = 264,
        [anon_sym_LBRACK] = 264,
        [anon_sym_LPAREN] = 264,
        [sym_comment] = 42,
    },
    [350] = {
        [anon_sym_EQ] = 290,
        [anon_sym_RBRACK] = 914,
        [anon_sym_LPAREN] = 294,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 298,
        [sym_comment] = 42,
    },
    [351] = {
        [aux_sym_declaration_repeat1] = 302,
        [anon_sym_COMMA] = 302,
        [anon_sym_SEMI] = 302,
        [anon_sym_EQ] = 302,
        [anon_sym_LBRACK] = 302,
        [anon_sym_LPAREN] = 302,
        [sym_comment] = 42,
    },
    [352] = {
        [aux_sym_declaration_repeat1] = 566,
        [anon_sym_COMMA] = 566,
        [anon_sym_SEMI] = 566,
        [anon_sym_EQ] = 566,
        [anon_sym_LBRACK] = 566,
        [anon_sym_LPAREN] = 566,
        [sym_comment] = 42,
    },
    [353] = {
        [anon_sym_LBRACK] = 568,
        [anon_sym_LPAREN] = 570,
        [anon_sym_RPAREN] = 916,
        [sym_comment] = 42,
    },
    [354] = {
        [aux_sym_declaration_repeat1] = 596,
        [anon_sym_COMMA] = 596,
        [anon_sym_SEMI] = 596,
        [anon_sym_EQ] = 596,
        [anon_sym_LBRACK] = 596,
        [anon_sym_LPAREN] = 596,
        [sym_comment] = 42,
    },
    [355] = {
        [anon_sym_SEMI] = 918,
        [sym_comment] = 42,
    },
    [356] = {
        [sym__type_specifier] = 920,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_macro_type] = 12,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 32,
        [sym_identifier] = 36,
        [sym_comment] = 42,
    },
    [357] = {
        [sym__init_declarator] = 922,
        [sym__declarator] = 924,
        [sym_pointer_declarator] = 712,
        [sym_function_declarator] = 712,
        [sym_array_declarator] = 712,
        [anon_sym_LPAREN] = 714,
        [anon_sym_STAR] = 716,
        [sym_identifier] = 712,
        [sym_comment] = 42,
    },
    [358] = {
        [sym_declaration_specifiers] = 680,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 682,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 684,
        [sym_type_qualifier] = 8,
        [sym_compound_statement] = 686,
        [sym__expression] = 688,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [sym__statement] = 684,
        [sym_for_statement] = 686,
        [sym_expression_statement] = 686,
        [sym_macro_type] = 12,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [aux_sym_compound_statement_repeat1] = 926,
        [ts_builtin_sym_error] = 928,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 32,
        [anon_sym_LBRACE] = 696,
        [anon_sym_RBRACE] = 930,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [anon_sym_AMP] = 702,
        [anon_sym_for] = 704,
        [sym_string] = 690,
        [sym_identifier] = 706,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [359] = {
        [sym_declaration_specifiers] = 932,
        [sym_storage_class_specifier] = 932,
        [sym__type_specifier] = 932,
        [sym_numeric_type_specifier] = 932,
        [sym_struct_specifier] = 932,
        [sym_declaration] = 932,
        [sym_type_qualifier] = 932,
        [sym_compound_statement] = 932,
        [sym__expression] = 932,
        [sym_cast_expression] = 932,
        [sym_math_expression] = 932,
        [sym_call_expression] = 932,
        [sym_pointer_expression] = 932,
        [sym_assignment_expression] = 932,
        [sym__statement] = 932,
        [sym_for_statement] = 932,
        [sym_expression_statement] = 932,
        [sym_macro_type] = 932,
        [aux_sym_declaration_specifiers_repeat1] = 932,
        [aux_sym_numeric_type_specifier_repeat1] = 932,
        [aux_sym_compound_statement_repeat1] = 932,
        [ts_builtin_sym_error] = 932,
        [anon_sym_typedef] = 932,
        [anon_sym_extern] = 932,
        [anon_sym_static] = 932,
        [anon_sym_auto] = 932,
        [anon_sym_register] = 932,
        [anon_sym_signed] = 932,
        [anon_sym_unsigned] = 932,
        [anon_sym_long] = 932,
        [anon_sym_short] = 932,
        [anon_sym_struct] = 932,
        [anon_sym_LBRACE] = 932,
        [anon_sym_RBRACE] = 932,
        [anon_sym_LPAREN] = 932,
        [anon_sym_STAR] = 932,
        [anon_sym_const] = 932,
        [anon_sym_restrict] = 932,
        [anon_sym_volatile] = 932,
        [anon_sym_AMP] = 932,
        [anon_sym_for] = 932,
        [sym_string] = 932,
        [sym_identifier] = 932,
        [sym_number] = 932,
        [sym_comment] = 42,
    },
    [360] = {
        [anon_sym_SEMI] = 934,
        [anon_sym_EQ] = 936,
        [anon_sym_LPAREN] = 938,
        [anon_sym_STAR] = 940,
        [anon_sym_PLUS] = 942,
        [sym_comment] = 42,
    },
    [361] = {
        [anon_sym_SEMI] = 300,
        [anon_sym_EQ] = 300,
        [anon_sym_LPAREN] = 300,
        [anon_sym_STAR] = 300,
        [anon_sym_PLUS] = 300,
        [sym_comment] = 42,
    },
    [362] = {
        [anon_sym_RBRACE] = 944,
        [sym_comment] = 42,
    },
    [363] = {
        [anon_sym_RBRACE] = 944,
        [anon_sym_SEMI] = 946,
        [sym_comment] = 42,
    },
    [364] = {
        [sym_declaration_specifiers] = 680,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 682,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 684,
        [sym_type_qualifier] = 8,
        [sym_compound_statement] = 686,
        [sym__expression] = 688,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [sym__statement] = 684,
        [sym_for_statement] = 686,
        [sym_expression_statement] = 686,
        [sym_macro_type] = 12,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [aux_sym_compound_statement_repeat1] = 948,
        [ts_builtin_sym_error] = 950,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 32,
        [anon_sym_LBRACE] = 696,
        [anon_sym_RBRACE] = 952,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [anon_sym_AMP] = 702,
        [anon_sym_for] = 704,
        [sym_string] = 690,
        [sym_identifier] = 706,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [365] = {
        [sym_preproc_define] = 954,
        [sym_preproc_call] = 954,
        [sym_function_definition] = 954,
        [sym_declaration_specifiers] = 954,
        [sym_storage_class_specifier] = 954,
        [sym__type_specifier] = 954,
        [sym_numeric_type_specifier] = 954,
        [sym_struct_specifier] = 954,
        [sym_declaration] = 954,
        [sym_type_qualifier] = 954,
        [sym_macro_type] = 954,
        [aux_sym_translation_unit_repeat1] = 954,
        [aux_sym_declaration_specifiers_repeat1] = 954,
        [aux_sym_numeric_type_specifier_repeat1] = 954,
        [ts_builtin_sym_error] = 954,
        [ts_builtin_sym_end] = 954,
        [anon_sym_POUNDdefine] = 954,
        [sym_preproc_directive] = 954,
        [anon_sym_typedef] = 954,
        [anon_sym_extern] = 954,
        [anon_sym_static] = 954,
        [anon_sym_auto] = 954,
        [anon_sym_register] = 954,
        [anon_sym_signed] = 954,
        [anon_sym_unsigned] = 954,
        [anon_sym_long] = 954,
        [anon_sym_short] = 954,
        [anon_sym_struct] = 954,
        [anon_sym_const] = 954,
        [anon_sym_restrict] = 954,
        [anon_sym_volatile] = 954,
        [sym_identifier] = 954,
        [sym_comment] = 42,
    },
    [366] = {
        [sym__type_specifier] = 304,
        [sym_numeric_type_specifier] = 306,
        [sym_struct_specifier] = 306,
        [sym_type_name] = 956,
        [sym_type_qualifier] = 310,
        [sym__expression] = 958,
        [sym_cast_expression] = 314,
        [sym_math_expression] = 314,
        [sym_call_expression] = 314,
        [sym_pointer_expression] = 314,
        [sym_assignment_expression] = 314,
        [sym_macro_type] = 306,
        [aux_sym_numeric_type_specifier_repeat1] = 316,
        [aux_sym_type_name_repeat1] = 318,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 320,
        [anon_sym_LPAREN] = 322,
        [anon_sym_STAR] = 324,
        [anon_sym_const] = 326,
        [anon_sym_restrict] = 326,
        [anon_sym_volatile] = 326,
        [anon_sym_AMP] = 324,
        [sym_string] = 314,
        [sym_identifier] = 328,
        [sym_number] = 314,
        [sym_comment] = 42,
    },
    [367] = {
        [sym__expression] = 960,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [368] = {
        [anon_sym_LPAREN] = 964,
        [sym_comment] = 42,
    },
    [369] = {
        [sym__init_declarator] = 90,
        [sym__declarator] = 90,
        [sym_pointer_declarator] = 90,
        [sym_function_declarator] = 90,
        [sym_array_declarator] = 90,
        [anon_sym_SEMI] = 332,
        [anon_sym_EQ] = 332,
        [anon_sym_LPAREN] = 966,
        [anon_sym_STAR] = 454,
        [anon_sym_PLUS] = 332,
        [sym_identifier] = 92,
        [sym_comment] = 42,
    },
    [370] = {
        [sym_declaration_specifiers] = 970,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 972,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 974,
        [sym_type_qualifier] = 8,
        [sym__expression] = 976,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [sym_macro_type] = 12,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [ts_builtin_sym_error] = 978,
        [anon_sym_typedef] = 28,
        [anon_sym_extern] = 28,
        [anon_sym_static] = 28,
        [anon_sym_auto] = 28,
        [anon_sym_register] = 28,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 32,
        [anon_sym_SEMI] = 974,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_const] = 34,
        [anon_sym_restrict] = 34,
        [anon_sym_volatile] = 34,
        [anon_sym_AMP] = 702,
        [sym_string] = 690,
        [sym_identifier] = 706,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [371] = {
        [sym__type_specifier] = 980,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_macro_type] = 12,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [anon_sym_signed] = 30,
        [anon_sym_unsigned] = 30,
        [anon_sym_long] = 30,
        [anon_sym_short] = 30,
        [anon_sym_struct] = 32,
        [sym_identifier] = 36,
        [sym_comment] = 42,
    },
    [372] = {
        [sym__init_declarator] = 982,
        [sym__declarator] = 984,
        [sym_pointer_declarator] = 712,
        [sym_function_declarator] = 712,
        [sym_array_declarator] = 712,
        [anon_sym_LPAREN] = 714,
        [anon_sym_STAR] = 716,
        [sym_identifier] = 712,
        [sym_comment] = 42,
    },
    [373] = {
        [sym__expression] = 986,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [anon_sym_SEMI] = 988,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [374] = {
        [anon_sym_SEMI] = 990,
        [anon_sym_EQ] = 936,
        [anon_sym_LPAREN] = 938,
        [anon_sym_STAR] = 940,
        [anon_sym_PLUS] = 942,
        [sym_comment] = 42,
    },
    [375] = {
        [anon_sym_SEMI] = 992,
        [sym_comment] = 42,
    },
    [376] = {
        [anon_sym_SEMI] = 994,
        [anon_sym_EQ] = 936,
        [anon_sym_LPAREN] = 938,
        [anon_sym_STAR] = 940,
        [anon_sym_PLUS] = 942,
        [sym_comment] = 42,
    },
    [377] = {
        [sym__expression] = 996,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_RPAREN] = 998,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [378] = {
        [anon_sym_SEMI] = 332,
        [anon_sym_EQ] = 332,
        [anon_sym_LPAREN] = 332,
        [anon_sym_STAR] = 332,
        [anon_sym_PLUS] = 332,
        [sym_comment] = 42,
    },
    [379] = {
        [aux_sym_call_expression_repeat1] = 1000,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 1002,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [380] = {
        [sym_compound_statement] = 686,
        [sym__expression] = 688,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [sym__statement] = 1004,
        [sym_for_statement] = 686,
        [sym_expression_statement] = 686,
        [anon_sym_LBRACE] = 696,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [anon_sym_for] = 704,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [381] = {
        [sym_declaration_specifiers] = 1006,
        [sym_storage_class_specifier] = 1006,
        [sym__type_specifier] = 1006,
        [sym_numeric_type_specifier] = 1006,
        [sym_struct_specifier] = 1006,
        [sym_declaration] = 1006,
        [sym_type_qualifier] = 1006,
        [sym_compound_statement] = 1006,
        [sym__expression] = 1006,
        [sym_cast_expression] = 1006,
        [sym_math_expression] = 1006,
        [sym_call_expression] = 1006,
        [sym_pointer_expression] = 1006,
        [sym_assignment_expression] = 1006,
        [sym__statement] = 1006,
        [sym_for_statement] = 1006,
        [sym_expression_statement] = 1006,
        [sym_macro_type] = 1006,
        [aux_sym_declaration_specifiers_repeat1] = 1006,
        [aux_sym_numeric_type_specifier_repeat1] = 1006,
        [aux_sym_compound_statement_repeat1] = 1006,
        [ts_builtin_sym_error] = 1006,
        [anon_sym_typedef] = 1006,
        [anon_sym_extern] = 1006,
        [anon_sym_static] = 1006,
        [anon_sym_auto] = 1006,
        [anon_sym_register] = 1006,
        [anon_sym_signed] = 1006,
        [anon_sym_unsigned] = 1006,
        [anon_sym_long] = 1006,
        [anon_sym_short] = 1006,
        [anon_sym_struct] = 1006,
        [anon_sym_LBRACE] = 1006,
        [anon_sym_RBRACE] = 1006,
        [anon_sym_LPAREN] = 1006,
        [anon_sym_STAR] = 1006,
        [anon_sym_const] = 1006,
        [anon_sym_restrict] = 1006,
        [anon_sym_volatile] = 1006,
        [anon_sym_AMP] = 1006,
        [anon_sym_for] = 1006,
        [sym_string] = 1006,
        [sym_identifier] = 1006,
        [sym_number] = 1006,
        [sym_comment] = 42,
    },
    [382] = {
        [anon_sym_RPAREN] = 1008,
        [sym_comment] = 42,
    },
    [383] = {
        [sym_compound_statement] = 686,
        [sym__expression] = 688,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [sym__statement] = 1010,
        [sym_for_statement] = 686,
        [sym_expression_statement] = 686,
        [anon_sym_LBRACE] = 696,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [anon_sym_for] = 704,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [384] = {
        [sym_declaration_specifiers] = 1012,
        [sym_storage_class_specifier] = 1012,
        [sym__type_specifier] = 1012,
        [sym_numeric_type_specifier] = 1012,
        [sym_struct_specifier] = 1012,
        [sym_declaration] = 1012,
        [sym_type_qualifier] = 1012,
        [sym_compound_statement] = 1012,
        [sym__expression] = 1012,
        [sym_cast_expression] = 1012,
        [sym_math_expression] = 1012,
        [sym_call_expression] = 1012,
        [sym_pointer_expression] = 1012,
        [sym_assignment_expression] = 1012,
        [sym__statement] = 1012,
        [sym_for_statement] = 1012,
        [sym_expression_statement] = 1012,
        [sym_macro_type] = 1012,
        [aux_sym_declaration_specifiers_repeat1] = 1012,
        [aux_sym_numeric_type_specifier_repeat1] = 1012,
        [aux_sym_compound_statement_repeat1] = 1012,
        [ts_builtin_sym_error] = 1012,
        [anon_sym_typedef] = 1012,
        [anon_sym_extern] = 1012,
        [anon_sym_static] = 1012,
        [anon_sym_auto] = 1012,
        [anon_sym_register] = 1012,
        [anon_sym_signed] = 1012,
        [anon_sym_unsigned] = 1012,
        [anon_sym_long] = 1012,
        [anon_sym_short] = 1012,
        [anon_sym_struct] = 1012,
        [anon_sym_LBRACE] = 1012,
        [anon_sym_RBRACE] = 1012,
        [anon_sym_LPAREN] = 1012,
        [anon_sym_STAR] = 1012,
        [anon_sym_const] = 1012,
        [anon_sym_restrict] = 1012,
        [anon_sym_volatile] = 1012,
        [anon_sym_AMP] = 1012,
        [anon_sym_for] = 1012,
        [sym_string] = 1012,
        [sym_identifier] = 1012,
        [sym_number] = 1012,
        [sym_comment] = 42,
    },
    [385] = {
        [sym_compound_statement] = 686,
        [sym__expression] = 688,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [sym__statement] = 1014,
        [sym_for_statement] = 686,
        [sym_expression_statement] = 686,
        [anon_sym_LBRACE] = 696,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [anon_sym_for] = 704,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [386] = {
        [sym_declaration_specifiers] = 1016,
        [sym_storage_class_specifier] = 1016,
        [sym__type_specifier] = 1016,
        [sym_numeric_type_specifier] = 1016,
        [sym_struct_specifier] = 1016,
        [sym_declaration] = 1016,
        [sym_type_qualifier] = 1016,
        [sym_compound_statement] = 1016,
        [sym__expression] = 1016,
        [sym_cast_expression] = 1016,
        [sym_math_expression] = 1016,
        [sym_call_expression] = 1016,
        [sym_pointer_expression] = 1016,
        [sym_assignment_expression] = 1016,
        [sym__statement] = 1016,
        [sym_for_statement] = 1016,
        [sym_expression_statement] = 1016,
        [sym_macro_type] = 1016,
        [aux_sym_declaration_specifiers_repeat1] = 1016,
        [aux_sym_numeric_type_specifier_repeat1] = 1016,
        [aux_sym_compound_statement_repeat1] = 1016,
        [ts_builtin_sym_error] = 1016,
        [anon_sym_typedef] = 1016,
        [anon_sym_extern] = 1016,
        [anon_sym_static] = 1016,
        [anon_sym_auto] = 1016,
        [anon_sym_register] = 1016,
        [anon_sym_signed] = 1016,
        [anon_sym_unsigned] = 1016,
        [anon_sym_long] = 1016,
        [anon_sym_short] = 1016,
        [anon_sym_struct] = 1016,
        [anon_sym_LBRACE] = 1016,
        [anon_sym_RBRACE] = 1016,
        [anon_sym_LPAREN] = 1016,
        [anon_sym_STAR] = 1016,
        [anon_sym_const] = 1016,
        [anon_sym_restrict] = 1016,
        [anon_sym_volatile] = 1016,
        [anon_sym_AMP] = 1016,
        [anon_sym_for] = 1016,
        [sym_string] = 1016,
        [sym_identifier] = 1016,
        [sym_number] = 1016,
        [sym_comment] = 42,
    },
    [387] = {
        [sym__expression] = 1018,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_RPAREN] = 1002,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [388] = {
        [sym__expression] = 1020,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [389] = {
        [sym__expression] = 1022,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_RPAREN] = 1024,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [390] = {
        [sym__expression] = 1026,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [391] = {
        [sym__expression] = 1028,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [392] = {
        [anon_sym_SEMI] = 352,
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 938,
        [anon_sym_STAR] = 940,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [393] = {
        [anon_sym_SEMI] = 352,
        [anon_sym_EQ] = 352,
        [anon_sym_LPAREN] = 938,
        [anon_sym_STAR] = 352,
        [anon_sym_PLUS] = 352,
        [sym_comment] = 42,
    },
    [394] = {
        [aux_sym_call_expression_repeat1] = 1030,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 1032,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [395] = {
        [anon_sym_SEMI] = 372,
        [anon_sym_EQ] = 372,
        [anon_sym_LPAREN] = 372,
        [anon_sym_STAR] = 372,
        [anon_sym_PLUS] = 372,
        [sym_comment] = 42,
    },
    [396] = {
        [anon_sym_RPAREN] = 1034,
        [sym_comment] = 42,
    },
    [397] = {
        [anon_sym_SEMI] = 394,
        [anon_sym_EQ] = 394,
        [anon_sym_LPAREN] = 394,
        [anon_sym_STAR] = 394,
        [anon_sym_PLUS] = 394,
        [sym_comment] = 42,
    },
    [398] = {
        [anon_sym_SEMI] = 404,
        [anon_sym_EQ] = 404,
        [anon_sym_LPAREN] = 404,
        [anon_sym_STAR] = 404,
        [anon_sym_PLUS] = 404,
        [sym_comment] = 42,
    },
    [399] = {
        [anon_sym_SEMI] = 396,
        [anon_sym_EQ] = 936,
        [anon_sym_LPAREN] = 938,
        [anon_sym_STAR] = 940,
        [anon_sym_PLUS] = 942,
        [sym_comment] = 42,
    },
    [400] = {
        [aux_sym_call_expression_repeat1] = 1036,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 1008,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [401] = {
        [anon_sym_RPAREN] = 1038,
        [sym_comment] = 42,
    },
    [402] = {
        [sym_compound_statement] = 686,
        [sym__expression] = 688,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [sym__statement] = 1040,
        [sym_for_statement] = 686,
        [sym_expression_statement] = 686,
        [anon_sym_LBRACE] = 696,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [anon_sym_for] = 704,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [403] = {
        [sym_declaration_specifiers] = 1042,
        [sym_storage_class_specifier] = 1042,
        [sym__type_specifier] = 1042,
        [sym_numeric_type_specifier] = 1042,
        [sym_struct_specifier] = 1042,
        [sym_declaration] = 1042,
        [sym_type_qualifier] = 1042,
        [sym_compound_statement] = 1042,
        [sym__expression] = 1042,
        [sym_cast_expression] = 1042,
        [sym_math_expression] = 1042,
        [sym_call_expression] = 1042,
        [sym_pointer_expression] = 1042,
        [sym_assignment_expression] = 1042,
        [sym__statement] = 1042,
        [sym_for_statement] = 1042,
        [sym_expression_statement] = 1042,
        [sym_macro_type] = 1042,
        [aux_sym_declaration_specifiers_repeat1] = 1042,
        [aux_sym_numeric_type_specifier_repeat1] = 1042,
        [aux_sym_compound_statement_repeat1] = 1042,
        [ts_builtin_sym_error] = 1042,
        [anon_sym_typedef] = 1042,
        [anon_sym_extern] = 1042,
        [anon_sym_static] = 1042,
        [anon_sym_auto] = 1042,
        [anon_sym_register] = 1042,
        [anon_sym_signed] = 1042,
        [anon_sym_unsigned] = 1042,
        [anon_sym_long] = 1042,
        [anon_sym_short] = 1042,
        [anon_sym_struct] = 1042,
        [anon_sym_LBRACE] = 1042,
        [anon_sym_RBRACE] = 1042,
        [anon_sym_LPAREN] = 1042,
        [anon_sym_STAR] = 1042,
        [anon_sym_const] = 1042,
        [anon_sym_restrict] = 1042,
        [anon_sym_volatile] = 1042,
        [anon_sym_AMP] = 1042,
        [anon_sym_for] = 1042,
        [sym_string] = 1042,
        [sym_identifier] = 1042,
        [sym_number] = 1042,
        [sym_comment] = 42,
    },
    [404] = {
        [sym__expression] = 632,
        [sym_cast_expression] = 632,
        [sym_math_expression] = 632,
        [sym_call_expression] = 632,
        [sym_pointer_expression] = 632,
        [sym_assignment_expression] = 632,
        [anon_sym_SEMI] = 632,
        [anon_sym_LPAREN] = 632,
        [anon_sym_STAR] = 632,
        [anon_sym_AMP] = 632,
        [sym_string] = 632,
        [sym_identifier] = 632,
        [sym_number] = 632,
        [sym_comment] = 42,
    },
    [405] = {
        [sym__expression] = 1044,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [anon_sym_SEMI] = 994,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [406] = {
        [anon_sym_SEMI] = 1046,
        [anon_sym_EQ] = 936,
        [anon_sym_LPAREN] = 938,
        [anon_sym_STAR] = 940,
        [anon_sym_PLUS] = 942,
        [sym_comment] = 42,
    },
    [407] = {
        [sym__expression] = 1048,
        [sym_cast_expression] = 338,
        [sym_math_expression] = 338,
        [sym_call_expression] = 338,
        [sym_pointer_expression] = 338,
        [sym_assignment_expression] = 338,
        [anon_sym_LPAREN] = 340,
        [anon_sym_RPAREN] = 1008,
        [anon_sym_STAR] = 344,
        [anon_sym_AMP] = 344,
        [sym_string] = 338,
        [sym_identifier] = 346,
        [sym_number] = 338,
        [sym_comment] = 42,
    },
    [408] = {
        [aux_sym_call_expression_repeat1] = 1050,
        [anon_sym_COMMA] = 356,
        [anon_sym_EQ] = 358,
        [anon_sym_LPAREN] = 360,
        [anon_sym_RPAREN] = 1038,
        [anon_sym_STAR] = 364,
        [anon_sym_PLUS] = 366,
        [sym_comment] = 42,
    },
    [409] = {
        [anon_sym_RPAREN] = 1052,
        [sym_comment] = 42,
    },
    [410] = {
        [sym_compound_statement] = 686,
        [sym__expression] = 688,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [sym__statement] = 1054,
        [sym_for_statement] = 686,
        [sym_expression_statement] = 686,
        [anon_sym_LBRACE] = 696,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [anon_sym_for] = 704,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [411] = {
        [sym_declaration_specifiers] = 1056,
        [sym_storage_class_specifier] = 1056,
        [sym__type_specifier] = 1056,
        [sym_numeric_type_specifier] = 1056,
        [sym_struct_specifier] = 1056,
        [sym_declaration] = 1056,
        [sym_type_qualifier] = 1056,
        [sym_compound_statement] = 1056,
        [sym__expression] = 1056,
        [sym_cast_expression] = 1056,
        [sym_math_expression] = 1056,
        [sym_call_expression] = 1056,
        [sym_pointer_expression] = 1056,
        [sym_assignment_expression] = 1056,
        [sym__statement] = 1056,
        [sym_for_statement] = 1056,
        [sym_expression_statement] = 1056,
        [sym_macro_type] = 1056,
        [aux_sym_declaration_specifiers_repeat1] = 1056,
        [aux_sym_numeric_type_specifier_repeat1] = 1056,
        [aux_sym_compound_statement_repeat1] = 1056,
        [ts_builtin_sym_error] = 1056,
        [anon_sym_typedef] = 1056,
        [anon_sym_extern] = 1056,
        [anon_sym_static] = 1056,
        [anon_sym_auto] = 1056,
        [anon_sym_register] = 1056,
        [anon_sym_signed] = 1056,
        [anon_sym_unsigned] = 1056,
        [anon_sym_long] = 1056,
        [anon_sym_short] = 1056,
        [anon_sym_struct] = 1056,
        [anon_sym_LBRACE] = 1056,
        [anon_sym_RBRACE] = 1056,
        [anon_sym_LPAREN] = 1056,
        [anon_sym_STAR] = 1056,
        [anon_sym_const] = 1056,
        [anon_sym_restrict] = 1056,
        [anon_sym_volatile] = 1056,
        [anon_sym_AMP] = 1056,
        [anon_sym_for] = 1056,
        [sym_string] = 1056,
        [sym_identifier] = 1056,
        [sym_number] = 1056,
        [sym_comment] = 42,
    },
    [412] = {
        [aux_sym_declaration_repeat1] = 1058,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 1060,
        [sym_comment] = 42,
    },
    [413] = {
        [aux_sym_declaration_repeat1] = 1058,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 1060,
        [anon_sym_EQ] = 648,
        [anon_sym_LBRACK] = 892,
        [anon_sym_LPAREN] = 894,
        [sym_comment] = 42,
    },
    [414] = {
        [anon_sym_SEMI] = 1062,
        [sym_comment] = 42,
    },
    [415] = {
        [sym__expression] = 718,
        [sym_cast_expression] = 718,
        [sym_math_expression] = 718,
        [sym_call_expression] = 718,
        [sym_pointer_expression] = 718,
        [sym_assignment_expression] = 718,
        [anon_sym_SEMI] = 718,
        [anon_sym_LPAREN] = 718,
        [anon_sym_STAR] = 718,
        [anon_sym_AMP] = 718,
        [sym_string] = 718,
        [sym_identifier] = 718,
        [sym_number] = 718,
        [sym_comment] = 42,
    },
    [416] = {
        [sym__expression] = 1064,
        [sym_cast_expression] = 1064,
        [sym_math_expression] = 1064,
        [sym_call_expression] = 1064,
        [sym_pointer_expression] = 1064,
        [sym_assignment_expression] = 1064,
        [anon_sym_SEMI] = 1064,
        [anon_sym_LPAREN] = 1064,
        [anon_sym_STAR] = 1064,
        [anon_sym_AMP] = 1064,
        [sym_string] = 1064,
        [sym_identifier] = 1064,
        [sym_number] = 1064,
        [sym_comment] = 42,
    },
    [417] = {
        [sym__init_declarator] = 1066,
        [sym__declarator] = 1068,
        [sym_pointer_declarator] = 712,
        [sym_function_declarator] = 712,
        [sym_array_declarator] = 712,
        [anon_sym_LPAREN] = 714,
        [anon_sym_STAR] = 716,
        [sym_identifier] = 712,
        [sym_comment] = 42,
    },
    [418] = {
        [aux_sym_declaration_repeat1] = 1070,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 1062,
        [sym_comment] = 42,
    },
    [419] = {
        [aux_sym_declaration_repeat1] = 1070,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 1062,
        [anon_sym_EQ] = 648,
        [anon_sym_LBRACK] = 892,
        [anon_sym_LPAREN] = 894,
        [sym_comment] = 42,
    },
    [420] = {
        [anon_sym_SEMI] = 1072,
        [sym_comment] = 42,
    },
    [421] = {
        [sym__expression] = 1074,
        [sym_cast_expression] = 1074,
        [sym_math_expression] = 1074,
        [sym_call_expression] = 1074,
        [sym_pointer_expression] = 1074,
        [sym_assignment_expression] = 1074,
        [anon_sym_SEMI] = 1074,
        [anon_sym_LPAREN] = 1074,
        [anon_sym_STAR] = 1074,
        [anon_sym_AMP] = 1074,
        [sym_string] = 1074,
        [sym_identifier] = 1074,
        [sym_number] = 1074,
        [sym_comment] = 42,
    },
    [422] = {
        [anon_sym_SEMI] = 334,
        [anon_sym_EQ] = 334,
        [anon_sym_LPAREN] = 938,
        [anon_sym_STAR] = 940,
        [anon_sym_PLUS] = 942,
        [sym_comment] = 42,
    },
    [423] = {
        [anon_sym_RPAREN] = 1076,
        [sym_comment] = 42,
    },
    [424] = {
        [anon_sym_EQ] = 422,
        [anon_sym_LPAREN] = 424,
        [anon_sym_RPAREN] = 1078,
        [anon_sym_STAR] = 428,
        [anon_sym_PLUS] = 430,
        [sym_comment] = 42,
    },
    [425] = {
        [anon_sym_SEMI] = 481,
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 42,
    },
    [426] = {
        [sym__expression] = 1080,
        [sym_cast_expression] = 690,
        [sym_math_expression] = 690,
        [sym_call_expression] = 690,
        [sym_pointer_expression] = 690,
        [sym_assignment_expression] = 690,
        [anon_sym_LPAREN] = 700,
        [anon_sym_STAR] = 702,
        [anon_sym_AMP] = 702,
        [sym_string] = 690,
        [sym_identifier] = 962,
        [sym_number] = 690,
        [sym_comment] = 42,
    },
    [427] = {
        [anon_sym_SEMI] = 485,
        [anon_sym_EQ] = 485,
        [anon_sym_LPAREN] = 485,
        [anon_sym_STAR] = 485,
        [anon_sym_PLUS] = 485,
        [sym_comment] = 42,
    },
    [428] = {
        [anon_sym_RBRACE] = 1082,
        [sym_comment] = 42,
    },
    [429] = {
        [anon_sym_RBRACE] = 1082,
        [anon_sym_SEMI] = 946,
        [sym_comment] = 42,
    },
    [430] = {
        [sym_declaration_specifiers] = 954,
        [sym_storage_class_specifier] = 954,
        [sym__type_specifier] = 954,
        [sym_numeric_type_specifier] = 954,
        [sym_struct_specifier] = 954,
        [sym_declaration] = 954,
        [sym_type_qualifier] = 954,
        [sym_compound_statement] = 954,
        [sym__expression] = 954,
        [sym_cast_expression] = 954,
        [sym_math_expression] = 954,
        [sym_call_expression] = 954,
        [sym_pointer_expression] = 954,
        [sym_assignment_expression] = 954,
        [sym__statement] = 954,
        [sym_for_statement] = 954,
        [sym_expression_statement] = 954,
        [sym_macro_type] = 954,
        [aux_sym_declaration_specifiers_repeat1] = 954,
        [aux_sym_numeric_type_specifier_repeat1] = 954,
        [aux_sym_compound_statement_repeat1] = 954,
        [ts_builtin_sym_error] = 954,
        [anon_sym_typedef] = 954,
        [anon_sym_extern] = 954,
        [anon_sym_static] = 954,
        [anon_sym_auto] = 954,
        [anon_sym_register] = 954,
        [anon_sym_signed] = 954,
        [anon_sym_unsigned] = 954,
        [anon_sym_long] = 954,
        [anon_sym_short] = 954,
        [anon_sym_struct] = 954,
        [anon_sym_LBRACE] = 954,
        [anon_sym_RBRACE] = 954,
        [anon_sym_LPAREN] = 954,
        [anon_sym_STAR] = 954,
        [anon_sym_const] = 954,
        [anon_sym_restrict] = 954,
        [anon_sym_volatile] = 954,
        [anon_sym_AMP] = 954,
        [anon_sym_for] = 954,
        [sym_string] = 954,
        [sym_identifier] = 954,
        [sym_number] = 954,
        [sym_comment] = 42,
    },
    [431] = {
        [sym_declaration_specifiers] = 1084,
        [sym_storage_class_specifier] = 1084,
        [sym__type_specifier] = 1084,
        [sym_numeric_type_specifier] = 1084,
        [sym_struct_specifier] = 1084,
        [sym_declaration] = 1084,
        [sym_type_qualifier] = 1084,
        [sym_compound_statement] = 1084,
        [sym__expression] = 1084,
        [sym_cast_expression] = 1084,
        [sym_math_expression] = 1084,
        [sym_call_expression] = 1084,
        [sym_pointer_expression] = 1084,
        [sym_assignment_expression] = 1084,
        [sym__statement] = 1084,
        [sym_for_statement] = 1084,
        [sym_expression_statement] = 1084,
        [sym_macro_type] = 1084,
        [aux_sym_declaration_specifiers_repeat1] = 1084,
        [aux_sym_numeric_type_specifier_repeat1] = 1084,
        [aux_sym_compound_statement_repeat1] = 1084,
        [ts_builtin_sym_error] = 1084,
        [anon_sym_typedef] = 1084,
        [anon_sym_extern] = 1084,
        [anon_sym_static] = 1084,
        [anon_sym_auto] = 1084,
        [anon_sym_register] = 1084,
        [anon_sym_signed] = 1084,
        [anon_sym_unsigned] = 1084,
        [anon_sym_long] = 1084,
        [anon_sym_short] = 1084,
        [anon_sym_struct] = 1084,
        [anon_sym_LBRACE] = 1084,
        [anon_sym_RBRACE] = 1084,
        [anon_sym_LPAREN] = 1084,
        [anon_sym_STAR] = 1084,
        [anon_sym_const] = 1084,
        [anon_sym_restrict] = 1084,
        [anon_sym_volatile] = 1084,
        [anon_sym_AMP] = 1084,
        [anon_sym_for] = 1084,
        [sym_string] = 1084,
        [sym_identifier] = 1084,
        [sym_number] = 1084,
        [sym_comment] = 42,
    },
    [432] = {
        [sym_declaration_specifiers] = 632,
        [sym_storage_class_specifier] = 632,
        [sym__type_specifier] = 632,
        [sym_numeric_type_specifier] = 632,
        [sym_struct_specifier] = 632,
        [sym_declaration] = 632,
        [sym_type_qualifier] = 632,
        [sym_compound_statement] = 632,
        [sym__expression] = 632,
        [sym_cast_expression] = 632,
        [sym_math_expression] = 632,
        [sym_call_expression] = 632,
        [sym_pointer_expression] = 632,
        [sym_assignment_expression] = 632,
        [sym__statement] = 632,
        [sym_for_statement] = 632,
        [sym_expression_statement] = 632,
        [sym_macro_type] = 632,
        [aux_sym_declaration_specifiers_repeat1] = 632,
        [aux_sym_numeric_type_specifier_repeat1] = 632,
        [aux_sym_compound_statement_repeat1] = 632,
        [ts_builtin_sym_error] = 632,
        [anon_sym_typedef] = 632,
        [anon_sym_extern] = 632,
        [anon_sym_static] = 632,
        [anon_sym_auto] = 632,
        [anon_sym_register] = 632,
        [anon_sym_signed] = 632,
        [anon_sym_unsigned] = 632,
        [anon_sym_long] = 632,
        [anon_sym_short] = 632,
        [anon_sym_struct] = 632,
        [anon_sym_LBRACE] = 632,
        [anon_sym_RBRACE] = 632,
        [anon_sym_LPAREN] = 632,
        [anon_sym_STAR] = 632,
        [anon_sym_const] = 632,
        [anon_sym_restrict] = 632,
        [anon_sym_volatile] = 632,
        [anon_sym_AMP] = 632,
        [anon_sym_for] = 632,
        [sym_string] = 632,
        [sym_identifier] = 632,
        [sym_number] = 632,
        [sym_comment] = 42,
    },
    [433] = {
        [sym_preproc_define] = 1084,
        [sym_preproc_call] = 1084,
        [sym_function_definition] = 1084,
        [sym_declaration_specifiers] = 1084,
        [sym_storage_class_specifier] = 1084,
        [sym__type_specifier] = 1084,
        [sym_numeric_type_specifier] = 1084,
        [sym_struct_specifier] = 1084,
        [sym_declaration] = 1084,
        [sym_type_qualifier] = 1084,
        [sym_macro_type] = 1084,
        [aux_sym_translation_unit_repeat1] = 1084,
        [aux_sym_declaration_specifiers_repeat1] = 1084,
        [aux_sym_numeric_type_specifier_repeat1] = 1084,
        [ts_builtin_sym_error] = 1084,
        [ts_builtin_sym_end] = 1084,
        [anon_sym_POUNDdefine] = 1084,
        [sym_preproc_directive] = 1084,
        [anon_sym_typedef] = 1084,
        [anon_sym_extern] = 1084,
        [anon_sym_static] = 1084,
        [anon_sym_auto] = 1084,
        [anon_sym_register] = 1084,
        [anon_sym_signed] = 1084,
        [anon_sym_unsigned] = 1084,
        [anon_sym_long] = 1084,
        [anon_sym_short] = 1084,
        [anon_sym_struct] = 1084,
        [anon_sym_const] = 1084,
        [anon_sym_restrict] = 1084,
        [anon_sym_volatile] = 1084,
        [sym_identifier] = 1084,
        [sym_comment] = 42,
    },
    [434] = {
        [anon_sym_RBRACE] = 1086,
        [sym_comment] = 42,
    },
    [435] = {
        [anon_sym_SEMI] = 946,
        [sym_comment] = 42,
    },
    [436] = {
        [sym_declaration_specifiers] = 1088,
        [sym_storage_class_specifier] = 1088,
        [sym__type_specifier] = 1088,
        [sym_numeric_type_specifier] = 1088,
        [sym_struct_specifier] = 1088,
        [sym_declaration] = 1088,
        [sym_type_qualifier] = 1088,
        [sym_compound_statement] = 1088,
        [sym__expression] = 1088,
        [sym_cast_expression] = 1088,
        [sym_math_expression] = 1088,
        [sym_call_expression] = 1088,
        [sym_pointer_expression] = 1088,
        [sym_assignment_expression] = 1088,
        [sym__statement] = 1088,
        [sym_for_statement] = 1088,
        [sym_expression_statement] = 1088,
        [sym_macro_type] = 1088,
        [aux_sym_declaration_specifiers_repeat1] = 1088,
        [aux_sym_numeric_type_specifier_repeat1] = 1088,
        [aux_sym_compound_statement_repeat1] = 1088,
        [ts_builtin_sym_error] = 1088,
        [anon_sym_typedef] = 1088,
        [anon_sym_extern] = 1088,
        [anon_sym_static] = 1088,
        [anon_sym_auto] = 1088,
        [anon_sym_register] = 1088,
        [anon_sym_signed] = 1088,
        [anon_sym_unsigned] = 1088,
        [anon_sym_long] = 1088,
        [anon_sym_short] = 1088,
        [anon_sym_struct] = 1088,
        [anon_sym_LBRACE] = 1088,
        [anon_sym_RBRACE] = 1088,
        [anon_sym_LPAREN] = 1088,
        [anon_sym_STAR] = 1088,
        [anon_sym_const] = 1088,
        [anon_sym_restrict] = 1088,
        [anon_sym_volatile] = 1088,
        [anon_sym_AMP] = 1088,
        [anon_sym_for] = 1088,
        [sym_string] = 1088,
        [sym_identifier] = 1088,
        [sym_number] = 1088,
        [sym_comment] = 42,
    },
    [437] = {
        [aux_sym_declaration_repeat1] = 1090,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 1092,
        [sym_comment] = 42,
    },
    [438] = {
        [aux_sym_declaration_repeat1] = 1090,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 1092,
        [anon_sym_EQ] = 648,
        [anon_sym_LBRACK] = 892,
        [anon_sym_LPAREN] = 894,
        [sym_comment] = 42,
    },
    [439] = {
        [anon_sym_SEMI] = 1094,
        [sym_comment] = 42,
    },
    [440] = {
        [sym_declaration_specifiers] = 718,
        [sym_storage_class_specifier] = 718,
        [sym__type_specifier] = 718,
        [sym_numeric_type_specifier] = 718,
        [sym_struct_specifier] = 718,
        [sym_declaration] = 718,
        [sym_type_qualifier] = 718,
        [sym_compound_statement] = 718,
        [sym__expression] = 718,
        [sym_cast_expression] = 718,
        [sym_math_expression] = 718,
        [sym_call_expression] = 718,
        [sym_pointer_expression] = 718,
        [sym_assignment_expression] = 718,
        [sym__statement] = 718,
        [sym_for_statement] = 718,
        [sym_expression_statement] = 718,
        [sym_macro_type] = 718,
        [aux_sym_declaration_specifiers_repeat1] = 718,
        [aux_sym_numeric_type_specifier_repeat1] = 718,
        [aux_sym_compound_statement_repeat1] = 718,
        [ts_builtin_sym_error] = 718,
        [anon_sym_typedef] = 718,
        [anon_sym_extern] = 718,
        [anon_sym_static] = 718,
        [anon_sym_auto] = 718,
        [anon_sym_register] = 718,
        [anon_sym_signed] = 718,
        [anon_sym_unsigned] = 718,
        [anon_sym_long] = 718,
        [anon_sym_short] = 718,
        [anon_sym_struct] = 718,
        [anon_sym_LBRACE] = 718,
        [anon_sym_RBRACE] = 718,
        [anon_sym_LPAREN] = 718,
        [anon_sym_STAR] = 718,
        [anon_sym_const] = 718,
        [anon_sym_restrict] = 718,
        [anon_sym_volatile] = 718,
        [anon_sym_AMP] = 718,
        [anon_sym_for] = 718,
        [sym_string] = 718,
        [sym_identifier] = 718,
        [sym_number] = 718,
        [sym_comment] = 42,
    },
    [441] = {
        [sym_declaration_specifiers] = 1064,
        [sym_storage_class_specifier] = 1064,
        [sym__type_specifier] = 1064,
        [sym_numeric_type_specifier] = 1064,
        [sym_struct_specifier] = 1064,
        [sym_declaration] = 1064,
        [sym_type_qualifier] = 1064,
        [sym_compound_statement] = 1064,
        [sym__expression] = 1064,
        [sym_cast_expression] = 1064,
        [sym_math_expression] = 1064,
        [sym_call_expression] = 1064,
        [sym_pointer_expression] = 1064,
        [sym_assignment_expression] = 1064,
        [sym__statement] = 1064,
        [sym_for_statement] = 1064,
        [sym_expression_statement] = 1064,
        [sym_macro_type] = 1064,
        [aux_sym_declaration_specifiers_repeat1] = 1064,
        [aux_sym_numeric_type_specifier_repeat1] = 1064,
        [aux_sym_compound_statement_repeat1] = 1064,
        [ts_builtin_sym_error] = 1064,
        [anon_sym_typedef] = 1064,
        [anon_sym_extern] = 1064,
        [anon_sym_static] = 1064,
        [anon_sym_auto] = 1064,
        [anon_sym_register] = 1064,
        [anon_sym_signed] = 1064,
        [anon_sym_unsigned] = 1064,
        [anon_sym_long] = 1064,
        [anon_sym_short] = 1064,
        [anon_sym_struct] = 1064,
        [anon_sym_LBRACE] = 1064,
        [anon_sym_RBRACE] = 1064,
        [anon_sym_LPAREN] = 1064,
        [anon_sym_STAR] = 1064,
        [anon_sym_const] = 1064,
        [anon_sym_restrict] = 1064,
        [anon_sym_volatile] = 1064,
        [anon_sym_AMP] = 1064,
        [anon_sym_for] = 1064,
        [sym_string] = 1064,
        [sym_identifier] = 1064,
        [sym_number] = 1064,
        [sym_comment] = 42,
    },
    [442] = {
        [sym__init_declarator] = 1096,
        [sym__declarator] = 1098,
        [sym_pointer_declarator] = 712,
        [sym_function_declarator] = 712,
        [sym_array_declarator] = 712,
        [anon_sym_LPAREN] = 714,
        [anon_sym_STAR] = 716,
        [sym_identifier] = 712,
        [sym_comment] = 42,
    },
    [443] = {
        [aux_sym_declaration_repeat1] = 1100,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 1094,
        [sym_comment] = 42,
    },
    [444] = {
        [aux_sym_declaration_repeat1] = 1100,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 1094,
        [anon_sym_EQ] = 648,
        [anon_sym_LBRACK] = 892,
        [anon_sym_LPAREN] = 894,
        [sym_comment] = 42,
    },
    [445] = {
        [anon_sym_SEMI] = 1102,
        [sym_comment] = 42,
    },
    [446] = {
        [sym_declaration_specifiers] = 1074,
        [sym_storage_class_specifier] = 1074,
        [sym__type_specifier] = 1074,
        [sym_numeric_type_specifier] = 1074,
        [sym_struct_specifier] = 1074,
        [sym_declaration] = 1074,
        [sym_type_qualifier] = 1074,
        [sym_compound_statement] = 1074,
        [sym__expression] = 1074,
        [sym_cast_expression] = 1074,
        [sym_math_expression] = 1074,
        [sym_call_expression] = 1074,
        [sym_pointer_expression] = 1074,
        [sym_assignment_expression] = 1074,
        [sym__statement] = 1074,
        [sym_for_statement] = 1074,
        [sym_expression_statement] = 1074,
        [sym_macro_type] = 1074,
        [aux_sym_declaration_specifiers_repeat1] = 1074,
        [aux_sym_numeric_type_specifier_repeat1] = 1074,
        [aux_sym_compound_statement_repeat1] = 1074,
        [ts_builtin_sym_error] = 1074,
        [anon_sym_typedef] = 1074,
        [anon_sym_extern] = 1074,
        [anon_sym_static] = 1074,
        [anon_sym_auto] = 1074,
        [anon_sym_register] = 1074,
        [anon_sym_signed] = 1074,
        [anon_sym_unsigned] = 1074,
        [anon_sym_long] = 1074,
        [anon_sym_short] = 1074,
        [anon_sym_struct] = 1074,
        [anon_sym_LBRACE] = 1074,
        [anon_sym_RBRACE] = 1074,
        [anon_sym_LPAREN] = 1074,
        [anon_sym_STAR] = 1074,
        [anon_sym_const] = 1074,
        [anon_sym_restrict] = 1074,
        [anon_sym_volatile] = 1074,
        [anon_sym_AMP] = 1074,
        [anon_sym_for] = 1074,
        [sym_string] = 1074,
        [sym_identifier] = 1074,
        [sym_number] = 1074,
        [sym_comment] = 42,
    },
    [447] = {
        [sym_preproc_define] = 1064,
        [sym_preproc_call] = 1064,
        [sym_function_definition] = 1064,
        [sym_declaration_specifiers] = 1064,
        [sym_storage_class_specifier] = 1064,
        [sym__type_specifier] = 1064,
        [sym_numeric_type_specifier] = 1064,
        [sym_struct_specifier] = 1064,
        [sym_declaration] = 1064,
        [sym_type_qualifier] = 1064,
        [sym_macro_type] = 1064,
        [aux_sym_translation_unit_repeat1] = 1064,
        [aux_sym_declaration_specifiers_repeat1] = 1064,
        [aux_sym_numeric_type_specifier_repeat1] = 1064,
        [ts_builtin_sym_error] = 1064,
        [ts_builtin_sym_end] = 1064,
        [anon_sym_POUNDdefine] = 1064,
        [sym_preproc_directive] = 1064,
        [anon_sym_typedef] = 1064,
        [anon_sym_extern] = 1064,
        [anon_sym_static] = 1064,
        [anon_sym_auto] = 1064,
        [anon_sym_register] = 1064,
        [anon_sym_signed] = 1064,
        [anon_sym_unsigned] = 1064,
        [anon_sym_long] = 1064,
        [anon_sym_short] = 1064,
        [anon_sym_struct] = 1064,
        [anon_sym_const] = 1064,
        [anon_sym_restrict] = 1064,
        [anon_sym_volatile] = 1064,
        [sym_identifier] = 1064,
        [sym_comment] = 42,
    },
    [448] = {
        [sym__init_declarator] = 1104,
        [sym__declarator] = 1106,
        [sym_pointer_declarator] = 58,
        [sym_function_declarator] = 58,
        [sym_array_declarator] = 58,
        [anon_sym_LPAREN] = 60,
        [anon_sym_STAR] = 62,
        [sym_identifier] = 58,
        [sym_comment] = 42,
    },
    [449] = {
        [aux_sym_declaration_repeat1] = 1108,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 678,
        [sym_comment] = 42,
    },
    [450] = {
        [sym_compound_statement] = 1110,
        [aux_sym_declaration_repeat1] = 1108,
        [anon_sym_LBRACE] = 646,
        [anon_sym_COMMA] = 640,
        [anon_sym_SEMI] = 678,
        [anon_sym_EQ] = 648,
        [anon_sym_LBRACK] = 650,
        [anon_sym_LPAREN] = 652,
        [sym_comment] = 42,
    },
    [451] = {
        [sym_preproc_define] = 1112,
        [sym_preproc_call] = 1112,
        [sym_function_definition] = 1112,
        [sym_declaration_specifiers] = 1112,
        [sym_storage_class_specifier] = 1112,
        [sym__type_specifier] = 1112,
        [sym_numeric_type_specifier] = 1112,
        [sym_struct_specifier] = 1112,
        [sym_declaration] = 1112,
        [sym_type_qualifier] = 1112,
        [sym_macro_type] = 1112,
        [aux_sym_translation_unit_repeat1] = 1112,
        [aux_sym_declaration_specifiers_repeat1] = 1112,
        [aux_sym_numeric_type_specifier_repeat1] = 1112,
        [ts_builtin_sym_error] = 1112,
        [ts_builtin_sym_end] = 1112,
        [anon_sym_POUNDdefine] = 1112,
        [sym_preproc_directive] = 1112,
        [anon_sym_typedef] = 1112,
        [anon_sym_extern] = 1112,
        [anon_sym_static] = 1112,
        [anon_sym_auto] = 1112,
        [anon_sym_register] = 1112,
        [anon_sym_signed] = 1112,
        [anon_sym_unsigned] = 1112,
        [anon_sym_long] = 1112,
        [anon_sym_short] = 1112,
        [anon_sym_struct] = 1112,
        [anon_sym_const] = 1112,
        [anon_sym_restrict] = 1112,
        [anon_sym_volatile] = 1112,
        [sym_identifier] = 1112,
        [sym_comment] = 42,
    },
    [452] = {
        [anon_sym_SEMI] = 1114,
        [sym_comment] = 42,
    },
    [453] = {
        [sym_preproc_define] = 1074,
        [sym_preproc_call] = 1074,
        [sym_function_definition] = 1074,
        [sym_declaration_specifiers] = 1074,
        [sym_storage_class_specifier] = 1074,
        [sym__type_specifier] = 1074,
        [sym_numeric_type_specifier] = 1074,
        [sym_struct_specifier] = 1074,
        [sym_declaration] = 1074,
        [sym_type_qualifier] = 1074,
        [sym_macro_type] = 1074,
        [aux_sym_translation_unit_repeat1] = 1074,
        [aux_sym_declaration_specifiers_repeat1] = 1074,
        [aux_sym_numeric_type_specifier_repeat1] = 1074,
        [ts_builtin_sym_error] = 1074,
        [ts_builtin_sym_end] = 1074,
        [anon_sym_POUNDdefine] = 1074,
        [sym_preproc_directive] = 1074,
        [anon_sym_typedef] = 1074,
        [anon_sym_extern] = 1074,
        [anon_sym_static] = 1074,
        [anon_sym_auto] = 1074,
        [anon_sym_register] = 1074,
        [anon_sym_signed] = 1074,
        [anon_sym_unsigned] = 1074,
        [anon_sym_long] = 1074,
        [anon_sym_short] = 1074,
        [anon_sym_struct] = 1074,
        [anon_sym_const] = 1074,
        [anon_sym_restrict] = 1074,
        [anon_sym_volatile] = 1074,
        [sym_identifier] = 1074,
        [sym_comment] = 42,
    },
};

static TSParseActionEntry ts_parse_actions[] = {
    [0] = {.count = 1}, ERROR(),
    [2] = {.count = 1}, SHIFT(1, 0),
    [4] = {.count = 1}, SHIFT(2, 0),
    [6] = {.count = 1}, SHIFT(3, 0),
    [8] = {.count = 1}, SHIFT(4, 0),
    [10] = {.count = 1}, SHIFT(5, 0),
    [12] = {.count = 1}, SHIFT(6, 0),
    [14] = {.count = 1}, SHIFT(7, 0),
    [16] = {.count = 1}, SHIFT(8, 0),
    [18] = {.count = 1}, SHIFT(9, 0),
    [20] = {.count = 1}, SHIFT(10, 0),
    [22] = {.count = 1}, REDUCE(sym_translation_unit, 0, 0),
    [24] = {.count = 1}, SHIFT(11, 0),
    [26] = {.count = 1}, SHIFT(12, 0),
    [28] = {.count = 1}, SHIFT(13, 0),
    [30] = {.count = 1}, SHIFT(14, 0),
    [32] = {.count = 1}, SHIFT(15, 0),
    [34] = {.count = 1}, SHIFT(16, 0),
    [36] = {.count = 1}, SHIFT(17, 0),
    [38] = {.count = 1}, SHIFT_EXTRA(),
    [40] = {.count = 1}, ACCEPT_INPUT(),
    [42] = {.count = 1}, SHIFT_EXTRA(),
    [44] = {.count = 1}, SHIFT(240, 0),
    [46] = {.count = 1}, REDUCE(aux_sym_translation_unit_repeat1, 1, 0),
    [48] = {.count = 1}, SHIFT(448, 0),
    [50] = {.count = 1}, REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0),
    [52] = {.count = 1}, SHIFT(239, 0),
    [54] = {.count = 1}, SHIFT(241, 0),
    [56] = {.count = 1}, SHIFT(242, 0),
    [58] = {.count = 1}, SHIFT(243, 0),
    [60] = {.count = 1}, SHIFT(244, 0),
    [62] = {.count = 1}, SHIFT(245, 0),
    [64] = {.count = 1}, REDUCE(sym__type_specifier, 1, 0),
    [66] = {.count = 1}, REDUCE(sym_translation_unit, 1, 0),
    [68] = {.count = 1}, REDUCE(sym_declaration_specifiers, 1, 0),
    [70] = {.count = 1}, SHIFT(238, 0),
    [72] = {.count = 1}, SHIFT(237, 0),
    [74] = {.count = 1}, SHIFT(233, 0),
    [76] = {.count = 1}, SHIFT(232, 0),
    [78] = {.count = 1}, REDUCE(sym_storage_class_specifier, 1, 0),
    [80] = {.count = 1}, SHIFT(231, 0),
    [82] = {.count = 1}, REDUCE(aux_sym_numeric_type_specifier_repeat1, 1, 0),
    [84] = {.count = 1}, SHIFT(223, 0),
    [86] = {.count = 1}, SHIFT(224, 0),
    [88] = {.count = 1}, REDUCE(sym_type_qualifier, 1, 0),
    [90] = {.count = 1}, REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT),
    [92] = {.count = 1}, REDUCE(sym__type_specifier, 1, FRAGILE),
    [94] = {.count = 2}, REDUCE(sym__type_specifier, 1, FRAGILE), SHIFT(18, 0),
    [97] = {.count = 1}, SHIFT(19, 0),
    [99] = {.count = 1}, SHIFT(20, 0),
    [101] = {.count = 1}, SHIFT(21, 0),
    [103] = {.count = 1}, SHIFT(22, 0),
    [105] = {.count = 1}, SHIFT(23, 0),
    [107] = {.count = 1}, SHIFT(222, 0),
    [109] = {.count = 1}, SHIFT(221, 0),
    [111] = {.count = 1}, SHIFT(27, 0),
    [113] = {.count = 1}, SHIFT(28, 0),
    [115] = {.count = 1}, SHIFT(24, 0),
    [117] = {.count = 1}, SHIFT(25, 0),
    [119] = {.count = 1}, SHIFT(26, 0),
    [121] = {.count = 1}, REDUCE(sym_macro_type, 4, 0),
    [123] = {.count = 1}, SHIFT(30, 0),
    [125] = {.count = 1}, SHIFT(31, 0),
    [127] = {.count = 1}, SHIFT(32, 0),
    [129] = {.count = 1}, SHIFT(33, 0),
    [131] = {.count = 1}, SHIFT(219, 0),
    [133] = {.count = 1}, SHIFT(35, 0),
    [135] = {.count = 1}, SHIFT(220, 0),
    [137] = {.count = 1}, SHIFT(37, 0),
    [139] = {.count = 1}, SHIFT(29, 0),
    [141] = {.count = 1}, SHIFT(34, 0),
    [143] = {.count = 1}, SHIFT(36, 0),
    [145] = {.count = 1}, SHIFT(52, 0),
    [147] = {.count = 1}, SHIFT(53, 0),
    [149] = {.count = 1}, SHIFT(54, 0),
    [151] = {.count = 1}, SHIFT(55, 0),
    [153] = {.count = 1}, SHIFT(51, 0),
    [155] = {.count = 1}, REDUCE(aux_sym_struct_specifier_repeat1, 1, 0),
    [157] = {.count = 1}, SHIFT(50, 0),
    [159] = {.count = 1}, SHIFT(49, 0),
    [161] = {.count = 1}, SHIFT(41, 0),
    [163] = {.count = 1}, SHIFT(42, 0),
    [165] = {.count = 1}, REDUCE(sym_struct_specifier, 4, 0),
    [167] = {.count = 2}, REDUCE(sym__type_specifier, 1, FRAGILE), SHIFT(38, 0),
    [170] = {.count = 1}, SHIFT(39, 0),
    [172] = {.count = 1}, SHIFT(40, 0),
    [174] = {.count = 1}, SHIFT(47, 0),
    [176] = {.count = 1}, SHIFT(48, 0),
    [178] = {.count = 1}, SHIFT(43, 0),
    [180] = {.count = 1}, SHIFT(44, 0),
    [182] = {.count = 1}, SHIFT(45, 0),
    [184] = {.count = 1}, SHIFT(46, 0),
    [186] = {.count = 1}, REDUCE(sym_struct_specifier, 5, 0),
    [188] = {.count = 1}, REDUCE(sym_struct_specifier, 3, 0),
    [190] = {.count = 1}, REDUCE(sym_numeric_type_specifier, 2, 0),
    [192] = {.count = 1}, REDUCE(aux_sym_struct_specifier_repeat1, 2, 0),
    [194] = {.count = 1}, REDUCE(sym_struct_declaration, 2, 0),
    [196] = {.count = 1}, SHIFT(57, 0),
    [198] = {.count = 1}, SHIFT(58, 0),
    [200] = {.count = 1}, REDUCE(sym__declarator, 1, 0),
    [202] = {.count = 1}, SHIFT(217, 0),
    [204] = {.count = 1}, SHIFT(195, 0),
    [206] = {.count = 1}, SHIFT(196, 0),
    [208] = {.count = 1}, SHIFT(197, 0),
    [210] = {.count = 1}, SHIFT(56, 0),
    [212] = {.count = 1}, REDUCE(sym_pointer_declarator, 2, FRAGILE),
    [214] = {.count = 1}, SHIFT(214, 0),
    [216] = {.count = 1}, SHIFT(82, 0),
    [218] = {.count = 1}, SHIFT(215, 0),
    [220] = {.count = 1}, SHIFT(84, 0),
    [222] = {.count = 1}, SHIFT(85, 0),
    [224] = {.count = 1}, SHIFT(86, 0),
    [226] = {.count = 1}, SHIFT(59, 0),
    [228] = {.count = 1}, SHIFT(60, 0),
    [230] = {.count = 1}, SHIFT(61, 0),
    [232] = {.count = 1}, SHIFT(62, 0),
    [234] = {.count = 1}, SHIFT(212, 0),
    [236] = {.count = 1}, SHIFT(69, 0),
    [238] = {.count = 1}, SHIFT(70, 0),
    [240] = {.count = 1}, SHIFT(71, 0),
    [242] = {.count = 1}, SHIFT(72, 0),
    [244] = {.count = 1}, SHIFT(63, 0),
    [246] = {.count = 1}, SHIFT(64, 0),
    [248] = {.count = 1}, SHIFT(65, 0),
    [250] = {.count = 1}, REDUCE(sym_function_declarator, 3, 0),
    [252] = {.count = 1}, SHIFT(68, 0),
    [254] = {.count = 1}, SHIFT(66, 0),
    [256] = {.count = 1}, REDUCE(sym_function_declarator, 4, 0),
    [258] = {.count = 1}, SHIFT(67, 0),
    [260] = {.count = 1}, REDUCE(aux_sym_function_declarator_repeat1, 2, 0),
    [262] = {.count = 1}, REDUCE(aux_sym_function_declarator_repeat1, 3, 0),
    [264] = {.count = 1}, REDUCE(sym_function_declarator, 5, 0),
    [266] = {.count = 1}, REDUCE(sym_parameter_declaration, 2, 0),
    [268] = {.count = 1}, SHIFT(74, 0),
    [270] = {.count = 1}, SHIFT(75, 0),
    [272] = {.count = 1}, SHIFT(194, 0),
    [274] = {.count = 1}, SHIFT(73, 0),
    [276] = {.count = 1}, SHIFT(81, 0),
    [278] = {.count = 1}, SHIFT(83, 0),
    [280] = {.count = 1}, SHIFT(76, 0),
    [282] = {.count = 1}, SHIFT(77, 0),
    [284] = {.count = 1}, SHIFT(78, 0),
    [286] = {.count = 1}, SHIFT(79, 0),
    [288] = {.count = 1}, SHIFT(80, 0),
    [290] = {.count = 1}, SHIFT(174, 0),
    [292] = {.count = 1}, SHIFT(193, 0),
    [294] = {.count = 1}, SHIFT(88, 0),
    [296] = {.count = 1}, SHIFT(89, 0),
    [298] = {.count = 1}, SHIFT(90, 0),
    [300] = {.count = 1}, REDUCE(sym__expression, 1, 0),
    [302] = {.count = 1}, REDUCE(sym_array_declarator, 3, 0),
    [304] = {.count = 1}, SHIFT(115, 0),
    [306] = {.count = 1}, SHIFT(116, 0),
    [308] = {.count = 1}, SHIFT(188, 0),
    [310] = {.count = 1}, SHIFT(118, 0),
    [312] = {.count = 1}, SHIFT(189, 0),
    [314] = {.count = 1}, SHIFT(120, 0),
    [316] = {.count = 1}, SHIFT(121, 0),
    [318] = {.count = 1}, SHIFT(122, 0),
    [320] = {.count = 1}, SHIFT(123, 0),
    [322] = {.count = 1}, SHIFT(124, 0),
    [324] = {.count = 1}, SHIFT(125, 0),
    [326] = {.count = 1}, SHIFT(126, 0),
    [328] = {.count = 1}, SHIFT(127, 0),
    [330] = {.count = 1}, SHIFT(87, 0),
    [332] = {.count = 1}, REDUCE(sym__expression, 1, FRAGILE),
    [334] = {.count = 1}, REDUCE(sym_pointer_expression, 2, FRAGILE),
    [336] = {.count = 1}, SHIFT(93, 0),
    [338] = {.count = 1}, SHIFT(94, 0),
    [340] = {.count = 1}, SHIFT(95, 0),
    [342] = {.count = 1}, SHIFT(96, 0),
    [344] = {.count = 1}, SHIFT(97, 0),
    [346] = {.count = 1}, SHIFT(98, 0),
    [348] = {.count = 1}, SHIFT(92, 0),
    [350] = {.count = 1}, SHIFT(91, 0),
    [352] = {.count = 1}, REDUCE(sym_math_expression, 3, FRAGILE),
    [354] = {.count = 1}, SHIFT(185, 0),
    [356] = {.count = 1}, SHIFT(108, 0),
    [358] = {.count = 1}, SHIFT(109, 0),
    [360] = {.count = 1}, SHIFT(100, 0),
    [362] = {.count = 1}, SHIFT(186, 0),
    [364] = {.count = 1}, SHIFT(101, 0),
    [366] = {.count = 1}, SHIFT(102, 0),
    [368] = {.count = 1}, SHIFT(117, 0),
    [370] = {.count = 1}, SHIFT(119, 0),
    [372] = {.count = 1}, REDUCE(sym_call_expression, 3, 0),
    [374] = {.count = 1}, SHIFT(99, 0),
    [376] = {.count = 1}, SHIFT(105, 0),
    [378] = {.count = 1}, SHIFT(106, 0),
    [380] = {.count = 1}, SHIFT(104, 0),
    [382] = {.count = 1}, SHIFT(103, 0),
    [384] = {.count = 1}, SHIFT(107, 0),
    [386] = {.count = 1}, SHIFT(110, 0),
    [388] = {.count = 1}, SHIFT(114, 0),
    [390] = {.count = 1}, SHIFT(112, 0),
    [392] = {.count = 1}, SHIFT(111, 0),
    [394] = {.count = 1}, REDUCE(sym_call_expression, 4, 0),
    [396] = {.count = 1}, REDUCE(sym_assignment_expression, 3, FRAGILE),
    [398] = {.count = 1}, SHIFT(113, 0),
    [400] = {.count = 1}, REDUCE(aux_sym_call_expression_repeat1, 2, 0),
    [402] = {.count = 1}, REDUCE(aux_sym_call_expression_repeat1, 3, 0),
    [404] = {.count = 1}, REDUCE(sym_call_expression, 5, 0),
    [406] = {.count = 1}, SHIFT(184, 0),
    [408] = {.count = 1}, SHIFT(161, 0),
    [410] = {.count = 1}, SHIFT(162, 0),
    [412] = {.count = 1}, REDUCE(sym_type_name, 1, 0),
    [414] = {.count = 1}, SHIFT(163, 0),
    [416] = {.count = 1}, SHIFT(182, 0),
    [418] = {.count = 1}, REDUCE(aux_sym_type_name_repeat1, 1, 0),
    [420] = {.count = 1}, SHIFT(181, 0),
    [422] = {.count = 1}, SHIFT(145, 0),
    [424] = {.count = 1}, SHIFT(133, 0),
    [426] = {.count = 1}, SHIFT(180, 0),
    [428] = {.count = 1}, SHIFT(134, 0),
    [430] = {.count = 1}, SHIFT(135, 0),
    [432] = {.count = 1}, SHIFT(179, 0),
    [434] = {.count = 1}, SHIFT(158, 0),
    [436] = {.count = 1}, SHIFT(159, 0),
    [438] = {.count = 1}, SHIFT(150, 0),
    [440] = {.count = 1}, SHIFT(151, 0),
    [442] = {.count = 1}, SHIFT(143, 0),
    [444] = {.count = 1}, SHIFT(144, 0),
    [446] = {.count = 1}, SHIFT(131, 0),
    [448] = {.count = 1}, SHIFT(132, 0),
    [450] = {.count = 3}, REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE), SHIFT(128, 0),
    [454] = {.count = 2}, REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE),
    [457] = {.count = 1}, SHIFT(129, 0),
    [459] = {.count = 1}, SHIFT(130, 0),
    [461] = {.count = 1}, SHIFT(138, 0),
    [463] = {.count = 1}, SHIFT(139, 0),
    [465] = {.count = 1}, SHIFT(137, 0),
    [467] = {.count = 1}, SHIFT(136, 0),
    [469] = {.count = 1}, SHIFT(140, 0),
    [471] = {.count = 1}, SHIFT(141, 0),
    [473] = {.count = 1}, SHIFT(142, 0),
    [475] = {.count = 1}, SHIFT(148, 0),
    [477] = {.count = 1}, SHIFT(146, 0),
    [479] = {.count = 1}, SHIFT(147, 0),
    [481] = {.count = 1}, REDUCE(sym__expression, 3, 0),
    [483] = {.count = 1}, SHIFT(149, 0),
    [485] = {.count = 1}, REDUCE(sym_cast_expression, 4, 0),
    [487] = {.count = 1}, SHIFT(156, 0),
    [489] = {.count = 1}, SHIFT(157, 0),
    [491] = {.count = 1}, SHIFT(152, 0),
    [493] = {.count = 1}, SHIFT(153, 0),
    [495] = {.count = 1}, SHIFT(154, 0),
    [497] = {.count = 1}, SHIFT(155, 0),
    [499] = {.count = 1}, SHIFT(160, 0),
    [501] = {.count = 1}, REDUCE(sym_type_name, 2, 0),
    [503] = {.count = 2}, REDUCE(sym__type_specifier, 1, FRAGILE), SHIFT(128, 0),
    [506] = {.count = 1}, SHIFT(165, 0),
    [508] = {.count = 1}, SHIFT(166, 0),
    [510] = {.count = 1}, REDUCE(sym_type_name, 3, 0),
    [512] = {.count = 1}, REDUCE(sym__abstract_declarator, 1, 0),
    [514] = {.count = 1}, SHIFT(177, 0),
    [516] = {.count = 1}, SHIFT(164, 0),
    [518] = {.count = 1}, REDUCE(sym_abstract_pointer_declarator, 1, FRAGILE),
    [520] = {.count = 1}, REDUCE(sym_abstract_pointer_declarator, 2, FRAGILE),
    [522] = {.count = 1}, SHIFT(172, 0),
    [524] = {.count = 1}, SHIFT(173, 0),
    [526] = {.count = 1}, SHIFT(167, 0),
    [528] = {.count = 1}, SHIFT(168, 0),
    [530] = {.count = 1}, SHIFT(169, 0),
    [532] = {.count = 1}, SHIFT(170, 0),
    [534] = {.count = 1}, REDUCE(sym_abstract_function_declarator, 3, 0),
    [536] = {.count = 1}, SHIFT(171, 0),
    [538] = {.count = 1}, REDUCE(sym_abstract_function_declarator, 4, 0),
    [540] = {.count = 1}, REDUCE(sym_abstract_function_declarator, 5, 0),
    [542] = {.count = 1}, SHIFT(175, 0),
    [544] = {.count = 1}, REDUCE(sym_abstract_array_declarator, 3, 0),
    [546] = {.count = 1}, SHIFT(176, 0),
    [548] = {.count = 1}, REDUCE(sym_abstract_array_declarator, 4, 0),
    [550] = {.count = 1}, SHIFT(178, 0),
    [552] = {.count = 1}, REDUCE(sym__abstract_declarator, 3, 0),
    [554] = {.count = 1}, REDUCE(aux_sym_type_name_repeat1, 2, 0),
    [556] = {.count = 1}, SHIFT(183, 0),
    [558] = {.count = 1}, SHIFT(187, 0),
    [560] = {.count = 1}, SHIFT(191, 0),
    [562] = {.count = 1}, SHIFT(190, 0),
    [564] = {.count = 1}, SHIFT(192, 0),
    [566] = {.count = 1}, REDUCE(sym_array_declarator, 4, 0),
    [568] = {.count = 1}, SHIFT(199, 0),
    [570] = {.count = 1}, SHIFT(200, 0),
    [572] = {.count = 1}, SHIFT(211, 0),
    [574] = {.count = 1}, SHIFT(209, 0),
    [576] = {.count = 1}, SHIFT(198, 0),
    [578] = {.count = 1}, SHIFT(206, 0),
    [580] = {.count = 1}, SHIFT(207, 0),
    [582] = {.count = 1}, SHIFT(201, 0),
    [584] = {.count = 1}, SHIFT(202, 0),
    [586] = {.count = 1}, SHIFT(203, 0),
    [588] = {.count = 1}, SHIFT(204, 0),
    [590] = {.count = 1}, SHIFT(205, 0),
    [592] = {.count = 1}, SHIFT(208, 0),
    [594] = {.count = 1}, SHIFT(210, 0),
    [596] = {.count = 1}, REDUCE(sym__declarator, 3, 0),
    [598] = {.count = 1}, SHIFT(213, 0),
    [600] = {.count = 1}, REDUCE(sym_parameter_declaration, 3, 0),
    [602] = {.count = 1}, SHIFT(216, 0),
    [604] = {.count = 1}, SHIFT(218, 0),
    [606] = {.count = 1}, SHIFT(229, 0),
    [608] = {.count = 1}, SHIFT(230, 0),
    [610] = {.count = 1}, SHIFT(225, 0),
    [612] = {.count = 1}, SHIFT(226, 0),
    [614] = {.count = 1}, SHIFT(227, 0),
    [616] = {.count = 1}, SHIFT(228, 0),
    [618] = {.count = 1}, REDUCE(aux_sym_numeric_type_specifier_repeat1, 2, 0),
    [620] = {.count = 1}, REDUCE(sym_preproc_call, 2, 0),
    [622] = {.count = 1}, SHIFT(234, 0),
    [624] = {.count = 1}, SHIFT(235, 0),
    [626] = {.count = 1}, REDUCE(sym_preproc_define, 3, 0),
    [628] = {.count = 1}, SHIFT(236, 0),
    [630] = {.count = 1}, REDUCE(sym_preproc_define, 4, 0),
    [632] = {.count = 1}, REDUCE(sym_declaration, 2, 0),
    [634] = {.count = 1}, REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0),
    [636] = {.count = 1}, REDUCE(aux_sym_translation_unit_repeat1, 2, 0),
    [638] = {.count = 1}, SHIFT(260, 0),
    [640] = {.count = 1}, SHIFT(262, 0),
    [642] = {.count = 1}, SHIFT(263, 0),
    [644] = {.count = 1}, SHIFT(259, 0),
    [646] = {.count = 1}, SHIFT(261, 0),
    [648] = {.count = 1}, SHIFT(264, 0),
    [650] = {.count = 1}, SHIFT(247, 0),
    [652] = {.count = 1}, SHIFT(248, 0),
    [654] = {.count = 1}, SHIFT(257, 0),
    [656] = {.count = 1}, SHIFT(246, 0),
    [658] = {.count = 1}, SHIFT(254, 0),
    [660] = {.count = 1}, SHIFT(255, 0),
    [662] = {.count = 1}, SHIFT(249, 0),
    [664] = {.count = 1}, SHIFT(250, 0),
    [666] = {.count = 1}, SHIFT(251, 0),
    [668] = {.count = 1}, SHIFT(252, 0),
    [670] = {.count = 1}, SHIFT(253, 0),
    [672] = {.count = 1}, SHIFT(256, 0),
    [674] = {.count = 1}, SHIFT(258, 0),
    [676] = {.count = 1}, REDUCE(sym_function_definition, 3, 0),
    [678] = {.count = 1}, SHIFT(447, 0),
    [680] = {.count = 1}, SHIFT(356, 0),
    [682] = {.count = 1}, SHIFT(357, 0),
    [684] = {.count = 1}, SHIFT(358, 0),
    [686] = {.count = 1}, SHIFT(359, 0),
    [688] = {.count = 1}, SHIFT(360, 0),
    [690] = {.count = 1}, SHIFT(361, 0),
    [692] = {.count = 1}, SHIFT(362, 0),
    [694] = {.count = 1}, SHIFT(363, 0),
    [696] = {.count = 1}, SHIFT(364, 0),
    [698] = {.count = 1}, SHIFT(365, 0),
    [700] = {.count = 1}, SHIFT(366, 0),
    [702] = {.count = 1}, SHIFT(367, 0),
    [704] = {.count = 1}, SHIFT(368, 0),
    [706] = {.count = 1}, SHIFT(369, 0),
    [708] = {.count = 1}, SHIFT(337, 0),
    [710] = {.count = 1}, SHIFT(338, 0),
    [712] = {.count = 1}, SHIFT(339, 0),
    [714] = {.count = 1}, SHIFT(340, 0),
    [716] = {.count = 1}, SHIFT(341, 0),
    [718] = {.count = 1}, REDUCE(sym_declaration, 3, 0),
    [720] = {.count = 1}, SHIFT(265, 0),
    [722] = {.count = 1}, SHIFT(266, 0),
    [724] = {.count = 1}, SHIFT(267, 0),
    [726] = {.count = 1}, SHIFT(268, 0),
    [728] = {.count = 1}, SHIFT(269, 0),
    [730] = {.count = 1}, SHIFT(270, 0),
    [732] = {.count = 1}, SHIFT(271, 0),
    [734] = {.count = 1}, REDUCE(sym__init_declarator, 3, 0),
    [736] = {.count = 1}, REDUCE(sym_initializer, 1, 0),
    [738] = {.count = 1}, SHIFT(335, 0),
    [740] = {.count = 1}, SHIFT(273, 0),
    [742] = {.count = 1}, SHIFT(274, 0),
    [744] = {.count = 1}, SHIFT(275, 0),
    [746] = {.count = 1}, SHIFT(288, 0),
    [748] = {.count = 1}, SHIFT(289, 0),
    [750] = {.count = 1}, SHIFT(290, 0),
    [752] = {.count = 1}, SHIFT(291, 0),
    [754] = {.count = 1}, SHIFT(292, 0),
    [756] = {.count = 1}, SHIFT(293, 0),
    [758] = {.count = 1}, SHIFT(294, 0),
    [760] = {.count = 1}, SHIFT(295, 0),
    [762] = {.count = 1}, SHIFT(296, 0),
    [764] = {.count = 1}, SHIFT(297, 0),
    [766] = {.count = 1}, SHIFT(298, 0),
    [768] = {.count = 1}, SHIFT(299, 0),
    [770] = {.count = 1}, SHIFT(283, 0),
    [772] = {.count = 1}, SHIFT(284, 0),
    [774] = {.count = 1}, SHIFT(272, 0),
    [776] = {.count = 1}, SHIFT(278, 0),
    [778] = {.count = 1}, SHIFT(279, 0),
    [780] = {.count = 1}, SHIFT(277, 0),
    [782] = {.count = 1}, SHIFT(276, 0),
    [784] = {.count = 1}, SHIFT(280, 0),
    [786] = {.count = 1}, SHIFT(281, 0),
    [788] = {.count = 1}, SHIFT(282, 0),
    [790] = {.count = 1}, SHIFT(286, 0),
    [792] = {.count = 1}, SHIFT(285, 0),
    [794] = {.count = 1}, SHIFT(287, 0),
    [796] = {.count = 1}, REDUCE(sym_initializer_list, 1, 0),
    [798] = {.count = 1}, SHIFT(332, 0),
    [800] = {.count = 1}, SHIFT(333, 0),
    [802] = {.count = 1}, SHIFT(331, 0),
    [804] = {.count = 1}, SHIFT(329, 0),
    [806] = {.count = 1}, SHIFT(301, 0),
    [808] = {.count = 1}, SHIFT(302, 0),
    [810] = {.count = 1}, SHIFT(303, 0),
    [812] = {.count = 1}, SHIFT(328, 0),
    [814] = {.count = 1}, SHIFT(321, 0),
    [816] = {.count = 1}, SHIFT(318, 0),
    [818] = {.count = 1}, SHIFT(316, 0),
    [820] = {.count = 1}, SHIFT(311, 0),
    [822] = {.count = 1}, SHIFT(312, 0),
    [824] = {.count = 1}, SHIFT(300, 0),
    [826] = {.count = 1}, SHIFT(306, 0),
    [828] = {.count = 1}, SHIFT(307, 0),
    [830] = {.count = 1}, SHIFT(305, 0),
    [832] = {.count = 1}, SHIFT(304, 0),
    [834] = {.count = 1}, SHIFT(308, 0),
    [836] = {.count = 1}, SHIFT(309, 0),
    [838] = {.count = 1}, SHIFT(310, 0),
    [840] = {.count = 1}, SHIFT(314, 0),
    [842] = {.count = 1}, SHIFT(313, 0),
    [844] = {.count = 1}, SHIFT(315, 0),
    [846] = {.count = 1}, SHIFT(317, 0),
    [848] = {.count = 1}, REDUCE(aux_sym_designation_repeat1, 2, 0),
    [850] = {.count = 1}, REDUCE(aux_sym_designation_repeat1, 3, 0),
    [852] = {.count = 1}, SHIFT(319, 0),
    [854] = {.count = 1}, SHIFT(320, 0),
    [856] = {.count = 1}, REDUCE(aux_sym_designation_repeat1, 4, 0),
    [858] = {.count = 1}, SHIFT(322, 0),
    [860] = {.count = 1}, SHIFT(323, 0),
    [862] = {.count = 1}, REDUCE(sym_initializer, 3, 0),
    [864] = {.count = 1}, SHIFT(324, 0),
    [866] = {.count = 1}, SHIFT(325, 0),
    [868] = {.count = 1}, SHIFT(326, 0),
    [870] = {.count = 1}, REDUCE(sym_initializer_list, 3, 0),
    [872] = {.count = 1}, SHIFT(327, 0),
    [874] = {.count = 1}, REDUCE(sym_initializer, 4, 0),
    [876] = {.count = 1}, REDUCE(sym_initializer_list, 4, 0),
    [878] = {.count = 1}, REDUCE(sym_designation, 2, 0),
    [880] = {.count = 1}, SHIFT(330, 0),
    [882] = {.count = 1}, REDUCE(sym_initializer_list, 2, 0),
    [884] = {.count = 1}, SHIFT(334, 0),
    [886] = {.count = 1}, SHIFT(336, 0),
    [888] = {.count = 1}, SHIFT(355, 0),
    [890] = {.count = 1}, REDUCE(aux_sym_declaration_repeat1, 2, 0),
    [892] = {.count = 1}, SHIFT(343, 0),
    [894] = {.count = 1}, SHIFT(344, 0),
    [896] = {.count = 1}, SHIFT(353, 0),
    [898] = {.count = 1}, SHIFT(342, 0),
    [900] = {.count = 1}, SHIFT(350, 0),
    [902] = {.count = 1}, SHIFT(351, 0),
    [904] = {.count = 1}, SHIFT(345, 0),
    [906] = {.count = 1}, SHIFT(346, 0),
    [908] = {.count = 1}, SHIFT(347, 0),
    [910] = {.count = 1}, SHIFT(348, 0),
    [912] = {.count = 1}, SHIFT(349, 0),
    [914] = {.count = 1}, SHIFT(352, 0),
    [916] = {.count = 1}, SHIFT(354, 0),
    [918] = {.count = 1}, REDUCE(aux_sym_declaration_repeat1, 3, 0),
    [920] = {.count = 1}, SHIFT(442, 0),
    [922] = {.count = 1}, SHIFT(437, 0),
    [924] = {.count = 1}, SHIFT(438, 0),
    [926] = {.count = 1}, SHIFT(434, 0),
    [928] = {.count = 1}, SHIFT(435, 0),
    [930] = {.count = 1}, REDUCE(aux_sym_compound_statement_repeat1, 1, 0),
    [932] = {.count = 1}, REDUCE(sym__statement, 1, 0),
    [934] = {.count = 1}, SHIFT(436, 0),
    [936] = {.count = 1}, SHIFT(388, 0),
    [938] = {.count = 1}, SHIFT(389, 0),
    [940] = {.count = 1}, SHIFT(390, 0),
    [942] = {.count = 1}, SHIFT(391, 0),
    [944] = {.count = 1}, SHIFT(433, 0),
    [946] = {.count = 1}, SHIFT(432, 0),
    [948] = {.count = 1}, SHIFT(428, 0),
    [950] = {.count = 1}, SHIFT(429, 0),
    [952] = {.count = 1}, SHIFT(430, 0),
    [954] = {.count = 1}, REDUCE(sym_compound_statement, 2, 0),
    [956] = {.count = 1}, SHIFT(423, 0),
    [958] = {.count = 1}, SHIFT(424, 0),
    [960] = {.count = 1}, SHIFT(422, 0),
    [962] = {.count = 1}, SHIFT(378, 0),
    [964] = {.count = 1}, SHIFT(370, 0),
    [966] = {.count = 3}, REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE), SHIFT(18, 0),
    [970] = {.count = 1}, SHIFT(371, 0),
    [972] = {.count = 1}, SHIFT(372, 0),
    [974] = {.count = 1}, SHIFT(373, 0),
    [976] = {.count = 1}, SHIFT(374, 0),
    [978] = {.count = 1}, SHIFT(375, 0),
    [980] = {.count = 1}, SHIFT(417, 0),
    [982] = {.count = 1}, SHIFT(412, 0),
    [984] = {.count = 1}, SHIFT(413, 0),
    [986] = {.count = 1}, SHIFT(376, 0),
    [988] = {.count = 1}, SHIFT(377, 0),
    [990] = {.count = 1}, SHIFT(405, 0),
    [992] = {.count = 1}, SHIFT(404, 0),
    [994] = {.count = 1}, SHIFT(387, 0),
    [996] = {.count = 1}, SHIFT(379, 0),
    [998] = {.count = 1}, SHIFT(380, 0),
    [1000] = {.count = 1}, SHIFT(382, 0),
    [1002] = {.count = 1}, SHIFT(383, 0),
    [1004] = {.count = 1}, SHIFT(381, 0),
    [1006] = {.count = 1}, REDUCE(sym_for_statement, 6, 0),
    [1008] = {.count = 1}, SHIFT(385, 0),
    [1010] = {.count = 1}, SHIFT(384, 0),
    [1012] = {.count = 1}, REDUCE(sym_for_statement, 7, 0),
    [1014] = {.count = 1}, SHIFT(386, 0),
    [1016] = {.count = 1}, REDUCE(sym_for_statement, 8, 0),
    [1018] = {.count = 1}, SHIFT(400, 0),
    [1020] = {.count = 1}, SHIFT(399, 0),
    [1022] = {.count = 1}, SHIFT(394, 0),
    [1024] = {.count = 1}, SHIFT(395, 0),
    [1026] = {.count = 1}, SHIFT(393, 0),
    [1028] = {.count = 1}, SHIFT(392, 0),
    [1030] = {.count = 1}, SHIFT(396, 0),
    [1032] = {.count = 1}, SHIFT(397, 0),
    [1034] = {.count = 1}, SHIFT(398, 0),
    [1036] = {.count = 1}, SHIFT(401, 0),
    [1038] = {.count = 1}, SHIFT(402, 0),
    [1040] = {.count = 1}, SHIFT(403, 0),
    [1042] = {.count = 1}, REDUCE(sym_for_statement, 9, 0),
    [1044] = {.count = 1}, SHIFT(406, 0),
    [1046] = {.count = 1}, SHIFT(407, 0),
    [1048] = {.count = 1}, SHIFT(408, 0),
    [1050] = {.count = 1}, SHIFT(409, 0),
    [1052] = {.count = 1}, SHIFT(410, 0),
    [1054] = {.count = 1}, SHIFT(411, 0),
    [1056] = {.count = 1}, REDUCE(sym_for_statement, 10, 0),
    [1058] = {.count = 1}, SHIFT(414, 0),
    [1060] = {.count = 1}, SHIFT(415, 0),
    [1062] = {.count = 1}, SHIFT(416, 0),
    [1064] = {.count = 1}, REDUCE(sym_declaration, 4, 0),
    [1066] = {.count = 1}, SHIFT(418, 0),
    [1068] = {.count = 1}, SHIFT(419, 0),
    [1070] = {.count = 1}, SHIFT(420, 0),
    [1072] = {.count = 1}, SHIFT(421, 0),
    [1074] = {.count = 1}, REDUCE(sym_declaration, 5, 0),
    [1076] = {.count = 1}, SHIFT(426, 0),
    [1078] = {.count = 1}, SHIFT(425, 0),
    [1080] = {.count = 1}, SHIFT(427, 0),
    [1082] = {.count = 1}, SHIFT(431, 0),
    [1084] = {.count = 1}, REDUCE(sym_compound_statement, 3, 0),
    [1086] = {.count = 1}, REDUCE(aux_sym_compound_statement_repeat1, 2, 0),
    [1088] = {.count = 1}, REDUCE(sym_expression_statement, 2, 0),
    [1090] = {.count = 1}, SHIFT(439, 0),
    [1092] = {.count = 1}, SHIFT(440, 0),
    [1094] = {.count = 1}, SHIFT(441, 0),
    [1096] = {.count = 1}, SHIFT(443, 0),
    [1098] = {.count = 1}, SHIFT(444, 0),
    [1100] = {.count = 1}, SHIFT(445, 0),
    [1102] = {.count = 1}, SHIFT(446, 0),
    [1104] = {.count = 1}, SHIFT(449, 0),
    [1106] = {.count = 1}, SHIFT(450, 0),
    [1108] = {.count = 1}, SHIFT(452, 0),
    [1110] = {.count = 1}, SHIFT(451, 0),
    [1112] = {.count = 1}, REDUCE(sym_function_definition, 4, 0),
    [1114] = {.count = 1}, SHIFT(453, 0),
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
