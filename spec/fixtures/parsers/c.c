#include "tree_sitter/parser.h"

#define STATE_COUNT 387
#define SYMBOL_COUNT 79

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
    sym__statement,
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
    [sym__statement] = "_statement",
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
    [sym__statement] = {.visible = false, .named = false, .extra = false},
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
            if (lookahead == ']')
                ADVANCE(124);
            LEX_ERROR();
        case 130:
            ACCEPT_TOKEN(anon_sym_PLUS);
        case 131:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(131);
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
                ADVANCE(132);
            if (lookahead == 's')
                ADVANCE(93);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            LEX_ERROR();
        case 132:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'd') ||
                ('f' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 'e')
                ADVANCE(133);
            ACCEPT_TOKEN(sym_identifier);
        case 133:
            if (('0' <= lookahead && lookahead <= '9') ||
                ('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == '_') ||
                ('a' <= lookahead && lookahead <= 'r') ||
                ('t' <= lookahead && lookahead <= 'z'))
                ADVANCE(15);
            if (lookahead == 's')
                ADVANCE(43);
            ACCEPT_TOKEN(sym_identifier);
        case 134:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(134);
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
        case 136:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(136);
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
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 138:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(138);
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
                ADVANCE(132);
            if (lookahead == 's')
                ADVANCE(93);
            if (lookahead == 'u')
                ADVANCE(75);
            if (lookahead == 'v')
                ADVANCE(83);
            LEX_ERROR();
        case 139:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(139);
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
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '[')
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
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
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
            if (lookahead == ')')
                ADVANCE(107);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '[')
                ADVANCE(114);
            LEX_ERROR();
        case 143:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == '\n')
                ADVANCE(156);
            if (lookahead == '/')
                ADVANCE(145);
            if (lookahead == '\\')
                ADVANCE(153);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(155);
            LEX_ERROR();
        case 144:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(144);
            if (lookahead == '/')
                ADVANCE(145);
            if (lookahead == '\\')
                ADVANCE(153);
            if (!((lookahead == 0) ||
                (lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' ') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(155);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 145:
            if (lookahead == '*')
                ADVANCE(146);
            if (lookahead == '/')
                ADVANCE(151);
            if (lookahead == '\\')
                ADVANCE(153);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(155);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 146:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '*')
                ADVANCE(147);
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(146);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 147:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '/')
                ADVANCE(148);
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '/') ||
                (lookahead == '\\')))
                ADVANCE(146);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 148:
            ACCEPT_TOKEN(sym_comment);
        case 149:
            if (lookahead == '\n')
                ADVANCE(150);
            if (lookahead == '*')
                ADVANCE(147);
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(146);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 150:
            if (lookahead == '\n')
                ADVANCE(11);
            if (lookahead == '*')
                ADVANCE(147);
            if (lookahead == '\\')
                ADVANCE(149);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '*') ||
                (lookahead == '\\')))
                ADVANCE(146);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 151:
            if (lookahead == '\\')
                ADVANCE(152);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(151);
            ACCEPT_TOKEN(sym_comment);
        case 152:
            if (lookahead == '\\')
                ADVANCE(152);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(151);
            ACCEPT_TOKEN(sym_comment);
        case 153:
            if (lookahead == '\n')
                ADVANCE(154);
            if (lookahead == '\\')
                ADVANCE(153);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(155);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 154:
            if (lookahead == '\\')
                ADVANCE(153);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(155);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 155:
            if (lookahead == '\\')
                ADVANCE(153);
            if (!((lookahead == 0) ||
                (lookahead == '\n') ||
                (lookahead == '\\')))
                ADVANCE(155);
            ACCEPT_TOKEN(sym_preproc_arg);
        case 156:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_LF);
        case 157:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(157);
            if (lookahead == '\n')
                ADVANCE(158);
            if (lookahead == '/')
                ADVANCE(10);
            LEX_ERROR();
        case 158:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_LF);
        case 159:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(159);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            LEX_ERROR();
        case 160:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(160);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(161);
            if (lookahead == '[')
                ADVANCE(114);
            if (lookahead == '{')
                ADVANCE(105);
            LEX_ERROR();
        case 161:
            ACCEPT_TOKEN(anon_sym_EQ);
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
            if (lookahead == '}')
                ADVANCE(110);
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
        case 164:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(164);
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
            LEX_ERROR();
        case 165:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(165);
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '.')
                ADVANCE(166);
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
        case 166:
            ACCEPT_TOKEN(anon_sym_DOT);
        case 167:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(167);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 168:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(168);
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
            if (lookahead == '}')
                ADVANCE(110);
            LEX_ERROR();
        case 169:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(169);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(161);
            LEX_ERROR();
        case 170:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(170);
            if (lookahead == '.')
                ADVANCE(166);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == '=')
                ADVANCE(161);
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
            if (lookahead == '\"')
                ADVANCE(116);
            if (lookahead == '&')
                ADVANCE(120);
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == '*')
                ADVANCE(98);
            if (lookahead == '.')
                ADVANCE(166);
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
        case 172:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(172);
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
            LEX_ERROR();
        case 173:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(173);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '}')
                ADVANCE(110);
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
            if (lookahead == '(')
                ADVANCE(97);
            if (lookahead == ',')
                ADVANCE(127);
            if (lookahead == '/')
                ADVANCE(10);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(161);
            if (lookahead == '[')
                ADVANCE(114);
            LEX_ERROR();
        case 176:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(176);
            if (lookahead == '\n')
                ADVANCE(177);
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
                ADVANCE(166);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(161);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
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
        case 177:
            START_TOKEN();
            ACCEPT_TOKEN(anon_sym_LF);
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(2);
            if ((lookahead == '\t') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(176);
            if (lookahead == '\n')
                ADVANCE(177);
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
                ADVANCE(166);
            if (lookahead == '/')
                ADVANCE(10);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(121);
            if (lookahead == ';')
                ADVANCE(101);
            if (lookahead == '=')
                ADVANCE(161);
            if (('A' <= lookahead && lookahead <= 'Z') ||
                (lookahead == 'b') ||
                (lookahead == 'd') ||
                ('f' <= lookahead && lookahead <= 'k') ||
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
    [83] = 131,
    [84] = 134,
    [85] = 129,
    [86] = 135,
    [87] = 134,
    [88] = 134,
    [89] = 129,
    [90] = 129,
    [91] = 136,
    [92] = 136,
    [93] = 131,
    [94] = 129,
    [95] = 134,
    [96] = 136,
    [97] = 135,
    [98] = 134,
    [99] = 134,
    [100] = 136,
    [101] = 136,
    [102] = 136,
    [103] = 136,
    [104] = 106,
    [105] = 134,
    [106] = 136,
    [107] = 136,
    [108] = 106,
    [109] = 136,
    [110] = 137,
    [111] = 137,
    [112] = 106,
    [113] = 138,
    [114] = 139,
    [115] = 139,
    [116] = 99,
    [117] = 92,
    [118] = 104,
    [119] = 131,
    [120] = 134,
    [121] = 138,
    [122] = 139,
    [123] = 92,
    [124] = 106,
    [125] = 137,
    [126] = 139,
    [127] = 135,
    [128] = 134,
    [129] = 134,
    [130] = 139,
    [131] = 139,
    [132] = 136,
    [133] = 139,
    [134] = 106,
    [135] = 139,
    [136] = 139,
    [137] = 106,
    [138] = 139,
    [139] = 139,
    [140] = 134,
    [141] = 139,
    [142] = 109,
    [143] = 111,
    [144] = 109,
    [145] = 112,
    [146] = 137,
    [147] = 137,
    [148] = 112,
    [149] = 137,
    [150] = 137,
    [151] = 137,
    [152] = 140,
    [153] = 140,
    [154] = 141,
    [155] = 142,
    [156] = 140,
    [157] = 115,
    [158] = 125,
    [159] = 126,
    [160] = 140,
    [161] = 106,
    [162] = 140,
    [163] = 140,
    [164] = 129,
    [165] = 140,
    [166] = 140,
    [167] = 140,
    [168] = 140,
    [169] = 137,
    [170] = 136,
    [171] = 92,
    [172] = 134,
    [173] = 136,
    [174] = 140,
    [175] = 106,
    [176] = 129,
    [177] = 129,
    [178] = 106,
    [179] = 139,
    [180] = 129,
    [181] = 134,
    [182] = 129,
    [183] = 128,
    [184] = 140,
    [185] = 140,
    [186] = 96,
    [187] = 96,
    [188] = 140,
    [189] = 115,
    [190] = 125,
    [191] = 126,
    [192] = 140,
    [193] = 106,
    [194] = 140,
    [195] = 140,
    [196] = 129,
    [197] = 140,
    [198] = 140,
    [199] = 140,
    [200] = 140,
    [201] = 128,
    [202] = 96,
    [203] = 128,
    [204] = 129,
    [205] = 113,
    [206] = 113,
    [207] = 140,
    [208] = 113,
    [209] = 112,
    [210] = 106,
    [211] = 106,
    [212] = 96,
    [213] = 109,
    [214] = 111,
    [215] = 109,
    [216] = 112,
    [217] = 96,
    [218] = 96,
    [219] = 112,
    [220] = 96,
    [221] = 99,
    [222] = 143,
    [223] = 1,
    [224] = 157,
    [225] = 1,
    [226] = 1,
    [227] = 96,
    [228] = 159,
    [229] = 160,
    [230] = 160,
    [231] = 96,
    [232] = 96,
    [233] = 160,
    [234] = 115,
    [235] = 125,
    [236] = 126,
    [237] = 160,
    [238] = 106,
    [239] = 160,
    [240] = 160,
    [241] = 129,
    [242] = 160,
    [243] = 160,
    [244] = 140,
    [245] = 160,
    [246] = 1,
    [247] = 162,
    [248] = 163,
    [249] = 159,
    [250] = 164,
    [251] = 164,
    [252] = 165,
    [253] = 131,
    [254] = 134,
    [255] = 164,
    [256] = 135,
    [257] = 134,
    [258] = 134,
    [259] = 164,
    [260] = 164,
    [261] = 136,
    [262] = 164,
    [263] = 106,
    [264] = 164,
    [265] = 164,
    [266] = 106,
    [267] = 139,
    [268] = 164,
    [269] = 134,
    [270] = 164,
    [271] = 167,
    [272] = 167,
    [273] = 163,
    [274] = 168,
    [275] = 168,
    [276] = 169,
    [277] = 165,
    [278] = 134,
    [279] = 99,
    [280] = 131,
    [281] = 134,
    [282] = 168,
    [283] = 135,
    [284] = 134,
    [285] = 134,
    [286] = 168,
    [287] = 168,
    [288] = 136,
    [289] = 168,
    [290] = 106,
    [291] = 168,
    [292] = 168,
    [293] = 106,
    [294] = 139,
    [295] = 168,
    [296] = 134,
    [297] = 168,
    [298] = 170,
    [299] = 169,
    [300] = 129,
    [301] = 170,
    [302] = 169,
    [303] = 167,
    [304] = 167,
    [305] = 171,
    [306] = 167,
    [307] = 163,
    [308] = 167,
    [309] = 167,
    [310] = 163,
    [311] = 167,
    [312] = 159,
    [313] = 171,
    [314] = 159,
    [315] = 92,
    [316] = 96,
    [317] = 162,
    [318] = 172,
    [319] = 172,
    [320] = 162,
    [321] = 112,
    [322] = 173,
    [323] = 1,
    [324] = 131,
    [325] = 134,
    [326] = 174,
    [327] = 172,
    [328] = 135,
    [329] = 134,
    [330] = 134,
    [331] = 172,
    [332] = 172,
    [333] = 136,
    [334] = 172,
    [335] = 106,
    [336] = 172,
    [337] = 172,
    [338] = 106,
    [339] = 139,
    [340] = 172,
    [341] = 134,
    [342] = 172,
    [343] = 1,
    [344] = 162,
    [345] = 162,
    [346] = 112,
    [347] = 100,
    [348] = 159,
    [349] = 175,
    [350] = 175,
    [351] = 96,
    [352] = 96,
    [353] = 175,
    [354] = 115,
    [355] = 125,
    [356] = 126,
    [357] = 175,
    [358] = 106,
    [359] = 175,
    [360] = 175,
    [361] = 129,
    [362] = 175,
    [363] = 175,
    [364] = 140,
    [365] = 175,
    [366] = 100,
    [367] = 96,
    [368] = 162,
    [369] = 159,
    [370] = 100,
    [371] = 162,
    [372] = 96,
    [373] = 159,
    [374] = 100,
    [375] = 162,
    [376] = 100,
    [377] = 1,
    [378] = 1,
    [379] = 92,
    [380] = 96,
    [381] = 159,
    [382] = 160,
    [383] = 1,
    [384] = 100,
    [385] = 1,
    [386] = 91,
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
        [aux_sym_translation_unit_repeat1] = ACTIONS(SHIFT(386)),
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
        [sym__type_specifier] = ACTIONS(SHIFT(380)),
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
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(379)),
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
        [sym__init_declarator] = ACTIONS(SHIFT(228)),
        [sym__declarator] = ACTIONS(SHIFT(229)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(230)),
        [sym_function_declarator] = ACTIONS(SHIFT(230)),
        [sym_array_declarator] = ACTIONS(SHIFT(230)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(231)),
        [anon_sym_STAR] = ACTIONS(SHIFT(232)),
        [sym_identifier] = ACTIONS(SHIFT(230)),
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
        [sym_identifier] = ACTIONS(SHIFT(227)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [10] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(226)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [11] = {
        [sym_identifier] = ACTIONS(SHIFT(222)),
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
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(221)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_numeric_type_specifier_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [14] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(213)),
        [sym_identifier] = ACTIONS(SHIFT(214)),
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
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), SHIFT(17)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
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
        [anon_sym_RPAREN] = ACTIONS(SHIFT(212)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [19] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [20] = {
        [sym_identifier] = ACTIONS(SHIFT(211)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [21] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(26)),
        [sym_identifier] = ACTIONS(SHIFT(27)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [22] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(23)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
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
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(209)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(210)),
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
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), SHIFT(37)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
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
        [sym__declarator] = ACTIONS(SHIFT(207)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(185)),
        [sym_function_declarator] = ACTIONS(SHIFT(185)),
        [sym_array_declarator] = ACTIONS(SHIFT(185)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(186)),
        [anon_sym_STAR] = ACTIONS(SHIFT(187)),
        [sym_identifier] = ACTIONS(SHIFT(185)),
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
        [sym__type_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_struct_declaration] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_macro_type] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_signed] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_long] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_short] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_struct] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(56)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(57)),
        [sym_identifier] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [56] = {
        [sym__expression] = ACTIONS(SHIFT(204)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(205)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
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
        [sym__type_specifier] = ACTIONS(SHIFT(202)),
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
        [sym__declarator] = ACTIONS(SHIFT(184)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(185)),
        [sym_function_declarator] = ACTIONS(SHIFT(185)),
        [sym_array_declarator] = ACTIONS(SHIFT(185)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(186)),
        [anon_sym_STAR] = ACTIONS(SHIFT(187)),
        [sym_identifier] = ACTIONS(SHIFT(185)),
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
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(73)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [73] = {
        [sym__expression] = ACTIONS(SHIFT(80)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(82)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
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
        [anon_sym_RBRACK] = ACTIONS(SHIFT(183)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(SHIFT(87)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(88)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [81] = {
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
        [sym__type_specifier] = ACTIONS(SHIFT(110)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(111)),
        [sym_struct_specifier] = ACTIONS(SHIFT(111)),
        [sym_type_name] = ACTIONS(SHIFT(178)),
        [sym_type_qualifier] = ACTIONS(SHIFT(113)),
        [sym__expression] = ACTIONS(SHIFT(179)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [sym_macro_type] = ACTIONS(SHIFT(111)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(116)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(117)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(118)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_const] = ACTIONS(SHIFT(121)),
        [anon_sym_restrict] = ACTIONS(SHIFT(121)),
        [anon_sym_volatile] = ACTIONS(SHIFT(121)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(122)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [84] = {
        [sym__expression] = ACTIONS(SHIFT(85)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [85] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(SHIFT(87)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(88)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [86] = {
        [sym__expression] = ACTIONS(SHIFT(91)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(94)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [87] = {
        [sym__expression] = ACTIONS(SHIFT(90)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [88] = {
        [sym__expression] = ACTIONS(SHIFT(89)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [89] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(SHIFT(87)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [90] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [91] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(175)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(105)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(176)),
        [anon_sym_STAR] = ACTIONS(SHIFT(98)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(99)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [92] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [93] = {
        [sym__type_specifier] = ACTIONS(SHIFT(110)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(111)),
        [sym_struct_specifier] = ACTIONS(SHIFT(111)),
        [sym_type_name] = ACTIONS(SHIFT(112)),
        [sym_type_qualifier] = ACTIONS(SHIFT(113)),
        [sym__expression] = ACTIONS(SHIFT(114)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [sym_macro_type] = ACTIONS(SHIFT(111)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(116)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(117)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(118)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_const] = ACTIONS(SHIFT(121)),
        [anon_sym_restrict] = ACTIONS(SHIFT(121)),
        [anon_sym_volatile] = ACTIONS(SHIFT(121)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(122)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [94] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [95] = {
        [sym__expression] = ACTIONS(SHIFT(96)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [96] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(98)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(99)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [97] = {
        [sym__expression] = ACTIONS(SHIFT(102)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(103)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [98] = {
        [sym__expression] = ACTIONS(SHIFT(101)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [99] = {
        [sym__expression] = ACTIONS(SHIFT(100)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [100] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(98)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [101] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [102] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(104)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(105)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(106)),
        [anon_sym_STAR] = ACTIONS(SHIFT(98)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(99)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [103] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [104] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(109)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [105] = {
        [sym__expression] = ACTIONS(SHIFT(107)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [106] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [107] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(108)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(105)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(98)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(99)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [108] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(aux_sym_call_expression_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [109] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [110] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(174)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(153)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(153)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(153)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(154)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(155)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [111] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [112] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(172)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [113] = {
        [sym__type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_type_qualifier] = ACTIONS(SHIFT(113)),
        [sym_macro_type] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(171)),
        [anon_sym_signed] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_unsigned] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_long] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_short] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_struct] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [anon_sym_const] = ACTIONS(SHIFT(121)),
        [anon_sym_restrict] = ACTIONS(SHIFT(121)),
        [anon_sym_volatile] = ACTIONS(SHIFT(121)),
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_type_name_repeat1, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [114] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(170)),
        [anon_sym_STAR] = ACTIONS(SHIFT(128)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(129)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [115] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [116] = {
        [sym_identifier] = ACTIONS(SHIFT(169)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [117] = {
        [sym__type_specifier] = ACTIONS(SHIFT(150)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(111)),
        [sym_struct_specifier] = ACTIONS(SHIFT(111)),
        [sym_macro_type] = ACTIONS(SHIFT(111)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(116)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(118)),
        [sym_identifier] = ACTIONS(SHIFT(151)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [118] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(142)),
        [sym_identifier] = ACTIONS(SHIFT(143)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [119] = {
        [sym__type_specifier] = ACTIONS(SHIFT(110)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(111)),
        [sym_struct_specifier] = ACTIONS(SHIFT(111)),
        [sym_type_name] = ACTIONS(SHIFT(137)),
        [sym_type_qualifier] = ACTIONS(SHIFT(113)),
        [sym__expression] = ACTIONS(SHIFT(138)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [sym_macro_type] = ACTIONS(SHIFT(111)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(116)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(117)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(118)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_const] = ACTIONS(SHIFT(121)),
        [anon_sym_restrict] = ACTIONS(SHIFT(121)),
        [anon_sym_volatile] = ACTIONS(SHIFT(121)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(122)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [120] = {
        [sym__expression] = ACTIONS(SHIFT(126)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(115)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [121] = {
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
    [122] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1), SHIFT(123)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [123] = {
        [sym__type_specifier] = ACTIONS(SHIFT(124)),
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
    [124] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(125)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [125] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_macro_type, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [126] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(128)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(129)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [127] = {
        [sym__expression] = ACTIONS(SHIFT(132)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(133)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [128] = {
        [sym__expression] = ACTIONS(SHIFT(131)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(115)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [129] = {
        [sym__expression] = ACTIONS(SHIFT(130)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(115)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [130] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(SHIFT(128)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [131] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [132] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(134)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(105)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(135)),
        [anon_sym_STAR] = ACTIONS(SHIFT(98)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(99)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [133] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [134] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(136)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [135] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [136] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [137] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(140)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [138] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(139)),
        [anon_sym_STAR] = ACTIONS(SHIFT(128)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(129)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [139] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [140] = {
        [sym__expression] = ACTIONS(SHIFT(141)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(115)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [141] = {
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [142] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(148)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(149)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [143] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(144)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [144] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(145)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(146)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [145] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(147)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [146] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [147] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [148] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(146)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [149] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [150] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(152)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(153)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(153)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(153)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(154)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [anon_sym_STAR] = ACTIONS(SHIFT(155)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [151] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), SHIFT(123)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [152] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(157)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(158)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [153] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__abstract_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [154] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(167)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(153)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(153)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(153)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(154)),
        [anon_sym_STAR] = ACTIONS(SHIFT(155)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [155] = {
        [sym__abstract_declarator] = ACTIONS(SHIFT(156)),
        [sym_abstract_pointer_declarator] = ACTIONS(SHIFT(153)),
        [sym_abstract_function_declarator] = ACTIONS(SHIFT(153)),
        [sym_abstract_array_declarator] = ACTIONS(SHIFT(153)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_pointer_declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(154)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_pointer_declarator, 1)),
        [anon_sym_STAR] = ACTIONS(SHIFT(155)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [156] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(157)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(158)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [157] = {
        [sym__expression] = ACTIONS(SHIFT(164)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(165)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [158] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(159)),
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
        [anon_sym_RPAREN] = ACTIONS(SHIFT(160)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [159] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(161)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(162)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [160] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [161] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(163)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [162] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [163] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [164] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(166)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(SHIFT(87)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(88)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [165] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [166] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_abstract_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [167] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(157)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(158)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(168)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [168] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__abstract_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__abstract_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [169] = {
        [sym__abstract_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_abstract_pointer_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_abstract_function_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_abstract_array_declarator] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [170] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [171] = {
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
    [172] = {
        [sym__expression] = ACTIONS(SHIFT(173)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [173] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [174] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(157)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(158)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_type_name, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [175] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(177)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [176] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [177] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [178] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(181)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [179] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(180)),
        [anon_sym_STAR] = ACTIONS(SHIFT(128)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(129)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [180] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [181] = {
        [sym__expression] = ACTIONS(SHIFT(182)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [182] = {
        [anon_sym_RBRACK] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [183] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [184] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(189)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(190)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(201)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [185] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [186] = {
        [sym__declarator] = ACTIONS(SHIFT(199)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(185)),
        [sym_function_declarator] = ACTIONS(SHIFT(185)),
        [sym_array_declarator] = ACTIONS(SHIFT(185)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(186)),
        [anon_sym_STAR] = ACTIONS(SHIFT(187)),
        [sym_identifier] = ACTIONS(SHIFT(185)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [187] = {
        [sym__declarator] = ACTIONS(SHIFT(188)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(185)),
        [sym_function_declarator] = ACTIONS(SHIFT(185)),
        [sym_array_declarator] = ACTIONS(SHIFT(185)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(186)),
        [anon_sym_STAR] = ACTIONS(SHIFT(187)),
        [sym_identifier] = ACTIONS(SHIFT(185)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [188] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(189)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(190)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [189] = {
        [sym__expression] = ACTIONS(SHIFT(196)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(197)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [190] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(191)),
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
        [anon_sym_RPAREN] = ACTIONS(SHIFT(192)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [191] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(193)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(194)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [192] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [193] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(195)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [194] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [195] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [196] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(198)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(SHIFT(87)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(88)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [197] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [198] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [199] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(189)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(190)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(200)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [200] = {
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [201] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [202] = {
        [sym__declarator] = ACTIONS(SHIFT(203)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(69)),
        [sym_function_declarator] = ACTIONS(SHIFT(69)),
        [sym_array_declarator] = ACTIONS(SHIFT(69)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(70)),
        [anon_sym_STAR] = ACTIONS(SHIFT(71)),
        [sym_identifier] = ACTIONS(SHIFT(69)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [203] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(73)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(74)),
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_parameter_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [204] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(206)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(SHIFT(87)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(88)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [205] = {
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
    [206] = {
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
    [207] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(189)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(190)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(208)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [208] = {
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
    [209] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(35)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [210] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_struct_specifier, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [211] = {
        [anon_sym_RPAREN] = ACTIONS(REDUCE(sym_numeric_type_specifier, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [212] = {
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
    [213] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(219)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(220)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [214] = {
        [anon_sym_LBRACE] = ACTIONS(SHIFT(215)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [215] = {
        [sym__type_specifier] = ACTIONS(SHIFT(29)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_declaration] = ACTIONS(SHIFT(31)),
        [sym_macro_type] = ACTIONS(SHIFT(30)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(32)),
        [aux_sym_struct_specifier_repeat1] = ACTIONS(SHIFT(216)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(34)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(217)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [216] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(218)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [217] = {
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
    [218] = {
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
    [219] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(217)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [220] = {
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
    [221] = {
        [sym_identifier] = ACTIONS(REDUCE(aux_sym_numeric_type_specifier_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [222] = {
        [anon_sym_LF] = ACTIONS(SHIFT(223)),
        [sym_preproc_arg] = ACTIONS(SHIFT(224)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [223] = {
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
    [224] = {
        [anon_sym_LF] = ACTIONS(SHIFT(225)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [225] = {
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
    [226] = {
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
    [227] = {
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
    [228] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(376)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(367)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(377)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [229] = {
        [sym_compound_statement] = ACTIONS(SHIFT(246)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(247)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(248)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(234)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [230] = {
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
    [231] = {
        [sym__declarator] = ACTIONS(SHIFT(244)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(185)),
        [sym_function_declarator] = ACTIONS(SHIFT(185)),
        [sym_array_declarator] = ACTIONS(SHIFT(185)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(186)),
        [anon_sym_STAR] = ACTIONS(SHIFT(187)),
        [sym_identifier] = ACTIONS(SHIFT(185)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [232] = {
        [sym__declarator] = ACTIONS(SHIFT(233)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(230)),
        [sym_function_declarator] = ACTIONS(SHIFT(230)),
        [sym_array_declarator] = ACTIONS(SHIFT(230)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(231)),
        [anon_sym_STAR] = ACTIONS(SHIFT(232)),
        [sym_identifier] = ACTIONS(SHIFT(230)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [233] = {
        [sym_compound_statement] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(234)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [234] = {
        [sym__expression] = ACTIONS(SHIFT(241)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(242)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [235] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(236)),
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
        [anon_sym_RPAREN] = ACTIONS(SHIFT(237)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [236] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(238)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(239)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [237] = {
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
    [238] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(240)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [239] = {
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
    [240] = {
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
    [241] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(243)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(SHIFT(87)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(88)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [242] = {
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
    [243] = {
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
    [244] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(189)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(190)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(245)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [245] = {
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
    [246] = {
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
    [247] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(315)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(316)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(317)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym__expression] = ACTIONS(SHIFT(318)),
        [sym_cast_expression] = ACTIONS(SHIFT(319)),
        [sym_math_expression] = ACTIONS(SHIFT(319)),
        [sym_call_expression] = ACTIONS(SHIFT(319)),
        [sym_pointer_expression] = ACTIONS(SHIFT(319)),
        [sym__statement] = ACTIONS(SHIFT(317)),
        [sym_expression_statement] = ACTIONS(SHIFT(320)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(321)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(322)),
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
        [anon_sym_RBRACE] = ACTIONS(SHIFT(323)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(324)),
        [anon_sym_STAR] = ACTIONS(SHIFT(325)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [anon_sym_AMP] = ACTIONS(SHIFT(325)),
        [sym_string] = ACTIONS(SHIFT(319)),
        [sym_identifier] = ACTIONS(SHIFT(326)),
        [sym_number] = ACTIONS(SHIFT(319)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [248] = {
        [sym_initializer] = ACTIONS(SHIFT(249)),
        [sym__expression] = ACTIONS(SHIFT(250)),
        [sym_cast_expression] = ACTIONS(SHIFT(251)),
        [sym_math_expression] = ACTIONS(SHIFT(251)),
        [sym_call_expression] = ACTIONS(SHIFT(251)),
        [sym_pointer_expression] = ACTIONS(SHIFT(251)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(252)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(253)),
        [anon_sym_STAR] = ACTIONS(SHIFT(254)),
        [anon_sym_AMP] = ACTIONS(SHIFT(254)),
        [sym_string] = ACTIONS(SHIFT(251)),
        [sym_identifier] = ACTIONS(SHIFT(251)),
        [sym_number] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [249] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [250] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(256)),
        [anon_sym_STAR] = ACTIONS(SHIFT(257)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(258)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [251] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [252] = {
        [sym_initializer] = ACTIONS(SHIFT(271)),
        [sym_initializer_list] = ACTIONS(SHIFT(272)),
        [sym_designation] = ACTIONS(SHIFT(273)),
        [sym__expression] = ACTIONS(SHIFT(274)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(276)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(277)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(278)),
        [anon_sym_DOT] = ACTIONS(SHIFT(279)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [253] = {
        [sym__type_specifier] = ACTIONS(SHIFT(110)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(111)),
        [sym_struct_specifier] = ACTIONS(SHIFT(111)),
        [sym_type_name] = ACTIONS(SHIFT(266)),
        [sym_type_qualifier] = ACTIONS(SHIFT(113)),
        [sym__expression] = ACTIONS(SHIFT(267)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [sym_macro_type] = ACTIONS(SHIFT(111)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(116)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(117)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(118)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_const] = ACTIONS(SHIFT(121)),
        [anon_sym_restrict] = ACTIONS(SHIFT(121)),
        [anon_sym_volatile] = ACTIONS(SHIFT(121)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(122)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [254] = {
        [sym__expression] = ACTIONS(SHIFT(255)),
        [sym_cast_expression] = ACTIONS(SHIFT(251)),
        [sym_math_expression] = ACTIONS(SHIFT(251)),
        [sym_call_expression] = ACTIONS(SHIFT(251)),
        [sym_pointer_expression] = ACTIONS(SHIFT(251)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(253)),
        [anon_sym_STAR] = ACTIONS(SHIFT(254)),
        [anon_sym_AMP] = ACTIONS(SHIFT(254)),
        [sym_string] = ACTIONS(SHIFT(251)),
        [sym_identifier] = ACTIONS(SHIFT(251)),
        [sym_number] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [255] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(256)),
        [anon_sym_STAR] = ACTIONS(SHIFT(257)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(258)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [256] = {
        [sym__expression] = ACTIONS(SHIFT(261)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(262)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [257] = {
        [sym__expression] = ACTIONS(SHIFT(260)),
        [sym_cast_expression] = ACTIONS(SHIFT(251)),
        [sym_math_expression] = ACTIONS(SHIFT(251)),
        [sym_call_expression] = ACTIONS(SHIFT(251)),
        [sym_pointer_expression] = ACTIONS(SHIFT(251)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(253)),
        [anon_sym_STAR] = ACTIONS(SHIFT(254)),
        [anon_sym_AMP] = ACTIONS(SHIFT(254)),
        [sym_string] = ACTIONS(SHIFT(251)),
        [sym_identifier] = ACTIONS(SHIFT(251)),
        [sym_number] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [258] = {
        [sym__expression] = ACTIONS(SHIFT(259)),
        [sym_cast_expression] = ACTIONS(SHIFT(251)),
        [sym_math_expression] = ACTIONS(SHIFT(251)),
        [sym_call_expression] = ACTIONS(SHIFT(251)),
        [sym_pointer_expression] = ACTIONS(SHIFT(251)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(253)),
        [anon_sym_STAR] = ACTIONS(SHIFT(254)),
        [anon_sym_AMP] = ACTIONS(SHIFT(254)),
        [sym_string] = ACTIONS(SHIFT(251)),
        [sym_identifier] = ACTIONS(SHIFT(251)),
        [sym_number] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [259] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(256)),
        [anon_sym_STAR] = ACTIONS(SHIFT(257)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [260] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(256)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [261] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(263)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(105)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(264)),
        [anon_sym_STAR] = ACTIONS(SHIFT(98)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(99)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [262] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [263] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(265)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [264] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [265] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [266] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(269)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [267] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(268)),
        [anon_sym_STAR] = ACTIONS(SHIFT(128)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(129)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [268] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [269] = {
        [sym__expression] = ACTIONS(SHIFT(270)),
        [sym_cast_expression] = ACTIONS(SHIFT(251)),
        [sym_math_expression] = ACTIONS(SHIFT(251)),
        [sym_call_expression] = ACTIONS(SHIFT(251)),
        [sym_pointer_expression] = ACTIONS(SHIFT(251)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(253)),
        [anon_sym_STAR] = ACTIONS(SHIFT(254)),
        [anon_sym_AMP] = ACTIONS(SHIFT(254)),
        [sym_string] = ACTIONS(SHIFT(251)),
        [sym_identifier] = ACTIONS(SHIFT(251)),
        [sym_number] = ACTIONS(SHIFT(251)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [270] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [271] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [272] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(312)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(313)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [273] = {
        [sym_initializer] = ACTIONS(SHIFT(311)),
        [sym__expression] = ACTIONS(SHIFT(274)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(277)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [274] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(283)),
        [anon_sym_STAR] = ACTIONS(SHIFT(284)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(285)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [275] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [276] = {
        [anon_sym_EQ] = ACTIONS(SHIFT(310)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [277] = {
        [sym_initializer] = ACTIONS(SHIFT(271)),
        [sym_initializer_list] = ACTIONS(SHIFT(303)),
        [sym_designation] = ACTIONS(SHIFT(273)),
        [sym__expression] = ACTIONS(SHIFT(274)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(276)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(277)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(278)),
        [anon_sym_DOT] = ACTIONS(SHIFT(279)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [278] = {
        [sym__expression] = ACTIONS(SHIFT(300)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [279] = {
        [sym_identifier] = ACTIONS(SHIFT(298)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [280] = {
        [sym__type_specifier] = ACTIONS(SHIFT(110)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(111)),
        [sym_struct_specifier] = ACTIONS(SHIFT(111)),
        [sym_type_name] = ACTIONS(SHIFT(293)),
        [sym_type_qualifier] = ACTIONS(SHIFT(113)),
        [sym__expression] = ACTIONS(SHIFT(294)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [sym_macro_type] = ACTIONS(SHIFT(111)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(116)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(117)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(118)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_const] = ACTIONS(SHIFT(121)),
        [anon_sym_restrict] = ACTIONS(SHIFT(121)),
        [anon_sym_volatile] = ACTIONS(SHIFT(121)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(122)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [281] = {
        [sym__expression] = ACTIONS(SHIFT(282)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [282] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(283)),
        [anon_sym_STAR] = ACTIONS(SHIFT(284)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(285)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [283] = {
        [sym__expression] = ACTIONS(SHIFT(288)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(289)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [284] = {
        [sym__expression] = ACTIONS(SHIFT(287)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [285] = {
        [sym__expression] = ACTIONS(SHIFT(286)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [286] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(283)),
        [anon_sym_STAR] = ACTIONS(SHIFT(284)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [287] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(283)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [288] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(290)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(105)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(291)),
        [anon_sym_STAR] = ACTIONS(SHIFT(98)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(99)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [289] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [290] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(292)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [291] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [292] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [293] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(296)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [294] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(295)),
        [anon_sym_STAR] = ACTIONS(SHIFT(128)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(129)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [295] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [296] = {
        [sym__expression] = ACTIONS(SHIFT(297)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [297] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [298] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(299)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(278)),
        [anon_sym_DOT] = ACTIONS(SHIFT(279)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [299] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [300] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(301)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(SHIFT(87)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(88)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [301] = {
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(302)),
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 3)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(278)),
        [anon_sym_DOT] = ACTIONS(SHIFT(279)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [302] = {
        [anon_sym_EQ] = ACTIONS(REDUCE(aux_sym_designation_repeat1, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [303] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(304)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(305)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [304] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [305] = {
        [sym_initializer] = ACTIONS(SHIFT(306)),
        [sym_designation] = ACTIONS(SHIFT(307)),
        [sym__expression] = ACTIONS(SHIFT(274)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(276)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(277)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(308)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(278)),
        [anon_sym_DOT] = ACTIONS(SHIFT(279)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [306] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [307] = {
        [sym_initializer] = ACTIONS(SHIFT(309)),
        [sym__expression] = ACTIONS(SHIFT(274)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(277)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [308] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [309] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [310] = {
        [sym_initializer] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_LBRACE] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_designation, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_designation, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [311] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer_list, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [312] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [313] = {
        [sym_initializer] = ACTIONS(SHIFT(306)),
        [sym_designation] = ACTIONS(SHIFT(307)),
        [sym__expression] = ACTIONS(SHIFT(274)),
        [sym_cast_expression] = ACTIONS(SHIFT(275)),
        [sym_math_expression] = ACTIONS(SHIFT(275)),
        [sym_call_expression] = ACTIONS(SHIFT(275)),
        [sym_pointer_expression] = ACTIONS(SHIFT(275)),
        [aux_sym_designation_repeat1] = ACTIONS(SHIFT(276)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(277)),
        [anon_sym_RBRACE] = ACTIONS(SHIFT(314)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(278)),
        [anon_sym_DOT] = ACTIONS(SHIFT(279)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(280)),
        [anon_sym_STAR] = ACTIONS(SHIFT(281)),
        [anon_sym_AMP] = ACTIONS(SHIFT(281)),
        [sym_string] = ACTIONS(SHIFT(275)),
        [sym_identifier] = ACTIONS(SHIFT(275)),
        [sym_number] = ACTIONS(SHIFT(275)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [314] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_initializer, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_initializer, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [315] = {
        [sym__type_specifier] = ACTIONS(SHIFT(372)),
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
    [316] = {
        [sym__init_declarator] = ACTIONS(SHIFT(348)),
        [sym__declarator] = ACTIONS(SHIFT(349)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_STAR] = ACTIONS(SHIFT(352)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [317] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(315)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(316)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(6)),
        [sym_struct_specifier] = ACTIONS(SHIFT(6)),
        [sym_declaration] = ACTIONS(SHIFT(317)),
        [sym_type_qualifier] = ACTIONS(SHIFT(4)),
        [sym__expression] = ACTIONS(SHIFT(318)),
        [sym_cast_expression] = ACTIONS(SHIFT(319)),
        [sym_math_expression] = ACTIONS(SHIFT(319)),
        [sym_call_expression] = ACTIONS(SHIFT(319)),
        [sym_pointer_expression] = ACTIONS(SHIFT(319)),
        [sym__statement] = ACTIONS(SHIFT(317)),
        [sym_expression_statement] = ACTIONS(SHIFT(320)),
        [sym_macro_type] = ACTIONS(SHIFT(6)),
        [aux_sym_declaration_specifiers_repeat1] = ACTIONS(SHIFT(8)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(9)),
        [aux_sym_compound_statement_repeat1] = ACTIONS(SHIFT(346)),
        [ts_builtin_sym_error] = ACTIONS(SHIFT(347)),
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
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 1)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(324)),
        [anon_sym_STAR] = ACTIONS(SHIFT(325)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [anon_sym_AMP] = ACTIONS(SHIFT(325)),
        [sym_string] = ACTIONS(SHIFT(319)),
        [sym_identifier] = ACTIONS(SHIFT(326)),
        [sym_number] = ACTIONS(SHIFT(319)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [318] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(345)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(328)),
        [anon_sym_STAR] = ACTIONS(SHIFT(329)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(330)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [319] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [320] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_declaration] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_math_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_call_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym__statement] = ACTIONS(REDUCE(sym__statement, 1)),
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
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_const] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym__statement, 1)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_string] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_number] = ACTIONS(REDUCE(sym__statement, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [321] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(343)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [322] = {
        [anon_sym_RBRACE] = ACTIONS(SHIFT(343)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(344)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [323] = {
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
    [324] = {
        [sym__type_specifier] = ACTIONS(SHIFT(110)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(111)),
        [sym_struct_specifier] = ACTIONS(SHIFT(111)),
        [sym_type_name] = ACTIONS(SHIFT(338)),
        [sym_type_qualifier] = ACTIONS(SHIFT(113)),
        [sym__expression] = ACTIONS(SHIFT(339)),
        [sym_cast_expression] = ACTIONS(SHIFT(115)),
        [sym_math_expression] = ACTIONS(SHIFT(115)),
        [sym_call_expression] = ACTIONS(SHIFT(115)),
        [sym_pointer_expression] = ACTIONS(SHIFT(115)),
        [sym_macro_type] = ACTIONS(SHIFT(111)),
        [aux_sym_numeric_type_specifier_repeat1] = ACTIONS(SHIFT(116)),
        [aux_sym_type_name_repeat1] = ACTIONS(SHIFT(117)),
        [anon_sym_signed] = ACTIONS(SHIFT(13)),
        [anon_sym_unsigned] = ACTIONS(SHIFT(13)),
        [anon_sym_long] = ACTIONS(SHIFT(13)),
        [anon_sym_short] = ACTIONS(SHIFT(13)),
        [anon_sym_struct] = ACTIONS(SHIFT(118)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(119)),
        [anon_sym_STAR] = ACTIONS(SHIFT(120)),
        [anon_sym_const] = ACTIONS(SHIFT(121)),
        [anon_sym_restrict] = ACTIONS(SHIFT(121)),
        [anon_sym_volatile] = ACTIONS(SHIFT(121)),
        [anon_sym_AMP] = ACTIONS(SHIFT(120)),
        [sym_string] = ACTIONS(SHIFT(115)),
        [sym_identifier] = ACTIONS(SHIFT(122)),
        [sym_number] = ACTIONS(SHIFT(115)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [325] = {
        [sym__expression] = ACTIONS(SHIFT(327)),
        [sym_cast_expression] = ACTIONS(SHIFT(319)),
        [sym_math_expression] = ACTIONS(SHIFT(319)),
        [sym_call_expression] = ACTIONS(SHIFT(319)),
        [sym_pointer_expression] = ACTIONS(SHIFT(319)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(324)),
        [anon_sym_STAR] = ACTIONS(SHIFT(325)),
        [anon_sym_AMP] = ACTIONS(SHIFT(325)),
        [sym_string] = ACTIONS(SHIFT(319)),
        [sym_identifier] = ACTIONS(SHIFT(319)),
        [sym_number] = ACTIONS(SHIFT(319)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [326] = {
        [sym__init_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym__declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_pointer_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_function_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_array_declarator] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1), SHIFT(17)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__type_specifier, 1), REDUCE(sym__expression, 1)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 1)),
        [sym_identifier] = ACTIONS(REDUCE(sym__type_specifier, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [327] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_expression, 2)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(328)),
        [anon_sym_STAR] = ACTIONS(SHIFT(329)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(330)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [328] = {
        [sym__expression] = ACTIONS(SHIFT(333)),
        [sym_cast_expression] = ACTIONS(SHIFT(92)),
        [sym_math_expression] = ACTIONS(SHIFT(92)),
        [sym_call_expression] = ACTIONS(SHIFT(92)),
        [sym_pointer_expression] = ACTIONS(SHIFT(92)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(93)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(334)),
        [anon_sym_STAR] = ACTIONS(SHIFT(95)),
        [anon_sym_AMP] = ACTIONS(SHIFT(95)),
        [sym_string] = ACTIONS(SHIFT(92)),
        [sym_identifier] = ACTIONS(SHIFT(92)),
        [sym_number] = ACTIONS(SHIFT(92)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [329] = {
        [sym__expression] = ACTIONS(SHIFT(332)),
        [sym_cast_expression] = ACTIONS(SHIFT(319)),
        [sym_math_expression] = ACTIONS(SHIFT(319)),
        [sym_call_expression] = ACTIONS(SHIFT(319)),
        [sym_pointer_expression] = ACTIONS(SHIFT(319)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(324)),
        [anon_sym_STAR] = ACTIONS(SHIFT(325)),
        [anon_sym_AMP] = ACTIONS(SHIFT(325)),
        [sym_string] = ACTIONS(SHIFT(319)),
        [sym_identifier] = ACTIONS(SHIFT(319)),
        [sym_number] = ACTIONS(SHIFT(319)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [330] = {
        [sym__expression] = ACTIONS(SHIFT(331)),
        [sym_cast_expression] = ACTIONS(SHIFT(319)),
        [sym_math_expression] = ACTIONS(SHIFT(319)),
        [sym_call_expression] = ACTIONS(SHIFT(319)),
        [sym_pointer_expression] = ACTIONS(SHIFT(319)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(324)),
        [anon_sym_STAR] = ACTIONS(SHIFT(325)),
        [anon_sym_AMP] = ACTIONS(SHIFT(325)),
        [sym_string] = ACTIONS(SHIFT(319)),
        [sym_identifier] = ACTIONS(SHIFT(319)),
        [sym_number] = ACTIONS(SHIFT(319)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [331] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(328)),
        [anon_sym_STAR] = ACTIONS(SHIFT(329)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [332] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(328)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_math_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [333] = {
        [aux_sym_call_expression_repeat1] = ACTIONS(SHIFT(335)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(105)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(97)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(336)),
        [anon_sym_STAR] = ACTIONS(SHIFT(98)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(99)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [334] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [335] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(337)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [336] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [337] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym_call_expression, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [338] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(341)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [339] = {
        [anon_sym_LPAREN] = ACTIONS(SHIFT(127)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(340)),
        [anon_sym_STAR] = ACTIONS(SHIFT(128)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(129)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [340] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym__expression, 3)),
        [anon_sym_PLUS] = ACTIONS(REDUCE(sym__expression, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [341] = {
        [sym__expression] = ACTIONS(SHIFT(342)),
        [sym_cast_expression] = ACTIONS(SHIFT(319)),
        [sym_math_expression] = ACTIONS(SHIFT(319)),
        [sym_call_expression] = ACTIONS(SHIFT(319)),
        [sym_pointer_expression] = ACTIONS(SHIFT(319)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(324)),
        [anon_sym_STAR] = ACTIONS(SHIFT(325)),
        [anon_sym_AMP] = ACTIONS(SHIFT(325)),
        [sym_string] = ACTIONS(SHIFT(319)),
        [sym_identifier] = ACTIONS(SHIFT(319)),
        [sym_number] = ACTIONS(SHIFT(319)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [342] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [anon_sym_PLUS] = ACTIONS(REDUCE_FRAGILE(sym_cast_expression, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [343] = {
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
    [344] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 2)),
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
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [345] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_declaration] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym__statement] = ACTIONS(REDUCE(sym_expression_statement, 2)),
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
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_string] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_identifier] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_number] = ACTIONS(REDUCE(sym_expression_statement, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [346] = {
        [anon_sym_RBRACE] = ACTIONS(REDUCE(aux_sym_compound_statement_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [347] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(344)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [348] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(366)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(367)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(368)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [349] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(248)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(354)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(355)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [350] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 1)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 1)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [351] = {
        [sym__declarator] = ACTIONS(SHIFT(364)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(185)),
        [sym_function_declarator] = ACTIONS(SHIFT(185)),
        [sym_array_declarator] = ACTIONS(SHIFT(185)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(186)),
        [anon_sym_STAR] = ACTIONS(SHIFT(187)),
        [sym_identifier] = ACTIONS(SHIFT(185)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [352] = {
        [sym__declarator] = ACTIONS(SHIFT(353)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_STAR] = ACTIONS(SHIFT(352)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [353] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_pointer_declarator, 2)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(354)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(355)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [354] = {
        [sym__expression] = ACTIONS(SHIFT(361)),
        [sym_cast_expression] = ACTIONS(SHIFT(81)),
        [sym_math_expression] = ACTIONS(SHIFT(81)),
        [sym_call_expression] = ACTIONS(SHIFT(81)),
        [sym_pointer_expression] = ACTIONS(SHIFT(81)),
        [anon_sym_RBRACK] = ACTIONS(SHIFT(362)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(83)),
        [anon_sym_STAR] = ACTIONS(SHIFT(84)),
        [anon_sym_AMP] = ACTIONS(SHIFT(84)),
        [sym_string] = ACTIONS(SHIFT(81)),
        [sym_identifier] = ACTIONS(SHIFT(81)),
        [sym_number] = ACTIONS(SHIFT(81)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [355] = {
        [sym_declaration_specifiers] = ACTIONS(SHIFT(58)),
        [sym_storage_class_specifier] = ACTIONS(SHIFT(4)),
        [sym__type_specifier] = ACTIONS(SHIFT(59)),
        [sym_numeric_type_specifier] = ACTIONS(SHIFT(30)),
        [sym_struct_specifier] = ACTIONS(SHIFT(30)),
        [sym_parameter_declaration] = ACTIONS(SHIFT(356)),
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
        [anon_sym_RPAREN] = ACTIONS(SHIFT(357)),
        [anon_sym_const] = ACTIONS(SHIFT(15)),
        [anon_sym_restrict] = ACTIONS(SHIFT(15)),
        [anon_sym_volatile] = ACTIONS(SHIFT(15)),
        [sym_identifier] = ACTIONS(SHIFT(36)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [356] = {
        [aux_sym_function_declarator_repeat1] = ACTIONS(SHIFT(358)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(63)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(359)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [357] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [358] = {
        [anon_sym_RPAREN] = ACTIONS(SHIFT(360)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [359] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [360] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_function_declarator, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [361] = {
        [anon_sym_RBRACK] = ACTIONS(SHIFT(363)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(86)),
        [anon_sym_STAR] = ACTIONS(SHIFT(87)),
        [anon_sym_PLUS] = ACTIONS(SHIFT(88)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [362] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [363] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_array_declarator, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [364] = {
        [anon_sym_LBRACK] = ACTIONS(SHIFT(189)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(190)),
        [anon_sym_RPAREN] = ACTIONS(SHIFT(365)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [365] = {
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_EQ] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LBRACK] = ACTIONS(REDUCE(sym__declarator, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym__declarator, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [366] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(371)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [367] = {
        [sym__init_declarator] = ACTIONS(SHIFT(369)),
        [sym__declarator] = ACTIONS(SHIFT(349)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_STAR] = ACTIONS(SHIFT(352)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [368] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 3)),
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
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 3)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [369] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(370)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(367)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [370] = {
        [anon_sym_SEMI] = ACTIONS(REDUCE(aux_sym_declaration_repeat1, 3)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [371] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 4)),
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
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 4)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 4)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [372] = {
        [sym__init_declarator] = ACTIONS(SHIFT(373)),
        [sym__declarator] = ACTIONS(SHIFT(349)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(350)),
        [sym_function_declarator] = ACTIONS(SHIFT(350)),
        [sym_array_declarator] = ACTIONS(SHIFT(350)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(351)),
        [anon_sym_STAR] = ACTIONS(SHIFT(352)),
        [sym_identifier] = ACTIONS(SHIFT(350)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [373] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(374)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(367)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(371)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [374] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(375)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [375] = {
        [sym_declaration_specifiers] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_storage_class_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_numeric_type_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_struct_specifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_declaration] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_type_qualifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_cast_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_math_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_call_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_pointer_expression] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym__statement] = ACTIONS(REDUCE(sym_declaration, 5)),
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
        [anon_sym_RBRACE] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_LPAREN] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_STAR] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_const] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_restrict] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_volatile] = ACTIONS(REDUCE(sym_declaration, 5)),
        [anon_sym_AMP] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_string] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_identifier] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_number] = ACTIONS(REDUCE(sym_declaration, 5)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [376] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(378)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [377] = {
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
    [378] = {
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
    [379] = {
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
    [380] = {
        [sym__init_declarator] = ACTIONS(SHIFT(381)),
        [sym__declarator] = ACTIONS(SHIFT(382)),
        [sym_pointer_declarator] = ACTIONS(SHIFT(230)),
        [sym_function_declarator] = ACTIONS(SHIFT(230)),
        [sym_array_declarator] = ACTIONS(SHIFT(230)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(231)),
        [anon_sym_STAR] = ACTIONS(SHIFT(232)),
        [sym_identifier] = ACTIONS(SHIFT(230)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [381] = {
        [aux_sym_declaration_repeat1] = ACTIONS(SHIFT(384)),
        [anon_sym_COMMA] = ACTIONS(SHIFT(367)),
        [anon_sym_SEMI] = ACTIONS(SHIFT(378)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [382] = {
        [sym_compound_statement] = ACTIONS(SHIFT(383)),
        [aux_sym_declaration_repeat1] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_LBRACE] = ACTIONS(SHIFT(247)),
        [anon_sym_COMMA] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_SEMI] = ACTIONS(REDUCE(sym__init_declarator, 1)),
        [anon_sym_EQ] = ACTIONS(SHIFT(248)),
        [anon_sym_LBRACK] = ACTIONS(SHIFT(234)),
        [anon_sym_LPAREN] = ACTIONS(SHIFT(235)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [383] = {
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
    [384] = {
        [anon_sym_SEMI] = ACTIONS(SHIFT(385)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
    [385] = {
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
    [386] = {
        [ts_builtin_sym_end] = ACTIONS(REDUCE(aux_sym_translation_unit_repeat1, 2)),
        [sym_comment] = ACTIONS(SHIFT_EXTRA()),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_c);
