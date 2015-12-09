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
    [sym_translation_unit] = {.visible = true, .named = true, .extra = false},
    [sym_preproc_define] = {.visible = true, .named = true, .extra = false},
    [sym_function_definition] = {.visible = true, .named = true, .extra = false},
    [sym_declaration_specifiers] = {.visible = true, .named = true, .extra = false},
    [sym_storage_class_specifier] = {.visible = true, .named = true, .extra = false},
    [sym__type_specifier] = {.visible = false, .named = false, .extra = false},
    [sym_numeric_type_specifier] = {.visible = true, .named = true, .extra = false},
    [sym_struct_specifier] = {.visible = true, .named = true, .extra = false},
    [sym_type_name] = {.visible = true, .named = true, .extra = false},
    [sym_struct_declaration] = {.visible = true, .named = true, .extra = false},
    [sym_parameter_declaration] = {.visible = true, .named = true, .extra = false},
    [sym_declaration] = {.visible = true, .named = true, .extra = false},
    [sym__init_declarator] = {.visible = false, .named = false, .extra = false},
    [sym_initializer] = {.visible = true, .named = true, .extra = false},
    [sym_initializer_list] = {.visible = true, .named = true, .extra = false},
    [sym_designation] = {.visible = true, .named = true, .extra = false},
    [sym__declarator] = {.visible = false, .named = false, .extra = false},
    [sym__abstract_declarator] = {.visible = false, .named = false, .extra = false},
    [sym_pointer_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_abstract_pointer_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_function_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_abstract_function_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_array_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_abstract_array_declarator] = {.visible = true, .named = true, .extra = false},
    [sym_type_qualifier] = {.visible = true, .named = true, .extra = false},
    [sym_compound_statement] = {.visible = true, .named = true, .extra = false},
    [sym__expression] = {.visible = false, .named = false, .extra = false},
    [sym_cast_expression] = {.visible = true, .named = true, .extra = false},
    [sym_math_expression] = {.visible = true, .named = true, .extra = false},
    [sym_call_expression] = {.visible = true, .named = true, .extra = false},
    [sym_pointer_expression] = {.visible = true, .named = true, .extra = false},
    [sym_assignment_expression] = {.visible = true, .named = true, .extra = false},
    [sym__statement] = {.visible = false, .named = false, .extra = false},
    [sym_for_statement] = {.visible = true, .named = true, .extra = false},
    [sym_expression_statement] = {.visible = true, .named = true, .extra = false},
    [sym_macro_type] = {.visible = true, .named = true, .extra = false},
    [aux_sym_translation_unit_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_declaration_specifiers_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_numeric_type_specifier_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_struct_specifier_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_type_name_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_declaration_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_designation_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_function_declarator_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_compound_statement_repeat1] = {.visible = false, .named = false, .extra = false},
    [aux_sym_call_expression_repeat1] = {.visible = false, .named = false, .extra = false},
    [ts_builtin_sym_error] = {.visible = true, .named = true, .extra = false},
    [ts_builtin_sym_end] = {.visible = false, .named = false, .extra = false},
    [anon_sym_POUNDdefine] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LF] = {.visible = true, .named = false, .extra = false},
    [sym_preproc_arg] = {.visible = true, .named = true, .extra = false},
    [anon_sym_typedef] = {.visible = true, .named = false, .extra = false},
    [anon_sym_extern] = {.visible = true, .named = false, .extra = false},
    [anon_sym_static] = {.visible = true, .named = false, .extra = false},
    [anon_sym_auto] = {.visible = true, .named = false, .extra = false},
    [anon_sym_register] = {.visible = true, .named = false, .extra = false},
    [anon_sym_signed] = {.visible = true, .named = false, .extra = false},
    [anon_sym_unsigned] = {.visible = true, .named = false, .extra = false},
    [anon_sym_long] = {.visible = true, .named = false, .extra = false},
    [anon_sym_short] = {.visible = true, .named = false, .extra = false},
    [anon_sym_struct] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LBRACE] = {.visible = true, .named = false, .extra = false},
    [anon_sym_RBRACE] = {.visible = true, .named = false, .extra = false},
    [anon_sym_COMMA] = {.visible = true, .named = false, .extra = false},
    [anon_sym_SEMI] = {.visible = true, .named = false, .extra = false},
    [anon_sym_EQ] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LBRACK] = {.visible = true, .named = false, .extra = false},
    [anon_sym_RBRACK] = {.visible = true, .named = false, .extra = false},
    [anon_sym_DOT] = {.visible = true, .named = false, .extra = false},
    [anon_sym_LPAREN] = {.visible = true, .named = false, .extra = false},
    [anon_sym_RPAREN] = {.visible = true, .named = false, .extra = false},
    [anon_sym_STAR] = {.visible = true, .named = false, .extra = false},
    [anon_sym_const] = {.visible = true, .named = false, .extra = false},
    [anon_sym_restrict] = {.visible = true, .named = false, .extra = false},
    [anon_sym_volatile] = {.visible = true, .named = false, .extra = false},
    [anon_sym_PLUS] = {.visible = true, .named = false, .extra = false},
    [anon_sym_AMP] = {.visible = true, .named = false, .extra = false},
    [anon_sym_for] = {.visible = true, .named = false, .extra = false},
    [sym_string] = {.visible = true, .named = true, .extra = false},
    [sym_identifier] = {.visible = true, .named = true, .extra = false},
    [sym_number] = {.visible = true, .named = true, .extra = false},
    [sym_comment] = {.visible = true, .named = true, .extra = true},
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
            ACCEPT_TOKEN(sym_identifier);
        case 16:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 't') ||
                ('v' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'u')
                ADVANCE(17);
            ACCEPT_TOKEN(sym_identifier);
        case 17:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(18);
            ACCEPT_TOKEN(sym_identifier);
        case 18:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(19);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 21:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(22);
            ACCEPT_TOKEN(sym_identifier);
        case 22:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(23);
            ACCEPT_TOKEN(sym_identifier);
        case 23:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(24);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 26:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(27);
            ACCEPT_TOKEN(sym_identifier);
        case 27:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(28);
            ACCEPT_TOKEN(sym_identifier);
        case 28:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(29);
            ACCEPT_TOKEN(sym_identifier);
        case 29:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(30);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 32:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(33);
            ACCEPT_TOKEN(sym_identifier);
        case 33:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'g')
                ADVANCE(34);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 37:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(38);
            ACCEPT_TOKEN(sym_identifier);
        case 38:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(39);
            ACCEPT_TOKEN(sym_identifier);
        case 39:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(40);
            ACCEPT_TOKEN(sym_identifier);
        case 40:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(41);
            ACCEPT_TOKEN(sym_identifier);
        case 41:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(42);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 44:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(45);
            ACCEPT_TOKEN(sym_identifier);
        case 45:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(46);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 47:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(48);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 50:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(51);
            ACCEPT_TOKEN(sym_identifier);
        case 51:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(52);
            ACCEPT_TOKEN(sym_identifier);
        case 52:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(53);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 55:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(56);
            ACCEPT_TOKEN(sym_identifier);
        case 56:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(57);
            ACCEPT_TOKEN(sym_identifier);
        case 57:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'd')
                ADVANCE(58);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 60:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(61);
            ACCEPT_TOKEN(sym_identifier);
        case 61:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(62);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 66:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(67);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 69:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'o') ||
                ('q' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'p')
                ADVANCE(70);
            ACCEPT_TOKEN(sym_identifier);
        case 70:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(71);
            ACCEPT_TOKEN(sym_identifier);
        case 71:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'd')
                ADVANCE(72);
            ACCEPT_TOKEN(sym_identifier);
        case 72:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(73);
            ACCEPT_TOKEN(sym_identifier);
        case 73:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'e') ||
                ('g' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'f')
                ADVANCE(74);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 76:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(77);
            ACCEPT_TOKEN(sym_identifier);
        case 77:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(78);
            ACCEPT_TOKEN(sym_identifier);
        case 78:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'f') ||
                ('h' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'g')
                ADVANCE(79);
            ACCEPT_TOKEN(sym_identifier);
        case 79:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'm') ||
                ('o' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'n')
                ADVANCE(80);
            ACCEPT_TOKEN(sym_identifier);
        case 80:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(81);
            ACCEPT_TOKEN(sym_identifier);
        case 81:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'c') ||
                ('e' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'd')
                ADVANCE(82);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 84:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(85);
            ACCEPT_TOKEN(sym_identifier);
        case 85:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('b' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'a')
                ADVANCE(86);
            ACCEPT_TOKEN(sym_identifier);
        case 86:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 's') ||
                ('u' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(87);
            ACCEPT_TOKEN(sym_identifier);
        case 87:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'h') ||
                ('j' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'i')
                ADVANCE(88);
            ACCEPT_TOKEN(sym_identifier);
        case 88:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'k') ||
                ('m' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'l')
                ADVANCE(89);
            ACCEPT_TOKEN(sym_identifier);
        case 89:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(90);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 94:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(64);
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
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
            ACCEPT_TOKEN(sym_identifier);
        case 134:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(43);
            ACCEPT_TOKEN(sym_identifier);
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
                ADVANCE(157);
            if (lookahead == '/')
                ADVANCE(146);
            if (lookahead == '\\')
                ADVANCE(154);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(156);
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
                ADVANCE(154);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(156);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 146:
            if (lookahead == '*')
                ADVANCE(147);
            if (lookahead == '/')
                ADVANCE(152);
            if (lookahead == '\\')
                ADVANCE(154);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(156);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 147:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '*')
                ADVANCE(148);
            if (lookahead == '\\')
                ADVANCE(150);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(147);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 148:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(149);
            if (lookahead == '\\')
                ADVANCE(150);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(147);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 149:
            ACCEPT_TOKEN(sym_comment);
        case 150:
            if (lookahead == '\n')
                ADVANCE(151);
            if (lookahead == '*')
                ADVANCE(148);
            if (lookahead == '\\')
                ADVANCE(150);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(147);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 151:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '*')
                ADVANCE(148);
            if (lookahead == '\\')
                ADVANCE(150);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(147);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 152:
            if (lookahead == '\\')
                ADVANCE(153);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(152);
            ACCEPT_TOKEN(sym_comment);
        case 153:
            if (lookahead == '\\')
                ADVANCE(153);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(152);
            ACCEPT_TOKEN(sym_comment);
        case 154:
            if (lookahead == '\n')
                ADVANCE(155);
            if (lookahead == '\\')
                ADVANCE(154);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(156);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 155:
            if (lookahead == '\\')
                ADVANCE(154);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(156);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 156:
            if (lookahead == '\\')
                ADVANCE(154);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(156);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 157:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_LF);
        case 158:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(158);
            if (lookahead == '\n')
                ADVANCE(159);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 159:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_LF);
        case 160:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(160);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            LEX_ERROR();
        case 161:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(161);
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
        case 162:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(162);
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
        case 163:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'n') ||
                ('p' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'o')
                ADVANCE(164);
            ACCEPT_TOKEN(sym_identifier);
        case 164:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'q') ||
                ('s' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'r')
                ADVANCE(165);
            ACCEPT_TOKEN(sym_identifier);
        case 165:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            ACCEPT_TOKEN(anon_sym_for);
        case 166:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(166);
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
        case 167:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(167);
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
        case 168:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(168);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '.')
                ADVANCE(169);
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
        case 169:
            ACCEPT_TOKEN(anon_sym_DOT);
        case 170:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(170);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(110);
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
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(131);
            if (lookahead == '}')
                ADVANCE(110);
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
            if (lookahead == '=')
                ADVANCE(131);
            LEX_ERROR();
        case 173:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(173);
            if (lookahead == '.')
                ADVANCE(169);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(131);
            if (lookahead == '[')
                ADVANCE(114);
            LEX_ERROR();
        case 174:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(174);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '.')
                ADVANCE(169);
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
        case 175:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(175);
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
        case 176:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(176);
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
        case 177:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(177);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 178:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(178);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 179:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(179);
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
        case 180:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(180);
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
        case 181:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(181);
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
        case 182:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(182);
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
                ADVANCE(163);
            if (lookahead == '{')
                ADVANCE(105);
            LEX_ERROR();
        case 183:
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
        case 184:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_LF);
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
    [233] = 158,
    [234] = 1,
    [235] = 1,
    [236] = 96,
    [237] = 92,
    [238] = 91,
    [239] = 160,
    [240] = 161,
    [241] = 161,
    [242] = 96,
    [243] = 96,
    [244] = 161,
    [245] = 115,
    [246] = 125,
    [247] = 126,
    [248] = 161,
    [249] = 106,
    [250] = 161,
    [251] = 161,
    [252] = 129,
    [253] = 161,
    [254] = 161,
    [255] = 141,
    [256] = 161,
    [257] = 1,
    [258] = 100,
    [259] = 162,
    [260] = 96,
    [261] = 1,
    [262] = 166,
    [263] = 160,
    [264] = 167,
    [265] = 167,
    [266] = 168,
    [267] = 132,
    [268] = 135,
    [269] = 167,
    [270] = 167,
    [271] = 136,
    [272] = 135,
    [273] = 135,
    [274] = 167,
    [275] = 167,
    [276] = 137,
    [277] = 167,
    [278] = 106,
    [279] = 167,
    [280] = 167,
    [281] = 106,
    [282] = 140,
    [283] = 167,
    [284] = 135,
    [285] = 167,
    [286] = 170,
    [287] = 170,
    [288] = 166,
    [289] = 171,
    [290] = 171,
    [291] = 172,
    [292] = 168,
    [293] = 135,
    [294] = 99,
    [295] = 132,
    [296] = 135,
    [297] = 171,
    [298] = 171,
    [299] = 136,
    [300] = 135,
    [301] = 135,
    [302] = 171,
    [303] = 171,
    [304] = 137,
    [305] = 171,
    [306] = 106,
    [307] = 171,
    [308] = 171,
    [309] = 106,
    [310] = 140,
    [311] = 171,
    [312] = 135,
    [313] = 171,
    [314] = 173,
    [315] = 172,
    [316] = 129,
    [317] = 173,
    [318] = 172,
    [319] = 170,
    [320] = 170,
    [321] = 174,
    [322] = 170,
    [323] = 166,
    [324] = 170,
    [325] = 170,
    [326] = 166,
    [327] = 135,
    [328] = 171,
    [329] = 170,
    [330] = 160,
    [331] = 174,
    [332] = 160,
    [333] = 135,
    [334] = 167,
    [335] = 160,
    [336] = 175,
    [337] = 175,
    [338] = 96,
    [339] = 96,
    [340] = 175,
    [341] = 115,
    [342] = 125,
    [343] = 126,
    [344] = 175,
    [345] = 106,
    [346] = 175,
    [347] = 175,
    [348] = 129,
    [349] = 175,
    [350] = 175,
    [351] = 141,
    [352] = 175,
    [353] = 100,
    [354] = 92,
    [355] = 96,
    [356] = 162,
    [357] = 162,
    [358] = 176,
    [359] = 176,
    [360] = 112,
    [361] = 177,
    [362] = 162,
    [363] = 1,
    [364] = 132,
    [365] = 135,
    [366] = 178,
    [367] = 179,
    [368] = 180,
    [369] = 92,
    [370] = 96,
    [371] = 181,
    [372] = 176,
    [373] = 100,
    [374] = 176,
    [375] = 136,
    [376] = 176,
    [377] = 137,
    [378] = 182,
    [379] = 162,
    [380] = 106,
    [381] = 182,
    [382] = 162,
    [383] = 182,
    [384] = 162,
    [385] = 136,
    [386] = 135,
    [387] = 136,
    [388] = 135,
    [389] = 135,
    [390] = 176,
    [391] = 176,
    [392] = 137,
    [393] = 176,
    [394] = 106,
    [395] = 176,
    [396] = 176,
    [397] = 176,
    [398] = 137,
    [399] = 106,
    [400] = 182,
    [401] = 162,
    [402] = 181,
    [403] = 181,
    [404] = 176,
    [405] = 136,
    [406] = 137,
    [407] = 106,
    [408] = 182,
    [409] = 162,
    [410] = 160,
    [411] = 175,
    [412] = 100,
    [413] = 181,
    [414] = 181,
    [415] = 96,
    [416] = 160,
    [417] = 175,
    [418] = 100,
    [419] = 181,
    [420] = 176,
    [421] = 106,
    [422] = 140,
    [423] = 176,
    [424] = 135,
    [425] = 176,
    [426] = 112,
    [427] = 177,
    [428] = 162,
    [429] = 162,
    [430] = 162,
    [431] = 1,
    [432] = 112,
    [433] = 100,
    [434] = 162,
    [435] = 160,
    [436] = 175,
    [437] = 100,
    [438] = 162,
    [439] = 162,
    [440] = 96,
    [441] = 160,
    [442] = 175,
    [443] = 100,
    [444] = 162,
    [445] = 1,
    [446] = 96,
    [447] = 160,
    [448] = 161,
    [449] = 1,
    [450] = 100,
    [451] = 1,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction *ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_translation_unit] = ACTIONS(SHIFT(1)),
        [sym_preproc_define] = ACTIONS(SHIFT(2)),
        [sym_function_definition] = ACTIONS(SHIFT(2)),
        [sym_declaration_specifiers] = ACTIONS(SHIFT(3)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(5)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(2)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(7)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(10)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_translation_unit, 0)),
        [anon_sym_POUNDdefine] = ACTIONS(SHIFT(11)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(14)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [1] = {
        [ts_builtin_sym_end] = ACTIONS(ACCEPT_INPUT()),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [2] = {
        [sym_preproc_define] = ACTIONS(SHIFT(2)),
        [sym_function_definition] = ACTIONS(SHIFT(2)),
        [sym_declaration_specifiers] = ACTIONS(SHIFT(3)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(5)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(2)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(238)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(10)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 1)),
        [anon_sym_POUNDdefine] = ACTIONS(SHIFT(11)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(14)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [3] = {
        [sym__type_specifier] = ACTIONS(SHIFT(446)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [4] = {
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(237)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [5] = {
        [sym__init_declarator] = ACTIONS(SHIFT(239)),
        [sym__declarator] = ACTIONS(SHIFT(240)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(241)),
        [sym_function_declarator] = ACTIONS(SHIFT(241)),
        [sym_array_declarator] = ACTIONS(SHIFT(241)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(242)),
        [anon_sym_STAR] = ACTIONS(SHIFT(243)),
        [sym_identifier] = ACTIONS(SHIFT(241)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [6] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [7] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_translation_unit, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [8] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration_specifiers, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [9] = {
        [sym_identifier] = ACTIONS(SHIFT(236)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [sym_identifier] = ACTIONS(SHIFT(231)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [12] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_storage_class_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [13] = {
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(230)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_numeric_type_specifier_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(222)),
        [sym_identifier] = ACTIONS(SHIFT(223)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [15] = {
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [16] = {
        [sym__init_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym__declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1), SHIFT(17)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [17] = {
        [sym__type_specifier] = ACTIONS(SHIFT(18)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(19)),
        [sym_struct_specifier] = ACTIONS(SHIFT(19)),
        [sym_macro_type] = ACTIONS(SHIFT(19)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(21)),
        [sym_identifier] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [18] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(221)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [sym_identifier] = ACTIONS(SHIFT(220)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(26)),
        [sym_identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(23)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [23] = {
        [sym__type_specifier] = ACTIONS(SHIFT(24)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(19)),
        [sym_struct_specifier] = ACTIONS(SHIFT(19)),
        [sym_macro_type] = ACTIONS(SHIFT(19)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(21)),
        [sym_identifier] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [24] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(25)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [25] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [26] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(218)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(219)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [27] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(28)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [28] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(33)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(35)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [29] = {
        [sym__declarator] = ACTIONS(SHIFT(51)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(52)),
        [sym_function_declarator] = ACTIONS(SHIFT(52)),
        [sym_array_declarator] = ACTIONS(SHIFT(52)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(53)),
        [anon_sym_STAR] = ACTIONS(SHIFT(54)),
        [sym_identifier] = ACTIONS(SHIFT(52)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [30] = {
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [31] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(50)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 1)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [32] = {
        [sym_identifier] = ACTIONS(SHIFT(49)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [33] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(48)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [34] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(40)),
        [sym_identifier] = ACTIONS(SHIFT(41)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [35] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [36] = {
        [sym__declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1), SHIFT(37)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [37] = {
        [sym__type_specifier] = ACTIONS(SHIFT(38)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(19)),
        [sym_struct_specifier] = ACTIONS(SHIFT(19)),
        [sym_macro_type] = ACTIONS(SHIFT(19)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(21)),
        [sym_identifier] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [38] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(39)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [39] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [40] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(46)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(47)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [41] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(42)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [42] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(43)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(44)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [43] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(45)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [44] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [45] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [46] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(44)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [47] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [48] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [49] = {
        [sym__declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [50] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_struct_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [51] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(56)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(57)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [52] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__declarator, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [53] = {
        [sym__declarator] = ACTIONS(SHIFT(216)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194)),
        [sym_function_declarator] = ACTIONS(SHIFT(194)),
        [sym_array_declarator] = ACTIONS(SHIFT(194)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [54] = {
        [sym__declarator] = ACTIONS(SHIFT(55)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(52)),
        [sym_function_declarator] = ACTIONS(SHIFT(52)),
        [sym_array_declarator] = ACTIONS(SHIFT(52)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(53)),
        [anon_sym_STAR] = ACTIONS(SHIFT(54)),
        [sym_identifier] = ACTIONS(SHIFT(52)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [55] = {
        [sym__type_specifier] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [sym_macro_type] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_long] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_short] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(56)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(57)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [56] = {
        [sym__expression] = ACTIONS(SHIFT(213)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(214)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [57] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(60)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(61)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [58] = {
        [sym__type_specifier] = ACTIONS(SHIFT(211)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [59] = {
        [sym__declarator] = ACTIONS(SHIFT(68)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(69)),
        [sym_function_declarator] = ACTIONS(SHIFT(69)),
        [sym_array_declarator] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_STAR] = ACTIONS(SHIFT(71)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [60] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(62)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(64)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [61] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [62] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(67)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [63] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(65)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [64] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [65] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(66)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_function_declarator_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [66] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_function_declarator_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [67] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [68] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(73)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [69] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [70] = {
        [sym__declarator] = ACTIONS(SHIFT(193)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194)),
        [sym_function_declarator] = ACTIONS(SHIFT(194)),
        [sym_array_declarator] = ACTIONS(SHIFT(194)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [71] = {
        [sym__declarator] = ACTIONS(SHIFT(72)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(69)),
        [sym_function_declarator] = ACTIONS(SHIFT(69)),
        [sym_array_declarator] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_STAR] = ACTIONS(SHIFT(71)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [72] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(73)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
        [sym__expression] = ACTIONS(SHIFT(80)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(82)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [74] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(75)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(76)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [75] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(77)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(78)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [76] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [77] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(79)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [78] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [79] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [80] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(192)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [82] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [83] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115)),
        [sym_type_name] = ACTIONS(SHIFT(187)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117)),
        [sym__expression] = ACTIONS(SHIFT(188)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [sym_macro_type] = ACTIONS(SHIFT(115)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_const] = ACTIONS(SHIFT(125)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [sym__expression] = ACTIONS(SHIFT(86)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [sym__expression] = ACTIONS(SHIFT(92)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(95)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [sym__expression] = ACTIONS(SHIFT(91)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [sym__expression] = ACTIONS(SHIFT(90)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(184)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(185)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115)),
        [sym_type_name] = ACTIONS(SHIFT(116)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117)),
        [sym__expression] = ACTIONS(SHIFT(118)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [sym_macro_type] = ACTIONS(SHIFT(115)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_const] = ACTIONS(SHIFT(125)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [sym__expression] = ACTIONS(SHIFT(98)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [99] = {
        [sym__expression] = ACTIONS(SHIFT(104)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(105)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [sym__expression] = ACTIONS(SHIFT(103)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [sym__expression] = ACTIONS(SHIFT(102)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [103] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(106)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(109)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [106] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(113)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [107] = {
        [sym__expression] = ACTIONS(SHIFT(111)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [108] = {
        [sym__expression] = ACTIONS(SHIFT(110)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(112)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(183)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(160)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(160)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(160)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(162)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [116] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(181)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [117] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(180)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(125)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(179)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [119] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [120] = {
        [sym_identifier] = ACTIONS(SHIFT(178)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [121] = {
        [sym__type_specifier] = ACTIONS(SHIFT(157)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115)),
        [sym_macro_type] = ACTIONS(SHIFT(115)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [sym_identifier] = ACTIONS(SHIFT(158)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [122] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(150)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [123] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115)),
        [sym_type_name] = ACTIONS(SHIFT(142)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117)),
        [sym__expression] = ACTIONS(SHIFT(143)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [sym_macro_type] = ACTIONS(SHIFT(115)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_const] = ACTIONS(SHIFT(125)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [124] = {
        [sym__expression] = ACTIONS(SHIFT(130)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(131)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [125] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym_type_qualifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1), SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
        [sym__type_specifier] = ACTIONS(SHIFT(128)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(19)),
        [sym_struct_specifier] = ACTIONS(SHIFT(19)),
        [sym_macro_type] = ACTIONS(SHIFT(19)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(20)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(21)),
        [sym_identifier] = ACTIONS(SHIFT(22)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(129)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [131] = {
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
        [sym__expression] = ACTIONS(SHIFT(137)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(138)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [133] = {
        [sym__expression] = ACTIONS(SHIFT(136)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(131)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [sym__expression] = ACTIONS(SHIFT(135)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(131)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(139)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(140)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [139] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(141)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [140] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(145)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [144] = {
        [sym__expression] = ACTIONS(SHIFT(146)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(131)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [145] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [sym__expression] = ACTIONS(SHIFT(148)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(131)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(155)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(156)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(151)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(152)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(153)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(154)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(153)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(159)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(160)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(160)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(160)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(162)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1), SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(164)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(165)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__abstract_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(176)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(160)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(160)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(160)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161)),
        [anon_sym_STAR] = ACTIONS(SHIFT(162)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(163)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(160)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(160)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(160)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE_FRAGILE(sym_abstract_pointer_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(161)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_abstract_pointer_declarator, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(162)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(164)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(165)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_abstract_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [sym__expression] = ACTIONS(SHIFT(171)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(172)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(166)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(167)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(168)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(169)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(170)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(174)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [172] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [sym__expression] = ACTIONS(SHIFT(175)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(164)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(165)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(177)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__abstract_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [180] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [sym__expression] = ACTIONS(SHIFT(182)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(164)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(165)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(186)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [185] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [186] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(190)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [188] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(189)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [sym__expression] = ACTIONS(SHIFT(191)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(210)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [sym__declarator] = ACTIONS(SHIFT(208)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194)),
        [sym_function_declarator] = ACTIONS(SHIFT(194)),
        [sym_array_declarator] = ACTIONS(SHIFT(194)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [sym__declarator] = ACTIONS(SHIFT(197)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194)),
        [sym_function_declarator] = ACTIONS(SHIFT(194)),
        [sym_array_declarator] = ACTIONS(SHIFT(194)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [sym__expression] = ACTIONS(SHIFT(205)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(206)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(200)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(201)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(202)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(203)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(204)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(207)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [206] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [207] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(209)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [209] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [sym__declarator] = ACTIONS(SHIFT(212)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(69)),
        [sym_function_declarator] = ACTIONS(SHIFT(69)),
        [sym_array_declarator] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_STAR] = ACTIONS(SHIFT(71)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(73)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [213] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(215)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(217)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
        [sym__type_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__declarator, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [218] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [219] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [221] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym__declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(228)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(229)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [224] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(225)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(226)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [225] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(227)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [226] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [227] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [228] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(226)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym__declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_numeric_type_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [231] = {
        [anon_sym_LF] = ACTIONS(SHIFT(232)),
        [sym_preproc_arg] = ACTIONS(SHIFT(233)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_preproc_define, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [233] = {
        [anon_sym_LF] = ACTIONS(SHIFT(234)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_preproc_define, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 2)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym__declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [237] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_declaration_specifiers_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [238] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(258)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(261)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [240] = {
        [sym_compound_statement] = ACTIONS(SHIFT(257)),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(258)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(259)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(261)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(245)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(246)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [241] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym__declarator, 1)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
        [sym__declarator] = ACTIONS(SHIFT(255)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194)),
        [sym_function_declarator] = ACTIONS(SHIFT(194)),
        [sym_array_declarator] = ACTIONS(SHIFT(194)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [243] = {
        [sym__declarator] = ACTIONS(SHIFT(244)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(241)),
        [sym_function_declarator] = ACTIONS(SHIFT(241)),
        [sym_array_declarator] = ACTIONS(SHIFT(241)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(242)),
        [anon_sym_STAR] = ACTIONS(SHIFT(243)),
        [sym_identifier] = ACTIONS(SHIFT(241)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [244] = {
        [sym_compound_statement] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(245)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(246)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
        [sym__expression] = ACTIONS(SHIFT(252)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(253)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [246] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(247)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(248)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [247] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(249)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(250)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [250] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(254)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(256)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym__declarator, 3)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_definition, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(445)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [259] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(354)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(355)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(356)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(357)),
        [sym__expression] = ACTIONS(SHIFT(358)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [sym__statement] = ACTIONS(SHIFT(356)),
        [sym_for_statement] = ACTIONS(SHIFT(357)),
        [sym_expression_statement] = ACTIONS(SHIFT(357)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(360)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(361)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(14)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(363)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [anon_sym_for] = ACTIONS(SHIFT(366)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(367)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [260] = {
        [sym__init_declarator] = ACTIONS(SHIFT(335)),
        [sym__declarator] = ACTIONS(SHIFT(336)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337)),
        [sym_function_declarator] = ACTIONS(SHIFT(337)),
        [sym_array_declarator] = ACTIONS(SHIFT(337)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339)),
        [sym_identifier] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [261] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [262] = {
        [sym_initializer] = ACTIONS(SHIFT(263)),
        [sym__expression] = ACTIONS(SHIFT(264)),
        [sym_cast_expression] = ACTIONS(SHIFT(265)),
        [sym_math_expression] = ACTIONS(SHIFT(265)),
        [sym_call_expression] = ACTIONS(SHIFT(265)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(266)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268)),
        [sym_string] = ACTIONS(SHIFT(265)),
        [sym_identifier] = ACTIONS(SHIFT(269)),
        [sym_number] = ACTIONS(SHIFT(265)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [264] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(333)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271)),
        [anon_sym_STAR] = ACTIONS(SHIFT(272)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [265] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [sym_initializer] = ACTIONS(SHIFT(286)),
        [sym_initializer_list] = ACTIONS(SHIFT(287)),
        [sym_designation] = ACTIONS(SHIFT(288)),
        [sym__expression] = ACTIONS(SHIFT(289)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(291)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [267] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115)),
        [sym_type_name] = ACTIONS(SHIFT(281)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117)),
        [sym__expression] = ACTIONS(SHIFT(282)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [sym_macro_type] = ACTIONS(SHIFT(115)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_const] = ACTIONS(SHIFT(125)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [268] = {
        [sym__expression] = ACTIONS(SHIFT(270)),
        [sym_cast_expression] = ACTIONS(SHIFT(265)),
        [sym_math_expression] = ACTIONS(SHIFT(265)),
        [sym_call_expression] = ACTIONS(SHIFT(265)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268)),
        [sym_string] = ACTIONS(SHIFT(265)),
        [sym_identifier] = ACTIONS(SHIFT(269)),
        [sym_number] = ACTIONS(SHIFT(265)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [269] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [270] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271)),
        [anon_sym_STAR] = ACTIONS(SHIFT(272)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [271] = {
        [sym__expression] = ACTIONS(SHIFT(276)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(277)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [272] = {
        [sym__expression] = ACTIONS(SHIFT(275)),
        [sym_cast_expression] = ACTIONS(SHIFT(265)),
        [sym_math_expression] = ACTIONS(SHIFT(265)),
        [sym_call_expression] = ACTIONS(SHIFT(265)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268)),
        [sym_string] = ACTIONS(SHIFT(265)),
        [sym_identifier] = ACTIONS(SHIFT(269)),
        [sym_number] = ACTIONS(SHIFT(265)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [273] = {
        [sym__expression] = ACTIONS(SHIFT(274)),
        [sym_cast_expression] = ACTIONS(SHIFT(265)),
        [sym_math_expression] = ACTIONS(SHIFT(265)),
        [sym_call_expression] = ACTIONS(SHIFT(265)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268)),
        [sym_string] = ACTIONS(SHIFT(265)),
        [sym_identifier] = ACTIONS(SHIFT(269)),
        [sym_number] = ACTIONS(SHIFT(265)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [274] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271)),
        [anon_sym_STAR] = ACTIONS(SHIFT(272)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [275] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [276] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(278)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(279)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [277] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [278] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(280)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [279] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [280] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [281] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(284)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [282] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(283)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [283] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [284] = {
        [sym__expression] = ACTIONS(SHIFT(285)),
        [sym_cast_expression] = ACTIONS(SHIFT(265)),
        [sym_math_expression] = ACTIONS(SHIFT(265)),
        [sym_call_expression] = ACTIONS(SHIFT(265)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268)),
        [sym_string] = ACTIONS(SHIFT(265)),
        [sym_identifier] = ACTIONS(SHIFT(269)),
        [sym_number] = ACTIONS(SHIFT(265)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [285] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [286] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [287] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(330)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(331)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [288] = {
        [sym_initializer] = ACTIONS(SHIFT(329)),
        [sym__expression] = ACTIONS(SHIFT(289)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [289] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(327)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299)),
        [anon_sym_STAR] = ACTIONS(SHIFT(300)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(301)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [290] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [291] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(326)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [292] = {
        [sym_initializer] = ACTIONS(SHIFT(286)),
        [sym_initializer_list] = ACTIONS(SHIFT(319)),
        [sym_designation] = ACTIONS(SHIFT(288)),
        [sym__expression] = ACTIONS(SHIFT(289)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(291)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [293] = {
        [sym__expression] = ACTIONS(SHIFT(316)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [294] = {
        [sym_identifier] = ACTIONS(SHIFT(314)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [295] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115)),
        [sym_type_name] = ACTIONS(SHIFT(309)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117)),
        [sym__expression] = ACTIONS(SHIFT(310)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [sym_macro_type] = ACTIONS(SHIFT(115)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_const] = ACTIONS(SHIFT(125)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [296] = {
        [sym__expression] = ACTIONS(SHIFT(298)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [297] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [298] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299)),
        [anon_sym_STAR] = ACTIONS(SHIFT(300)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(301)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [299] = {
        [sym__expression] = ACTIONS(SHIFT(304)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(305)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [300] = {
        [sym__expression] = ACTIONS(SHIFT(303)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [301] = {
        [sym__expression] = ACTIONS(SHIFT(302)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [302] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299)),
        [anon_sym_STAR] = ACTIONS(SHIFT(300)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [303] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [304] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(306)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(307)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [305] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [306] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(308)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [307] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [308] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [309] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(312)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [310] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(311)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [311] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [312] = {
        [sym__expression] = ACTIONS(SHIFT(313)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [313] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [314] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(315)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [315] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [316] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(317)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [317] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(318)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [318] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [319] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(320)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(321)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [320] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [321] = {
        [sym_initializer] = ACTIONS(SHIFT(322)),
        [sym_designation] = ACTIONS(SHIFT(323)),
        [sym__expression] = ACTIONS(SHIFT(289)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(291)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(324)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [322] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [323] = {
        [sym_initializer] = ACTIONS(SHIFT(325)),
        [sym__expression] = ACTIONS(SHIFT(289)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [324] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [325] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [326] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [327] = {
        [sym__expression] = ACTIONS(SHIFT(328)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [328] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_EQ] = ACTIONS(SHIFT(327)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(299)),
        [anon_sym_STAR] = ACTIONS(SHIFT(300)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(301)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [329] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [330] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [331] = {
        [sym_initializer] = ACTIONS(SHIFT(322)),
        [sym_designation] = ACTIONS(SHIFT(323)),
        [sym__expression] = ACTIONS(SHIFT(289)),
        [sym_cast_expression] = ACTIONS(SHIFT(290)),
        [sym_math_expression] = ACTIONS(SHIFT(290)),
        [sym_call_expression] = ACTIONS(SHIFT(290)),
        [sym_pointer_expression] = ACTIONS(SHIFT(290)),
        [sym_assignment_expression] = ACTIONS(SHIFT(290)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(291)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(292)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(332)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(293)),
        [anon_sym_DOT] = ACTIONS(SHIFT(294)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(296)),
        [anon_sym_AMP] = ACTIONS(SHIFT(296)),
        [sym_string] = ACTIONS(SHIFT(290)),
        [sym_identifier] = ACTIONS(SHIFT(297)),
        [sym_number] = ACTIONS(SHIFT(290)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [332] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [333] = {
        [sym__expression] = ACTIONS(SHIFT(334)),
        [sym_cast_expression] = ACTIONS(SHIFT(265)),
        [sym_math_expression] = ACTIONS(SHIFT(265)),
        [sym_call_expression] = ACTIONS(SHIFT(265)),
        [sym_pointer_expression] = ACTIONS(SHIFT(265)),
        [sym_assignment_expression] = ACTIONS(SHIFT(265)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(267)),
        [anon_sym_STAR] = ACTIONS(SHIFT(268)),
        [anon_sym_AMP] = ACTIONS(SHIFT(268)),
        [sym_string] = ACTIONS(SHIFT(265)),
        [sym_identifier] = ACTIONS(SHIFT(269)),
        [sym_number] = ACTIONS(SHIFT(265)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [334] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_EQ] = ACTIONS(SHIFT(333)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(271)),
        [anon_sym_STAR] = ACTIONS(SHIFT(272)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(273)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [335] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(353)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [336] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(353)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [337] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [338] = {
        [sym__declarator] = ACTIONS(SHIFT(351)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(194)),
        [sym_function_declarator] = ACTIONS(SHIFT(194)),
        [sym_array_declarator] = ACTIONS(SHIFT(194)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(195)),
        [anon_sym_STAR] = ACTIONS(SHIFT(196)),
        [sym_identifier] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [339] = {
        [sym__declarator] = ACTIONS(SHIFT(340)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337)),
        [sym_function_declarator] = ACTIONS(SHIFT(337)),
        [sym_array_declarator] = ACTIONS(SHIFT(337)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339)),
        [sym_identifier] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [340] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [341] = {
        [sym__expression] = ACTIONS(SHIFT(348)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [sym_assignment_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(349)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(85)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [342] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(343)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(344)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [343] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(345)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(346)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [344] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [345] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(347)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [346] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [347] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [348] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(173)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(87)),
        [anon_sym_STAR] = ACTIONS(SHIFT(88)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(89)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [349] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [350] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [351] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(198)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(199)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(352)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [352] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [353] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [354] = {
        [sym__type_specifier] = ACTIONS(SHIFT(440)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [355] = {
        [sym__init_declarator] = ACTIONS(SHIFT(435)),
        [sym__declarator] = ACTIONS(SHIFT(436)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337)),
        [sym_function_declarator] = ACTIONS(SHIFT(337)),
        [sym_array_declarator] = ACTIONS(SHIFT(337)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339)),
        [sym_identifier] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [356] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(354)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(355)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(356)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(357)),
        [sym__expression] = ACTIONS(SHIFT(358)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [sym__statement] = ACTIONS(SHIFT(356)),
        [sym_for_statement] = ACTIONS(SHIFT(357)),
        [sym_expression_statement] = ACTIONS(SHIFT(357)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(432)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(433)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(14)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [anon_sym_for] = ACTIONS(SHIFT(366)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(367)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [357] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_math_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_call_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_for_statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_macro_type] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym__statement, 1)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_static] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_register] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_for] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_string] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [358] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(434)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [359] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [360] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(431)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [361] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(431)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(430)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [362] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(354)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(355)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(356)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym_compound_statement] = ACTIONS(SHIFT(357)),
        [sym__expression] = ACTIONS(SHIFT(358)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [sym__statement] = ACTIONS(SHIFT(356)),
        [sym_for_statement] = ACTIONS(SHIFT(357)),
        [sym_expression_statement] = ACTIONS(SHIFT(357)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(426)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(427)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(14)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(428)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [anon_sym_for] = ACTIONS(SHIFT(366)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(367)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [363] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [364] = {
        [sym__type_specifier] = ACTIONS(SHIFT(114)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(115)),
        [sym_struct_specifier] = ACTIONS(SHIFT(115)),
        [sym_type_name] = ACTIONS(SHIFT(421)),
        [sym_type_qualifier] = ACTIONS(SHIFT(117)),
        [sym__expression] = ACTIONS(SHIFT(422)),
        [sym_cast_expression] = ACTIONS(SHIFT(119)),
        [sym_math_expression] = ACTIONS(SHIFT(119)),
        [sym_call_expression] = ACTIONS(SHIFT(119)),
        [sym_pointer_expression] = ACTIONS(SHIFT(119)),
        [sym_assignment_expression] = ACTIONS(SHIFT(119)),
        [sym_macro_type] = ACTIONS(SHIFT(115)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(120)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(121)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(122)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(123)),
        [anon_sym_STAR] = ACTIONS(SHIFT(124)),
        [anon_sym_const] = ACTIONS(SHIFT(125)),
        [anon_sym_restrict] = ACTIONS(SHIFT(125)),
        [anon_sym_volatile] = ACTIONS(SHIFT(125)),
        [anon_sym_AMP] = ACTIONS(SHIFT(124)),
        [sym_string] = ACTIONS(SHIFT(119)),
        [sym_identifier] = ACTIONS(SHIFT(126)),
        [sym_number] = ACTIONS(SHIFT(119)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [365] = {
        [sym__expression] = ACTIONS(SHIFT(420)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [366] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(368)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [367] = {
        [sym__init_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym__declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1), SHIFT(17)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1), REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_identifier] = ACTIONS(REDUCE_FRAGILE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [368] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(369)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(370)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(371)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym__expression] = ACTIONS(SHIFT(372)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(373)),
        [anon_sym_typedef] = ACTIONS(SHIFT(12)),
        [anon_sym_extern] = ACTIONS(SHIFT(12)),
        [anon_sym_static] = ACTIONS(SHIFT(12)),
        [anon_sym_auto] = ACTIONS(SHIFT(12)),
        [anon_sym_register] = ACTIONS(SHIFT(12)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(14)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(371)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(367)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [369] = {
        [sym__type_specifier] = ACTIONS(SHIFT(415)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(14)),
        [sym_identifier] = ACTIONS(SHIFT(16)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [370] = {
        [sym__init_declarator] = ACTIONS(SHIFT(410)),
        [sym__declarator] = ACTIONS(SHIFT(411)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337)),
        [sym_function_declarator] = ACTIONS(SHIFT(337)),
        [sym_array_declarator] = ACTIONS(SHIFT(337)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339)),
        [sym_identifier] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [371] = {
        [sym__expression] = ACTIONS(SHIFT(374)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(375)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [372] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(403)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [373] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(402)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [374] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(385)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [375] = {
        [sym__expression] = ACTIONS(SHIFT(377)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(378)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [376] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [377] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(380)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(381)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [378] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357)),
        [sym__expression] = ACTIONS(SHIFT(358)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [sym__statement] = ACTIONS(SHIFT(379)),
        [sym_for_statement] = ACTIONS(SHIFT(357)),
        [sym_expression_statement] = ACTIONS(SHIFT(357)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [anon_sym_for] = ACTIONS(SHIFT(366)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [379] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 6)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [380] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(383)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [381] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357)),
        [sym__expression] = ACTIONS(SHIFT(358)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [sym__statement] = ACTIONS(SHIFT(382)),
        [sym_for_statement] = ACTIONS(SHIFT(357)),
        [sym_expression_statement] = ACTIONS(SHIFT(357)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [anon_sym_for] = ACTIONS(SHIFT(366)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [382] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 7)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [383] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357)),
        [sym__expression] = ACTIONS(SHIFT(358)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [sym__statement] = ACTIONS(SHIFT(384)),
        [sym_for_statement] = ACTIONS(SHIFT(357)),
        [sym_expression_statement] = ACTIONS(SHIFT(357)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [anon_sym_for] = ACTIONS(SHIFT(366)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [384] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 8)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [385] = {
        [sym__expression] = ACTIONS(SHIFT(398)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(381)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [386] = {
        [sym__expression] = ACTIONS(SHIFT(397)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [387] = {
        [sym__expression] = ACTIONS(SHIFT(392)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(393)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [388] = {
        [sym__expression] = ACTIONS(SHIFT(391)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [389] = {
        [sym__expression] = ACTIONS(SHIFT(390)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [390] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [391] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [392] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(394)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(395)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [393] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [394] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(396)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [395] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [396] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [397] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_assignment_expression, 3)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [398] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(399)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(383)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [399] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(400)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [400] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357)),
        [sym__expression] = ACTIONS(SHIFT(358)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [sym__statement] = ACTIONS(SHIFT(401)),
        [sym_for_statement] = ACTIONS(SHIFT(357)),
        [sym_expression_statement] = ACTIONS(SHIFT(357)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [anon_sym_for] = ACTIONS(SHIFT(366)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [401] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 9)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [402] = {
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [403] = {
        [sym__expression] = ACTIONS(SHIFT(404)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(385)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [404] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(405)),
        [anon_sym_EQ] = ACTIONS(SHIFT(386)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [405] = {
        [sym__expression] = ACTIONS(SHIFT(406)),
        [sym_cast_expression] = ACTIONS(SHIFT(93)),
        [sym_math_expression] = ACTIONS(SHIFT(93)),
        [sym_call_expression] = ACTIONS(SHIFT(93)),
        [sym_pointer_expression] = ACTIONS(SHIFT(93)),
        [sym_assignment_expression] = ACTIONS(SHIFT(93)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(383)),
        [anon_sym_STAR] = ACTIONS(SHIFT(96)),
        [anon_sym_AMP] = ACTIONS(SHIFT(96)),
        [sym_string] = ACTIONS(SHIFT(93)),
        [sym_identifier] = ACTIONS(SHIFT(97)),
        [sym_number] = ACTIONS(SHIFT(93)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [406] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(407)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(107)),
        [anon_sym_EQ] = ACTIONS(SHIFT(108)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(99)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(400)),
        [anon_sym_STAR] = ACTIONS(SHIFT(100)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(101)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [407] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(408)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [408] = {
        [sym_compound_statement] = ACTIONS(SHIFT(357)),
        [sym__expression] = ACTIONS(SHIFT(358)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [sym__statement] = ACTIONS(SHIFT(409)),
        [sym_for_statement] = ACTIONS(SHIFT(357)),
        [sym_expression_statement] = ACTIONS(SHIFT(357)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(362)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [anon_sym_for] = ACTIONS(SHIFT(366)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [409] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_declaration] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym__expression] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym__statement] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_string] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_identifier] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_number] = ACTIONS(REDUCE(sym_for_statement, 10)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [410] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(412)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(413)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [411] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(412)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(413)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [412] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(414)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [413] = {
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [414] = {
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [415] = {
        [sym__init_declarator] = ACTIONS(SHIFT(416)),
        [sym__declarator] = ACTIONS(SHIFT(417)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337)),
        [sym_function_declarator] = ACTIONS(SHIFT(337)),
        [sym_array_declarator] = ACTIONS(SHIFT(337)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339)),
        [sym_identifier] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [416] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(418)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(414)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [417] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(418)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(414)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [418] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(419)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [419] = {
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [420] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE_FRAGILE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(387)),
        [anon_sym_STAR] = ACTIONS(SHIFT(388)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(389)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [421] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(424)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [422] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(144)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(132)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(423)),
        [anon_sym_STAR] = ACTIONS(SHIFT(133)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(134)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [423] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [424] = {
        [sym__expression] = ACTIONS(SHIFT(425)),
        [sym_cast_expression] = ACTIONS(SHIFT(359)),
        [sym_math_expression] = ACTIONS(SHIFT(359)),
        [sym_call_expression] = ACTIONS(SHIFT(359)),
        [sym_pointer_expression] = ACTIONS(SHIFT(359)),
        [sym_assignment_expression] = ACTIONS(SHIFT(359)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(364)),
        [anon_sym_STAR] = ACTIONS(SHIFT(365)),
        [anon_sym_AMP] = ACTIONS(SHIFT(365)),
        [sym_string] = ACTIONS(SHIFT(359)),
        [sym_identifier] = ACTIONS(SHIFT(376)),
        [sym_number] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [425] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [426] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(429)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [427] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(429)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(430)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [428] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_compound_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [429] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [430] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 2)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [431] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_compound_statement, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [432] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [433] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(430)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [434] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [435] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(437)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(438)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [436] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(437)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(438)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [437] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(439)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [438] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 3)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [439] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [440] = {
        [sym__init_declarator] = ACTIONS(SHIFT(441)),
        [sym__declarator] = ACTIONS(SHIFT(442)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(337)),
        [sym_function_declarator] = ACTIONS(SHIFT(337)),
        [sym_array_declarator] = ACTIONS(SHIFT(337)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(338)),
        [anon_sym_STAR] = ACTIONS(SHIFT(339)),
        [sym_identifier] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [441] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(443)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(439)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [442] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(443)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(439)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(341)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(342)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [443] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(444)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [444] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_compound_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_assignment_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_for_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_expression_statement] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_for] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [445] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 4)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [446] = {
        [sym__init_declarator] = ACTIONS(SHIFT(447)),
        [sym__declarator] = ACTIONS(SHIFT(448)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(241)),
        [sym_function_declarator] = ACTIONS(SHIFT(241)),
        [sym_array_declarator] = ACTIONS(SHIFT(241)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(242)),
        [anon_sym_STAR] = ACTIONS(SHIFT(243)),
        [sym_identifier] = ACTIONS(SHIFT(241)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [447] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(450)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(445)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [448] = {
        [sym_compound_statement] = ACTIONS(SHIFT(449)),
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(450)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(259)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(260)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(445)),
        [anon_sym_EQ] = ACTIONS(SHIFT(262)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(245)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(246)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [449] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_function_definition, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [450] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(451)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [451] = {
        [sym_preproc_define] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_function_definition] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_translation_unit_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_declaration, 5)),
        [ts_builtin_sym_error] = ACTIONS(REDUCE(sym_declaration, 5)),
        [ts_builtin_sym_end] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_POUNDdefine] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_typedef] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_extern] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_static] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_auto] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_register] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
