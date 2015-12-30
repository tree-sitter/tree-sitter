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

static unsigned short ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_translation_unit] = 2,
        [sym_preproc_define] = 4,
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
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 30,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 34,
        [sym_comment] = 36,
    },
    [1] = {
        [ts_builtin_sym_end] = 38,
        [sym_comment] = 40,
    },
    [2] = {
        [sym_preproc_define] = 4,
        [sym_function_definition] = 4,
        [sym_declaration_specifiers] = 6,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 10,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 4,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 12,
        [aux_sym_translation_unit_repeat1] = 42,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [ts_builtin_sym_error] = 20,
        [ts_builtin_sym_end] = 44,
        [anon_sym_POUNDdefine] = 24,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 30,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 34,
        [sym_comment] = 40,
    },
    [3] = {
        [sym__type_specifier] = 46,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_macro_type] = 12,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 30,
        [sym_identifier] = 34,
        [sym_comment] = 40,
    },
    [4] = {
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 48,
        [sym_numeric_type_specifier] = 48,
        [sym_struct_specifier] = 48,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 48,
        [aux_sym_declaration_specifiers_repeat1] = 50,
        [aux_sym_numeric_type_specifier_repeat1] = 48,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 48,
        [anon_sym_unsigned] = 48,
        [anon_sym_long] = 48,
        [anon_sym_short] = 48,
        [anon_sym_struct] = 48,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 48,
        [sym_comment] = 40,
    },
    [5] = {
        [sym__init_declarator] = 52,
        [sym__declarator] = 54,
        [sym_pointer_declarator] = 56,
        [sym_function_declarator] = 56,
        [sym_array_declarator] = 56,
        [anon_sym_LPAREN] = 58,
        [anon_sym_STAR] = 60,
        [sym_identifier] = 56,
        [sym_comment] = 40,
    },
    [6] = {
        [sym__init_declarator] = 62,
        [sym__declarator] = 62,
        [sym_pointer_declarator] = 62,
        [sym_function_declarator] = 62,
        [sym_array_declarator] = 62,
        [anon_sym_LPAREN] = 62,
        [anon_sym_STAR] = 62,
        [sym_identifier] = 62,
        [sym_comment] = 40,
    },
    [7] = {
        [ts_builtin_sym_end] = 64,
        [sym_comment] = 40,
    },
    [8] = {
        [sym__type_specifier] = 66,
        [sym_numeric_type_specifier] = 66,
        [sym_struct_specifier] = 66,
        [sym_macro_type] = 66,
        [aux_sym_numeric_type_specifier_repeat1] = 66,
        [anon_sym_signed] = 66,
        [anon_sym_unsigned] = 66,
        [anon_sym_long] = 66,
        [anon_sym_short] = 66,
        [anon_sym_struct] = 66,
        [sym_identifier] = 66,
        [sym_comment] = 40,
    },
    [9] = {
        [sym_identifier] = 68,
        [sym_comment] = 40,
    },
    [10] = {
        [anon_sym_SEMI] = 70,
        [sym_comment] = 40,
    },
    [11] = {
        [sym_identifier] = 72,
        [sym_comment] = 40,
    },
    [12] = {
        [sym_storage_class_specifier] = 74,
        [sym__type_specifier] = 74,
        [sym_numeric_type_specifier] = 74,
        [sym_struct_specifier] = 74,
        [sym_type_qualifier] = 74,
        [sym_macro_type] = 74,
        [aux_sym_declaration_specifiers_repeat1] = 74,
        [aux_sym_numeric_type_specifier_repeat1] = 74,
        [anon_sym_typedef] = 74,
        [anon_sym_extern] = 74,
        [anon_sym_static] = 74,
        [anon_sym_auto] = 74,
        [anon_sym_register] = 74,
        [anon_sym_signed] = 74,
        [anon_sym_unsigned] = 74,
        [anon_sym_long] = 74,
        [anon_sym_short] = 74,
        [anon_sym_struct] = 74,
        [anon_sym_const] = 74,
        [anon_sym_restrict] = 74,
        [anon_sym_volatile] = 74,
        [sym_identifier] = 74,
        [sym_comment] = 40,
    },
    [13] = {
        [aux_sym_numeric_type_specifier_repeat1] = 76,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [sym_identifier] = 78,
        [sym_comment] = 40,
    },
    [14] = {
        [anon_sym_LBRACE] = 80,
        [sym_identifier] = 82,
        [sym_comment] = 40,
    },
    [15] = {
        [sym_storage_class_specifier] = 84,
        [sym__type_specifier] = 84,
        [sym_numeric_type_specifier] = 84,
        [sym_struct_specifier] = 84,
        [sym_type_qualifier] = 84,
        [sym_macro_type] = 84,
        [aux_sym_declaration_specifiers_repeat1] = 84,
        [aux_sym_numeric_type_specifier_repeat1] = 84,
        [anon_sym_typedef] = 84,
        [anon_sym_extern] = 84,
        [anon_sym_static] = 84,
        [anon_sym_auto] = 84,
        [anon_sym_register] = 84,
        [anon_sym_signed] = 84,
        [anon_sym_unsigned] = 84,
        [anon_sym_long] = 84,
        [anon_sym_short] = 84,
        [anon_sym_struct] = 84,
        [anon_sym_const] = 84,
        [anon_sym_restrict] = 84,
        [anon_sym_volatile] = 84,
        [sym_identifier] = 84,
        [sym_comment] = 40,
    },
    [16] = {
        [sym__init_declarator] = 86,
        [sym__declarator] = 86,
        [sym_pointer_declarator] = 88,
        [sym_function_declarator] = 86,
        [sym_array_declarator] = 86,
        [anon_sym_LPAREN] = 90,
        [anon_sym_STAR] = 88,
        [sym_identifier] = 88,
        [sym_comment] = 40,
    },
    [17] = {
        [sym__type_specifier] = 93,
        [sym_numeric_type_specifier] = 95,
        [sym_struct_specifier] = 95,
        [sym_macro_type] = 95,
        [aux_sym_numeric_type_specifier_repeat1] = 97,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 99,
        [sym_identifier] = 101,
        [sym_comment] = 40,
    },
    [18] = {
        [anon_sym_RPAREN] = 103,
        [sym_comment] = 40,
    },
    [19] = {
        [anon_sym_RPAREN] = 62,
        [sym_comment] = 40,
    },
    [20] = {
        [sym_identifier] = 105,
        [sym_comment] = 40,
    },
    [21] = {
        [anon_sym_LBRACE] = 107,
        [sym_identifier] = 109,
        [sym_comment] = 40,
    },
    [22] = {
        [anon_sym_LPAREN] = 111,
        [anon_sym_RPAREN] = 88,
        [sym_comment] = 40,
    },
    [23] = {
        [sym__type_specifier] = 113,
        [sym_numeric_type_specifier] = 95,
        [sym_struct_specifier] = 95,
        [sym_macro_type] = 95,
        [aux_sym_numeric_type_specifier_repeat1] = 97,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 99,
        [sym_identifier] = 101,
        [sym_comment] = 40,
    },
    [24] = {
        [anon_sym_RPAREN] = 115,
        [sym_comment] = 40,
    },
    [25] = {
        [anon_sym_RPAREN] = 117,
        [sym_comment] = 40,
    },
    [26] = {
        [sym__type_specifier] = 119,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_struct_declaration] = 123,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [aux_sym_struct_specifier_repeat1] = 127,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RBRACE] = 131,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [27] = {
        [anon_sym_LBRACE] = 135,
        [sym_comment] = 40,
    },
    [28] = {
        [sym__type_specifier] = 119,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_struct_declaration] = 123,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [aux_sym_struct_specifier_repeat1] = 137,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RBRACE] = 139,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [29] = {
        [sym__declarator] = 141,
        [sym_pointer_declarator] = 143,
        [sym_function_declarator] = 143,
        [sym_array_declarator] = 143,
        [anon_sym_LPAREN] = 145,
        [anon_sym_STAR] = 147,
        [sym_identifier] = 143,
        [sym_comment] = 40,
    },
    [30] = {
        [sym__declarator] = 62,
        [sym_pointer_declarator] = 62,
        [sym_function_declarator] = 62,
        [sym_array_declarator] = 62,
        [anon_sym_LPAREN] = 62,
        [anon_sym_STAR] = 62,
        [sym_identifier] = 62,
        [sym_comment] = 40,
    },
    [31] = {
        [sym__type_specifier] = 119,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_struct_declaration] = 123,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [aux_sym_struct_specifier_repeat1] = 149,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RBRACE] = 151,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [32] = {
        [sym_identifier] = 153,
        [sym_comment] = 40,
    },
    [33] = {
        [anon_sym_RBRACE] = 155,
        [sym_comment] = 40,
    },
    [34] = {
        [anon_sym_LBRACE] = 157,
        [sym_identifier] = 159,
        [sym_comment] = 40,
    },
    [35] = {
        [anon_sym_RPAREN] = 161,
        [sym_comment] = 40,
    },
    [36] = {
        [sym__declarator] = 86,
        [sym_pointer_declarator] = 88,
        [sym_function_declarator] = 86,
        [sym_array_declarator] = 86,
        [anon_sym_LPAREN] = 163,
        [anon_sym_STAR] = 88,
        [sym_identifier] = 88,
        [sym_comment] = 40,
    },
    [37] = {
        [sym__type_specifier] = 166,
        [sym_numeric_type_specifier] = 95,
        [sym_struct_specifier] = 95,
        [sym_macro_type] = 95,
        [aux_sym_numeric_type_specifier_repeat1] = 97,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 99,
        [sym_identifier] = 101,
        [sym_comment] = 40,
    },
    [38] = {
        [anon_sym_RPAREN] = 168,
        [sym_comment] = 40,
    },
    [39] = {
        [sym__declarator] = 117,
        [sym_pointer_declarator] = 117,
        [sym_function_declarator] = 117,
        [sym_array_declarator] = 117,
        [anon_sym_LPAREN] = 117,
        [anon_sym_STAR] = 117,
        [sym_identifier] = 117,
        [sym_comment] = 40,
    },
    [40] = {
        [sym__type_specifier] = 119,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_struct_declaration] = 123,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [aux_sym_struct_specifier_repeat1] = 170,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RBRACE] = 172,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [41] = {
        [anon_sym_LBRACE] = 174,
        [sym_comment] = 40,
    },
    [42] = {
        [sym__type_specifier] = 119,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_struct_declaration] = 123,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [aux_sym_struct_specifier_repeat1] = 176,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RBRACE] = 178,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [43] = {
        [anon_sym_RBRACE] = 180,
        [sym_comment] = 40,
    },
    [44] = {
        [sym__declarator] = 161,
        [sym_pointer_declarator] = 161,
        [sym_function_declarator] = 161,
        [sym_array_declarator] = 161,
        [anon_sym_LPAREN] = 161,
        [anon_sym_STAR] = 161,
        [sym_identifier] = 161,
        [sym_comment] = 40,
    },
    [45] = {
        [sym__declarator] = 182,
        [sym_pointer_declarator] = 182,
        [sym_function_declarator] = 182,
        [sym_array_declarator] = 182,
        [anon_sym_LPAREN] = 182,
        [anon_sym_STAR] = 182,
        [sym_identifier] = 182,
        [sym_comment] = 40,
    },
    [46] = {
        [anon_sym_RBRACE] = 178,
        [sym_comment] = 40,
    },
    [47] = {
        [sym__declarator] = 184,
        [sym_pointer_declarator] = 184,
        [sym_function_declarator] = 184,
        [sym_array_declarator] = 184,
        [anon_sym_LPAREN] = 184,
        [anon_sym_STAR] = 184,
        [sym_identifier] = 184,
        [sym_comment] = 40,
    },
    [48] = {
        [anon_sym_RPAREN] = 182,
        [sym_comment] = 40,
    },
    [49] = {
        [sym__declarator] = 186,
        [sym_pointer_declarator] = 186,
        [sym_function_declarator] = 186,
        [sym_array_declarator] = 186,
        [anon_sym_LPAREN] = 186,
        [anon_sym_STAR] = 186,
        [sym_identifier] = 186,
        [sym_comment] = 40,
    },
    [50] = {
        [anon_sym_RBRACE] = 188,
        [sym_comment] = 40,
    },
    [51] = {
        [sym__type_specifier] = 190,
        [sym_numeric_type_specifier] = 190,
        [sym_struct_specifier] = 190,
        [sym_struct_declaration] = 190,
        [sym_macro_type] = 190,
        [aux_sym_numeric_type_specifier_repeat1] = 190,
        [aux_sym_struct_specifier_repeat1] = 190,
        [anon_sym_signed] = 190,
        [anon_sym_unsigned] = 190,
        [anon_sym_long] = 190,
        [anon_sym_short] = 190,
        [anon_sym_struct] = 190,
        [anon_sym_RBRACE] = 190,
        [anon_sym_LBRACK] = 192,
        [anon_sym_LPAREN] = 194,
        [sym_identifier] = 190,
        [sym_comment] = 40,
    },
    [52] = {
        [sym__type_specifier] = 196,
        [sym_numeric_type_specifier] = 196,
        [sym_struct_specifier] = 196,
        [sym_struct_declaration] = 196,
        [sym_macro_type] = 196,
        [aux_sym_numeric_type_specifier_repeat1] = 196,
        [aux_sym_struct_specifier_repeat1] = 196,
        [anon_sym_signed] = 196,
        [anon_sym_unsigned] = 196,
        [anon_sym_long] = 196,
        [anon_sym_short] = 196,
        [anon_sym_struct] = 196,
        [anon_sym_RBRACE] = 196,
        [anon_sym_LBRACK] = 196,
        [anon_sym_LPAREN] = 196,
        [sym_identifier] = 196,
        [sym_comment] = 40,
    },
    [53] = {
        [sym__declarator] = 198,
        [sym_pointer_declarator] = 200,
        [sym_function_declarator] = 200,
        [sym_array_declarator] = 200,
        [anon_sym_LPAREN] = 202,
        [anon_sym_STAR] = 204,
        [sym_identifier] = 200,
        [sym_comment] = 40,
    },
    [54] = {
        [sym__declarator] = 206,
        [sym_pointer_declarator] = 143,
        [sym_function_declarator] = 143,
        [sym_array_declarator] = 143,
        [anon_sym_LPAREN] = 145,
        [anon_sym_STAR] = 147,
        [sym_identifier] = 143,
        [sym_comment] = 40,
    },
    [55] = {
        [sym__type_specifier] = 208,
        [sym_numeric_type_specifier] = 208,
        [sym_struct_specifier] = 208,
        [sym_struct_declaration] = 208,
        [sym_macro_type] = 208,
        [aux_sym_numeric_type_specifier_repeat1] = 208,
        [aux_sym_struct_specifier_repeat1] = 208,
        [anon_sym_signed] = 208,
        [anon_sym_unsigned] = 208,
        [anon_sym_long] = 208,
        [anon_sym_short] = 208,
        [anon_sym_struct] = 208,
        [anon_sym_RBRACE] = 208,
        [anon_sym_LBRACK] = 192,
        [anon_sym_LPAREN] = 194,
        [sym_identifier] = 208,
        [sym_comment] = 40,
    },
    [56] = {
        [sym__expression] = 210,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_RBRACK] = 214,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [57] = {
        [sym_declaration_specifiers] = 222,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 224,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_parameter_declaration] = 226,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 121,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RPAREN] = 228,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [58] = {
        [sym__type_specifier] = 230,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [59] = {
        [sym__declarator] = 232,
        [sym_pointer_declarator] = 234,
        [sym_function_declarator] = 234,
        [sym_array_declarator] = 234,
        [anon_sym_LPAREN] = 236,
        [anon_sym_STAR] = 238,
        [sym_identifier] = 234,
        [sym_comment] = 40,
    },
    [60] = {
        [aux_sym_function_declarator_repeat1] = 240,
        [anon_sym_COMMA] = 242,
        [anon_sym_RPAREN] = 244,
        [sym_comment] = 40,
    },
    [61] = {
        [sym__type_specifier] = 246,
        [sym_numeric_type_specifier] = 246,
        [sym_struct_specifier] = 246,
        [sym_struct_declaration] = 246,
        [sym_macro_type] = 246,
        [aux_sym_numeric_type_specifier_repeat1] = 246,
        [aux_sym_struct_specifier_repeat1] = 246,
        [anon_sym_signed] = 246,
        [anon_sym_unsigned] = 246,
        [anon_sym_long] = 246,
        [anon_sym_short] = 246,
        [anon_sym_struct] = 246,
        [anon_sym_RBRACE] = 246,
        [anon_sym_LBRACK] = 246,
        [anon_sym_LPAREN] = 246,
        [sym_identifier] = 246,
        [sym_comment] = 40,
    },
    [62] = {
        [anon_sym_RPAREN] = 248,
        [sym_comment] = 40,
    },
    [63] = {
        [sym_declaration_specifiers] = 222,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 224,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_parameter_declaration] = 250,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 121,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [64] = {
        [sym__type_specifier] = 252,
        [sym_numeric_type_specifier] = 252,
        [sym_struct_specifier] = 252,
        [sym_struct_declaration] = 252,
        [sym_macro_type] = 252,
        [aux_sym_numeric_type_specifier_repeat1] = 252,
        [aux_sym_struct_specifier_repeat1] = 252,
        [anon_sym_signed] = 252,
        [anon_sym_unsigned] = 252,
        [anon_sym_long] = 252,
        [anon_sym_short] = 252,
        [anon_sym_struct] = 252,
        [anon_sym_RBRACE] = 252,
        [anon_sym_LBRACK] = 252,
        [anon_sym_LPAREN] = 252,
        [sym_identifier] = 252,
        [sym_comment] = 40,
    },
    [65] = {
        [aux_sym_function_declarator_repeat1] = 254,
        [anon_sym_COMMA] = 242,
        [anon_sym_RPAREN] = 256,
        [sym_comment] = 40,
    },
    [66] = {
        [anon_sym_RPAREN] = 258,
        [sym_comment] = 40,
    },
    [67] = {
        [sym__type_specifier] = 260,
        [sym_numeric_type_specifier] = 260,
        [sym_struct_specifier] = 260,
        [sym_struct_declaration] = 260,
        [sym_macro_type] = 260,
        [aux_sym_numeric_type_specifier_repeat1] = 260,
        [aux_sym_struct_specifier_repeat1] = 260,
        [anon_sym_signed] = 260,
        [anon_sym_unsigned] = 260,
        [anon_sym_long] = 260,
        [anon_sym_short] = 260,
        [anon_sym_struct] = 260,
        [anon_sym_RBRACE] = 260,
        [anon_sym_LBRACK] = 260,
        [anon_sym_LPAREN] = 260,
        [sym_identifier] = 260,
        [sym_comment] = 40,
    },
    [68] = {
        [aux_sym_function_declarator_repeat1] = 262,
        [anon_sym_COMMA] = 262,
        [anon_sym_LBRACK] = 264,
        [anon_sym_LPAREN] = 266,
        [anon_sym_RPAREN] = 262,
        [sym_comment] = 40,
    },
    [69] = {
        [aux_sym_function_declarator_repeat1] = 196,
        [anon_sym_COMMA] = 196,
        [anon_sym_LBRACK] = 196,
        [anon_sym_LPAREN] = 196,
        [anon_sym_RPAREN] = 196,
        [sym_comment] = 40,
    },
    [70] = {
        [sym__declarator] = 268,
        [sym_pointer_declarator] = 200,
        [sym_function_declarator] = 200,
        [sym_array_declarator] = 200,
        [anon_sym_LPAREN] = 202,
        [anon_sym_STAR] = 204,
        [sym_identifier] = 200,
        [sym_comment] = 40,
    },
    [71] = {
        [sym__declarator] = 270,
        [sym_pointer_declarator] = 234,
        [sym_function_declarator] = 234,
        [sym_array_declarator] = 234,
        [anon_sym_LPAREN] = 236,
        [anon_sym_STAR] = 238,
        [sym_identifier] = 234,
        [sym_comment] = 40,
    },
    [72] = {
        [aux_sym_function_declarator_repeat1] = 208,
        [anon_sym_COMMA] = 208,
        [anon_sym_LBRACK] = 264,
        [anon_sym_LPAREN] = 266,
        [anon_sym_RPAREN] = 208,
        [sym_comment] = 40,
    },
    [73] = {
        [sym__expression] = 272,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_RBRACK] = 274,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [74] = {
        [sym_declaration_specifiers] = 222,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 224,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_parameter_declaration] = 276,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 121,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RPAREN] = 278,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [75] = {
        [aux_sym_function_declarator_repeat1] = 280,
        [anon_sym_COMMA] = 242,
        [anon_sym_RPAREN] = 282,
        [sym_comment] = 40,
    },
    [76] = {
        [aux_sym_function_declarator_repeat1] = 246,
        [anon_sym_COMMA] = 246,
        [anon_sym_LBRACK] = 246,
        [anon_sym_LPAREN] = 246,
        [anon_sym_RPAREN] = 246,
        [sym_comment] = 40,
    },
    [77] = {
        [anon_sym_RPAREN] = 284,
        [sym_comment] = 40,
    },
    [78] = {
        [aux_sym_function_declarator_repeat1] = 252,
        [anon_sym_COMMA] = 252,
        [anon_sym_LBRACK] = 252,
        [anon_sym_LPAREN] = 252,
        [anon_sym_RPAREN] = 252,
        [sym_comment] = 40,
    },
    [79] = {
        [aux_sym_function_declarator_repeat1] = 260,
        [anon_sym_COMMA] = 260,
        [anon_sym_LBRACK] = 260,
        [anon_sym_LPAREN] = 260,
        [anon_sym_RPAREN] = 260,
        [sym_comment] = 40,
    },
    [80] = {
        [anon_sym_EQ] = 286,
        [anon_sym_RBRACK] = 288,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 294,
        [sym_comment] = 40,
    },
    [81] = {
        [anon_sym_EQ] = 296,
        [anon_sym_RBRACK] = 296,
        [anon_sym_LPAREN] = 296,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 296,
        [sym_comment] = 40,
    },
    [82] = {
        [aux_sym_function_declarator_repeat1] = 298,
        [anon_sym_COMMA] = 298,
        [anon_sym_LBRACK] = 298,
        [anon_sym_LPAREN] = 298,
        [anon_sym_RPAREN] = 298,
        [sym_comment] = 40,
    },
    [83] = {
        [sym__type_specifier] = 300,
        [sym_numeric_type_specifier] = 302,
        [sym_struct_specifier] = 302,
        [sym_type_name] = 304,
        [sym_type_qualifier] = 306,
        [sym__expression] = 308,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [sym_macro_type] = 302,
        [aux_sym_numeric_type_specifier_repeat1] = 312,
        [aux_sym_type_name_repeat1] = 314,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 316,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_const] = 322,
        [anon_sym_restrict] = 322,
        [anon_sym_volatile] = 322,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 324,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [84] = {
        [sym__expression] = 326,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [85] = {
        [anon_sym_EQ] = 328,
        [anon_sym_RBRACK] = 328,
        [anon_sym_LPAREN] = 328,
        [anon_sym_STAR] = 328,
        [anon_sym_PLUS] = 328,
        [sym_comment] = 40,
    },
    [86] = {
        [anon_sym_EQ] = 330,
        [anon_sym_RBRACK] = 330,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 294,
        [sym_comment] = 40,
    },
    [87] = {
        [sym__expression] = 332,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_RPAREN] = 338,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [88] = {
        [sym__expression] = 344,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [89] = {
        [sym__expression] = 346,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [90] = {
        [anon_sym_EQ] = 348,
        [anon_sym_RBRACK] = 348,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [91] = {
        [anon_sym_EQ] = 348,
        [anon_sym_RBRACK] = 348,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 348,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [92] = {
        [aux_sym_call_expression_repeat1] = 350,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 358,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [93] = {
        [aux_sym_call_expression_repeat1] = 296,
        [anon_sym_COMMA] = 296,
        [anon_sym_EQ] = 296,
        [anon_sym_LPAREN] = 296,
        [anon_sym_RPAREN] = 296,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 296,
        [sym_comment] = 40,
    },
    [94] = {
        [sym__type_specifier] = 300,
        [sym_numeric_type_specifier] = 302,
        [sym_struct_specifier] = 302,
        [sym_type_name] = 364,
        [sym_type_qualifier] = 306,
        [sym__expression] = 366,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [sym_macro_type] = 302,
        [aux_sym_numeric_type_specifier_repeat1] = 312,
        [aux_sym_type_name_repeat1] = 314,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 316,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_const] = 322,
        [anon_sym_restrict] = 322,
        [anon_sym_volatile] = 322,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 324,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [95] = {
        [anon_sym_EQ] = 368,
        [anon_sym_RBRACK] = 368,
        [anon_sym_LPAREN] = 368,
        [anon_sym_STAR] = 368,
        [anon_sym_PLUS] = 368,
        [sym_comment] = 40,
    },
    [96] = {
        [sym__expression] = 370,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [97] = {
        [aux_sym_call_expression_repeat1] = 328,
        [anon_sym_COMMA] = 328,
        [anon_sym_EQ] = 328,
        [anon_sym_LPAREN] = 328,
        [anon_sym_RPAREN] = 328,
        [anon_sym_STAR] = 328,
        [anon_sym_PLUS] = 328,
        [sym_comment] = 40,
    },
    [98] = {
        [aux_sym_call_expression_repeat1] = 330,
        [anon_sym_COMMA] = 330,
        [anon_sym_EQ] = 330,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 330,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [99] = {
        [sym__expression] = 372,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_RPAREN] = 374,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [100] = {
        [sym__expression] = 376,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [101] = {
        [sym__expression] = 378,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [102] = {
        [aux_sym_call_expression_repeat1] = 348,
        [anon_sym_COMMA] = 348,
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 348,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [103] = {
        [aux_sym_call_expression_repeat1] = 348,
        [anon_sym_COMMA] = 348,
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 348,
        [anon_sym_STAR] = 348,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [104] = {
        [aux_sym_call_expression_repeat1] = 380,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 382,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [105] = {
        [aux_sym_call_expression_repeat1] = 368,
        [anon_sym_COMMA] = 368,
        [anon_sym_EQ] = 368,
        [anon_sym_LPAREN] = 368,
        [anon_sym_RPAREN] = 368,
        [anon_sym_STAR] = 368,
        [anon_sym_PLUS] = 368,
        [sym_comment] = 40,
    },
    [106] = {
        [anon_sym_RPAREN] = 384,
        [sym_comment] = 40,
    },
    [107] = {
        [sym__expression] = 386,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [108] = {
        [sym__expression] = 388,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [109] = {
        [aux_sym_call_expression_repeat1] = 390,
        [anon_sym_COMMA] = 390,
        [anon_sym_EQ] = 390,
        [anon_sym_LPAREN] = 390,
        [anon_sym_RPAREN] = 390,
        [anon_sym_STAR] = 390,
        [anon_sym_PLUS] = 390,
        [sym_comment] = 40,
    },
    [110] = {
        [aux_sym_call_expression_repeat1] = 392,
        [anon_sym_COMMA] = 392,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 392,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [111] = {
        [aux_sym_call_expression_repeat1] = 394,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 396,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [112] = {
        [anon_sym_RPAREN] = 398,
        [sym_comment] = 40,
    },
    [113] = {
        [aux_sym_call_expression_repeat1] = 400,
        [anon_sym_COMMA] = 400,
        [anon_sym_EQ] = 400,
        [anon_sym_LPAREN] = 400,
        [anon_sym_RPAREN] = 400,
        [anon_sym_STAR] = 400,
        [anon_sym_PLUS] = 400,
        [sym_comment] = 40,
    },
    [114] = {
        [sym__abstract_declarator] = 402,
        [sym_abstract_pointer_declarator] = 404,
        [sym_abstract_function_declarator] = 404,
        [sym_abstract_array_declarator] = 404,
        [anon_sym_LPAREN] = 406,
        [anon_sym_RPAREN] = 408,
        [anon_sym_STAR] = 410,
        [sym_comment] = 40,
    },
    [115] = {
        [sym__abstract_declarator] = 62,
        [sym_abstract_pointer_declarator] = 62,
        [sym_abstract_function_declarator] = 62,
        [sym_abstract_array_declarator] = 62,
        [anon_sym_LPAREN] = 62,
        [anon_sym_RPAREN] = 62,
        [anon_sym_STAR] = 62,
        [sym_comment] = 40,
    },
    [116] = {
        [anon_sym_RPAREN] = 412,
        [sym_comment] = 40,
    },
    [117] = {
        [sym__type_specifier] = 414,
        [sym_numeric_type_specifier] = 414,
        [sym_struct_specifier] = 414,
        [sym_type_qualifier] = 306,
        [sym_macro_type] = 414,
        [aux_sym_numeric_type_specifier_repeat1] = 414,
        [aux_sym_type_name_repeat1] = 416,
        [anon_sym_signed] = 414,
        [anon_sym_unsigned] = 414,
        [anon_sym_long] = 414,
        [anon_sym_short] = 414,
        [anon_sym_struct] = 414,
        [anon_sym_const] = 322,
        [anon_sym_restrict] = 322,
        [anon_sym_volatile] = 322,
        [sym_identifier] = 414,
        [sym_comment] = 40,
    },
    [118] = {
        [anon_sym_EQ] = 418,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 422,
        [anon_sym_STAR] = 424,
        [anon_sym_PLUS] = 426,
        [sym_comment] = 40,
    },
    [119] = {
        [anon_sym_EQ] = 296,
        [anon_sym_LPAREN] = 296,
        [anon_sym_RPAREN] = 296,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 296,
        [sym_comment] = 40,
    },
    [120] = {
        [sym_identifier] = 428,
        [sym_comment] = 40,
    },
    [121] = {
        [sym__type_specifier] = 430,
        [sym_numeric_type_specifier] = 302,
        [sym_struct_specifier] = 302,
        [sym_macro_type] = 302,
        [aux_sym_numeric_type_specifier_repeat1] = 312,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 316,
        [sym_identifier] = 432,
        [sym_comment] = 40,
    },
    [122] = {
        [anon_sym_LBRACE] = 434,
        [sym_identifier] = 436,
        [sym_comment] = 40,
    },
    [123] = {
        [sym__type_specifier] = 300,
        [sym_numeric_type_specifier] = 302,
        [sym_struct_specifier] = 302,
        [sym_type_name] = 438,
        [sym_type_qualifier] = 306,
        [sym__expression] = 440,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [sym_macro_type] = 302,
        [aux_sym_numeric_type_specifier_repeat1] = 312,
        [aux_sym_type_name_repeat1] = 314,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 316,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_const] = 322,
        [anon_sym_restrict] = 322,
        [anon_sym_volatile] = 322,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 324,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [124] = {
        [sym__expression] = 442,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 444,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [125] = {
        [sym__type_specifier] = 84,
        [sym_numeric_type_specifier] = 84,
        [sym_struct_specifier] = 84,
        [sym_type_qualifier] = 84,
        [sym_macro_type] = 84,
        [aux_sym_numeric_type_specifier_repeat1] = 84,
        [aux_sym_type_name_repeat1] = 84,
        [anon_sym_signed] = 84,
        [anon_sym_unsigned] = 84,
        [anon_sym_long] = 84,
        [anon_sym_short] = 84,
        [anon_sym_struct] = 84,
        [anon_sym_const] = 84,
        [anon_sym_restrict] = 84,
        [anon_sym_volatile] = 84,
        [sym_identifier] = 84,
        [sym_comment] = 40,
    },
    [126] = {
        [sym__abstract_declarator] = 86,
        [sym_abstract_pointer_declarator] = 86,
        [sym_abstract_function_declarator] = 86,
        [sym_abstract_array_declarator] = 86,
        [anon_sym_EQ] = 328,
        [anon_sym_LPAREN] = 446,
        [anon_sym_RPAREN] = 450,
        [anon_sym_STAR] = 450,
        [anon_sym_PLUS] = 328,
        [sym_comment] = 40,
    },
    [127] = {
        [sym__type_specifier] = 453,
        [sym_numeric_type_specifier] = 95,
        [sym_struct_specifier] = 95,
        [sym_macro_type] = 95,
        [aux_sym_numeric_type_specifier_repeat1] = 97,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 99,
        [sym_identifier] = 101,
        [sym_comment] = 40,
    },
    [128] = {
        [anon_sym_RPAREN] = 455,
        [sym_comment] = 40,
    },
    [129] = {
        [sym__abstract_declarator] = 117,
        [sym_abstract_pointer_declarator] = 117,
        [sym_abstract_function_declarator] = 117,
        [sym_abstract_array_declarator] = 117,
        [anon_sym_LPAREN] = 117,
        [anon_sym_RPAREN] = 117,
        [anon_sym_STAR] = 117,
        [sym_comment] = 40,
    },
    [130] = {
        [anon_sym_EQ] = 330,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 330,
        [anon_sym_STAR] = 424,
        [anon_sym_PLUS] = 426,
        [sym_comment] = 40,
    },
    [131] = {
        [anon_sym_EQ] = 328,
        [anon_sym_LPAREN] = 328,
        [anon_sym_RPAREN] = 328,
        [anon_sym_STAR] = 328,
        [anon_sym_PLUS] = 328,
        [sym_comment] = 40,
    },
    [132] = {
        [sym__expression] = 457,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_RPAREN] = 459,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [133] = {
        [sym__expression] = 461,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 444,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [134] = {
        [sym__expression] = 463,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 444,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [135] = {
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 348,
        [anon_sym_STAR] = 424,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [136] = {
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 348,
        [anon_sym_STAR] = 348,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [137] = {
        [aux_sym_call_expression_repeat1] = 465,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 467,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [138] = {
        [anon_sym_EQ] = 368,
        [anon_sym_LPAREN] = 368,
        [anon_sym_RPAREN] = 368,
        [anon_sym_STAR] = 368,
        [anon_sym_PLUS] = 368,
        [sym_comment] = 40,
    },
    [139] = {
        [anon_sym_RPAREN] = 469,
        [sym_comment] = 40,
    },
    [140] = {
        [anon_sym_EQ] = 390,
        [anon_sym_LPAREN] = 390,
        [anon_sym_RPAREN] = 390,
        [anon_sym_STAR] = 390,
        [anon_sym_PLUS] = 390,
        [sym_comment] = 40,
    },
    [141] = {
        [anon_sym_EQ] = 400,
        [anon_sym_LPAREN] = 400,
        [anon_sym_RPAREN] = 400,
        [anon_sym_STAR] = 400,
        [anon_sym_PLUS] = 400,
        [sym_comment] = 40,
    },
    [142] = {
        [anon_sym_RPAREN] = 471,
        [sym_comment] = 40,
    },
    [143] = {
        [anon_sym_EQ] = 418,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 473,
        [anon_sym_STAR] = 424,
        [anon_sym_PLUS] = 426,
        [sym_comment] = 40,
    },
    [144] = {
        [sym__expression] = 475,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 444,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [145] = {
        [anon_sym_EQ] = 477,
        [anon_sym_LPAREN] = 477,
        [anon_sym_RPAREN] = 477,
        [anon_sym_STAR] = 477,
        [anon_sym_PLUS] = 477,
        [sym_comment] = 40,
    },
    [146] = {
        [anon_sym_EQ] = 418,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 392,
        [anon_sym_STAR] = 424,
        [anon_sym_PLUS] = 426,
        [sym_comment] = 40,
    },
    [147] = {
        [sym__expression] = 479,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 444,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [148] = {
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_RPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 40,
    },
    [149] = {
        [sym__type_specifier] = 119,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_struct_declaration] = 123,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [aux_sym_struct_specifier_repeat1] = 483,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RBRACE] = 485,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [150] = {
        [anon_sym_LBRACE] = 487,
        [sym_comment] = 40,
    },
    [151] = {
        [sym__type_specifier] = 119,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_struct_declaration] = 123,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [aux_sym_struct_specifier_repeat1] = 489,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RBRACE] = 491,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [152] = {
        [anon_sym_RBRACE] = 493,
        [sym_comment] = 40,
    },
    [153] = {
        [sym__abstract_declarator] = 161,
        [sym_abstract_pointer_declarator] = 161,
        [sym_abstract_function_declarator] = 161,
        [sym_abstract_array_declarator] = 161,
        [anon_sym_LPAREN] = 161,
        [anon_sym_RPAREN] = 161,
        [anon_sym_STAR] = 161,
        [sym_comment] = 40,
    },
    [154] = {
        [sym__abstract_declarator] = 182,
        [sym_abstract_pointer_declarator] = 182,
        [sym_abstract_function_declarator] = 182,
        [sym_abstract_array_declarator] = 182,
        [anon_sym_LPAREN] = 182,
        [anon_sym_RPAREN] = 182,
        [anon_sym_STAR] = 182,
        [sym_comment] = 40,
    },
    [155] = {
        [anon_sym_RBRACE] = 491,
        [sym_comment] = 40,
    },
    [156] = {
        [sym__abstract_declarator] = 184,
        [sym_abstract_pointer_declarator] = 184,
        [sym_abstract_function_declarator] = 184,
        [sym_abstract_array_declarator] = 184,
        [anon_sym_LPAREN] = 184,
        [anon_sym_RPAREN] = 184,
        [anon_sym_STAR] = 184,
        [sym_comment] = 40,
    },
    [157] = {
        [sym__abstract_declarator] = 495,
        [sym_abstract_pointer_declarator] = 404,
        [sym_abstract_function_declarator] = 404,
        [sym_abstract_array_declarator] = 404,
        [anon_sym_LPAREN] = 406,
        [anon_sym_RPAREN] = 497,
        [anon_sym_STAR] = 410,
        [sym_comment] = 40,
    },
    [158] = {
        [sym__abstract_declarator] = 86,
        [sym_abstract_pointer_declarator] = 88,
        [sym_abstract_function_declarator] = 86,
        [sym_abstract_array_declarator] = 86,
        [anon_sym_LPAREN] = 499,
        [anon_sym_RPAREN] = 88,
        [anon_sym_STAR] = 88,
        [sym_comment] = 40,
    },
    [159] = {
        [anon_sym_LBRACK] = 502,
        [anon_sym_LPAREN] = 504,
        [anon_sym_RPAREN] = 506,
        [sym_comment] = 40,
    },
    [160] = {
        [anon_sym_LBRACK] = 508,
        [anon_sym_LPAREN] = 508,
        [anon_sym_RPAREN] = 508,
        [sym_comment] = 40,
    },
    [161] = {
        [sym__abstract_declarator] = 510,
        [sym_abstract_pointer_declarator] = 404,
        [sym_abstract_function_declarator] = 404,
        [sym_abstract_array_declarator] = 404,
        [anon_sym_LPAREN] = 406,
        [anon_sym_STAR] = 410,
        [sym_comment] = 40,
    },
    [162] = {
        [sym__abstract_declarator] = 512,
        [sym_abstract_pointer_declarator] = 404,
        [sym_abstract_function_declarator] = 404,
        [sym_abstract_array_declarator] = 404,
        [anon_sym_LBRACK] = 514,
        [anon_sym_LPAREN] = 406,
        [anon_sym_RPAREN] = 514,
        [anon_sym_STAR] = 410,
        [sym_comment] = 40,
    },
    [163] = {
        [anon_sym_LBRACK] = 502,
        [anon_sym_LPAREN] = 504,
        [anon_sym_RPAREN] = 516,
        [sym_comment] = 40,
    },
    [164] = {
        [sym__expression] = 518,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_RBRACK] = 520,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [165] = {
        [sym_declaration_specifiers] = 222,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 224,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_parameter_declaration] = 522,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 121,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RPAREN] = 524,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [166] = {
        [aux_sym_function_declarator_repeat1] = 526,
        [anon_sym_COMMA] = 242,
        [anon_sym_RPAREN] = 528,
        [sym_comment] = 40,
    },
    [167] = {
        [anon_sym_LBRACK] = 530,
        [anon_sym_LPAREN] = 530,
        [anon_sym_RPAREN] = 530,
        [sym_comment] = 40,
    },
    [168] = {
        [anon_sym_RPAREN] = 532,
        [sym_comment] = 40,
    },
    [169] = {
        [anon_sym_LBRACK] = 534,
        [anon_sym_LPAREN] = 534,
        [anon_sym_RPAREN] = 534,
        [sym_comment] = 40,
    },
    [170] = {
        [anon_sym_LBRACK] = 536,
        [anon_sym_LPAREN] = 536,
        [anon_sym_RPAREN] = 536,
        [sym_comment] = 40,
    },
    [171] = {
        [anon_sym_EQ] = 286,
        [anon_sym_RBRACK] = 538,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 294,
        [sym_comment] = 40,
    },
    [172] = {
        [anon_sym_LBRACK] = 540,
        [anon_sym_LPAREN] = 540,
        [anon_sym_RPAREN] = 540,
        [sym_comment] = 40,
    },
    [173] = {
        [sym__expression] = 542,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [174] = {
        [anon_sym_LBRACK] = 544,
        [anon_sym_LPAREN] = 544,
        [anon_sym_RPAREN] = 544,
        [sym_comment] = 40,
    },
    [175] = {
        [anon_sym_EQ] = 286,
        [anon_sym_RBRACK] = 392,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 294,
        [sym_comment] = 40,
    },
    [176] = {
        [anon_sym_LBRACK] = 502,
        [anon_sym_LPAREN] = 504,
        [anon_sym_RPAREN] = 546,
        [sym_comment] = 40,
    },
    [177] = {
        [anon_sym_LBRACK] = 548,
        [anon_sym_LPAREN] = 548,
        [anon_sym_RPAREN] = 548,
        [sym_comment] = 40,
    },
    [178] = {
        [sym__abstract_declarator] = 186,
        [sym_abstract_pointer_declarator] = 186,
        [sym_abstract_function_declarator] = 186,
        [sym_abstract_array_declarator] = 186,
        [anon_sym_LPAREN] = 186,
        [anon_sym_RPAREN] = 186,
        [anon_sym_STAR] = 186,
        [sym_comment] = 40,
    },
    [179] = {
        [aux_sym_call_expression_repeat1] = 477,
        [anon_sym_COMMA] = 477,
        [anon_sym_EQ] = 477,
        [anon_sym_LPAREN] = 477,
        [anon_sym_RPAREN] = 477,
        [anon_sym_STAR] = 477,
        [anon_sym_PLUS] = 477,
        [sym_comment] = 40,
    },
    [180] = {
        [sym__type_specifier] = 550,
        [sym_numeric_type_specifier] = 550,
        [sym_struct_specifier] = 550,
        [sym_macro_type] = 550,
        [aux_sym_numeric_type_specifier_repeat1] = 550,
        [anon_sym_signed] = 550,
        [anon_sym_unsigned] = 550,
        [anon_sym_long] = 550,
        [anon_sym_short] = 550,
        [anon_sym_struct] = 550,
        [sym_identifier] = 550,
        [sym_comment] = 40,
    },
    [181] = {
        [sym__expression] = 552,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [182] = {
        [aux_sym_call_expression_repeat1] = 481,
        [anon_sym_COMMA] = 481,
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_RPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 40,
    },
    [183] = {
        [anon_sym_LBRACK] = 502,
        [anon_sym_LPAREN] = 504,
        [anon_sym_RPAREN] = 497,
        [sym_comment] = 40,
    },
    [184] = {
        [anon_sym_RPAREN] = 554,
        [sym_comment] = 40,
    },
    [185] = {
        [anon_sym_EQ] = 390,
        [anon_sym_RBRACK] = 390,
        [anon_sym_LPAREN] = 390,
        [anon_sym_STAR] = 390,
        [anon_sym_PLUS] = 390,
        [sym_comment] = 40,
    },
    [186] = {
        [anon_sym_EQ] = 400,
        [anon_sym_RBRACK] = 400,
        [anon_sym_LPAREN] = 400,
        [anon_sym_STAR] = 400,
        [anon_sym_PLUS] = 400,
        [sym_comment] = 40,
    },
    [187] = {
        [anon_sym_RPAREN] = 556,
        [sym_comment] = 40,
    },
    [188] = {
        [anon_sym_EQ] = 418,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 558,
        [anon_sym_STAR] = 424,
        [anon_sym_PLUS] = 426,
        [sym_comment] = 40,
    },
    [189] = {
        [anon_sym_EQ] = 477,
        [anon_sym_RBRACK] = 477,
        [anon_sym_LPAREN] = 477,
        [anon_sym_STAR] = 477,
        [anon_sym_PLUS] = 477,
        [sym_comment] = 40,
    },
    [190] = {
        [sym__expression] = 560,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [191] = {
        [anon_sym_EQ] = 481,
        [anon_sym_RBRACK] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 40,
    },
    [192] = {
        [aux_sym_function_declarator_repeat1] = 562,
        [anon_sym_COMMA] = 562,
        [anon_sym_LBRACK] = 562,
        [anon_sym_LPAREN] = 562,
        [anon_sym_RPAREN] = 562,
        [sym_comment] = 40,
    },
    [193] = {
        [anon_sym_LBRACK] = 564,
        [anon_sym_LPAREN] = 566,
        [anon_sym_RPAREN] = 568,
        [sym_comment] = 40,
    },
    [194] = {
        [anon_sym_LBRACK] = 196,
        [anon_sym_LPAREN] = 196,
        [anon_sym_RPAREN] = 196,
        [sym_comment] = 40,
    },
    [195] = {
        [sym__declarator] = 570,
        [sym_pointer_declarator] = 200,
        [sym_function_declarator] = 200,
        [sym_array_declarator] = 200,
        [anon_sym_LPAREN] = 202,
        [anon_sym_STAR] = 204,
        [sym_identifier] = 200,
        [sym_comment] = 40,
    },
    [196] = {
        [sym__declarator] = 572,
        [sym_pointer_declarator] = 200,
        [sym_function_declarator] = 200,
        [sym_array_declarator] = 200,
        [anon_sym_LPAREN] = 202,
        [anon_sym_STAR] = 204,
        [sym_identifier] = 200,
        [sym_comment] = 40,
    },
    [197] = {
        [anon_sym_LBRACK] = 564,
        [anon_sym_LPAREN] = 566,
        [anon_sym_RPAREN] = 208,
        [sym_comment] = 40,
    },
    [198] = {
        [sym__expression] = 574,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_RBRACK] = 576,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [199] = {
        [sym_declaration_specifiers] = 222,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 224,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_parameter_declaration] = 578,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 121,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RPAREN] = 580,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [200] = {
        [aux_sym_function_declarator_repeat1] = 582,
        [anon_sym_COMMA] = 242,
        [anon_sym_RPAREN] = 584,
        [sym_comment] = 40,
    },
    [201] = {
        [anon_sym_LBRACK] = 246,
        [anon_sym_LPAREN] = 246,
        [anon_sym_RPAREN] = 246,
        [sym_comment] = 40,
    },
    [202] = {
        [anon_sym_RPAREN] = 586,
        [sym_comment] = 40,
    },
    [203] = {
        [anon_sym_LBRACK] = 252,
        [anon_sym_LPAREN] = 252,
        [anon_sym_RPAREN] = 252,
        [sym_comment] = 40,
    },
    [204] = {
        [anon_sym_LBRACK] = 260,
        [anon_sym_LPAREN] = 260,
        [anon_sym_RPAREN] = 260,
        [sym_comment] = 40,
    },
    [205] = {
        [anon_sym_EQ] = 286,
        [anon_sym_RBRACK] = 588,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 294,
        [sym_comment] = 40,
    },
    [206] = {
        [anon_sym_LBRACK] = 298,
        [anon_sym_LPAREN] = 298,
        [anon_sym_RPAREN] = 298,
        [sym_comment] = 40,
    },
    [207] = {
        [anon_sym_LBRACK] = 562,
        [anon_sym_LPAREN] = 562,
        [anon_sym_RPAREN] = 562,
        [sym_comment] = 40,
    },
    [208] = {
        [anon_sym_LBRACK] = 564,
        [anon_sym_LPAREN] = 566,
        [anon_sym_RPAREN] = 590,
        [sym_comment] = 40,
    },
    [209] = {
        [anon_sym_LBRACK] = 592,
        [anon_sym_LPAREN] = 592,
        [anon_sym_RPAREN] = 592,
        [sym_comment] = 40,
    },
    [210] = {
        [aux_sym_function_declarator_repeat1] = 592,
        [anon_sym_COMMA] = 592,
        [anon_sym_LBRACK] = 592,
        [anon_sym_LPAREN] = 592,
        [anon_sym_RPAREN] = 592,
        [sym_comment] = 40,
    },
    [211] = {
        [sym__declarator] = 594,
        [sym_pointer_declarator] = 234,
        [sym_function_declarator] = 234,
        [sym_array_declarator] = 234,
        [anon_sym_LPAREN] = 236,
        [anon_sym_STAR] = 238,
        [sym_identifier] = 234,
        [sym_comment] = 40,
    },
    [212] = {
        [aux_sym_function_declarator_repeat1] = 596,
        [anon_sym_COMMA] = 596,
        [anon_sym_LBRACK] = 264,
        [anon_sym_LPAREN] = 266,
        [anon_sym_RPAREN] = 596,
        [sym_comment] = 40,
    },
    [213] = {
        [anon_sym_EQ] = 286,
        [anon_sym_RBRACK] = 598,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 294,
        [sym_comment] = 40,
    },
    [214] = {
        [sym__type_specifier] = 298,
        [sym_numeric_type_specifier] = 298,
        [sym_struct_specifier] = 298,
        [sym_struct_declaration] = 298,
        [sym_macro_type] = 298,
        [aux_sym_numeric_type_specifier_repeat1] = 298,
        [aux_sym_struct_specifier_repeat1] = 298,
        [anon_sym_signed] = 298,
        [anon_sym_unsigned] = 298,
        [anon_sym_long] = 298,
        [anon_sym_short] = 298,
        [anon_sym_struct] = 298,
        [anon_sym_RBRACE] = 298,
        [anon_sym_LBRACK] = 298,
        [anon_sym_LPAREN] = 298,
        [sym_identifier] = 298,
        [sym_comment] = 40,
    },
    [215] = {
        [sym__type_specifier] = 562,
        [sym_numeric_type_specifier] = 562,
        [sym_struct_specifier] = 562,
        [sym_struct_declaration] = 562,
        [sym_macro_type] = 562,
        [aux_sym_numeric_type_specifier_repeat1] = 562,
        [aux_sym_struct_specifier_repeat1] = 562,
        [anon_sym_signed] = 562,
        [anon_sym_unsigned] = 562,
        [anon_sym_long] = 562,
        [anon_sym_short] = 562,
        [anon_sym_struct] = 562,
        [anon_sym_RBRACE] = 562,
        [anon_sym_LBRACK] = 562,
        [anon_sym_LPAREN] = 562,
        [sym_identifier] = 562,
        [sym_comment] = 40,
    },
    [216] = {
        [anon_sym_LBRACK] = 564,
        [anon_sym_LPAREN] = 566,
        [anon_sym_RPAREN] = 600,
        [sym_comment] = 40,
    },
    [217] = {
        [sym__type_specifier] = 592,
        [sym_numeric_type_specifier] = 592,
        [sym_struct_specifier] = 592,
        [sym_struct_declaration] = 592,
        [sym_macro_type] = 592,
        [aux_sym_numeric_type_specifier_repeat1] = 592,
        [aux_sym_struct_specifier_repeat1] = 592,
        [anon_sym_signed] = 592,
        [anon_sym_unsigned] = 592,
        [anon_sym_long] = 592,
        [anon_sym_short] = 592,
        [anon_sym_struct] = 592,
        [anon_sym_RBRACE] = 592,
        [anon_sym_LBRACK] = 592,
        [anon_sym_LPAREN] = 592,
        [sym_identifier] = 592,
        [sym_comment] = 40,
    },
    [218] = {
        [anon_sym_RBRACE] = 139,
        [sym_comment] = 40,
    },
    [219] = {
        [anon_sym_RPAREN] = 184,
        [sym_comment] = 40,
    },
    [220] = {
        [anon_sym_RPAREN] = 186,
        [sym_comment] = 40,
    },
    [221] = {
        [sym__init_declarator] = 117,
        [sym__declarator] = 117,
        [sym_pointer_declarator] = 117,
        [sym_function_declarator] = 117,
        [sym_array_declarator] = 117,
        [anon_sym_LPAREN] = 117,
        [anon_sym_STAR] = 117,
        [sym_identifier] = 117,
        [sym_comment] = 40,
    },
    [222] = {
        [sym__type_specifier] = 119,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_struct_declaration] = 123,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [aux_sym_struct_specifier_repeat1] = 602,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RBRACE] = 604,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [223] = {
        [anon_sym_LBRACE] = 606,
        [sym_comment] = 40,
    },
    [224] = {
        [sym__type_specifier] = 119,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_struct_declaration] = 123,
        [sym_macro_type] = 121,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [aux_sym_struct_specifier_repeat1] = 608,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RBRACE] = 610,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [225] = {
        [anon_sym_RBRACE] = 612,
        [sym_comment] = 40,
    },
    [226] = {
        [sym__init_declarator] = 161,
        [sym__declarator] = 161,
        [sym_pointer_declarator] = 161,
        [sym_function_declarator] = 161,
        [sym_array_declarator] = 161,
        [anon_sym_LPAREN] = 161,
        [anon_sym_STAR] = 161,
        [sym_identifier] = 161,
        [sym_comment] = 40,
    },
    [227] = {
        [sym__init_declarator] = 182,
        [sym__declarator] = 182,
        [sym_pointer_declarator] = 182,
        [sym_function_declarator] = 182,
        [sym_array_declarator] = 182,
        [anon_sym_LPAREN] = 182,
        [anon_sym_STAR] = 182,
        [sym_identifier] = 182,
        [sym_comment] = 40,
    },
    [228] = {
        [anon_sym_RBRACE] = 610,
        [sym_comment] = 40,
    },
    [229] = {
        [sym__init_declarator] = 184,
        [sym__declarator] = 184,
        [sym_pointer_declarator] = 184,
        [sym_function_declarator] = 184,
        [sym_array_declarator] = 184,
        [anon_sym_LPAREN] = 184,
        [anon_sym_STAR] = 184,
        [sym_identifier] = 184,
        [sym_comment] = 40,
    },
    [230] = {
        [sym_identifier] = 614,
        [sym_comment] = 40,
    },
    [231] = {
        [anon_sym_LF] = 616,
        [sym_preproc_arg] = 618,
        [sym_comment] = 40,
    },
    [232] = {
        [sym_preproc_define] = 620,
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
        [sym_comment] = 40,
    },
    [233] = {
        [anon_sym_LF] = 622,
        [sym_comment] = 40,
    },
    [234] = {
        [sym_preproc_define] = 624,
        [sym_function_definition] = 624,
        [sym_declaration_specifiers] = 624,
        [sym_storage_class_specifier] = 624,
        [sym__type_specifier] = 624,
        [sym_numeric_type_specifier] = 624,
        [sym_struct_specifier] = 624,
        [sym_declaration] = 624,
        [sym_type_qualifier] = 624,
        [sym_macro_type] = 624,
        [aux_sym_translation_unit_repeat1] = 624,
        [aux_sym_declaration_specifiers_repeat1] = 624,
        [aux_sym_numeric_type_specifier_repeat1] = 624,
        [ts_builtin_sym_error] = 624,
        [ts_builtin_sym_end] = 624,
        [anon_sym_POUNDdefine] = 624,
        [anon_sym_typedef] = 624,
        [anon_sym_extern] = 624,
        [anon_sym_static] = 624,
        [anon_sym_auto] = 624,
        [anon_sym_register] = 624,
        [anon_sym_signed] = 624,
        [anon_sym_unsigned] = 624,
        [anon_sym_long] = 624,
        [anon_sym_short] = 624,
        [anon_sym_struct] = 624,
        [anon_sym_const] = 624,
        [anon_sym_restrict] = 624,
        [anon_sym_volatile] = 624,
        [sym_identifier] = 624,
        [sym_comment] = 40,
    },
    [235] = {
        [sym_preproc_define] = 626,
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
        [sym_comment] = 40,
    },
    [236] = {
        [sym__init_declarator] = 186,
        [sym__declarator] = 186,
        [sym_pointer_declarator] = 186,
        [sym_function_declarator] = 186,
        [sym_array_declarator] = 186,
        [anon_sym_LPAREN] = 186,
        [anon_sym_STAR] = 186,
        [sym_identifier] = 186,
        [sym_comment] = 40,
    },
    [237] = {
        [sym__type_specifier] = 628,
        [sym_numeric_type_specifier] = 628,
        [sym_struct_specifier] = 628,
        [sym_macro_type] = 628,
        [aux_sym_numeric_type_specifier_repeat1] = 628,
        [anon_sym_signed] = 628,
        [anon_sym_unsigned] = 628,
        [anon_sym_long] = 628,
        [anon_sym_short] = 628,
        [anon_sym_struct] = 628,
        [sym_identifier] = 628,
        [sym_comment] = 40,
    },
    [238] = {
        [ts_builtin_sym_end] = 630,
        [sym_comment] = 40,
    },
    [239] = {
        [aux_sym_declaration_repeat1] = 632,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 636,
        [sym_comment] = 40,
    },
    [240] = {
        [sym_compound_statement] = 638,
        [aux_sym_declaration_repeat1] = 632,
        [anon_sym_LBRACE] = 640,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 636,
        [anon_sym_EQ] = 642,
        [anon_sym_LBRACK] = 644,
        [anon_sym_LPAREN] = 646,
        [sym_comment] = 40,
    },
    [241] = {
        [sym_compound_statement] = 196,
        [aux_sym_declaration_repeat1] = 196,
        [anon_sym_LBRACE] = 196,
        [anon_sym_COMMA] = 196,
        [anon_sym_SEMI] = 196,
        [anon_sym_EQ] = 196,
        [anon_sym_LBRACK] = 196,
        [anon_sym_LPAREN] = 196,
        [sym_comment] = 40,
    },
    [242] = {
        [sym__declarator] = 648,
        [sym_pointer_declarator] = 200,
        [sym_function_declarator] = 200,
        [sym_array_declarator] = 200,
        [anon_sym_LPAREN] = 202,
        [anon_sym_STAR] = 204,
        [sym_identifier] = 200,
        [sym_comment] = 40,
    },
    [243] = {
        [sym__declarator] = 650,
        [sym_pointer_declarator] = 56,
        [sym_function_declarator] = 56,
        [sym_array_declarator] = 56,
        [anon_sym_LPAREN] = 58,
        [anon_sym_STAR] = 60,
        [sym_identifier] = 56,
        [sym_comment] = 40,
    },
    [244] = {
        [sym_compound_statement] = 208,
        [aux_sym_declaration_repeat1] = 208,
        [anon_sym_LBRACE] = 208,
        [anon_sym_COMMA] = 208,
        [anon_sym_SEMI] = 208,
        [anon_sym_EQ] = 208,
        [anon_sym_LBRACK] = 644,
        [anon_sym_LPAREN] = 646,
        [sym_comment] = 40,
    },
    [245] = {
        [sym__expression] = 652,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_RBRACK] = 654,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [246] = {
        [sym_declaration_specifiers] = 222,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 224,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_parameter_declaration] = 656,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 121,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RPAREN] = 658,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [247] = {
        [aux_sym_function_declarator_repeat1] = 660,
        [anon_sym_COMMA] = 242,
        [anon_sym_RPAREN] = 662,
        [sym_comment] = 40,
    },
    [248] = {
        [sym_compound_statement] = 246,
        [aux_sym_declaration_repeat1] = 246,
        [anon_sym_LBRACE] = 246,
        [anon_sym_COMMA] = 246,
        [anon_sym_SEMI] = 246,
        [anon_sym_EQ] = 246,
        [anon_sym_LBRACK] = 246,
        [anon_sym_LPAREN] = 246,
        [sym_comment] = 40,
    },
    [249] = {
        [anon_sym_RPAREN] = 664,
        [sym_comment] = 40,
    },
    [250] = {
        [sym_compound_statement] = 252,
        [aux_sym_declaration_repeat1] = 252,
        [anon_sym_LBRACE] = 252,
        [anon_sym_COMMA] = 252,
        [anon_sym_SEMI] = 252,
        [anon_sym_EQ] = 252,
        [anon_sym_LBRACK] = 252,
        [anon_sym_LPAREN] = 252,
        [sym_comment] = 40,
    },
    [251] = {
        [sym_compound_statement] = 260,
        [aux_sym_declaration_repeat1] = 260,
        [anon_sym_LBRACE] = 260,
        [anon_sym_COMMA] = 260,
        [anon_sym_SEMI] = 260,
        [anon_sym_EQ] = 260,
        [anon_sym_LBRACK] = 260,
        [anon_sym_LPAREN] = 260,
        [sym_comment] = 40,
    },
    [252] = {
        [anon_sym_EQ] = 286,
        [anon_sym_RBRACK] = 666,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 294,
        [sym_comment] = 40,
    },
    [253] = {
        [sym_compound_statement] = 298,
        [aux_sym_declaration_repeat1] = 298,
        [anon_sym_LBRACE] = 298,
        [anon_sym_COMMA] = 298,
        [anon_sym_SEMI] = 298,
        [anon_sym_EQ] = 298,
        [anon_sym_LBRACK] = 298,
        [anon_sym_LPAREN] = 298,
        [sym_comment] = 40,
    },
    [254] = {
        [sym_compound_statement] = 562,
        [aux_sym_declaration_repeat1] = 562,
        [anon_sym_LBRACE] = 562,
        [anon_sym_COMMA] = 562,
        [anon_sym_SEMI] = 562,
        [anon_sym_EQ] = 562,
        [anon_sym_LBRACK] = 562,
        [anon_sym_LPAREN] = 562,
        [sym_comment] = 40,
    },
    [255] = {
        [anon_sym_LBRACK] = 564,
        [anon_sym_LPAREN] = 566,
        [anon_sym_RPAREN] = 668,
        [sym_comment] = 40,
    },
    [256] = {
        [sym_compound_statement] = 592,
        [aux_sym_declaration_repeat1] = 592,
        [anon_sym_LBRACE] = 592,
        [anon_sym_COMMA] = 592,
        [anon_sym_SEMI] = 592,
        [anon_sym_EQ] = 592,
        [anon_sym_LBRACK] = 592,
        [anon_sym_LPAREN] = 592,
        [sym_comment] = 40,
    },
    [257] = {
        [sym_preproc_define] = 670,
        [sym_function_definition] = 670,
        [sym_declaration_specifiers] = 670,
        [sym_storage_class_specifier] = 670,
        [sym__type_specifier] = 670,
        [sym_numeric_type_specifier] = 670,
        [sym_struct_specifier] = 670,
        [sym_declaration] = 670,
        [sym_type_qualifier] = 670,
        [sym_macro_type] = 670,
        [aux_sym_translation_unit_repeat1] = 670,
        [aux_sym_declaration_specifiers_repeat1] = 670,
        [aux_sym_numeric_type_specifier_repeat1] = 670,
        [ts_builtin_sym_error] = 670,
        [ts_builtin_sym_end] = 670,
        [anon_sym_POUNDdefine] = 670,
        [anon_sym_typedef] = 670,
        [anon_sym_extern] = 670,
        [anon_sym_static] = 670,
        [anon_sym_auto] = 670,
        [anon_sym_register] = 670,
        [anon_sym_signed] = 670,
        [anon_sym_unsigned] = 670,
        [anon_sym_long] = 670,
        [anon_sym_short] = 670,
        [anon_sym_struct] = 670,
        [anon_sym_const] = 670,
        [anon_sym_restrict] = 670,
        [anon_sym_volatile] = 670,
        [sym_identifier] = 670,
        [sym_comment] = 40,
    },
    [258] = {
        [anon_sym_SEMI] = 672,
        [sym_comment] = 40,
    },
    [259] = {
        [sym_declaration_specifiers] = 674,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 676,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 678,
        [sym_type_qualifier] = 8,
        [sym_compound_statement] = 680,
        [sym__expression] = 682,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [sym__statement] = 678,
        [sym_for_statement] = 680,
        [sym_expression_statement] = 680,
        [sym_macro_type] = 12,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [aux_sym_compound_statement_repeat1] = 686,
        [ts_builtin_sym_error] = 688,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 30,
        [anon_sym_LBRACE] = 690,
        [anon_sym_RBRACE] = 692,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [anon_sym_AMP] = 696,
        [anon_sym_for] = 698,
        [sym_string] = 684,
        [sym_identifier] = 700,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [260] = {
        [sym__init_declarator] = 702,
        [sym__declarator] = 704,
        [sym_pointer_declarator] = 706,
        [sym_function_declarator] = 706,
        [sym_array_declarator] = 706,
        [anon_sym_LPAREN] = 708,
        [anon_sym_STAR] = 710,
        [sym_identifier] = 706,
        [sym_comment] = 40,
    },
    [261] = {
        [sym_preproc_define] = 712,
        [sym_function_definition] = 712,
        [sym_declaration_specifiers] = 712,
        [sym_storage_class_specifier] = 712,
        [sym__type_specifier] = 712,
        [sym_numeric_type_specifier] = 712,
        [sym_struct_specifier] = 712,
        [sym_declaration] = 712,
        [sym_type_qualifier] = 712,
        [sym_macro_type] = 712,
        [aux_sym_translation_unit_repeat1] = 712,
        [aux_sym_declaration_specifiers_repeat1] = 712,
        [aux_sym_numeric_type_specifier_repeat1] = 712,
        [ts_builtin_sym_error] = 712,
        [ts_builtin_sym_end] = 712,
        [anon_sym_POUNDdefine] = 712,
        [anon_sym_typedef] = 712,
        [anon_sym_extern] = 712,
        [anon_sym_static] = 712,
        [anon_sym_auto] = 712,
        [anon_sym_register] = 712,
        [anon_sym_signed] = 712,
        [anon_sym_unsigned] = 712,
        [anon_sym_long] = 712,
        [anon_sym_short] = 712,
        [anon_sym_struct] = 712,
        [anon_sym_const] = 712,
        [anon_sym_restrict] = 712,
        [anon_sym_volatile] = 712,
        [sym_identifier] = 712,
        [sym_comment] = 40,
    },
    [262] = {
        [sym_initializer] = 714,
        [sym__expression] = 716,
        [sym_cast_expression] = 718,
        [sym_math_expression] = 718,
        [sym_call_expression] = 718,
        [sym_pointer_expression] = 718,
        [sym_assignment_expression] = 718,
        [anon_sym_LBRACE] = 720,
        [anon_sym_LPAREN] = 722,
        [anon_sym_STAR] = 724,
        [anon_sym_AMP] = 724,
        [sym_string] = 718,
        [sym_identifier] = 726,
        [sym_number] = 718,
        [sym_comment] = 40,
    },
    [263] = {
        [aux_sym_declaration_repeat1] = 728,
        [anon_sym_COMMA] = 728,
        [anon_sym_SEMI] = 728,
        [sym_comment] = 40,
    },
    [264] = {
        [aux_sym_declaration_repeat1] = 730,
        [anon_sym_COMMA] = 730,
        [anon_sym_SEMI] = 730,
        [anon_sym_EQ] = 732,
        [anon_sym_LPAREN] = 734,
        [anon_sym_STAR] = 736,
        [anon_sym_PLUS] = 738,
        [sym_comment] = 40,
    },
    [265] = {
        [aux_sym_declaration_repeat1] = 296,
        [anon_sym_COMMA] = 296,
        [anon_sym_SEMI] = 296,
        [anon_sym_EQ] = 296,
        [anon_sym_LPAREN] = 296,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 296,
        [sym_comment] = 40,
    },
    [266] = {
        [sym_initializer] = 740,
        [sym_initializer_list] = 742,
        [sym_designation] = 744,
        [sym__expression] = 746,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [aux_sym_designation_repeat1] = 750,
        [anon_sym_LBRACE] = 752,
        [anon_sym_LBRACK] = 754,
        [anon_sym_DOT] = 756,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [267] = {
        [sym__type_specifier] = 300,
        [sym_numeric_type_specifier] = 302,
        [sym_struct_specifier] = 302,
        [sym_type_name] = 764,
        [sym_type_qualifier] = 306,
        [sym__expression] = 766,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [sym_macro_type] = 302,
        [aux_sym_numeric_type_specifier_repeat1] = 312,
        [aux_sym_type_name_repeat1] = 314,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 316,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_const] = 322,
        [anon_sym_restrict] = 322,
        [anon_sym_volatile] = 322,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 324,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [268] = {
        [sym__expression] = 768,
        [sym_cast_expression] = 718,
        [sym_math_expression] = 718,
        [sym_call_expression] = 718,
        [sym_pointer_expression] = 718,
        [sym_assignment_expression] = 718,
        [anon_sym_LPAREN] = 722,
        [anon_sym_STAR] = 724,
        [anon_sym_AMP] = 724,
        [sym_string] = 718,
        [sym_identifier] = 726,
        [sym_number] = 718,
        [sym_comment] = 40,
    },
    [269] = {
        [aux_sym_declaration_repeat1] = 328,
        [anon_sym_COMMA] = 328,
        [anon_sym_SEMI] = 328,
        [anon_sym_EQ] = 328,
        [anon_sym_LPAREN] = 328,
        [anon_sym_STAR] = 328,
        [anon_sym_PLUS] = 328,
        [sym_comment] = 40,
    },
    [270] = {
        [aux_sym_declaration_repeat1] = 330,
        [anon_sym_COMMA] = 330,
        [anon_sym_SEMI] = 330,
        [anon_sym_EQ] = 330,
        [anon_sym_LPAREN] = 734,
        [anon_sym_STAR] = 736,
        [anon_sym_PLUS] = 738,
        [sym_comment] = 40,
    },
    [271] = {
        [sym__expression] = 770,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_RPAREN] = 772,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [272] = {
        [sym__expression] = 774,
        [sym_cast_expression] = 718,
        [sym_math_expression] = 718,
        [sym_call_expression] = 718,
        [sym_pointer_expression] = 718,
        [sym_assignment_expression] = 718,
        [anon_sym_LPAREN] = 722,
        [anon_sym_STAR] = 724,
        [anon_sym_AMP] = 724,
        [sym_string] = 718,
        [sym_identifier] = 726,
        [sym_number] = 718,
        [sym_comment] = 40,
    },
    [273] = {
        [sym__expression] = 776,
        [sym_cast_expression] = 718,
        [sym_math_expression] = 718,
        [sym_call_expression] = 718,
        [sym_pointer_expression] = 718,
        [sym_assignment_expression] = 718,
        [anon_sym_LPAREN] = 722,
        [anon_sym_STAR] = 724,
        [anon_sym_AMP] = 724,
        [sym_string] = 718,
        [sym_identifier] = 726,
        [sym_number] = 718,
        [sym_comment] = 40,
    },
    [274] = {
        [aux_sym_declaration_repeat1] = 348,
        [anon_sym_COMMA] = 348,
        [anon_sym_SEMI] = 348,
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 734,
        [anon_sym_STAR] = 736,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [275] = {
        [aux_sym_declaration_repeat1] = 348,
        [anon_sym_COMMA] = 348,
        [anon_sym_SEMI] = 348,
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 734,
        [anon_sym_STAR] = 348,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [276] = {
        [aux_sym_call_expression_repeat1] = 778,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 780,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [277] = {
        [aux_sym_declaration_repeat1] = 368,
        [anon_sym_COMMA] = 368,
        [anon_sym_SEMI] = 368,
        [anon_sym_EQ] = 368,
        [anon_sym_LPAREN] = 368,
        [anon_sym_STAR] = 368,
        [anon_sym_PLUS] = 368,
        [sym_comment] = 40,
    },
    [278] = {
        [anon_sym_RPAREN] = 782,
        [sym_comment] = 40,
    },
    [279] = {
        [aux_sym_declaration_repeat1] = 390,
        [anon_sym_COMMA] = 390,
        [anon_sym_SEMI] = 390,
        [anon_sym_EQ] = 390,
        [anon_sym_LPAREN] = 390,
        [anon_sym_STAR] = 390,
        [anon_sym_PLUS] = 390,
        [sym_comment] = 40,
    },
    [280] = {
        [aux_sym_declaration_repeat1] = 400,
        [anon_sym_COMMA] = 400,
        [anon_sym_SEMI] = 400,
        [anon_sym_EQ] = 400,
        [anon_sym_LPAREN] = 400,
        [anon_sym_STAR] = 400,
        [anon_sym_PLUS] = 400,
        [sym_comment] = 40,
    },
    [281] = {
        [anon_sym_RPAREN] = 784,
        [sym_comment] = 40,
    },
    [282] = {
        [anon_sym_EQ] = 418,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 786,
        [anon_sym_STAR] = 424,
        [anon_sym_PLUS] = 426,
        [sym_comment] = 40,
    },
    [283] = {
        [aux_sym_declaration_repeat1] = 477,
        [anon_sym_COMMA] = 477,
        [anon_sym_SEMI] = 477,
        [anon_sym_EQ] = 477,
        [anon_sym_LPAREN] = 477,
        [anon_sym_STAR] = 477,
        [anon_sym_PLUS] = 477,
        [sym_comment] = 40,
    },
    [284] = {
        [sym__expression] = 788,
        [sym_cast_expression] = 718,
        [sym_math_expression] = 718,
        [sym_call_expression] = 718,
        [sym_pointer_expression] = 718,
        [sym_assignment_expression] = 718,
        [anon_sym_LPAREN] = 722,
        [anon_sym_STAR] = 724,
        [anon_sym_AMP] = 724,
        [sym_string] = 718,
        [sym_identifier] = 726,
        [sym_number] = 718,
        [sym_comment] = 40,
    },
    [285] = {
        [aux_sym_declaration_repeat1] = 481,
        [anon_sym_COMMA] = 481,
        [anon_sym_SEMI] = 481,
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 40,
    },
    [286] = {
        [anon_sym_RBRACE] = 790,
        [anon_sym_COMMA] = 790,
        [sym_comment] = 40,
    },
    [287] = {
        [anon_sym_RBRACE] = 792,
        [anon_sym_COMMA] = 794,
        [sym_comment] = 40,
    },
    [288] = {
        [sym_initializer] = 796,
        [sym__expression] = 746,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [anon_sym_LBRACE] = 752,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [289] = {
        [anon_sym_RBRACE] = 730,
        [anon_sym_COMMA] = 730,
        [anon_sym_EQ] = 798,
        [anon_sym_LPAREN] = 800,
        [anon_sym_STAR] = 802,
        [anon_sym_PLUS] = 804,
        [sym_comment] = 40,
    },
    [290] = {
        [anon_sym_RBRACE] = 296,
        [anon_sym_COMMA] = 296,
        [anon_sym_EQ] = 296,
        [anon_sym_LPAREN] = 296,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 296,
        [sym_comment] = 40,
    },
    [291] = {
        [anon_sym_EQ] = 806,
        [sym_comment] = 40,
    },
    [292] = {
        [sym_initializer] = 740,
        [sym_initializer_list] = 808,
        [sym_designation] = 744,
        [sym__expression] = 746,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [aux_sym_designation_repeat1] = 750,
        [anon_sym_LBRACE] = 752,
        [anon_sym_LBRACK] = 754,
        [anon_sym_DOT] = 756,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [293] = {
        [sym__expression] = 810,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [294] = {
        [sym_identifier] = 812,
        [sym_comment] = 40,
    },
    [295] = {
        [sym__type_specifier] = 300,
        [sym_numeric_type_specifier] = 302,
        [sym_struct_specifier] = 302,
        [sym_type_name] = 814,
        [sym_type_qualifier] = 306,
        [sym__expression] = 816,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [sym_macro_type] = 302,
        [aux_sym_numeric_type_specifier_repeat1] = 312,
        [aux_sym_type_name_repeat1] = 314,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 316,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_const] = 322,
        [anon_sym_restrict] = 322,
        [anon_sym_volatile] = 322,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 324,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [296] = {
        [sym__expression] = 818,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [297] = {
        [anon_sym_RBRACE] = 328,
        [anon_sym_COMMA] = 328,
        [anon_sym_EQ] = 328,
        [anon_sym_LPAREN] = 328,
        [anon_sym_STAR] = 328,
        [anon_sym_PLUS] = 328,
        [sym_comment] = 40,
    },
    [298] = {
        [anon_sym_RBRACE] = 330,
        [anon_sym_COMMA] = 330,
        [anon_sym_EQ] = 330,
        [anon_sym_LPAREN] = 800,
        [anon_sym_STAR] = 802,
        [anon_sym_PLUS] = 804,
        [sym_comment] = 40,
    },
    [299] = {
        [sym__expression] = 820,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_RPAREN] = 822,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [300] = {
        [sym__expression] = 824,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [301] = {
        [sym__expression] = 826,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [302] = {
        [anon_sym_RBRACE] = 348,
        [anon_sym_COMMA] = 348,
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 800,
        [anon_sym_STAR] = 802,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [303] = {
        [anon_sym_RBRACE] = 348,
        [anon_sym_COMMA] = 348,
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 800,
        [anon_sym_STAR] = 348,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [304] = {
        [aux_sym_call_expression_repeat1] = 828,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 830,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [305] = {
        [anon_sym_RBRACE] = 368,
        [anon_sym_COMMA] = 368,
        [anon_sym_EQ] = 368,
        [anon_sym_LPAREN] = 368,
        [anon_sym_STAR] = 368,
        [anon_sym_PLUS] = 368,
        [sym_comment] = 40,
    },
    [306] = {
        [anon_sym_RPAREN] = 832,
        [sym_comment] = 40,
    },
    [307] = {
        [anon_sym_RBRACE] = 390,
        [anon_sym_COMMA] = 390,
        [anon_sym_EQ] = 390,
        [anon_sym_LPAREN] = 390,
        [anon_sym_STAR] = 390,
        [anon_sym_PLUS] = 390,
        [sym_comment] = 40,
    },
    [308] = {
        [anon_sym_RBRACE] = 400,
        [anon_sym_COMMA] = 400,
        [anon_sym_EQ] = 400,
        [anon_sym_LPAREN] = 400,
        [anon_sym_STAR] = 400,
        [anon_sym_PLUS] = 400,
        [sym_comment] = 40,
    },
    [309] = {
        [anon_sym_RPAREN] = 834,
        [sym_comment] = 40,
    },
    [310] = {
        [anon_sym_EQ] = 418,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 836,
        [anon_sym_STAR] = 424,
        [anon_sym_PLUS] = 426,
        [sym_comment] = 40,
    },
    [311] = {
        [anon_sym_RBRACE] = 477,
        [anon_sym_COMMA] = 477,
        [anon_sym_EQ] = 477,
        [anon_sym_LPAREN] = 477,
        [anon_sym_STAR] = 477,
        [anon_sym_PLUS] = 477,
        [sym_comment] = 40,
    },
    [312] = {
        [sym__expression] = 838,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [313] = {
        [anon_sym_RBRACE] = 481,
        [anon_sym_COMMA] = 481,
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 40,
    },
    [314] = {
        [aux_sym_designation_repeat1] = 840,
        [anon_sym_EQ] = 842,
        [anon_sym_LBRACK] = 754,
        [anon_sym_DOT] = 756,
        [sym_comment] = 40,
    },
    [315] = {
        [anon_sym_EQ] = 844,
        [sym_comment] = 40,
    },
    [316] = {
        [anon_sym_EQ] = 286,
        [anon_sym_RBRACK] = 846,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 294,
        [sym_comment] = 40,
    },
    [317] = {
        [aux_sym_designation_repeat1] = 848,
        [anon_sym_EQ] = 844,
        [anon_sym_LBRACK] = 754,
        [anon_sym_DOT] = 756,
        [sym_comment] = 40,
    },
    [318] = {
        [anon_sym_EQ] = 850,
        [sym_comment] = 40,
    },
    [319] = {
        [anon_sym_RBRACE] = 852,
        [anon_sym_COMMA] = 854,
        [sym_comment] = 40,
    },
    [320] = {
        [anon_sym_RBRACE] = 856,
        [anon_sym_COMMA] = 856,
        [sym_comment] = 40,
    },
    [321] = {
        [sym_initializer] = 858,
        [sym_designation] = 860,
        [sym__expression] = 746,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [aux_sym_designation_repeat1] = 750,
        [anon_sym_LBRACE] = 752,
        [anon_sym_RBRACE] = 862,
        [anon_sym_LBRACK] = 754,
        [anon_sym_DOT] = 756,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [322] = {
        [anon_sym_RBRACE] = 864,
        [anon_sym_COMMA] = 864,
        [sym_comment] = 40,
    },
    [323] = {
        [sym_initializer] = 866,
        [sym__expression] = 746,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [anon_sym_LBRACE] = 752,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [324] = {
        [anon_sym_RBRACE] = 868,
        [anon_sym_COMMA] = 868,
        [sym_comment] = 40,
    },
    [325] = {
        [anon_sym_RBRACE] = 870,
        [anon_sym_COMMA] = 870,
        [sym_comment] = 40,
    },
    [326] = {
        [sym_initializer] = 872,
        [sym__expression] = 872,
        [sym_cast_expression] = 872,
        [sym_math_expression] = 872,
        [sym_call_expression] = 872,
        [sym_pointer_expression] = 872,
        [sym_assignment_expression] = 872,
        [anon_sym_LBRACE] = 872,
        [anon_sym_LPAREN] = 872,
        [anon_sym_STAR] = 872,
        [anon_sym_AMP] = 872,
        [sym_string] = 872,
        [sym_identifier] = 872,
        [sym_number] = 872,
        [sym_comment] = 40,
    },
    [327] = {
        [sym__expression] = 874,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [328] = {
        [anon_sym_RBRACE] = 392,
        [anon_sym_COMMA] = 392,
        [anon_sym_EQ] = 798,
        [anon_sym_LPAREN] = 800,
        [anon_sym_STAR] = 802,
        [anon_sym_PLUS] = 804,
        [sym_comment] = 40,
    },
    [329] = {
        [anon_sym_RBRACE] = 876,
        [anon_sym_COMMA] = 876,
        [sym_comment] = 40,
    },
    [330] = {
        [aux_sym_declaration_repeat1] = 856,
        [anon_sym_COMMA] = 856,
        [anon_sym_SEMI] = 856,
        [sym_comment] = 40,
    },
    [331] = {
        [sym_initializer] = 858,
        [sym_designation] = 860,
        [sym__expression] = 746,
        [sym_cast_expression] = 748,
        [sym_math_expression] = 748,
        [sym_call_expression] = 748,
        [sym_pointer_expression] = 748,
        [sym_assignment_expression] = 748,
        [aux_sym_designation_repeat1] = 750,
        [anon_sym_LBRACE] = 752,
        [anon_sym_RBRACE] = 878,
        [anon_sym_LBRACK] = 754,
        [anon_sym_DOT] = 756,
        [anon_sym_LPAREN] = 758,
        [anon_sym_STAR] = 760,
        [anon_sym_AMP] = 760,
        [sym_string] = 748,
        [sym_identifier] = 762,
        [sym_number] = 748,
        [sym_comment] = 40,
    },
    [332] = {
        [aux_sym_declaration_repeat1] = 868,
        [anon_sym_COMMA] = 868,
        [anon_sym_SEMI] = 868,
        [sym_comment] = 40,
    },
    [333] = {
        [sym__expression] = 880,
        [sym_cast_expression] = 718,
        [sym_math_expression] = 718,
        [sym_call_expression] = 718,
        [sym_pointer_expression] = 718,
        [sym_assignment_expression] = 718,
        [anon_sym_LPAREN] = 722,
        [anon_sym_STAR] = 724,
        [anon_sym_AMP] = 724,
        [sym_string] = 718,
        [sym_identifier] = 726,
        [sym_number] = 718,
        [sym_comment] = 40,
    },
    [334] = {
        [aux_sym_declaration_repeat1] = 392,
        [anon_sym_COMMA] = 392,
        [anon_sym_SEMI] = 392,
        [anon_sym_EQ] = 732,
        [anon_sym_LPAREN] = 734,
        [anon_sym_STAR] = 736,
        [anon_sym_PLUS] = 738,
        [sym_comment] = 40,
    },
    [335] = {
        [aux_sym_declaration_repeat1] = 882,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 884,
        [sym_comment] = 40,
    },
    [336] = {
        [aux_sym_declaration_repeat1] = 882,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 884,
        [anon_sym_EQ] = 642,
        [anon_sym_LBRACK] = 886,
        [anon_sym_LPAREN] = 888,
        [sym_comment] = 40,
    },
    [337] = {
        [aux_sym_declaration_repeat1] = 196,
        [anon_sym_COMMA] = 196,
        [anon_sym_SEMI] = 196,
        [anon_sym_EQ] = 196,
        [anon_sym_LBRACK] = 196,
        [anon_sym_LPAREN] = 196,
        [sym_comment] = 40,
    },
    [338] = {
        [sym__declarator] = 890,
        [sym_pointer_declarator] = 200,
        [sym_function_declarator] = 200,
        [sym_array_declarator] = 200,
        [anon_sym_LPAREN] = 202,
        [anon_sym_STAR] = 204,
        [sym_identifier] = 200,
        [sym_comment] = 40,
    },
    [339] = {
        [sym__declarator] = 892,
        [sym_pointer_declarator] = 706,
        [sym_function_declarator] = 706,
        [sym_array_declarator] = 706,
        [anon_sym_LPAREN] = 708,
        [anon_sym_STAR] = 710,
        [sym_identifier] = 706,
        [sym_comment] = 40,
    },
    [340] = {
        [aux_sym_declaration_repeat1] = 208,
        [anon_sym_COMMA] = 208,
        [anon_sym_SEMI] = 208,
        [anon_sym_EQ] = 208,
        [anon_sym_LBRACK] = 886,
        [anon_sym_LPAREN] = 888,
        [sym_comment] = 40,
    },
    [341] = {
        [sym__expression] = 894,
        [sym_cast_expression] = 212,
        [sym_math_expression] = 212,
        [sym_call_expression] = 212,
        [sym_pointer_expression] = 212,
        [sym_assignment_expression] = 212,
        [anon_sym_RBRACK] = 896,
        [anon_sym_LPAREN] = 216,
        [anon_sym_STAR] = 218,
        [anon_sym_AMP] = 218,
        [sym_string] = 212,
        [sym_identifier] = 220,
        [sym_number] = 212,
        [sym_comment] = 40,
    },
    [342] = {
        [sym_declaration_specifiers] = 222,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 224,
        [sym_numeric_type_specifier] = 121,
        [sym_struct_specifier] = 121,
        [sym_parameter_declaration] = 898,
        [sym_type_qualifier] = 8,
        [sym_macro_type] = 121,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 125,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 129,
        [anon_sym_RPAREN] = 900,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [sym_identifier] = 133,
        [sym_comment] = 40,
    },
    [343] = {
        [aux_sym_function_declarator_repeat1] = 902,
        [anon_sym_COMMA] = 242,
        [anon_sym_RPAREN] = 904,
        [sym_comment] = 40,
    },
    [344] = {
        [aux_sym_declaration_repeat1] = 246,
        [anon_sym_COMMA] = 246,
        [anon_sym_SEMI] = 246,
        [anon_sym_EQ] = 246,
        [anon_sym_LBRACK] = 246,
        [anon_sym_LPAREN] = 246,
        [sym_comment] = 40,
    },
    [345] = {
        [anon_sym_RPAREN] = 906,
        [sym_comment] = 40,
    },
    [346] = {
        [aux_sym_declaration_repeat1] = 252,
        [anon_sym_COMMA] = 252,
        [anon_sym_SEMI] = 252,
        [anon_sym_EQ] = 252,
        [anon_sym_LBRACK] = 252,
        [anon_sym_LPAREN] = 252,
        [sym_comment] = 40,
    },
    [347] = {
        [aux_sym_declaration_repeat1] = 260,
        [anon_sym_COMMA] = 260,
        [anon_sym_SEMI] = 260,
        [anon_sym_EQ] = 260,
        [anon_sym_LBRACK] = 260,
        [anon_sym_LPAREN] = 260,
        [sym_comment] = 40,
    },
    [348] = {
        [anon_sym_EQ] = 286,
        [anon_sym_RBRACK] = 908,
        [anon_sym_LPAREN] = 290,
        [anon_sym_STAR] = 292,
        [anon_sym_PLUS] = 294,
        [sym_comment] = 40,
    },
    [349] = {
        [aux_sym_declaration_repeat1] = 298,
        [anon_sym_COMMA] = 298,
        [anon_sym_SEMI] = 298,
        [anon_sym_EQ] = 298,
        [anon_sym_LBRACK] = 298,
        [anon_sym_LPAREN] = 298,
        [sym_comment] = 40,
    },
    [350] = {
        [aux_sym_declaration_repeat1] = 562,
        [anon_sym_COMMA] = 562,
        [anon_sym_SEMI] = 562,
        [anon_sym_EQ] = 562,
        [anon_sym_LBRACK] = 562,
        [anon_sym_LPAREN] = 562,
        [sym_comment] = 40,
    },
    [351] = {
        [anon_sym_LBRACK] = 564,
        [anon_sym_LPAREN] = 566,
        [anon_sym_RPAREN] = 910,
        [sym_comment] = 40,
    },
    [352] = {
        [aux_sym_declaration_repeat1] = 592,
        [anon_sym_COMMA] = 592,
        [anon_sym_SEMI] = 592,
        [anon_sym_EQ] = 592,
        [anon_sym_LBRACK] = 592,
        [anon_sym_LPAREN] = 592,
        [sym_comment] = 40,
    },
    [353] = {
        [anon_sym_SEMI] = 912,
        [sym_comment] = 40,
    },
    [354] = {
        [sym__type_specifier] = 914,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_macro_type] = 12,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 30,
        [sym_identifier] = 34,
        [sym_comment] = 40,
    },
    [355] = {
        [sym__init_declarator] = 916,
        [sym__declarator] = 918,
        [sym_pointer_declarator] = 706,
        [sym_function_declarator] = 706,
        [sym_array_declarator] = 706,
        [anon_sym_LPAREN] = 708,
        [anon_sym_STAR] = 710,
        [sym_identifier] = 706,
        [sym_comment] = 40,
    },
    [356] = {
        [sym_declaration_specifiers] = 674,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 676,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 678,
        [sym_type_qualifier] = 8,
        [sym_compound_statement] = 680,
        [sym__expression] = 682,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [sym__statement] = 678,
        [sym_for_statement] = 680,
        [sym_expression_statement] = 680,
        [sym_macro_type] = 12,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [aux_sym_compound_statement_repeat1] = 920,
        [ts_builtin_sym_error] = 922,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 30,
        [anon_sym_LBRACE] = 690,
        [anon_sym_RBRACE] = 924,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [anon_sym_AMP] = 696,
        [anon_sym_for] = 698,
        [sym_string] = 684,
        [sym_identifier] = 700,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [357] = {
        [sym_declaration_specifiers] = 926,
        [sym_storage_class_specifier] = 926,
        [sym__type_specifier] = 926,
        [sym_numeric_type_specifier] = 926,
        [sym_struct_specifier] = 926,
        [sym_declaration] = 926,
        [sym_type_qualifier] = 926,
        [sym_compound_statement] = 926,
        [sym__expression] = 926,
        [sym_cast_expression] = 926,
        [sym_math_expression] = 926,
        [sym_call_expression] = 926,
        [sym_pointer_expression] = 926,
        [sym_assignment_expression] = 926,
        [sym__statement] = 926,
        [sym_for_statement] = 926,
        [sym_expression_statement] = 926,
        [sym_macro_type] = 926,
        [aux_sym_declaration_specifiers_repeat1] = 926,
        [aux_sym_numeric_type_specifier_repeat1] = 926,
        [aux_sym_compound_statement_repeat1] = 926,
        [ts_builtin_sym_error] = 926,
        [anon_sym_typedef] = 926,
        [anon_sym_extern] = 926,
        [anon_sym_static] = 926,
        [anon_sym_auto] = 926,
        [anon_sym_register] = 926,
        [anon_sym_signed] = 926,
        [anon_sym_unsigned] = 926,
        [anon_sym_long] = 926,
        [anon_sym_short] = 926,
        [anon_sym_struct] = 926,
        [anon_sym_LBRACE] = 926,
        [anon_sym_RBRACE] = 926,
        [anon_sym_LPAREN] = 926,
        [anon_sym_STAR] = 926,
        [anon_sym_const] = 926,
        [anon_sym_restrict] = 926,
        [anon_sym_volatile] = 926,
        [anon_sym_AMP] = 926,
        [anon_sym_for] = 926,
        [sym_string] = 926,
        [sym_identifier] = 926,
        [sym_number] = 926,
        [sym_comment] = 40,
    },
    [358] = {
        [anon_sym_SEMI] = 928,
        [anon_sym_EQ] = 930,
        [anon_sym_LPAREN] = 932,
        [anon_sym_STAR] = 934,
        [anon_sym_PLUS] = 936,
        [sym_comment] = 40,
    },
    [359] = {
        [anon_sym_SEMI] = 296,
        [anon_sym_EQ] = 296,
        [anon_sym_LPAREN] = 296,
        [anon_sym_STAR] = 296,
        [anon_sym_PLUS] = 296,
        [sym_comment] = 40,
    },
    [360] = {
        [anon_sym_RBRACE] = 938,
        [sym_comment] = 40,
    },
    [361] = {
        [anon_sym_RBRACE] = 938,
        [anon_sym_SEMI] = 940,
        [sym_comment] = 40,
    },
    [362] = {
        [sym_declaration_specifiers] = 674,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 676,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 678,
        [sym_type_qualifier] = 8,
        [sym_compound_statement] = 680,
        [sym__expression] = 682,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [sym__statement] = 678,
        [sym_for_statement] = 680,
        [sym_expression_statement] = 680,
        [sym_macro_type] = 12,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [aux_sym_compound_statement_repeat1] = 942,
        [ts_builtin_sym_error] = 944,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 30,
        [anon_sym_LBRACE] = 690,
        [anon_sym_RBRACE] = 946,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [anon_sym_AMP] = 696,
        [anon_sym_for] = 698,
        [sym_string] = 684,
        [sym_identifier] = 700,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [363] = {
        [sym_preproc_define] = 948,
        [sym_function_definition] = 948,
        [sym_declaration_specifiers] = 948,
        [sym_storage_class_specifier] = 948,
        [sym__type_specifier] = 948,
        [sym_numeric_type_specifier] = 948,
        [sym_struct_specifier] = 948,
        [sym_declaration] = 948,
        [sym_type_qualifier] = 948,
        [sym_macro_type] = 948,
        [aux_sym_translation_unit_repeat1] = 948,
        [aux_sym_declaration_specifiers_repeat1] = 948,
        [aux_sym_numeric_type_specifier_repeat1] = 948,
        [ts_builtin_sym_error] = 948,
        [ts_builtin_sym_end] = 948,
        [anon_sym_POUNDdefine] = 948,
        [anon_sym_typedef] = 948,
        [anon_sym_extern] = 948,
        [anon_sym_static] = 948,
        [anon_sym_auto] = 948,
        [anon_sym_register] = 948,
        [anon_sym_signed] = 948,
        [anon_sym_unsigned] = 948,
        [anon_sym_long] = 948,
        [anon_sym_short] = 948,
        [anon_sym_struct] = 948,
        [anon_sym_const] = 948,
        [anon_sym_restrict] = 948,
        [anon_sym_volatile] = 948,
        [sym_identifier] = 948,
        [sym_comment] = 40,
    },
    [364] = {
        [sym__type_specifier] = 300,
        [sym_numeric_type_specifier] = 302,
        [sym_struct_specifier] = 302,
        [sym_type_name] = 950,
        [sym_type_qualifier] = 306,
        [sym__expression] = 952,
        [sym_cast_expression] = 310,
        [sym_math_expression] = 310,
        [sym_call_expression] = 310,
        [sym_pointer_expression] = 310,
        [sym_assignment_expression] = 310,
        [sym_macro_type] = 302,
        [aux_sym_numeric_type_specifier_repeat1] = 312,
        [aux_sym_type_name_repeat1] = 314,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 316,
        [anon_sym_LPAREN] = 318,
        [anon_sym_STAR] = 320,
        [anon_sym_const] = 322,
        [anon_sym_restrict] = 322,
        [anon_sym_volatile] = 322,
        [anon_sym_AMP] = 320,
        [sym_string] = 310,
        [sym_identifier] = 324,
        [sym_number] = 310,
        [sym_comment] = 40,
    },
    [365] = {
        [sym__expression] = 954,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [366] = {
        [anon_sym_LPAREN] = 958,
        [sym_comment] = 40,
    },
    [367] = {
        [sym__init_declarator] = 86,
        [sym__declarator] = 86,
        [sym_pointer_declarator] = 86,
        [sym_function_declarator] = 86,
        [sym_array_declarator] = 86,
        [anon_sym_SEMI] = 328,
        [anon_sym_EQ] = 328,
        [anon_sym_LPAREN] = 960,
        [anon_sym_STAR] = 450,
        [anon_sym_PLUS] = 328,
        [sym_identifier] = 88,
        [sym_comment] = 40,
    },
    [368] = {
        [sym_declaration_specifiers] = 964,
        [sym_storage_class_specifier] = 8,
        [sym__type_specifier] = 966,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_declaration] = 968,
        [sym_type_qualifier] = 8,
        [sym__expression] = 970,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [sym_macro_type] = 12,
        [aux_sym_declaration_specifiers_repeat1] = 16,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [ts_builtin_sym_error] = 972,
        [anon_sym_typedef] = 26,
        [anon_sym_extern] = 26,
        [anon_sym_static] = 26,
        [anon_sym_auto] = 26,
        [anon_sym_register] = 26,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 30,
        [anon_sym_SEMI] = 968,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_const] = 32,
        [anon_sym_restrict] = 32,
        [anon_sym_volatile] = 32,
        [anon_sym_AMP] = 696,
        [sym_string] = 684,
        [sym_identifier] = 700,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [369] = {
        [sym__type_specifier] = 974,
        [sym_numeric_type_specifier] = 12,
        [sym_struct_specifier] = 12,
        [sym_macro_type] = 12,
        [aux_sym_numeric_type_specifier_repeat1] = 18,
        [anon_sym_signed] = 28,
        [anon_sym_unsigned] = 28,
        [anon_sym_long] = 28,
        [anon_sym_short] = 28,
        [anon_sym_struct] = 30,
        [sym_identifier] = 34,
        [sym_comment] = 40,
    },
    [370] = {
        [sym__init_declarator] = 976,
        [sym__declarator] = 978,
        [sym_pointer_declarator] = 706,
        [sym_function_declarator] = 706,
        [sym_array_declarator] = 706,
        [anon_sym_LPAREN] = 708,
        [anon_sym_STAR] = 710,
        [sym_identifier] = 706,
        [sym_comment] = 40,
    },
    [371] = {
        [sym__expression] = 980,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [anon_sym_SEMI] = 982,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [372] = {
        [anon_sym_SEMI] = 984,
        [anon_sym_EQ] = 930,
        [anon_sym_LPAREN] = 932,
        [anon_sym_STAR] = 934,
        [anon_sym_PLUS] = 936,
        [sym_comment] = 40,
    },
    [373] = {
        [anon_sym_SEMI] = 986,
        [sym_comment] = 40,
    },
    [374] = {
        [anon_sym_SEMI] = 988,
        [anon_sym_EQ] = 930,
        [anon_sym_LPAREN] = 932,
        [anon_sym_STAR] = 934,
        [anon_sym_PLUS] = 936,
        [sym_comment] = 40,
    },
    [375] = {
        [sym__expression] = 990,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_RPAREN] = 992,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [376] = {
        [anon_sym_SEMI] = 328,
        [anon_sym_EQ] = 328,
        [anon_sym_LPAREN] = 328,
        [anon_sym_STAR] = 328,
        [anon_sym_PLUS] = 328,
        [sym_comment] = 40,
    },
    [377] = {
        [aux_sym_call_expression_repeat1] = 994,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 996,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [378] = {
        [sym_compound_statement] = 680,
        [sym__expression] = 682,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [sym__statement] = 998,
        [sym_for_statement] = 680,
        [sym_expression_statement] = 680,
        [anon_sym_LBRACE] = 690,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [anon_sym_for] = 698,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [379] = {
        [sym_declaration_specifiers] = 1000,
        [sym_storage_class_specifier] = 1000,
        [sym__type_specifier] = 1000,
        [sym_numeric_type_specifier] = 1000,
        [sym_struct_specifier] = 1000,
        [sym_declaration] = 1000,
        [sym_type_qualifier] = 1000,
        [sym_compound_statement] = 1000,
        [sym__expression] = 1000,
        [sym_cast_expression] = 1000,
        [sym_math_expression] = 1000,
        [sym_call_expression] = 1000,
        [sym_pointer_expression] = 1000,
        [sym_assignment_expression] = 1000,
        [sym__statement] = 1000,
        [sym_for_statement] = 1000,
        [sym_expression_statement] = 1000,
        [sym_macro_type] = 1000,
        [aux_sym_declaration_specifiers_repeat1] = 1000,
        [aux_sym_numeric_type_specifier_repeat1] = 1000,
        [aux_sym_compound_statement_repeat1] = 1000,
        [ts_builtin_sym_error] = 1000,
        [anon_sym_typedef] = 1000,
        [anon_sym_extern] = 1000,
        [anon_sym_static] = 1000,
        [anon_sym_auto] = 1000,
        [anon_sym_register] = 1000,
        [anon_sym_signed] = 1000,
        [anon_sym_unsigned] = 1000,
        [anon_sym_long] = 1000,
        [anon_sym_short] = 1000,
        [anon_sym_struct] = 1000,
        [anon_sym_LBRACE] = 1000,
        [anon_sym_RBRACE] = 1000,
        [anon_sym_LPAREN] = 1000,
        [anon_sym_STAR] = 1000,
        [anon_sym_const] = 1000,
        [anon_sym_restrict] = 1000,
        [anon_sym_volatile] = 1000,
        [anon_sym_AMP] = 1000,
        [anon_sym_for] = 1000,
        [sym_string] = 1000,
        [sym_identifier] = 1000,
        [sym_number] = 1000,
        [sym_comment] = 40,
    },
    [380] = {
        [anon_sym_RPAREN] = 1002,
        [sym_comment] = 40,
    },
    [381] = {
        [sym_compound_statement] = 680,
        [sym__expression] = 682,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [sym__statement] = 1004,
        [sym_for_statement] = 680,
        [sym_expression_statement] = 680,
        [anon_sym_LBRACE] = 690,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [anon_sym_for] = 698,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [382] = {
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
        [sym_comment] = 40,
    },
    [383] = {
        [sym_compound_statement] = 680,
        [sym__expression] = 682,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [sym__statement] = 1008,
        [sym_for_statement] = 680,
        [sym_expression_statement] = 680,
        [anon_sym_LBRACE] = 690,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [anon_sym_for] = 698,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [384] = {
        [sym_declaration_specifiers] = 1010,
        [sym_storage_class_specifier] = 1010,
        [sym__type_specifier] = 1010,
        [sym_numeric_type_specifier] = 1010,
        [sym_struct_specifier] = 1010,
        [sym_declaration] = 1010,
        [sym_type_qualifier] = 1010,
        [sym_compound_statement] = 1010,
        [sym__expression] = 1010,
        [sym_cast_expression] = 1010,
        [sym_math_expression] = 1010,
        [sym_call_expression] = 1010,
        [sym_pointer_expression] = 1010,
        [sym_assignment_expression] = 1010,
        [sym__statement] = 1010,
        [sym_for_statement] = 1010,
        [sym_expression_statement] = 1010,
        [sym_macro_type] = 1010,
        [aux_sym_declaration_specifiers_repeat1] = 1010,
        [aux_sym_numeric_type_specifier_repeat1] = 1010,
        [aux_sym_compound_statement_repeat1] = 1010,
        [ts_builtin_sym_error] = 1010,
        [anon_sym_typedef] = 1010,
        [anon_sym_extern] = 1010,
        [anon_sym_static] = 1010,
        [anon_sym_auto] = 1010,
        [anon_sym_register] = 1010,
        [anon_sym_signed] = 1010,
        [anon_sym_unsigned] = 1010,
        [anon_sym_long] = 1010,
        [anon_sym_short] = 1010,
        [anon_sym_struct] = 1010,
        [anon_sym_LBRACE] = 1010,
        [anon_sym_RBRACE] = 1010,
        [anon_sym_LPAREN] = 1010,
        [anon_sym_STAR] = 1010,
        [anon_sym_const] = 1010,
        [anon_sym_restrict] = 1010,
        [anon_sym_volatile] = 1010,
        [anon_sym_AMP] = 1010,
        [anon_sym_for] = 1010,
        [sym_string] = 1010,
        [sym_identifier] = 1010,
        [sym_number] = 1010,
        [sym_comment] = 40,
    },
    [385] = {
        [sym__expression] = 1012,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_RPAREN] = 996,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [386] = {
        [sym__expression] = 1014,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [387] = {
        [sym__expression] = 1016,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_RPAREN] = 1018,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [388] = {
        [sym__expression] = 1020,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [389] = {
        [sym__expression] = 1022,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [390] = {
        [anon_sym_SEMI] = 348,
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 932,
        [anon_sym_STAR] = 934,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [391] = {
        [anon_sym_SEMI] = 348,
        [anon_sym_EQ] = 348,
        [anon_sym_LPAREN] = 932,
        [anon_sym_STAR] = 348,
        [anon_sym_PLUS] = 348,
        [sym_comment] = 40,
    },
    [392] = {
        [aux_sym_call_expression_repeat1] = 1024,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 1026,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [393] = {
        [anon_sym_SEMI] = 368,
        [anon_sym_EQ] = 368,
        [anon_sym_LPAREN] = 368,
        [anon_sym_STAR] = 368,
        [anon_sym_PLUS] = 368,
        [sym_comment] = 40,
    },
    [394] = {
        [anon_sym_RPAREN] = 1028,
        [sym_comment] = 40,
    },
    [395] = {
        [anon_sym_SEMI] = 390,
        [anon_sym_EQ] = 390,
        [anon_sym_LPAREN] = 390,
        [anon_sym_STAR] = 390,
        [anon_sym_PLUS] = 390,
        [sym_comment] = 40,
    },
    [396] = {
        [anon_sym_SEMI] = 400,
        [anon_sym_EQ] = 400,
        [anon_sym_LPAREN] = 400,
        [anon_sym_STAR] = 400,
        [anon_sym_PLUS] = 400,
        [sym_comment] = 40,
    },
    [397] = {
        [anon_sym_SEMI] = 392,
        [anon_sym_EQ] = 930,
        [anon_sym_LPAREN] = 932,
        [anon_sym_STAR] = 934,
        [anon_sym_PLUS] = 936,
        [sym_comment] = 40,
    },
    [398] = {
        [aux_sym_call_expression_repeat1] = 1030,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 1002,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [399] = {
        [anon_sym_RPAREN] = 1032,
        [sym_comment] = 40,
    },
    [400] = {
        [sym_compound_statement] = 680,
        [sym__expression] = 682,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [sym__statement] = 1034,
        [sym_for_statement] = 680,
        [sym_expression_statement] = 680,
        [anon_sym_LBRACE] = 690,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [anon_sym_for] = 698,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [401] = {
        [sym_declaration_specifiers] = 1036,
        [sym_storage_class_specifier] = 1036,
        [sym__type_specifier] = 1036,
        [sym_numeric_type_specifier] = 1036,
        [sym_struct_specifier] = 1036,
        [sym_declaration] = 1036,
        [sym_type_qualifier] = 1036,
        [sym_compound_statement] = 1036,
        [sym__expression] = 1036,
        [sym_cast_expression] = 1036,
        [sym_math_expression] = 1036,
        [sym_call_expression] = 1036,
        [sym_pointer_expression] = 1036,
        [sym_assignment_expression] = 1036,
        [sym__statement] = 1036,
        [sym_for_statement] = 1036,
        [sym_expression_statement] = 1036,
        [sym_macro_type] = 1036,
        [aux_sym_declaration_specifiers_repeat1] = 1036,
        [aux_sym_numeric_type_specifier_repeat1] = 1036,
        [aux_sym_compound_statement_repeat1] = 1036,
        [ts_builtin_sym_error] = 1036,
        [anon_sym_typedef] = 1036,
        [anon_sym_extern] = 1036,
        [anon_sym_static] = 1036,
        [anon_sym_auto] = 1036,
        [anon_sym_register] = 1036,
        [anon_sym_signed] = 1036,
        [anon_sym_unsigned] = 1036,
        [anon_sym_long] = 1036,
        [anon_sym_short] = 1036,
        [anon_sym_struct] = 1036,
        [anon_sym_LBRACE] = 1036,
        [anon_sym_RBRACE] = 1036,
        [anon_sym_LPAREN] = 1036,
        [anon_sym_STAR] = 1036,
        [anon_sym_const] = 1036,
        [anon_sym_restrict] = 1036,
        [anon_sym_volatile] = 1036,
        [anon_sym_AMP] = 1036,
        [anon_sym_for] = 1036,
        [sym_string] = 1036,
        [sym_identifier] = 1036,
        [sym_number] = 1036,
        [sym_comment] = 40,
    },
    [402] = {
        [sym__expression] = 626,
        [sym_cast_expression] = 626,
        [sym_math_expression] = 626,
        [sym_call_expression] = 626,
        [sym_pointer_expression] = 626,
        [sym_assignment_expression] = 626,
        [anon_sym_SEMI] = 626,
        [anon_sym_LPAREN] = 626,
        [anon_sym_STAR] = 626,
        [anon_sym_AMP] = 626,
        [sym_string] = 626,
        [sym_identifier] = 626,
        [sym_number] = 626,
        [sym_comment] = 40,
    },
    [403] = {
        [sym__expression] = 1038,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [anon_sym_SEMI] = 988,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [404] = {
        [anon_sym_SEMI] = 1040,
        [anon_sym_EQ] = 930,
        [anon_sym_LPAREN] = 932,
        [anon_sym_STAR] = 934,
        [anon_sym_PLUS] = 936,
        [sym_comment] = 40,
    },
    [405] = {
        [sym__expression] = 1042,
        [sym_cast_expression] = 334,
        [sym_math_expression] = 334,
        [sym_call_expression] = 334,
        [sym_pointer_expression] = 334,
        [sym_assignment_expression] = 334,
        [anon_sym_LPAREN] = 336,
        [anon_sym_RPAREN] = 1002,
        [anon_sym_STAR] = 340,
        [anon_sym_AMP] = 340,
        [sym_string] = 334,
        [sym_identifier] = 342,
        [sym_number] = 334,
        [sym_comment] = 40,
    },
    [406] = {
        [aux_sym_call_expression_repeat1] = 1044,
        [anon_sym_COMMA] = 352,
        [anon_sym_EQ] = 354,
        [anon_sym_LPAREN] = 356,
        [anon_sym_RPAREN] = 1032,
        [anon_sym_STAR] = 360,
        [anon_sym_PLUS] = 362,
        [sym_comment] = 40,
    },
    [407] = {
        [anon_sym_RPAREN] = 1046,
        [sym_comment] = 40,
    },
    [408] = {
        [sym_compound_statement] = 680,
        [sym__expression] = 682,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [sym__statement] = 1048,
        [sym_for_statement] = 680,
        [sym_expression_statement] = 680,
        [anon_sym_LBRACE] = 690,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [anon_sym_for] = 698,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [409] = {
        [sym_declaration_specifiers] = 1050,
        [sym_storage_class_specifier] = 1050,
        [sym__type_specifier] = 1050,
        [sym_numeric_type_specifier] = 1050,
        [sym_struct_specifier] = 1050,
        [sym_declaration] = 1050,
        [sym_type_qualifier] = 1050,
        [sym_compound_statement] = 1050,
        [sym__expression] = 1050,
        [sym_cast_expression] = 1050,
        [sym_math_expression] = 1050,
        [sym_call_expression] = 1050,
        [sym_pointer_expression] = 1050,
        [sym_assignment_expression] = 1050,
        [sym__statement] = 1050,
        [sym_for_statement] = 1050,
        [sym_expression_statement] = 1050,
        [sym_macro_type] = 1050,
        [aux_sym_declaration_specifiers_repeat1] = 1050,
        [aux_sym_numeric_type_specifier_repeat1] = 1050,
        [aux_sym_compound_statement_repeat1] = 1050,
        [ts_builtin_sym_error] = 1050,
        [anon_sym_typedef] = 1050,
        [anon_sym_extern] = 1050,
        [anon_sym_static] = 1050,
        [anon_sym_auto] = 1050,
        [anon_sym_register] = 1050,
        [anon_sym_signed] = 1050,
        [anon_sym_unsigned] = 1050,
        [anon_sym_long] = 1050,
        [anon_sym_short] = 1050,
        [anon_sym_struct] = 1050,
        [anon_sym_LBRACE] = 1050,
        [anon_sym_RBRACE] = 1050,
        [anon_sym_LPAREN] = 1050,
        [anon_sym_STAR] = 1050,
        [anon_sym_const] = 1050,
        [anon_sym_restrict] = 1050,
        [anon_sym_volatile] = 1050,
        [anon_sym_AMP] = 1050,
        [anon_sym_for] = 1050,
        [sym_string] = 1050,
        [sym_identifier] = 1050,
        [sym_number] = 1050,
        [sym_comment] = 40,
    },
    [410] = {
        [aux_sym_declaration_repeat1] = 1052,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 1054,
        [sym_comment] = 40,
    },
    [411] = {
        [aux_sym_declaration_repeat1] = 1052,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 1054,
        [anon_sym_EQ] = 642,
        [anon_sym_LBRACK] = 886,
        [anon_sym_LPAREN] = 888,
        [sym_comment] = 40,
    },
    [412] = {
        [anon_sym_SEMI] = 1056,
        [sym_comment] = 40,
    },
    [413] = {
        [sym__expression] = 712,
        [sym_cast_expression] = 712,
        [sym_math_expression] = 712,
        [sym_call_expression] = 712,
        [sym_pointer_expression] = 712,
        [sym_assignment_expression] = 712,
        [anon_sym_SEMI] = 712,
        [anon_sym_LPAREN] = 712,
        [anon_sym_STAR] = 712,
        [anon_sym_AMP] = 712,
        [sym_string] = 712,
        [sym_identifier] = 712,
        [sym_number] = 712,
        [sym_comment] = 40,
    },
    [414] = {
        [sym__expression] = 1058,
        [sym_cast_expression] = 1058,
        [sym_math_expression] = 1058,
        [sym_call_expression] = 1058,
        [sym_pointer_expression] = 1058,
        [sym_assignment_expression] = 1058,
        [anon_sym_SEMI] = 1058,
        [anon_sym_LPAREN] = 1058,
        [anon_sym_STAR] = 1058,
        [anon_sym_AMP] = 1058,
        [sym_string] = 1058,
        [sym_identifier] = 1058,
        [sym_number] = 1058,
        [sym_comment] = 40,
    },
    [415] = {
        [sym__init_declarator] = 1060,
        [sym__declarator] = 1062,
        [sym_pointer_declarator] = 706,
        [sym_function_declarator] = 706,
        [sym_array_declarator] = 706,
        [anon_sym_LPAREN] = 708,
        [anon_sym_STAR] = 710,
        [sym_identifier] = 706,
        [sym_comment] = 40,
    },
    [416] = {
        [aux_sym_declaration_repeat1] = 1064,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 1056,
        [sym_comment] = 40,
    },
    [417] = {
        [aux_sym_declaration_repeat1] = 1064,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 1056,
        [anon_sym_EQ] = 642,
        [anon_sym_LBRACK] = 886,
        [anon_sym_LPAREN] = 888,
        [sym_comment] = 40,
    },
    [418] = {
        [anon_sym_SEMI] = 1066,
        [sym_comment] = 40,
    },
    [419] = {
        [sym__expression] = 1068,
        [sym_cast_expression] = 1068,
        [sym_math_expression] = 1068,
        [sym_call_expression] = 1068,
        [sym_pointer_expression] = 1068,
        [sym_assignment_expression] = 1068,
        [anon_sym_SEMI] = 1068,
        [anon_sym_LPAREN] = 1068,
        [anon_sym_STAR] = 1068,
        [anon_sym_AMP] = 1068,
        [sym_string] = 1068,
        [sym_identifier] = 1068,
        [sym_number] = 1068,
        [sym_comment] = 40,
    },
    [420] = {
        [anon_sym_SEMI] = 330,
        [anon_sym_EQ] = 330,
        [anon_sym_LPAREN] = 932,
        [anon_sym_STAR] = 934,
        [anon_sym_PLUS] = 936,
        [sym_comment] = 40,
    },
    [421] = {
        [anon_sym_RPAREN] = 1070,
        [sym_comment] = 40,
    },
    [422] = {
        [anon_sym_EQ] = 418,
        [anon_sym_LPAREN] = 420,
        [anon_sym_RPAREN] = 1072,
        [anon_sym_STAR] = 424,
        [anon_sym_PLUS] = 426,
        [sym_comment] = 40,
    },
    [423] = {
        [anon_sym_SEMI] = 477,
        [anon_sym_EQ] = 477,
        [anon_sym_LPAREN] = 477,
        [anon_sym_STAR] = 477,
        [anon_sym_PLUS] = 477,
        [sym_comment] = 40,
    },
    [424] = {
        [sym__expression] = 1074,
        [sym_cast_expression] = 684,
        [sym_math_expression] = 684,
        [sym_call_expression] = 684,
        [sym_pointer_expression] = 684,
        [sym_assignment_expression] = 684,
        [anon_sym_LPAREN] = 694,
        [anon_sym_STAR] = 696,
        [anon_sym_AMP] = 696,
        [sym_string] = 684,
        [sym_identifier] = 956,
        [sym_number] = 684,
        [sym_comment] = 40,
    },
    [425] = {
        [anon_sym_SEMI] = 481,
        [anon_sym_EQ] = 481,
        [anon_sym_LPAREN] = 481,
        [anon_sym_STAR] = 481,
        [anon_sym_PLUS] = 481,
        [sym_comment] = 40,
    },
    [426] = {
        [anon_sym_RBRACE] = 1076,
        [sym_comment] = 40,
    },
    [427] = {
        [anon_sym_RBRACE] = 1076,
        [anon_sym_SEMI] = 940,
        [sym_comment] = 40,
    },
    [428] = {
        [sym_declaration_specifiers] = 948,
        [sym_storage_class_specifier] = 948,
        [sym__type_specifier] = 948,
        [sym_numeric_type_specifier] = 948,
        [sym_struct_specifier] = 948,
        [sym_declaration] = 948,
        [sym_type_qualifier] = 948,
        [sym_compound_statement] = 948,
        [sym__expression] = 948,
        [sym_cast_expression] = 948,
        [sym_math_expression] = 948,
        [sym_call_expression] = 948,
        [sym_pointer_expression] = 948,
        [sym_assignment_expression] = 948,
        [sym__statement] = 948,
        [sym_for_statement] = 948,
        [sym_expression_statement] = 948,
        [sym_macro_type] = 948,
        [aux_sym_declaration_specifiers_repeat1] = 948,
        [aux_sym_numeric_type_specifier_repeat1] = 948,
        [aux_sym_compound_statement_repeat1] = 948,
        [ts_builtin_sym_error] = 948,
        [anon_sym_typedef] = 948,
        [anon_sym_extern] = 948,
        [anon_sym_static] = 948,
        [anon_sym_auto] = 948,
        [anon_sym_register] = 948,
        [anon_sym_signed] = 948,
        [anon_sym_unsigned] = 948,
        [anon_sym_long] = 948,
        [anon_sym_short] = 948,
        [anon_sym_struct] = 948,
        [anon_sym_LBRACE] = 948,
        [anon_sym_RBRACE] = 948,
        [anon_sym_LPAREN] = 948,
        [anon_sym_STAR] = 948,
        [anon_sym_const] = 948,
        [anon_sym_restrict] = 948,
        [anon_sym_volatile] = 948,
        [anon_sym_AMP] = 948,
        [anon_sym_for] = 948,
        [sym_string] = 948,
        [sym_identifier] = 948,
        [sym_number] = 948,
        [sym_comment] = 40,
    },
    [429] = {
        [sym_declaration_specifiers] = 1078,
        [sym_storage_class_specifier] = 1078,
        [sym__type_specifier] = 1078,
        [sym_numeric_type_specifier] = 1078,
        [sym_struct_specifier] = 1078,
        [sym_declaration] = 1078,
        [sym_type_qualifier] = 1078,
        [sym_compound_statement] = 1078,
        [sym__expression] = 1078,
        [sym_cast_expression] = 1078,
        [sym_math_expression] = 1078,
        [sym_call_expression] = 1078,
        [sym_pointer_expression] = 1078,
        [sym_assignment_expression] = 1078,
        [sym__statement] = 1078,
        [sym_for_statement] = 1078,
        [sym_expression_statement] = 1078,
        [sym_macro_type] = 1078,
        [aux_sym_declaration_specifiers_repeat1] = 1078,
        [aux_sym_numeric_type_specifier_repeat1] = 1078,
        [aux_sym_compound_statement_repeat1] = 1078,
        [ts_builtin_sym_error] = 1078,
        [anon_sym_typedef] = 1078,
        [anon_sym_extern] = 1078,
        [anon_sym_static] = 1078,
        [anon_sym_auto] = 1078,
        [anon_sym_register] = 1078,
        [anon_sym_signed] = 1078,
        [anon_sym_unsigned] = 1078,
        [anon_sym_long] = 1078,
        [anon_sym_short] = 1078,
        [anon_sym_struct] = 1078,
        [anon_sym_LBRACE] = 1078,
        [anon_sym_RBRACE] = 1078,
        [anon_sym_LPAREN] = 1078,
        [anon_sym_STAR] = 1078,
        [anon_sym_const] = 1078,
        [anon_sym_restrict] = 1078,
        [anon_sym_volatile] = 1078,
        [anon_sym_AMP] = 1078,
        [anon_sym_for] = 1078,
        [sym_string] = 1078,
        [sym_identifier] = 1078,
        [sym_number] = 1078,
        [sym_comment] = 40,
    },
    [430] = {
        [sym_declaration_specifiers] = 626,
        [sym_storage_class_specifier] = 626,
        [sym__type_specifier] = 626,
        [sym_numeric_type_specifier] = 626,
        [sym_struct_specifier] = 626,
        [sym_declaration] = 626,
        [sym_type_qualifier] = 626,
        [sym_compound_statement] = 626,
        [sym__expression] = 626,
        [sym_cast_expression] = 626,
        [sym_math_expression] = 626,
        [sym_call_expression] = 626,
        [sym_pointer_expression] = 626,
        [sym_assignment_expression] = 626,
        [sym__statement] = 626,
        [sym_for_statement] = 626,
        [sym_expression_statement] = 626,
        [sym_macro_type] = 626,
        [aux_sym_declaration_specifiers_repeat1] = 626,
        [aux_sym_numeric_type_specifier_repeat1] = 626,
        [aux_sym_compound_statement_repeat1] = 626,
        [ts_builtin_sym_error] = 626,
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
        [anon_sym_LBRACE] = 626,
        [anon_sym_RBRACE] = 626,
        [anon_sym_LPAREN] = 626,
        [anon_sym_STAR] = 626,
        [anon_sym_const] = 626,
        [anon_sym_restrict] = 626,
        [anon_sym_volatile] = 626,
        [anon_sym_AMP] = 626,
        [anon_sym_for] = 626,
        [sym_string] = 626,
        [sym_identifier] = 626,
        [sym_number] = 626,
        [sym_comment] = 40,
    },
    [431] = {
        [sym_preproc_define] = 1078,
        [sym_function_definition] = 1078,
        [sym_declaration_specifiers] = 1078,
        [sym_storage_class_specifier] = 1078,
        [sym__type_specifier] = 1078,
        [sym_numeric_type_specifier] = 1078,
        [sym_struct_specifier] = 1078,
        [sym_declaration] = 1078,
        [sym_type_qualifier] = 1078,
        [sym_macro_type] = 1078,
        [aux_sym_translation_unit_repeat1] = 1078,
        [aux_sym_declaration_specifiers_repeat1] = 1078,
        [aux_sym_numeric_type_specifier_repeat1] = 1078,
        [ts_builtin_sym_error] = 1078,
        [ts_builtin_sym_end] = 1078,
        [anon_sym_POUNDdefine] = 1078,
        [anon_sym_typedef] = 1078,
        [anon_sym_extern] = 1078,
        [anon_sym_static] = 1078,
        [anon_sym_auto] = 1078,
        [anon_sym_register] = 1078,
        [anon_sym_signed] = 1078,
        [anon_sym_unsigned] = 1078,
        [anon_sym_long] = 1078,
        [anon_sym_short] = 1078,
        [anon_sym_struct] = 1078,
        [anon_sym_const] = 1078,
        [anon_sym_restrict] = 1078,
        [anon_sym_volatile] = 1078,
        [sym_identifier] = 1078,
        [sym_comment] = 40,
    },
    [432] = {
        [anon_sym_RBRACE] = 1080,
        [sym_comment] = 40,
    },
    [433] = {
        [anon_sym_SEMI] = 940,
        [sym_comment] = 40,
    },
    [434] = {
        [sym_declaration_specifiers] = 1082,
        [sym_storage_class_specifier] = 1082,
        [sym__type_specifier] = 1082,
        [sym_numeric_type_specifier] = 1082,
        [sym_struct_specifier] = 1082,
        [sym_declaration] = 1082,
        [sym_type_qualifier] = 1082,
        [sym_compound_statement] = 1082,
        [sym__expression] = 1082,
        [sym_cast_expression] = 1082,
        [sym_math_expression] = 1082,
        [sym_call_expression] = 1082,
        [sym_pointer_expression] = 1082,
        [sym_assignment_expression] = 1082,
        [sym__statement] = 1082,
        [sym_for_statement] = 1082,
        [sym_expression_statement] = 1082,
        [sym_macro_type] = 1082,
        [aux_sym_declaration_specifiers_repeat1] = 1082,
        [aux_sym_numeric_type_specifier_repeat1] = 1082,
        [aux_sym_compound_statement_repeat1] = 1082,
        [ts_builtin_sym_error] = 1082,
        [anon_sym_typedef] = 1082,
        [anon_sym_extern] = 1082,
        [anon_sym_static] = 1082,
        [anon_sym_auto] = 1082,
        [anon_sym_register] = 1082,
        [anon_sym_signed] = 1082,
        [anon_sym_unsigned] = 1082,
        [anon_sym_long] = 1082,
        [anon_sym_short] = 1082,
        [anon_sym_struct] = 1082,
        [anon_sym_LBRACE] = 1082,
        [anon_sym_RBRACE] = 1082,
        [anon_sym_LPAREN] = 1082,
        [anon_sym_STAR] = 1082,
        [anon_sym_const] = 1082,
        [anon_sym_restrict] = 1082,
        [anon_sym_volatile] = 1082,
        [anon_sym_AMP] = 1082,
        [anon_sym_for] = 1082,
        [sym_string] = 1082,
        [sym_identifier] = 1082,
        [sym_number] = 1082,
        [sym_comment] = 40,
    },
    [435] = {
        [aux_sym_declaration_repeat1] = 1084,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 1086,
        [sym_comment] = 40,
    },
    [436] = {
        [aux_sym_declaration_repeat1] = 1084,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 1086,
        [anon_sym_EQ] = 642,
        [anon_sym_LBRACK] = 886,
        [anon_sym_LPAREN] = 888,
        [sym_comment] = 40,
    },
    [437] = {
        [anon_sym_SEMI] = 1088,
        [sym_comment] = 40,
    },
    [438] = {
        [sym_declaration_specifiers] = 712,
        [sym_storage_class_specifier] = 712,
        [sym__type_specifier] = 712,
        [sym_numeric_type_specifier] = 712,
        [sym_struct_specifier] = 712,
        [sym_declaration] = 712,
        [sym_type_qualifier] = 712,
        [sym_compound_statement] = 712,
        [sym__expression] = 712,
        [sym_cast_expression] = 712,
        [sym_math_expression] = 712,
        [sym_call_expression] = 712,
        [sym_pointer_expression] = 712,
        [sym_assignment_expression] = 712,
        [sym__statement] = 712,
        [sym_for_statement] = 712,
        [sym_expression_statement] = 712,
        [sym_macro_type] = 712,
        [aux_sym_declaration_specifiers_repeat1] = 712,
        [aux_sym_numeric_type_specifier_repeat1] = 712,
        [aux_sym_compound_statement_repeat1] = 712,
        [ts_builtin_sym_error] = 712,
        [anon_sym_typedef] = 712,
        [anon_sym_extern] = 712,
        [anon_sym_static] = 712,
        [anon_sym_auto] = 712,
        [anon_sym_register] = 712,
        [anon_sym_signed] = 712,
        [anon_sym_unsigned] = 712,
        [anon_sym_long] = 712,
        [anon_sym_short] = 712,
        [anon_sym_struct] = 712,
        [anon_sym_LBRACE] = 712,
        [anon_sym_RBRACE] = 712,
        [anon_sym_LPAREN] = 712,
        [anon_sym_STAR] = 712,
        [anon_sym_const] = 712,
        [anon_sym_restrict] = 712,
        [anon_sym_volatile] = 712,
        [anon_sym_AMP] = 712,
        [anon_sym_for] = 712,
        [sym_string] = 712,
        [sym_identifier] = 712,
        [sym_number] = 712,
        [sym_comment] = 40,
    },
    [439] = {
        [sym_declaration_specifiers] = 1058,
        [sym_storage_class_specifier] = 1058,
        [sym__type_specifier] = 1058,
        [sym_numeric_type_specifier] = 1058,
        [sym_struct_specifier] = 1058,
        [sym_declaration] = 1058,
        [sym_type_qualifier] = 1058,
        [sym_compound_statement] = 1058,
        [sym__expression] = 1058,
        [sym_cast_expression] = 1058,
        [sym_math_expression] = 1058,
        [sym_call_expression] = 1058,
        [sym_pointer_expression] = 1058,
        [sym_assignment_expression] = 1058,
        [sym__statement] = 1058,
        [sym_for_statement] = 1058,
        [sym_expression_statement] = 1058,
        [sym_macro_type] = 1058,
        [aux_sym_declaration_specifiers_repeat1] = 1058,
        [aux_sym_numeric_type_specifier_repeat1] = 1058,
        [aux_sym_compound_statement_repeat1] = 1058,
        [ts_builtin_sym_error] = 1058,
        [anon_sym_typedef] = 1058,
        [anon_sym_extern] = 1058,
        [anon_sym_static] = 1058,
        [anon_sym_auto] = 1058,
        [anon_sym_register] = 1058,
        [anon_sym_signed] = 1058,
        [anon_sym_unsigned] = 1058,
        [anon_sym_long] = 1058,
        [anon_sym_short] = 1058,
        [anon_sym_struct] = 1058,
        [anon_sym_LBRACE] = 1058,
        [anon_sym_RBRACE] = 1058,
        [anon_sym_LPAREN] = 1058,
        [anon_sym_STAR] = 1058,
        [anon_sym_const] = 1058,
        [anon_sym_restrict] = 1058,
        [anon_sym_volatile] = 1058,
        [anon_sym_AMP] = 1058,
        [anon_sym_for] = 1058,
        [sym_string] = 1058,
        [sym_identifier] = 1058,
        [sym_number] = 1058,
        [sym_comment] = 40,
    },
    [440] = {
        [sym__init_declarator] = 1090,
        [sym__declarator] = 1092,
        [sym_pointer_declarator] = 706,
        [sym_function_declarator] = 706,
        [sym_array_declarator] = 706,
        [anon_sym_LPAREN] = 708,
        [anon_sym_STAR] = 710,
        [sym_identifier] = 706,
        [sym_comment] = 40,
    },
    [441] = {
        [aux_sym_declaration_repeat1] = 1094,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 1088,
        [sym_comment] = 40,
    },
    [442] = {
        [aux_sym_declaration_repeat1] = 1094,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 1088,
        [anon_sym_EQ] = 642,
        [anon_sym_LBRACK] = 886,
        [anon_sym_LPAREN] = 888,
        [sym_comment] = 40,
    },
    [443] = {
        [anon_sym_SEMI] = 1096,
        [sym_comment] = 40,
    },
    [444] = {
        [sym_declaration_specifiers] = 1068,
        [sym_storage_class_specifier] = 1068,
        [sym__type_specifier] = 1068,
        [sym_numeric_type_specifier] = 1068,
        [sym_struct_specifier] = 1068,
        [sym_declaration] = 1068,
        [sym_type_qualifier] = 1068,
        [sym_compound_statement] = 1068,
        [sym__expression] = 1068,
        [sym_cast_expression] = 1068,
        [sym_math_expression] = 1068,
        [sym_call_expression] = 1068,
        [sym_pointer_expression] = 1068,
        [sym_assignment_expression] = 1068,
        [sym__statement] = 1068,
        [sym_for_statement] = 1068,
        [sym_expression_statement] = 1068,
        [sym_macro_type] = 1068,
        [aux_sym_declaration_specifiers_repeat1] = 1068,
        [aux_sym_numeric_type_specifier_repeat1] = 1068,
        [aux_sym_compound_statement_repeat1] = 1068,
        [ts_builtin_sym_error] = 1068,
        [anon_sym_typedef] = 1068,
        [anon_sym_extern] = 1068,
        [anon_sym_static] = 1068,
        [anon_sym_auto] = 1068,
        [anon_sym_register] = 1068,
        [anon_sym_signed] = 1068,
        [anon_sym_unsigned] = 1068,
        [anon_sym_long] = 1068,
        [anon_sym_short] = 1068,
        [anon_sym_struct] = 1068,
        [anon_sym_LBRACE] = 1068,
        [anon_sym_RBRACE] = 1068,
        [anon_sym_LPAREN] = 1068,
        [anon_sym_STAR] = 1068,
        [anon_sym_const] = 1068,
        [anon_sym_restrict] = 1068,
        [anon_sym_volatile] = 1068,
        [anon_sym_AMP] = 1068,
        [anon_sym_for] = 1068,
        [sym_string] = 1068,
        [sym_identifier] = 1068,
        [sym_number] = 1068,
        [sym_comment] = 40,
    },
    [445] = {
        [sym_preproc_define] = 1058,
        [sym_function_definition] = 1058,
        [sym_declaration_specifiers] = 1058,
        [sym_storage_class_specifier] = 1058,
        [sym__type_specifier] = 1058,
        [sym_numeric_type_specifier] = 1058,
        [sym_struct_specifier] = 1058,
        [sym_declaration] = 1058,
        [sym_type_qualifier] = 1058,
        [sym_macro_type] = 1058,
        [aux_sym_translation_unit_repeat1] = 1058,
        [aux_sym_declaration_specifiers_repeat1] = 1058,
        [aux_sym_numeric_type_specifier_repeat1] = 1058,
        [ts_builtin_sym_error] = 1058,
        [ts_builtin_sym_end] = 1058,
        [anon_sym_POUNDdefine] = 1058,
        [anon_sym_typedef] = 1058,
        [anon_sym_extern] = 1058,
        [anon_sym_static] = 1058,
        [anon_sym_auto] = 1058,
        [anon_sym_register] = 1058,
        [anon_sym_signed] = 1058,
        [anon_sym_unsigned] = 1058,
        [anon_sym_long] = 1058,
        [anon_sym_short] = 1058,
        [anon_sym_struct] = 1058,
        [anon_sym_const] = 1058,
        [anon_sym_restrict] = 1058,
        [anon_sym_volatile] = 1058,
        [sym_identifier] = 1058,
        [sym_comment] = 40,
    },
    [446] = {
        [sym__init_declarator] = 1098,
        [sym__declarator] = 1100,
        [sym_pointer_declarator] = 56,
        [sym_function_declarator] = 56,
        [sym_array_declarator] = 56,
        [anon_sym_LPAREN] = 58,
        [anon_sym_STAR] = 60,
        [sym_identifier] = 56,
        [sym_comment] = 40,
    },
    [447] = {
        [aux_sym_declaration_repeat1] = 1102,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 672,
        [sym_comment] = 40,
    },
    [448] = {
        [sym_compound_statement] = 1104,
        [aux_sym_declaration_repeat1] = 1102,
        [anon_sym_LBRACE] = 640,
        [anon_sym_COMMA] = 634,
        [anon_sym_SEMI] = 672,
        [anon_sym_EQ] = 642,
        [anon_sym_LBRACK] = 644,
        [anon_sym_LPAREN] = 646,
        [sym_comment] = 40,
    },
    [449] = {
        [sym_preproc_define] = 1106,
        [sym_function_definition] = 1106,
        [sym_declaration_specifiers] = 1106,
        [sym_storage_class_specifier] = 1106,
        [sym__type_specifier] = 1106,
        [sym_numeric_type_specifier] = 1106,
        [sym_struct_specifier] = 1106,
        [sym_declaration] = 1106,
        [sym_type_qualifier] = 1106,
        [sym_macro_type] = 1106,
        [aux_sym_translation_unit_repeat1] = 1106,
        [aux_sym_declaration_specifiers_repeat1] = 1106,
        [aux_sym_numeric_type_specifier_repeat1] = 1106,
        [ts_builtin_sym_error] = 1106,
        [ts_builtin_sym_end] = 1106,
        [anon_sym_POUNDdefine] = 1106,
        [anon_sym_typedef] = 1106,
        [anon_sym_extern] = 1106,
        [anon_sym_static] = 1106,
        [anon_sym_auto] = 1106,
        [anon_sym_register] = 1106,
        [anon_sym_signed] = 1106,
        [anon_sym_unsigned] = 1106,
        [anon_sym_long] = 1106,
        [anon_sym_short] = 1106,
        [anon_sym_struct] = 1106,
        [anon_sym_const] = 1106,
        [anon_sym_restrict] = 1106,
        [anon_sym_volatile] = 1106,
        [sym_identifier] = 1106,
        [sym_comment] = 40,
    },
    [450] = {
        [anon_sym_SEMI] = 1108,
        [sym_comment] = 40,
    },
    [451] = {
        [sym_preproc_define] = 1068,
        [sym_function_definition] = 1068,
        [sym_declaration_specifiers] = 1068,
        [sym_storage_class_specifier] = 1068,
        [sym__type_specifier] = 1068,
        [sym_numeric_type_specifier] = 1068,
        [sym_struct_specifier] = 1068,
        [sym_declaration] = 1068,
        [sym_type_qualifier] = 1068,
        [sym_macro_type] = 1068,
        [aux_sym_translation_unit_repeat1] = 1068,
        [aux_sym_declaration_specifiers_repeat1] = 1068,
        [aux_sym_numeric_type_specifier_repeat1] = 1068,
        [ts_builtin_sym_error] = 1068,
        [ts_builtin_sym_end] = 1068,
        [anon_sym_POUNDdefine] = 1068,
        [anon_sym_typedef] = 1068,
        [anon_sym_extern] = 1068,
        [anon_sym_static] = 1068,
        [anon_sym_auto] = 1068,
        [anon_sym_register] = 1068,
        [anon_sym_signed] = 1068,
        [anon_sym_unsigned] = 1068,
        [anon_sym_long] = 1068,
        [anon_sym_short] = 1068,
        [anon_sym_struct] = 1068,
        [anon_sym_const] = 1068,
        [anon_sym_restrict] = 1068,
        [anon_sym_volatile] = 1068,
        [sym_identifier] = 1068,
        [sym_comment] = 40,
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
    [36] = {.count = 1}, SHIFT_EXTRA(),
    [38] = {.count = 1}, ACCEPT_INPUT(),
    [40] = {.count = 1}, SHIFT_EXTRA(),
    [42] = {.count = 1}, SHIFT(238, 0),
    [44] = {.count = 1}, REDUCE(aux_sym_translation_unit_repeat1, 1, 0),
    [46] = {.count = 1}, SHIFT(446, 0),
    [48] = {.count = 1}, REDUCE(aux_sym_declaration_specifiers_repeat1, 1, 0),
    [50] = {.count = 1}, SHIFT(237, 0),
    [52] = {.count = 1}, SHIFT(239, 0),
    [54] = {.count = 1}, SHIFT(240, 0),
    [56] = {.count = 1}, SHIFT(241, 0),
    [58] = {.count = 1}, SHIFT(242, 0),
    [60] = {.count = 1}, SHIFT(243, 0),
    [62] = {.count = 1}, REDUCE(sym__type_specifier, 1, 0),
    [64] = {.count = 1}, REDUCE(sym_translation_unit, 1, 0),
    [66] = {.count = 1}, REDUCE(sym_declaration_specifiers, 1, 0),
    [68] = {.count = 1}, SHIFT(236, 0),
    [70] = {.count = 1}, SHIFT(235, 0),
    [72] = {.count = 1}, SHIFT(231, 0),
    [74] = {.count = 1}, REDUCE(sym_storage_class_specifier, 1, 0),
    [76] = {.count = 1}, SHIFT(230, 0),
    [78] = {.count = 1}, REDUCE(aux_sym_numeric_type_specifier_repeat1, 1, 0),
    [80] = {.count = 1}, SHIFT(222, 0),
    [82] = {.count = 1}, SHIFT(223, 0),
    [84] = {.count = 1}, REDUCE(sym_type_qualifier, 1, 0),
    [86] = {.count = 1}, REDUCE(sym__type_specifier, 1, FRAGILE|CAN_HIDE_SPLIT),
    [88] = {.count = 1}, REDUCE(sym__type_specifier, 1, FRAGILE),
    [90] = {.count = 2}, REDUCE(sym__type_specifier, 1, FRAGILE), SHIFT(17, 0),
    [93] = {.count = 1}, SHIFT(18, 0),
    [95] = {.count = 1}, SHIFT(19, 0),
    [97] = {.count = 1}, SHIFT(20, 0),
    [99] = {.count = 1}, SHIFT(21, 0),
    [101] = {.count = 1}, SHIFT(22, 0),
    [103] = {.count = 1}, SHIFT(221, 0),
    [105] = {.count = 1}, SHIFT(220, 0),
    [107] = {.count = 1}, SHIFT(26, 0),
    [109] = {.count = 1}, SHIFT(27, 0),
    [111] = {.count = 1}, SHIFT(23, 0),
    [113] = {.count = 1}, SHIFT(24, 0),
    [115] = {.count = 1}, SHIFT(25, 0),
    [117] = {.count = 1}, REDUCE(sym_macro_type, 4, 0),
    [119] = {.count = 1}, SHIFT(29, 0),
    [121] = {.count = 1}, SHIFT(30, 0),
    [123] = {.count = 1}, SHIFT(31, 0),
    [125] = {.count = 1}, SHIFT(32, 0),
    [127] = {.count = 1}, SHIFT(218, 0),
    [129] = {.count = 1}, SHIFT(34, 0),
    [131] = {.count = 1}, SHIFT(219, 0),
    [133] = {.count = 1}, SHIFT(36, 0),
    [135] = {.count = 1}, SHIFT(28, 0),
    [137] = {.count = 1}, SHIFT(33, 0),
    [139] = {.count = 1}, SHIFT(35, 0),
    [141] = {.count = 1}, SHIFT(51, 0),
    [143] = {.count = 1}, SHIFT(52, 0),
    [145] = {.count = 1}, SHIFT(53, 0),
    [147] = {.count = 1}, SHIFT(54, 0),
    [149] = {.count = 1}, SHIFT(50, 0),
    [151] = {.count = 1}, REDUCE(aux_sym_struct_specifier_repeat1, 1, 0),
    [153] = {.count = 1}, SHIFT(49, 0),
    [155] = {.count = 1}, SHIFT(48, 0),
    [157] = {.count = 1}, SHIFT(40, 0),
    [159] = {.count = 1}, SHIFT(41, 0),
    [161] = {.count = 1}, REDUCE(sym_struct_specifier, 4, 0),
    [163] = {.count = 2}, REDUCE(sym__type_specifier, 1, FRAGILE), SHIFT(37, 0),
    [166] = {.count = 1}, SHIFT(38, 0),
    [168] = {.count = 1}, SHIFT(39, 0),
    [170] = {.count = 1}, SHIFT(46, 0),
    [172] = {.count = 1}, SHIFT(47, 0),
    [174] = {.count = 1}, SHIFT(42, 0),
    [176] = {.count = 1}, SHIFT(43, 0),
    [178] = {.count = 1}, SHIFT(44, 0),
    [180] = {.count = 1}, SHIFT(45, 0),
    [182] = {.count = 1}, REDUCE(sym_struct_specifier, 5, 0),
    [184] = {.count = 1}, REDUCE(sym_struct_specifier, 3, 0),
    [186] = {.count = 1}, REDUCE(sym_numeric_type_specifier, 2, 0),
    [188] = {.count = 1}, REDUCE(aux_sym_struct_specifier_repeat1, 2, 0),
    [190] = {.count = 1}, REDUCE(sym_struct_declaration, 2, 0),
    [192] = {.count = 1}, SHIFT(56, 0),
    [194] = {.count = 1}, SHIFT(57, 0),
    [196] = {.count = 1}, REDUCE(sym__declarator, 1, 0),
    [198] = {.count = 1}, SHIFT(216, 0),
    [200] = {.count = 1}, SHIFT(194, 0),
    [202] = {.count = 1}, SHIFT(195, 0),
    [204] = {.count = 1}, SHIFT(196, 0),
    [206] = {.count = 1}, SHIFT(55, 0),
    [208] = {.count = 1}, REDUCE(sym_pointer_declarator, 2, FRAGILE),
    [210] = {.count = 1}, SHIFT(213, 0),
    [212] = {.count = 1}, SHIFT(81, 0),
    [214] = {.count = 1}, SHIFT(214, 0),
    [216] = {.count = 1}, SHIFT(83, 0),
    [218] = {.count = 1}, SHIFT(84, 0),
    [220] = {.count = 1}, SHIFT(85, 0),
    [222] = {.count = 1}, SHIFT(58, 0),
    [224] = {.count = 1}, SHIFT(59, 0),
    [226] = {.count = 1}, SHIFT(60, 0),
    [228] = {.count = 1}, SHIFT(61, 0),
    [230] = {.count = 1}, SHIFT(211, 0),
    [232] = {.count = 1}, SHIFT(68, 0),
    [234] = {.count = 1}, SHIFT(69, 0),
    [236] = {.count = 1}, SHIFT(70, 0),
    [238] = {.count = 1}, SHIFT(71, 0),
    [240] = {.count = 1}, SHIFT(62, 0),
    [242] = {.count = 1}, SHIFT(63, 0),
    [244] = {.count = 1}, SHIFT(64, 0),
    [246] = {.count = 1}, REDUCE(sym_function_declarator, 3, 0),
    [248] = {.count = 1}, SHIFT(67, 0),
    [250] = {.count = 1}, SHIFT(65, 0),
    [252] = {.count = 1}, REDUCE(sym_function_declarator, 4, 0),
    [254] = {.count = 1}, SHIFT(66, 0),
    [256] = {.count = 1}, REDUCE(aux_sym_function_declarator_repeat1, 2, 0),
    [258] = {.count = 1}, REDUCE(aux_sym_function_declarator_repeat1, 3, 0),
    [260] = {.count = 1}, REDUCE(sym_function_declarator, 5, 0),
    [262] = {.count = 1}, REDUCE(sym_parameter_declaration, 2, 0),
    [264] = {.count = 1}, SHIFT(73, 0),
    [266] = {.count = 1}, SHIFT(74, 0),
    [268] = {.count = 1}, SHIFT(193, 0),
    [270] = {.count = 1}, SHIFT(72, 0),
    [272] = {.count = 1}, SHIFT(80, 0),
    [274] = {.count = 1}, SHIFT(82, 0),
    [276] = {.count = 1}, SHIFT(75, 0),
    [278] = {.count = 1}, SHIFT(76, 0),
    [280] = {.count = 1}, SHIFT(77, 0),
    [282] = {.count = 1}, SHIFT(78, 0),
    [284] = {.count = 1}, SHIFT(79, 0),
    [286] = {.count = 1}, SHIFT(173, 0),
    [288] = {.count = 1}, SHIFT(192, 0),
    [290] = {.count = 1}, SHIFT(87, 0),
    [292] = {.count = 1}, SHIFT(88, 0),
    [294] = {.count = 1}, SHIFT(89, 0),
    [296] = {.count = 1}, REDUCE(sym__expression, 1, 0),
    [298] = {.count = 1}, REDUCE(sym_array_declarator, 3, 0),
    [300] = {.count = 1}, SHIFT(114, 0),
    [302] = {.count = 1}, SHIFT(115, 0),
    [304] = {.count = 1}, SHIFT(187, 0),
    [306] = {.count = 1}, SHIFT(117, 0),
    [308] = {.count = 1}, SHIFT(188, 0),
    [310] = {.count = 1}, SHIFT(119, 0),
    [312] = {.count = 1}, SHIFT(120, 0),
    [314] = {.count = 1}, SHIFT(121, 0),
    [316] = {.count = 1}, SHIFT(122, 0),
    [318] = {.count = 1}, SHIFT(123, 0),
    [320] = {.count = 1}, SHIFT(124, 0),
    [322] = {.count = 1}, SHIFT(125, 0),
    [324] = {.count = 1}, SHIFT(126, 0),
    [326] = {.count = 1}, SHIFT(86, 0),
    [328] = {.count = 1}, REDUCE(sym__expression, 1, FRAGILE),
    [330] = {.count = 1}, REDUCE(sym_pointer_expression, 2, FRAGILE),
    [332] = {.count = 1}, SHIFT(92, 0),
    [334] = {.count = 1}, SHIFT(93, 0),
    [336] = {.count = 1}, SHIFT(94, 0),
    [338] = {.count = 1}, SHIFT(95, 0),
    [340] = {.count = 1}, SHIFT(96, 0),
    [342] = {.count = 1}, SHIFT(97, 0),
    [344] = {.count = 1}, SHIFT(91, 0),
    [346] = {.count = 1}, SHIFT(90, 0),
    [348] = {.count = 1}, REDUCE(sym_math_expression, 3, FRAGILE),
    [350] = {.count = 1}, SHIFT(184, 0),
    [352] = {.count = 1}, SHIFT(107, 0),
    [354] = {.count = 1}, SHIFT(108, 0),
    [356] = {.count = 1}, SHIFT(99, 0),
    [358] = {.count = 1}, SHIFT(185, 0),
    [360] = {.count = 1}, SHIFT(100, 0),
    [362] = {.count = 1}, SHIFT(101, 0),
    [364] = {.count = 1}, SHIFT(116, 0),
    [366] = {.count = 1}, SHIFT(118, 0),
    [368] = {.count = 1}, REDUCE(sym_call_expression, 3, 0),
    [370] = {.count = 1}, SHIFT(98, 0),
    [372] = {.count = 1}, SHIFT(104, 0),
    [374] = {.count = 1}, SHIFT(105, 0),
    [376] = {.count = 1}, SHIFT(103, 0),
    [378] = {.count = 1}, SHIFT(102, 0),
    [380] = {.count = 1}, SHIFT(106, 0),
    [382] = {.count = 1}, SHIFT(109, 0),
    [384] = {.count = 1}, SHIFT(113, 0),
    [386] = {.count = 1}, SHIFT(111, 0),
    [388] = {.count = 1}, SHIFT(110, 0),
    [390] = {.count = 1}, REDUCE(sym_call_expression, 4, 0),
    [392] = {.count = 1}, REDUCE(sym_assignment_expression, 3, FRAGILE),
    [394] = {.count = 1}, SHIFT(112, 0),
    [396] = {.count = 1}, REDUCE(aux_sym_call_expression_repeat1, 2, 0),
    [398] = {.count = 1}, REDUCE(aux_sym_call_expression_repeat1, 3, 0),
    [400] = {.count = 1}, REDUCE(sym_call_expression, 5, 0),
    [402] = {.count = 1}, SHIFT(183, 0),
    [404] = {.count = 1}, SHIFT(160, 0),
    [406] = {.count = 1}, SHIFT(161, 0),
    [408] = {.count = 1}, REDUCE(sym_type_name, 1, 0),
    [410] = {.count = 1}, SHIFT(162, 0),
    [412] = {.count = 1}, SHIFT(181, 0),
    [414] = {.count = 1}, REDUCE(aux_sym_type_name_repeat1, 1, 0),
    [416] = {.count = 1}, SHIFT(180, 0),
    [418] = {.count = 1}, SHIFT(144, 0),
    [420] = {.count = 1}, SHIFT(132, 0),
    [422] = {.count = 1}, SHIFT(179, 0),
    [424] = {.count = 1}, SHIFT(133, 0),
    [426] = {.count = 1}, SHIFT(134, 0),
    [428] = {.count = 1}, SHIFT(178, 0),
    [430] = {.count = 1}, SHIFT(157, 0),
    [432] = {.count = 1}, SHIFT(158, 0),
    [434] = {.count = 1}, SHIFT(149, 0),
    [436] = {.count = 1}, SHIFT(150, 0),
    [438] = {.count = 1}, SHIFT(142, 0),
    [440] = {.count = 1}, SHIFT(143, 0),
    [442] = {.count = 1}, SHIFT(130, 0),
    [444] = {.count = 1}, SHIFT(131, 0),
    [446] = {.count = 3}, REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE), SHIFT(127, 0),
    [450] = {.count = 2}, REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE),
    [453] = {.count = 1}, SHIFT(128, 0),
    [455] = {.count = 1}, SHIFT(129, 0),
    [457] = {.count = 1}, SHIFT(137, 0),
    [459] = {.count = 1}, SHIFT(138, 0),
    [461] = {.count = 1}, SHIFT(136, 0),
    [463] = {.count = 1}, SHIFT(135, 0),
    [465] = {.count = 1}, SHIFT(139, 0),
    [467] = {.count = 1}, SHIFT(140, 0),
    [469] = {.count = 1}, SHIFT(141, 0),
    [471] = {.count = 1}, SHIFT(147, 0),
    [473] = {.count = 1}, SHIFT(145, 0),
    [475] = {.count = 1}, SHIFT(146, 0),
    [477] = {.count = 1}, REDUCE(sym__expression, 3, 0),
    [479] = {.count = 1}, SHIFT(148, 0),
    [481] = {.count = 1}, REDUCE(sym_cast_expression, 4, 0),
    [483] = {.count = 1}, SHIFT(155, 0),
    [485] = {.count = 1}, SHIFT(156, 0),
    [487] = {.count = 1}, SHIFT(151, 0),
    [489] = {.count = 1}, SHIFT(152, 0),
    [491] = {.count = 1}, SHIFT(153, 0),
    [493] = {.count = 1}, SHIFT(154, 0),
    [495] = {.count = 1}, SHIFT(159, 0),
    [497] = {.count = 1}, REDUCE(sym_type_name, 2, 0),
    [499] = {.count = 2}, REDUCE(sym__type_specifier, 1, FRAGILE), SHIFT(127, 0),
    [502] = {.count = 1}, SHIFT(164, 0),
    [504] = {.count = 1}, SHIFT(165, 0),
    [506] = {.count = 1}, REDUCE(sym_type_name, 3, 0),
    [508] = {.count = 1}, REDUCE(sym__abstract_declarator, 1, 0),
    [510] = {.count = 1}, SHIFT(176, 0),
    [512] = {.count = 1}, SHIFT(163, 0),
    [514] = {.count = 1}, REDUCE(sym_abstract_pointer_declarator, 1, FRAGILE),
    [516] = {.count = 1}, REDUCE(sym_abstract_pointer_declarator, 2, FRAGILE),
    [518] = {.count = 1}, SHIFT(171, 0),
    [520] = {.count = 1}, SHIFT(172, 0),
    [522] = {.count = 1}, SHIFT(166, 0),
    [524] = {.count = 1}, SHIFT(167, 0),
    [526] = {.count = 1}, SHIFT(168, 0),
    [528] = {.count = 1}, SHIFT(169, 0),
    [530] = {.count = 1}, REDUCE(sym_abstract_function_declarator, 3, 0),
    [532] = {.count = 1}, SHIFT(170, 0),
    [534] = {.count = 1}, REDUCE(sym_abstract_function_declarator, 4, 0),
    [536] = {.count = 1}, REDUCE(sym_abstract_function_declarator, 5, 0),
    [538] = {.count = 1}, SHIFT(174, 0),
    [540] = {.count = 1}, REDUCE(sym_abstract_array_declarator, 3, 0),
    [542] = {.count = 1}, SHIFT(175, 0),
    [544] = {.count = 1}, REDUCE(sym_abstract_array_declarator, 4, 0),
    [546] = {.count = 1}, SHIFT(177, 0),
    [548] = {.count = 1}, REDUCE(sym__abstract_declarator, 3, 0),
    [550] = {.count = 1}, REDUCE(aux_sym_type_name_repeat1, 2, 0),
    [552] = {.count = 1}, SHIFT(182, 0),
    [554] = {.count = 1}, SHIFT(186, 0),
    [556] = {.count = 1}, SHIFT(190, 0),
    [558] = {.count = 1}, SHIFT(189, 0),
    [560] = {.count = 1}, SHIFT(191, 0),
    [562] = {.count = 1}, REDUCE(sym_array_declarator, 4, 0),
    [564] = {.count = 1}, SHIFT(198, 0),
    [566] = {.count = 1}, SHIFT(199, 0),
    [568] = {.count = 1}, SHIFT(210, 0),
    [570] = {.count = 1}, SHIFT(208, 0),
    [572] = {.count = 1}, SHIFT(197, 0),
    [574] = {.count = 1}, SHIFT(205, 0),
    [576] = {.count = 1}, SHIFT(206, 0),
    [578] = {.count = 1}, SHIFT(200, 0),
    [580] = {.count = 1}, SHIFT(201, 0),
    [582] = {.count = 1}, SHIFT(202, 0),
    [584] = {.count = 1}, SHIFT(203, 0),
    [586] = {.count = 1}, SHIFT(204, 0),
    [588] = {.count = 1}, SHIFT(207, 0),
    [590] = {.count = 1}, SHIFT(209, 0),
    [592] = {.count = 1}, REDUCE(sym__declarator, 3, 0),
    [594] = {.count = 1}, SHIFT(212, 0),
    [596] = {.count = 1}, REDUCE(sym_parameter_declaration, 3, 0),
    [598] = {.count = 1}, SHIFT(215, 0),
    [600] = {.count = 1}, SHIFT(217, 0),
    [602] = {.count = 1}, SHIFT(228, 0),
    [604] = {.count = 1}, SHIFT(229, 0),
    [606] = {.count = 1}, SHIFT(224, 0),
    [608] = {.count = 1}, SHIFT(225, 0),
    [610] = {.count = 1}, SHIFT(226, 0),
    [612] = {.count = 1}, SHIFT(227, 0),
    [614] = {.count = 1}, REDUCE(aux_sym_numeric_type_specifier_repeat1, 2, 0),
    [616] = {.count = 1}, SHIFT(232, 0),
    [618] = {.count = 1}, SHIFT(233, 0),
    [620] = {.count = 1}, REDUCE(sym_preproc_define, 3, 0),
    [622] = {.count = 1}, SHIFT(234, 0),
    [624] = {.count = 1}, REDUCE(sym_preproc_define, 4, 0),
    [626] = {.count = 1}, REDUCE(sym_declaration, 2, 0),
    [628] = {.count = 1}, REDUCE(aux_sym_declaration_specifiers_repeat1, 2, 0),
    [630] = {.count = 1}, REDUCE(aux_sym_translation_unit_repeat1, 2, 0),
    [632] = {.count = 1}, SHIFT(258, 0),
    [634] = {.count = 1}, SHIFT(260, 0),
    [636] = {.count = 1}, SHIFT(261, 0),
    [638] = {.count = 1}, SHIFT(257, 0),
    [640] = {.count = 1}, SHIFT(259, 0),
    [642] = {.count = 1}, SHIFT(262, 0),
    [644] = {.count = 1}, SHIFT(245, 0),
    [646] = {.count = 1}, SHIFT(246, 0),
    [648] = {.count = 1}, SHIFT(255, 0),
    [650] = {.count = 1}, SHIFT(244, 0),
    [652] = {.count = 1}, SHIFT(252, 0),
    [654] = {.count = 1}, SHIFT(253, 0),
    [656] = {.count = 1}, SHIFT(247, 0),
    [658] = {.count = 1}, SHIFT(248, 0),
    [660] = {.count = 1}, SHIFT(249, 0),
    [662] = {.count = 1}, SHIFT(250, 0),
    [664] = {.count = 1}, SHIFT(251, 0),
    [666] = {.count = 1}, SHIFT(254, 0),
    [668] = {.count = 1}, SHIFT(256, 0),
    [670] = {.count = 1}, REDUCE(sym_function_definition, 3, 0),
    [672] = {.count = 1}, SHIFT(445, 0),
    [674] = {.count = 1}, SHIFT(354, 0),
    [676] = {.count = 1}, SHIFT(355, 0),
    [678] = {.count = 1}, SHIFT(356, 0),
    [680] = {.count = 1}, SHIFT(357, 0),
    [682] = {.count = 1}, SHIFT(358, 0),
    [684] = {.count = 1}, SHIFT(359, 0),
    [686] = {.count = 1}, SHIFT(360, 0),
    [688] = {.count = 1}, SHIFT(361, 0),
    [690] = {.count = 1}, SHIFT(362, 0),
    [692] = {.count = 1}, SHIFT(363, 0),
    [694] = {.count = 1}, SHIFT(364, 0),
    [696] = {.count = 1}, SHIFT(365, 0),
    [698] = {.count = 1}, SHIFT(366, 0),
    [700] = {.count = 1}, SHIFT(367, 0),
    [702] = {.count = 1}, SHIFT(335, 0),
    [704] = {.count = 1}, SHIFT(336, 0),
    [706] = {.count = 1}, SHIFT(337, 0),
    [708] = {.count = 1}, SHIFT(338, 0),
    [710] = {.count = 1}, SHIFT(339, 0),
    [712] = {.count = 1}, REDUCE(sym_declaration, 3, 0),
    [714] = {.count = 1}, SHIFT(263, 0),
    [716] = {.count = 1}, SHIFT(264, 0),
    [718] = {.count = 1}, SHIFT(265, 0),
    [720] = {.count = 1}, SHIFT(266, 0),
    [722] = {.count = 1}, SHIFT(267, 0),
    [724] = {.count = 1}, SHIFT(268, 0),
    [726] = {.count = 1}, SHIFT(269, 0),
    [728] = {.count = 1}, REDUCE(sym__init_declarator, 3, 0),
    [730] = {.count = 1}, REDUCE(sym_initializer, 1, 0),
    [732] = {.count = 1}, SHIFT(333, 0),
    [734] = {.count = 1}, SHIFT(271, 0),
    [736] = {.count = 1}, SHIFT(272, 0),
    [738] = {.count = 1}, SHIFT(273, 0),
    [740] = {.count = 1}, SHIFT(286, 0),
    [742] = {.count = 1}, SHIFT(287, 0),
    [744] = {.count = 1}, SHIFT(288, 0),
    [746] = {.count = 1}, SHIFT(289, 0),
    [748] = {.count = 1}, SHIFT(290, 0),
    [750] = {.count = 1}, SHIFT(291, 0),
    [752] = {.count = 1}, SHIFT(292, 0),
    [754] = {.count = 1}, SHIFT(293, 0),
    [756] = {.count = 1}, SHIFT(294, 0),
    [758] = {.count = 1}, SHIFT(295, 0),
    [760] = {.count = 1}, SHIFT(296, 0),
    [762] = {.count = 1}, SHIFT(297, 0),
    [764] = {.count = 1}, SHIFT(281, 0),
    [766] = {.count = 1}, SHIFT(282, 0),
    [768] = {.count = 1}, SHIFT(270, 0),
    [770] = {.count = 1}, SHIFT(276, 0),
    [772] = {.count = 1}, SHIFT(277, 0),
    [774] = {.count = 1}, SHIFT(275, 0),
    [776] = {.count = 1}, SHIFT(274, 0),
    [778] = {.count = 1}, SHIFT(278, 0),
    [780] = {.count = 1}, SHIFT(279, 0),
    [782] = {.count = 1}, SHIFT(280, 0),
    [784] = {.count = 1}, SHIFT(284, 0),
    [786] = {.count = 1}, SHIFT(283, 0),
    [788] = {.count = 1}, SHIFT(285, 0),
    [790] = {.count = 1}, REDUCE(sym_initializer_list, 1, 0),
    [792] = {.count = 1}, SHIFT(330, 0),
    [794] = {.count = 1}, SHIFT(331, 0),
    [796] = {.count = 1}, SHIFT(329, 0),
    [798] = {.count = 1}, SHIFT(327, 0),
    [800] = {.count = 1}, SHIFT(299, 0),
    [802] = {.count = 1}, SHIFT(300, 0),
    [804] = {.count = 1}, SHIFT(301, 0),
    [806] = {.count = 1}, SHIFT(326, 0),
    [808] = {.count = 1}, SHIFT(319, 0),
    [810] = {.count = 1}, SHIFT(316, 0),
    [812] = {.count = 1}, SHIFT(314, 0),
    [814] = {.count = 1}, SHIFT(309, 0),
    [816] = {.count = 1}, SHIFT(310, 0),
    [818] = {.count = 1}, SHIFT(298, 0),
    [820] = {.count = 1}, SHIFT(304, 0),
    [822] = {.count = 1}, SHIFT(305, 0),
    [824] = {.count = 1}, SHIFT(303, 0),
    [826] = {.count = 1}, SHIFT(302, 0),
    [828] = {.count = 1}, SHIFT(306, 0),
    [830] = {.count = 1}, SHIFT(307, 0),
    [832] = {.count = 1}, SHIFT(308, 0),
    [834] = {.count = 1}, SHIFT(312, 0),
    [836] = {.count = 1}, SHIFT(311, 0),
    [838] = {.count = 1}, SHIFT(313, 0),
    [840] = {.count = 1}, SHIFT(315, 0),
    [842] = {.count = 1}, REDUCE(aux_sym_designation_repeat1, 2, 0),
    [844] = {.count = 1}, REDUCE(aux_sym_designation_repeat1, 3, 0),
    [846] = {.count = 1}, SHIFT(317, 0),
    [848] = {.count = 1}, SHIFT(318, 0),
    [850] = {.count = 1}, REDUCE(aux_sym_designation_repeat1, 4, 0),
    [852] = {.count = 1}, SHIFT(320, 0),
    [854] = {.count = 1}, SHIFT(321, 0),
    [856] = {.count = 1}, REDUCE(sym_initializer, 3, 0),
    [858] = {.count = 1}, SHIFT(322, 0),
    [860] = {.count = 1}, SHIFT(323, 0),
    [862] = {.count = 1}, SHIFT(324, 0),
    [864] = {.count = 1}, REDUCE(sym_initializer_list, 3, 0),
    [866] = {.count = 1}, SHIFT(325, 0),
    [868] = {.count = 1}, REDUCE(sym_initializer, 4, 0),
    [870] = {.count = 1}, REDUCE(sym_initializer_list, 4, 0),
    [872] = {.count = 1}, REDUCE(sym_designation, 2, 0),
    [874] = {.count = 1}, SHIFT(328, 0),
    [876] = {.count = 1}, REDUCE(sym_initializer_list, 2, 0),
    [878] = {.count = 1}, SHIFT(332, 0),
    [880] = {.count = 1}, SHIFT(334, 0),
    [882] = {.count = 1}, SHIFT(353, 0),
    [884] = {.count = 1}, REDUCE(aux_sym_declaration_repeat1, 2, 0),
    [886] = {.count = 1}, SHIFT(341, 0),
    [888] = {.count = 1}, SHIFT(342, 0),
    [890] = {.count = 1}, SHIFT(351, 0),
    [892] = {.count = 1}, SHIFT(340, 0),
    [894] = {.count = 1}, SHIFT(348, 0),
    [896] = {.count = 1}, SHIFT(349, 0),
    [898] = {.count = 1}, SHIFT(343, 0),
    [900] = {.count = 1}, SHIFT(344, 0),
    [902] = {.count = 1}, SHIFT(345, 0),
    [904] = {.count = 1}, SHIFT(346, 0),
    [906] = {.count = 1}, SHIFT(347, 0),
    [908] = {.count = 1}, SHIFT(350, 0),
    [910] = {.count = 1}, SHIFT(352, 0),
    [912] = {.count = 1}, REDUCE(aux_sym_declaration_repeat1, 3, 0),
    [914] = {.count = 1}, SHIFT(440, 0),
    [916] = {.count = 1}, SHIFT(435, 0),
    [918] = {.count = 1}, SHIFT(436, 0),
    [920] = {.count = 1}, SHIFT(432, 0),
    [922] = {.count = 1}, SHIFT(433, 0),
    [924] = {.count = 1}, REDUCE(aux_sym_compound_statement_repeat1, 1, 0),
    [926] = {.count = 1}, REDUCE(sym__statement, 1, 0),
    [928] = {.count = 1}, SHIFT(434, 0),
    [930] = {.count = 1}, SHIFT(386, 0),
    [932] = {.count = 1}, SHIFT(387, 0),
    [934] = {.count = 1}, SHIFT(388, 0),
    [936] = {.count = 1}, SHIFT(389, 0),
    [938] = {.count = 1}, SHIFT(431, 0),
    [940] = {.count = 1}, SHIFT(430, 0),
    [942] = {.count = 1}, SHIFT(426, 0),
    [944] = {.count = 1}, SHIFT(427, 0),
    [946] = {.count = 1}, SHIFT(428, 0),
    [948] = {.count = 1}, REDUCE(sym_compound_statement, 2, 0),
    [950] = {.count = 1}, SHIFT(421, 0),
    [952] = {.count = 1}, SHIFT(422, 0),
    [954] = {.count = 1}, SHIFT(420, 0),
    [956] = {.count = 1}, SHIFT(376, 0),
    [958] = {.count = 1}, SHIFT(368, 0),
    [960] = {.count = 3}, REDUCE(sym__type_specifier, 1, FRAGILE), REDUCE(sym__expression, 1, FRAGILE), SHIFT(17, 0),
    [964] = {.count = 1}, SHIFT(369, 0),
    [966] = {.count = 1}, SHIFT(370, 0),
    [968] = {.count = 1}, SHIFT(371, 0),
    [970] = {.count = 1}, SHIFT(372, 0),
    [972] = {.count = 1}, SHIFT(373, 0),
    [974] = {.count = 1}, SHIFT(415, 0),
    [976] = {.count = 1}, SHIFT(410, 0),
    [978] = {.count = 1}, SHIFT(411, 0),
    [980] = {.count = 1}, SHIFT(374, 0),
    [982] = {.count = 1}, SHIFT(375, 0),
    [984] = {.count = 1}, SHIFT(403, 0),
    [986] = {.count = 1}, SHIFT(402, 0),
    [988] = {.count = 1}, SHIFT(385, 0),
    [990] = {.count = 1}, SHIFT(377, 0),
    [992] = {.count = 1}, SHIFT(378, 0),
    [994] = {.count = 1}, SHIFT(380, 0),
    [996] = {.count = 1}, SHIFT(381, 0),
    [998] = {.count = 1}, SHIFT(379, 0),
    [1000] = {.count = 1}, REDUCE(sym_for_statement, 6, 0),
    [1002] = {.count = 1}, SHIFT(383, 0),
    [1004] = {.count = 1}, SHIFT(382, 0),
    [1006] = {.count = 1}, REDUCE(sym_for_statement, 7, 0),
    [1008] = {.count = 1}, SHIFT(384, 0),
    [1010] = {.count = 1}, REDUCE(sym_for_statement, 8, 0),
    [1012] = {.count = 1}, SHIFT(398, 0),
    [1014] = {.count = 1}, SHIFT(397, 0),
    [1016] = {.count = 1}, SHIFT(392, 0),
    [1018] = {.count = 1}, SHIFT(393, 0),
    [1020] = {.count = 1}, SHIFT(391, 0),
    [1022] = {.count = 1}, SHIFT(390, 0),
    [1024] = {.count = 1}, SHIFT(394, 0),
    [1026] = {.count = 1}, SHIFT(395, 0),
    [1028] = {.count = 1}, SHIFT(396, 0),
    [1030] = {.count = 1}, SHIFT(399, 0),
    [1032] = {.count = 1}, SHIFT(400, 0),
    [1034] = {.count = 1}, SHIFT(401, 0),
    [1036] = {.count = 1}, REDUCE(sym_for_statement, 9, 0),
    [1038] = {.count = 1}, SHIFT(404, 0),
    [1040] = {.count = 1}, SHIFT(405, 0),
    [1042] = {.count = 1}, SHIFT(406, 0),
    [1044] = {.count = 1}, SHIFT(407, 0),
    [1046] = {.count = 1}, SHIFT(408, 0),
    [1048] = {.count = 1}, SHIFT(409, 0),
    [1050] = {.count = 1}, REDUCE(sym_for_statement, 10, 0),
    [1052] = {.count = 1}, SHIFT(412, 0),
    [1054] = {.count = 1}, SHIFT(413, 0),
    [1056] = {.count = 1}, SHIFT(414, 0),
    [1058] = {.count = 1}, REDUCE(sym_declaration, 4, 0),
    [1060] = {.count = 1}, SHIFT(416, 0),
    [1062] = {.count = 1}, SHIFT(417, 0),
    [1064] = {.count = 1}, SHIFT(418, 0),
    [1066] = {.count = 1}, SHIFT(419, 0),
    [1068] = {.count = 1}, REDUCE(sym_declaration, 5, 0),
    [1070] = {.count = 1}, SHIFT(424, 0),
    [1072] = {.count = 1}, SHIFT(423, 0),
    [1074] = {.count = 1}, SHIFT(425, 0),
    [1076] = {.count = 1}, SHIFT(429, 0),
    [1078] = {.count = 1}, REDUCE(sym_compound_statement, 3, 0),
    [1080] = {.count = 1}, REDUCE(aux_sym_compound_statement_repeat1, 2, 0),
    [1082] = {.count = 1}, REDUCE(sym_expression_statement, 2, 0),
    [1084] = {.count = 1}, SHIFT(437, 0),
    [1086] = {.count = 1}, SHIFT(438, 0),
    [1088] = {.count = 1}, SHIFT(439, 0),
    [1090] = {.count = 1}, SHIFT(441, 0),
    [1092] = {.count = 1}, SHIFT(442, 0),
    [1094] = {.count = 1}, SHIFT(443, 0),
    [1096] = {.count = 1}, SHIFT(444, 0),
    [1098] = {.count = 1}, SHIFT(447, 0),
    [1100] = {.count = 1}, SHIFT(448, 0),
    [1102] = {.count = 1}, SHIFT(450, 0),
    [1104] = {.count = 1}, SHIFT(449, 0),
    [1106] = {.count = 1}, REDUCE(sym_function_definition, 4, 0),
    [1108] = {.count = 1}, SHIFT(451, 0),
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
