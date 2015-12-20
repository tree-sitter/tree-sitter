#include "tree_sitter/parser.h"

#define STATE_COUNT 452
#define SYMBOL_COUNT 82

enum {
    sym_translation_unit = ts_builtin_sym_start,
    sym_preproc_define,
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

static TSTree *ts_lex(TSLexer *lexer, TSStateId lex_state) {
    START_LEXER();
    switch (lex_state) {
        case 1:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(1);
            if (lookahead == '#')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(16);
            if (lookahead == 'c')
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(25);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(35);
            if (lookahead == 's')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            LEX_ERROR();
        case 2:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 3:
            if (lookahead == 'd')
                ADVANCE(4);
            LEX_ERROR();
        case 4:
            if (lookahead == 'e')
                ADVANCE(5);
            LEX_ERROR();
        case 5:
            if (lookahead == 'f')
                ADVANCE(6);
            LEX_ERROR();
        case 6:
            if (lookahead == 'i')
                ADVANCE(7);
            LEX_ERROR();
        case 7:
            if (lookahead == 'n')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if (lookahead == 'e')
                ADVANCE(9);
            LEX_ERROR();
        case 9:
            ACCEPT_TOKEN(anon_sym_POUNDdefine);
        case 10:
            if (lookahead == '*')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(14);
            LEX_ERROR();
        case 11:
            if (lookahead == '*')
                ADVANCE(12);
            if (!((lookahead == 0) ||
                (lookahead == '*')))
                ADVANCE(11);
            LEX_ERROR();
        case 12:
            if (lookahead == '/')
                ADVANCE(13);
            if (!((lookahead == 0) ||
                (lookahead == '/')))
                ADVANCE(11);
            LEX_ERROR();
        case 13:
            ACCEPT_TOKEN(sym_comment);
        case 14:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(14);
            ACCEPT_TOKEN(sym_comment);
        case 15:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 16:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'u')
                ADVANCE(17);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 17:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(18);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 18:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(19);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 19:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_auto);
        case 20:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(21);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 21:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(22);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 22:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(23);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 23:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(24);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 24:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_const);
        case 25:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'w') ||
                (lookahead == 'y') ||
                (lookahead == 'z'))
                ADVANCE(15);
            if (lookahead == 'x')
                ADVANCE(26);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 26:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(27);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 27:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(28);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 28:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(29);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 29:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(30);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 30:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_extern);
        case 31:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(32);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 32:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(33);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 33:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'g')
                ADVANCE(34);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 34:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_long);
        case 35:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(36);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 36:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'g')
                ADVANCE(37);
            if (lookahead == 's')
                ADVANCE(43);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 37:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(38);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 38:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(39);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 39:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(40);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 40:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(41);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 41:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(42);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 42:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_register);
        case 43:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(44);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 44:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(45);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 45:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(46);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 46:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(47);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(48);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 48:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_restrict);
        case 49:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'h')
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(59);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(51);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(52);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(53);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 53:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_short);
        case 54:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'g')
                ADVANCE(55);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(56);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(57);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'd')
                ADVANCE(58);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 58:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_signed);
        case 59:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(60);
            if (lookahead == 'r')
                ADVANCE(64);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(61);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(62);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 62:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(63);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 63:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_static);
        case 64:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'u')
                ADVANCE(65);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 65:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(66);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(67);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 67:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_struct);
        case 68:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'x') ||
                (lookahead == 'z'))
                ADVANCE(15);
            if (lookahead == 'y')
                ADVANCE(69);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'p')
                ADVANCE(70);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(71);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 71:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'd')
                ADVANCE(72);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 72:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(73);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 73:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(74);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 74:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_typedef);
        case 75:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(76);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 76:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(77);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 77:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(78);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 78:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'g')
                ADVANCE(79);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 79:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(80);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 80:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(81);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 81:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'd')
                ADVANCE(82);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 82:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_unsigned);
        case 83:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(84);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 84:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(85);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 85:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(86);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 86:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(87);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 87:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(88);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 88:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(89);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 89:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(90);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 90:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_volatile);
        case 91:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(91);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 92:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(92);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 's')
                ADVANCE(93);
            if (lookahead == 'u')
                ADVANCE(75);
            LEX_ERROR();
        case 93:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'h')
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(54);
            if (lookahead == 't')
                ADVANCE(94);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(64);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 95:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(95);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(16);
            if (lookahead == 'c')
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(25);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(35);
            if (lookahead == 's')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            LEX_ERROR();
        case 96:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(96);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 97:
            ACCEPT_TOKEN(anon_sym_LPAREN);
        case 98:
            ACCEPT_TOKEN(anon_sym_STAR);
        case 99:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(99);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 100:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(100);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            LEX_ERROR();
        case 101:
            ACCEPT_TOKEN(anon_sym_SEMI);
        case 102:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(102);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 's')
                ADVANCE(103);
            if (lookahead == 'u')
                ADVANCE(75);
            LEX_ERROR();
        case 103:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'g') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'h')
                ADVANCE(50);
            if (lookahead == 'i')
                ADVANCE(54);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 104:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(104);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '{')
                ADVANCE(105);
            LEX_ERROR();
        case 105:
            ACCEPT_TOKEN(anon_sym_LBRACE);
        case 106:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(106);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 107:
            ACCEPT_TOKEN(anon_sym_RPAREN);
        case 108:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(108);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 109:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(109);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 's')
                ADVANCE(93);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 110:
            ACCEPT_TOKEN(anon_sym_RBRACE);
        case 111:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(111);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '{')
                ADVANCE(105);
            LEX_ERROR();
        case 112:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(112);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 113:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(113);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'r') ||
                (lookahead == 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(114);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 's')
                ADVANCE(93);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 114:
            ACCEPT_TOKEN(anon_sym_LBRACK);
        case 115:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(115);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == ']')
                ADVANCE(124);
            LEX_ERROR();
        case 116:
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '\\')
                ADVANCE(118);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(116);
            LEX_ERROR();
        case 117:
            ACCEPT_TOKEN(sym_string);
        case 118:
            if (lookahead == '\"')
                ADVANCE(119);
            if (lookahead == '\\')
                ADVANCE(118);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(116);
            LEX_ERROR();
        case 119:
            if (lookahead == '\"')
                ADVANCE(117);
            if (lookahead == '\\')
                ADVANCE(118);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(116);
            ACCEPT_TOKEN(sym_string);
        case 120:
            ACCEPT_TOKEN(anon_sym_AMP);
        case 121:
            if (lookahead == '.')
                ADVANCE(122);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            ACCEPT_TOKEN(sym_number);
        case 122:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(123);
            LEX_ERROR();
        case 123:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(123);
            ACCEPT_TOKEN(sym_number);
        case 124:
            ACCEPT_TOKEN(anon_sym_RBRACK);
        case 125:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(125);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(16);
            if (lookahead == 'c')
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(25);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(35);
            if (lookahead == 's')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            LEX_ERROR();
        case 126:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(126);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 127:
            ACCEPT_TOKEN(anon_sym_COMMA);
        case 128:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(128);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(114);
            LEX_ERROR();
        case 129:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(129);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(131);
            if (lookahead == ']')
                ADVANCE(124);
            LEX_ERROR();
        case 130:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 131:
            ACCEPT_TOKEN(anon_sym_EQ);
        case 132:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(132);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                (lookahead == 't') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(20);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(133);
            if (lookahead == 's')
                ADVANCE(93);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            LEX_ERROR();
        case 133:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(134);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 134:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(43);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 135:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(135);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 137:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(137);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(131);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
            if (lookahead == '/')
                ADVANCE(10);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'a') ||
                (lookahead == 'b') ||
                ('d' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                (lookahead == 't') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'c')
                ADVANCE(20);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(133);
            if (lookahead == 's')
                ADVANCE(93);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            LEX_ERROR();
        case 140:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(140);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(131);
            LEX_ERROR();
        case 141:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(141);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(114);
            LEX_ERROR();
        case 142:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(142);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 143:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(143);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(114);
            LEX_ERROR();
        case 144:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(145);
            if (lookahead == '\n')
                ADVANCE(153);
            if (lookahead == '/')
                ADVANCE(146);
            if (lookahead == '\\')
                ADVANCE(151);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(152);
            LEX_ERROR();
        case 145:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(145);
            if (lookahead == '/')
                ADVANCE(146);
            if (lookahead == '\\')
                ADVANCE(151);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(152);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 146:
            if (lookahead == '*')
                ADVANCE(147);
            if (lookahead == '/')
                ADVANCE(150);
            if (lookahead == '\\')
                ADVANCE(151);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(152);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 147:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '*')
                ADVANCE(148);
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(147);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 148:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(13);
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(147);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 149:
            if (lookahead == '\n')
                ADVANCE(147);
            if (lookahead == '*')
                ADVANCE(148);
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(147);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 150:
            if (lookahead == '\\')
                ADVANCE(150);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(150);
            ACCEPT_TOKEN(sym_comment);
        case 151:
            if (lookahead == '\n')
                ADVANCE(152);
            if (lookahead == '\\')
                ADVANCE(151);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(152);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 152:
            if (lookahead == '\\')
                ADVANCE(151);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(152);
            ACCEPT_FRAGILE_TOKEN(sym_preproc_arg);
        case 153:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_LF);
        case 154:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(154);
            if (lookahead == '\n')
                ADVANCE(153);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 155:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(155);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            LEX_ERROR();
        case 156:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(156);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(131);
            if (lookahead == '[')
                ADVANCE(114);
            if (lookahead == '{')
                ADVANCE(105);
            LEX_ERROR();
        case 157:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(157);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(16);
            if (lookahead == 'c')
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(35);
            if (lookahead == 's')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            if (lookahead == '{')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 158:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(159);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 159:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(160);
            ACCEPT_FRAGILE_TOKEN(sym_identifier);
        case 160:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_for);
        case 161:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(161);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '{')
                ADVANCE(105);
            LEX_ERROR();
        case 162:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(162);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(131);
            LEX_ERROR();
        case 163:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(163);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '.')
                ADVANCE(164);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(114);
            if (lookahead == '{')
                ADVANCE(105);
            LEX_ERROR();
        case 164:
            ACCEPT_TOKEN(anon_sym_DOT);
        case 165:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(165);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 166:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(166);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(131);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 167:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(167);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(131);
            LEX_ERROR();
        case 168:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(168);
            if (lookahead == '.')
                ADVANCE(164);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(131);
            if (lookahead == '[')
                ADVANCE(114);
            LEX_ERROR();
        case 169:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(169);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '.')
                ADVANCE(164);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(114);
            if (lookahead == '{')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 170:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(170);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(131);
            if (lookahead == '[')
                ADVANCE(114);
            LEX_ERROR();
        case 171:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(171);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(131);
            LEX_ERROR();
        case 172:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(172);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 173:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(173);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 174:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(174);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(130);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(131);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 175:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(175);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (lookahead == ';')
                ADVANCE(101);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(16);
            if (lookahead == 'c')
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(25);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(35);
            if (lookahead == 's')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            LEX_ERROR();
        case 176:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(176);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (lookahead == ';')
                ADVANCE(101);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            LEX_ERROR();
        case 177:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(177);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == '{')
                ADVANCE(105);
            LEX_ERROR();
        case 178:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(178);
            if (lookahead == '\n')
                ADVANCE(153);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '#')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '.')
                ADVANCE(164);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(131);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(114);
            if (lookahead == ']')
                ADVANCE(124);
            if (lookahead == 'a')
                ADVANCE(16);
            if (lookahead == 'c')
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(158);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(35);
            if (lookahead == 's')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            if (lookahead == '{')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(183);
            if (lookahead == '\n')
                ADVANCE(184);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '#')
                ADVANCE(3);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '+')
                ADVANCE(130);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '.')
                ADVANCE(169);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(131);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('g' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'q') ||
                ('w' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == '[')
                ADVANCE(114);
            if (lookahead == ']')
                ADVANCE(124);
            if (lookahead == 'a')
                ADVANCE(16);
            if (lookahead == 'c')
                ADVANCE(20);
            if (lookahead == 'e')
                ADVANCE(25);
            if (lookahead == 'f')
                ADVANCE(163);
            if (lookahead == 'l')
                ADVANCE(31);
            if (lookahead == 'r')
                ADVANCE(35);
            if (lookahead == 's')
                ADVANCE(49);
            if (lookahead == 't')
                ADVANCE(68);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            if (lookahead == '{')
                ADVANCE(105);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 91,
    [2] = 1,
    [3] = 92,
    [4] = 95,
    [5] = 96,
    [6] = 96,
    [7] = 91,
    [8] = 92,
    [9] = 99,
    [10] = 100,
    [11] = 99,
    [12] = 95,
    [13] = 102,
    [14] = 104,
    [15] = 95,
    [16] = 96,
    [17] = 92,
    [18] = 106,
    [19] = 106,
    [20] = 99,
    [21] = 104,
    [22] = 108,
    [23] = 92,
    [24] = 106,
    [25] = 106,
    [26] = 109,
    [27] = 111,
    [28] = 109,
    [29] = 96,
    [30] = 96,
    [31] = 109,
    [32] = 99,
    [33] = 112,
    [34] = 104,
    [35] = 106,
    [36] = 96,
    [37] = 92,
    [38] = 106,
    [39] = 96,
    [40] = 109,
    [41] = 111,
    [42] = 109,
    [43] = 112,
    [44] = 96,
    [45] = 96,
    [46] = 112,
    [47] = 96,
    [48] = 106,
    [49] = 96,
    [50] = 112,
    [51] = 113,
    [52] = 113,
    [53] = 96,
    [54] = 96,
    [55] = 113,
    [56] = 115,
    [57] = 125,
    [58] = 92,
    [59] = 96,
    [60] = 126,
    [61] = 113,
    [62] = 106,
    [63] = 95,
    [64] = 113,
    [65] = 126,
    [66] = 106,
    [67] = 113,
    [68] = 128,
    [69] = 128,
    [70] = 96,
    [71] = 96,
    [72] = 128,
    [73] = 115,
    [74] = 125,
    [75] = 126,
    [76] = 128,
    [77] = 106,
    [78] = 128,
    [79] = 128,
    [80] = 129,
    [81] = 129,
    [82] = 128,
    [83] = 132,
    [84] = 135,
    [85] = 129,
    [86] = 129,
    [87] = 136,
    [88] = 135,
    [89] = 135,
    [90] = 129,
    [91] = 129,
    [92] = 137,
    [93] = 137,
    [94] = 132,
    [95] = 129,
    [96] = 135,
    [97] = 137,
    [98] = 137,
    [99] = 136,
    [100] = 135,
    [101] = 135,
    [102] = 137,
    [103] = 137,
    [104] = 137,
    [105] = 137,
    [106] = 106,
    [107] = 135,
    [108] = 135,
    [109] = 137,
    [110] = 137,
    [111] = 137,
    [112] = 106,
    [113] = 137,
    [114] = 138,
    [115] = 138,
    [116] = 106,
    [117] = 139,
    [118] = 140,
    [119] = 140,
    [120] = 99,
    [121] = 92,
    [122] = 104,
    [123] = 132,
    [124] = 135,
    [125] = 139,
    [126] = 140,
    [127] = 92,
    [128] = 106,
    [129] = 138,
    [130] = 140,
    [131] = 140,
    [132] = 136,
    [133] = 135,
    [134] = 135,
    [135] = 140,
    [136] = 140,
    [137] = 137,
    [138] = 140,
    [139] = 106,
    [140] = 140,
    [141] = 140,
    [142] = 106,
    [143] = 140,
    [144] = 135,
    [145] = 140,
    [146] = 140,
    [147] = 135,
    [148] = 140,
    [149] = 109,
    [150] = 111,
    [151] = 109,
    [152] = 112,
    [153] = 138,
    [154] = 138,
    [155] = 112,
    [156] = 138,
    [157] = 138,
    [158] = 138,
    [159] = 141,
    [160] = 141,
    [161] = 142,
    [162] = 143,
    [163] = 141,
    [164] = 115,
    [165] = 125,
    [166] = 126,
    [167] = 141,
    [168] = 106,
    [169] = 141,
    [170] = 141,
    [171] = 129,
    [172] = 141,
    [173] = 135,
    [174] = 141,
    [175] = 129,
    [176] = 141,
    [177] = 141,
    [178] = 138,
    [179] = 137,
    [180] = 92,
    [181] = 135,
    [182] = 137,
    [183] = 141,
    [184] = 106,
    [185] = 129,
    [186] = 129,
    [187] = 106,
    [188] = 140,
    [189] = 129,
    [190] = 135,
    [191] = 129,
    [192] = 128,
    [193] = 141,
    [194] = 141,
    [195] = 96,
    [196] = 96,
    [197] = 141,
    [198] = 115,
    [199] = 125,
    [200] = 126,
    [201] = 141,
    [202] = 106,
    [203] = 141,
    [204] = 141,
    [205] = 129,
    [206] = 141,
    [207] = 141,
    [208] = 141,
    [209] = 141,
    [210] = 128,
    [211] = 96,
    [212] = 128,
    [213] = 129,
    [214] = 113,
    [215] = 113,
    [216] = 141,
    [217] = 113,
    [218] = 112,
    [219] = 106,
    [220] = 106,
    [221] = 96,
    [222] = 109,
    [223] = 111,
    [224] = 109,
    [225] = 112,
    [226] = 96,
    [227] = 96,
    [228] = 112,
    [229] = 96,
    [230] = 99,
    [231] = 144,
    [232] = 1,
    [233] = 154,
    [234] = 1,
    [235] = 1,
    [236] = 96,
    [237] = 92,
    [238] = 91,
    [239] = 155,
    [240] = 156,
    [241] = 156,
    [242] = 96,
    [243] = 96,
    [244] = 156,
    [245] = 115,
    [246] = 125,
    [247] = 126,
    [248] = 156,
    [249] = 106,
    [250] = 156,
    [251] = 156,
    [252] = 129,
    [253] = 156,
    [254] = 156,
    [255] = 141,
    [256] = 156,
    [257] = 1,
    [258] = 100,
    [259] = 157,
    [260] = 96,
    [261] = 1,
    [262] = 161,
    [263] = 155,
    [264] = 162,
    [265] = 162,
    [266] = 163,
    [267] = 132,
    [268] = 135,
    [269] = 162,
    [270] = 162,
    [271] = 136,
    [272] = 135,
    [273] = 135,
    [274] = 162,
    [275] = 162,
    [276] = 137,
    [277] = 162,
    [278] = 106,
    [279] = 162,
    [280] = 162,
    [281] = 106,
    [282] = 140,
    [283] = 162,
    [284] = 135,
    [285] = 162,
    [286] = 165,
    [287] = 165,
    [288] = 161,
    [289] = 166,
    [290] = 166,
    [291] = 167,
    [292] = 163,
    [293] = 135,
    [294] = 99,
    [295] = 132,
    [296] = 135,
    [297] = 166,
    [298] = 166,
    [299] = 136,
    [300] = 135,
    [301] = 135,
    [302] = 166,
    [303] = 166,
    [304] = 137,
    [305] = 166,
    [306] = 106,
    [307] = 166,
    [308] = 166,
    [309] = 106,
    [310] = 140,
    [311] = 166,
    [312] = 135,
    [313] = 166,
    [314] = 168,
    [315] = 167,
    [316] = 129,
    [317] = 168,
    [318] = 167,
    [319] = 165,
    [320] = 165,
    [321] = 169,
    [322] = 165,
    [323] = 161,
    [324] = 165,
    [325] = 165,
    [326] = 161,
    [327] = 135,
    [328] = 166,
    [329] = 165,
    [330] = 155,
    [331] = 169,
    [332] = 155,
    [333] = 135,
    [334] = 162,
    [335] = 155,
    [336] = 170,
    [337] = 170,
    [338] = 96,
    [339] = 96,
    [340] = 170,
    [341] = 115,
    [342] = 125,
    [343] = 126,
    [344] = 170,
    [345] = 106,
    [346] = 170,
    [347] = 170,
    [348] = 129,
    [349] = 170,
    [350] = 170,
    [351] = 141,
    [352] = 170,
    [353] = 100,
    [354] = 92,
    [355] = 96,
    [356] = 157,
    [357] = 157,
    [358] = 171,
    [359] = 171,
    [360] = 112,
    [361] = 172,
    [362] = 157,
    [363] = 1,
    [364] = 132,
    [365] = 135,
    [366] = 173,
    [367] = 174,
    [368] = 175,
    [369] = 92,
    [370] = 96,
    [371] = 176,
    [372] = 171,
    [373] = 100,
    [374] = 171,
    [375] = 136,
    [376] = 171,
    [377] = 137,
    [378] = 177,
    [379] = 157,
    [380] = 106,
    [381] = 177,
    [382] = 157,
    [383] = 177,
    [384] = 157,
    [385] = 136,
    [386] = 135,
    [387] = 136,
    [388] = 135,
    [389] = 135,
    [390] = 171,
    [391] = 171,
    [392] = 137,
    [393] = 171,
    [394] = 106,
    [395] = 171,
    [396] = 171,
    [397] = 171,
    [398] = 137,
    [399] = 106,
    [400] = 177,
    [401] = 157,
    [402] = 176,
    [403] = 176,
    [404] = 171,
    [405] = 136,
    [406] = 137,
    [407] = 106,
    [408] = 177,
    [409] = 157,
    [410] = 155,
    [411] = 170,
    [412] = 100,
    [413] = 176,
    [414] = 176,
    [415] = 96,
    [416] = 155,
    [417] = 170,
    [418] = 100,
    [419] = 176,
    [420] = 171,
    [421] = 106,
    [422] = 140,
    [423] = 171,
    [424] = 135,
    [425] = 171,
    [426] = 112,
    [427] = 172,
    [428] = 157,
    [429] = 157,
    [430] = 157,
    [431] = 1,
    [432] = 112,
    [433] = 100,
    [434] = 157,
    [435] = 155,
    [436] = 170,
    [437] = 100,
    [438] = 157,
    [439] = 157,
    [440] = 96,
    [441] = 155,
    [442] = 170,
    [443] = 100,
    [444] = 157,
    [445] = 1,
    [446] = 96,
    [447] = 155,
    [448] = 156,
    [449] = 1,
    [450] = 100,
    [451] = 1,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction *ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_translation_unit] = ACTIONS(SHIFT(1, 0)),
        [sym_preproc_define] = ACTIONS(SHIFT(2, 0)),
        [sym_function_definition] = ACTIONS(SHIFT(2, 0)),
        [sym_declaration_specifiers] = ACTIONS(SHIFT(3, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(5, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_declaration] = ACTIONS(SHIFT(2, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(6, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(7, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9, 0)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(10, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_translation_unit, 0, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(SHIFT(11, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(SHIFT(16, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [1] = {
        [ts_builtin_sym_end] = ACTIONS(ACCEPT_INPUT()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [2] = {
        [sym_preproc_define] = ACTIONS(SHIFT(2, 0)),
        [sym_function_definition] = ACTIONS(SHIFT(2, 0)),
        [sym_declaration_specifiers] = ACTIONS(SHIFT(3, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(5, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_declaration] = ACTIONS(SHIFT(2, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(6, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(238, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9, 0)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(10, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 1, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(SHIFT(11, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(SHIFT(16, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [3] = {
        [sym__type_specifier] = ACTIONS(SHIFT(446, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(6, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(14, 0)),
        [sym_identifier] = ACTIONS(SHIFT(16, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [4] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(237, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [5] = {
        [sym__init_declarator] = ACTIONS(SHIFT(239, 0)),
        [sym__declarator] = ACTIONS(SHIFT(240, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(241, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(241, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(241, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(242, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(243, 0)),
        [sym_identifier] = ACTIONS(SHIFT(241, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [7] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_translation_unit, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [sym_identifier] = ACTIONS(SHIFT(236, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(235, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [sym_identifier] = ACTIONS(SHIFT(231, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(230, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_numeric_type_specifier_repeat1, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(222, 0)),
        [sym_identifier] = ACTIONS(SHIFT(223, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [15] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE), SHIFT(17, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [sym__type_specifier] = ACTIONS(SHIFT(18, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(19, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(19, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(19, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(20, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(21, 0)),
        [sym_identifier] = ACTIONS(SHIFT(22, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(221, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [sym_identifier] = ACTIONS(SHIFT(220, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(26, 0)),
        [sym_identifier] = ACTIONS(SHIFT(27, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(23, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [sym__type_specifier] = ACTIONS(SHIFT(24, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(19, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(19, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(19, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(20, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(21, 0)),
        [sym_identifier] = ACTIONS(SHIFT(22, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(25, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(218, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(219, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(28, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(33, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(35, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [sym__declarator] = ACTIONS(SHIFT(51, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(52, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(52, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(52, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(53, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(54, 0)),
        [sym_identifier] = ACTIONS(SHIFT(52, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(50, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 1, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [sym_identifier] = ACTIONS(SHIFT(49, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [33] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(48, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [34] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(40, 0)),
        [sym_identifier] = ACTIONS(SHIFT(41, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [35] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [36] = {
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE), SHIFT(37, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [37] = {
        [sym__type_specifier] = ACTIONS(SHIFT(38, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(19, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(19, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(19, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(20, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(21, 0)),
        [sym_identifier] = ACTIONS(SHIFT(22, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [38] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(39, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [39] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [40] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(46, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(47, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [41] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(42, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [42] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(43, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(44, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [43] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(45, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [44] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [45] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [46] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(44, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [47] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [48] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [49] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [50] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [51] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(56, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(57, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_declaration, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [52] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [53] = {
        [sym__declarator] = ACTIONS(SHIFT(216, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(194, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196, 0)),
        [sym_identifier] = ACTIONS(SHIFT(194, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [54] = {
        [sym__declarator] = ACTIONS(SHIFT(55, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(52, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(52, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(52, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(53, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(54, 0)),
        [sym_identifier] = ACTIONS(SHIFT(52, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [55] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(56, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(57, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [56] = {
        [sym__expression] = ACTIONS(SHIFT(213, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(214, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [57] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(59, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(60, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(61, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [58] = {
        [sym__type_specifier] = ACTIONS(SHIFT(211, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [59] = {
        [sym__declarator] = ACTIONS(SHIFT(68, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(69, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(69, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(69, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(71, 0)),
        [sym_identifier] = ACTIONS(SHIFT(69, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [60] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(62, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(64, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [61] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [62] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(67, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [63] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(59, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(65, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [64] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [65] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(66, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_function_declarator_repeat1, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [66] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_function_declarator_repeat1, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [67] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [68] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(73, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [69] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [70] = {
        [sym__declarator] = ACTIONS(SHIFT(193, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(194, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196, 0)),
        [sym_identifier] = ACTIONS(SHIFT(194, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [71] = {
        [sym__declarator] = ACTIONS(SHIFT(72, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(69, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(69, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(69, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(71, 0)),
        [sym_identifier] = ACTIONS(SHIFT(69, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [72] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(73, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
        [sym__expression] = ACTIONS(SHIFT(80, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(82, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(59, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(75, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(76, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [75] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(77, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(78, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(79, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [80] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(192, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [82] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_type_name] = ACTIONS(SHIFT(187, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117, 0)),
        [sym__expression] = ACTIONS(SHIFT(188, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(115, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120, 0)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(122, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(126, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [sym__expression] = ACTIONS(SHIFT(86, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [sym__expression] = ACTIONS(SHIFT(92, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(95, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [sym__expression] = ACTIONS(SHIFT(91, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [sym__expression] = ACTIONS(SHIFT(90, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(184, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(185, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_type_name] = ACTIONS(SHIFT(116, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117, 0)),
        [sym__expression] = ACTIONS(SHIFT(118, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(115, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120, 0)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(122, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(126, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [sym__expression] = ACTIONS(SHIFT(98, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [99] = {
        [sym__expression] = ACTIONS(SHIFT(104, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(105, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [sym__expression] = ACTIONS(SHIFT(103, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [sym__expression] = ACTIONS(SHIFT(102, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [103] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(106, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(109, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [106] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(113, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [107] = {
        [sym__expression] = ACTIONS(SHIFT(111, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [108] = {
        [sym__expression] = ACTIONS(SHIFT(110, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(112, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(183, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(160, 0)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(160, 0)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(160, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(162, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [116] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(181, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [117] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(180, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125, 0)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(179, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [119] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [120] = {
        [sym_identifier] = ACTIONS(SHIFT(178, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [121] = {
        [sym__type_specifier] = ACTIONS(SHIFT(157, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(115, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(122, 0)),
        [sym_identifier] = ACTIONS(SHIFT(158, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [122] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(149, 0)),
        [sym_identifier] = ACTIONS(SHIFT(150, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [123] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_type_name] = ACTIONS(SHIFT(142, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117, 0)),
        [sym__expression] = ACTIONS(SHIFT(143, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(115, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120, 0)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(122, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(126, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [124] = {
        [sym__expression] = ACTIONS(SHIFT(130, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(131, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [125] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_qualifier, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE), SHIFT(127, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
        [sym__type_specifier] = ACTIONS(SHIFT(128, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(19, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(19, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(19, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(20, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(21, 0)),
        [sym_identifier] = ACTIONS(SHIFT(22, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(129, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [131] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
        [sym__expression] = ACTIONS(SHIFT(137, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(138, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [133] = {
        [sym__expression] = ACTIONS(SHIFT(136, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(131, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [sym__expression] = ACTIONS(SHIFT(135, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(131, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(139, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(140, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [139] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(141, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [140] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(147, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(145, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [144] = {
        [sym__expression] = ACTIONS(SHIFT(146, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(131, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [145] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [sym__expression] = ACTIONS(SHIFT(148, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(131, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(155, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(156, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(151, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(152, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(153, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(154, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(153, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(159, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(160, 0)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(160, 0)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(160, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 2, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(162, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE), SHIFT(127, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(164, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(165, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__abstract_declarator, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 1, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(176, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(160, 0)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(160, 0)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(160, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(162, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(163, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(160, 0)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(160, 0)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(160, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_pointer_declarator, 1, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_pointer_declarator, 1, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(SHIFT(162, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(164, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(165, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_pointer_declarator, 2, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [sym__expression] = ACTIONS(SHIFT(171, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(172, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(59, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(166, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(167, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(168, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(169, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(170, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(174, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [172] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [sym__expression] = ACTIONS(SHIFT(175, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173, 0)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(164, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(165, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(177, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__abstract_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [180] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [sym__expression] = ACTIONS(SHIFT(182, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(164, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(165, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(186, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [185] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [186] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(190, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [188] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(189, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [sym__expression] = ACTIONS(SHIFT(191, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(210, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [sym__declarator] = ACTIONS(SHIFT(208, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(194, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196, 0)),
        [sym_identifier] = ACTIONS(SHIFT(194, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [sym__declarator] = ACTIONS(SHIFT(197, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(194, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196, 0)),
        [sym_identifier] = ACTIONS(SHIFT(194, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [sym__expression] = ACTIONS(SHIFT(205, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(206, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(59, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(200, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(201, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(202, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(203, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(204, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(207, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(209, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [209] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [sym__declarator] = ACTIONS(SHIFT(212, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(69, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(69, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(69, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(71, 0)),
        [sym_identifier] = ACTIONS(SHIFT(69, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(73, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74, 0)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [213] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(215, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(217, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(35, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [219] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym__declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_macro_type, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(228, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(229, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(224, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(225, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(226, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [225] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(227, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [228] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(226, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_numeric_type_specifier_repeat1, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [231] = {
        [anon_sym_LF] = ACTIONS(SHIFT(232, 0)),
        [sym_preproc_arg] = ACTIONS(SHIFT(233, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_preproc_define, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [233] = {
        [anon_sym_LF] = ACTIONS(SHIFT(234, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_preproc_define, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym__declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [237] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [238] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(258, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(261, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [240] = {
        [sym_compound_statement] = ACTIONS(SHIFT(257, 0)),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(258, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(259, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(261, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(245, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(246, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [241] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
        [sym__declarator] = ACTIONS(SHIFT(255, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(194, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196, 0)),
        [sym_identifier] = ACTIONS(SHIFT(194, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [243] = {
        [sym__declarator] = ACTIONS(SHIFT(244, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(241, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(241, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(241, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(242, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(243, 0)),
        [sym_identifier] = ACTIONS(SHIFT(241, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(245, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(246, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
        [sym__expression] = ACTIONS(SHIFT(252, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(253, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [246] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(59, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(247, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(248, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [247] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(249, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(250, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(251, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [250] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(254, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(256, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_definition, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(445, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [259] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(354, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(355, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_declaration] = ACTIONS(SHIFT(356, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_compound_statement] = ACTIONS(SHIFT(357, 0)),
        [sym__expression] = ACTIONS(SHIFT(358, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [sym__statement] = ACTIONS(SHIFT(356, 0)),
        [sym_for_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_expression_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(6, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(360, 0)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(361, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(363, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_for] = ACTIONS(SHIFT(366, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(367, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [260] = {
        [sym__init_declarator] = ACTIONS(SHIFT(335, 0)),
        [sym__declarator] = ACTIONS(SHIFT(336, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(337, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339, 0)),
        [sym_identifier] = ACTIONS(SHIFT(337, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [261] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [262] = {
        [sym_initializer] = ACTIONS(SHIFT(263, 0)),
        [sym__expression] = ACTIONS(SHIFT(264, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(266, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268, 0)),
        [sym_string] = ACTIONS(SHIFT(265, 0)),
        [sym_identifier] = ACTIONS(SHIFT(269, 0)),
        [sym_number] = ACTIONS(SHIFT(265, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [264] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 1, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(333, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(272, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(273, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [265] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [sym_initializer] = ACTIONS(SHIFT(286, 0)),
        [sym_initializer_list] = ACTIONS(SHIFT(287, 0)),
        [sym_designation] = ACTIONS(SHIFT(288, 0)),
        [sym__expression] = ACTIONS(SHIFT(289, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(291, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293, 0)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [267] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_type_name] = ACTIONS(SHIFT(281, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117, 0)),
        [sym__expression] = ACTIONS(SHIFT(282, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(115, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120, 0)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(122, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(126, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [268] = {
        [sym__expression] = ACTIONS(SHIFT(270, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268, 0)),
        [sym_string] = ACTIONS(SHIFT(265, 0)),
        [sym_identifier] = ACTIONS(SHIFT(269, 0)),
        [sym_number] = ACTIONS(SHIFT(265, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [269] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [270] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(272, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(273, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [271] = {
        [sym__expression] = ACTIONS(SHIFT(276, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(277, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [272] = {
        [sym__expression] = ACTIONS(SHIFT(275, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268, 0)),
        [sym_string] = ACTIONS(SHIFT(265, 0)),
        [sym_identifier] = ACTIONS(SHIFT(269, 0)),
        [sym_number] = ACTIONS(SHIFT(265, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [273] = {
        [sym__expression] = ACTIONS(SHIFT(274, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268, 0)),
        [sym_string] = ACTIONS(SHIFT(265, 0)),
        [sym_identifier] = ACTIONS(SHIFT(269, 0)),
        [sym_number] = ACTIONS(SHIFT(265, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [274] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(272, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [275] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [276] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(278, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(279, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [277] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [278] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(280, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [279] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [280] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [281] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(284, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [282] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(283, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [283] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [284] = {
        [sym__expression] = ACTIONS(SHIFT(285, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268, 0)),
        [sym_string] = ACTIONS(SHIFT(265, 0)),
        [sym_identifier] = ACTIONS(SHIFT(269, 0)),
        [sym_number] = ACTIONS(SHIFT(265, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [285] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [286] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [287] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(330, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(331, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [288] = {
        [sym_initializer] = ACTIONS(SHIFT(329, 0)),
        [sym__expression] = ACTIONS(SHIFT(289, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [289] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(327, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(300, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(301, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [290] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [291] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(326, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [292] = {
        [sym_initializer] = ACTIONS(SHIFT(286, 0)),
        [sym_initializer_list] = ACTIONS(SHIFT(319, 0)),
        [sym_designation] = ACTIONS(SHIFT(288, 0)),
        [sym__expression] = ACTIONS(SHIFT(289, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(291, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293, 0)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [293] = {
        [sym__expression] = ACTIONS(SHIFT(316, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [294] = {
        [sym_identifier] = ACTIONS(SHIFT(314, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [295] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_type_name] = ACTIONS(SHIFT(309, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117, 0)),
        [sym__expression] = ACTIONS(SHIFT(310, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(115, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120, 0)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(122, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(126, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [296] = {
        [sym__expression] = ACTIONS(SHIFT(298, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [297] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [298] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(300, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(301, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [299] = {
        [sym__expression] = ACTIONS(SHIFT(304, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(305, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [300] = {
        [sym__expression] = ACTIONS(SHIFT(303, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [301] = {
        [sym__expression] = ACTIONS(SHIFT(302, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [302] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(300, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [303] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [304] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(306, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(307, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [305] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [306] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(308, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [307] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [308] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [309] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(312, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [310] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(311, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [311] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [312] = {
        [sym__expression] = ACTIONS(SHIFT(313, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [313] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [314] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(315, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293, 0)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [315] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [316] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(317, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [317] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(318, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293, 0)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [318] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [319] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(320, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(321, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [320] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [321] = {
        [sym_initializer] = ACTIONS(SHIFT(322, 0)),
        [sym_designation] = ACTIONS(SHIFT(323, 0)),
        [sym__expression] = ACTIONS(SHIFT(289, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(291, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(324, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293, 0)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [322] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [323] = {
        [sym_initializer] = ACTIONS(SHIFT(325, 0)),
        [sym__expression] = ACTIONS(SHIFT(289, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [324] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [325] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [326] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [327] = {
        [sym__expression] = ACTIONS(SHIFT(328, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [328] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(SHIFT(327, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(300, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(301, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [329] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [330] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [331] = {
        [sym_initializer] = ACTIONS(SHIFT(322, 0)),
        [sym_designation] = ACTIONS(SHIFT(323, 0)),
        [sym__expression] = ACTIONS(SHIFT(289, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290, 0)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(291, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(332, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293, 0)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296, 0)),
        [sym_string] = ACTIONS(SHIFT(290, 0)),
        [sym_identifier] = ACTIONS(SHIFT(297, 0)),
        [sym_number] = ACTIONS(SHIFT(290, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [332] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [333] = {
        [sym__expression] = ACTIONS(SHIFT(334, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268, 0)),
        [sym_string] = ACTIONS(SHIFT(265, 0)),
        [sym_identifier] = ACTIONS(SHIFT(269, 0)),
        [sym_number] = ACTIONS(SHIFT(265, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [334] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(SHIFT(333, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(272, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(273, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [335] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(353, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [336] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(353, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [337] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [338] = {
        [sym__declarator] = ACTIONS(SHIFT(351, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(194, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(194, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196, 0)),
        [sym_identifier] = ACTIONS(SHIFT(194, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [339] = {
        [sym__declarator] = ACTIONS(SHIFT(340, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(337, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339, 0)),
        [sym_identifier] = ACTIONS(SHIFT(337, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [340] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_declarator, 2, FRAGILE)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [341] = {
        [sym__expression] = ACTIONS(SHIFT(348, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(349, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84, 0)),
        [sym_string] = ACTIONS(SHIFT(81, 0)),
        [sym_identifier] = ACTIONS(SHIFT(85, 0)),
        [sym_number] = ACTIONS(SHIFT(81, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [342] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(59, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30, 0)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(343, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(30, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(34, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(344, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [sym_identifier] = ACTIONS(SHIFT(36, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [343] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(345, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(346, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [344] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [345] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(347, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [346] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [347] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [348] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173, 0)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(350, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [349] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [350] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [351] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(352, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [352] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [353] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [354] = {
        [sym__type_specifier] = ACTIONS(SHIFT(440, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(6, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(14, 0)),
        [sym_identifier] = ACTIONS(SHIFT(16, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [355] = {
        [sym__init_declarator] = ACTIONS(SHIFT(435, 0)),
        [sym__declarator] = ACTIONS(SHIFT(436, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(337, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339, 0)),
        [sym_identifier] = ACTIONS(SHIFT(337, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [356] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(354, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(355, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_declaration] = ACTIONS(SHIFT(356, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_compound_statement] = ACTIONS(SHIFT(357, 0)),
        [sym__expression] = ACTIONS(SHIFT(358, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [sym__statement] = ACTIONS(SHIFT(356, 0)),
        [sym_for_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_expression_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(6, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(432, 0)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(433, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_for] = ACTIONS(SHIFT(366, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(367, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [357] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_string] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_number] = ACTIONS(REDUCE(sym__statement, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [358] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(434, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [359] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [360] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(431, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [361] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(431, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(430, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [362] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(354, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(355, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_declaration] = ACTIONS(SHIFT(356, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym_compound_statement] = ACTIONS(SHIFT(357, 0)),
        [sym__expression] = ACTIONS(SHIFT(358, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [sym__statement] = ACTIONS(SHIFT(356, 0)),
        [sym_for_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_expression_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(6, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(426, 0)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(427, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362, 0)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(428, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_for] = ACTIONS(SHIFT(366, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(367, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [363] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [364] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115, 0)),
        [sym_type_name] = ACTIONS(SHIFT(421, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117, 0)),
        [sym__expression] = ACTIONS(SHIFT(422, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(115, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120, 0)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(122, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124, 0)),
        [sym_string] = ACTIONS(SHIFT(119, 0)),
        [sym_identifier] = ACTIONS(SHIFT(126, 0)),
        [sym_number] = ACTIONS(SHIFT(119, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [365] = {
        [sym__expression] = ACTIONS(SHIFT(420, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [366] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(368, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [367] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE), SHIFT(17, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [368] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(369, 0)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4, 0)),
        [sym__type_specifier] = ACTIONS(SHIFT(370, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_declaration] = ACTIONS(SHIFT(371, 0)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4, 0)),
        [sym__expression] = ACTIONS(SHIFT(372, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(6, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9, 0)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(373, 0)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_extern] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_static] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_auto] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_register] = ACTIONS(SHIFT(12, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(14, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(371, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_const] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(367, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [369] = {
        [sym__type_specifier] = ACTIONS(SHIFT(415, 0)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6, 0)),
        [sym_macro_type] = ACTIONS(SHIFT(6, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9, 0)),
        [anon_sym_signed] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_long] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_short] = ACTIONS(SHIFT(13, 0)),
        [anon_sym_struct] = ACTIONS(SHIFT(14, 0)),
        [sym_identifier] = ACTIONS(SHIFT(16, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [370] = {
        [sym__init_declarator] = ACTIONS(SHIFT(410, 0)),
        [sym__declarator] = ACTIONS(SHIFT(411, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(337, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339, 0)),
        [sym_identifier] = ACTIONS(SHIFT(337, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [371] = {
        [sym__expression] = ACTIONS(SHIFT(374, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(375, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [372] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(403, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [373] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(402, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [374] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(385, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [375] = {
        [sym__expression] = ACTIONS(SHIFT(377, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(378, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [376] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [377] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(380, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(381, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [378] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357, 0)),
        [sym__expression] = ACTIONS(SHIFT(358, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [sym__statement] = ACTIONS(SHIFT(379, 0)),
        [sym_for_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_expression_statement] = ACTIONS(SHIFT(357, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_for] = ACTIONS(SHIFT(366, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [379] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 6, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [380] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(383, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [381] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357, 0)),
        [sym__expression] = ACTIONS(SHIFT(358, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [sym__statement] = ACTIONS(SHIFT(382, 0)),
        [sym_for_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_expression_statement] = ACTIONS(SHIFT(357, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_for] = ACTIONS(SHIFT(366, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [382] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 7, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [383] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357, 0)),
        [sym__expression] = ACTIONS(SHIFT(358, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [sym__statement] = ACTIONS(SHIFT(384, 0)),
        [sym_for_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_expression_statement] = ACTIONS(SHIFT(357, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_for] = ACTIONS(SHIFT(366, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [384] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 8, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [385] = {
        [sym__expression] = ACTIONS(SHIFT(398, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(381, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [386] = {
        [sym__expression] = ACTIONS(SHIFT(397, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [387] = {
        [sym__expression] = ACTIONS(SHIFT(392, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(393, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [388] = {
        [sym__expression] = ACTIONS(SHIFT(391, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [389] = {
        [sym__expression] = ACTIONS(SHIFT(390, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [390] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [391] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_math_expression, 3, FRAGILE)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [392] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(394, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(395, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [393] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [394] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(396, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [395] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [396] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [397] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_assignment_expression, 3, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [398] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(399, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(383, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [399] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(400, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [400] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357, 0)),
        [sym__expression] = ACTIONS(SHIFT(358, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [sym__statement] = ACTIONS(SHIFT(401, 0)),
        [sym_for_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_expression_statement] = ACTIONS(SHIFT(357, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_for] = ACTIONS(SHIFT(366, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [401] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 9, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [402] = {
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [403] = {
        [sym__expression] = ACTIONS(SHIFT(404, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(385, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [404] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(405, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [405] = {
        [sym__expression] = ACTIONS(SHIFT(406, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(383, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96, 0)),
        [sym_string] = ACTIONS(SHIFT(93, 0)),
        [sym_identifier] = ACTIONS(SHIFT(97, 0)),
        [sym_number] = ACTIONS(SHIFT(93, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [406] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(407, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(400, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [407] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(408, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [408] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357, 0)),
        [sym__expression] = ACTIONS(SHIFT(358, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [sym__statement] = ACTIONS(SHIFT(409, 0)),
        [sym_for_statement] = ACTIONS(SHIFT(357, 0)),
        [sym_expression_statement] = ACTIONS(SHIFT(357, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_for] = ACTIONS(SHIFT(366, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [409] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 10, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [410] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(412, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(413, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [411] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(412, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(413, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [412] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(414, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [413] = {
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [414] = {
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [415] = {
        [sym__init_declarator] = ACTIONS(SHIFT(416, 0)),
        [sym__declarator] = ACTIONS(SHIFT(417, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(337, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339, 0)),
        [sym_identifier] = ACTIONS(SHIFT(337, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [416] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(418, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(414, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [417] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(418, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(414, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [418] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(419, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [419] = {
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [420] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_expression, 2, FRAGILE)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [421] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(424, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [422] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132, 0)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(423, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133, 0)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [423] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [424] = {
        [sym__expression] = ACTIONS(SHIFT(425, 0)),
        [sym_cast_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_math_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_call_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359, 0)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365, 0)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365, 0)),
        [sym_string] = ACTIONS(SHIFT(359, 0)),
        [sym_identifier] = ACTIONS(SHIFT(376, 0)),
        [sym_number] = ACTIONS(SHIFT(359, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [425] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [426] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(429, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [427] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(429, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(430, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [428] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_compound_statement, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [429] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [430] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [431] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [432] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [433] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(430, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [434] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [435] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(437, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(438, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [436] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(437, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(438, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [437] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(439, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [438] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 3, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [439] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [440] = {
        [sym__init_declarator] = ACTIONS(SHIFT(441, 0)),
        [sym__declarator] = ACTIONS(SHIFT(442, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(337, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(337, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339, 0)),
        [sym_identifier] = ACTIONS(SHIFT(337, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [441] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(443, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(439, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [442] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(443, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(439, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [443] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(444, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [444] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [445] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [446] = {
        [sym__init_declarator] = ACTIONS(SHIFT(447, 0)),
        [sym__declarator] = ACTIONS(SHIFT(448, 0)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(241, 0)),
        [sym_function_declarator] = ACTIONS(SHIFT(241, 0)),
        [sym_array_declarator] = ACTIONS(SHIFT(241, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(242, 0)),
        [anon_sym_STAR] = ACTIONS(SHIFT(243, 0)),
        [sym_identifier] = ACTIONS(SHIFT(241, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [447] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(450, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(445, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [448] = {
        [sym_compound_statement] = ACTIONS(SHIFT(449, 0)),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(450, 0)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(259, 0)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260, 0)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(445, 0)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262, 0)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(245, 0)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(246, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [449] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_definition, 4, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [450] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(451, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [451] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5, 0)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
